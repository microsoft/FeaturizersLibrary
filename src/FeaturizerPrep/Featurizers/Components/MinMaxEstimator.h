// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>
#include "../../Archive.h"
#include "../../Featurizer.h"
#include "../../Traits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {


/////////////////////////////////////////////////////////////////////////
///  \class         MinMaxAnnotation
///  \brief         An annotation class which contains the min feature and the max
///                 for an input column
///
template <typename T>
class MinMaxAnnotation : public Annotation {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    T const                           Min;
    T const                           Max;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MinMaxAnnotation(T min, T max);
    ~MinMaxAnnotation(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MinMaxAnnotation);
};

/////////////////////////////////////////////////////////////////////////
///  \class         MinMaxEstimator
///  \brief         An AnnotationEstimator class that finds the min, max
///
template <typename InputT, size_t ColIndexV>
class MinMaxEstimator : public AnnotationEstimator<InputT const &> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MinMaxEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~MinMaxEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MinMaxEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                             = AnnotationEstimator<InputT const &>;
    using TraitsT                              = Traits<InputT>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    InputT                                       _min;
    InputT                                       _max;
    
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    Estimator::FitResult fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) override;

    Estimator::FitResult complete_training_impl(void) override;

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
// |  MinMaxAnnotation
// |
// ----------------------------------------------------------------------
template <typename T>
MinMaxAnnotation<T>::MinMaxAnnotation(T min, T max) :
    Annotation(this),
    Min(std::move(min)),
    Max(std::move(max)) {
}

// ----------------------------------------------------------------------
// |
// |  MinMaxEstimator
// |
// ----------------------------------------------------------------------

template <typename InputT, size_t ColIndexV>
MinMaxEstimator<InputT,ColIndexV>::MinMaxEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    AnnotationEstimator<InputT const &>("MinMaxEstimator", std::move(pAllColumnAnnotations)){
        // didn't use std::numeric_limits::min() because for float this is not the smallest possible value
        // but the smallest value closest to 0 instead
        _min = std::numeric_limits<InputT>::max();
        _max = std::numeric_limits<InputT>::lowest();
}

template <typename InputT, size_t ColIndexV>
Estimator::FitResult MinMaxEstimator<InputT,ColIndexV>::fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) {
    typename BaseType::FitBufferInputType const * const                 pEndBuffer(pBuffer + cBuffer);
    while(pBuffer != pEndBuffer) {
        InputT const &                                   input(*pBuffer++);
        // null input should be ignored
        if(TraitsT::IsNull(input))
            continue;
        if(input < _min) {
            _min = input;
        }
        if(input > _max) {
            _max = input;
        }
    }

    return Estimator::FitResult::Continue;
}

template <typename InputT, size_t ColIndexV>
Estimator::FitResult MinMaxEstimator<InputT,ColIndexV>::complete_training_impl(void) {
    assert(_min<=_max);
    BaseType::add_annotation(std::make_shared<MinMaxAnnotation<InputT>>(std::move(_min),std::move(_max)), ColIndexV);

    return Estimator::FitResult::Complete;
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
