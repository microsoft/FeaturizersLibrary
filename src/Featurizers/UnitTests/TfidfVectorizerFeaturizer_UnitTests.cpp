// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Archive.h"
#include "../TfidfVectorizerFeaturizer.h"
#include "../Structs.h"
#include "../TestHelpers.h"
#include "../../Traits.h"

namespace NS = Microsoft::Featurizer;

using IndexMapType = typename NS::Featurizers::TfidfVectorizerTransformer::IndexMapType;

//todo: more tests will be added

TEST_CASE("string_standard_1") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::TFIDFStruct;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("this is the first document");

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>( TransformedType(1,0.384085f),
                                                                            TransformedType(3,0.384085f),
                                                                            TransformedType(5,0.384085f),
                                                                            TransformedType(4,0.580286f),
                                                                            TransformedType(2,0.469791f)
                                                                          );

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                NS::CreateTestAnnotationMapsPtr(1), 0, 1.0, 0.0, 1, IndexMapType(), false, "l2", true, true, false
                ),
            trainingBatches,
            inferencingInput
        )== inferencingOutput
    );       
}

TEST_CASE("string_standard_2") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::TFIDFStruct;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("this document is the second document");

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>( TransformedType(1,0.281089f),
                                                                            TransformedType(3,0.281089f),
                                                                            TransformedType(5,0.281089f),
                                                                            TransformedType(0,0.538648f),
                                                                            TransformedType(2,0.687624f)
                                                                          );

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                NS::CreateTestAnnotationMapsPtr(1), 0, 1.0, 0.0, 1, IndexMapType(), false, "l2", true, true, false
                ),
            trainingBatches,
            inferencingInput
        )== inferencingOutput
    );       
}

TEST_CASE("string_standard_3") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::TFIDFStruct;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("and this is the third one");

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>( TransformedType(1,0.267104f),
                                                                            TransformedType(7,0.511849f),
                                                                            TransformedType(8,0.511849f),
                                                                            TransformedType(3,0.267104f),
                                                                            TransformedType(5,0.267104f),
                                                                            TransformedType(6,0.511849f)
                                                                          );

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                NS::CreateTestAnnotationMapsPtr(1), 0, 1.0, 0.0, 1, IndexMapType(), false, "l2", true, true, false
                ),
            trainingBatches,
            inferencingInput
        )== inferencingOutput
    );       
}

TEST_CASE("string_standard_4") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::TFIDFStruct;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("is this the first document");

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>( TransformedType(1,0.384085f),
                                                                            TransformedType(3,0.384085f),
                                                                            TransformedType(5,0.384085f),
                                                                            TransformedType(4,0.580286f),
                                                                            TransformedType(2,0.469791f)
                                                                          );

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                NS::CreateTestAnnotationMapsPtr(1), 0, 1.0, 0.0, 1, IndexMapType(), false, "l2", true, true, false
                ),
            trainingBatches,
            inferencingInput
        )== inferencingOutput
    );       
}




