// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../Featurizers/PCAFeaturizer.h"
#include "../TestHelpers.h"
#include "../../Archive.h"

namespace NS = Microsoft::Featurizer;

template<typename InputT, typename TransformedT>
void EstimatorTest(std::vector<std::vector<InputT>> const &inputBatches,
                    std::vector<TransformedT> const &eigenValuesLabel,
                    std::vector<std::vector<TransformedT>> const &eigenVectorsLabel) {

    using PCAComponentsEstimator                       = NS::Featurizers::PCAComponentsEstimator<InputT, TransformedT>;
    using PCAComponentsAnnotationData                  = NS::Featurizers::PCAComponentsAnnotationData<TransformedT>;

    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    PCAComponentsEstimator                             estimator(pAllColumnAnnotations, 0, inputBatches.size());

    NS::TestHelpers::Train(estimator, inputBatches);

    PCAComponentsAnnotationData const &                mdAnnotation(estimator.get_annotation_data());

    std::vector<TransformedT> const &                  eigenValuesMat(mdAnnotation.Eigenvalues);
    std::vector<std::vector<TransformedT>> const &     eigenVectorsMat(mdAnnotation.Eigenvectors);

    CHECK(NS::TestHelpers::FuzzyCheck(eigenValuesMat, eigenValuesLabel));
    for (size_t rowNum = 0; rowNum < eigenVectorsLabel.size(); ++rowNum)
        CHECK(NS::TestHelpers::FuzzyCheck(eigenVectorsMat[rowNum], eigenVectorsLabel[rowNum]));

    // commented and remain for future checking
    // std::cout << "U: " << NS::Traits<std::vector<std::vector<dataT>>>::ToString(uMat) << std::endl;
    // std::cout << "V: " << NS::Traits<std::vector<std::vector<dataT>>>::ToString(vMat) << std::endl;
    // std::cout << "S: " << NS::Traits<std::vector<dataT>>::ToString(sMat) << std::endl;
}

template<typename InputT, typename TransformedT>
void TestWrapperPCA(){
    std::vector<std::vector<InputT>> trainingBatches = NS::TestHelpers::make_vector<std::vector<InputT>>(
        NS::TestHelpers::make_vector<InputT>(-1.0f, -1.0f),
        NS::TestHelpers::make_vector<InputT>(-2.0f, -1.0f),
        NS::TestHelpers::make_vector<InputT>(-3.0f, -2.0f),
        NS::TestHelpers::make_vector<InputT>( 1.0f,  1.0f),
        NS::TestHelpers::make_vector<InputT>( 2.0f,  1.0f),
        NS::TestHelpers::make_vector<InputT>( 3.0f,  2.0f)
    );
    std::vector<TransformedT> eigenValuesLabel = NS::TestHelpers::make_vector<TransformedT>( 0.302284f, 39.697716f);
    std::vector<std::vector<TransformedT>> eigenVectorsLabel = NS::TestHelpers::make_vector<std::vector<TransformedT>>(
        NS::TestHelpers::make_vector<TransformedT>(-0.544914f, 0.838492f),
        NS::TestHelpers::make_vector<TransformedT>( 0.838492f, 0.544914f)
    );
    EstimatorTest<InputT, TransformedT>(trainingBatches, eigenValuesLabel, eigenVectorsLabel);
}

TEST_CASE("Invalid_Annotation") {
    using dataT = std::float_t;
    std::vector<dataT> validEigenValues = NS::TestHelpers::make_vector<dataT>(0.0f);
    std::vector<std::vector<dataT>> validEigenVectors = NS::TestHelpers::make_vector<std::vector<dataT>>(NS::TestHelpers::make_vector<dataT>(0.0f));
    std::vector<dataT> invalidEigenValues = NS::TestHelpers::make_vector<dataT>();
    std::vector<std::vector<dataT>> invalidEigenVectors1 = NS::TestHelpers::make_vector<std::vector<dataT>>();
    std::vector<std::vector<dataT>> invalidEigenVectors2 = NS::TestHelpers::make_vector<std::vector<dataT>>(NS::TestHelpers::make_vector<dataT>());
    CHECK_THROWS_WITH(NS::Featurizers::PCAComponentsAnnotationData<dataT>(invalidEigenValues, validEigenVectors), "eigenvalues");
    CHECK_THROWS_WITH(NS::Featurizers::PCAComponentsAnnotationData<dataT>(validEigenValues, invalidEigenVectors1), "eigenvectors");
    CHECK_THROWS_WITH(NS::Featurizers::PCAComponentsAnnotationData<dataT>(validEigenValues, invalidEigenVectors2), "eigenvector");
}

