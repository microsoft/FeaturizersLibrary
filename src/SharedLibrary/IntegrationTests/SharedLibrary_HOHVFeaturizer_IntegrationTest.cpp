// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_HashOneHotVectorizerFeaturizer.h"

TEST_CASE("int8") {
    HashOneHotVectorizerFeaturizer_int8_t_Test(
        std::vector<std::int8_t>(),
        std::vector<std::int8_t>{
            static_cast<std::int8_t>(15)
        },
        [](std::vector<HashOneHotVectorizerStruct> const &args) {
            HashOneHotVectorizerStruct obj(args[0]);
            return (obj.ColIndex == 29 && obj.NumCols == 100 && obj.Val == true);
        },
        static_cast<std::uint32_t>(2),
        static_cast<std::uint32_t>(100)
    );
}

TEST_CASE("string") {
    HashOneHotVectorizerFeaturizer_string_Test(
        std::vector<std::string>(),
        std::vector<std::string>{
            static_cast<std::string>("hello")
        },
        [](std::vector<HashOneHotVectorizerStruct> const &args) {
            HashOneHotVectorizerStruct obj(args[0]);
            return (obj.ColIndex == 25 && obj.NumCols == 100 && obj.Val == true);
        },
        static_cast<std::uint32_t>(2),
        static_cast<std::uint32_t>(100)
    );
}


