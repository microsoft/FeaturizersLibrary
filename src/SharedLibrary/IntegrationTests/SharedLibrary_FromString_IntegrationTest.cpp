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
        },
        false
    );
}

TEST_CASE("float") {
    FromStringFeaturizer_float_Test(
        std::vector<std::string>(),
        std::vector<std::string>{
            "1.0",
            "NaN",
            "2.0"
        },
        [](std::vector<float> const &args) {
            REQUIRE(args.size() == 3);
            CHECK(Approx(args[0]) == 1.0);
            CHECK(Microsoft::Featurizer::Traits<float>::IsNull(args[1]));
            CHECK(Approx(args[2]) == 2.0);
            return true;
        },
        false
    );
}

TEST_CASE("float - empty strings") {
    FromStringFeaturizer_float_Test(
        std::vector<std::string>(),
        std::vector<std::string>{
            "1.0",
            "NaN",
            "",
            "2.0"
        },
        [](std::vector<float> const &args) {
            REQUIRE(args.size() == 4);
            CHECK(Approx(args[0]) == 1.0);
            CHECK(Microsoft::Featurizer::Traits<float>::IsNull(args[1]));
            CHECK(Microsoft::Featurizer::Traits<float>::IsNull(args[2]));
            CHECK(Approx(args[3]) == 2.0);
            return true;
        },
        true
    );
}
