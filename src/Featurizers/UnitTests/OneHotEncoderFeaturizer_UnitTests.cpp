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

#if 0 // TODO: Add unordered_map to Traits

// TEST_CASE("Serialization/Deserialization- Numeric") {
//     using InputType       = std::uint32_t;
//     using TransformedType = NS::Featurizers::OneHotStruct;
//     using TransformerType = NS::Featurizers::OneHotEstimator<InputType, TransformedType>::Transformer;
//     IndexMap<InputType, std::uint32_t> indexmap({
//                                    {6, 1},
//                                    {7, 2},
//                                    {8, 3},
//                                    {10, 4},
//                                    {11, 5},
//                                    {15, 6},
//                                    {18, 7},
//                                    {20, 8},
//                                    {30, 9}
//                                    });
//     Histogram<InputType> histogram({
//                                    {6, 1},
//                                    {7, 5},
//                                    {8, 3},
//                                    {10, 4},
//                                    {11, 9},
//                                    {15, 7},
//                                    {18, 10},
//                                    {20, 1},
//                                    {30, 2}
//                                    });
//     auto model = std::make_shared<TransformerType>(indexmap, histogram, true);

//     NS::Archive archive;
//     model->save(archive);
//     std::vector<unsigned char> vec = archive.commit();
//     CHECK(vec.size() == 153);

//     NS::Archive loader(vec);
//     TransformerType modelLoaded(loader);
//     CHECK(modelLoaded==*model);
// }

// TEST_CASE("Serialization/Deserialization- string") {
//     using InputType       = std::string;
//     using TransformedType = NS::Featurizers::OneHotStruct;
//     using TransformerType = NS::Featurizers::OneHotEstimator<InputType, TransformedType>::Transformer;

//     IndexMap<InputType, std::uint32_t> indexmap({
//                                     {"apple", 1},
//                                     {"banana", 2},
//                                     {"grape", 3},
//                                     {"orange", 4},
//                                     {"peach", 5}});
//     Histogram<InputType> histogram({
//                                     {"apple", 4},
//                                     {"banana", 2},
//                                     {"grape", 3},
//                                     {"orange", 7},
//                                     {"peach", 9}});
//     auto model = std::make_shared<TransformerType>(indexmap, histogram, false);

//     NS::Archive archive;
//     model->save(archive);
//     std::vector<unsigned char> vec = archive.commit();

//     NS::Archive loader(vec);
//     TransformerType modelLoaded(loader);
//     CHECK(modelLoaded==*model);

// }
#endif
