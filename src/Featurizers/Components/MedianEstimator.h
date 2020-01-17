// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <queue>

#include "TrainingOnlyEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         MedianEstimatorName("MedianEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         MedianAnnotationData
///  \brief         Annotation produced that contains the median value encountered
///                 during training.
///
template <typename T>
class MedianAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    T const                                 Median;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MedianAnnotationData(T median);
    ~MedianAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MedianAnnotationData);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         MedianTrainingOnlyPolicy
///  \brief         `MedianEstimator` implementation details.
///
template <typename InputT, typename TransformedT, bool InterpolateValuesV>
class MedianTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<InputT>::IsNullableType == false || Traits<InputT>::IsNativeNullableType, "'InputT' should not be a nullable type");
    static_assert(Traits<TransformedT>::IsNullableType == false || Traits<TransformedT>::IsNativeNullableType, "'TransformedT' should not be a nullable type");

    using InputType                         = InputT;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = MedianEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    void fit(InputType const &input);
    MedianAnnotationData<TransformedT> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    // Note that a priority_queue is used here over another type, as a priority_queue
    // ensures that sorting only happens when a value is retrieved while sorting would
    // need to happen during insertion for other types. For this algorithm, it means
    // that sorting only happens when we need to rebalance the queues.
    using MaxHeapType                       = std::priority_queue<InputT>;
    using MinHeapType                       = std::priority_queue<InputT, std::vector<InputT>, std::greater<InputT>>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    MaxHeapType                             _smaller;
    MinHeapType                             _larger;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    TransformedT _get_interpolated_value(std::true_type /*supports Interpolated values*/);
    TransformedT _get_interpolated_value(std::false_type /*supports Interpolated values*/);
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \typedef       MedianEstimator
///  \brief         An `Estimator` that computes the median value encountered
///                 during training.
///
template <
    typename InputT,
    typename TransformedT=InputT,
    bool InterpolateValuesV=true,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using MedianEstimator                       = TrainingOnlyEstimatorImpl<Details::MedianTrainingOnlyPolicy<InputT, TransformedT, InterpolateValuesV>, MaxNumTrainingItemsV>;

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
// |  MedianAnnotationData
// |
// ----------------------------------------------------------------------
template <typename T>
MedianAnnotationData<T>::MedianAnnotationData(T median) :
    Median(std::move(median)) {
}

// ----------------------------------------------------------------------
// |
// |  Details::MedianTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, bool InterpolateValuesV>
void Details::MedianTrainingOnlyPolicy<InputT, TransformedT, InterpolateValuesV>::fit(InputType const &input) {
    if(_smaller.empty() || input <= _smaller.top())
        _smaller.emplace(input);
    else
        _larger.emplace(input);

    // Rebalance if necessary
    if(_smaller.size() >= _larger.size() + 2) {
        _larger.emplace(_smaller.top());
        _smaller.pop();
    }
    else if(_larger.size() > _smaller.size()) {
        _smaller.emplace(_larger.top());
        _larger.pop();
    }
}

template <typename InputT, typename TransformedT, bool InterpolateValuesV>
MedianAnnotationData<TransformedT> Details::MedianTrainingOnlyPolicy<InputT, TransformedT, InterpolateValuesV>::complete_training(void) {
    size_t const                            numElements(_smaller.size() + _larger.size());

    if(numElements == 0)
        throw std::runtime_error("No elements were provided during training");

    TransformedT                            median;

#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127) // conditional expression is constant
#endif

    if(InterpolateValuesV == false || numElements & 1) {
        assert(_smaller.empty() == false);
        assert(InterpolateValuesV == false || _smaller.size() == _larger.size() + 1);

        median = static_cast<TransformedT>(_smaller.top());
    }
    else
        median = this->_get_interpolated_value(std::integral_constant<bool, InterpolateValuesV>());

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

    // Clean up after ourselves
    _smaller = MaxHeapType();
    _larger = MinHeapType();

    return median;
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, bool InterpolateValuesV>
TransformedT Details::MedianTrainingOnlyPolicy<InputT, TransformedT, InterpolateValuesV>::_get_interpolated_value(std::true_type /*supports Interpolated values*/) {
    assert(_smaller.empty() == false);

    InputT const                            greater(_larger.empty() ? 0 : _larger.top());

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

    return static_cast<TransformedT>((static_cast<double>(_smaller.top()) + greater) / 2);

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
}

template <typename InputT, typename TransformedT, bool InterpolateValuesV>
TransformedT Details::MedianTrainingOnlyPolicy<InputT, TransformedT, InterpolateValuesV>::_get_interpolated_value(std::false_type /*supports Interpolated values*/) {
    throw std::runtime_error("This should never be called");
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
