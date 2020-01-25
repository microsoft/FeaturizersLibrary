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

template <typename MatrixT>
void PCATransformerTest() {
    std::float_t eps = 0.0001f;

    MatrixT trainingMatrix(6, 2);
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

    MatrixT input = trainingMatrix;

    #if (defined __clang__)
    #   pragma clang diagnostic push
    #   pragma clang diagnostic ignored "-Wdouble-promotion"
    #endif

    MatrixT label(6, 2);
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
    #endif

    using PCAEstimator                                 = NS::Featurizers::PCAEstimator<MatrixT>;
    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    std::vector<std::vector<MatrixT>> trainingBatches  = NS::TestHelpers::make_vector<std::vector<MatrixT>>(
        NS::TestHelpers::make_vector<MatrixT>(trainingMatrix)
    );

    std::vector<MatrixT> inputContainers = NS::TestHelpers::make_vector<MatrixT>(input);
    std::vector<MatrixT> outputContainer = NS::TestHelpers::TransformerEstimatorTest(PCAEstimator(pAllColumnAnnotations, 0), trainingBatches, inputContainers);

    MatrixT output = outputContainer[0];

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

    CHECK((output.cwiseProduct(output) - label.cwiseProduct(label)).norm() < eps);

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
}

TEST_CASE("Invalid_Annotation") {
    using MatrixT = Eigen::MatrixX<float>;
    MatrixT invalidEigenVectors;
    MatrixT validEigenVectors(2, 2);
    CHECK_THROWS_WITH(NS::Featurizers::PCATransformer<MatrixT>(invalidEigenVectors), "eigenvectors");
}

TEST_CASE("Invalid_fit") {
    using MatrixT = Eigen::MatrixX<float>;

    MatrixT trainingMatrix(3, 3);
    trainingMatrix(0, 0) = -1;
    trainingMatrix(0, 1) = -1;
    trainingMatrix(0, 2) =  0;
    trainingMatrix(1, 0) =  0;
    trainingMatrix(1, 1) = -2;
    trainingMatrix(1, 2) = -1;
    trainingMatrix(2, 0) = -3;
    trainingMatrix(2, 1) =  0;
    trainingMatrix(2, 2) = -2;

    using PCAEstimator                                 = NS::Featurizers::PCAEstimator<MatrixT>;
    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    PCAEstimator                                       estimator(pAllColumnAnnotations, 0);

    estimator.begin_training();
    estimator.fit(trainingMatrix);

    CHECK_THROWS_WITH(estimator.fit(trainingMatrix), "fit_impl() should not be called move than once in PCAFeaturizer");
}

TEST_CASE("PCATransformerTest") {
    PCATransformerTest<Eigen::MatrixX<float>>();
    PCATransformerTest<Eigen::MatrixX<double>>();
}

TEST_CASE("Serialization/Deserialization") {
    using MatrixT = Eigen::MatrixX<float>;
    using TransformerType = NS::Featurizers::PCATransformer<MatrixT>;

    MatrixT eigenValues(3, 1);
    eigenValues(0, 0) = 3.79535f;
    eigenValues(1, 0) = 2.21387f;
    eigenValues(2, 0) = 0.83309f;

    MatrixT eigenVectors(3, 3);
    eigenVectors(0, 0) =  0.805059f;
    eigenVectors(0, 1) = -0.315908f;
    eigenVectors(0, 2) = -0.502078f;
    eigenVectors(1, 0) =  0.204052f;
    eigenVectors(1, 1) =  0.942225f;
    eigenVectors(1, 2) = -0.265660f;
    eigenVectors(2, 0) =  0.556994f;
    eigenVectors(2, 1) =  0.111422f;
    eigenVectors(2, 2) =  0.823008f;

    TransformerType                         original(eigenVectors);

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
        (NS::Featurizers::PCATransformer<Eigen::MatrixX<float>>(in)),
        Catch::Contains("Unsupported archive version")
    );
}

TEST_CASE("access to shape information") {
    using MatrixT = Eigen::MatrixX<float>;
    MatrixT eigenVector(6, 2);
    eigenVector(0, 0) = -1;
    eigenVector(0, 1) = -1;
    eigenVector(1, 0) = -2;
    eigenVector(1, 1) = -1;
    eigenVector(2, 0) = -3;
    eigenVector(2, 1) = -2;
    eigenVector(3, 0) = 1;
    eigenVector(3, 1) = 1;
    eigenVector(4, 0) = 2;
    eigenVector(4, 1) = 1;
    eigenVector(5, 0) = 3;
    eigenVector(5, 1) = 2;

    Microsoft::Featurizer::Featurizers::PCATransformer<MatrixT>    pcaTransformer(eigenVector);

    CHECK(pcaTransformer.getEigenVectorRowsNumber() == 6);
    CHECK(pcaTransformer.getEigenVectorColsNumber() == 2);
}

