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
void EstimatorTest(InputT const &trainingMatrix,
                   TransformedT const &eigenValuesLabel,
                   TransformedT const &eigenVectorsLabel,
                   std::float_t eps = 0.000001f) {

    using PCAComponentsEstimator                       = NS::Featurizers::PCAComponentsEstimator<InputT, TransformedT>;
    using PCAComponentsAnnotationData                  = NS::Featurizers::PCAComponentsAnnotationData<TransformedT>;

    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    PCAComponentsEstimator                             estimator(pAllColumnAnnotations, 0);

    estimator.begin_training();
    estimator.fit(trainingMatrix);
    estimator.complete_training();

    PCAComponentsAnnotationData const &                mdAnnotation(estimator.get_annotation_data());

    TransformedT const &                               eigenValuesMat(mdAnnotation.Eigenvalues);
    TransformedT const &                               eigenVectorsMat(mdAnnotation.Eigenvectors);

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#elif (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127)
#endif

    CHECK((eigenValuesMat - eigenValuesLabel).norm() < eps);
    CHECK((eigenVectorsMat - eigenVectorsLabel).norm() < eps);


#if (defined __clang__)
#   pragma clang diagnostic pop
#elif (defined _MSC_VER)
#   pragma warning(pop)
#endif

}

template<typename InputT, typename TransformedT>
void TestWrapperPCA(){

    InputT trainingMatrix(6, 2);
    trainingMatrix(0, 0) = -1;
    trainingMatrix(0, 1) = -1;
    trainingMatrix(1, 0) = -2;
    trainingMatrix(1, 1) = -1;
    trainingMatrix(2, 0) = -3;
    trainingMatrix(2, 1) = -2;
    trainingMatrix(3, 0) = 1;
    trainingMatrix(3, 1) = 1;
    trainingMatrix(4, 0) = 2;
    trainingMatrix(4, 1) = 1;
    trainingMatrix(5, 0) = 3;
    trainingMatrix(5, 1) = 2;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#elif (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127)
#endif

    TransformedT eigenValuesLabel(2, 1);
    eigenValuesLabel(0, 0) = 0.302284f;
    eigenValuesLabel(1, 0) = 39.697716f;

    TransformedT eigenVectorsLabel(2, 2);
    eigenVectorsLabel(0, 0) = -0.544914f;
    eigenVectorsLabel(0, 1) = 0.838492f;
    eigenVectorsLabel(1, 0) = 0.838492f;
    eigenVectorsLabel(1, 1) =  0.544914f;

#if (defined __clang__)
#   pragma clang diagnostic pop
#elif (defined _MSC_VER)
#   pragma warning(pop)
#endif

    EstimatorTest<InputT, TransformedT>(trainingMatrix, eigenValuesLabel, eigenVectorsLabel);
}

TEST_CASE("Invalid_Annotation") {
    // using dataT = std::float_t;
    // std::vector<dataT> validEigenValues = NS::TestHelpers::make_vector<dataT>(0.0f);
    // std::vector<std::vector<dataT>> validEigenVectors = NS::TestHelpers::make_vector<std::vector<dataT>>(NS::TestHelpers::make_vector<dataT>(0.0f));
    // std::vector<dataT> invalidEigenValues = NS::TestHelpers::make_vector<dataT>();
    // std::vector<std::vector<dataT>> invalidEigenVectors1 = NS::TestHelpers::make_vector<std::vector<dataT>>();
    // std::vector<std::vector<dataT>> invalidEigenVectors2 = NS::TestHelpers::make_vector<std::vector<dataT>>(NS::TestHelpers::make_vector<dataT>());
    // CHECK_THROWS_WITH(NS::Featurizers::PCAComponentsAnnotationData<std::vector<dataT>>(invalidEigenValues, validEigenVectors), "eigenvalues");
    // CHECK_THROWS_WITH(NS::Featurizers::PCAComponentsAnnotationData<std::vector<dataT>>(validEigenValues, invalidEigenVectors1), "eigenvectors");
    // CHECK_THROWS_WITH(NS::Featurizers::PCAComponentsAnnotationData<std::vector<dataT>>(validEigenValues, invalidEigenVectors2), "eigenvector");
}

TEST_CASE("Invalid_TrainingPolicy") {
    //using InputT = std::float_t;
    //using TransformedT = std::float_t;
    //CHECK_THROWS_WITH(NS::Featurizers::ComponentsDetails::PCATrainingOnlyPolicy<InputT, TransformedT>(0), "numRows");
    //error: too many arguments provided to function-like macro invocation
}

TEST_CASE("Eigen_Estimator_Itegration") {
    TestWrapperPCA<Eigen::MatrixX<float>, Eigen::MatrixX<float>>();
    //TestWrapperPCA<Eigen::MatrixX<float>, Eigen::MatrixX<double>>();
    TestWrapperPCA<Eigen::MatrixX<double>, Eigen::MatrixX<double>>();
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
