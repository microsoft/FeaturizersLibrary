// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Featurizers/MinMaxScalarFeaturizer.h"
#include "../TestHelpers.h"
#include "../../Archive.h"
#include "../../Traits.h"

namespace NS = Microsoft::Featurizer;

// test for int
TEST_CASE("int") {
    using InputType       = std::int8_t;
    using TransformedType = std::double_t;

    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(1)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(3)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(5)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(7)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(9)));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(15));

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        static_cast<TransformedType>(1.75)
    );

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MinMaxScalarEstimator<InputType, TransformedType>(NS::CreateTestAnnotationMapsPtr(1), 0),
            trainingBatches,
            inferencingInput
        ) == inferencingOutput
    );
}

// test for float
TEST_CASE("float") {
    using InputType       = std::float_t;
    using TransformedType = std::double_t;

    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(-1)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(-0.5)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(0)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(1)));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(2));

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        static_cast<TransformedType>(1.5)
    );

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MinMaxScalarEstimator<InputType, TransformedType>(NS::CreateTestAnnotationMapsPtr(1), 0),
            trainingBatches,
            inferencingInput
        ) == inferencingOutput
    );
}

// test for only one input
TEST_CASE("only one input") {
    using InputType       = std::int8_t;
    using TransformedType = std::double_t;

    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(-1)));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(2));

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        static_cast<TransformedType>(0)
    );

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MinMaxScalarEstimator<InputType, TransformedType>(NS::CreateTestAnnotationMapsPtr(1), 0),
            trainingBatches,
            inferencingInput
        ) == inferencingOutput
    );
}

// test for null inferencing data
TEST_CASE("null training data") {
    using InputType       = std::float_t;
    using TransformedType = std::double_t;

    InputType null = NS::Traits<InputType>::CreateNullValue();
    // null data in training data should be ignored
    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(-1)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(-0.5)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(0)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(1))
                                    );

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(null);


    std::vector<TransformedType> inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MinMaxScalarEstimator<InputType, TransformedType>(NS::CreateTestAnnotationMapsPtr(1), 0),
            trainingBatches,
            inferencingInput
    );
    CHECK(NS::Traits<TransformedType>::IsNull(inferencingOutput[0]));
}

TEST_CASE("Serialization/Deserialization") {
    using InputType       = std::float_t;
    using TransformedType = std::double_t;
    using TransformerType = NS::Featurizers::MinMaxScalarTransformer<InputType, TransformedType>;

    auto model = std::make_shared<TransformerType>(static_cast<InputType>(-5), static_cast<InputType>(9));

    NS::Archive archive;
    model->save(archive);
    std::vector<unsigned char> vec = archive.commit();
    CHECK(vec.size() == 8);

    NS::Archive loader(vec);
    TransformerType modelLoaded(loader);
    CHECK(modelLoaded == *model);
}
