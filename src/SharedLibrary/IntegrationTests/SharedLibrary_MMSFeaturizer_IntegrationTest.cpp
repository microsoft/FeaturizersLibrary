// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_MinMaxScalarFeaturizer.h"

TEST_CASE("double_t") {
    MinMaxScalarFeaturizer_double_t_Test(
        std::vector<std::double_t>{
            static_cast<std::double_t>(-1),
            static_cast<std::double_t>(-0.5),
            static_cast<std::double_t>(0),
            static_cast<std::double_t>(1)
        },
        std::vector<std::double_t>{
            static_cast<std::double_t>(2)
        },
        [](std::vector<std::double_t> const &args) {
            return args == std::vector<std::double_t>{static_cast<std::double_t>(1.5)};
        }
    );
}
