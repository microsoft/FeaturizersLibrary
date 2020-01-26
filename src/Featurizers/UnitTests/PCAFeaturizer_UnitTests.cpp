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
void PCATransformerTestImpl(MatrixT const &trainingMatrix, MatrixT const &label) {
    std::float_t eps = 0.0001f;
    MatrixT input = trainingMatrix;

    using PCAEstimator                                 = NS::Featurizers::PCAEstimator<MatrixT>;
    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    std::vector<std::vector<MatrixT>> trainingBatches  = NS::TestHelpers::make_vector<std::vector<MatrixT>>(
        NS::TestHelpers::make_vector<MatrixT>(trainingMatrix)
    );

    std::vector<MatrixT> inputContainers = NS::TestHelpers::make_vector<MatrixT>(input);
    std::vector<Eigen::MatrixX<typename MatrixT::Scalar>> outputContainer = NS::TestHelpers::TransformerEstimatorTest(PCAEstimator(pAllColumnAnnotations, 0), trainingBatches, inputContainers);

    REQUIRE(outputContainer.size() == 1);

    Eigen::MatrixX<typename MatrixT::Scalar> const &    output(outputContainer[0]);

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

    CHECK((output.cwiseProduct(output) - label.cwiseProduct(label)).norm() < eps);

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
}

template <typename T>
void PCATransformerTestStandard(void) {
    // ----------------------------------------------------------------------
    using Matrix                            = Eigen::MatrixX<T>;
    // ----------------------------------------------------------------------

    Matrix                                  matrix(6, 2);

    // -1 -1
    // -2 -1
    // -3 -2
    //  1  1
    //  2  1
    //  3  2

    matrix(0, 0) = -1;
    matrix(0, 1) = -1;
    matrix(1, 0) = -2;
    matrix(1, 1) = -1;
    matrix(2, 0) = -3;
    matrix(2, 1) = -2;
    matrix(3, 0) = 1;
    matrix(3, 1) = 1;
    matrix(4, 0) = 2;
    matrix(4, 1) = 1;
    matrix(5, 0) = 3;
    matrix(5, 1) = 2;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

    Matrix                                  label(6, 2);

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

    PCATransformerTestImpl(matrix, label);
}

template <typename T>
void PCATransformerTestMap(void) {
    // ----------------------------------------------------------------------
    using Matrix                            = Eigen::Map<Eigen::MatrixX<T>>;
    // ----------------------------------------------------------------------

    // -1 -1
    // -2 -1
    // -3 -2
    //  1  1
    //  2  1
    //  3  2

    // Column major order
    T                                       data[]{
        -1, -2, -3, 1, 2, 3,
        -1, -1, -2, 1, 1, 2
    };

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

    T                                       labelData[]{
        -0.2935787f, 0.2513348f, -0.0422439f, 0.2935787f, -0.2513348f, 0.0422439f,
        -1.3834058f, -2.2218980f, -3.6053038f, 1.3834058f, 2.2218980f, 3.6053038f

    };

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

    Matrix                                  matrix(data, 6, 2);
    Matrix                                  labelMatrix(labelData, 6, 2);

    PCATransformerTestImpl(matrix, labelMatrix);
}

TEST_CASE("Standard") {
    PCATransformerTestStandard<float>();
    PCATransformerTestStandard<double>();
}

TEST_CASE("Map") {
    PCATransformerTestMap<float>();
    PCATransformerTestMap<double>();
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

    CHECK_THROWS_WITH(estimator.fit(trainingMatrix), "`fit` should not be invoked on an estimator that is not training or is already finished/complete");
}


TEST_CASE("Different training and inferencing data") {
    using MatrixType = Eigen::MatrixX<std::double_t>;

    MatrixType trainingMatrix(3, 3);
    trainingMatrix(0, 0) = -1;
    trainingMatrix(0, 1) = -1;
    trainingMatrix(0, 2) =  0;
    trainingMatrix(1, 0) =  0;
    trainingMatrix(1, 1) = -2;
    trainingMatrix(1, 2) = -1;
    trainingMatrix(2, 0) = -3;
    trainingMatrix(2, 1) =  0;
    trainingMatrix(2, 2) = -2;

    MatrixType inferenceMatrix(3, 3);
    inferenceMatrix(0, 0) = 1;
    inferenceMatrix(0, 1) = 0;
    inferenceMatrix(0, 2) = 0;
    inferenceMatrix(1, 0) = 0;
    inferenceMatrix(1, 1) = 1;
    inferenceMatrix(1, 2) = 0;
    inferenceMatrix(2, 0) = 0;
    inferenceMatrix(2, 1) = 0;
    inferenceMatrix(2, 2) = 1;



    using PCAEstimator                                 = NS::Featurizers::PCAEstimator<MatrixType>;
    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    std::vector<std::vector<MatrixType>> trainingBatches  = NS::TestHelpers::make_vector<std::vector<MatrixType>>(
        NS::TestHelpers::make_vector<MatrixType>(trainingMatrix)
    );

    std::vector<MatrixType> inputContainers = NS::TestHelpers::make_vector<MatrixType>(inferenceMatrix);
    std::vector<MatrixType> outputContainer = NS::TestHelpers::TransformerEstimatorTest(PCAEstimator(pAllColumnAnnotations, 0), trainingBatches, inputContainers);


    MatrixType inferenceOutput(3, 3);
    inferenceOutput(0, 0) =  0.588348;
    inferenceOutput(0, 1) =  0.784465;
    inferenceOutput(0, 2) = -0.196116;
    inferenceOutput(1, 0) =  0.196583;
    inferenceOutput(1, 1) = -0.374023;
    inferenceOutput(1, 2) = -0.906345;
    inferenceOutput(2, 0) =  0.784348;
    inferenceOutput(2, 1) = -0.494694;
    inferenceOutput(2, 2) =  0.374268;

    std::cout<<outputContainer[0]<<std::endl;
    std::cout<<inferenceOutput<<std::endl;

    // we used a randomized algorithm for the decomposition of matrices
    // so for all compilers, the absolute values of matrix element are the same
    // but signedness can be different for an entire column
    std::double_t eps = 0.00001;
    for (MatrixType::Index col=0; col < outputContainer[0].cols(); ++col) {
        // bool negative = std::abs(inferenceOutput(0,col) - outputContainer[0](0,col)) > eps;
        for (MatrixType::Index row=0; row < outputContainer[0].rows(); ++row) {
            // if (negative) {
            //     CHECK(std::abs(inferenceOutput(row, col) + outputContainer[0](row,col)) <= eps);
            // }
            // else {
                CHECK(std::abs(inferenceOutput(row, col) - outputContainer[0](row,col)) <= eps);
            // }
        }
    }
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
