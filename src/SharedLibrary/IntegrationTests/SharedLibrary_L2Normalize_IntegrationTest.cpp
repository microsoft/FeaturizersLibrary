// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_L2NormalizeFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("int") {
    // ----------------------------------------------------------------------
    using Ints                              = std::vector<int>;
    // ----------------------------------------------------------------------

    Ints const                              input{4, 1, 2, 2};

    L2NormalizeFeaturizer_int32_Test(
        std::vector<Ints>{input},
        std::vector<Ints>{input},
        [](std::vector<std::vector<double>> const &args) {
            REQUIRE(args.size() == 1);
            CHECK(args[0] == std::vector<double>{0.8, 0.2, 0.4, 0.4});
            return true;
        }
    );
}
