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
///  \class         TimeSeriesFrequencyAnnotation
///  \brief         This is an annotation class which holds the frequency
///                 of TimeSeries
///
class TimeSeriesFrequencyAnnotation : public Annotation {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using FrequencyType                     = std::chrono::system_clock::duration;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    FrequencyType                           Value;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TimeSeriesFrequencyAnnotation(FrequencyType value);
    ~TimeSeriesFrequencyAnnotation(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TimeSeriesFrequencyAnnotation);
};

/////////////////////////////////////////////////////////////////////////
///  \class         TimeSeriesFrequencyEstimator
///  \brief         This class computes the frequency of timeseries by keeping
///                 track of minimum difference(frequency) observed between two
///                 timepoints for a given grain. Note that frequency is same for
///                 complete dataset.
///
class TimeSeriesFrequencyEstimator : public FitEstimator<std::tuple<std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TimeSeriesFrequencyEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~TimeSeriesFrequencyEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TimeSeriesFrequencyEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using KeyType                           = std::vector<std::string>;
    using ColsToImputeType                  = std::vector<nonstd::optional<std::string>>;
    using BaseType                          = FitEstimator<std::tuple<std::chrono::system_clock::time_point, KeyType, ColsToImputeType>>;
    using FrequencyType                     = std::chrono::system_clock::duration;
    using TimePointType                     = std::chrono::system_clock::time_point;
    using MapType                           = std::map<KeyType, TimePointType>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    MapType                                 _grainTimePointTracker;
    FrequencyType                           _minFrequency;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;

    FitResult fit_impl(typename BaseType::InputType const *pBuffer, size_t cBuffer) override;

    void complete_training_impl(void) override;
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
// |  TimeSeriesFrequencyAnnotation
// |
// ----------------------------------------------------------------------
inline TimeSeriesFrequencyAnnotation::TimeSeriesFrequencyAnnotation(TimeSeriesFrequencyAnnotation::FrequencyType value) :
    Value(std::move(value)) {
}

// ----------------------------------------------------------------------
// |
// |  TimeSeriesFrequencyEstimator
// |
// ----------------------------------------------------------------------
inline TimeSeriesFrequencyEstimator::TimeSeriesFrequencyEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("TimeSeriesFrequencyEstimator", std::move(pAllColumnAnnotations))
    ,_minFrequency(std::chrono::system_clock::duration::max().count()){
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
inline bool TimeSeriesFrequencyEstimator::begin_training_impl(void) /*override*/ {
    return true;
}

inline FitResult TimeSeriesFrequencyEstimator::fit_impl(typename BaseType::InputType const *pBuffer, size_t cBuffer) {
    typename BaseType::InputType const * const          pEndBuffer(pBuffer + cBuffer);

    while(pBuffer != pEndBuffer) {
        std::tuple<std::chrono::system_clock::time_point, KeyType, ColsToImputeType> const &        input(*pBuffer++);
        TimePointType const &                                           timeValue (std::get<0>(input));
        KeyType const &                                                 keyValues (std::get<1>(input));
        typename MapType::iterator const                                iter(_grainTimePointTracker.find(keyValues));

        if(iter == _grainTimePointTracker.end())
            _grainTimePointTracker.insert(std::make_pair(keyValues, timeValue));
        else
        {
            TimePointType const &                                       lastObservedTimeValue(iter->second);
            if(lastObservedTimeValue >= timeValue)
                throw std::runtime_error("Input stream not in chronological order.");

            FrequencyType                                               currentFrequency(timeValue-lastObservedTimeValue);
            if(currentFrequency <= _minFrequency)
                _minFrequency = currentFrequency;

            iter->second = timeValue;
        }
    }

    return FitResult::Continue;
}

inline void TimeSeriesFrequencyEstimator::complete_training_impl(void) {

    BaseType::add_annotation(std::make_shared<TimeSeriesFrequencyAnnotation>(std::move(_minFrequency)), 0);
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
