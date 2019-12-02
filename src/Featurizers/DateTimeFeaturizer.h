// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <chrono>
#include <ctime>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include <stdio.h>

#include "../Archive.h"
#include "Components/InferenceOnlyFeaturizerImpl.h"
#include "../Traits.h"
#include "Structs.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         DateTimeTransformer
///  \brief         A Transformer that takes a chrono::system_clock::time_point and
///                 returns a struct with all the data split out.
///
//std::chrono::system_clock::time_point
class DateTimeTransformer : public Components::InferenceOnlyTransformerImpl<std::int64_t, TimePoint> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = Components::InferenceOnlyTransformerImpl<std::int64_t, TimePoint>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    DateTimeTransformer(std::string optionalCountryName, std::string optionalDataRootDir=std::string());
    DateTimeTransformer(Archive &ar);

    // This constructor is necessary at the dataRootDir may be different between
    // the machine that created the archive and this machine that is deserializing it.
    DateTimeTransformer(Archive &ar, std::string dataRootDir);

    ~DateTimeTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(DateTimeTransformer);

    void save(Archive & ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using JsonStream                        = nlohmann::json;
    using HolidayMap                        = std::unordered_map<InputType, std::string>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::string const                         _countryName;

    HolidayMap                                _dateHolidayMap;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(InputType const &input, CallbackFunction const &callback) override;
    void flush_impl(CallbackFunction const &callback) override;
};

class DateTimeEstimator :
    public TransformerEstimator<
        typename DateTimeTransformer::InputType,
        typename DateTimeTransformer::TransformedType
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = TransformerEstimator<
        typename DateTimeTransformer::InputType,
        typename DateTimeTransformer::TransformedType
    >;

    using TransformerType                   = DateTimeTransformer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    nonstd::optional<std::string> const     Country;
    nonstd::optional<std::string> const     DataRootDir;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    static bool IsValidCountry(std::string const &value, nonstd::optional<std::string> dataRootDir=nonstd::optional<std::string>());
    static std::vector<std::string> GetSupportedCountries(nonstd::optional<std::string> dataRootDir=nonstd::optional<std::string>());

    DateTimeEstimator(
        AnnotationMapsPtr pAllColumnAnnotations,
        nonstd::optional<std::string> const &optionalCountryName,
        nonstd::optional<std::string> const &optionalDataRootDir
    );
    ~DateTimeEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(DateTimeEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;
    FitResult fit_impl(InputType const *pBuffer, size_t cBuffer) override;
    void complete_training_impl(void) override;

    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override;
};


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Implementation
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// |
// |  DateTimeTransformer
// |
// ----------------------------------------------------------------------
namespace {

#if (defined _WIN32)
    std::string GetBinaryPath(void) {
        char                                result[MAX_PATH];

        GetModuleFileName(nullptr, result, sizeof(result));

        unsigned long const                 error(GetLastError());

        if(error != 0)
            throw std::runtime_error(std::to_string(error));

        return result;
    }

