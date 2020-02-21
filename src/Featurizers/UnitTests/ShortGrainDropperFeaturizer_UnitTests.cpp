// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../Featurizers/ShortGrainDropperFeaturizer.h"
#include "../TestHelpers.h"
#include "../../Archive.h"

namespace NS = Microsoft::Featurizer;

void Test(){
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<std::vector<std::string>>>(
        NS::TestHelpers::make_vector<std::vector<std::string>>(
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("c", "d")
        )
    );

    auto inferencingInput = NS::TestHelpers::make_vector<std::vector<std::string>>(
        NS::TestHelpers::make_vector<std::string>("a", "b"),
        NS::TestHelpers::make_vector<std::string>("c", "d"),
        NS::TestHelpers::make_vector<std::string>("e", "f")
    );

    auto inferencingOutput = NS::TestHelpers::make_vector<bool>(
        false,
        true,
        false
    );

    //parameter setting
    std::uint32_t windowSize = 0;
    std::vector<std::uint32_t> lags = NS::TestHelpers::make_vector<std::uint32_t>(0, 0);
    std::uint32_t maxHorizon = 1;
    nonstd::optional<std::uint32_t> cv = static_cast<std::uint32_t>(1);

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::ShortGrainDropperEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0, windowSize, lags, maxHorizon, cv),
            trainingBatches,
            inferencingInput
        ) == inferencingOutput
    );
}

TEST_CASE("test") {
    Test();
}
