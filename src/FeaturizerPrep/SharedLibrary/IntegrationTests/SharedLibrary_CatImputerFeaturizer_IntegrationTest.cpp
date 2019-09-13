// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_CatImputerFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("int8") {
    CatImputerFeaturizer_int8_t_Test(
        std::vector<nonstd::optional<std::int8_t>>{
            static_cast<std::int8_t>(1),
            static_cast<std::int8_t>(2),
            nonstd::optional<std::int8_t>(),
            static_cast<std::int8_t>(3),
            nonstd::optional<std::int8_t>(),
            static_cast<std::int8_t>(4),
            static_cast<std::int8_t>(5),
            static_cast<std::int8_t>(5),
            static_cast<std::int8_t>(6),
            static_cast<std::int8_t>(7),
            nonstd::optional<std::int8_t>()
        },
        std::vector<nonstd::optional<std::int8_t>>{
            static_cast<std::int8_t>(1),
            static_cast<std::int8_t>(2),
            static_cast<std::int8_t>(3),
            static_cast<std::int8_t>(4),
            static_cast<std::int8_t>(5),
            static_cast<std::int8_t>(6),
            static_cast<std::int8_t>(7),
            nonstd::optional<std::int8_t>()
        },
        [](std::vector<std::int8_t> const &args) {
            return args == std::vector<std::int8_t>{1, 2, 3, 4, 5, 6, 7, 5};
        }
    );
}
