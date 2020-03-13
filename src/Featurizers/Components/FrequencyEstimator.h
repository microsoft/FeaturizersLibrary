// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>

#include "TrainingOnlyEstimatorImpl.h"
#include "GrainFeaturizerImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

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
    FrequencyType               _frequency;
    nonstd::optional<InputType> _lastObserved;
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

// Normally we want the featurizer name at the top of the file, but GrainFeaturizers are just type defs, so we want the name next to it.
static constexpr char const * const         GrainFrequencyEstimatorName("GrainFrequencyEstimator");
template <
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using GrainedFrequencyEstimator = GrainEstimatorImpl<std::vector<std::string>, FrequencyEstimator<MaxNumTrainingItemsV>>;


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
    _frequency(std::chrono::system_clock::duration::max().count()) {
}

void Details::FrequencyTrainingOnlyPolicy::fit(InputType const &input) {
    if (_lastObserved.has_value()) {
        InputType const & lastObservedValue(*_lastObserved);
        if (lastObservedValue >= input) {
            throw std::runtime_error("Input stream not in chronological order.");
        }
        FrequencyType currFrequency(input - lastObservedValue);
        if (currFrequency <= _frequency) {
            _frequency = currFrequency;
        }
    }
    _lastObserved = input;
}

FrequencyAnnotation Details::FrequencyTrainingOnlyPolicy::complete_training(void) {
    if (_frequency == std::chrono::system_clock::duration(std::chrono::system_clock::duration::max().count())) {
        throw std::runtime_error("Need to provide more than one value to get a frequency");
    }
    return FrequencyAnnotation(std::move(_frequency));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
