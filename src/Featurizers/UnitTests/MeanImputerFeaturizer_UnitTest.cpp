// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../MeanImputerFeaturizer.h"
#include "../TestHelpers.h"

#include "../../3rdParty/optional.h"

namespace NS = Microsoft::Featurizer;

TEST_CASE("int") {
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MeanImputerEstimator<int>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<nonstd::optional<int>>{
                10,
                20,
                nonstd::optional<int>(),
                30,
                40,
                nonstd::optional<int>()
            },
            {
                nonstd::optional<int>(),
                1,
                2,
                3,
                nonstd::optional<int>()
            }
        ) == std::vector<double>{25.0, 1.0, 2.0, 3.0, 25.0}
    );
}

TEST_CASE("float") {
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MeanImputerEstimator<float>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<float>{
                10.0f,
                20.0f,
                NS::Traits<float>::CreateNullValue(),
                30.0f,
                40.0f,
                NS::Traits<float>::CreateNullValue()
            },
            {
                NS::Traits<float>::CreateNullValue(),
                1.0f,
                2.0f,
                3.0f,
                NS::Traits<float>::CreateNullValue()
            }
        ) == std::vector<double>{25.0, 1.0, 2.0, 3.0, 25.0}
    );
}

TEST_CASE("No items") {
    NS::Featurizers::MeanImputerEstimator<int>          estimator(NS::CreateTestAnnotationMapsPtr(1), 0);

    estimator.begin_training();
    CHECK_THROWS_WITH(estimator.complete_training(), "No values were provided");
}

TEST_CASE("No non-empty items") {
    CHECK_THROWS_WITH(
        (NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MeanImputerEstimator<float>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<float>{
                NS::Traits<float>::CreateNullValue(),
                NS::Traits<float>::CreateNullValue()
            },
            {
                1.0f
            }
        )),
        "No values were provided"
    );
}

TEST_CASE("Exceptions") {
    CHECK_THROWS_WITH(NS::Featurizers::MeanImputerEstimator<int>(NS::CreateTestAnnotationMapsPtr(1), 10), "colIndex");
}
