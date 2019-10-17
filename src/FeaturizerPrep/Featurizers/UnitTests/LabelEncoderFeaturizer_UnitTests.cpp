// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Featurizers/LabelEncoderFeaturizer.h"
#include "../TestHelpers.h"
#include "../../Traits.h"

namespace NS = Microsoft::Featurizer;

template <typename KeyT, typename IndexT>
using IndexMap = std::map<KeyT, IndexT>;



// test for unsigned int
TEST_CASE("uint32_t") {
    using InputType       = std::uint32_t;
    using TransformedType = std::uint32_t;

    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(10, 20, 10),
                                    NS::TestHelpers::make_vector<InputType>(30),
                                    NS::TestHelpers::make_vector<InputType>(10, 10, 11, 15),
                                    NS::TestHelpers::make_vector<InputType>(18,  8));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(11, 8, 10, 15, 20);

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        3,
        1,
        2,
        4,
        6
    );

    NS::AnnotationMapsPtr const                         pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::LabelEncoderEstimator<InputType>   estimator(pAllColumnAnnotations);
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            estimator,
            trainingBatches,
            inferencingInput
        )== inferencingOutput
    );
}

// test for string
TEST_CASE("string") {
    using InputType       = std::string;
    using TransformedType = std::uint32_t;

    NS::AnnotationMapsPtr const                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::LabelEncoderEstimator<InputType>    estimator(pAllColumnAnnotations,true);
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            estimator,
            NS::TestHelpers::make_vector<std::vector<std::string>>(
                NS::TestHelpers::make_vector<std::string>("orange", "apple",  "orange",
                                                          "grape",  "carrot", "carrot",
                                                          "peach",  "banana", "orange")
            ),
            NS::TestHelpers::make_vector<std::string>("banana", "grape", "apple")
        )== NS::TestHelpers::make_vector<TransformedType>(2, 4, 1)
    );
}

TEST_CASE("not found value, non-throw mode") {
    using InputType       = std::string;
    using TransformedType = std::uint32_t;

    // when an inference data is not seen before, in the non-throw mode, the featurizer should generate 0
    NS::AnnotationMapsPtr const                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::LabelEncoderEstimator<InputType>    estimator(pAllColumnAnnotations,true);
    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            estimator,
            NS::TestHelpers::make_vector<std::vector<std::string>>(
                NS::TestHelpers::make_vector<std::string>("orange", "apple",  "orange",
                                                          "grape",  "carrot", "carrot",
                                                          "peach",  "banana", "orange")
            ),
            std::vector<std::string>({"banana", "grape", "apple","hello"})
        )== NS::TestHelpers::make_vector<TransformedType>(2, 4, 1, 0)
    );
}

TEST_CASE("not found value, throw mode") {
    using InputType       = std::string;
    using TransformedType = std::uint32_t;

    // when an inference data is not seen before, in the throw mode, the featurizer should generate a run time error
    NS::AnnotationMapsPtr const                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::LabelEncoderEstimator<InputType>    estimator(pAllColumnAnnotations,false);
    CHECK_THROWS_WITH(
        NS::TestHelpers::TransformerEstimatorTest(
            estimator,
            NS::TestHelpers::make_vector<std::vector<std::string>>(
                NS::TestHelpers::make_vector<std::string>("orange", "apple",  "orange",
                                                          "grape",  "carrot", "carrot",
                                                          "peach",  "banana", "orange")
            ),
            std::vector<std::string>({"banana", "grape", "apple","hello"})
        )== NS::TestHelpers::make_vector<TransformedType>(2, 4, 1, 0), "Throwing an error is enabled when unseen inference data is taken! If you want different behaviours, change the input flag!"
    );
}

// null inference data is not yet supported
// To be deleted once functionality complete
TEST_CASE("null inference data") {
    using InputType       = nonstd::optional<std::string>;
    using TransformedType = std::uint32_t;

    NS::AnnotationMapsPtr const                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::LabelEncoderEstimator<InputType>    estimator(pAllColumnAnnotations, false);
    CHECK_THROWS_WITH(
        NS::TestHelpers::TransformerEstimatorTest(
            estimator,
            NS::TestHelpers::make_vector<std::vector<InputType>>(
                NS::TestHelpers::make_vector<InputType>("orange", "apple",  "orange",
                                                          "grape",  "carrot", "carrot",
                                                          "peach",  "banana", "orange")
            ),
            NS::TestHelpers::make_vector<InputType>("banana", "grape", "apple","orange", NS::Traits<InputType>::CreateNullValue())
        )== NS::TestHelpers::make_vector<TransformedType>(2, 4, 1, 0), "null inferencing data is not supported for label encoder yet!"
    );
}


TEST_CASE("Serialization/Deserialization- Numeric") {
    using InputType       = std::uint32_t;
    using TransformedType = std::uint32_t;
    using TransformerType = NS::Featurizers::CategorizeEstimator<InputType, TransformedType>::Transformer;
    IndexMap<InputType, TransformedType> indexmap({
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
    auto model = std::make_shared<TransformerType>(indexmap, true);

    NS::Archive archive;
    model->save(archive);
    std::vector<unsigned char> vec = archive.commit();
    CHECK(vec.size() == 77);

    NS::Archive loader(vec);
    TransformerType modelLoaded(loader);
    CHECK(modelLoaded==*model);
}

TEST_CASE("Serialization/Deserialization- string") {
    using InputType       = std::string;
    using TransformedType = std::uint32_t;
    using TransformerType = NS::Featurizers::CategorizeEstimator<InputType,TransformedType>::Transformer;
    
    IndexMap<InputType, TransformedType> indexmap({
                                    {"apple", 1},
                                    {"banana", 2},
                                    {"grape", 3},
                                    {"orange", 4},
                                    {"peach", 5}});
    auto model = std::make_shared<TransformerType>(indexmap, false);

    NS::Archive archive;
    model->save(archive);
    std::vector<unsigned char> vec = archive.commit();

    NS::Archive loader(vec);
    TransformerType modelLoaded(loader);
    CHECK(modelLoaded == *model);

}


