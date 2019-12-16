// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Featurizers/StandardScaleWrapperFeaturizer.h"
#include "../TestHelpers.h"
#include "../../Traits.h"

namespace NS = Microsoft::Featurizer;

// test for no valid input
TEST_CASE("no valid input") {
    // when no valid input is passed in
    // L2NormUpdater.commit() would throw an error becacuse no update() is called
    using InputType       = std::double_t;
    using TransformedType = std::double_t;

    InputType null = NS::Traits<InputType>::CreateNullValue();
    
    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(null),
                                    NS::TestHelpers::make_vector<InputType>(null),
                                    NS::TestHelpers::make_vector<InputType>(null),
                                    NS::TestHelpers::make_vector<InputType>(null),
                                    NS::TestHelpers::make_vector<InputType>(null));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(2);

    NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK_THROWS_WITH(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::StandardScaleWrapperEstimator<InputType, TransformedType>(pAllColumnAnnotations, 0, true, true),
            trainingBatches,
            inferencingInput
        ), "update is not called before l2 is committed!"
    );
}
// test for int
TEST_CASE("1 int") {
    using InputType       = int;
    using TransformedType = std::double_t;

    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(10));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(15);

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        static_cast<TransformedType>(5)
    );

    NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(NS::TestHelpers::FuzzyCheck(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::StandardScaleWrapperEstimator<InputType>(pAllColumnAnnotations, 0, true, true),
            trainingBatches,
            inferencingInput
        ), inferencingOutput
    ));
}
TEST_CASE("5 ints") {
    using InputType       = int;
    using TransformedType = std::double_t;

    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(1),
                                    NS::TestHelpers::make_vector<InputType>(3),
                                    NS::TestHelpers::make_vector<InputType>(5),
                                    NS::TestHelpers::make_vector<InputType>(7),
                                    NS::TestHelpers::make_vector<InputType>(9));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(2);

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        static_cast<TransformedType>(-1.06066017)
    );

    NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(NS::TestHelpers::FuzzyCheck(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::StandardScaleWrapperEstimator<InputType>(pAllColumnAnnotations, 0, true, true),
            trainingBatches,
            inferencingInput
        ), inferencingOutput
    ));
}

// test for float_t
TEST_CASE("8 random float_t") {
    using InputType       = std::float_t;
    using TransformedType = std::double_t;

    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(10.3)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(20.1)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(8.4)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(8.2)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(10.3)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(30.1)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(30.4)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(15.8)));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(15.7));

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        static_cast<TransformedType>(-0.11521303)
    );

    NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    CHECK(NS::TestHelpers::FuzzyCheck(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::StandardScaleWrapperEstimator<InputType>(pAllColumnAnnotations, 0, true, true),
            trainingBatches,
            inferencingInput
        ), inferencingOutput
    ));
}

// test for non valid inference input
TEST_CASE("non-valid inference input") {
    using InputType       = std::double_t;
    using TransformedType = std::double_t;

    InputType null = NS::Traits<TransformedType>::CreateNullValue();
    
    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(1),
                                    NS::TestHelpers::make_vector<InputType>(3),
                                    NS::TestHelpers::make_vector<InputType>(5));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(null);

    NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    // if inference input is null, inference output should also be null
    CHECK( NS::Traits<TransformedType>::IsNull(
            NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::StandardScaleWrapperEstimator<InputType, TransformedType>(pAllColumnAnnotations, 0, true, true),
            trainingBatches,
            inferencingInput
        )[0])
    );
}
// test for with_mean, with_std
TEST_CASE("without_mean_std") {
    using InputType       = std::float_t;
    using TransformedType = std::double_t;

    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(10.3)),
                                    NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(20.1)));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(15.7));

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        static_cast<TransformedType>(15.7)
    );

    NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    
    CHECK(NS::TestHelpers::FuzzyCheck(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::StandardScaleWrapperEstimator<InputType, TransformedType>(pAllColumnAnnotations, 0, false, false),
            trainingBatches,
            inferencingInput
        ), inferencingOutput
    ));
}
TEST_CASE("Serialization/Deserialization") {
    using InputType       = std::float_t;
    using TransformedType = std::double_t;
    using TransformerType = NS::Featurizers::StandardScalerTransformer<InputType, TransformedType>;

    auto model = std::make_shared<TransformerType>(static_cast<std::double_t>(-3.7), static_cast<std::double_t>(6.8));

    NS::Archive archive;
    model->save(archive);
    std::vector<unsigned char> vec = archive.commit();
    CHECK(vec.size() == 16);

    NS::Archive loader(vec);
    TransformerType modelLoaded(loader);
    CHECK(modelLoaded==*model);
}
