// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "../Traits.h"

#include "Components/InferenceOnlyFeaturizerImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         ForecastingPivotTransformer
///  \brief         Expand output from upstream featurizers where all values
///                 in the same column across matrixes are not null/empty
///
template <typename InputT>
class ForecastingPivotTransformer :
    public Components::InferenceOnlyTransformerImpl<
        typename std::vector<Microsoft::Featurizer::RowMajMatrix<typename Microsoft::Featurizer::Traits<InputT>::nullable_type>>,
        std::vector<InputT>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<InputT>::IsNullableType == false || Traits<InputT>::IsNativeNullableType, "'InputT' should not be a nullable type");

    using BaseType =
        Components::InferenceOnlyTransformerImpl<
            typename std::vector<Microsoft::Featurizer::RowMajMatrix<typename Microsoft::Featurizer::Traits<InputT>::nullable_type>>,
            std::vector<InputT>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ForecastingPivotTransformer(void) = default;
    ForecastingPivotTransformer(Archive &ar);

    ~ForecastingPivotTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ForecastingPivotTransformer);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using NullableType                      = typename Microsoft::Featurizer::Traits<InputT>::nullable_type;
    using MatrixType                        = Microsoft::Featurizer::RowMajMatrix<NullableType>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC runs into problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        if (input.empty()) {
            throw std::invalid_argument("There's no input matrix passed in!");
        }
        
        Eigen::Index const col_size(input[0].cols());

        for (Eigen::Index col = 0; col < col_size; ++col) {
            std::vector<InputT> ret;
            bool has_nan(false);

            // if any nans is found in the current column across all matrixes, this column is omitted
            for (MatrixType const & matrix : input) {
                // all matrixes must have the same column number
                if (matrix.cols() != col_size) {
                    throw std::invalid_argument("All input matrixes should have the same number of columns!");
                }

                for (Eigen::Index row = 0; row < matrix.rows(); ++row) {
                    if (Traits<NullableType>::IsNull(matrix(row, col))) {
                        has_nan = true;
                        break;
                    }

                    ret.emplace_back(Traits<NullableType>::GetNullableValue(matrix(row, col)));
                }

                if (has_nan) {
                    break;
                }
            }

            if (!has_nan) {
                callback(std::move(ret));
            }
        }
    }
};

/////////////////////////////////////////////////////////////////////////
///  \typedef       ForecastingPivotEstimator
///  \brief         Estimator that creates `ForecastingPivotTransformer`.
///
template <typename T>
class ForecastingPivotEstimator : public Components::InferenceOnlyEstimatorImpl<ForecastingPivotTransformer<T>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = Components::InferenceOnlyEstimatorImpl<ForecastingPivotTransformer<T>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ForecastingPivotEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~ForecastingPivotEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ForecastingPivotEstimator);
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
// |  ForecastingPivotTransformer
// |
// ----------------------------------------------------------------------
template <typename T>
ForecastingPivotTransformer<T>::ForecastingPivotTransformer(Archive &ar) :
    BaseType(ar) {
}

// ----------------------------------------------------------------------
// |
// |  ForecastingPivotEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
ForecastingPivotEstimator<T>::ForecastingPivotEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("ForecastingPivotEstimator", std::move(pAllColumnAnnotations)) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
