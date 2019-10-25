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

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::MaxAbsScalarEstimator<InputT, TransformedT>       estimator = NS::Featurizers::MaxAbsScalarEstimator<InputT, TransformedT>(pAllColumnAnnotations);

    CHECK(
        NS::TestHelpers::FuzzyCheck(
            NS::TestHelpers::TransformerEstimatorTest(
                estimator,
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
