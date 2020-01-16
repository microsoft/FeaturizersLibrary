// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Featurizers/NormalizeFeaturizer.h"
#include "../TestHelpers.h"
#include "../../Traits.h"
#include "../Structs.h"
namespace NS = Microsoft::Featurizer;

// TODO:: Add more unit tests
TEST_CASE("test") {
    using ValueType       = std::int16_t;
    using InputType       = std::vector<ValueType>;
    using TransformedType = std::vector<long double>;

    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(NS::TestHelpers::make_vector<ValueType>(4, 1, 2, 2)),
                                    NS::TestHelpers::make_vector<InputType>(NS::TestHelpers::make_vector<ValueType>(1, 3, 9, 3)),
                                    NS::TestHelpers::make_vector<InputType>(NS::TestHelpers::make_vector<ValueType>(5, 7, 5, 1)));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(NS::TestHelpers::make_vector<ValueType>(4, 1, 2, 2));

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        NS::TestHelpers::make_vector<long double>(0.8, 0.2, 0.4, 0.4)
    );

    NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::NormalizeEstimator<InputType, NS::Featurizers::NormType::L2>(pAllColumnAnnotations, 0),
            trainingBatches,
            inferencingInput
        ) == inferencingOutput
    );
}
