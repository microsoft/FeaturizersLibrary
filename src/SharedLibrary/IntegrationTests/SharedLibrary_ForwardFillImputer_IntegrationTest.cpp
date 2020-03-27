// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_ForwardFillImputerFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("Standard - string") {
    ForwardFillImputerFeaturizer_string_Test(
        std::vector<nonstd::optional<std::string>>(),
        std::vector<nonstd::optional<std::string>>{
            "1",
            nonstd::optional<std::string>(),
            "2",
            "3",
            nonstd::optional<std::string>(),
            nonstd::optional<std::string>(),
            "4",
        },
        [](std::vector<std::string> const &args) {
            CHECK(
                args == std::vector<std::string>{
                    "1",
                    "1",
                    "2",
                    "3",
                    "3",
                    "3",
                    "4"
                }
            );
            return true;
        }
    );
}

TEST_CASE("Standard - int") {
    ForwardFillImputerFeaturizer_int64_Test(
        std::vector<nonstd::optional<int64_t>>(),
        std::vector<nonstd::optional<int64_t>>{
            1,
            nonstd::optional<int64_t>(),
            2,
            3,
            nonstd::optional<int64_t>(),
            nonstd::optional<int64_t>(),
            4,
        },
        [](std::vector<int64_t> const &args) {
            CHECK(
                args == std::vector<int64_t>{
                    1,
                    1,
                    2,
                    3,
                    3,
                    3,
                    4
                }
            );
            return true;
        }
    );
}

TEST_CASE("Standard - double") {
    ForwardFillImputerFeaturizer_double_Test(
        std::vector<double>(),
        std::vector<double>{
            1.0,
            Microsoft::Featurizer::Traits<double>::CreateNullValue(),
            2.0,
            3.0,
            Microsoft::Featurizer::Traits<double>::CreateNullValue(),
            Microsoft::Featurizer::Traits<double>::CreateNullValue(),
            4.0,
        },
        [](std::vector<double> const &args) {
            CHECK(
                args == std::vector<double>{
                    1.0,
                    1.0,
                    2.0,
                    3.0,
                    3.0,
                    3.0,
                    4.0
                }
            );
            return true;
        }
    );
}
