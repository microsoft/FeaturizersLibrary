// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../SampleAddFeaturizer.h"

// ----------------------------------------------------------------------
using Microsoft::Featurizer::SampleAddEstimator;
using Microsoft::Featurizer::CreateTestAnnotationMapsPtr;
// ----------------------------------------------------------------------

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif

SampleAddEstimator::TransformerPtr Train(std::vector<std::uint16_t> const &input) {
    SampleAddEstimator                      estimator(CreateTestAnnotationMapsPtr(2));

    estimator.fit(input.data(), input.size());
    estimator.complete_training();

    return estimator.create_transformer();
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

TEST_CASE("SampleAddFeaturizer") {
    CHECK(Train({10})->execute(20) == 30);
    CHECK(Train({20})->execute(1) == 21);

    CHECK(Train({10, 20})->execute(20) == 50);
    CHECK(Train({10, 20, 30})->execute(20) == 80);
}
