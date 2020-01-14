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
            0,
            0,
            1,
            1
        },
        std::vector<std::int8_t>{
            2
        },
        [](std::vector<std::double_t> const &args) {
            return args[0] == 3.0;
        },
        true,
        true
    );
}

TEST_CASE("double_t_without_mean_with_std") {
    StandardScaleWrapperFeaturizer_double_Test(
        std::vector<std::double_t>{
            0.0,
            0.0,
            1.0,
            1.0
        },
        std::vector<std::double_t>{
            2.0
        },
        [](std::vector<std::double_t> const &args) {
            return args[0] == 4.0;
        },
        false,
        true
    );
}

TEST_CASE("double_t_with_mean_without_std") {
    StandardScaleWrapperFeaturizer_double_Test(
        std::vector<std::double_t>{
            0.0,
            0.0,
            1.0,
            1.0
        },
        std::vector<std::double_t>{
            2.0
        },
        [](std::vector<std::double_t> const &args) {
            return args[0] == 1.5;
        },
        true,
        false
    );
}

TEST_CASE("double_t_without_mean_without_std") {
    StandardScaleWrapperFeaturizer_double_Test(
        std::vector<std::double_t>{
            0.0,
            0.0,
            1.0,
            1.0
        },
        std::vector<std::double_t>{
            2.0
        },
        [](std::vector<std::double_t> const &args) {
            return args[0] == 2.0;
        },
        false,
        false
    );
}
