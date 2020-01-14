// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_StandardScaleWrapperFeaturizer.h"

TEST_CASE("int8_t_with_mean_with_std") {
    StandardScaleWrapperFeaturizer_int8_Test(
        std::vector<std::int8_t>{
            static_cast<std::int8_t>(0),
            static_cast<std::int8_t>(0),
            static_cast<std::int8_t>(1),
            static_cast<std::int8_t>(1)
        },
        std::vector<std::int8_t>{
            static_cast<std::int8_t>(2)
        },
        [](std::vector<std::double_t> const &args) {
            return args == std::vector<std::double_t>{static_cast<std::double_t>(3)};
        },
        bool(true),
        bool(true)
    );
}

TEST_CASE("double_t_without_mean_with_std") {
    StandardScaleWrapperFeaturizer_double_Test(
        std::vector<std::double_t>{
            static_cast<std::double_t>(0),
            static_cast<std::double_t>(0),
            static_cast<std::double_t>(1),
            static_cast<std::double_t>(1)
        },
        std::vector<std::double_t>{
            static_cast<std::double_t>(2)
        },
        [](std::vector<std::double_t> const &args) {
            return args == std::vector<std::double_t>{static_cast<std::double_t>(4)};
        },
        bool(false),
        bool(true)
    );
}

TEST_CASE("double_t_with_mean_without_std") {
    StandardScaleWrapperFeaturizer_double_Test(
        std::vector<std::double_t>{
            static_cast<std::double_t>(0),
            static_cast<std::double_t>(0),
            static_cast<std::double_t>(1),
            static_cast<std::double_t>(1)
        },
        std::vector<std::double_t>{
            static_cast<std::double_t>(2)
        },
        [](std::vector<std::double_t> const &args) {
            return args == std::vector<std::double_t>{static_cast<std::double_t>(1.5)};
        },
        bool(true),
        bool(false)
    );
}

TEST_CASE("double_t_without_mean_without_std") {
    StandardScaleWrapperFeaturizer_double_Test(
        std::vector<std::double_t>{
            static_cast<std::double_t>(0),
            static_cast<std::double_t>(0),
            static_cast<std::double_t>(1),
            static_cast<std::double_t>(1)
        },
        std::vector<std::double_t>{
            static_cast<std::double_t>(2)
        },
        [](std::vector<std::double_t> const &args) {
            return args == std::vector<std::double_t>{static_cast<std::double_t>(2)};
        },
        bool(false),
        bool(false)
    );
}
