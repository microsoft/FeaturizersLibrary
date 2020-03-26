// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_MaxNormalizeFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("double") {
    // ----------------------------------------------------------------------
    using Doubles                           = std::vector<double>;
    // ----------------------------------------------------------------------

    Doubles const                           input{7.9, 4.37,  6,  10};

    MaxNormalizeFeaturizer_double_Test(
        std::vector<Doubles>{input},
        std::vector<Doubles>{input},
        [](std::vector<std::vector<double>> const &args) {
            REQUIRE(args.size() == 1);
            CHECK(args[0] == std::vector<double>{0.79, 0.437,  0.6, 1.0});
            return true;
        }
    );
}
