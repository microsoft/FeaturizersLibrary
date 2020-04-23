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

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wold-style-cast"
#   pragma clang diagnostic ignored "-Wshift-sign-overflow"
#   pragma clang diagnostic ignored "-Wsign-conversion"

#   if (!defined __apple_build_version__ )
#       pragma clang diagnostic ignored "-Wimplicit-int-conversion"
#   endif
#elif (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4244) // conversion from 'unsigned int' to 'unsigned char', possible loss of data
#endif

#include "../3rdParty/iso_week.h"
#include "../3rdParty/json.h"

#if (defined __clang__)
#   pragma clang diagnostic pop
#elif (defined _MSC_VER)
#   pragma warning(pop)
#endif

#include "../Archive.h"
#include "Components/InferenceOnlyFeaturizerImpl.h"
#include "../Traits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \fn            IsValidDirectory
///  \brief         Returns true if the specified directory is valid.
///
bool IsValidDirectory(std::string const &dirname);

/////////////////////////////////////////////////////////////////////////
///  \fn            GetExecutable
///  \brief         Returns the fullpath of the current executable.
///
std::string GetExecutable(void);

/////////////////////////////////////////////////////////////////////////
///  \fn            GetDateTimeFeaturizerDataDirectory
///  \brief         Returns the fullpath of the data directory. The executable's
///                 path is used as the root if `optionalDataRootDir` is empty.
///
std::string GetDateTimeFeaturizerDataDirectory(std::string optionalDataRootDir);

/////////////////////////////////////////////////////////////////////////
///  \struct        TimePoint
///  \brief         Struct to hold various components of DateTime information
///
struct TimePoint {
    std::int32_t year = 0;          // calendar year
    std::uint8_t month = 0;         // calendar month, 1 through 12
    std::uint8_t day = 0;           // calendar day of month, 1 through 31
    std::uint8_t hour = 0;          // hour of day, 0 through 23
    std::uint8_t minute = 0;        // minute of day, 0 through 59
    std::uint8_t second = 0;        // second of day, 0 through 59
    std::uint8_t amPm = 0;          // 0 if hour is before noon (12 pm), 1 otherwise
    std::uint8_t hour12 = 0;        // hour of day on a 12 basis, without the AM/PM piece
    std::uint8_t dayOfWeek = 0;     // day of week, 0 (Monday) through 6 (Sunday)
    std::uint8_t dayOfQuarter = 0;  // day of quarter, 1 through 92
    std::uint16_t dayOfYear = 0;    // day of year, 1 through 366
    std::uint16_t weekOfMonth = 0;  // week of the month, 0 - 4
    std::uint8_t quarterOfYear = 0; // calendar quarter, 1 through 4
    std::uint8_t halfOfYear = 0;    // 1 if date is prior to July 1, 2 otherwise
    std::uint8_t weekIso = 0;       // ISO week, see below for details
    std::int32_t yearIso = 0;      // ISO year, see details later
    std::string monthLabel = "";    // calendar month as string, 'January' through 'December'
    std::string amPmLabel = "";     // 'am' if hour is before noon (12 pm), 'pm' otherwise
    std::string dayOfWeekLabel = "";// day of week as string
    std::string holidayName = "";   // If a country is provided, we check if the date is a holiday
    std::uint8_t isPaidTimeOff = 0; // If its a holiday, is it PTO

    // ISO year and week are defined in ISO 8601, see Wikipedia.ISO for details.
    // In short, ISO weeks always start on Monday and last 7 days.
    // ISO years start on the first week of year that has a Thursday.
    // This means if January 1 falls on a Friday, ISO year will begin only on
    // January 4. As such, ISO years may differ from calendar years.

    TimePoint(const std::chrono::system_clock::time_point& sysTime);

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TimePoint);

    enum {
        JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE,
        JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
    };
    enum {
        SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
    };

private:
    const std::string _weekDays[7] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    };

    const std::string _months[12] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
};

/////////////////////////////////////////////////////////////////////////
///  \class         DateTimeTransformer
///  \brief         A Transformer that takes a chrono::system_clock::time_point and
///                 returns a struct with all the data split out.
///
class DateTimeTransformer : public Components::InferenceOnlyTransformerImpl<std::chrono::system_clock::time_point, TimePoint> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = Components::InferenceOnlyTransformerImpl<std::chrono::system_clock::time_point, TimePoint>;

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

    bool operator==(DateTimeTransformer const &other) const;

    void save(Archive & ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using JsonStream                        = nlohmann::json;
    using HolidayMap                        = std::unordered_map<std::int64_t, std::string>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::string const                       _countryName;
    HolidayMap const                        _dateHolidayMap;

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

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
