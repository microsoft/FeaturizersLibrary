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

class MyFeaturizer : public Microsoft::Featurizer::InferenceOnlyFeaturizerImpl<MyTransformer> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType                          = Microsoft::Featurizer::InferenceOnlyFeaturizerImpl<MyTransformer>;

    // ----------------------------------------------------------------------
    // |  Public Methods
    MyFeaturizer(AnnotationMapsPtr pAllColumnAnnotations) :
        BaseType("MyFeaturizer", std::move(pAllColumnAnnotations)) {
    }

    ~MyFeaturizer(void) override = default;

    MyFeaturizer(MyFeaturizer const &) = delete;
    MyFeaturizer & operator =(MyFeaturizer const &) = delete;

    MyFeaturizer(MyFeaturizer &&) = default;
    MyFeaturizer & operator =(MyFeaturizer &&) = delete;
};

TEST_CASE("MyFeaturizer") {
    MyFeaturizer                            featurizer(CreateTestAnnotationMapsPtr(2));

    CHECK(featurizer.Name == "MyFeaturizer");
    CHECK(featurizer.is_training_complete());
    CHECK(featurizer.has_created_transformer() == false);

    auto const                              pTransformer(featurizer.create_transformer());

    CHECK(featurizer.has_created_transformer());

    CHECK(pTransformer->execute(3));
    CHECK(pTransformer->execute(4) == false);
}
