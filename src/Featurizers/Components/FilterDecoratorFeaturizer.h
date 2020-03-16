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
///  \class         FilterDecoratorTransformer
///  \brief         Tuple values can accumulate when multiple featurizers
///                 are run through a pipeline. This transformer will extract
///                 specific values from the input tuple, returning a subset of
///                 each input type.
///
template <typename InputTupleT, size_t... FilterInputTupleIndexVs>
class FilterDecoratorTransformer :
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
    FilterDecoratorTransformer(void) = default;
    FilterDecoratorTransformer(Archive &ar);
    ~FilterDecoratorTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FilterDecoratorTransformer);

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
///  \class         FilterDecoratorEstimator
///  \brief         Estimator whose purpose in life is to create a
///                 FilterDecoratorTransformer object (no training is required).
///
template <typename InputTupleT, size_t... FilterInputTupleIndexVs>
class FilterDecoratorEstimator :
    public InferenceOnlyEstimatorImpl<
        FilterDecoratorTransformer<InputTupleT, FilterInputTupleIndexVs...>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = InferenceOnlyEstimatorImpl<FilterDecoratorTransformer<InputTupleT, FilterInputTupleIndexVs...>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    FilterDecoratorEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~FilterDecoratorEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FilterDecoratorEstimator);
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
// |  FilterDecoratorTransformer
// |
// ----------------------------------------------------------------------
template <typename InputTupleT, size_t... FilterInputTupleIndexVs>
FilterDecoratorTransformer<InputTupleT, FilterInputTupleIndexVs...>::FilterDecoratorTransformer(Archive &ar) :
    BaseType(ar) {
}

// ----------------------------------------------------------------------
// |
// |  FilterDecoratorEstimator
// |
// ----------------------------------------------------------------------
template <typename InputTupleT, size_t... FilterInputTupleIndexVs>
FilterDecoratorEstimator<InputTupleT, FilterInputTupleIndexVs...>::FilterDecoratorEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("FilterDecoratorEstimator", std::move(pAllColumnAnnotations)) {
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
