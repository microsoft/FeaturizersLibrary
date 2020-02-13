#pragma once
// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Traits.h"
#include "Components/InferenceOnlyFeaturizerImpl.h"

#include <tuple>
#include <numeric>

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

template<size_t I, typename TupleT>
using TupleElement = typename std::tuple_element<I, TupleT>::type;

/////////////////////////////////////////////////////////////////////////
///  \class         SampleSequenceSum
///  \brief         Accepts a sequence via an iterator pair and returns a sum of it
///
template <typename IteratorRangeT>
class SampleSequenceSumTransformer :
    public Components::InferenceOnlyTransformerImpl<IteratorRangeT, 
    typename std::iterator_traits<TupleElement<0, IteratorRangeT>>::value_type> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::InferenceOnlyTransformerImpl<IteratorRangeT,
        typename std::iterator_traits<TupleElement<0, IteratorRangeT>>::value_type>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SampleSequenceSumTransformer(void) = default;
    SampleSequenceSumTransformer(Archive& ar);

    ~SampleSequenceSumTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SampleSequenceSumTransformer);
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using IteratorType = TupleElement<0, IteratorRangeT>;
    using ValueType = typename std::iterator_traits<IteratorType>::value_type;
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(IteratorRangeT const& input, typename BaseType::CallbackFunction const& callback) override;
};

template <typename IteratorRangeT>
class SampleSequenceSumEstimator : public Components::InferenceOnlyEstimatorImpl<SampleSequenceSumTransformer<IteratorRangeT>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::InferenceOnlyEstimatorImpl<SampleSequenceSumTransformer<IteratorRangeT>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SampleSequenceSumEstimator(AnnotationMapsPtr pAllCoumnAnnotations);
    ~SampleSequenceSumEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SampleSequenceSumEstimator);
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
// |  SampleSequenceSumTransformer
// |
// ----------------------------------------------------------------------
template<typename IteratorRangeT>
inline SampleSequenceSumTransformer<IteratorRangeT>::SampleSequenceSumTransformer(Archive& ar) :
    BaseType(ar) {
}

template<typename IteratorRangeT>
inline void SampleSequenceSumTransformer<IteratorRangeT>::execute_impl(IteratorRangeT const& input, typename BaseType::CallbackFunction const& callback) {
    auto result = std::accumulate(std::get<0>(input), std::get<1>(input), ValueType(0));
    callback(result);
}

// ----------------------------------------------------------------------
// |
// |  SampleSequenceSumEstimator
// |
// ----------------------------------------------------------------------
template <typename IteratorRangeT>
inline SampleSequenceSumEstimator<IteratorRangeT>::SampleSequenceSumEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("MissingDummiesEstimator", std::move(pAllColumnAnnotations)) {}
}
}
} // namespace Microsoft
