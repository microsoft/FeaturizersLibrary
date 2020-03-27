// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_BackwardFillImputerFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("Standard - string") {
    BackwardFillImputerFeaturizer_string_Test(
        std::vector<nonstd::optional<std::string>>(),
        std::vector<nonstd::optional<std::string>>{
            nonstd::optional<std::string>(),
            nonstd::optional<std::string>(),
            "2",
            nonstd::optional<std::string>(),
            "3"
        },
        [](std::vector<std::vector<std::string>> const &args) {
            CHECK(
                args == std::vector<std::vector<std::string>>{
                    {},
                    {},
                    {"2", "2", "2"},
                    {},
                    {"3", "3"},
                    {} // Nothing to flush
                }
            );
            return true;
        }
    );
}

TEST_CASE("Standard - int64") {
    BackwardFillImputerFeaturizer_int64_Test(
        std::vector<nonstd::optional<int64_t>>(),
        std::vector<nonstd::optional<int64_t>>{
            nonstd::optional<int64_t>(),
            nonstd::optional<int64_t>(),
            2,
            nonstd::optional<int64_t>(),
            3
        },
        [](std::vector<std::vector<int64_t>> const &args) {
            CHECK(
                args == std::vector<std::vector<int64_t>>{
                    {},
                    {},
                    {2, 2, 2},
                    {},
                    {3, 3},
                    {} // Nothing to flush
                }
            );
            return true;
        }
    );
}

TEST_CASE("Standard - double") {
    BackwardFillImputerFeaturizer_double_Test(
        std::vector<double>(),
        std::vector<double>{
            Microsoft::Featurizer::Traits<double>::CreateNullValue(),
            Microsoft::Featurizer::Traits<double>::CreateNullValue(),
            2.0,
            Microsoft::Featurizer::Traits<double>::CreateNullValue(),
            3.0
        },
        [](std::vector<std::vector<double>> const &args) {
            CHECK(
                args == std::vector<std::vector<double>>{
                    {},
                    {},
                    {2.0, 2.0, 2.0},
                    {},
                    {3.0, 3.0},
                    {} // Nothing to flush
                }
            );
            return true;
        }
    );
}
