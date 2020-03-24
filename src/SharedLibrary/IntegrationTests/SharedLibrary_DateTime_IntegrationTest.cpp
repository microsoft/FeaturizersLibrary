// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_DateTimeFeaturizer.h"
#include "../SharedLibrary_DateTimeFeaturizerCustom.h"

TEST_CASE("Standard - int64") {
    DateTimeFeaturizer_Test(
        std::vector<std::int64_t>(),
        std::vector<std::int64_t>{1751241600, 217081625},
        [](std::vector<TimePoint> const &args) {
            if(args.size() != 2)
                return false;

            // First value
            TimePoint const &               tp1(args[0]);

            if(tp1.year != 2025) return false;
            if(tp1.month != 6) return false;
            if(tp1.day != 30) return false;
            if(strcmp(tp1.monthLabel, "June") != 0) return false;

            // Second value
            TimePoint const &               tp2(args[1]);

            if(tp2.year != 1976) return false;
            if(tp2.month != 11) return false;
            if(tp2.day != 17) return false;
            if(strcmp(tp2.monthLabel, "November") != 0) return false;

            return true;
        },
        nullptr,
        nullptr
    );
}

TEST_CASE("Standard - string") {
    DateTimeFeaturizer_Test(
        std::vector<std::string>(),
        std::vector<std::string>{"2025-06-30T10:23:01Z", "1976-11-17T21:22:23Z"},
        [](std::vector<TimePoint> const &args) {
            if(args.size() != 2)
                return false;

            // First value
            TimePoint const &               tp1(args[0]);

            if(tp1.year != 2025) return false;
            if(tp1.month != 6) return false;
            if(tp1.day != 30) return false;
            if(tp1.hour != 10) return false;
            if(tp1.minute != 23) return false;
            if(tp1.second != 1) return false;
            if(strcmp(tp1.monthLabel, "June") != 0) return false;

            // Second value
            TimePoint const &               tp2(args[1]);

            if(tp2.year != 1976) return false;
            if(tp2.month != 11) return false;
            if(tp2.day != 17) return false;
            if(tp2.hour != 21) return false;
            if(tp2.minute != 22) return false;
            if(tp2.second != 23) return false;
            if(strcmp(tp2.monthLabel, "November") != 0) return false;

            return true;
        },
        nullptr,
        nullptr
    );
}

TEST_CASE("IsValidCountry") {
    ErrorInfoHandle *                       pErrorInfo(nullptr);
    bool                                    result;

    result = false;
    CHECK(DateTimeFeaturizer_IsValidCountry("United States", nullptr, &result, &pErrorInfo));
    CHECK(pErrorInfo == nullptr);
    CHECK(result);

    result = false;
    CHECK(DateTimeFeaturizer_IsValidCountry("united states", nullptr, &result, &pErrorInfo));
    CHECK(pErrorInfo == nullptr);
    CHECK(result);

    result = false;
    CHECK(DateTimeFeaturizer_IsValidCountry("unitedstates", nullptr, &result, &pErrorInfo));
    CHECK(pErrorInfo == nullptr);
    CHECK(result);

    result = true;
    CHECK(DateTimeFeaturizer_IsValidCountry("not a valid country", nullptr, &result, &pErrorInfo));
    CHECK(pErrorInfo == nullptr);
    CHECK(result == false);
}

TEST_CASE("GetSupportedCountries") {
    ErrorInfoHandle *                       pErrorInfo(nullptr);
    StringBuffer *                          pStringBuffers(nullptr);
    size_t                                  numStringBuffers;

    CHECK(DateTimeFeaturizer_GetSupportedCountries(nullptr, &pStringBuffers, &numStringBuffers, &pErrorInfo));
    CHECK(pErrorInfo == nullptr);
    REQUIRE(pStringBuffers != nullptr);
    REQUIRE(numStringBuffers != 0);

    // Spot check a few of the values
    CHECK(strcmp(pStringBuffers->pString, "Argentina") == 0);
    CHECK(strcmp((pStringBuffers + numStringBuffers - 1)->pString, "Wales") == 0);

    CHECK(DateTimeFeaturizer_DestroyStringBuffers(pStringBuffers, numStringBuffers, &pErrorInfo));
    CHECK(pErrorInfo == nullptr);
}
