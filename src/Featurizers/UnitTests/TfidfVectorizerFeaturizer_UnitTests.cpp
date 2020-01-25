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

using IndexMap = typename NS::Featurizers::TfidfVectorizerTransformer::IndexMap;
using AnalyzerMethod = NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy::AnalyzerMethod;

template<typename T>
void SparseVectorNumericCheck(NS::Featurizers::SparseVectorEncoding<T> const &a,
                              NS::Featurizers::SparseVectorEncoding<T> const &b) {
    CHECK(a.NumElements == b.NumElements);
    assert(a.Values.size() == b.Values.size());
    std::vector<NS::Featurizers::SparseVectorEncoding<std::float_t>::ValueEncoding> const & aValues(a.Values);
    std::vector<NS::Featurizers::SparseVectorEncoding<std::float_t>::ValueEncoding> const & bValues(b.Values);
    for (size_t idx = 0; idx < a.Values.size(); ++idx) {
        CHECK(aValues[idx].Index == bValues[idx].Index);
        CHECK(Approx(aValues[idx].Value) == bValues[idx].Value);
    }
}

TEST_CASE("string_standard_1") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("this is the first document");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.469791f, 1));
    values.emplace_back(TransformedType::ValueEncoding(0.580286f, 2));
    values.emplace_back(TransformedType::ValueEncoding(0.384085f, 3));
    values.emplace_back(TransformedType::ValueEncoding(0.384085f, 6));
    values.emplace_back(TransformedType::ValueEncoding(0.384085f, 8));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    Microsoft::Featurizer::Strings::ToLower,
                                    AnalyzerMethod::Word,
                                    ""
                                ),
                                trainingBatches,
                                inferencingInput
                            );

    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));

    // for (auto const & item : result[0].Values)
    //     std::cout << item.Value << ", "<< item.Index << std::endl;
}

// TEST_CASE("string_standard_2") {
//     using InputType       = std::string;
//     using TransformedType = NS::Featurizers::TFIDFStruct;

//     auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
//                                 NS::TestHelpers::make_vector<InputType>("this is the first document"),
//                                 NS::TestHelpers::make_vector<InputType>("this document is the second document"),
//                                 NS::TestHelpers::make_vector<InputType>("and this is the third one"),
//                                 NS::TestHelpers::make_vector<InputType>("is this the first document")
//                             );

//     auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("this document is the second document");

//     auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>( TransformedType(3,0.281089f),
//                                                                             TransformedType(6,0.281089f),
//                                                                             TransformedType(8,0.281089f),
//                                                                             TransformedType(5,0.538648f),
//                                                                             TransformedType(1,0.687624f)
//                                                                           );

//     // auto result = NS::TestHelpers::TransformerEstimatorTest(
//     //         NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0),
//     //         trainingBatches,
//     //         inferencingInput
//     //     );
//     // for (auto i : result) {
//     //     std::cout << i.dictionaryId << ":" << i.tfidf << std::endl;
//     // }
//     // std::cout << "--------------------------------" << std::endl;

//     CHECK(
//         NS::TestHelpers::TransformerEstimatorTest(
//             NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0),
//             trainingBatches,
//             inferencingInput
//         )== inferencingOutput
//     );
// }

// TEST_CASE("string_standard_3") {
//     using InputType       = std::string;
//     using TransformedType = NS::Featurizers::TFIDFStruct;

//     auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
//                                 NS::TestHelpers::make_vector<InputType>("this is the first document"),
//                                 NS::TestHelpers::make_vector<InputType>("this document is the second document"),
//                                 NS::TestHelpers::make_vector<InputType>("and this is the third one"),
//                                 NS::TestHelpers::make_vector<InputType>("is this the first document")
//                             );

//     auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("and this is the third one");

//     auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>( TransformedType(3,0.267104f),
//                                                                             TransformedType(0,0.511849f),
//                                                                             TransformedType(4,0.511849f),
//                                                                             TransformedType(6,0.267104f),
//                                                                             TransformedType(8,0.267104f),
//                                                                             TransformedType(7,0.511849f)
//                                                                           );
//     // auto result = NS::TestHelpers::TransformerEstimatorTest(
//     //         NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0),
//     //         trainingBatches,
//     //         inferencingInput
//     //     );
//     // for (auto i : result) {
//     //     std::cout << i.dictionaryId << ":" << i.tfidf << std::endl;
//     // }
//     // std::cout << "--------------------------------" << std::endl;

//     CHECK(
//         NS::TestHelpers::TransformerEstimatorTest(
//             NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0),
//             trainingBatches,
//             inferencingInput
//         )== inferencingOutput
//     );
// }

// TEST_CASE("string_standard_4") {
//     using InputType       = std::string;
//     using TransformedType = NS::Featurizers::TFIDFStruct;

//     auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
//                                 NS::TestHelpers::make_vector<InputType>("this is the first document"),
//                                 NS::TestHelpers::make_vector<InputType>("this document is the second document"),
//                                 NS::TestHelpers::make_vector<InputType>("and this is the third one"),
//                                 NS::TestHelpers::make_vector<InputType>("is this the first document")
//                             );

//     auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("is this the first document");

//     auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>( TransformedType(3,0.384085f),
//                                                                             TransformedType(6,0.384085f),
//                                                                             TransformedType(8,0.384085f),
//                                                                             TransformedType(2,0.580286f),
//                                                                             TransformedType(1,0.469791f)
//                                                                           );
//     // auto result = NS::TestHelpers::TransformerEstimatorTest(
//     //         NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0),
//     //         trainingBatches,
//     //         inferencingInput
//     //     );
//     // for (auto i : result) {
//     //     std::cout << i.dictionaryId << ":" << i.tfidf << std::endl;
//     // }
//     // std::cout << "--------------------------------" << std::endl;

//     CHECK(
//         NS::TestHelpers::TransformerEstimatorTest(
//             NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0),
//             trainingBatches,
//             inferencingInput
//         )== inferencingOutput
//     );
// }




