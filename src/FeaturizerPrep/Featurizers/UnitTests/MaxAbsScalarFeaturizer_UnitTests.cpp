// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Featurizers/MaxAbsScalarFeaturizer.h"
#include "../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

template<typename InputT, typename TransformedT>
void TestWrapper(){
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputT>>(
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(-4)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(3)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(0)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(2)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(-1))
    );

    auto inferencingInput = NS::TestHelpers::make_vector<InputT>(
        static_cast<InputT>(-4),
        static_cast<InputT>(3),
        static_cast<InputT>(0),
        static_cast<InputT>(2),
        static_cast<InputT>(-1)
    );

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedT>(
        static_cast<TransformedT>(-1.0 ),
        static_cast<TransformedT>( 0.75),
        static_cast<TransformedT>( 0.0 ),
        static_cast<TransformedT>( 0.5 ),
        static_cast<TransformedT>(-0.25)
    );

    CHECK(
        NS::TestHelpers::FuzzyCheck(
            NS::TestHelpers::TransformerEstimatorTest(
                NS::Featurizers::MaxAbsScalarEstimator<InputT, TransformedT>(NS::CreateTestAnnotationMapsPtr(1), 0),
                trainingBatches,
                inferencingInput
            ), 
            inferencingOutput
        )
    );

}

template<typename InputT, typename TransformedT>
void TestWrapper_ZeroScale(){
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputT>>(
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(0)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(0)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(0))
    );

    auto inferencingInput = NS::TestHelpers::make_vector<InputT>(
        static_cast<InputT>(0),
        static_cast<InputT>(0),
        static_cast<InputT>(0)
    );

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedT>(
        static_cast<TransformedT>(0),
        static_cast<TransformedT>(0),
        static_cast<TransformedT>(0)
    );

    CHECK(
        NS::TestHelpers::FuzzyCheck(
            NS::TestHelpers::TransformerEstimatorTest(
                NS::Featurizers::MaxAbsScalarEstimator<InputT, TransformedT>(NS::CreateTestAnnotationMapsPtr(1), 0),
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
    TestWrapper<InputT, TransformedT>();
    TestWrapper_ZeroScale<InputT, TransformedT>();
}

//Integration test
TEST_CASE("MaxAbsScalarFeaturizer - input<int8_t> - output<float_t/double_t>") {
    TestWrapper_Integration_Tests<std::int8_t, std::float_t>();
    TestWrapper_Integration_Tests<std::int8_t, std::double_t>();
}

TEST_CASE("MaxAbsScalarFeaturizer - input<float_t> - output<float_t/double_t>") {
    TestWrapper_Integration_Tests<std::float_t, std::float_t>();
    TestWrapper_Integration_Tests<std::float_t, std::double_t>();
}
