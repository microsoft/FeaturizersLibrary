// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "TrainingOnlyEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         MatrixDecompositionEstimatorName("MatrixDecompositionEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         MatrixDecompositionAnnotationData
///  \brief         Contains 
///
template <typename T>
class MatrixDecompositionAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using SingularValueType                          = std::vector<T>;
    using SingularVectorType                         = std::vector<std::vector<T>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    SingularValueType const                          Sigma;
    SingularVectorType const                         U;
    SingularVectorType const                         V;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MatrixDecompositionAnnotationData(SingularValueType sigma, SingularVectorType u, SingularVectorType v);
    ~MatrixDecompositionAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MatrixDecompositionAnnotationData);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         MatrixDecompositionTrainingOnlyPolicy
///  \brief         `MatrixDecompositionEstimator` implementation details.
///
template <typename T>
class MatrixDecompositionTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                                  = T;
    using SingularValueType                          = std::vector<T>;
    using SingularVectorType                         = std::vector<std::vector<T>>;
    using MatrixType                                 = std::vector<T>;
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = MatrixDecompositionEstimatorName;
    enum DecompositionMethod {
        SVD = 0,
        PCA = 1
    };
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MatrixDecompositionTrainingOnlyPolicy(DecompositionMethod method, size_t numRows);

    void fit(InputType const &input);
    MatrixDecompositionAnnotationData<T> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    MatrixType                                       _matrix;

    SingularValueType                                _sigma;
    SingularVectorType                               _u;
    SingularVectorType                               _v;

    DecompositionMethod const                        _method;
    size_t const                                     _numRows;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         MatrixDecompositionEstimator
///  \brief         This class 
///                
///
template <
    typename T,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class MatrixDecompositionEstimator :
    public TrainingOnlyEstimatorImpl<
        Details::MatrixDecompositionTrainingOnlyPolicy<T>,
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
            Details::MatrixDecompositionTrainingOnlyPolicy<T>,
            MaxNumTrainingItemsV
        >;
    using DecompositionMethod = typename Details::MatrixDecompositionTrainingOnlyPolicy<T>::DecompositionMethod;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MatrixDecompositionEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, DecompositionMethod method, size_t numRows);
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
MatrixDecompositionAnnotationData<T>::MatrixDecompositionAnnotationData(SingularValueType sigma, SingularVectorType u, SingularVectorType v) :
    Sigma(std::move(sigma)),
    U(std::move(u)),
    V(std::move(v)) {
}

// ----------------------------------------------------------------------
// |
// |  MatrixDecompositionEstimator
// |
// ----------------------------------------------------------------------
template <typename T, size_t MaxNumTrainingItemsV>
MatrixDecompositionEstimator<T, MaxNumTrainingItemsV>::MatrixDecompositionEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, DecompositionMethod method, size_t numRows) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex), true, std::move(method), std::move(numRows)) {
}

// ----------------------------------------------------------------------
// |
// |  Details::MatrixDecompositionTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::MatrixDecompositionTrainingOnlyPolicy<T>::MatrixDecompositionTrainingOnlyPolicy(DecompositionMethod method, size_t numRows) :
    //todo:variable validation 
    _method(method),
    _numRows(std::move(numRows)) {
}

template <typename T>
void Details::MatrixDecompositionTrainingOnlyPolicy<T>::fit(InputType const &input) {
    _matrix.emplace_back(input);
}

template <typename T>
MatrixDecompositionAnnotationData<T> Details::MatrixDecompositionTrainingOnlyPolicy<T>::complete_training(void) {

    //svd, pca solver goes here...
    //svd, pca solver goes here...
    //svd, pca solver goes here...
    //svd, pca solver goes here...
    //svd, pca solver goes here...
    //svd, pca solver goes here...
    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------
    //sample code. just copy the origin matrix to output variable with the correct shape.
    size_t numCols = _matrix.size() / _numRows;
    std::vector<std::double_t> temp_vec;
    for (T const & val : _matrix) {
        _sigma.emplace_back(val);
        temp_vec.emplace_back(val);
        if (temp_vec.size() % numCols == 0) {
            _u.emplace_back(temp_vec);
            _v.emplace_back(temp_vec);
            temp_vec = {};
        }   
    }
    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------
    // ----------------------------------------------------------------------
    
    return MatrixDecompositionAnnotationData<T>(std::move(_sigma), std::move(_u), std::move(_v));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
