// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#include "DateTimeFeaturizer.h"
#ifdef _WIN32
    #include <direct.h>
    #include <Windows.h>
#else
    #include <unistd.h>
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
    std::string GetBinaryPath() {
        #ifdef _WIN32
            char result[ MAX_PATH ];
            std::string binaryPath = std::string( result, GetModuleFileName( nullptr, result, MAX_PATH ) );
            unsigned long ret = GetLastError();
            if (ret != 0) {
                throw std::runtime_error(std::to_string(ret));
            }
        #else
            char result[ PATH_MAX ];
            ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
            if (count < 0) {
                throw std::runtime_error("readlink");
            }
            std::string binaryPath = std::string( result, (count > 0) ? count : 0 );
        #endif
        return binaryPath;
    }

    nlohmann::json GetJsonStream(std::string const & _countryName) {
        nlohmann::json holidaysByCountry;

        std::string jsonFilename = _countryName + ".json";
        std::string binaryPath = GetBinaryPath();
        #ifdef _WIN32
            std::string path = binaryPath.substr(0, binaryPath.find_last_of("\\")) + "\\Data\\DateTimeFeaturizer\\" + jsonFilename;
        #else
            std::string path = binaryPath.substr(0, binaryPath.find_last_of("/")) + "/Data/DateTimeFeaturizer/" + jsonFilename;
        #endif

        std::ifstream file(path);
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        if (file) {
            holidaysByCountry = nlohmann::json::parse(file);
        }
        return holidaysByCountry;
    }
}

DateTimeTransformer::DateTimeTransformer(Archive &ar) :
    _countryName(Traits<std::string>::deserialize(ar)) {
    DateTimeTransformer(this->_countryName);
}

DateTimeTransformer::DateTimeTransformer(nonstd::optional<std::string> const & countryName):
    _countryName(countryName.has_value() ? countryName.value() : std::string()) {

    if (!_countryName.empty()) {
        JsonStream holidaysByCountry = GetJsonStream(_countryName);

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

DateTimeTransformer::TransformedType DateTimeTransformer::execute(InputType input) /*override*/ {
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
    return result;
}

void DateTimeTransformer::save(Archive & ar) const /*override*/ {
    Traits<std::string>::serialize(ar, _countryName);
}

// ----------------------------------------------------------------------
// |
// |  DateTimeEstimator
// |
// ----------------------------------------------------------------------
DateTimeEstimator::DateTimeEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("DateTimeEstimator", std::move(pAllColumnAnnotations)) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
