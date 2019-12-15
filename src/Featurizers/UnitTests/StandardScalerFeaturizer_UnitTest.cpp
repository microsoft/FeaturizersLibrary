// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Featurizers/StandardScalerFeaturizer.h"
#include "../TestHelpers.h"
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

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(2));

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        static_cast<TransformedType>(-1.06066017)
    );

    NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(NS::TestHelpers::FuzzyCheck(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::StandardScalerEstimator<InputType>(pAllColumnAnnotations, 0, true, true),
            trainingBatches,
            inferencingInput
        ), inferencingOutput
    ));
}

// // test for float_t
// TEST_CASE("float_t") {
//     using InputType       = std::float_t;
//     using TransformedType = std::double_t;

//     auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(10.3)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(20.1)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(8.4)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(8.2)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(10.3)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(30.1)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(30.4)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(15.8)));

//     auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(15.7));

//     auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
//         static_cast<TransformedType>(-0.11521303)
//     );

//     NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
//     NS::Featurizers::StandardScalarEstimator<InputType>   estimator(pAllColumnAnnotations);
//     CHECK(NS::TestHelpers::FuzzyCheck(
//         NS::TestHelpers::TransformerEstimatorTest(
//             estimator,
//             trainingBatches,
//             inferencingInput
//         ), inferencingOutput
//     ));
// }

// // test for with_mean, with_std
// TEST_CASE("without_mean_std") {
//     using InputType       = std::float_t;
//     using TransformedType = std::double_t;

//     auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(10.3)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(20.1)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(8.4)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(8.2)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(10.3)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(30.1)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(30.4)),
//                                     NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(15.8)));

//     auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(static_cast<InputType>(15.7));

//     auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
//         static_cast<TransformedType>(15.7)
//     );

//     NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
//     NS::Featurizers::StandardScalarEstimator<InputType>   estimator(pAllColumnAnnotations, false, false);
//     CHECK(NS::TestHelpers::FuzzyCheck(
//         NS::TestHelpers::TransformerEstimatorTest(
//             estimator,
//             trainingBatches,
//             inferencingInput
//         ), inferencingOutput
//     ));
// }
// TEST_CASE("Serialization/Deserialization") {
//     using InputType       = std::float_t;
//     using TransformerType = NS::Featurizers::SScalingEstimator<InputType>::Transformer;
//     auto model = std::make_shared<TransformerType>(static_cast<std::double_t>(-3.7), static_cast<std::double_t>(6.8), true, false);

//     NS::Archive archive;
//     model->save(archive);
//     std::vector<unsigned char> vec = archive.commit();
//     CHECK(vec.size() == 18);

//     NS::Archive loader(vec);
//     TransformerType modelLoaded(loader);
//     CHECK(modelLoaded==*model);
// }
