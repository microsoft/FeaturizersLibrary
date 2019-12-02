// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once
#include "../Featurizer.h"


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

/////////////////////////////////////////////////////////////////////////
///  \struct        OneHotStruct
///  \brief         Struct to hold return value of one hot encoder,
///                 consist of <category index, total size of category, # of appearances>
///
struct OneHotStruct {
    std::uint32_t const index;                                    // category index
    std::uint32_t const size;                                     // category total size
    std::uint32_t const appearances;                              // number of appearances

    OneHotStruct(std::uint32_t i, std::uint32_t s, std::uint32_t a);
    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(OneHotStruct);
    bool operator==(OneHotStruct const &other) const;
};

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
// |  OneHotStruct
// |
// ----------------------------------------------------------------------

bool OneHotStruct::operator==(OneHotStruct const &other) const {
    return (appearances == other.appearances) && (index == other.index) && (size == other.size);
}
OneHotStruct::OneHotStruct(std::uint32_t i, std::uint32_t s, std::uint32_t a) :
    index(std::move(i)),
    size(std::move(s)),
    appearances(std::move(a)) {
        if (index >= size) {
            throw std::invalid_argument("Category index should be smaller than total number of categories!");
        }
}

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

}
}
}
