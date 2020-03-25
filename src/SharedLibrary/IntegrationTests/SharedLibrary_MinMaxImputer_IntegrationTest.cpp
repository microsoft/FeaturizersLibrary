// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_MinMaxImputerFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("min - int") {
    MinMaxImputerFeaturizer_int32_Test(
        std::vector<nonstd::optional<std::int32_t>>{
            10,
            20,
            30,
            nonstd::optional<std::int32_t>(),
            40,
            50,
            nonstd::optional<std::int32_t>()
        },
        std::vector<nonstd::optional<std::int32_t>>{
            1,
            2,
            nonstd::optional<std::int32_t>(),
            3,
            nonstd::optional<std::int32_t>(),
            nonstd::optional<std::int32_t>()
        },
        [](std::vector<std::int32_t> const &args) {
            return args == std::vector<std::int32_t>{
                1,
                2,
                10,
                3,
                10,
                10
            };
        },
        true
    );
}

TEST_CASE("min - float") {
    MinMaxImputerFeaturizer_float_Test(
        std::vector<float>{
            10.0f,
            20.0f,
            30.0f,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            40.0f,
            50.0f,
            std::numeric_limits<std::float_t>::quiet_NaN()
        },
        std::vector<float>{
            1.0f,
            2.0f,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            3.0f,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            std::numeric_limits<std::float_t>::quiet_NaN()
        },
        [](std::vector<float> const &args) {
            return args == std::vector<float>{
                1.0f,
                2.0f,
                10.0f,
                3.0f,
                10.0f,
                10.0f
            };
        },
        true
    );
}

TEST_CASE("min - string") {
    MinMaxImputerFeaturizer_string_Test(
        std::vector<nonstd::optional<std::string>>{
            "10",
            "20",
            "30",
            nonstd::optional<std::string>(),
            "40",
            "50",
            nonstd::optional<std::string>()
        },
        std::vector<nonstd::optional<std::string>>{
            "1",
            "2",
            nonstd::optional<std::string>(),
            "3",
            nonstd::optional<std::string>(),
            nonstd::optional<std::string>()
        },
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{
                "1",
                "2",
                "10",
                "3",
                "10",
                "10"
            };
        },
        true
    );
}

TEST_CASE("max - int") {
    MinMaxImputerFeaturizer_int32_Test(
        std::vector<nonstd::optional<std::int32_t>>{
            10,
            20,
            30,
            nonstd::optional<std::int32_t>(),
            40,
            50,
            nonstd::optional<std::int32_t>()
        },
        std::vector<nonstd::optional<std::int32_t>>{
            1,
            2,
            nonstd::optional<std::int32_t>(),
            3,
            nonstd::optional<std::int32_t>(),
            nonstd::optional<std::int32_t>()
        },
        [](std::vector<std::int32_t> const &args) {
            return args == std::vector<std::int32_t>{
                1,
                2,
                50,
                3,
                50,
                50
            };
        },
        false
    );
}

TEST_CASE("max - float") {
    MinMaxImputerFeaturizer_float_Test(
        std::vector<float>{
            10.0f,
            20.0f,
            30.0f,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            40.0f,
            50.0f,
            std::numeric_limits<std::float_t>::quiet_NaN()
        },
        std::vector<float>{
            1.0f,
            2.0f,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            3.0f,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            std::numeric_limits<std::float_t>::quiet_NaN()
        },
        [](std::vector<float> const &args) {
            return args == std::vector<float>{
                1.0f,
                2.0f,
                50.0f,
                3.0f,
                50.0f,
                50.0f
            };
        },
        false
    );
}

TEST_CASE("max - string") {
    MinMaxImputerFeaturizer_string_Test(
        std::vector<nonstd::optional<std::string>>{
            "10",
            "20",
            "30",
            nonstd::optional<std::string>(),
            "40",
            "50",
            nonstd::optional<std::string>()
        },
        std::vector<nonstd::optional<std::string>>{
            "1",
            "2",
            nonstd::optional<std::string>(),
            "3",
            nonstd::optional<std::string>(),
            nonstd::optional<std::string>()
        },
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{
                "1",
                "2",
                "50",
                "3",
                "50",
                "50"
            };
        },
        false
    );
}
