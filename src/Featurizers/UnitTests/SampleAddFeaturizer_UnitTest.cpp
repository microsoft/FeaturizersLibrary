// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../SampleAddFeaturizer.h"

// ----------------------------------------------------------------------
using Microsoft::Featurizer::Featurizers::SampleAddEstimator;
using Microsoft::Featurizer::CreateTestAnnotationMapsPtr;
// ----------------------------------------------------------------------

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif

SampleAddEstimator::TransformerUniquePtr Train(std::vector<std::uint16_t> const &input) {
    SampleAddEstimator                      estimator(CreateTestAnnotationMapsPtr(2));

    estimator.begin_training();
    estimator.fit(input.data(), input.size());
    estimator.complete_training();

    return estimator.create_transformer();
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

TEST_CASE("SampleAddFeaturizer") {
    // ----------------------------------------------------------------------
    using StandardTransformer               = Microsoft::Featurizer::StandardTransformer<std::uint16_t, std::uint32_t>;
    // ----------------------------------------------------------------------

    CHECK(static_cast<StandardTransformer *>(Train({10}).get())->execute(20) == 30);
    CHECK(static_cast<StandardTransformer *>(Train({20}).get())->execute(1) == 21);

    CHECK(static_cast<StandardTransformer *>(Train({10, 20}).get())->execute(20) == 50);
    CHECK(static_cast<StandardTransformer *>(Train({10, 20, 30}).get())->execute(20) == 80);
}
