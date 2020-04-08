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
void TruncatedSVDTransformerTestImpl(MatrixT const &trainingMatrix, MatrixT const &label) {
    std::float_t eps = 0.0001f;
    MatrixT input = trainingMatrix;

    using SVDEstimator                                 = NS::Featurizers::TruncatedSVDEstimator<MatrixT>;
    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    std::vector<std::vector<MatrixT>> trainingBatches  = NS::TestHelpers::make_vector<std::vector<MatrixT>>(
        NS::TestHelpers::make_vector<MatrixT>(trainingMatrix)
    );

    std::vector<MatrixT> inputContainers = NS::TestHelpers::make_vector<MatrixT>(input);
    std::vector<typename NS::InputMatrixTypeMapper<MatrixT>::MatrixType> outputContainer = NS::TestHelpers::TransformerEstimatorTest(SVDEstimator(pAllColumnAnnotations, 0, 42), trainingBatches, inputContainers);

    REQUIRE(outputContainer.size() == 1);

    typename NS::InputMatrixTypeMapper<MatrixT>::MatrixType const &    output(outputContainer[0]);

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
void TruncatedSVDTransformerTestColMajStandard(void) {
    // ----------------------------------------------------------------------
    using Matrix                            = NS::ColMajMatrix<T>;
    // ----------------------------------------------------------------------

    Matrix                                  trainingMatrix(3, 3);

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

    Matrix                                  label(3, 3);

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

    TruncatedSVDTransformerTestImpl(trainingMatrix, label);
}

template <typename T>
void TruncatedSVDTransformerTestRowMajStandard(void) {
    // ----------------------------------------------------------------------
    using Matrix = NS::RowMajMatrix<T>;
    // ----------------------------------------------------------------------

    Matrix                                  trainingMatrix(3, 3);

    trainingMatrix(0, 0) = -1;
    trainingMatrix(0, 1) = -1;
    trainingMatrix(0, 2) = 0;
    trainingMatrix(1, 0) = 0;
    trainingMatrix(1, 1) = -2;
    trainingMatrix(1, 2) = -1;
    trainingMatrix(2, 0) = -3;
    trainingMatrix(2, 1) = 0;
    trainingMatrix(2, 2) = -2;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

    Matrix                                  label(3, 3);

    label(0, 0) = -1.009107f;
    label(0, 1) = 0.626315f;
    label(0, 2) = -0.767745f;
    label(1, 0) = -0.965105f;
    label(1, 1) = 1.995869f;
    label(1, 2) = 0.291682f;
    label(2, 0) = -3.529165f;
    label(2, 1) = -0.724887f;
    label(2, 2) = 0.139759f;

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

    TruncatedSVDTransformerTestImpl(trainingMatrix, label);
}

template <typename T>
void TruncatedSVDTransformerTestMapColMaj(void) {
    // ----------------------------------------------------------------------
    using Matrix                            = Eigen::Map<NS::ColMajMatrix<T>>;
    // ----------------------------------------------------------------------

    // Column major order
    T                                       data[]{
        -1, 0, -3,
        -1, -2, 0,
        0, -1, -2

    };

    #if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

    T                                       labelData[]{
        -1.009107f, -0.965105f, -3.529165f,
        0.626315f, 1.995869f, -0.724887f,
        -0.767745f, 0.291682f, 0.139759f
    };

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

    Matrix                                  matrix(data, 3, 3);
    Matrix                                  labelMatrix(labelData, 3, 3);

    TruncatedSVDTransformerTestImpl(matrix, labelMatrix);
}

template <typename T>
void TruncatedSVDTransformerTestMapColMajConst(void) {
    // ----------------------------------------------------------------------
    using Matrix = Eigen::Map<const NS::ColMajMatrix<T>>;
    // ----------------------------------------------------------------------

    // Column major order
    const T   data[] = {
        -1, 0, -3,
        -1, -2, 0,
        0, -1, -2

    };

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

    const T labelData[] = {
        -1.009107f, -0.965105f, -3.529165f,
        0.626315f, 1.995869f, -0.724887f,
        -0.767745f, 0.291682f, 0.139759f
        };

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

    Matrix                                  matrix(data, 3, 3);
    Matrix                                  labelMatrix(labelData, 3, 3);

    TruncatedSVDTransformerTestImpl(matrix, labelMatrix);
}

template <typename T>
void TruncatedSVDTransformerTestMapRowMaj(void) {
    // ----------------------------------------------------------------------
    using Matrix = Eigen::Map<NS::RowMajMatrix<T>>;
    // ----------------------------------------------------------------------

    // Row major order
    T                                       data[]{
        -1, -1, 0,
        0, -2, -1,
        -3, 0, -2
    };

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif
    T                                       labelData[]{
        -1.009107f, 0.626315f, -0.767745f,
        -0.965105f, 1.995869f, 0.291682f,
        -3.529165f, -0.724887f, 0.139759f
    };

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

    Matrix                                  matrix(data, 3, 3);
    Matrix                                  labelMatrix(labelData, 3, 3);

    TruncatedSVDTransformerTestImpl(matrix, labelMatrix);
}

template <typename T>
void TruncatedSVDTransformerTestMapRowMajConst(void) {
    // ----------------------------------------------------------------------
    using Matrix = Eigen::Map<const NS::RowMajMatrix<T>>;
    // ----------------------------------------------------------------------

    // Row major order
    const T  data[] = {
        -1, -1, 0,
        0, -2, -1,
        -3, 0, -2
        };

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif
    const T labelData[] = {
        -1.009107f, 0.626315f, -0.767745f,
        -0.965105f, 1.995869f, 0.291682f,
        -3.529165f, -0.724887f, 0.139759f
    };

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

    Matrix                                  matrix(data, 3, 3);
    Matrix                                  labelMatrix(labelData, 3, 3);

    TruncatedSVDTransformerTestImpl(matrix, labelMatrix);
}


TEST_CASE("Standard ") {
    TruncatedSVDTransformerTestColMajStandard<float>();
    TruncatedSVDTransformerTestColMajStandard<double>();
    TruncatedSVDTransformerTestRowMajStandard<float>();
    TruncatedSVDTransformerTestRowMajStandard<double>();
}

TEST_CASE("Map") {
    TruncatedSVDTransformerTestMapColMaj<float>();
    TruncatedSVDTransformerTestMapColMaj<double>();
    TruncatedSVDTransformerTestMapColMajConst<double>();

    TruncatedSVDTransformerTestMapRowMaj<float>();
    TruncatedSVDTransformerTestMapRowMaj<double>();
    TruncatedSVDTransformerTestMapRowMajConst<float>();
    TruncatedSVDTransformerTestMapRowMajConst<double>();
}

TEST_CASE("Invalid_Annotation ColMajor") {
    using MatrixT = Eigen::MatrixX<float>;
    MatrixT invalidSingularVectors;
    MatrixT validSingularVectors(2, 2);
    CHECK_THROWS_WITH(NS::Featurizers::TruncatedSVDTransformer<MatrixT>(invalidSingularVectors), "singularvectors");
}

TEST_CASE("Invalid_Annotation RowMajor") {
    using MatrixT = NS::RowMajMatrix <float>;
    MatrixT invalidSingularVectors;
    MatrixT validSingularVectors(2, 2);
    CHECK_THROWS_WITH(NS::Featurizers::TruncatedSVDTransformer<MatrixT>(invalidSingularVectors), "singularvectors");
}

TEST_CASE("Invalid_fit ColMajor") {
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

    CHECK_THROWS_WITH(estimator.fit(trainingMatrix), "`fit` should not be invoked on an estimator that is not training or is already finished/complete");
}

TEST_CASE("Invalid_fit RowMajor") {
    using MatrixT = NS::RowMajMatrix<float>;

    MatrixT trainingMatrix(3, 3);
    trainingMatrix(0, 0) = -1;
    trainingMatrix(0, 1) = -1;
    trainingMatrix(0, 2) = 0;
    trainingMatrix(1, 0) = 0;
    trainingMatrix(1, 1) = -2;
    trainingMatrix(1, 2) = -1;
    trainingMatrix(2, 0) = -3;
    trainingMatrix(2, 1) = 0;
    trainingMatrix(2, 2) = -2;

    using SVDEstimator = NS::Featurizers::TruncatedSVDEstimator<MatrixT>;
    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    SVDEstimator                                       estimator(pAllColumnAnnotations, 0);

    estimator.begin_training();
    estimator.fit(trainingMatrix);

    CHECK_THROWS_WITH(estimator.fit(trainingMatrix), "`fit` should not be invoked on an estimator that is not training or is already finished/complete");
}

TEST_CASE("Different training and inferencing data ColMajor") {
    using MatrixType = NS::RowMajMatrix<std::double_t>;

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
    inferenceOutput(0, 1) = -0.315909;
    inferenceOutput(0, 2) = -0.502083;
    inferenceOutput(1, 0) =  0.204052;
    inferenceOutput(1, 1) =  0.942224;
    inferenceOutput(1, 2) = -0.265661;
    inferenceOutput(2, 0) =  0.557;
    inferenceOutput(2, 1) =  0.111421;
    inferenceOutput(2, 2) =  0.823005;

    for (MatrixType::Index col=0; col < outputContainer[0].cols(); ++col) {
        for (MatrixType::Index row=0; row < outputContainer[0].rows(); ++row) {
                 CHECK(Approx(inferenceOutput(row, col)) == outputContainer[0](row, col));
        }
    }
}

TEST_CASE("Different training and inferencing data RowMajor") {
    using MatrixType = NS::RowMajMatrix<std::double_t>;

    MatrixType trainingMatrix(3, 3);
    trainingMatrix(0, 0) = -1;
    trainingMatrix(0, 1) = -1;
    trainingMatrix(0, 2) = 0;
    trainingMatrix(1, 0) = 0;
    trainingMatrix(1, 1) = -2;
    trainingMatrix(1, 2) = -1;
    trainingMatrix(2, 0) = -3;
    trainingMatrix(2, 1) = 0;
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

    using SVDEstimator = NS::Featurizers::TruncatedSVDEstimator<MatrixType>;
    NS::AnnotationMapsPtr const                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    std::vector<std::vector<MatrixType>> trainingBatches = NS::TestHelpers::make_vector<std::vector<MatrixType>>(
        NS::TestHelpers::make_vector<MatrixType>(trainingMatrix)
        );

    std::vector<MatrixType> inputContainers = NS::TestHelpers::make_vector<MatrixType>(inferenceMatrix);
    std::vector<MatrixType> outputContainer = NS::TestHelpers::TransformerEstimatorTest(SVDEstimator(pAllColumnAnnotations, 0), trainingBatches, inputContainers);


    MatrixType inferenceOutput(3, 3);
    inferenceOutput(0, 0) = 0.805055;
    inferenceOutput(0, 1) = -0.315909;
    inferenceOutput(0, 2) = -0.502083;
    inferenceOutput(1, 0) = 0.204052;
    inferenceOutput(1, 1) = 0.942224;
    inferenceOutput(1, 2) = -0.265661;
    inferenceOutput(2, 0) = 0.557;
    inferenceOutput(2, 1) = 0.111421;
    inferenceOutput(2, 2) = 0.823005;

    for(MatrixType::Index col = 0; col < outputContainer[0].cols(); ++col) {
        for(MatrixType::Index row = 0; row < outputContainer[0].rows(); ++row) {
            CHECK(Approx(inferenceOutput(row, col)) == outputContainer[0](row, col));
            }
        }
}

TEST_CASE("Serialization/Deserialization ColMajor") {
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

TEST_CASE("Serialization/Deserialization RowMajor") {
    using MatrixT = NS::RowMajMatrix<float>;
    using TransformerType = NS::Featurizers::TruncatedSVDTransformer<MatrixT>;

    MatrixT singularValues(3, 1);
    singularValues(0, 0) = 3.79535f;
    singularValues(1, 0) = 2.21387f;
    singularValues(2, 0) = 0.83309f;

    MatrixT singularVectors(3, 3);
    singularVectors(0, 0) = 0.805059f;
    singularVectors(0, 1) = -0.315908f;
    singularVectors(0, 2) = -0.502078f;
    singularVectors(1, 0) = 0.204052f;
    singularVectors(1, 1) = 0.942225f;
    singularVectors(1, 2) = -0.265660f;
    singularVectors(2, 0) = 0.556994f;
    singularVectors(2, 1) = 0.111422f;
    singularVectors(2, 2) = 0.823008f;

    TransformerType                         original(singularVectors);

    NS::Archive                             out;

    original.save(out);

    NS::Archive                             in(out.commit());
    TransformerType                         other(in);

    CHECK(other == original);
}

TEST_CASE("Serialization Version Error ColMajor") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        (NS::Featurizers::TruncatedSVDTransformer<Eigen::MatrixX<float>>(in)),
        Catch::Contains("Unsupported archive version")
    );
}

