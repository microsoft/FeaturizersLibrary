// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Featurizers/NumericalizeFeaturizer.h"
#include "../TestHelpers.h"
#include "../../Archive.h"
#include "../../Traits.h"

namespace NS = Microsoft::Featurizer;

template <typename KeyT, typename IndexT>
using IndexMap = std::unordered_map<KeyT, IndexT>;

// test for unsigned int
TEST_CASE("uint32_t") {
    using InputType       = std::uint32_t;
    using TransformedType = double;

    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(10, 20, 10),
                                    NS::TestHelpers::make_vector<InputType>(30),
                                    NS::TestHelpers::make_vector<InputType>(10, 10, 11, 15),
                                    NS::TestHelpers::make_vector<InputType>(18, 8));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(11, 8, 10, 15, 20);

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        2.,
        0.,
        1.,
        3.,
        5.
    );

    auto test_result = NS::TestHelpers::TransformerEstimatorTest(
        NS::Featurizers::NumericalizeEstimator<InputType>(NS::CreateTestAnnotationMapsPtr(1), 0),
        trainingBatches,
        inferencingInput);

    CHECK(test_result == inferencingOutput);
}

TEST_CASE("string") {
    using InputType       = std::string;
    using TransformedType = std::double_t;

    auto trainingBatches = NS::TestHelpers::make_vector<std::vector<std::string>>(
        NS::TestHelpers::make_vector<std::string>("orange", "apple", "orange",
        "grape", "carrot", "carrot",
        "peach", "banana", "orange"));

    auto inferencingInput = NS::TestHelpers::make_vector<std::string>("banana", "grape", "apple");

    auto expectedOutput = NS::TestHelpers::make_vector<TransformedType>(1., 3., 0.);

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::NumericalizeEstimator<InputType>(NS::CreateTestAnnotationMapsPtr(1), 0),
            trainingBatches,
            inferencingInput
        ) == expectedOutput
    );
}

// Fails to compare:
// with expansion :
//{ 1.0, 3.0, 0.0, nan }
//==
//    { 1.0, 3.0, 0.0, nan }
//TEST_CASE("not found value") {
//    using InputType       = std::string;
//    using TransformedType = std::double_t;
//
//    // when an inference data is not seen before, the featurizer should generate empty optional
//    auto trainingBatches = NS::TestHelpers::make_vector<std::vector<std::string>>(
//        NS::TestHelpers::make_vector<std::string>("orange", "apple", "orange",
//        "grape", "carrot", "carrot",
//        "peach", "banana", "orange")
//        );
//
//    auto inferencingInput = std::vector<std::string>({ "banana", "grape", "apple", "hello" });
//    auto expectedOutput = NS::TestHelpers::make_vector<TransformedType>(1., 3., 0., std::numeric_limits<double>::quiet_NaN());
//
//    CHECK(
//        NS::TestHelpers::TransformerEstimatorTest(
//            NS::Featurizers::NumericalizeEstimator<InputType>(NS::CreateTestAnnotationMapsPtr(1), 0),
//            trainingBatches,
//            inferencingInput
//        ) == expectedOutput
//    );
//}

TEST_CASE("Serialization/Deserialization- Numeric") {
    using InputType       = std::uint32_t;
    using TransformerType = NS::Featurizers::NumericalizeTransformer<InputType>;

    IndexMap<InputType, std::uint32_t>    indexmap(
        {
            {6, 1},
            {7, 2},
            {8, 3},
            {10, 4},
            {11, 5},
            {15, 6},
            {18, 7},
            {20, 8},
            {30, 9}
        }
    );

    TransformerType                         original(std::move(indexmap));
    NS::Archive                             out;

    original.save(out);

    NS::Archive                             in(out.commit());
    TransformerType                         other(in);

    CHECK(other == original);
}

TEST_CASE("Serialization/Deserialization- string") {
    using InputType       = std::string;
    using TransformerType = NS::Featurizers::NumericalizeTransformer<InputType>;

    IndexMap<InputType, std::uint32_t>    indexmap(
        {
            {"apple", 1},
            {"banana", 2},
            {"grape", 3},
            {"orange", 4},
            {"peach", 5}
        }
    );

    TransformerType                         original(std::move(indexmap));
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
        NS::Featurizers::NumericalizeTransformer<std::string>(in),
        Catch::Contains("Unsupported archive version")
    );
}
