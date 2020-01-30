// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_TfidfVectorizerFeaturizer.h"

TEST_CASE("standard") {
    std::uint32_t topKTerms = 3;
    TfidfVectorizerFeaturizer_Test(
        std::vector<std::string>{"jumpy fox"},
        std::vector<std::string>{"jumpy fox"},
        [](std::vector<Microsoft::Featurizer::Featurizers::SparseVectorEncoding<std::float_t>> const &args) {
            REQUIRE(args.size() == 1);
            Microsoft::Featurizer::Featurizers::SparseVectorEncoding<std::float_t> const & obj(args[0]);

            REQUIRE(obj.NumElements == 3);

            CHECK(Approx(obj.Values[0].Value) == 0.57735f);
            CHECK(obj.Values[0].Index == 0);

            CHECK(Approx(obj.Values[1].Value) == 0.57735f);
            CHECK(obj.Values[1].Index == 1);

            CHECK(Approx(obj.Values[2].Value) == 0.57735f);
            CHECK(obj.Values[2].Index == 2);

            return true;
        },
        true,
        static_cast<std::uint8_t>(TfidfVectorizerFeaturizer_AnalyzerMethod_Word),
        "",
        static_cast<std::uint8_t>(TfidfVectorizerFeaturizer_NormMethod_L2),
        static_cast<std::uint32_t>(TfidfVectorizerFeaturizer_TfidfPolicy_UseIdf | TfidfVectorizerFeaturizer_TfidfPolicy_SmoothIdf),
        0.0f,
        1.0f,
        &topKTerms,
        static_cast<std::uint32_t>(1),
        static_cast<std::uint32_t>(2)
    );
}

