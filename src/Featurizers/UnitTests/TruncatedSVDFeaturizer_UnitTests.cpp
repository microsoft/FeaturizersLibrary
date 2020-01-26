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

template <typename MatrixT>
void TruncatedSVDTransformerTest() {
    std::float_t eps = 0.0001f;

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

    MatrixT input = trainingMatrix;

    #if (defined __clang__)
    #   pragma clang diagnostic push
    #   pragma clang diagnostic ignored "-Wdouble-promotion"
    #endif

    MatrixT label(3, 3);
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

    using SVDEstimator                                 = NS::Featurizers::TruncatedSVDEstimator<MatrixT>;
    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    std::vector<std::vector<MatrixT>> trainingBatches  = NS::TestHelpers::make_vector<std::vector<MatrixT>>(
        NS::TestHelpers::make_vector<MatrixT>(trainingMatrix)
    );

    std::vector<MatrixT> inputContainers = NS::TestHelpers::make_vector<MatrixT>(input);
    std::vector<MatrixT> outputContainer = NS::TestHelpers::TransformerEstimatorTest(SVDEstimator(pAllColumnAnnotations, 0), trainingBatches, inputContainers);

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
    MatrixT invalidSingularVectors;
    MatrixT validSingularVectors(2, 2);
    CHECK_THROWS_WITH(NS::Featurizers::TruncatedSVDTransformer<MatrixT>(invalidSingularVectors), "singularvectors");
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

    using SVDEstimator                                 = NS::Featurizers::TruncatedSVDEstimator<MatrixT>;
    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    SVDEstimator                                       estimator(pAllColumnAnnotations, 0);

    estimator.begin_training();
    estimator.fit(trainingMatrix);

    CHECK_THROWS_WITH(estimator.fit(trainingMatrix), "fit_impl() should not be called move than once in TruncatedSVDFeaturizer");
}

TEST_CASE("TruncatedSVDTransformerTest") {
    TruncatedSVDTransformerTest<Eigen::MatrixX<float>>();
    TruncatedSVDTransformerTest<Eigen::MatrixX<double>>();
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

    using SVDEstimator                                 = NS::Featurizers::TruncatedSVDEstimator<MatrixType>;
    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    std::vector<std::vector<MatrixType>> trainingBatches  = NS::TestHelpers::make_vector<std::vector<MatrixType>>(
        NS::TestHelpers::make_vector<MatrixType>(trainingMatrix)
    );

    std::vector<MatrixType> inputContainers = NS::TestHelpers::make_vector<MatrixType>(inferenceMatrix);
    std::vector<MatrixType> outputContainer = NS::TestHelpers::TransformerEstimatorTest(SVDEstimator(pAllColumnAnnotations, 0), trainingBatches, inputContainers);


    MatrixType inferenceOutput(3, 3);
    inferenceOutput(0, 0) =  0.805055;
    inferenceOutput(0, 1) =  0.315909;
    inferenceOutput(0, 2) =  0.502083;
    inferenceOutput(1, 0) =  0.204052;
    inferenceOutput(1, 1) = -0.942224;
    inferenceOutput(1, 2) =  0.265661;
    inferenceOutput(2, 0) =  0.557;
    inferenceOutput(2, 1) = -0.111421;
    inferenceOutput(2, 2) = -0.823005;

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
    using TransformerType = NS::Featurizers::TruncatedSVDTransformer<MatrixT>;

    MatrixT singularValues(3, 1);
    singularValues(0, 0) = 3.79535f;
    singularValues(1, 0) = 2.21387f;
    singularValues(2, 0) = 0.83309f;

    MatrixT singularVectors(3, 3);
    singularVectors(0, 0) =  0.805059f;
    singularVectors(0, 1) = -0.315908f;
    singularVectors(0, 2) = -0.502078f;
    singularVectors(1, 0) =  0.204052f;
    singularVectors(1, 1) =  0.942225f;
    singularVectors(1, 2) = -0.265660f;
    singularVectors(2, 0) =  0.556994f;
    singularVectors(2, 1) =  0.111422f;
    singularVectors(2, 2) =  0.823008f;

    TransformerType                         original(singularVectors);

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
        (NS::Featurizers::TruncatedSVDTransformer<Eigen::MatrixX<float>>(in)),
        Catch::Contains("Unsupported archive version")
    );
}

