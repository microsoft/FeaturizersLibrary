// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "InferenceOnlyFeaturizerImpl.h"

#include "Details/EstimatorTraits.h"
#include "Details/FilterTraits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

/////////////////////////////////////////////////////////////////////////
///  \class         FilterSinkTransformer
///  \brief         Tuple values can accumulate when multiple featurizers
///                 are run through a pipeline. This transformer will extract
///                 specific values from the input tuple, returning a subset of
///                 each input type.
///
template <typename InputTupleT, size_t... FilterInputTupleIndexVs>
class FilterSinkTransformer :
    public InferenceOnlyTransformerImpl<
        InputTupleT,
        typename Details::FilterFeaturizerTraits<InputTupleT, FilterInputTupleIndexVs...>::FilteredType
    >
{
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using FilterFeaturizerTraits            = Details::FilterFeaturizerTraits<InputTupleT, FilterInputTupleIndexVs...>;

    using BaseType =
        InferenceOnlyTransformerImpl<
            InputTupleT,
            typename FilterFeaturizerTraits::FilteredType
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    FilterSinkTransformer(void) = default;
    FilterSinkTransformer(Archive &ar);
    ~FilterSinkTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FilterSinkTransformer);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        callback(FilterFeaturizerTraits::ToFilteredType(input));
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         FilterSinkEstimator
///  \brief         Estimator whose purpose in life is to create a
///                 FilterSinkTransformer object (no training is required).
///
template <typename InputTupleT, size_t... FilterInputTupleIndexVs>
class FilterSinkEstimator :
    public InferenceOnlyEstimatorImpl<
        FilterSinkTransformer<InputTupleT, FilterInputTupleIndexVs...>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = InferenceOnlyEstimatorImpl<FilterSinkTransformer<InputTupleT, FilterInputTupleIndexVs...>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    FilterSinkEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~FilterSinkEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FilterSinkEstimator);
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
// |  FilterSinkTransformer
// |
// ----------------------------------------------------------------------
template <typename InputTupleT, size_t... FilterInputTupleIndexVs>
FilterSinkTransformer<InputTupleT, FilterInputTupleIndexVs...>::FilterSinkTransformer(Archive &ar) :
    BaseType(ar) {
}

// ----------------------------------------------------------------------
// |
// |  FilterSinkEstimator
// |
// ----------------------------------------------------------------------
template <typename InputTupleT, size_t... FilterInputTupleIndexVs>
FilterSinkEstimator<InputTupleT, FilterInputTupleIndexVs...>::FilterSinkEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("FilterSinkEstimator", std::move(pAllColumnAnnotations)) {
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
