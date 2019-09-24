// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../../Archive.h"
#include "../../Featurizer.h"
#include "../../Traits.h"
#include "../Components/PipelineExecutionEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

/////////////////////////////////////////////////////////////////////////
///  \class         TimeSeriesMedianAnnotation
///  \brief         This is an annotation class which holds the Median
///                 per grain for TimeSeries
///
class TimeSeriesMedianAnnotation : public Annotation {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using KeyType                           = std::vector<std::string>;
    using ValueType                         = std::vector<double_t>;
    using MedianMapType                     = std::map<KeyType,ValueType>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    MedianMapType const                     Value;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TimeSeriesMedianAnnotation(std::map<KeyType,ValueType> value);
    ~TimeSeriesMedianAnnotation(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TimeSeriesMedianAnnotation);
};

/////////////////////////////////////////////////////////////////////////
///  \class         TimeSeriesMedianEstimator
///  \brief         This class computes the median per grain.
///                 .
///
class TimeSeriesMedianEstimator : public AnnotationEstimator<std::tuple<std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>> const &> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TimeSeriesMedianEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~TimeSeriesMedianEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TimeSeriesMedianEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using KeyType                           = std::vector<std::string>;
    using ColsToImputeType                  = std::vector<nonstd::optional<std::string>>;
    using BaseType                          = AnnotationEstimator<std::tuple<std::chrono::system_clock::time_point, KeyType, ColsToImputeType> const &>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    // _aggregateTracker is used to track sum in fit, while countTracker tracks count.
    // However, in complete_training_impl, we divide values(sum) in _aggregateTracker
    // by corresponding counts and after that it tracks median.
    // Annotation is created using _aggregateTracker.
    std::map<KeyType,std::vector<double_t>>  _aggregateTracker;
    std::map<KeyType,std::vector<int64_t>>   _countTracker;

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
// |  TimeSeriesMedianAnnotation
// |
// ----------------------------------------------------------------------
TimeSeriesMedianAnnotation::TimeSeriesMedianAnnotation(TimeSeriesMedianAnnotation::MedianMapType value) :
    Annotation(this),
    Value(std::move(value)) {
}

// ----------------------------------------------------------------------
// |
// |  TimeSeriesMedianEstimator
// |
// ----------------------------------------------------------------------
TimeSeriesMedianEstimator::TimeSeriesMedianEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    AnnotationEstimator<std::tuple<std::chrono::system_clock::time_point, KeyType, ColsToImputeType> const &>("TimeSeriesMedianEstimator", std::move(pAllColumnAnnotations))
    {
}

Estimator::FitResult TimeSeriesMedianEstimator::fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) {
    typename BaseType::FitBufferInputType const * const                 pEndBuffer(pBuffer + cBuffer);
    while(pBuffer != pEndBuffer) {
        std::tuple<std::chrono::system_clock::time_point, KeyType, ColsToImputeType> const &        input(*pBuffer++);
        KeyType const &                                                 key (std::get<1>(input));
        ColsToImputeType const &                                        colValues (std::get<2>(input));

        if(_aggregateTracker.find(key) == _aggregateTracker.end()) {
            _aggregateTracker.insert(std::make_pair(key, std::vector<double_t>(colValues.size(), 0.0)));
            _countTracker.insert(std::make_pair(key, std::vector<int64_t>(colValues.size(), 0)));
        }

        for(std::size_t i=0; i< colValues.size(); ++i) {
            if(Traits<std::string>::IsNull(colValues[i]))
                continue;

            _aggregateTracker[key][i] += Traits<std::double_t>::FromString(Traits<std::string>::GetNullableValue(colValues[i]));
            _countTracker[key][i] += 1;
        }
    }

    return Estimator::FitResult::Continue;
}

Estimator::FitResult TimeSeriesMedianEstimator::complete_training_impl(void) {
    // Note that this class reuses _aggregateTracker to calculate median values before
    // moving it to the annotation.
    for(auto & kvp: _aggregateTracker) {
        KeyType const & key = kvp.first;
        for(std::size_t i=0; i< kvp.second.size(); ++i) {
            auto count = _countTracker[key][i];
            if(count == 0)
                throw std::runtime_error("No valid value found for median computation.");
            kvp.second[i] /= count;
        }
    }
    _countTracker.clear();

    BaseType::add_annotation(std::make_shared<TimeSeriesMedianAnnotation>(std::move(_aggregateTracker)), 0);
    return Estimator::FitResult::Complete;
}


} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
