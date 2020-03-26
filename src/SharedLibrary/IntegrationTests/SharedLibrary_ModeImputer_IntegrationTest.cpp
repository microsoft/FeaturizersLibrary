// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_ModeImputerFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("int8") {
    ModeImputerFeaturizer_int8_Test(
        std::vector<nonstd::optional<std::int8_t>>{
            nonstd::optional<std::int8_t>(),
            static_cast<std::int8_t>(10),
            static_cast<std::int8_t>(30),
            static_cast<std::int8_t>(20),
            nonstd::optional<std::int8_t>(),
            static_cast<std::int8_t>(20),
            static_cast<std::int8_t>(40),
            nonstd::optional<std::int8_t>(),
            static_cast<std::int8_t>(30),
            nonstd::optional<std::int8_t>(),
            nonstd::optional<std::int8_t>()
        },
        std::vector<nonstd::optional<std::int8_t>>{
            nonstd::optional<std::int8_t>(),
            static_cast<std::int8_t>(1),
            static_cast<std::int8_t>(2),
            nonstd::optional<std::int8_t>(),
            nonstd::optional<std::int8_t>(),
            static_cast<std::int8_t>(3),
            nonstd::optional<std::int8_t>()
        },
        [](std::vector<std::int8_t> const &args) {
            return args == std::vector<std::int8_t>{
                static_cast<std::int8_t>(30),
                static_cast<std::int8_t>(1),
                static_cast<std::int8_t>(2),
                static_cast<std::int8_t>(30),
                static_cast<std::int8_t>(30),
                static_cast<std::int8_t>(3),
                static_cast<std::int8_t>(30)
            };
        }
    );
}

TEST_CASE("float") {
    ModeImputerFeaturizer_float_Test(
        std::vector<float>{
            std::numeric_limits<std::float_t>::quiet_NaN(),
            10.0f,
            30.0f,
            20.0f,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            20.0f,
            40.0f,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            30.0f,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            std::numeric_limits<std::float_t>::quiet_NaN()
        },
        std::vector<std::float_t>{
            std::numeric_limits<std::float_t>::quiet_NaN(),
            1.0f,
            2.0f,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            std::numeric_limits<std::float_t>::quiet_NaN(),
            3,
            std::numeric_limits<std::float_t>::quiet_NaN()
        },
        [](std::vector<std::float_t> const &args) {
            return args == std::vector<std::float_t>{
                30.0f,
                1.0f,
                2.0f,
                30.0f,
                30.0f,
                3.0f,
                30.0f
            };
        }
    );
}

TEST_CASE("string") {
    ModeImputerFeaturizer_string_Test(
        std::vector<nonstd::optional<std::string>>{
            nonstd::optional<std::string>(),
            "10.0",
            "30.0",
            "20.0",
            nonstd::optional<std::string>(),
            "20.0",
            "40.0",
            nonstd::optional<std::string>(),
            "30.0",
            nonstd::optional<std::string>(),
            nonstd::optional<std::string>()
        },
        std::vector<nonstd::optional<std::string>>{
            nonstd::optional<std::string>(),
            "1.0",
            "2.0",
            nonstd::optional<std::string>(),
            nonstd::optional<std::string>(),
            "3.0",
            nonstd::optional<std::string>()
        },
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{
                "30.0",
                "1.0",
                "2.0",
                "30.0",
                "30.0",
                "3.0",
                "30.0"
            };
        }
    );
}
