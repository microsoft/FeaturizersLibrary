// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_CountVectorizerFeaturizer.h"

TEST_CASE("Standard") {
    std::uint32_t topK(3);
    CountVectorizerFeaturizer_Test(
        std::vector<std::string>{"oraNge apple oranGE grape", "grApe caRrOt carrot apple", "peach Banana orange banana"},
        std::vector<std::string>{"banana grape grape apple apple apple orange"},
        [](std::vector<Microsoft::Featurizer::Featurizers::SparseVectorEncoding<std::uint32_t>> const &args) {
            REQUIRE(args.size() == 1);

            Microsoft::Featurizer::Featurizers::SparseVectorEncoding<std::uint32_t> const & obj(args[0]);
            return (obj.NumElements == 3 && obj.Values[0].Value == 3 && obj.Values[0].Index == 0
                                         && obj.Values[1].Value == 2 && obj.Values[1].Index == 1
                                         && obj.Values[2].Value == 1 && obj.Values[2].Index == 2);
        },
        true,
        static_cast<std::uint8_t>(CountVectorizerFeaturizer_AnalyzerMethod_Word),
        "",
        1.0f,
        0.0f,
        &topK,
        static_cast<std::uint32_t>(1),
        static_cast<std::uint32_t>(1),
        false
    );
}
