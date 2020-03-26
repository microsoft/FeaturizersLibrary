// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_MeanImputerFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("int8") {
    MeanImputerFeaturizer_int8_Test(
        std::vector<nonstd::optional<std::int8_t>>{
            static_cast<std::int8_t>(10),
            static_cast<std::int8_t>(20),
            static_cast<std::int8_t>(30),
            nonstd::optional<std::int8_t>(),
            static_cast<std::int8_t>(40),
            static_cast<std::int8_t>(50),
            nonstd::optional<std::int8_t>(),
            nonstd::optional<std::int8_t>()
        },
        std::vector<nonstd::optional<std::int8_t>>{
            static_cast<std::int8_t>(1),
            static_cast<std::int8_t>(2),
            nonstd::optional<std::int8_t>(),
            static_cast<std::int8_t>(3),
            nonstd::optional<std::int8_t>(),
            nonstd::optional<std::int8_t>()
        },
        [](std::vector<double> const &args) {
            return args == std::vector<double>{
                1.0,
                2.0,
                30.0,
                3.0,
                30.0,
                30.0
            };
        }
    );
}

TEST_CASE("float") {
    MeanImputerFeaturizer_float_Test(
        std::vector<float>{
            10.0f,
            20.0f,
            30.0f,
            std::numeric_limits<std::float_t>::quiet_NaN(),
            40.0f,
            50.0f,
            std::numeric_limits<std::float_t>::quiet_NaN(),
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
        [](std::vector<double> const &args) {
            return args == std::vector<double>{
                1.0,
                2.0,
                30.0,
                3.0,
                30.0,
                30.0
            };
        }
    );
}

TEST_CASE("double") {
    MeanImputerFeaturizer_double_Test(
        std::vector<double>{
            10.0,
            20.0,
            30.0,
            std::numeric_limits<std::double_t>::quiet_NaN(),
            40.0,
            50.0,
            std::numeric_limits<std::double_t>::quiet_NaN(),
            std::numeric_limits<std::double_t>::quiet_NaN()
        },
        std::vector<double>{
            1.0,
            2.0,
            std::numeric_limits<std::double_t>::quiet_NaN(),
            3.0,
            std::numeric_limits<std::double_t>::quiet_NaN(),
            std::numeric_limits<std::double_t>::quiet_NaN()
        },
        [](std::vector<double> const &args) {
            return args == std::vector<double>{
                1.0,
                2.0,
                30.0,
                3.0,
                30.0,
                30.0
            };
        }
    );
}
