// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../MinMaxImputerFeaturizer.h"
#include "../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

TEST_CASE("Min - int") {
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MinMaxImputerEstimator<int>(NS::CreateTestAnnotationMapsPtr(1), 0, true),
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
        ) == std::vector<int>{10, 1, 2, 3, 10}
    );
}

TEST_CASE("Min - float") {
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MinMaxImputerEstimator<float>(NS::CreateTestAnnotationMapsPtr(1), 0, true),
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
        ) == std::vector<float>{10.0f, 1.0f, 2.0f, 3.0f, 10.0f}
    );
}

TEST_CASE("Min - string") {
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MinMaxImputerEstimator<std::string>(NS::CreateTestAnnotationMapsPtr(1), 0, true),
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
        ) == std::vector<std::string>{"10", "1", "2", "3", "10"}
    );
}

TEST_CASE("Max - int") {
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MinMaxImputerEstimator<int>(NS::CreateTestAnnotationMapsPtr(1), 0, false),
            std::vector<nonstd::optional<int>>{
                -10,
                -20,
                nonstd::optional<int>(),
                -30,
                nonstd::optional<int>()
            },
            {
                nonstd::optional<int>(),
                -1,
                -2,
                -3,
                nonstd::optional<int>()
            }
        ) == std::vector<int>{-10, -1, -2, -3, -10}
    );
}

TEST_CASE("Max - float") {
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MinMaxImputerEstimator<float>(NS::CreateTestAnnotationMapsPtr(1), 0, false),
            std::vector<float>{
                -10.0f,
                -20.0f,
                NS::Traits<float>::CreateNullValue(),
                -30.0f,
                NS::Traits<float>::CreateNullValue()
            },
            {
                NS::Traits<float>::CreateNullValue(),
                -1.0f,
                -2.0f,
                -3.0f,
                NS::Traits<float>::CreateNullValue()
            }
        ) == std::vector<float>{-10.0f, -1.0f, -2.0f, -3.0f, -10.0f}
    );
}

TEST_CASE("Max - string") {
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MinMaxImputerEstimator<std::string>(NS::CreateTestAnnotationMapsPtr(1), 0, false),
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
        ) == std::vector<std::string>{"30", "1", "2", "3", "30"}
    );
}

TEST_CASE("No inputs - int") {
    NS::Featurizers::MinMaxImputerEstimator<int>        estimator(NS::CreateTestAnnotationMapsPtr(1), 0, true);

    estimator.begin_training();
    CHECK_THROWS_WITH(estimator.complete_training(), "The imputed value may not be null");
}

TEST_CASE("No inputs - nullable type") {
    // No inputs aren't a problem when the input type is nullable
    NS::Featurizers::MinMaxImputerEstimator<float>      estimator(NS::CreateTestAnnotationMapsPtr(1), 0, true);

    estimator.begin_training();
    estimator.complete_training();
}

TEST_CASE("Exceptions") {
    CHECK_THROWS_WITH(NS::Featurizers::MinMaxImputerEstimator<int>(NS::CreateTestAnnotationMapsPtr(1), 10, true), "colIndex");
}
