// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#include "DateTimeFeaturizer.h"
#ifdef _WIN32
    #include <direct.h>
    #include <Windows.h>
#else
#   if (defined __APPLE__)
#       include <mach-o/dyld.h>
#   endif

#   include <dirent.h>
#   include <unistd.h>
#endif

#ifdef _MSC_VER
inline struct tm *gmtime_r(time_t const* const timer, struct tm* const  result) {
    return gmtime_s(result, timer) == 0 ? result : nullptr;
}

#endif

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

// ----------------------------------------------------------------------
// |
// |  TimePoint
// |
// ----------------------------------------------------------------------
TimePoint::TimePoint(const std::chrono::system_clock::time_point& sysTime) {
    // Get to a tm to get what we need.
    // Eventually C++202x will have expanded chrono support that might
    // have what we need, but not yet!
    std::tm tmt;
    time_t tt = std::chrono::system_clock::to_time_t(sysTime);
    std::tm* res = gmtime_r(&tt, &tmt);
    if (res) {
        year = static_cast<std::int32_t>(tmt.tm_year) + 1900;
        month = static_cast<std::uint8_t>(tmt.tm_mon) + 1;
        day = static_cast<std::uint8_t>(tmt.tm_mday);
        hour = static_cast<std::uint8_t>(tmt.tm_hour);
        minute = static_cast<std::uint8_t>(tmt.tm_min);
        second = static_cast<std::uint8_t>(tmt.tm_sec);
        amPm = hour < 12 ? 0 : 1;
        hour12 = hour <= 12 ? hour : hour - 12;
        dayOfWeek = static_cast<std::uint8_t>(tmt.tm_wday);
        dayOfYear = static_cast<std::uint16_t>(tmt.tm_yday);
        weekOfMonth = (day - 1) / 7;
        quarterOfYear = (month + 2) / 3;
        halfOfYear = month <= 6 ? 1 : 2;

        date::year_month_day ymd = date::year_month_day{ date::year(year), date::month(month), date::day(day) };
        date::sys_days days(ymd);
        iso_week::year_weeknum_weekday iso_date = iso_week::year_weeknum_weekday{ days };

        // calculate the day of the quarter
        if(month <= 3){
            date::year_month_day startOfQuarter = date::year_month_day{ date::year(year), date::month(1), date::day(1) };
            dayOfQuarter = static_cast<uint8_t>(date::round<date::days>(days - startOfQuarter.operator date::sys_days()).count() + 1);
        }
        else if(month <= 6){
            date::year_month_day startOfQuarter = date::year_month_day{ date::year(year), date::month(4), date::day(1) };
            dayOfQuarter = static_cast<uint8_t>(date::round<date::days>(days - startOfQuarter.operator date::sys_days()).count() + 1);
        }
        else if(month <= 9){
            date::year_month_day startOfQuarter = date::year_month_day{ date::year(year), date::month(7), date::day(1) };
            dayOfQuarter = static_cast<uint8_t>(date::round<date::days>(days - startOfQuarter.operator date::sys_days()).count() + 1);
        }
        else{
            date::year_month_day startOfQuarter = date::year_month_day{ date::year(year), date::month(10), date::day(1) };
            dayOfQuarter = static_cast<uint8_t>(date::round<date::days>(days - startOfQuarter.operator date::sys_days()).count() + 1);
        }

        weekIso = static_cast<std::uint8_t>(iso_date.weeknum().operator unsigned());
        yearIso = iso_date.year().operator int();
        monthLabel = _months[month - 1];
        amPmLabel = amPm ? "pm" : "am";
        dayOfWeekLabel = _weekDays[dayOfWeek];
        holidayName = "";
        isPaidTimeOff = 0;               // TODO
    }
    else
    {
        if (tt < 0) {
            throw std::invalid_argument("Dates prior to 1970 are not supported.");
        }
        else {
            throw std::invalid_argument("Unknown error converting input date.");
        }
    }
}

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
    DateTimeTransformer(ar, "") {
}

DateTimeTransformer::DateTimeTransformer(Archive &ar, std::string dataRootDir) :
    DateTimeTransformer(
        [&ar, &dataRootDir](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            return DateTimeTransformer(Traits<std::string>::deserialize(ar), std::move(dataRootDir));
        }()
    ) {
}

DateTimeTransformer::DateTimeTransformer(std::string optionalCountryName, std::string optionalDataRootDir):
    _countryName(std::move(optionalCountryName)),
    _dateHolidayMap(
        [this, &optionalDataRootDir]() {
            if(_countryName.empty())
                return HolidayMap();

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
            std::vector<std::int64_t> dateVector = holidaysByCountry.at("Date").get<std::vector<std::int64_t>>();
            std::vector<std::string> nameVector = holidaysByCountry.at("Holiday").get<std::vector<std::string>>();
            HolidayMap                      holidays;

            assert(dateVector.size() == nameVector.size());
            for (unsigned long iter = 0; iter < dateVector.size(); ++iter) {
                holidays[dateVector[iter]] = nameVector[iter];
            }

            return holidays;
        }()
    ) {

}

bool DateTimeTransformer::operator==(DateTimeTransformer const &other) const {
    return _dateHolidayMap == other._dateHolidayMap;
}

void DateTimeTransformer::save(Archive & ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<std::string>::serialize(ar, _countryName);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
void DateTimeTransformer::execute_impl(InputType const &input, CallbackFunction const &callback) /*override*/ {
    static constexpr long long const        secondsPerDay(60 * 60 * 24);

    TimePoint                               result(input);

    if (!_dateHolidayMap.empty()) {
        // Values in the holiday map are based on midnight of the corresponding day. When looking up holidays for this time,
        // remove any seconds since midnight.
        long long const                     totalSeconds(std::chrono::time_point_cast<std::chrono::seconds>(input).time_since_epoch().count());
        long long const                     holidayKey(totalSeconds - (totalSeconds % secondsPerDay));
        HolidayMap::const_iterator const    iter(_dateHolidayMap.find(static_cast<std::int64_t>(holidayKey)));

        if(iter != _dateHolidayMap.end())
            result.holidayName = iter->second;
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
    return typename BaseType::TransformerUniquePtr(new DateTimeTransformer(
        Country ? *Country : std::string(),
        DataRootDir ? *DataRootDir : std::string()
    ));
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
