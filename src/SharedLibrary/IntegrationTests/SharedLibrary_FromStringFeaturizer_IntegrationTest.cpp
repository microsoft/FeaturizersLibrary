// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_FromStringFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("bool") {
    FromStringFeaturizer_bool_Test(
        std::vector<std::string>(),
        std::vector<std::string>{
            "True",
            "False",
            "not a bool"
        },
        [](std::vector<bool> const &args) {
            REQUIRE(args.size() == 3);
            CHECK(args[0] == true);
            CHECK(args[1] == false);
            CHECK(args[2] == false);
            return true;
        }
    );
}
