// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../DateTimeFeaturizer.h"

namespace NS = Microsoft::Featurizer;

using SysClock = std::chrono::system_clock;

TEST_CASE("DateTimeEstimator") {
    CHECK(strcmp(NS::Featurizers::DateTimeEstimator(NS::CreateTestAnnotationMapsPtr(2), nonstd::optional<std::string>(), nonstd::optional<std::string>()).Name, "DateTimeEstimator") == 0);

    NS::Featurizers::DateTimeEstimator      estimator(NS::CreateTestAnnotationMapsPtr(2), nonstd::optional<std::string>(), nonstd::optional<std::string>());

    estimator.begin_training();
    estimator.complete_training();

    CHECK(dynamic_cast<NS::Featurizers::DateTimeTransformer *>(estimator.create_transformer().get()));
}

TEST_CASE("DateTimeEstimator - IsValidCountry") {
    CHECK(NS::Featurizers::DateTimeEstimator::IsValidCountry("United States"));
    CHECK(NS::Featurizers::DateTimeEstimator::IsValidCountry("United States.json"));
    CHECK(NS::Featurizers::DateTimeEstimator::IsValidCountry("united states"));
    CHECK(NS::Featurizers::DateTimeEstimator::IsValidCountry("unitedstates"));

    CHECK(NS::Featurizers::DateTimeEstimator::IsValidCountry("This is not a valid country") == false);

    // Invalid data root dir
    CHECK_THROWS(NS::Featurizers::DateTimeEstimator::IsValidCountry("United States", "This is not a valid directory"));
}

TEST_CASE("DateTimeEstimator - GetSupportedCountries") {
    CHECK(
        NS::Featurizers::DateTimeEstimator::GetSupportedCountries() ==
        std::vector<std::string>{
            "Argentina",
            "Australia",
            "Austria",
            "Belarus",
            "Belgium",
            "Brazil",
            "Canada",
            "Colombia",
            "Croatia",
            "Czech",
            "Denmark",
            "England",
            "Finland",
            "France",
            "Germany",
            "Hungary",
            "India",
            "Ireland",
            "Isle of Man",
            "Italy",
            "Japan",
            "Mexico",
            "Netherlands",
            "New Zealand",
            "Northern Ireland",
            "Norway",
            "Poland",
            "Portugal",
            "Scotland",
            "Slovenia",
            "South Africa",
            "Spain",
            "Sweden",
            "Switzerland",
            "Ukraine",
            "United Kingdom",
            "United States",
            "Wales"
        }
    );
}

TEST_CASE("DateTimeTransformer - Countries") {
    // CHECK needs a well-understood value to validate, and a DateTimeTransformer
    // isn't one of those. Wrap the creation of the transformer in this method
    // that returns a well-understood bool. This works because the object will
    // either be created or it won't.

    // Note that clang x86 ran into an internal compiler error when this method
    // was implemented as an anonymous lambda.
    struct Internal {
        static bool Creator(std::string arg) {
            // This will either throw or it won't
            NS::Featurizers::DateTimeTransformer(std::move(arg));
            return true;
        }
    };

    CHECK(Internal::Creator(""));
    CHECK(Internal::Creator("United States"));
    CHECK(Internal::Creator("United States.json"));
    CHECK(Internal::Creator("united states"));
    CHECK(Internal::Creator("unitedstates"));
    CHECK_THROWS(Internal::Creator("This is not a valid country name"));
}

TEST_CASE("Past - 1976 Nov 17, 12:27:04", "[DateTimeTransformer][DateTime]") {
    const time_t date = 217081624;
    SysClock::time_point stp = SysClock::from_time_t(date);

    // Constructor
    NS::Featurizers::TimePoint tp(stp);
    CHECK(tp.year == 1976);
    CHECK(tp.month == NS::Featurizers::TimePoint::NOVEMBER);
    CHECK(tp.day == 17);
    CHECK(tp.hour == 12);
    CHECK(tp.minute == 27);
    CHECK(tp.second == 4);
    CHECK(tp.dayOfWeek == NS::Featurizers::TimePoint::WEDNESDAY);
    CHECK(tp.dayOfYear == 321);
    CHECK(tp.quarterOfYear == 4);
    CHECK(tp.weekOfMonth == 2);
    CHECK(tp.amPm == 1);
    CHECK(tp.hour12 == 12);
    CHECK(tp.dayOfQuarter == 48);
    CHECK(tp.halfOfYear == 2);
    CHECK(tp.weekIso == 47);
    CHECK(tp.yearIso == 1976);
    CHECK(tp.monthLabel == "November");
    CHECK(tp.amPmLabel == "pm");
    CHECK(tp.dayOfWeekLabel == "Wednesday");
    CHECK(tp.holidayName == "");
    CHECK(tp.isPaidTimeOff == 0);

    // assignment
    NS::Featurizers::TimePoint tp1 = stp;
    CHECK(tp1.year == 1976);
    CHECK(tp1.month == NS::Featurizers::TimePoint::NOVEMBER);
    CHECK(tp1.day == 17);

    // function
    NS::Featurizers::TimePoint tp2 = NS::Featurizers::TimePoint(stp);
    CHECK(tp2.year == 1976);
    CHECK(tp2.month == NS::Featurizers::TimePoint::NOVEMBER);
    CHECK(tp2.day == 17);
}

