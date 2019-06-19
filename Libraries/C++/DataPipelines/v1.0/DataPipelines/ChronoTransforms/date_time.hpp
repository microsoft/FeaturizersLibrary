// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#pragma once

#include <chrono>
#include <ctime>

namespace DataPipelines::Chrono {
    struct TimePoint {
        int32_t year = 0;
        uint8_t month = 0;      /* 1-12 */
        uint8_t day = 0;        /* 1-31 */
        uint8_t hour = 0;       /* 0-23 */
        uint8_t minute = 0;     /* 0-59 */
        uint8_t second = 0;     /* 0-59 */
        uint8_t dayOfWeek = 0;  /* 0-6 */
        uint16_t dayOfYear = 0; /* 0-365 */
        uint8_t quarterOfYear = 0; /* 1-4 */
        uint8_t weekOfMonth = 0; /* 0-4 */

        TimePoint(const std::chrono::system_clock::time_point& sysTime);

        TimePoint(TimePoint&&) = default;
        TimePoint(const TimePoint&) = delete;
        TimePoint& operator=(const TimePoint&) = delete;

        enum { 
            JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, 
            JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
        };
        enum {
            SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
        };
    };

    inline TimePoint SystemToDPTimePoint(const std::chrono::system_clock::time_point& sysTime) {
        return TimePoint (sysTime);
    }
}
