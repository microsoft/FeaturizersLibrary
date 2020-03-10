// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>

#include "TrainingOnlyEstimatorImpl.h"
#include "FrequencyEstimator.h"
#include "GrainEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

// TODO: This should be removed in favor of the StatisticalMetricsEstimator

static constexpr char const * const         FrequencyMinimumEstimatorName("FrequencyMinimumEstimator");
static constexpr char const * const         GrainedFrequencyEstimatorName("GrainedFrequencyEstimator");

using GrainedFrequencyEstimator = GrainEstimatorImpl<std::string, FrequencyEstimator<>>;

/////////////////////////////////////////////////////////////////////////
///  \class         FrequencyMinimumAnnotation
///  \brief         This is an annotation class which holds the frequency
///                 of TimeSeries
///
class FrequencyMinimumAnnotation{
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
    FrequencyMinimumAnnotation(FrequencyType value);
    ~FrequencyMinimumAnnotation(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FrequencyMinimumAnnotation);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         FrequencyMinimumTrainingOnlyPolicy
///  \brief         `FrequencyMinimumEstimator` implementation details.
///
template <typename EstimatorT>
class FrequencyMinimumTrainingOnlyPolicy {
public:

    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                     = std::tuple<std::string, std::chrono::system_clock::time_point>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = FrequencyMinimumEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    FrequencyMinimumTrainingOnlyPolicy(void);

    void fit(InputType const &input);
    FrequencyMinimumAnnotation complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using FrequencyType                     = std::chrono::system_clock::duration;
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    GrainedFrequencyEstimator                      _estimator;
};
}
/////////////////////////////////////////////////////////////////////////
///  \typedef       FrequencyMinimumEstimator
///  \brief         A training-only class that finds the min, max
///
template <
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class FrequencyMinimumEstimator :
    public TrainingOnlyEstimatorImpl<
        Details::FrequencyMinimumTrainingOnlyPolicy<FrequencyMinimumEstimator<MaxNumTrainingItemsV>>,
        MaxNumTrainingItemsV
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        TrainingOnlyEstimatorImpl<
            Details::FrequencyMinimumTrainingOnlyPolicy<FrequencyMinimumEstimator<MaxNumTrainingItemsV>>,
            MaxNumTrainingItemsV
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    FrequencyMinimumEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);

    ~FrequencyMinimumEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FrequencyMinimumEstimator);

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
// |  FrequencyMinimumAnnotation
// |
// ----------------------------------------------------------------------
inline FrequencyMinimumAnnotation::FrequencyMinimumAnnotation(FrequencyMinimumAnnotation::FrequencyType value) :
    Value(std::move(value)) {
}

// ----------------------------------------------------------------------
// |
// |  FrequencyMinimumEstimator
// |
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
FrequencyMinimumEstimator<MaxNumTrainingItemsV>::FrequencyMinimumEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex)) {
}

// ----------------------------------------------------------------------
// |
// |  Details::FrequencyMinimumTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename EstimatorT>
Details::FrequencyMinimumTrainingOnlyPolicy<EstimatorT>::FrequencyMinimumTrainingOnlyPolicy(void) :
    _estimator(GrainedFrequencyEstimator(std::make_shared<AnnotationMaps>(EstimatorT.get_column_annotations()),0)) {
        _estimator.begin_training();
}

template <typename EstimatorT>
void Details::FrequencyMinimumTrainingOnlyPolicy<EstimatorT>::fit(InputType const &input) {
    _estimator.fit(input);
}

template <typename EstimatorT>
FrequencyMinimumAnnotation Details::FrequencyMinimumTrainingOnlyPolicy<EstimatorT>::complete_training(void) {
    GrainEstimatorAnnotation<std::string> const & data(EstimatorT.get_annotation_data(EstimatorT.get_column_annotations(), EstimatorT.get_column_index(), GrainedFrequencyEstimatorName));
    AnnotationMap annotation(data.Annotations);
    auto it = annotation.begin();
    FrequencyType freq(std::chrono::system_clock::duration::max().count());
    while (it != annotation.end()) {
        if (freq >= it->second->Value) {
            freq = it->second->Value;
        }
    }
    return FrequencyMinimumAnnotation(std::move(freq));
}



} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
