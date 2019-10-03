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
///  \class         RobustScalarNormAnnotation
///  \brief         An annotation class which contains the center and scale
///                 for an input column
///
template <typename T, typename TransformedT>
class RobustScalarNormAnnotation : public Annotation {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    TransformedT const                           Median;
    TransformedT const                           Scale;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    RobustScalarNormAnnotation(TransformedT median, TransformedT scale);
    ~RobustScalarNormAnnotation(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(RobustScalarNormAnnotation);
};

/////////////////////////////////////////////////////////////////////////
///  \class         RobustScalarNormEstimator
///  \brief         An AnnotationEstimator class that computes the center and range 
///                 for an input column and creates a RobustScalarNormAnnotation.
///
template <typename InputT,typename TransformedT, size_t ColIndexV>
class RobustScalarNormEstimator : public AnnotationEstimator<InputT const &> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using QRangeType                             = std::tuple<std::float_t, std::float_t>;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    RobustScalarNormEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool with_centering, QRangeType quantile_range);
    ~RobustScalarNormEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(RobustScalarNormEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                             = AnnotationEstimator<InputT const &>;
    using MaxHeapType                          = std::priority_queue<InputT>;
    using MinHeapType                          = std::priority_queue<InputT, std::vector<InputT>, std::greater<InputT> >;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    bool const                                 _with_centering;
    bool const                                 _with_scaling;
    QRangeType const                           _quantile_range;
    

    InputT                                     _upperBound; 
    InputT                                     _lowerBound;
    //two maps to find stream median. max heap to store the smaller half elements, min heap to store the greater half elements 
    MaxHeapType                                _smallerHalf; 
    MinHeapType                                _greaterHalf; 
    
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    Estimator::FitResult fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) override;

    Estimator::FitResult complete_training_impl(void) override;

    void UpdateStreamMedianHeap(InputT const & input);
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
// |  NormAnnotation
// |
// ----------------------------------------------------------------------
template <typename T, typename TransformedT>
RobustScalarNormAnnotation<T, TransformedT>::RobustScalarNormAnnotation(TransformedT median, TransformedT scale) :
    Annotation(this),
    Median(std::move(median)),
    Scale(std::move(scale)) {
    if (scale <= 0)
        throw std::runtime_error("scale must bigger than 0");
}

// ----------------------------------------------------------------------
// |
// |  NormEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT,typename TransformedT, size_t ColIndexV>
RobustScalarNormEstimator<InputT,TransformedT,ColIndexV>::RobustScalarNormEstimator(AnnotationMapsPtr pAllColumnAnnotations,  bool with_centering, QRangeType quantile_range) :
    AnnotationEstimator<InputT const &>("RobustScalarNormEstimator", std::move(pAllColumnAnnotations)),
    _with_centering(std::move(with_centering)),
    _with_scaling(std::get<0>(quantile_range) < static_cast<std::float_t>(0) ? false : true),
    _quantile_range(std::move(quantile_range)) {

    if (_with_scaling) {
        if (!(std::get<0>(_quantile_range) >= 0 && std::get<1>(_quantile_range) <= 100 && std::get<0>(_quantile_range) < std::get<1>(_quantile_range))) {
            throw std::runtime_error("Quantile Range check failed");
        }
    }

    if (_with_scaling) {
        _lowerBound = std::numeric_limits<InputT>::max();
        _upperBound = std::numeric_limits<InputT>::min();
    }
}

template <typename InputT,typename TransformedT, size_t ColIndexV>
Estimator::FitResult RobustScalarNormEstimator<InputT, TransformedT,ColIndexV>::fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) {

    typename BaseType::FitBufferInputType const * const                 pEndBuffer(pBuffer + cBuffer); 

    while(pBuffer != pEndBuffer) {
        InputT const &                                   input(*pBuffer++);

        if (_with_scaling) {
            this->_lowerBound = std::min(this->_lowerBound, input);
            this->_upperBound = std::max(this->_upperBound, input);
        }

        if (_with_centering) {
            UpdateStreamMedianHeap(input);
        }
    }
    
    return Estimator::FitResult::Continue;
}

template <typename InputT,typename TransformedT, size_t ColIndexV>
Estimator::FitResult RobustScalarNormEstimator<InputT,TransformedT,ColIndexV>::complete_training_impl(void) {
    // create the median and range
    TransformedT                                median;
    TransformedT                                scale;
    InputT                                      range;
                       
    //calculate the median
    median = static_cast<TransformedT>(0);  

    size_t heapSize = this->_smallerHalf.size() + this->_greaterHalf.size();
    if (_with_centering) {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#elif (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4244) // conversion from 'unsigned int' to 'unsigned char', possible loss of data
#endif
        if (heapSize % 2 != 0) {
            median = this->_smallerHalf.top();
        } else if (heapSize != 0) {
            median = (this->_smallerHalf.top() + this->_greaterHalf.top()) / 2;
        }

#if (defined __clang__)
#   pragma clang diagnostic pop
#elif (defined _MSC_VER)
#   pragma warning(pop)
#endif

    }

    //calculate the range
    range = _with_scaling ? this->_upperBound - this->_lowerBound : static_cast<InputT>(1);

    //calculate the scale
    std::float_t                                qRangeRatio = 1.0;
    if (_with_scaling) {
        qRangeRatio = (std::get<1>(_quantile_range) - std::get<0>(_quantile_range)) / 100;
        if (qRangeRatio < 0 || qRangeRatio > 1) {
            throw std::runtime_error("Quantile Range check failed");
        }
    }

    scale = static_cast<TransformedT>(range) * static_cast<TransformedT>(qRangeRatio);

    BaseType::add_annotation(std::make_shared<RobustScalarNormAnnotation<InputT, TransformedT>>(std::move(median), std::move(scale)), ColIndexV);

    //clear class variables
    if (_with_scaling) {
        this->_upperBound = InputT();
        this->_lowerBound = InputT();

        this->_greaterHalf = MinHeapType();
        this->_smallerHalf = MaxHeapType();
    }
    
    return Estimator::FitResult::Complete;
}

template <typename InputT,typename TransformedT, size_t ColIndexV>
void RobustScalarNormEstimator<InputT,TransformedT,ColIndexV>::UpdateStreamMedianHeap(InputT const & input) {

    if (_smallerHalf.empty() || input <= _smallerHalf.top()) {
        _smallerHalf.emplace(std::move(input));
    } else {
        _greaterHalf.emplace(std::move(input));
    }

    // unsigned danger
    if (_smallerHalf.size() >= _greaterHalf.size() + 2) {
        _greaterHalf.emplace(std::move(_smallerHalf.top()));
        _smallerHalf.pop();
    } else if (_greaterHalf.size() > _smallerHalf.size()) {
        _smallerHalf.emplace(std::move(_greaterHalf.top()));
        _greaterHalf.pop();
    }
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
