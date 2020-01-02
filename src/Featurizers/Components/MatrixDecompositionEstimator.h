// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "TrainingOnlyEstimatorImpl.h"

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wold-style-cast"
#   pragma clang diagnostic ignored "-Wsign-conversion"
#   pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#   pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#   pragma clang diagnostic ignored "-Wextra-semi-stmt"
#   pragma clang diagnostic ignored "-Wmissing-noreturn"
#   pragma clang diagnostic ignored "-Wdocumentation"
#   pragma clang diagnostic ignored "-Wcast-align"
#   pragma clang diagnostic ignored "-Wfloat-equal"
#elif (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127)
#endif

#include "../../3rdParty/eigen-git-mirror/Eigen/Core"
#include "../../3rdParty/eigen-git-mirror/Eigen/Eigen"
#include "../../3rdParty/eigen-git-mirror/Eigen/SVD"

#if (defined __clang__)
#   pragma clang diagnostic pop
#elif (defined _MSC_VER)
#   pragma warning(pop)
#endif

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         MatrixDecompositionEstimatorName("MatrixDecompositionEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         MatrixDecompositionAnnotationData
///  \brief         Contains matrix decomposition components: 
///                 for PCA, they are eigenvalues and eigenvectors
///                 for SVD, they are singularvalues and singularvectors
template <typename T>
class MatrixDecompositionAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using CharacteristicValuesContainer              = std::vector<T>;
    using FeatureVectorContainer                     = std::vector<CharacteristicValuesContainer>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    CharacteristicValuesContainer const              Sigma;
    FeatureVectorContainer const                     U;
    FeatureVectorContainer const                     V;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MatrixDecompositionAnnotationData(CharacteristicValuesContainer sigma, FeatureVectorContainer u, FeatureVectorContainer v);
    ~MatrixDecompositionAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MatrixDecompositionAnnotationData);
};

// ----------------------------------------------------------------------
// |
// |  2d Eigen::MatrixX<T> -> vector<vector<T>>
// |
// ----------------------------------------------------------------------
namespace {

template <typename T>
inline std::vector<std::vector<T>> EigenMatrixX2VectorContainer(Eigen::MatrixX<T> const & eigenMatrix) {
    std::vector<std::vector<T>> returnVector;
    for (Eigen::Index rowIdx = 0; rowIdx < eigenMatrix.rows(); ++rowIdx) {
        std::vector<T> tempRow;
        for (Eigen::Index colIdx = 0; colIdx < eigenMatrix.cols(); ++colIdx) {
            tempRow.emplace_back(eigenMatrix(rowIdx, colIdx));
        }
        returnVector.emplace_back(tempRow);
    }
    return returnVector;
}

template <typename T>
inline std::vector<T> EigenMatrixX2Vector(Eigen::MatrixX<T> const & eigenMatrix) {
    std::vector<T> returnVector;
    for (Eigen::Index rowIdx = 0; rowIdx < eigenMatrix.rows(); ++rowIdx) { 
        for (Eigen::Index colIdx = 0; colIdx < eigenMatrix.cols(); ++colIdx) {
            returnVector.emplace_back(eigenMatrix(rowIdx, colIdx));
        }
    }
    return returnVector;
}

template <typename T>
inline Eigen::MatrixX<T> VectorContainer2EigenMatrix(std::vector<T> const & vector, size_t numRows, size_t numCols) {
    Eigen::MatrixX<T> eigenMatrix(numRows, numCols);
    size_t count = 0;
    for (T const & val : vector) {
        eigenMatrix(static_cast<Eigen::Index>(count / numCols), static_cast<Eigen::Index>(count % numCols)) = val;
        ++count;
    }
    return eigenMatrix;
}

}

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         SVDTrainingOnlyPolicy
///  \brief         `MatrixDecompositionEstimator` implementation details.
///
template <typename T>
class SVDTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                                  = T;
    using SingularValuesContainer                    = std::vector<T>;
    using SingularVectorContainer                    = std::vector<SingularValuesContainer>;
    using MatrixT                                    = std::vector<T>;
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = MatrixDecompositionEstimatorName;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SVDTrainingOnlyPolicy(size_t numRows);

    void fit(InputType const &input);
    MatrixDecompositionAnnotationData<T> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                                     _numRows;

    MatrixT                                          _matrix;
    SingularValuesContainer                          _sigma;
    SingularVectorContainer                          _u;
    SingularVectorContainer                          _v;
};

/////////////////////////////////////////////////////////////////////////
///  \class         PCATrainingOnlyPolicy
///  \brief         `MatrixDecompositionEstimator` implementation details.
///
template <typename T>
class PCATrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                                  = T;
    using EigenValuesContainer                       = std::vector<T>;
    using EigenValuesContainers                      = std::vector<EigenValuesContainer>;
    using MatrixT                                    = std::vector<T>;
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = MatrixDecompositionEstimatorName;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    PCATrainingOnlyPolicy(size_t numRows);

    void fit(InputType const &input);
    MatrixDecompositionAnnotationData<T> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                                     _numRows;

    MatrixT                                          _matrix;
    EigenValuesContainer                             _sigma;
    EigenValuesContainers                            _u;
    EigenValuesContainers                            _v;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         MatrixDecompositionEstimator
