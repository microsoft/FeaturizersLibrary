// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../InferenceOnlyFeaturizerImpl.h"

// ----------------------------------------------------------------------
using Microsoft::Featurizer::CreateTestAnnotationMapsPtr;

namespace NS = Microsoft::Featurizer;
// ----------------------------------------------------------------------

class MyTransformer : public Microsoft::Featurizer::Featurizers::Components::InferenceOnlyTransformerImpl<int, bool> {
public:
    MyTransformer(void) = default;
    ~MyTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MyTransformer);

private:
    void execute_impl(InputType const &input, CallbackFunction const &callback) override {
        callback(input & 1);
    }
};

class MyEstimator : public Microsoft::Featurizer::Featurizers::Components::InferenceOnlyEstimatorImpl<MyTransformer> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType                          = Microsoft::Featurizer::Featurizers::Components::InferenceOnlyEstimatorImpl<MyTransformer>;

    // ----------------------------------------------------------------------
    // |  Public Methods
    MyEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
        BaseType("MyEstimator", std::move(pAllColumnAnnotations)) {
    }

    ~MyEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MyEstimator);
};

TEST_CASE("MyEstimator") {
    MyEstimator                            featurizer(CreateTestAnnotationMapsPtr(2));

    CHECK(strcmp(featurizer.Name, "MyEstimator") == 0);

    CHECK(featurizer.get_state() == NS::TrainingState::Pending);
    featurizer.begin_training();
    CHECK(featurizer.get_state() == NS::TrainingState::Finished);
    featurizer.complete_training();
    CHECK(featurizer.get_state() == NS::TrainingState::Completed);

    CHECK(featurizer.has_created_transformer() == false);

    auto const                              pTransformer(featurizer.create_transformer());

    CHECK(featurizer.has_created_transformer());

    MyTransformer &                         transformer(static_cast<MyTransformer &>(*pTransformer));

    CHECK(transformer.execute(3));
    CHECK(transformer.execute(4) == false);
}
