// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_DateTimeFeaturizer.h"

TEST_CASE("Standard") {
    DateTimeFeaturizer_Test(
        std::vector<std::int64_t>(),
        std::vector<std::int64_t>{1751241600, 217081625},
        [](std::vector<TimePoint *> const &args) {
            if(args.size() != 2)
                return false;

            // First value
            TimePoint const &               tp1(*args[0]);

            if(tp1.year != 2025) return false;
            if(tp1.month != 6) return false;
            if(tp1.day != 30) return false;
            if(strcmp(tp1.monthLabel_ptr, "June") != 0) return false;

            // Second value
            TimePoint const &               tp2(*args[1]);

            if(tp2.year != 1976) return false;
            if(tp2.month != 11) return false;
            if(tp2.day != 17) return false;
            if(strcmp(tp2.monthLabel_ptr, "November") != 0) return false;

            return true;
        }
    );
}
