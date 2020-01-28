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
using NormMethod = typename NS::Featurizers::TfidfVectorizerTransformer::NormMethod;
using TfidfPolicy = typename NS::Featurizers::TfidfPolicy;

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

// for (auto const & item : result[0].Values)
//     std::cout << item.Value << ", "<< item.Index << std::endl;

TEST_CASE("string_standard_1_with_decorator") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is THE first document"),
                                NS::TestHelpers::make_vector<InputType>("this DOCUMENT is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the THIRD one"),
                                NS::TestHelpers::make_vector<InputType>("IS this THE first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("THIS is the FIRST document");

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
                                    true,
                                    AnalyzerMethod::Word,
                                    ""
                                ),
                                trainingBatches,
                                inferencingInput
                            );

    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_standard_1_no_decorator") {
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
                                    false,
                                    AnalyzerMethod::Word,
                                    ""
                                ),
                                trainingBatches,
                                inferencingInput
                            );
    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_standard_2_with_decorator") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is THE first document"),
                                NS::TestHelpers::make_vector<InputType>("this DOCUMENT is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the THIRD one"),
                                NS::TestHelpers::make_vector<InputType>("IS this THE first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("this DOCUMENT is the second document");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.687624f, 1));
    values.emplace_back(TransformedType::ValueEncoding(0.281089f, 3));
    values.emplace_back(TransformedType::ValueEncoding(0.538648f, 5));
    values.emplace_back(TransformedType::ValueEncoding(0.281089f, 6));
    values.emplace_back(TransformedType::ValueEncoding(0.281089f, 8));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    true,
                                    AnalyzerMethod::Word,
                                    ""
                                ),
                                trainingBatches,
                                inferencingInput
                            );

    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_standard_2_no_decorator") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("this document is the second document");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.687624f, 1));
    values.emplace_back(TransformedType::ValueEncoding(0.281089f, 3));
    values.emplace_back(TransformedType::ValueEncoding(0.538648f, 5));
    values.emplace_back(TransformedType::ValueEncoding(0.281089f, 6));
    values.emplace_back(TransformedType::ValueEncoding(0.281089f, 8));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    false,
                                    AnalyzerMethod::Word,
                                    ""
                                ),
                                trainingBatches,
                                inferencingInput
                            );
    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_standard_3_with_decorator") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is THE first document"),
                                NS::TestHelpers::make_vector<InputType>("this DOCUMENT is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the THIRD one"),
                                NS::TestHelpers::make_vector<InputType>("IS this THE first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("and this is the THIRD one");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.511849f, 0));
    values.emplace_back(TransformedType::ValueEncoding(0.267104f, 3));
    values.emplace_back(TransformedType::ValueEncoding(0.511849f, 4));
    values.emplace_back(TransformedType::ValueEncoding(0.267104f, 6));
    values.emplace_back(TransformedType::ValueEncoding(0.511849f, 7));
    values.emplace_back(TransformedType::ValueEncoding(0.267104f, 8));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    true,
                                    AnalyzerMethod::Word,
                                    ""
                                ),
                                trainingBatches,
                                inferencingInput
                            );

    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_standard_3_no_decorator") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("and this is the third one");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.511849f, 0));
    values.emplace_back(TransformedType::ValueEncoding(0.267104f, 3));
    values.emplace_back(TransformedType::ValueEncoding(0.511849f, 4));
    values.emplace_back(TransformedType::ValueEncoding(0.267104f, 6));
    values.emplace_back(TransformedType::ValueEncoding(0.511849f, 7));
    values.emplace_back(TransformedType::ValueEncoding(0.267104f, 8));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    false,
                                    AnalyzerMethod::Word,
                                    ""
                                ),
                                trainingBatches,
                                inferencingInput
                            );
    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_standard_4_with_decorator") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is THE first document"),
                                NS::TestHelpers::make_vector<InputType>("this DOCUMENT is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the THIRD one"),
                                NS::TestHelpers::make_vector<InputType>("IS this THE first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("IS this THE first document");

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
                                    true,
                                    AnalyzerMethod::Word,
                                    ""
                                ),
                                trainingBatches,
                                inferencingInput
                            );

    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_standard_4_no_decorator") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("is this the first document");

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
                                    false,
                                    AnalyzerMethod::Word,
                                    ""
                                ),
                                trainingBatches,
                                inferencingInput
                            );
    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_L1Norm") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("is this the first document");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.213315f, 1));
    values.emplace_back(TransformedType::ValueEncoding(0.263487f, 2));
    values.emplace_back(TransformedType::ValueEncoding(0.174399f, 3));
    values.emplace_back(TransformedType::ValueEncoding(0.174399f, 6));
    values.emplace_back(TransformedType::ValueEncoding(0.174399f, 8));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    false,
                                    AnalyzerMethod::Word,
                                    "",
                                    NormMethod::L1
                                ),
                                trainingBatches,
                                inferencingInput
                            );
    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_bitflag_1000") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("the second document");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.577350f, 1));
    values.emplace_back(TransformedType::ValueEncoding(0.577350f, 5));
    values.emplace_back(TransformedType::ValueEncoding(0.577350f, 6));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    false,
                                    AnalyzerMethod::Word,
                                    "",
                                    NormMethod::L2,
                                    TfidfPolicy::Binary
                                ),
                                trainingBatches,
                                inferencingInput
                            );
    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_bitflag_1110") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("the second document");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.492489f, 1));
    values.emplace_back(TransformedType::ValueEncoding(0.771579f, 5));
    values.emplace_back(TransformedType::ValueEncoding(0.402642f, 6));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    false,
                                    AnalyzerMethod::Word,
                                    "",
                                    NormMethod::L2,
                                    TfidfPolicy::Binary | TfidfPolicy::UseIdf | TfidfPolicy::SmoothIdf
                                ),
                                trainingBatches,
                                inferencingInput
                            );
    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_bitflag_1100") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("the second document");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.464313f, 1));
    values.emplace_back(TransformedType::ValueEncoding(0.801943f, 5));
    values.emplace_back(TransformedType::ValueEncoding(0.375901f, 6));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    false,
                                    AnalyzerMethod::Word,
                                    "",
                                    NormMethod::L2,
                                    TfidfPolicy::Binary | TfidfPolicy::UseIdf
                                ),
                                trainingBatches,
                                inferencingInput
                            );
    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_bitflag_0000") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("the second document");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.577350f, 1));
    values.emplace_back(TransformedType::ValueEncoding(0.577350f, 5));
    values.emplace_back(TransformedType::ValueEncoding(0.577350f, 6));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    false,
                                    AnalyzerMethod::Word,
                                    "",
                                    NormMethod::L2,
                                    static_cast<TfidfPolicy>(0)
                                ),
                                trainingBatches,
                                inferencingInput
                            );
    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_bitflag_0100") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("the second document");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.464313f, 1));
    values.emplace_back(TransformedType::ValueEncoding(0.801943f, 5));
    values.emplace_back(TransformedType::ValueEncoding(0.375901f, 6));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    false,
                                    AnalyzerMethod::Word,
                                    "",
                                    NormMethod::L2,
                                    TfidfPolicy::UseIdf
                                ),
                                trainingBatches,
                                inferencingInput
                            );
    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_bitflag_0001") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("the second document");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.577350f, 1));
    values.emplace_back(TransformedType::ValueEncoding(0.577350f, 5));
    values.emplace_back(TransformedType::ValueEncoding(0.577350f, 6));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    false,
                                    AnalyzerMethod::Word,
                                    "",
                                    NormMethod::L2,
                                    TfidfPolicy::SublinearTf
                                ),
                                trainingBatches,
                                inferencingInput
                            );
    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_bitflag_0111") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("the second document");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.492489f, 1));
    values.emplace_back(TransformedType::ValueEncoding(0.771579f, 5));
    values.emplace_back(TransformedType::ValueEncoding(0.402642f, 6));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    false,
                                    AnalyzerMethod::Word,
                                    "",
                                    NormMethod::L2,
                                    TfidfPolicy::UseIdf | TfidfPolicy::SmoothIdf | TfidfPolicy::SublinearTf
                                ),
                                trainingBatches,
                                inferencingInput
                            );
    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}

TEST_CASE("string_bitflag_0101") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::float_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                                NS::TestHelpers::make_vector<InputType>("this is the first document"),
                                NS::TestHelpers::make_vector<InputType>("this document is the second document"),
                                NS::TestHelpers::make_vector<InputType>("and this is the third one"),
                                NS::TestHelpers::make_vector<InputType>("is this the first document")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("the second document");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(0.464313f, 1));
    values.emplace_back(TransformedType::ValueEncoding(0.801943f, 5));
    values.emplace_back(TransformedType::ValueEncoding(0.375901f, 6));

    auto inferencingLabel = NS::TestHelpers::make_vector<TransformedType>(TransformedType(9, std::move(values)));
    auto inferencingOutput = NS::TestHelpers::TransformerEstimatorTest(
                                NS::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>(
                                    NS::CreateTestAnnotationMapsPtr(1),
                                    0,
                                    false,
                                    AnalyzerMethod::Word,
                                    "",
                                    NormMethod::L2,
                                    TfidfPolicy::UseIdf | TfidfPolicy::SublinearTf
                                ),
                                trainingBatches,
                                inferencingInput
                            );
    SparseVectorNumericCheck<std::float_t>(std::move(inferencingOutput[0]), std::move(inferencingLabel[0]));
}








