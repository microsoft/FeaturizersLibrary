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

static constexpr char const * const         MinMaxEstimatorName("MinMaxEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         MinMaxAnnotationData
///  \brief         An annotation class which contains the min feature and the max
///                 for an input column
///
template <typename T>
class MinMaxAnnotationData {
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
    MinMaxAnnotationData(T min, T max);
    ~MinMaxAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MinMaxAnnotationData);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         MinMaxTrainingOnlyPolicy
///  \brief         `MinMaxEstimator` implementation details.
///
template <typename T>
class MinMaxTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<T>::IsNullableType == false || Traits<T>::IsNativeNullableType, "Support for nullable types has not been implemented yet");

    using InputType                         = T;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = MinMaxEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MinMaxTrainingOnlyPolicy(void);

    void fit(InputType const &input);
    MinMaxAnnotationData<T> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    InputType                               _min;
    InputType                               _max;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \typedef       MinMaxEstimator
///  \brief         A training-only class that finds the min, max
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using MinMaxEstimator                       = TrainingOnlyEstimatorImpl<Details::MinMaxTrainingOnlyPolicy<InputT>, MaxNumTrainingItemsV>;

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
// |  MinMaxAnnotationData
// |
// ----------------------------------------------------------------------
template <typename T>
MinMaxAnnotationData<T>::MinMaxAnnotationData(T min, T max) :
    Min(std::move(min)),
    Max(std::move(max)) {
    if(Min > Max)
        throw std::invalid_argument("min is > max");
}

// ----------------------------------------------------------------------
// |
// |  Details::MinMaxTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::MinMaxTrainingOnlyPolicy<T>::MinMaxTrainingOnlyPolicy(void) :
    // didn't use std::numeric_limits::min() because for float this is not the smallest possible value
    // but the smallest value closest to 0 instead
    _min(std::numeric_limits<T>::max()),
    _max(std::numeric_limits<T>::lowest()) {
}

template <typename T>
void Details::MinMaxTrainingOnlyPolicy<T>::fit(InputType const &input) {
    if(input < _min)
        _min = input;
    if(input > _max)
        _max = input;
}

template <typename T>
MinMaxAnnotationData<T> Details::MinMaxTrainingOnlyPolicy<T>::complete_training(void) {
    return MinMaxAnnotationData<T>(std::move(_min), std::move(_max));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
