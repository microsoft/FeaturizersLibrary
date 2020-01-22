// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_MedianImputerFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("int32 - odd number of items") {
    MedianImputerFeaturizer_int32_Test(
        std::vector<nonstd::optional<int>>{
            30,
            50,
            40,
            nonstd::optional<int>(),
            nonstd::optional<int>(),
            10,
            20
        },
        std::vector<nonstd::optional<int>>{
            1,
            2,
            3,
            nonstd::optional<int>(),
            nonstd::optional<int>(),
            4,
            5,
            nonstd::optional<int>()
        },
        [](std::vector<double> const &args) {
            return args == std::vector<double>{
                1,
                2,
                3,
                30,
                30,
                4,
                5,
                30
            };
        }
    );
}

TEST_CASE("int32 - even number of items") {
    MedianImputerFeaturizer_int32_Test(
        std::vector<nonstd::optional<int>>{
            30,
            50,
            40,
            nonstd::optional<int>(),
            nonstd::optional<int>(),
            10,
            20,
            60
        },
        std::vector<nonstd::optional<int>>{
            1,
            2,
            3,
            nonstd::optional<int>(),
            nonstd::optional<int>(),
            4,
            5,
            nonstd::optional<int>()
        },
        [](std::vector<double> const &args) {
            return args == std::vector<double>{
                1,
                2,
                3,
                35,
                35,
                4,
                5,
                35
            };
        }
    );
}

TEST_CASE("float - odd number of items") {
    MedianImputerFeaturizer_float_Test(
        std::vector<float>{
            30,
            50,
            40,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            std::numeric_limits<std::float_t>::quiet_NaN(),
            10,
            20
        },
        std::vector<float>{
            1,
            2,
            3,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            std::numeric_limits<std::float_t>::quiet_NaN(),
            4,
            5,
            std::numeric_limits<std::float_t>::quiet_NaN()
        },
        [](std::vector<double> const &args) {
            return args == std::vector<double>{
                1,
                2,
                3,
                30,
                30,
                4,
                5,
                30
            };
        }
    );
}

TEST_CASE("float - even number of items") {
    MedianImputerFeaturizer_float_Test(
        std::vector<float>{
            30,
            50,
            40,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            std::numeric_limits<std::float_t>::quiet_NaN(),
            10,
            20,
            60
        },
        std::vector<float>{
            1,
            2,
            3,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            std::numeric_limits<std::float_t>::quiet_NaN(),
            4,
            5,
            std::numeric_limits<std::float_t>::quiet_NaN()
        },
        [](std::vector<double> const &args) {
            return args == std::vector<double>{
                1,
                2,
                3,
                35,
                35,
                4,
                5,
                35
            };
        }
    );
}

TEST_CASE("string - odd number of items") {
    MedianImputerFeaturizer_string_Test(
        std::vector<nonstd::optional<std::string>>{
            "30",
            "50",
            "40",
            nonstd::optional<std::string>(),
            nonstd::optional<std::string>(),
            "10",
            "20"
        },
        std::vector<nonstd::optional<std::string>>{
            "1",
            "2",
            "3",
            nonstd::optional<std::string>(),
            nonstd::optional<std::string>(),
            "4",
            "5",
            nonstd::optional<std::string>()
        },
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{
                "1",
                "2",
                "3",
                "30",
                "30",
                "4",
                "5",
                "30"
            };
        }
    );
}

TEST_CASE("string - even number of items") {
    MedianImputerFeaturizer_string_Test(
        std::vector<nonstd::optional<std::string>>{
            "30",
            "50",
            "40",
            nonstd::optional<std::string>(),
            nonstd::optional<std::string>(),
            "10",
            "20",
            "60"
        },
        std::vector<nonstd::optional<std::string>>{
            "1",
            "2",
            "3",
            nonstd::optional<std::string>(),
            nonstd::optional<std::string>(),
            "4",
            "5",
            nonstd::optional<std::string>()
        },
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{
                "1",
                "2",
                "3",
                "30",
                "30",
                "4",
                "5",
                "30"
            };
        }
    );
}