///  \brief         This class generates MatrixDecompositionAnnotationData
///                 by processing input matrix using Eigen
///
template <
    typename DecompositionPolicy,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class MatrixDecompositionEstimator :
    public TrainingOnlyEstimatorImpl<
        DecompositionPolicy,
        MaxNumTrainingItemsV
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        TrainingOnlyEstimatorImpl<
            DecompositionPolicy,
            MaxNumTrainingItemsV
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MatrixDecompositionEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, size_t numRows);
    ~MatrixDecompositionEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MatrixDecompositionEstimator);
};

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Implementation
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
// |
// |  MatrixDecompositionAnnotationData
// |
// ----------------------------------------------------------------------
template <typename T>
MatrixDecompositionAnnotationData<T>::MatrixDecompositionAnnotationData(CharacteristicValuesContainer sigma, FeatureVectorContainer u, FeatureVectorContainer v) :
    Sigma(
        std::move(
            [&sigma](void) -> CharacteristicValuesContainer & {
                if(sigma.size() == 0)
                    throw std::invalid_argument("sigma");

                return sigma;
            }()
        )
    ),
    U(
        std::move(
            [&u](void) -> FeatureVectorContainer & {
                if(u.size() == 0 || u[0].size() == 0)
                    throw std::invalid_argument("u");

                return u;
            }()
        )
    ),
    V(
        std::move(
            [&v](void) -> FeatureVectorContainer & {
                if(v.size() == 0 || v[0].size() == 0)
                    throw std::invalid_argument("v");

                return v;
            }()
        )
    ) {
}

// ----------------------------------------------------------------------
// |
// |  MatrixDecompositionEstimator
// |
// ----------------------------------------------------------------------
template <typename DecompositionPolicy, size_t MaxNumTrainingItemsV>
MatrixDecompositionEstimator<DecompositionPolicy, MaxNumTrainingItemsV>::MatrixDecompositionEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, size_t numRows) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex), true, std::move(numRows)) {
}

// ----------------------------------------------------------------------
// |
// |  Details::SVDTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::SVDTrainingOnlyPolicy<T>::SVDTrainingOnlyPolicy(size_t numRows) :
    _numRows(
        [&numRows](void) -> size_t & {
            if(numRows == 0)
                throw std::invalid_argument("numRows");

            return numRows;
        }()
    ) {
}

template <typename T>
void Details::SVDTrainingOnlyPolicy<T>::fit(InputType const &input) {
    _matrix.emplace_back(input);
}

template <typename T>
MatrixDecompositionAnnotationData<T> Details::SVDTrainingOnlyPolicy<T>::complete_training(void) {

    Eigen::JacobiSVD<Eigen::MatrixX<T>> svd(
        [&]() -> Eigen::MatrixX<T> {
            size_t const numColsConst = _matrix.size() / _numRows;
            size_t const numRowsConst = _numRows;
           
            return VectorContainer2EigenMatrix(_matrix, numRowsConst, numColsConst);
        }(),
        Eigen::ComputeThinU | Eigen::ComputeThinV
    );

    _sigma = EigenMatrixX2Vector<T>(svd.singularValues());
    _u = EigenMatrixX2VectorContainer<T>(svd.matrixU());
    _v = EigenMatrixX2VectorContainer<T>(svd.matrixV());
    
    return MatrixDecompositionAnnotationData<T>(std::move(_sigma), std::move(_u), std::move(_v));
}

// ----------------------------------------------------------------------
// |
// |  Details::PCATrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::PCATrainingOnlyPolicy<T>::PCATrainingOnlyPolicy(size_t numRows) :
    _numRows(
        [&numRows](void) -> size_t & {
            if(numRows == 0)
                throw std::invalid_argument("numRows");

            return numRows;
        }()
    ) {
}

template <typename T>
void Details::PCATrainingOnlyPolicy<T>::fit(InputType const &input) {
    _matrix.emplace_back(input);
}

template <typename T>
MatrixDecompositionAnnotationData<T> Details::PCATrainingOnlyPolicy<T>::complete_training(void) {

    Eigen::SelfAdjointEigenSolver<Eigen::MatrixX<T>> eig(
        [&]() -> Eigen::MatrixX<T> {
            size_t const numColsConst = _matrix.size() / _numRows;
            size_t const numRowsConst = _numRows;
           
            Eigen::MatrixX<T> M = VectorContainer2EigenMatrix(_matrix, numRowsConst, numColsConst);

            //compute for centered training data
            Eigen::MatrixX<T> centered = M.rowwise() - M.colwise().mean();
            //compute for covariance matrix
            Eigen::MatrixX<T> cov = centered.adjoint() * centered;
            //using covariance matrix to compute PCA
            return cov;
        }()
    );

    //PCA uses sigma but sklearn PCA uses sqrt(sigma), this implementation follows first concept. 
    _sigma = EigenMatrixX2Vector<T>(eig.eigenvalues());
    _u = EigenMatrixX2VectorContainer<T>(eig.eigenvectors());
    _v = EigenMatrixX2VectorContainer<T>(eig.eigenvectors().transpose());
    
    return MatrixDecompositionAnnotationData<T>(std::move(_sigma), std::move(_u), std::move(_v));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
