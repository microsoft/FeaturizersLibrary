// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_HashOneHotVectorizerFeaturizer.h"

TEST_CASE("int8") {
    HashOneHotVectorizerFeaturizer_int8_Test(
        std::vector<std::int8_t>(),
        std::vector<std::int8_t>{
            static_cast<std::int8_t>(15)
        },
        [](std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &args) {
            REQUIRE(args.size() == 1);

            Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t> const & obj(args[0]);
            return (obj.Index == 29 && obj.NumElements == 100 && obj.Value == 1);
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
        [](std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &args) {
            REQUIRE(args.size() == 1);

            Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t> const & obj(args[0]);
            return (obj.Index == 25 && obj.NumElements == 100 && obj.Value == 1);
        },
        static_cast<std::uint32_t>(2),
        static_cast<std::uint32_t>(100)
    );
}
