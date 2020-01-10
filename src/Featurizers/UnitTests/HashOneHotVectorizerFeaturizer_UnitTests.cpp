// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../HashOneHotVectorizerFeaturizer.h"

namespace NS = Microsoft::Featurizer;
using Encoding = NS::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>;

TEST_CASE("HashOneHotVectorizerEstimator") {
    CHECK(strcmp(NS::Featurizers::HashOneHotVectorizerEstimator<std::int8_t>(NS::CreateTestAnnotationMapsPtr(1), 2, 100).Name, "HashOneHotVectorizerEstimator") == 0);

    NS::Featurizers::HashOneHotVectorizerEstimator<std::int8_t>      estimator(NS::CreateTestAnnotationMapsPtr(1), 2, 100);

    estimator.begin_training();
    estimator.complete_training();

    CHECK(dynamic_cast<NS::Featurizers::HashOneHotVectorizerTransformer<std::int8_t> *>(estimator.create_transformer().get()));
}

TEST_CASE("HashOneHotVectorizerTransformer_int8") {
    NS::Featurizers::HashOneHotVectorizerTransformer<std::int8_t> hvtransformer(2, 100);
    Encoding out = hvtransformer.execute(15);
    Encoding label(100, 1, 29);
    CHECK(label == out);
}

TEST_CASE("HashOneHotVectorizerTransformer_int32") {
    NS::Featurizers::HashOneHotVectorizerTransformer<std::int32_t> hvtransformer(2, 100);
    Encoding out = hvtransformer.execute(15);
    Encoding label(100, 1, 22);
    CHECK(label == out);
}

TEST_CASE("HashOneHotVectorizerTransformer_double") {
    NS::Featurizers::HashOneHotVectorizerTransformer<std::double_t> hvtransformer(2, 100);
    Encoding out = hvtransformer.execute(15.0);
    Encoding label(100, 1, 99);
    CHECK(label == out);
}

TEST_CASE("HashOneHotVectorizerTransformer_string") {
    NS::Featurizers::HashOneHotVectorizerTransformer<std::string> hvtransformer(2, 100);
    Encoding out = hvtransformer.execute("hello");
    Encoding label(100, 1, 25);
    CHECK(label == out);
}

TEST_CASE("Serialization") {
    NS::Featurizers::HashOneHotVectorizerTransformer<std::string>           original(2, 100);
    NS::Archive                                                             out;

    original.save(out);

    NS::Archive                             in(out.commit());

    NS::Featurizers::HashOneHotVectorizerTransformer<std::string>           other(in);

    CHECK(other == original);
}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        NS::Featurizers::HashOneHotVectorizerTransformer<std::string>(in),
        Catch::Contains("Unsupported archive version")
    );
}