TEST_CASE("Past - 1976 Nov 17, 12:27:05", "[DateTimeTransformer][DateTimeTransformer]") {
    NS::Featurizers::DateTimeTransformer    dt("");
    NS::Featurizers::TimePoint              tp(dt.execute(217081625));

    CHECK(tp.year == 1976);
    CHECK(tp.month == NS::Featurizers::TimePoint::NOVEMBER);
    CHECK(tp.day == 17);
    CHECK(tp.hour == 12);
    CHECK(tp.minute == 27);
    CHECK(tp.second == 5);
    CHECK(tp.dayOfWeek == NS::Featurizers::TimePoint::WEDNESDAY);
    CHECK(tp.dayOfYear == 321);
    CHECK(tp.quarterOfYear == 4);
    CHECK(tp.weekOfMonth == 2);
    CHECK(true);

}

TEST_CASE("Future - 2025 June 30", "[DateTimeTransformer][DateTimeTransformer]") {
    NS::Featurizers::DateTimeTransformer dt("");
    NS::Featurizers::TimePoint tp = dt.execute(1751241600);
    CHECK(tp.year == 2025);
    CHECK(tp.month == NS::Featurizers::TimePoint::JUNE);
    CHECK(tp.day == 30);
    CHECK(tp.hour == 0);
    CHECK(tp.minute == 0);
    CHECK(tp.second == 0);
    CHECK(tp.dayOfWeek == NS::Featurizers::TimePoint::MONDAY);
    CHECK(tp.dayOfYear == 180);
    CHECK(tp.quarterOfYear == 2);
    CHECK(tp.weekOfMonth == 4);
    CHECK(tp.amPm == 0);
    CHECK(tp.hour12 == 0);
    CHECK(tp.dayOfQuarter == 91);
    CHECK(tp.halfOfYear == 1);
    CHECK(tp.weekIso == 27);
    CHECK(tp.yearIso == 2025);
    CHECK(tp.monthLabel == "June");
    CHECK(tp.amPmLabel == "am");
    CHECK(tp.dayOfWeekLabel == "Monday");
    CHECK(tp.holidayName == "");
    CHECK(tp.isPaidTimeOff == 0);
}

TEST_CASE("Holidays - No CountryName input - No Holiday date", "[DateTimeTransformer][DateTimeTransformer]") {
    NS::Featurizers::DateTimeTransformer dt("");
    NS::Featurizers::TimePoint tp = dt.execute(157161600);
    CHECK(tp.holidayName == "");
}

TEST_CASE("Holidays - Canada - Christmas Day", "[DateTimeTransformer][DateTimeTransformer]") {
    NS::Featurizers::DateTimeTransformer dt("Canada");
    NS::Featurizers::TimePoint tp = dt.execute(157161600);
    CHECK(tp.holidayName == "Christmas Day");
}

TEST_CASE("Holidays - Canada - Christmas Day ++", "[DateTimeTransformer][DateTimeTransformer]") {
    NS::Featurizers::DateTimeTransformer dt("Canada");
    NS::Featurizers::TimePoint tp = dt.execute(157161650);
    CHECK(tp.holidayName == "Christmas Day");
}

TEST_CASE("Holidays - Canada - 1 day before Christmas Day", "[DateTimeTransformer][DateTimeTransformer]") {
    NS::Featurizers::DateTimeTransformer dt("Canada");
    NS::Featurizers::TimePoint tp = dt.execute(157161599);
    CHECK(tp.holidayName == "1 day before Christmas Day");
}

TEST_CASE("Holidays - Finland - 1 day before Juhannusaatto", "[DateTimeTransformer][DateTimeTransformer]") {
    NS::Featurizers::DateTimeTransformer dt("Finland");
    NS::Featurizers::TimePoint tp = dt.execute(1088035200);
    CHECK(tp.holidayName == "1 day before Juhannusaatto");
}

TEST_CASE("Holidays - Finland - No Holiday date", "[DateTimeTransformer][DateTimeTransformer]") {
    NS::Featurizers::DateTimeTransformer dt("Finland");
    NS::Featurizers::TimePoint tp = dt.execute(227813600);
    CHECK(tp.holidayName == "");
}

#ifdef _MSC_VER
// others define system_clock::time_point as nanoseconds (64-bit),
// which rolls over somewhere around 2260. Still a couple hundred years!
TEST_CASE("Far Future - 2998 March 2, 14:03:02", "[DateTimeTransformer][DateTimeTransformer]") {

    NS::Featurizers::DateTimeTransformer dt("");
    NS::Featurizers::TimePoint tp = dt.execute(32445842582);
    CHECK(tp.year == 2998);
    CHECK(tp.month == NS::Featurizers::TimePoint::MARCH);
    CHECK(tp.day == 2);
    CHECK(tp.hour == 14);
    CHECK(tp.minute == 3);
    CHECK(tp.second == 2);
    CHECK(tp.dayOfWeek == NS::Featurizers::TimePoint::FRIDAY);
    CHECK(tp.dayOfYear == 60);
    CHECK(tp.quarterOfYear == 1);
    CHECK(tp.weekOfMonth == 0);
}

#else

// msvcrt doesn't support negative time_t, so nothing before 1970
TEST_CASE("Pre-Epoch - 1776 July 4", "[DateTimeTransformer][DateTimeTransformer]")
{

    // Constructor
    NS::Featurizers::DateTimeTransformer dt("");
    NS::Featurizers::TimePoint tp = dt.execute(-6106060800);
    CHECK(tp.year == 1776);
    CHECK(tp.month == NS::Featurizers::TimePoint::JULY);
    CHECK(tp.day == 4);
}
#endif /* _MSVCRT */
