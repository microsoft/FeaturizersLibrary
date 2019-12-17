// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Featurizers/OneHotEncoderFeaturizer.h"
#include "../TestHelpers.h"
#include "../../Archive.h"
#include "../../Traits.h"

namespace NS = Microsoft::Featurizer;

template <typename InputT>
using IndexMap = typename NS::Featurizers::Components::IndexMapAnnotationData<InputT>::IndexMap;

template <typename InputT>
using Histogram = typename NS::Featurizers::Components::HistogramAnnotationData<InputT>::Histogram;

// test for unsigned int
TEST_CASE("uint32_t") {
    using InputType       = std::uint32_t;
    using TransformedType = NS::Featurizers::OneHotStruct;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                NS::TestHelpers::make_vector<InputType>(10, 20, 10),
                NS::TestHelpers::make_vector<InputType>(30),
                NS::TestHelpers::make_vector<InputType>(10, 10, 11, 15),
                NS::TestHelpers::make_vector<InputType>(18, 8));

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>(11, 8, 10, 15, 20);

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        TransformedType(2,7,1),
        TransformedType(0,7,1),
        TransformedType(1,7,1),
        TransformedType(3,7,1),
        TransformedType(5,7,1)
    );
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::OneHotEncoderEstimator<InputType>(NS::CreateTestAnnotationMapsPtr(1), 0, false),
            trainingBatches,
            inferencingInput
        )== inferencingOutput
    );
}

// test for string
TEST_CASE("string") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::OneHotStruct;
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                            NS::TestHelpers::make_vector<InputType>("orange", "apple",  "orange",
                                                                    "grape",  "carrot", "carrot",
                                                                    "peach",  "banana", "orange")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("banana", "grape", "apple","orange");

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
                                                                           TransformedType(1,6,1),
                                                                           TransformedType(3,6,1),
                                                                           TransformedType(0,6,1),
                                                                           TransformedType(4,6,1)
    );
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::OneHotEncoderEstimator<InputType>(NS::CreateTestAnnotationMapsPtr(1), 0, false),
            trainingBatches,
            inferencingInput
        )== inferencingOutput
    );
}

TEST_CASE("Empty index map") {
    CHECK_THROWS_WITH(NS::Featurizers::OneHotEncoderTransformer<std::string>(IndexMap<std::string>(), true) , "Index map is empty!");
}

TEST_CASE("unseen values") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::OneHotStruct;
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                            NS::TestHelpers::make_vector<InputType>("orange", "apple",  "orange",
                                                                    "grape",  "carrot", "carrot",
                                                                    "peach",  "banana", "orange")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("banana", "grape", "apple","orange", "hello");

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
                                                                           TransformedType(2,7,1),
                                                                           TransformedType(4,7,1),
                                                                           TransformedType(1,7,1),
                                                                           TransformedType(5,7,1),
                                                                           TransformedType(0,7,1)
    );
    // when an inference data is not seen before, in the non-throw mode, the featurizer should generate 0
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::OneHotEncoderEstimator<InputType>(NS::CreateTestAnnotationMapsPtr(1), 0, true),
            trainingBatches,
            inferencingInput
        )== inferencingOutput
    );
    // when an inference data is not seen before, in the throw mode, the featurizer should throw an error
    CHECK_THROWS_WITH(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::OneHotEncoderEstimator<InputType>(NS::CreateTestAnnotationMapsPtr(1), 0, false),
            trainingBatches,
            inferencingInput
        )== inferencingOutput, "'input' was not found"
    );
}

TEST_CASE("Serialization/Deserialization- Numeric") {
    using InputType       = std::uint32_t;
    using TransformerType = NS::Featurizers::OneHotEncoderTransformer<InputType>;

    IndexMap<InputType>                     indexmap({
                                   {6, 1},
                                   {7, 2},
                                   {8, 3},
                                   {10, 4},
                                   {11, 5},
                                   {15, 6},
                                   {18, 7},
                                   {20, 8},
                                   {30, 9}
                                   });

    TransformerType                         original(indexmap, true);
    NS::Archive                             out;

    original.save(out);

    NS::Archive                             in(out.commit());
    TransformerType                         other(in);

    CHECK(other == original);
}

TEST_CASE("Serialization/Deserialization- string") {
    using InputType       = std::string;
    using TransformerType = NS::Featurizers::OneHotEncoderTransformer<InputType>;

    IndexMap<InputType>                     indexmap({
                                    {"apple", 1},
                                    {"banana", 2},
                                    {"grape", 3},
                                    {"orange", 4},
                                    {"peach", 5}});

    TransformerType                         original(indexmap, false);
    NS::Archive                             out;

    original.save(out);

    NS::Archive                             in(out.commit());
    TransformerType                         other(in);

    CHECK(other == original);
}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        (NS::Featurizers::OneHotEncoderTransformer<std::string>(in)),
        Catch::Contains("Unsupported archive version")
    );
}