TEST_CASE("Invalid_TrainingPolicy") {
    //using InputT = std::float_t;
    //using TransformedT = std::float_t;
    //CHECK_THROWS_WITH(NS::Featurizers::ComponentsDetails::PCATrainingOnlyPolicy<InputT, TransformedT>(0), "numRows");
    //error: too many arguments provided to function-like macro invocation
}

TEST_CASE("Eigen_Estimator_Itegration") {
    TestWrapperPCA<std::float_t, std::float_t>();
    TestWrapperPCA<std::float_t, std::double_t>();
    TestWrapperPCA<std::double_t, std::double_t>();
}

// TEST_CASE("PCA_Transformer") {
//     using InputT = std::vector<std::float_t>;
//     using TransformedT = std::vector<std::float_t>;
//     std::vector<InputT> trainingBatches = NS::TestHelpers::make_vector<InputT>(
//         NS::TestHelpers::make_vector<typename InputT::value_type>(-1.0f, -1.0f),
//         NS::TestHelpers::make_vector<typename InputT::value_type>(-2.0f, -1.0f),
//         NS::TestHelpers::make_vector<typename InputT::value_type>(-3.0f, -2.0f),
//         NS::TestHelpers::make_vector<typename InputT::value_type>( 1.0f,  1.0f),
//         NS::TestHelpers::make_vector<typename InputT::value_type>( 2.0f,  1.0f),
//         NS::TestHelpers::make_vector<typename InputT::value_type>( 3.0f,  2.0f)
//     );
//     std::vector<InputT> input = NS::TestHelpers::make_vector<InputT>(
//         NS::TestHelpers::make_vector<typename InputT::value_type>(-1.0f, -1.0f),
//         NS::TestHelpers::make_vector<typename InputT::value_type>(-2.0f, -1.0f),
//         NS::TestHelpers::make_vector<typename InputT::value_type>(-3.0f, -2.0f),
//         NS::TestHelpers::make_vector<typename InputT::value_type>( 1.0f,  1.0f),
//         NS::TestHelpers::make_vector<typename InputT::value_type>( 2.0f,  1.0f),
//         NS::TestHelpers::make_vector<typename InputT::value_type>( 3.0f,  2.0f)
//     );
//     std::vector<TransformedT> label = NS::TestHelpers::make_vector<TransformedT>(
//         NS::TestHelpers::make_vector<typename TransformedT::value_type>(-1.0f, -1.0f),
//         NS::TestHelpers::make_vector<typename TransformedT::value_type>(-2.0f, -1.0f),
//         NS::TestHelpers::make_vector<typename TransformedT::value_type>(-3.0f, -2.0f),
//         NS::TestHelpers::make_vector<typename TransformedT::value_type>( 1.0f,  1.0f),
//         NS::TestHelpers::make_vector<typename TransformedT::value_type>( 2.0f,  1.0f),
//         NS::TestHelpers::make_vector<typename TransformedT::value_type>( 3.0f,  2.0f)
//     );
//     CHECK(
//         NS::TestHelpers::TransformerEstimatorTest(
//             NS::Featurizers::PCAEstimator<InputT, TransformedT>(NS::CreateTestAnnotationMapsPtr(1), 0, trainingBatches.size()),
//             trainingBatches,
//             input
//         ) == label
//     );
// }



// TEST_CASE("Serialization/Deserialization") {
//     using InputType       = std::float_t;
//     using TransformedType = std::double_t;
//     using TransformerType = NS::Featurizers::MinMaxScalarTransformer<InputType, TransformedType>;

//     auto model = std::make_shared<TransformerType>(static_cast<InputType>(-5), static_cast<InputType>(9));

//     NS::Archive archive;
//     model->save(archive);
//     std::vector<unsigned char> vec = archive.commit();
    
//     NS::Archive loader(vec);
//     TransformerType modelLoaded(loader);
//     CHECK(modelLoaded == *model);
// }

// TEST_CASE("Serialization Version Error") {
//     NS::Archive                             out;

//     out.serialize(static_cast<std::uint16_t>(2));
//     out.serialize(static_cast<std::uint16_t>(0));

//     NS::Archive                             in(out.commit());

//     CHECK_THROWS_WITH(
//         (NS::Featurizers::MinMaxScalarTransformer<std::uint8_t, std::double_t>(in)),
//         Catch::Contains("Unsupported archive version")
//     );
// }
