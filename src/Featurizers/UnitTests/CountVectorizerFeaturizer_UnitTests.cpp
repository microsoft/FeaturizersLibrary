// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Archive.h"
#include "../CountVectorizerFeaturizer.h"
#include "../Structs.h"
#include "../TestHelpers.h"
#include "../../Traits.h"

namespace NS = Microsoft::Featurizer;

using IndexMapType = std::unordered_map<std::string, std::uint32_t>;
using AnalyzerMethod                       = NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy::AnalyzerMethod;

//todo: more tests will be added

TEST_CASE("string_nobinary") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::uint32_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                            NS::TestHelpers::make_vector<InputType>("orange apple orange grape"),
                            NS::TestHelpers::make_vector<InputType>("grape carrot carrot apple"),
                            NS::TestHelpers::make_vector<InputType>("peach banana orange banana")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("banana grape grape apple apple apple orange");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(3,0));
    values.emplace_back(TransformedType::ValueEncoding(1,1));
    values.emplace_back(TransformedType::ValueEncoding(2,3));
    values.emplace_back(TransformedType::ValueEncoding(1,4));
    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
                                                                           TransformedType(6          /// is this 6 or 4??? training dictionary size or inference dictionary size
                                                                           , std::move(values))
                                                                          );


    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::CountVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0, Microsoft::Featurizer::Strings::ToLower, AnalyzerMethod::Word, "",
                                                                                                                              1.0, 0, nonstd::optional<std::uint32_t>(), nonstd::optional<IndexMapType>(), 1, 1, false),
            trainingBatches,
            inferencingInput
        )== inferencingOutput
    );
}

// TEST_CASE("string_binary") {
//     using InputType       = std::string;
//     using TransformedType = NS::Featurizers::SingleValueSparseVectorEncoding<std::uint64_t>;

//     auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
//                             NS::TestHelpers::make_vector<InputType>("orange apple orange"),
//                             NS::TestHelpers::make_vector<InputType>("grape carrot carrot"),
//                             NS::TestHelpers::make_vector<InputType>("peach banana orange")
//                             );

//     auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("banana grape grape apple apple apple orange");

//     auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
//                                                                            TransformedType(0,1),
//                                                                            TransformedType(2,1),
//                                                                            TransformedType(3,1),
//                                                                            TransformedType(1,1)
//                                                                           );

//     CHECK(
//         NS::TestHelpers::TransformerEstimatorTest(
//             NS::Featurizers::CountVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0, 1.0, 0.0, 1, IndexMapType(), true),
//             trainingBatches,
//             inferencingInput
//         )== inferencingOutput
//     );
// }

// TEST_CASE("string_nobinary_0.5-1.0") {
//     using InputType       = std::string;
//     using TransformedType = NS::Featurizers::SingleValueSparseVectorEncoding<std::uint64_t>;

//     auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
//                             NS::TestHelpers::make_vector<InputType>("orange apple orange grape"),
//                             NS::TestHelpers::make_vector<InputType>("grape carrot carrot apple"),
//                             NS::TestHelpers::make_vector<InputType>("peach banana orange banana")
//                             );

//     auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("banana grape grape apple apple apple orange");

//     auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
//                                                                            TransformedType(0,3),
//                                                                            TransformedType(1,2),
//                                                                            TransformedType(2,1)
//                                                                           );

//     CHECK(
//         NS::TestHelpers::TransformerEstimatorTest(
//             NS::Featurizers::CountVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0, 1.0, 0.5, 1, IndexMapType(), false),
//             trainingBatches,
//             inferencingInput
//         )== inferencingOutput
//     );
// }

// TEST_CASE("string_nobinary_0.5-1.0_vocabulary") {
//     using InputType       = std::string;
//     using TransformedType = NS::Featurizers::SingleValueSparseVectorEncoding<std::uint64_t>;

//     auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
//                             NS::TestHelpers::make_vector<InputType>("orange apple orange grape"),
//                             NS::TestHelpers::make_vector<InputType>("grape carrot carrot apple"),
//                             NS::TestHelpers::make_vector<InputType>("peach banana orange banana")
//                             );

//     auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("banana grape grape apple apple apple orange");

//     auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
//                                                                            TransformedType(2,3),
//                                                                            TransformedType(1,2),
//                                                                            TransformedType(0,1)
//                                                                           );

//     IndexMapType vocabulary;
//     vocabulary.insert(std::make_pair("apple", 2));
//     vocabulary.insert(std::make_pair("grape", 1));
//     vocabulary.insert(std::make_pair("orange", 0));

//     CHECK(
//         NS::TestHelpers::TransformerEstimatorTest(
//             NS::Featurizers::CountVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0, 1.0, 0.5, 1, vocabulary, false),
//             trainingBatches,
//             inferencingInput
//         )== inferencingOutput
//     );
// }
