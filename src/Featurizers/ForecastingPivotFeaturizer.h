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

namespace Details {

template <typename T, bool IsNativeNullableTypeV>
struct ScalarTypeImpl {
    using type                              = T;
};

template <typename T>
struct ScalarTypeImpl<T, false> {
    using type                              = typename T::value_type;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         ForecastingPivotTransformerTraits
///  \brief         Extracts information from types passed to
///                 `ForecastingPivotTransformer`.
///
template <typename MatrixIteratorRangeT>
struct ForecastingPivotTransformerTraits {
    static_assert(IsIteratorRange<MatrixIteratorRangeT>::value, "'MatrixIteratorRangeT' must be an iterator pair");

    using IteratorType                      = typename std::remove_reference<decltype(std::get<0>(std::declval<MatrixIteratorRangeT>()))>::type;
    using MatrixType                        = typename std::iterator_traits<IteratorType>::value_type;

    static_assert(IsMatrix<MatrixType>::value, "'MatrixIteratorRangeT' must be an iterator range of Matrix types");

    using MatrixScalarType                  = typename MatrixType::Scalar;

    static_assert(Traits<MatrixScalarType>::IsNullableType, "'MatrixIteratorRangeT' must be an iterator range of Matrix types composed of nullable values");

    // Remove the "optional-ness" if the matrix scalar type
    using ScalarType                        = typename Details::ScalarTypeImpl<MatrixScalarType, Traits<MatrixScalarType>::IsNativeNullableType>::type;
};

/////////////////////////////////////////////////////////////////////////
///  \class         ForecastingPivotTransformer
///  \brief         Expand output from upstream featurizers where all values
///                 in the same column across matrixes are not null/empty
///
template <typename MatrixIteratorRangeT>
class ForecastingPivotTransformer :
    public Components::InferenceOnlyTransformerImpl<
        MatrixIteratorRangeT,
        std::vector<typename ForecastingPivotTransformerTraits<MatrixIteratorRangeT>::ScalarType>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TheseTraits                       = ForecastingPivotTransformerTraits<MatrixIteratorRangeT>;

    using BaseType =
        Components::InferenceOnlyTransformerImpl<
            MatrixIteratorRangeT,
            std::vector<typename TheseTraits::ScalarType>
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
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC runs into problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        // ----------------------------------------------------------------------
        using MatrixType                    = typename TheseTraits::MatrixType;
        using IteratorType                  = typename TheseTraits::IteratorType;
        using NullableType                  = typename Microsoft::Featurizer::Traits<typename TheseTraits::ScalarType>::nullable_type;
        // ----------------------------------------------------------------------

        IteratorType const                  begin(std::get<0>(input));
        IteratorType const                  end(std::get<1>(input));

        if (begin == end) {
            throw std::invalid_argument("There's no input matrix passed in!");
        }

        Eigen::Index const col_size(begin->cols());

        for (Eigen::Index col = 0; col < col_size; ++col) {
            typename BaseType::TransformedType          ret;
            bool                                        has_nan(false);

            // if any nans is found in the current column across all matrixes, this column is omitted
            IteratorType                    ptr(begin);

            while(ptr != end) {
                MatrixType const &          matrix(*ptr++);

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
template <typename MatrixIteratorRangeT>
class ForecastingPivotEstimator : public Components::InferenceOnlyEstimatorImpl<ForecastingPivotTransformer<MatrixIteratorRangeT>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = Components::InferenceOnlyEstimatorImpl<ForecastingPivotTransformer<MatrixIteratorRangeT>>;

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
template <typename MatrixIteratorRangeT>
ForecastingPivotTransformer<MatrixIteratorRangeT>::ForecastingPivotTransformer(Archive &ar) :
    BaseType(ar) {
}

// ----------------------------------------------------------------------
// |
// |  ForecastingPivotEstimator
// |
// ----------------------------------------------------------------------
template <typename MatrixIteratorRangeT>
ForecastingPivotEstimator<MatrixIteratorRangeT>::ForecastingPivotEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("ForecastingPivotEstimator", std::move(pAllColumnAnnotations)) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
