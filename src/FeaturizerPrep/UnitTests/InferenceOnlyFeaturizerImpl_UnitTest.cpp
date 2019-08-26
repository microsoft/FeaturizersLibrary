// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../InferenceOnlyFeaturizerImpl.h"

// ----------------------------------------------------------------------
using Microsoft::Featurizer::CreateTestAnnotationMapsPtr;
// ----------------------------------------------------------------------

class MyTransformer : public Microsoft::Featurizer::InferenceOnlyTransformerImpl<int, bool> {
public:
    MyTransformer(void) = default;
    MyTransformer(Microsoft::Featurizer::Archive &ar) :
        Microsoft::Featurizer::InferenceOnlyTransformerImpl<int, bool>(ar) {
    }

    ~MyTransformer(void) override = default;

    MyTransformer(MyTransformer const &) = delete;
    MyTransformer & operator =(MyTransformer const &) = delete;

    MyTransformer(MyTransformer &&) = default;
    MyTransformer & operator =(MyTransformer &&) = delete;

    TransformedType execute(InputType input) override {
        return input & 1;
    }
};

class MyEstimator : public Microsoft::Featurizer::InferenceOnlyEstimatorImpl<MyTransformer> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType                          = Microsoft::Featurizer::InferenceOnlyEstimatorImpl<MyTransformer>;

    // ----------------------------------------------------------------------
    // |  Public Methods
    MyEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
        BaseType("MyEstimator", std::move(pAllColumnAnnotations)) {
    }

    ~MyEstimator(void) override = default;

    MyEstimator(MyEstimator const &) = delete;
    MyEstimator & operator =(MyEstimator const &) = delete;

    MyEstimator(MyEstimator &&) = default;
    MyEstimator & operator =(MyEstimator &&) = delete;
};

TEST_CASE("MyEstimator") {
    MyEstimator                            featurizer(CreateTestAnnotationMapsPtr(2));

    CHECK(featurizer.Name == "MyEstimator");
    CHECK(featurizer.is_training_complete());
    CHECK(featurizer.has_created_transformer() == false);

    auto const                              pTransformer(featurizer.create_transformer());

    CHECK(featurizer.has_created_transformer());

    CHECK(pTransformer->execute(3));
    CHECK(pTransformer->execute(4) == false);
}
