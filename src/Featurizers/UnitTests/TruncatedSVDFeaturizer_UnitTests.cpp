// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../Featurizers/TruncatedSVDFeaturizer.h"
#include "../TestHelpers.h"
#include "../../Archive.h"

namespace NS = Microsoft::Featurizer;

template<typename InputT, typename TransformedT>
void EstimatorTest(InputT const &trainingMatrix,
                   TransformedT const &singularValuesLabel,
                   TransformedT const &singularVectorsLabel,
                   std::float_t eps = 0.0001f) {

    using SVDComponentsEstimator                       = NS::Featurizers::SVDComponentsEstimator<InputT, TransformedT>;
    using SVDComponentsAnnotationData                  = NS::Featurizers::SVDComponentsAnnotationData<TransformedT>;

    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    SVDComponentsEstimator                             estimator(pAllColumnAnnotations, 0);

    estimator.begin_training();
    estimator.fit(trainingMatrix);
    estimator.complete_training();

    SVDComponentsAnnotationData const &                mdAnnotation(estimator.get_annotation_data());

    TransformedT const &                               singularValuesMat(mdAnnotation.SingularValues);
    TransformedT const &                               singularVectorsMat(mdAnnotation.SingularVectors);

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

    CHECK((singularValuesMat.cwiseProduct(singularValuesMat) - singularValuesLabel.cwiseProduct(singularValuesLabel)).norm() < eps);
    CHECK((singularVectorsMat.cwiseProduct(singularVectorsMat) - singularVectorsLabel.cwiseProduct(singularVectorsLabel)).norm() < eps);

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

}

template<typename InputT, typename TransformedT>
void TestWrapperSVD(){

    InputT trainingMatrix(3, 3);
    trainingMatrix(0, 0) = -1;
    trainingMatrix(0, 1) = -1;
    trainingMatrix(0, 2) =  0;
    trainingMatrix(1, 0) =  0;
    trainingMatrix(1, 1) = -2;
    trainingMatrix(1, 2) = -1;
    trainingMatrix(2, 0) = -3;
    trainingMatrix(2, 1) =  0;
    trainingMatrix(2, 2) = -2;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

    TransformedT singularValuesLabel(3, 1);
    singularValuesLabel(0, 0) = 3.79535f;
    singularValuesLabel(1, 0) = 2.21387f;
    singularValuesLabel(2, 0) = 0.83309f;

    TransformedT singularVectorsLabel(3, 3);
    singularVectorsLabel(0, 0) =  0.805059f;
    singularVectorsLabel(0, 1) = -0.315908f;
    singularVectorsLabel(0, 2) = -0.502078f;
    singularVectorsLabel(1, 0) =  0.204052f;
    singularVectorsLabel(1, 1) =  0.942225f;
    singularVectorsLabel(1, 2) = -0.265660f;
    singularVectorsLabel(2, 0) =  0.556994f;
    singularVectorsLabel(2, 1) =  0.111422f;
    singularVectorsLabel(2, 2) =  0.823008f;

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

    EstimatorTest<InputT, TransformedT>(trainingMatrix, singularValuesLabel, singularVectorsLabel);
}

TEST_CASE("Invalid_Annotation") {
    using dataT = Eigen::MatrixX<float>;
    dataT invalidSingularValues;
    dataT invalidSingularVectors;
    dataT validSingularValues(2, 2);
    dataT validSingularVectors(2, 2);
    CHECK_THROWS_WITH(NS::Featurizers::SVDComponentsAnnotationData<dataT>(invalidSingularValues, validSingularVectors), "singularvalues");
    CHECK_THROWS_WITH(NS::Featurizers::SVDComponentsAnnotationData<dataT>(validSingularValues, invalidSingularVectors), "singularvectors");
}

//TODO: error: too many arguments provided to function-like macro invocation
TEST_CASE("Invalid_TrainingPolicy") {
    //using InputT = Eigen::MatrixX<float>;
    //using TransformedT = Eigen::MatrixX<float>;
    //CHECK_THROWS_WITH(NS::Featurizers::ComponentsDetails::SVDTrainingOnlyPolicy<InputT, TransformedT>(0), "numRows");
}

TEST_CASE("Singular_Estimator_Itegration") {
    TestWrapperSVD<Eigen::MatrixX<float>, Eigen::MatrixX<float>>();
    TestWrapperSVD<Eigen::MatrixX<double>, Eigen::MatrixX<double>>();
}

TEST_CASE("SVD_Transformer") {
    using InputT = Eigen::MatrixX<float>;
    using TransformedT = Eigen::MatrixX<float>;
    std::float_t eps = 0.0001f;

    InputT trainingMatrix(3, 3);
    trainingMatrix(0, 0) = -1;
    trainingMatrix(0, 1) = -1;
    trainingMatrix(0, 2) =  0;
    trainingMatrix(1, 0) =  0;
    trainingMatrix(1, 1) = -2;
    trainingMatrix(1, 2) = -1;
    trainingMatrix(2, 0) = -3;
    trainingMatrix(2, 1) =  0;
    trainingMatrix(2, 2) = -2;

    InputT input = trainingMatrix;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

    TransformedT label(3, 3);
    label(0, 0) = -1.009107f;
    label(0, 1) =  0.626315f;
    label(0, 2) = -0.767745f;
    label(1, 0) = -0.965105f;
    label(1, 1) =  1.995869f;
    label(1, 2) =  0.291682f;
    label(2, 0) = -3.529165f;
    label(2, 1) = -0.724887f;
    label(2, 2) =  0.139759f;

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

    using SVDEstimator                                 = NS::Featurizers::SVDEstimator<InputT, TransformedT>;
    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    SVDEstimator                                       estimator(pAllColumnAnnotations, 0);

    estimator.begin_training();
    estimator.fit(trainingMatrix);
    estimator.complete_training();

    typename SVDEstimator::TransformerUniquePtr        pTransformer(estimator.create_transformer());

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
#endif

    CHECK((output.cwiseProduct(output) - label.cwiseProduct(label)).norm() < eps);
   
#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
}

TEST_CASE("Serialization/Deserialization") {
    using InputT = Eigen::MatrixX<float>;
    using TransformedT = Eigen::MatrixX<float>;
    using TransformerType = NS::Featurizers::SVDTransformer<InputT, TransformedT>;

    TransformedT singularValues(3, 1);
    singularValues(0, 0) = 3.79535f;
    singularValues(1, 0) = 2.21387f;
    singularValues(2, 0) = 0.83309f;

    TransformedT singularVectors(3, 3);
    singularVectors(0, 0) =  0.805059f;
    singularVectors(0, 1) = -0.315908f;
    singularVectors(0, 2) = -0.502078f;
    singularVectors(1, 0) =  0.204052f;
    singularVectors(1, 1) =  0.942225f;
    singularVectors(1, 2) = -0.265660f;
    singularVectors(2, 0) =  0.556994f;
    singularVectors(2, 1) =  0.111422f;
    singularVectors(2, 2) =  0.823008f;
    
    TransformerType                         original(singularValues, singularVectors);

    NS::Archive                             out;

    original.save(out);

    NS::Archive                             in(out.commit());
    TransformerType                         other(in);

    //CHECK(other == original);
}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        (NS::Featurizers::SVDTransformer<Eigen::MatrixX<float>, Eigen::MatrixX<float>>(in)),
        Catch::Contains("Unsupported archive version")
    );
}