TEST_CASE("Serialization Version Error RowMajor") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        (NS::Featurizers::TruncatedSVDTransformer<NS::RowMajMatrix<float>>(in)),
        Catch::Contains("Unsupported archive version")
    );
}

TEST_CASE("access to shape information ColMajor") {
    using MatrixT = Eigen::MatrixX<float>;
    MatrixT singularVectors(6, 2);
    singularVectors(0, 0) = -1;
    singularVectors(0, 1) = -1;
    singularVectors(1, 0) = -2;
    singularVectors(1, 1) = -1;
    singularVectors(2, 0) = -3;
    singularVectors(2, 1) = -2;
    singularVectors(3, 0) = 1;
    singularVectors(3, 1) = 1;
    singularVectors(4, 0) = 2;
    singularVectors(4, 1) = 1;
    singularVectors(5, 0) = 3;
    singularVectors(5, 1) = 2;

    Microsoft::Featurizer::Featurizers::TruncatedSVDTransformer<MatrixT>    svdTransformer(singularVectors);

    CHECK(svdTransformer.getEigenVectorRowsNumber() == 6);
    CHECK(svdTransformer.getEigenVectorColsNumber() == 2);
}

TEST_CASE("access to shape information RowMajor") {
    using MatrixT = NS::RowMajMatrix<float>;
    MatrixT singularVectors(6, 2);
    singularVectors(0, 0) = -1;
    singularVectors(0, 1) = -1;
    singularVectors(1, 0) = -2;
    singularVectors(1, 1) = -1;
    singularVectors(2, 0) = -3;
    singularVectors(2, 1) = -2;
    singularVectors(3, 0) = 1;
    singularVectors(3, 1) = 1;
    singularVectors(4, 0) = 2;
    singularVectors(4, 1) = 1;
    singularVectors(5, 0) = 3;
    singularVectors(5, 1) = 2;

    Microsoft::Featurizer::Featurizers::TruncatedSVDTransformer<MatrixT>    svdTransformer(singularVectors);

    CHECK(svdTransformer.getEigenVectorRowsNumber() == 6);
    CHECK(svdTransformer.getEigenVectorColsNumber() == 2);
}
