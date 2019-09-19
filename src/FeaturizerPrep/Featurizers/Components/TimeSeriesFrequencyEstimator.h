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
class TimeSeriesFrequencyEstimator : public AnnotationEstimator<std::tuple<std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>> const &> {
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
    using BaseType                          = AnnotationEstimator<std::tuple<std::chrono::system_clock::time_point, KeyType, ColsToImputeType> const &>;
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
// |  TimeSeriesFrequencyAnnotation
// |
// ----------------------------------------------------------------------
TimeSeriesFrequencyAnnotation::TimeSeriesFrequencyAnnotation(TimeSeriesFrequencyAnnotation::FrequencyType value) :
    Annotation(this),
    Value(std::move(value)) {
}

// ----------------------------------------------------------------------
// |
// |  TimeSeriesFrequencyEstimator
// |
// ----------------------------------------------------------------------
TimeSeriesFrequencyEstimator::TimeSeriesFrequencyEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    AnnotationEstimator<std::tuple<std::chrono::system_clock::time_point, KeyType, ColsToImputeType> const &>("TimeSeriesFrequencyEstimator", std::move(pAllColumnAnnotations))
    ,_minFrequency(std::chrono::system_clock::duration::max().count()){
}

Estimator::FitResult TimeSeriesFrequencyEstimator::fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) {
    std::ignore = pBuffer;
    std::ignore = cBuffer;

    return Estimator::FitResult::Continue;
}

Estimator::FitResult TimeSeriesFrequencyEstimator::complete_training_impl(void) {

    BaseType::add_annotation(std::make_shared<TimeSeriesFrequencyAnnotation>(std::move(_minFrequency)), 0);
    return Estimator::FitResult::Complete;
}


} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