    std::string GetDataDirectory(std::string optionalDataRootDir) {
        std::string const                   binaryPath(
            [&optionalDataRootDir](void) {
                if(optionalDataRootDir.empty() == false) {
                    if(*optionalDataRootDir.rbegin() == '\\')
                        optionalDataRootDir.resize(optionalDataRootDir.size() - 1);

                    unsigned long const     attributes(GetFileAttributes(optionalDataRootDir.c_str()));

                    if(attributes == INVALID_FILE_ATTRIBUTES || (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
                        throw std::invalid_argument("Invalid 'dataRootDir'");

                    return optionalDataRootDir;
                }

                std::string                 result(GetBinaryPath());

                return result.substr(0, result.find_last_of("\\"));
            }()
        );

        return binaryPath + "\\Data\\DateTimeFeaturizer\\";
    }

    bool EnumCountries(
        std::function<bool (std::string)> const &callback,
        std::string const &optionalDataRootDir
    ) {
        // Note that this code is not exception safe!
        std::string                         dataDir(GetDataDirectory(optionalDataRootDir) + "*");
        WIN32_FIND_DATA                     data;
        HANDLE                              handle;
        bool                                result(true);

        handle = FindFirstFile(dataDir.c_str(), &data);
        if(handle == INVALID_HANDLE_VALUE)
            return result;

        while(true) {
            if((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
                if(callback(data.cFileName) == false) {
                    result = false;
                    break;
                }
            }

            if(FindNextFile(handle, &data) == false)
                break;
        }

        FindClose(handle);
        return result;
    }

#else
#   if (defined __APPLE__)
    std::string GetBinaryPath(void) {
        char                                result[PATH_MAX + 1];
        uint32_t                            size(sizeof(result));

        if(_NSGetExecutablePath(result, &size) != 0)
            throw std::runtime_error("_NSGetExecutablePath");

        return result;
    }
#else
    std::string GetBinaryPath(void) {
        char                                result[PATH_MAX + 1];

        memset(result, 0x00, sizeof(result));

        ssize_t const                       count(readlink("/proc/self/exe", result, sizeof(result)));

        if(count < 0)
            throw std::runtime_error("readlink");

        return result;
    }
#endif

    std::string GetDataDirectory(std::string optionalDataRootDir) {
        std::string const                   binaryPath(
            [&optionalDataRootDir](void) {
                if(optionalDataRootDir.empty() == false) {
                    if(*optionalDataRootDir.rbegin() == '/')
                        optionalDataRootDir.resize(optionalDataRootDir.size() - 1);

                    DIR *                           dir(opendir(optionalDataRootDir.c_str()));

                    if(dir == nullptr)
                        throw std::invalid_argument("Invalid 'dataRootDir'");

                    closedir(dir);

                    return optionalDataRootDir;
                }

                std::string                 result(GetBinaryPath());

                return result.substr(0, result.find_last_of("/"));
            }()
        );

        return binaryPath + "/Data/DateTimeFeaturizer/";
    }

    bool EnumCountries(
        std::function<bool (std::string)> const &callback,
        std::string const &optionalDataRootDir
    ) {
        // Note that this code is not exception safe
        bool                                result(true);
        DIR *                               dir(opendir(GetDataDirectory(optionalDataRootDir).c_str()));

        if(dir == nullptr)
            return result;

        dirent *                            info(nullptr);

        while((info = readdir(dir)) != nullptr) {
            // Skip directories
            if(info->d_type == DT_DIR)
                continue;

            if(callback(info->d_name) == false)
                return false;
        }

        closedir(dir);

        return result;
    }

#endif

nlohmann::json GetJsonStream(std::string const & jsonFilename) {
    nlohmann::json                          holidaysByCountry;
    std::ifstream                           file(jsonFilename);

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    if(file)
        holidaysByCountry = nlohmann::json::parse(file);

    return holidaysByCountry;
}

std::string RemoveCountryExtension(std::string const &country) {
    std::string::size_type const            dot(country.find_last_of('.'));

    if(dot == std::string::npos)
        return country;

    return country.substr(0, dot);
}

bool DoesCountryMatch(std::string const &country, std::string query) {
    if(query == country)
        return true;

    // Remove the ext
    query = RemoveCountryExtension(query);
    if(query == country)
        return true;

    // Convert to lowercase
    std::transform(query.begin(), query.end(), query.begin(), [](char c) { return std::tolower(c); });
    if(query == country)
        return true;

    // Remove spaces
    query.erase(std::remove_if(query.begin(), query.end(), [](char c) { return std::isspace(c); }), query.end());
    if(query == country)
        return true;

    return false;
}

} // anonymous namespace

DateTimeTransformer::DateTimeTransformer(Archive &ar) :
    DateTimeTransformer(Traits<std::string>::deserialize(ar), "") {
}

DateTimeTransformer::DateTimeTransformer(Archive &ar, std::string dataRootDir) :
    DateTimeTransformer(Traits<std::string>::deserialize(ar), std::move(dataRootDir)) {
}

DateTimeTransformer::DateTimeTransformer(std::string optionalCountryName, std::string optionalDataRootDir):
    _countryName(std::move(optionalCountryName)) {

    if (!_countryName.empty()) {
        // Get the corresponding file
        std::string                         filename;

        if(
            EnumCountries(
                [this, &filename](std::string country) {
                    if(DoesCountryMatch(_countryName, country)) {
                        filename = std::move(country);

                        // Don't continue processing
                        return false;
                    }

                    return true;
                },
                optionalDataRootDir
            )
        ) {
            // A true return value means that we have enumerated through all of the country names and didn't find a match
            throw std::invalid_argument(_countryName);
        }

        JsonStream holidaysByCountry = GetJsonStream(GetDataDirectory(optionalDataRootDir) + filename);

        //Convert Jsonstream to std::unordered_map
        //Note that the map keys are generated with "Date" and "Holiday" so no need to check existence
        std::vector<InputType> dateVector = holidaysByCountry.at("Date").get<std::vector<InputType>>();
        std::vector<std::string> nameVector = holidaysByCountry.at("Holiday").get<std::vector<std::string>>();

        assert(dateVector.size() == nameVector.size());
        for (unsigned long iter = 0; iter < dateVector.size(); ++iter) {
            _dateHolidayMap[dateVector[iter]] = nameVector[iter];
        }
    }
}

void DateTimeTransformer::save(Archive & ar) const /*override*/ {
    Traits<std::string>::serialize(ar, _countryName);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
void DateTimeTransformer::execute_impl(InputType const &input, CallbackFunction const &callback) /*override*/ {
    std::chrono::time_point<std::chrono::system_clock> time(std::chrono::seconds {input} );
    TimePoint result = TimePoint(time);

    if (!_dateHolidayMap.empty()) {
        //Normalize dateKey by cast one day range of time into an exact time
        //86400 is the total number of seconds in a day, and as the holiday time is provided in a manner(00:00:00 in one
        //day, so we need to consider any time that falls into this day.
        InputType dateKey = (input - input % 86400);

        auto x = _dateHolidayMap.find(dateKey);
        if (x != _dateHolidayMap.end()) {
            result.holidayName = x->second;
        }
    }

    callback(std::move(result));
}

void DateTimeTransformer::flush_impl(CallbackFunction const &) /*override*/ {
}

// ----------------------------------------------------------------------
// |
// |  DateTimeEstimator
// |
// ----------------------------------------------------------------------
/*static*/ bool DateTimeEstimator::IsValidCountry(std::string const &value, nonstd::optional<std::string> dataRootDir) {
    // EnumCountries will return true if the enumeration completes
    // and false if it was terminated. In this case, termination means
    // that the country was found.
    return EnumCountries(
        [&value](std::string country) {
            // Continue if the countries don't match
            return DoesCountryMatch(value, std::move(country)) == false;
        },
        dataRootDir ? *dataRootDir : std::string()
    ) == false;
}

/*static*/ std::vector<std::string> DateTimeEstimator::GetSupportedCountries(nonstd::optional<std::string> dataRootDir) {
    std::vector<std::string>                results;

    EnumCountries(
        [&results](std::string country) {
            results.emplace_back(RemoveCountryExtension(country));
            return true;
        },
        dataRootDir ? *dataRootDir : std::string()
    );

    std::sort(results.begin(), results.end());

    return results;
}

DateTimeEstimator::DateTimeEstimator(
    AnnotationMapsPtr pAllColumnAnnotations,
    nonstd::optional<std::string> const &countryName,
    nonstd::optional<std::string> const &dataRootDir
) :
    BaseType("DateTimeEstimator", std::move(pAllColumnAnnotations)),
    Country(countryName),
    DataRootDir(dataRootDir) {
        if(Country && DateTimeEstimator::IsValidCountry(*Country, DataRootDir) == false) {
            char                            buffer[1024];

            snprintf(buffer, sizeof(buffer), "'%s' is not a supported country name", Country->c_str());
            throw std::invalid_argument(buffer);
        }
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
bool DateTimeEstimator::begin_training_impl(void) /*override*/ {
    return false;
}

FitResult DateTimeEstimator::fit_impl(InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

void DateTimeEstimator::complete_training_impl(void) /*override*/ {
}

typename DateTimeEstimator::BaseType::TransformerUniquePtr DateTimeEstimator::create_transformer_impl(void) /*override*/ {
    return std::make_unique<DateTimeTransformer>(
        Country ? *Country : std::string(),
        DataRootDir ? *DataRootDir : std::string()
    );
}


} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
