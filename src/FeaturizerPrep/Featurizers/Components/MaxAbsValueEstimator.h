// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <queue>
#include "../../Archive.h"
#include "../../Featurizer.h"
#include "../../Traits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

/////////////////////////////////////////////////////////////////////////
///  \class         MaxAbsValueAnnotation
///  \brief         An annotation class which contains the maxAbsVal(maximum absolute value)
///                 for an input column
///
template <typename T, typename TransformedT>
class MaxAbsValueAnnotation : public Annotation {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    TransformedT const                           MaxAbsVal;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MaxAbsValueAnnotation(TransformedT maxAbsVal);
    ~MaxAbsValueAnnotation(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MaxAbsValueAnnotation);
};

/////////////////////////////////////////////////////////////////////////
///  \class         MaxAbsValueEstimator
///  \brief         An AnnotationEstimator class that computes the maxAbsVal 
///                 for an input column and creates a MaxAbsValueAnnotation.
///
template <typename InputT,typename TransformedT, size_t ColIndexV>
class MaxAbsValueEstimator : public AnnotationEstimator<InputT const &> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MaxAbsValueEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~MaxAbsValueEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MaxAbsValueEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                             = AnnotationEstimator<InputT const &>;
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    InputT                                     _outerBound; 
    
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
// |  MaxAbsValueAnnotation
// |
// ----------------------------------------------------------------------
template <typename T, typename TransformedT>
MaxAbsValueAnnotation<T, TransformedT>::MaxAbsValueAnnotation(TransformedT maxAbsVal) :
    Annotation(this),
    MaxAbsVal(std::move(maxAbsVal)) {
    if (maxAbsVal <= 0)
        throw std::runtime_error("maxAbsVal must bigger than 0");
}

// ----------------------------------------------------------------------
// |
// |  MaxAbsValueEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT,typename TransformedT, size_t ColIndexV>
MaxAbsValueEstimator<InputT,TransformedT,ColIndexV>::MaxAbsValueEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    AnnotationEstimator<InputT const &>("MaxAbsValueEstimator", std::move(pAllColumnAnnotations)) {

    _outerBound = static_cast<InputT>(0);
}

template <typename InputT,typename TransformedT, size_t ColIndexV>
Estimator::FitResult MaxAbsValueEstimator<InputT, TransformedT,ColIndexV>::fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) {

    typename BaseType::FitBufferInputType const * const                 pEndBuffer(pBuffer + cBuffer); 

    while(pBuffer != pEndBuffer) {
        InputT const &                                   input(*pBuffer++);

#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4146) 
#endif

        this->_outerBound = std::max(this->_outerBound, static_cast<InputT>(input < 0 ? -input : input)); 

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

    }
    
    return Estimator::FitResult::Continue;
}

template <typename InputT,typename TransformedT, size_t ColIndexV>
Estimator::FitResult MaxAbsValueEstimator<InputT,TransformedT,ColIndexV>::complete_training_impl(void) {

    TransformedT                                maxAbsVal = static_cast<TransformedT>(_outerBound);
                    
    BaseType::add_annotation(std::make_shared<MaxAbsValueAnnotation<InputT, TransformedT>>(std::move(maxAbsVal)), ColIndexV);

    //clear class variables
    this->_outerBound = InputT();

    return Estimator::FitResult::Complete;
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
