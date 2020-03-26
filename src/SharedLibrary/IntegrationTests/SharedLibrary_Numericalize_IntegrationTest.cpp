// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_NumericalizeFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("int") {
    NumericalizeFeaturizer_int32_Test(
        std::vector<int>{
            10,
            20,
            30,
            40,
            50
        },
        std::vector<int>{
            3,
            10,
            2,
            20,
            30,
            40,
            50,
            1
        },
        [](std::vector<std::double_t> const &args) {
            std::vector<std::double_t> const            expected{
                std::numeric_limits<double>::quiet_NaN(),
                0.0,
                std::numeric_limits<double>::quiet_NaN(),
                1.0,
                2.0,
                3.0,
                4.0,
                std::numeric_limits<double>::quiet_NaN()
            };

            REQUIRE(args.size() == expected.size());

            for(size_t i=0; i < args.size(); ++i) {
                bool const                  arg_nan(std::isnan(args[i]));
                bool const                  expected_nan(std::isnan(expected[i]));

                if(arg_nan || expected_nan)
                    CHECK(arg_nan == expected_nan);
                else
                    CHECK(Approx(args[i]) == expected[i]);
            }

            return true;
        }
    );
}

TEST_CASE("string") {
    NumericalizeFeaturizer_string_Test(
        std::vector<std::string>{
            "10",
            "20",
            "30",
            "40",
            "50"
        },
        std::vector<std::string>{
            "3",
            "10",
            "2",
            "20",
            "30",
            "40",
            "50",
            "1"
        },
        [](std::vector<std::double_t> const &args) {
            std::vector<std::double_t> const            expected{
                std::numeric_limits<double>::quiet_NaN(),
                0.0,
                std::numeric_limits<double>::quiet_NaN(),
                1.0,
                2.0,
                3.0,
                4.0,
                std::numeric_limits<double>::quiet_NaN()
            };

            REQUIRE(args.size() == expected.size());

            for(size_t i=0; i < args.size(); ++i) {
                bool const                  arg_nan(std::isnan(args[i]));
                bool const                  expected_nan(std::isnan(expected[i]));

                if(arg_nan || expected_nan)
                    CHECK(arg_nan == expected_nan);
                else
                    CHECK(Approx(args[i]) == expected[i]);
            }

            return true;
        }
    );
}
