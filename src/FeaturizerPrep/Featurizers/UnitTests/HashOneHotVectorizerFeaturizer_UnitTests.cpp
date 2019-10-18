// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../HashOneHotVectorizerFeaturizer.h"

namespace NS = Microsoft::Featurizer;

using HOHVStruct = NS::Featurizers::HashOneHotVectorizerStruct;


TEST_CASE("HashOneHotVectorizerEstimator") {
    CHECK(NS::Featurizers::HashOneHotVectorizerEstimator<std::int8_t>(NS::CreateTestAnnotationMapsPtr(1), 2, 100).Name == "HashOneHotVectorizerEstimator");
    CHECK(NS::Featurizers::HashOneHotVectorizerEstimator<std::int8_t>(NS::CreateTestAnnotationMapsPtr(1), 2, 100).is_training_complete());
    CHECK(dynamic_cast<NS::Featurizers::HashOneHotVectorizerTransformer<std::int8_t> *>(NS::Featurizers::HashOneHotVectorizerEstimator<std::int8_t>(NS::CreateTestAnnotationMapsPtr(1) , 2, 100).create_transformer().get()));
}

TEST_CASE("HashOneHotVectorizerTransformer_int8") {
    NS::Featurizers::HashOneHotVectorizerTransformer<std::int8_t> hvtransformer(2, 100);
    HOHVStruct out = hvtransformer.execute(15);
    HOHVStruct label = HOHVStruct{29, 100, true};
    CHECK(label == out);
}

TEST_CASE("HashOneHotVectorizerTransformer_int32") {
    NS::Featurizers::HashOneHotVectorizerTransformer<std::int32_t> hvtransformer(2, 100);
    HOHVStruct out = hvtransformer.execute(15);
    HOHVStruct label = HOHVStruct{22, 100, true};
    CHECK(label == out);
}

TEST_CASE("HashOneHotVectorizerTransformer_double") {
    NS::Featurizers::HashOneHotVectorizerTransformer<std::double_t> hvtransformer(2, 100);
    HOHVStruct out = hvtransformer.execute(15.0);
    HOHVStruct label = HOHVStruct{99, 100, true};
    CHECK(label == out);
}

TEST_CASE("HashOneHotVectorizerTransformer_string") {
    NS::Featurizers::HashOneHotVectorizerTransformer<std::string> hvtransformer(2, 100);
    HOHVStruct out = hvtransformer.execute("hello");
    HOHVStruct label = HOHVStruct{25, 100, true};
    CHECK(label == out);
}


