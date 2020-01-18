// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../MedianImputerFeaturizer.h"
#include "../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

TEST_CASE("int") {
    // Odd number of items (no interpolation required)
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MedianImputerEstimator<nonstd::optional<int>, float>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<nonstd::optional<int>>{
                10,
                20,
                nonstd::optional<int>(),
                30,
                nonstd::optional<int>()
            },
            {
                nonstd::optional<int>(),
                1,
                2,
                3,
                nonstd::optional<int>()
            }
        ) == std::vector<float>{20.0f, 1.0f, 2.0f, 3.0f, 20.0f}
    );

    // Even number of items (interpolated)
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MedianImputerEstimator<nonstd::optional<int>, float>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<nonstd::optional<int>>{
                10,
                40,
                20,
                nonstd::optional<int>(),
                30,
                nonstd::optional<int>()
            },
            {
                nonstd::optional<int>(),
                1,
                2,
                3,
                nonstd::optional<int>()
            }
        ) == std::vector<float>{25.0f, 1.0f, 2.0f, 3.0f, 25.0f}
    );

    // Even number of items (interpolation disabled)
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MedianImputerEstimator<nonstd::optional<int>, float, false>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<nonstd::optional<int>>{
                10,
                40,
                20,
                nonstd::optional<int>(),
                30,
                nonstd::optional<int>()
            },
            {
                nonstd::optional<int>(),
                1,
                2,
                3,
                nonstd::optional<int>()
            }
        ) == std::vector<float>{20.0f, 1.0f, 2.0f, 3.0f, 20.0f}
    );
}

TEST_CASE("float") {
    // Odd number of items (no interpolation required)
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MedianImputerEstimator<float, float>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<float>{
                10.0f,
                20.0f,
                NS::Traits<float>::CreateNullValue(),
                30.0f,
                NS::Traits<float>::CreateNullValue()
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

    // Even number of items (interpolated)
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MedianImputerEstimator<float, float>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<float>{
                40.0f,
                10.0f,
                20.0f,
                NS::Traits<float>::CreateNullValue(),
                30.0f,
                NS::Traits<float>::CreateNullValue()
            },
            {
                NS::Traits<float>::CreateNullValue(),
                1.0f,
                2.0f,
                3.0f,
                NS::Traits<float>::CreateNullValue()
            }
        ) == std::vector<float>{25.0f, 1.0f, 2.0f, 3.0f, 25.0f}
    );

    // Even number of items (interpolation disabled)
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MedianImputerEstimator<float, float, false>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<float>{
                40.0f,
                10.0f,
                20.0f,
                NS::Traits<float>::CreateNullValue(),
                30.0f,
                NS::Traits<float>::CreateNullValue()
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
    // Odd number of items
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MedianImputerEstimator<nonstd::optional<std::string>, std::string, false>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<nonstd::optional<std::string>>{
                "10",
                "20",
                nonstd::optional<std::string>(),
                "30",
                nonstd::optional<std::string>()
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

    // Even number of items (no interpolation)
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MedianImputerEstimator<nonstd::optional<std::string>, std::string, false>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<nonstd::optional<std::string>>{
                "10",
                "20",
                nonstd::optional<std::string>(),
                "30",
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

TEST_CASE("Null inputs - int") {
    CHECK_THROWS_WITH(
        (NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MedianImputerEstimator<nonstd::optional<int>, int, false>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<nonstd::optional<int>>{
                nonstd::optional<int>(),
                nonstd::optional<int>()
            },
            {
                nonstd::optional<int>(),
                1,
                2,
                3,
                nonstd::optional<int>()
            }
        )),
        "No elements were provided during training"
    );
}

TEST_CASE("Null inputs - float") {
    CHECK_THROWS_WITH(
        (NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MedianImputerEstimator<float, float>(NS::CreateTestAnnotationMapsPtr(1), 0),
            std::vector<float>{
                NS::Traits<float>::CreateNullValue(),
                NS::Traits<float>::CreateNullValue()
            },
            {
                NS::Traits<float>::CreateNullValue(),
                1,
                2,
                3,
                NS::Traits<float>::CreateNullValue()
            }
        )),
        "No elements were provided during training"
    );
}

TEST_CASE("No inputs - int") {
    NS::Featurizers::MedianImputerEstimator<nonstd::optional<int>, int>     estimator(NS::CreateTestAnnotationMapsPtr(1), 0);

    estimator.begin_training();
    CHECK_THROWS_WITH(estimator.complete_training(), "No elements were provided during training");
}

TEST_CASE("No inputs - nullable type") {
    NS::Featurizers::MedianImputerEstimator<float, float>                   estimator(NS::CreateTestAnnotationMapsPtr(1), 0);

    estimator.begin_training();
    CHECK_THROWS_WITH(estimator.complete_training(), "No elements were provided during training");
}

TEST_CASE("Exceptions") {
    CHECK_THROWS_WITH(
        (NS::Featurizers::MedianImputerEstimator<float, float>(NS::CreateTestAnnotationMapsPtr(1), 10)),
        "colIndex"
    );
}
