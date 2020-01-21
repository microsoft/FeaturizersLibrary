// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../ModeImputerFeaturizer.h"
#include "../TestHelpers.h"

#include "../../3rdParty/optional.h"

namespace NS = Microsoft::Featurizer;

TEST_CASE("int") {
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::ModeImputerEstimator<int>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<nonstd::optional<int>>{
                10,
                20,
                nonstd::optional<int>(),
                30,
                nonstd::optional<int>(),
                20,
                nonstd::optional<int>(),
                40
            },
            {
                nonstd::optional<int>(),
                1,
                2,
                3,
                nonstd::optional<int>()
            }
        ) == std::vector<int>{20, 1, 2, 3, 20}
    );
}

TEST_CASE("float") {
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::ModeImputerEstimator<float>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<float>{
                10.0f,
                20.0f,
                NS::Traits<float>::CreateNullValue(),
                30.0f,
                NS::Traits<float>::CreateNullValue(),
                20.0f,
                NS::Traits<float>::CreateNullValue(),
                40.0f
            },
            {
                NS::Traits<float>::CreateNullValue(),
                1.0f,
                2.0f,
                3.0f,
                NS::Traits<float>::CreateNullValue()
            }
        ) == std::vector<float>{20.0f, 1.0f, 2.0f, 3.0f, 20.0f}
    );
}

TEST_CASE("string") {
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::ModeImputerEstimator<std::string>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<nonstd::optional<std::string>>{
                "10",
                "20",
                nonstd::optional<std::string>(),
                "30",
                nonstd::optional<std::string>(),
                "20",
                nonstd::optional<std::string>(),
                "40"
            },
            {
                nonstd::optional<std::string>(),
                "1",
                "2",
                "3",
                nonstd::optional<std::string>()
            }
        ) == std::vector<std::string>{"20", "1", "2", "3", "20"}
    );
}

TEST_CASE("int - duplicate modes") {
    // When there are multiple values found with the same number of occurrences,
    // we should default to using the first encountered.
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::ModeImputerEstimator<int>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<nonstd::optional<int>>{
                10,
                20,
                nonstd::optional<int>(),
                30,
                nonstd::optional<int>(),
                20,
                30,
                nonstd::optional<int>(),
                40,
                40
            },
            {
                nonstd::optional<int>(),
                1,
                2,
                3,
                nonstd::optional<int>()
            }
        ) == std::vector<int>{20, 1, 2, 3, 20}
    );
}

TEST_CASE("No items") {
    NS::Featurizers::ModeImputerEstimator<int>          estimator(NS::CreateTestAnnotationMapsPtr(1), 0);

    estimator.begin_training();
    CHECK_THROWS_WITH(estimator.complete_training(), "value");
}

TEST_CASE("All nullable items") {
    CHECK_THROWS_WITH(
        ((NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::ModeImputerEstimator<int>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<nonstd::optional<int>>{
                nonstd::optional<int>(),
                nonstd::optional<int>()
            },
            {
                1
            }
        ))),
        "The histogram does not contain any supported values"
    );
}

TEST_CASE("Exceptions") {
    CHECK_THROWS_WITH(NS::Featurizers::ModeImputerEstimator<int>(NS::CreateTestAnnotationMapsPtr(1), 10), "colIndex");
}
