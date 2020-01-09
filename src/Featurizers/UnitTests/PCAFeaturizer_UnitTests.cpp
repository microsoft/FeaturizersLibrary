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
    eigenValuesLabel(0, 0) =  0.302284f;
    eigenValuesLabel(1, 0) = 39.697716f;

    TransformedT eigenVectorsLabel(2, 2);
    eigenVectorsLabel(0, 0) = -0.544914f;
    eigenVectorsLabel(0, 1) =  0.838492f;
    eigenVectorsLabel(1, 0) =  0.838492f;
    eigenVectorsLabel(1, 1) =  0.544914f;

#if (defined __clang__)
#   pragma clang diagnostic pop
#elif (defined _MSC_VER)
#   pragma warning(pop)
#endif

    EstimatorTest<InputT, TransformedT>(trainingMatrix, eigenValuesLabel, eigenVectorsLabel);
}

TEST_CASE("Invalid_Annotation") {
    using dataT = Eigen::MatrixX<float>;
    dataT invalidEigenValues;
    dataT invalidEigenVectors;
    dataT validEigenValues(2, 2);
    dataT validEigenVectors(2, 2);
    CHECK_THROWS_WITH(NS::Featurizers::PCAComponentsAnnotationData<dataT>(invalidEigenValues, validEigenVectors), "eigenvalues");
    CHECK_THROWS_WITH(NS::Featurizers::PCAComponentsAnnotationData<dataT>(validEigenValues, invalidEigenVectors), "eigenvectors");
}

//TODO: error: too many arguments provided to function-like macro invocation
TEST_CASE("Invalid_TrainingPolicy") {
    //using InputT = Eigen::MatrixX<float>;
    //using TransformedT = Eigen::MatrixX<float>;
    //CHECK_THROWS_WITH(NS::Featurizers::ComponentsDetails::PCATrainingOnlyPolicy<InputT, TransformedT>(0), "numRows");
}

TEST_CASE("Eigen_Estimator_Itegration") {
    TestWrapperPCA<Eigen::MatrixX<float>, Eigen::MatrixX<float>>();
    TestWrapperPCA<Eigen::MatrixX<double>, Eigen::MatrixX<double>>();
}

TEST_CASE("PCA_Transformer") {
    using InputT = Eigen::MatrixX<float>;
    using TransformedT = Eigen::MatrixX<float>;
    std::float_t eps = 0.000001f;

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

    InputT input = trainingMatrix;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#elif (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127)
#endif

    TransformedT label(6, 2);
    label(0, 0) = -0.2935787f;
    label(0, 1) = -1.3834058f;
    label(1, 0) =  0.2513348f;
    label(1, 1) = -2.2218980f;
    label(2, 0) = -0.0422439f;
    label(2, 1) = -3.6053038f;
    label(3, 0) =  0.2935787f;
    label(3, 1) =  1.3834058f;
    label(4, 0) = -0.2513348f;
    label(4, 1) =  2.2218980f;
    label(5, 0) =  0.0422439f;
    label(5, 1) =  3.6053038f;

#if (defined __clang__)
#   pragma clang diagnostic pop
#elif (defined _MSC_VER)
#   pragma warning(pop)
#endif

    using PCAEstimator                                 = NS::Featurizers::PCAEstimator<InputT, TransformedT>;
    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    PCAEstimator                                       estimator(pAllColumnAnnotations, 0);

    estimator.begin_training();
    estimator.fit(trainingMatrix);
    estimator.complete_training();

    typename PCAEstimator::TransformerUniquePtr        pTransformer(estimator.create_transformer());

    TransformedT                                       output;
    auto const                                         callback(
        [&output](TransformedT value) {
            output = std::move(value);
        }
    );

    pTransformer->execute(input, callback);
    pTransformer->flush(callback);

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#elif (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127)
#endif

    CHECK((output - label).norm() < eps);

#if (defined __clang__)
#   pragma clang diagnostic pop
#elif (defined _MSC_VER)
#   pragma warning(pop)
#endif
}

//TODO
TEST_CASE("Serialization/Deserialization") {

}

//TODO
TEST_CASE("Serialization Version Error") {
    
}
