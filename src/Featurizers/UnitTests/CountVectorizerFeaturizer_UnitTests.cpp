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

using IndexMapType   = std::unordered_map<std::string, std::uint32_t>;
using AnalyzerMethod = NS::Featurizers::Components::AnalyzerMethod;


TEST_CASE("empty index map") {
    IndexMapType indexMap(
        {
            {"apple", 1},
            {"banana", 2},
            {"grape", 3},
            {"orange", 4},
            {"peach", 5}
        }
    );
    CHECK_THROWS_WITH(NS::Featurizers::CountVectorizerTransformer(IndexMapType(), false, false, AnalyzerMethod::Word, "", 1, 1), "Index map is empty!");
    CHECK_THROWS_WITH(NS::Featurizers::CountVectorizerTransformer(indexMap, false, false, AnalyzerMethod::Word, "", 0, 1), "ngramRangeMin");
    CHECK_THROWS_WITH(NS::Featurizers::CountVectorizerTransformer(indexMap, false, false, AnalyzerMethod::Word, "", 1, 0), "ngramRangeMax");
}

TEST_CASE("empty training data - without binary without decorator") {
    using InputType       = std::string;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                            NS::TestHelpers::make_vector<InputType>("")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("banana grape grape apple apple apple orange");

    CHECK_THROWS_WITH(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::CountVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0, false, AnalyzerMethod::Word, "",
                                                                                                                              1.0, 0, nonstd::optional<std::uint32_t>(), nonstd::optional<IndexMapType>(), 1, 1, false),
            trainingBatches,
            inferencingInput
        ), "termFrequencyAndIndex"
    );
}

TEST_CASE("empty inferencing data - without binary without decorator") {
    using InputType       = std::string;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                            NS::TestHelpers::make_vector<InputType>("orange apple orange grape"),
                            NS::TestHelpers::make_vector<InputType>("grape carrot carrot apple"),
                            NS::TestHelpers::make_vector<InputType>("peach banana orange banana")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("");

    CHECK_THROWS_WITH(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::CountVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0, false, AnalyzerMethod::Word, "",
                                                                                                                              1.0, 0, nonstd::optional<std::uint32_t>(), nonstd::optional<IndexMapType>(), 1, 1, false),
            trainingBatches,
            inferencingInput
        ), "'values' is empty"
    );
}
TEST_CASE("string - without binary without decorator") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::uint32_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                            NS::TestHelpers::make_vector<InputType>("orange apple oranGE grape"),
                            NS::TestHelpers::make_vector<InputType>("grApe carrot carrot apple"),
                            NS::TestHelpers::make_vector<InputType>("peach Banana orange banana")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("grApe banana grape grape apple apple apple orange oranGE");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(3,1));
    values.emplace_back(TransformedType::ValueEncoding(1,2));
    values.emplace_back(TransformedType::ValueEncoding(1,4));
    values.emplace_back(TransformedType::ValueEncoding(2,5));
    values.emplace_back(TransformedType::ValueEncoding(1,6));
    values.emplace_back(TransformedType::ValueEncoding(1,7));
    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
                                                                           TransformedType(9
                                                                           , std::move(values))
                                                                          );


    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::CountVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0, false, AnalyzerMethod::Word, "",
                                                                                                                              1.0, 0, nonstd::optional<std::uint32_t>(), nonstd::optional<IndexMapType>(), 1, 1, false),
            trainingBatches,
            inferencingInput
        )== inferencingOutput
    );
}
TEST_CASE("string - without binary with decorator") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::uint32_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                            NS::TestHelpers::make_vector<InputType>("oraNge apple oranGE grape"),
                            NS::TestHelpers::make_vector<InputType>("grApe caRrOt carrot apple"),
                            NS::TestHelpers::make_vector<InputType>("peach Banana orange banana")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("banana grape grape apple apple apple orange");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(3,0));
    values.emplace_back(TransformedType::ValueEncoding(1,1));
    values.emplace_back(TransformedType::ValueEncoding(2,3));
    values.emplace_back(TransformedType::ValueEncoding(1,4));
    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
                                                                           TransformedType(6
                                                                           , std::move(values))
                                                                          );


    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::CountVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0, true, AnalyzerMethod::Word, "",
                                                                                                                              1.0, 0, nonstd::optional<std::uint32_t>(), nonstd::optional<IndexMapType>(), 1, 1, false),
            trainingBatches,
            inferencingInput
        )== inferencingOutput
    );
}

TEST_CASE("string - with binary without decorator") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::uint32_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                            NS::TestHelpers::make_vector<InputType>("orange apple orange grape"),
                            NS::TestHelpers::make_vector<InputType>("grape carrot carrot apple"),
                            NS::TestHelpers::make_vector<InputType>("peach banana orange banana")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("banana grape grape apple apple apple orange");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(1,0));
    values.emplace_back(TransformedType::ValueEncoding(1,1));
    values.emplace_back(TransformedType::ValueEncoding(1,3));
    values.emplace_back(TransformedType::ValueEncoding(1,4));
    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
                                                                           TransformedType(6
                                                                           , std::move(values))
                                                                          );


    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::CountVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0, false, AnalyzerMethod::Word, "",
                                                                                                                              1.0, 0, nonstd::optional<std::uint32_t>(), nonstd::optional<IndexMapType>(), 1, 1, true),
            trainingBatches,
            inferencingInput
        )== inferencingOutput
    );
}


TEST_CASE("string - with binary with decorator") {
    using InputType       = std::string;
    using TransformedType = NS::Featurizers::SparseVectorEncoding<std::uint32_t>;

    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputType>>(
                            NS::TestHelpers::make_vector<InputType>("oraNge apple oranGE grape"),
                            NS::TestHelpers::make_vector<InputType>("grApe caRrOt carrot apple"),
                            NS::TestHelpers::make_vector<InputType>("peach Banana orange banana")
                            );

    auto inferencingInput =  NS::TestHelpers::make_vector<InputType>("banana grape grape apple apple apple orange");

    std::vector<TransformedType::ValueEncoding> values;
    values.emplace_back(TransformedType::ValueEncoding(1,0));
    values.emplace_back(TransformedType::ValueEncoding(1,1));
    values.emplace_back(TransformedType::ValueEncoding(1,3));
    values.emplace_back(TransformedType::ValueEncoding(1,4));
    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
                                                                           TransformedType(6
                                                                           , std::move(values))
                                                                          );


    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::CountVectorizerEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0, true, AnalyzerMethod::Word, "",
                                                                                                                              1.0, 0, nonstd::optional<std::uint32_t>(), nonstd::optional<IndexMapType>(), 1, 1, true),
            trainingBatches,
            inferencingInput
        )== inferencingOutput
    );
}

TEST_CASE("Serialization/Deserialization") {
    using TransformerType = NS::Featurizers::CountVectorizerTransformer;

    IndexMapType indexMap(
        {
            {"apple", 1},
            {"banana", 2},
            {"grape", 3},
            {"orange", 4},
            {"peach", 5}
        }
    );

    TransformerType                         original(indexMap, false, false, AnalyzerMethod::Word, "", 1, 1);
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
        NS::Featurizers::CountVectorizerTransformer(in),
        Catch::Contains("Unsupported archive version")
    );
}
