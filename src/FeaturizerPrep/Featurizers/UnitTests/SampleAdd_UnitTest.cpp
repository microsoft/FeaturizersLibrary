// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../SampleAdd.h"

// ----------------------------------------------------------------------
using Microsoft::Featurizer::SampleAddFeaturizer;
using Microsoft::Featurizer::CreateTestAnnotationMapsPtr;
// ----------------------------------------------------------------------

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif

SampleAddFeaturizer::TransformerPtr Train(std::vector<std::uint16_t> const &input) {
    SampleAddFeaturizer                     featurizer(CreateTestAnnotationMapsPtr(2));

    featurizer.fit(input.data(), input.size());
    featurizer.complete_training();

    return featurizer.create_transformer();
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
