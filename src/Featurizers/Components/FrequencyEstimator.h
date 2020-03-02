// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>

#include "TrainingOnlyEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

// TODO: This should be removed in favor of the StatisticalMetricsEstimator

static constexpr char const * const         FrequencyEstimatorName("FrequencyEstimator");



/////////////////////////////////////////////////////////////////////////
///  \class         FrequencyAnnotation
///  \brief         This is an annotation class which holds the frequency
///                 of TimeSeries
///
class FrequencyAnnotation{
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
    FrequencyAnnotation(FrequencyType value);
    ~FrequencyAnnotation(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FrequencyAnnotation);
};

namespace Details {
    
/////////////////////////////////////////////////////////////////////////
///  \class         FrequencyTrainingOnlyPolicy
///  \brief         `FrequencyEstimator` implementation details.
///
class FrequencyTrainingOnlyPolicy {
public:

    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                     = std::chrono::system_clock::time_point;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = FrequencyEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    FrequencyTrainingOnlyPolicy(void);

    void fit(InputType const &input);
    FrequencyAnnotation complete_training(void);

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
    FrequencyType _frequency;
    InputType _lastObserved;

    bool _hasSeenValues;
};
}

/////////////////////////////////////////////////////////////////////////
///  \typedef       FrequencyEstimator
///  \brief         A training-only class that finds the min, max
///
template <
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using FrequencyEstimator                       = TrainingOnlyEstimatorImpl<Details::FrequencyTrainingOnlyPolicy, MaxNumTrainingItemsV>;


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
// |  FrequencyAnnotation
// |
// ----------------------------------------------------------------------
inline FrequencyAnnotation::FrequencyAnnotation(FrequencyAnnotation::FrequencyType value) :
    Value(std::move(value)) {
}

// ----------------------------------------------------------------------
// |
// |  Details::FrequencyTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
Details::FrequencyTrainingOnlyPolicy::FrequencyTrainingOnlyPolicy(void) :
    _frequency(std::chrono::system_clock::duration::max().count()),
    _hasSeenValues(false) {
}

void Details::FrequencyTrainingOnlyPolicy::fit(InputType const &input) {
    if (!_hasSeenValues) {
        _lastObserved = input;
        _hasSeenValues = true;
        return;
    }
    if (_lastObserved >= input) {
        throw std::runtime_error("Input stream not in chronological order.");
    }
    FrequencyType currFrequency(input - _lastObserved);
    if (currFrequency <= _frequency) {
        _frequency = currFrequency;
    }
}

FrequencyAnnotation Details::FrequencyTrainingOnlyPolicy::complete_training(void) {
    return FrequencyAnnotation(std::move(_frequency));
}


} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft