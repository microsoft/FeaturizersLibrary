// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Archive.h"
#include "../../Featurizers/RobustScalarFeaturizer.h"
#include "../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

template<typename InputT, typename TransformedT>
void TestWrapper_Default_WithCentering(){
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputT>>(
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(1)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(7)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(5)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(3)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(9))
    );

    auto inferencingInput = NS::TestHelpers::make_vector<InputT>(
        static_cast<InputT>(1),
        static_cast<InputT>(3),
        static_cast<InputT>(5),
        static_cast<InputT>(7),
        static_cast<InputT>(9)
    );

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedT>(
        static_cast<TransformedT>(-1.0),
        static_cast<TransformedT>(-0.5),
        static_cast<TransformedT>( 0.0),
        static_cast<TransformedT>( 0.5),
        static_cast<TransformedT>( 1.0)
    );

    CHECK(
        NS::TestHelpers::FuzzyCheck(
            NS::TestHelpers::TransformerEstimatorTest(
                NS::Featurizers::RobustScalarEstimator<InputT, TransformedT>::CreateWithDefaultScaling(NS::CreateTestAnnotationMapsPtr(1), 0, true),
                trainingBatches,
                inferencingInput
            ),
            inferencingOutput
        )
    );
}

template<typename InputT, typename TransformedT>
void TestWrapper_Default_NoCentering(){
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputT>>(
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(1)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(7)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(5)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(3)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(9))
    );

    auto inferencingInput = NS::TestHelpers::make_vector<InputT>(
        static_cast<InputT>(1),
        static_cast<InputT>(3),
        static_cast<InputT>(5),
        static_cast<InputT>(7),
        static_cast<InputT>(9)
    );

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedT>(
        static_cast<TransformedT>(1.0/4.0),
        static_cast<TransformedT>(3.0/4.0),
        static_cast<TransformedT>(5.0/4.0),
        static_cast<TransformedT>(7.0/4.0),
        static_cast<TransformedT>(9.0/4.0)
    );

    CHECK(
        NS::TestHelpers::FuzzyCheck(
            NS::TestHelpers::TransformerEstimatorTest(
                NS::Featurizers::RobustScalarEstimator<InputT, TransformedT>::CreateWithDefaultScaling(NS::CreateTestAnnotationMapsPtr(1), 0, false),
                trainingBatches,
                inferencingInput
            ),
            inferencingOutput
        )
    );
}

template<typename InputT, typename TransformedT>
void TestWrapper_Default_NoCentering_ZeroScale(){
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputT>>(
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(10)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(10)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(10))
    );

    auto inferencingInput = NS::TestHelpers::make_vector<InputT>(
        static_cast<InputT>(10),
        static_cast<InputT>(10),
        static_cast<InputT>(10)
    );

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedT>(
        static_cast<TransformedT>(10),
        static_cast<TransformedT>(10),
        static_cast<TransformedT>(10)
    );

    CHECK(
        NS::TestHelpers::FuzzyCheck(
            NS::TestHelpers::TransformerEstimatorTest(
                NS::Featurizers::RobustScalarEstimator<InputT, TransformedT>::CreateWithDefaultScaling(NS::CreateTestAnnotationMapsPtr(1), 0, false),
                trainingBatches,
                inferencingInput
            ),
            inferencingOutput
        )
    );
}

template<typename InputT, typename TransformedT>
void TestWrapper_WithCentering_NoScaling(){
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputT>>(
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(1)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(7)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(5)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(3)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(9))
    );

    auto inferencingInput = NS::TestHelpers::make_vector<InputT>(
        static_cast<InputT>(1),
        static_cast<InputT>(3),
        static_cast<InputT>(5),
        static_cast<InputT>(7),
        static_cast<InputT>(9)
    );

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedT>(
        static_cast<TransformedT>(-4),
        static_cast<TransformedT>(-2),
        static_cast<TransformedT>(0),
        static_cast<TransformedT>(2),
        static_cast<TransformedT>(4)
    );

    CHECK(
        NS::TestHelpers::FuzzyCheck(
            NS::TestHelpers::TransformerEstimatorTest(
                NS::Featurizers::RobustScalarEstimator<InputT, TransformedT>(NS::CreateTestAnnotationMapsPtr(1), 0, true),
                trainingBatches,
                inferencingInput
            ),
            inferencingOutput
        )
    );
}

template<typename InputT, typename TransformedT>
void TestWrapper_WithCentering_CustomScaling(std::float_t q_min, std::float_t q_max){
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputT>>(
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(1)),
        NS::TestHelpers:: make_vector<InputT>(static_cast<InputT>(7)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(5)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(3)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(9))
    );

    auto inferencingInput = NS::TestHelpers::make_vector<InputT>(
        static_cast<InputT>(1),
        static_cast<InputT>(3),
        static_cast<InputT>(5),
        static_cast<InputT>(7),
        static_cast<InputT>(9)
    );

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedT>(
        static_cast<TransformedT>(static_cast<std::float_t>(-50.0) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>(-25.0) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>(  0.0) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>( 25.0) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>( 50.0) / (q_max - q_min))
    );

    CHECK(
        NS::TestHelpers::FuzzyCheck(
            NS::TestHelpers::TransformerEstimatorTest(
                NS::Featurizers::RobustScalarEstimator<InputT, TransformedT>(NS::CreateTestAnnotationMapsPtr(1), 0, true, q_min, q_max),
                trainingBatches,
                inferencingInput
            ),
            inferencingOutput
        )
    );
}

template<typename InputT, typename TransformedT>
void TestWrapper_NoCentering_CustomScaling(std::float_t q_min, std::float_t q_max){
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputT>>(
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(1)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(7)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(5)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(3)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(9))
    );

    auto inferencingInput = NS::TestHelpers::make_vector<InputT>(
        static_cast<InputT>(1),
        static_cast<InputT>(3),
        static_cast<InputT>(5),
        static_cast<InputT>(7),
        static_cast<InputT>(9)
    );

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedT>(
        static_cast<TransformedT>(static_cast<std::float_t>( 12.5) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>( 37.5) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>( 62.5) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>( 87.5) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>(112.5) / (q_max - q_min))
    );

    CHECK(
        NS::TestHelpers::FuzzyCheck(
            NS::TestHelpers::TransformerEstimatorTest(
                NS::Featurizers::RobustScalarEstimator<InputT, TransformedT>(NS::CreateTestAnnotationMapsPtr(1), 0, false, q_min, q_max),
                trainingBatches,
                inferencingInput
            ),
            inferencingOutput
        )
    );
}

//TestWrapper for Integration test
template<typename InputT, typename TransformedT>
void TestWrapper_Integration_Tests(){
    TestWrapper_Default_WithCentering<InputT, TransformedT>();
    TestWrapper_Default_NoCentering<InputT, TransformedT>();
    TestWrapper_Default_NoCentering_ZeroScale<InputT, TransformedT>();
    TestWrapper_WithCentering_NoScaling<InputT, TransformedT>();
    TestWrapper_WithCentering_CustomScaling<InputT, TransformedT>(0.0, 100.0);
    TestWrapper_WithCentering_CustomScaling<InputT, TransformedT>(20.0, 80.0);
    TestWrapper_WithCentering_CustomScaling<InputT, TransformedT>(35.0, 65.0);
    TestWrapper_NoCentering_CustomScaling<InputT, TransformedT>(0.0, 100.0);
    TestWrapper_NoCentering_CustomScaling<InputT, TransformedT>(20.0, 80.0);
    TestWrapper_NoCentering_CustomScaling<InputT, TransformedT>(35.0, 65.0);
}

//Integration test
TEST_CASE("RobustScalarFeaturizer - input<int8_t> - output<float_t/double_t>") {
    TestWrapper_Integration_Tests<std::int8_t, std::float_t>();
    TestWrapper_Integration_Tests<std::int8_t, std::double_t>();
}

TEST_CASE("RobustScalarFeaturizer - input<float_t> - output<float_t/double_t>") {
    TestWrapper_Integration_Tests<std::float_t, std::float_t>();
    TestWrapper_Integration_Tests<std::float_t, std::double_t>();
}
