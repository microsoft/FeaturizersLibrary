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
#endif

#include "../../3rdParty/eigen-git-mirror/Eigen/Core"
#include "../../3rdParty/eigen-git-mirror/Eigen/Eigen"
#include "../../3rdParty/eigen-git-mirror/Eigen/SVD"

#if (defined __clang__)
#   pragma clang diagnostic pop
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

    size_t numColsConst = _matrix.size() / _numRows;
    size_t numRowsConst = _numRows;
    
    //consider use lambda
    Eigen::MatrixX<T> M(numRowsConst, numColsConst);

    size_t count = 0;
    for (T const & val : _matrix) {
        M(static_cast<Eigen::Index>(count / numColsConst), static_cast<Eigen::Index>(count % numColsConst)) = val;
        ++count;
    }

    Eigen::JacobiSVD<Eigen::MatrixX<T>> svd(M, Eigen::ComputeThinU | Eigen::ComputeThinV);

    Eigen::MatrixX<T> sigma = svd.singularValues();
    for (Eigen::Index i = 0; i < sigma.rows(); i++) {
        for (Eigen::Index j = 0; j < sigma.cols(); j++) {
            _sigma.emplace_back(sigma(i, j));
        }
    }

    Eigen::MatrixX<T> u = svd.matrixU();
    for (Eigen::Index i = 0; i < u.rows(); i++) {
        std::vector<T> tempU;
        for (Eigen::Index j = 0; j < u.cols(); j++) {
            tempU.emplace_back(u(i, j));
        }
        _u.emplace_back(tempU);
    }

    Eigen::MatrixX<T> v = svd.matrixV();
    for (Eigen::Index i = 0; i < v.rows(); i++) {
        std::vector<T> tempV;
        for (Eigen::Index j = 0; j < v.cols(); j++) {
            tempV.emplace_back(v(i, j));
        }
        _v.emplace_back(tempV);
    }
    
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

    size_t const numColsConst = _matrix.size() / _numRows;
    size_t const numRowsConst = _numRows;
    
    //consider use lambda
    Eigen::MatrixX<T> M(numRowsConst, numColsConst);

    size_t count = 0;
    for (T const & val : _matrix) {
        M(static_cast<Eigen::Index>(count / numColsConst), static_cast<Eigen::Index>(count % numColsConst)) = val;
        ++count;
    }

    Eigen::MatrixX<T> centered = M.rowwise() - M.colwise().mean();
    Eigen::MatrixX<T> cov = centered.adjoint() * centered;

    Eigen::SelfAdjointEigenSolver<Eigen::MatrixX<T>> eig(cov);

    Eigen::MatrixX<T> sigma = eig.eigenvalues();
    for (Eigen::Index i = 0; i < sigma.rows(); i++) {
        for (Eigen::Index j = 0; j < sigma.cols(); j++) {
            _sigma.emplace_back(sigma(i, j));
        }
    }

    Eigen::MatrixX<T> u = eig.eigenvectors();
    for (Eigen::Index i = 0; i < u.rows(); i++) {
        std::vector<T> tempU;
        for (Eigen::Index j = 0; j < u.cols(); j++) {
            tempU.emplace_back(u(i, j));
        }
        _u.emplace_back(tempU);
    }

    Eigen::MatrixX<T> v = u.transpose();
    for (Eigen::Index i = 0; i < v.rows(); i++) {
        std::vector<T> tempV;
        for (Eigen::Index j = 0; j < v.cols(); j++) {
            tempV.emplace_back(v(i, j));
        }
        _v.emplace_back(tempV);
    }
    
    return MatrixDecompositionAnnotationData<T>(std::move(_sigma), std::move(_u), std::move(_v));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
