// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_ImputationMakerFeaturizer.h"

TEST_CASE("int8") {
    ImputationMakerFeaturizer_int8_t_Test(
        std::vector<nonstd::optional<std::int8_t>>(),
        std::vector<nonstd::optional<std::int8_t>>{
            static_cast<std::int8_t>(1),
            static_cast<std::int8_t>(2),
            nonstd::optional<std::int8_t>()
        },
        [](std::vector<bool> const &args) {
            return args == std::vector<bool>{false, false, true};
        }
    );
}

TEST_CASE("double") {
    std::double_t input_d = std::numeric_limits<std::double_t>::quiet_NaN();
    ImputationMakerFeaturizer_double_t_Test(
        std::vector<std::double_t>(),
        std::vector<std::double_t>{
            static_cast<std::double_t>(1.0),
            static_cast<std::double_t>(2.0),   
            input_d    
        },
        [](std::vector<bool> const &args) {
            return args == std::vector<bool>{false, false, true};
        }
    );
}

TEST_CASE("string") {
    using type = nonstd::optional<std::string>;
    ImputationMakerFeaturizer_string_Test(
        std::vector<nonstd::optional<std::string>>(),
        std::vector<nonstd::optional<std::string>>{
            "hello",
            "world",
            type{}
        },
        [](std::vector<bool> const &args) {
            return args == std::vector<bool>{false, false, true};
        }
    );
}

