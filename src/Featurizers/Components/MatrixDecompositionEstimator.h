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
///  \brief         Contains an MatrixDecomposition 
///
template <typename T>
class MatrixDecompositionAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using SingularValueType                          = T;
    using SingularVectorType                         = std::vector<SingularValueType>;

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
    using SingularValueType                          = InputType;
    using SingularVectorType                         = std::vector<SingularValueType>;
    using MatrixType                                 = SingularVectorType;
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
    MatrixDecompositionTrainingOnlyPolicy(std::string mode);

    void fit(InputType const &input);
    MatrixDecompositionAnnotationData<T> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    MatrixType                                       _matrix;

    SingularValueType const                          _sigma;
    SingularVectorType const                         _u;
    SingularVectorType const                         _v;

    std::string const                                _mode;
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

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MatrixDecompositionEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, std::string mode);
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
MatrixDecompositionEstimator<T, MaxNumTrainingItemsV>::MatrixDecompositionEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, std::string mode) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex), true, std::move(mode)) {
}

// ----------------------------------------------------------------------
// |
// |  Details::MatrixDecompositionTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::MatrixDecompositionTrainingOnlyPolicy<T>::MatrixDecompositionTrainingOnlyPolicy(std::string mode) :
    _mode(
        std::move(
            [&mode](void) -> std::string & {
                if(mode != "svd" && mode != "pca")
                    throw std::invalid_argument("only support svd and pca for now");

                return mode;
            }()
        )
    ) {
}

template <typename T>
void Details::MatrixDecompositionTrainingOnlyPolicy<T>::fit(InputType const &input) {
    _matrix.emplace_back(input);
}

template <typename T>
MatrixDecompositionAnnotationData<T> Details::MatrixDecompositionTrainingOnlyPolicy<T>::complete_training(void) {
    
    //do math

    return MatrixDecompositionAnnotationData<T>(_sigma, _u, _v);
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
