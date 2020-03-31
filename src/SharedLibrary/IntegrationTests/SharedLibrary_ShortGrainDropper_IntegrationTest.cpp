// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_ShortGrainDropperFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("Standard") {
    std::vector<std::vector<std::string>> const         training{
        std::vector<std::string>{ "a", "b" },
        std::vector<std::string>{ "a", "b" },
        std::vector<std::string>{ "a", "b" },
        std::vector<std::string>{ "a", "b" },
        std::vector<std::string>{ "a", "b" },

        std::vector<std::string>{ "a", "c" },
        std::vector<std::string>{ "a", "c" },
        std::vector<std::string>{ "a", "c" },
        std::vector<std::string>{ "a", "c" },

        std::vector<std::string>{ "a", "d" },
        std::vector<std::string>{ "a", "d" },
        std::vector<std::string>{ "a", "d" },

        std::vector<std::string>{ "a", "e" },
        std::vector<std::string>{ "a", "e" },

        std::vector<std::string>{ "a", "f" }
    };

    std::vector<std::vector<std::string>> const         inference{
        std::vector<std::string>{ "a", "b" },
        std::vector<std::string>{ "a", "c" },
        std::vector<std::string>{ "a", "d" },
        std::vector<std::string>{ "a", "e" },
        std::vector<std::string>{ "a", "f" },
        std::vector<std::string>{ "a", "g" }
    };

    SECTION("MinPoints = 5") {
        ShortGrainDropperFeaturizer_Test(
            training,
            inference,
            [](std::vector<bool> const &args) {
                CHECK(
                    args == std::vector<bool>{
                        false,
                        true,
                        true,
                        true,
                        true,
                        true
                    }
                );
                return true;
            },
            5UL
        );
    }

    SECTION("MinPoints = 3") {
        ShortGrainDropperFeaturizer_Test(
            training,
            inference,
            [](std::vector<bool> const &args) {
                CHECK(
                    args == std::vector<bool>{
                        false,
                        false,
                        false,
                        true,
                        true,
                        true
                    }
                );
                return true;
            },
            3UL
        );
    }
}
