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

// TODO: This should be split into 2 estimators

static constexpr char const * const         RobustScalarNormEstimatorName("RobustScalarNormEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         RobustScalarNormAnnotationData
///  \brief         An annotation class which contains the center and scale
///                 for an input column
///
template <typename T>
class RobustScalarNormAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    T const                                 Median;
    T const                                 Scale;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    RobustScalarNormAnnotationData(T median, T scale);
    ~RobustScalarNormAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(RobustScalarNormAnnotationData);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         RobustScalarNormTrainingOnlyPolicy
///  \brief         `RobustScalarNormEstimator` implementation details.
///
template <typename InputT, typename TransformedT>
class RobustScalarNormTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = InputT;
    using ScalingParameters                 = std::tuple<float, float>;
    using OptionalScalingParameters         = nonstd::optional<ScalingParameters>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = RobustScalarNormEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    RobustScalarNormTrainingOnlyPolicy(bool withCentering, OptionalScalingParameters optionalScalingParameters);

    void fit(InputType const &input);
    RobustScalarNormAnnotationData<TransformedT> complete_training(void);

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
    bool const                              _withCentering;
    OptionalScalingParameters const         _optionalScalingParameters;

    InputT                                  _lowerBound;
    InputT                                  _upperBound;

    MaxHeapType                             _smallerHalf;
    MinHeapType                             _greaterHalf;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         RobustScalarNormEstimator
///  \brief         An `Estimator` class that computes the center and range
///                 for an input column and creates a `RobustScalarNormAnnotationData`.
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class RobustScalarNormEstimator : public TrainingOnlyEstimatorImpl<Details::RobustScalarNormTrainingOnlyPolicy<InputT, TransformedT>, MaxNumTrainingItemsV> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TrainingOnlyEstimatorImpl<Details::RobustScalarNormTrainingOnlyPolicy<InputT, TransformedT>, MaxNumTrainingItemsV>;
    using OptionalScalingParameters         = typename Details::RobustScalarNormTrainingOnlyPolicy<InputT, TransformedT>::OptionalScalingParameters;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    RobustScalarNormEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool withCentering, OptionalScalingParameters optionalScalingParameters);
    ~RobustScalarNormEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(RobustScalarNormEstimator);
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
// |  RobustScalarNormAnnotationData
// |
// ----------------------------------------------------------------------
template <typename T>
RobustScalarNormAnnotationData<T>::RobustScalarNormAnnotationData(T median, T scale) :
    Median(std::move(median)),
    Scale(
        std::move(
            [&scale](void) -> T & {
                if(scale < 0)
                    throw std::invalid_argument("scale");

                return scale;
            }()
        )
    ) {
}

// ----------------------------------------------------------------------
// |
// |  RobustScalarNormEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
RobustScalarNormEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::RobustScalarNormEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool withCentering, OptionalScalingParameters optionalScalingParameters) :
    BaseType(
        std::move(pAllColumnAnnotations),
        std::move(colIndex),
        true,
        std::move(withCentering),
        std::move(optionalScalingParameters)
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::RobustScalarNormTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
Details::RobustScalarNormTrainingOnlyPolicy<InputT, TransformedT>::RobustScalarNormTrainingOnlyPolicy(bool withCentering, OptionalScalingParameters optionalScalingParameters) :
    _withCentering(std::move(withCentering)),
    _optionalScalingParameters(
        std::move(
            [&optionalScalingParameters](void) -> OptionalScalingParameters & {
                if(
                    optionalScalingParameters
                    && (
                        std::get<0>(*optionalScalingParameters) < 0.0f
                        || std::get<0>(*optionalScalingParameters) > 100.0f
                        || std::get<1>(*optionalScalingParameters) < 0.0f
                        || std::get<1>(*optionalScalingParameters) > 100.0f
                        || std::get<0>(*optionalScalingParameters) > std::get<1>(*optionalScalingParameters)
                    )
                )
                    throw std::invalid_argument("optionalScalingParameters");

                return optionalScalingParameters;
            }()
        )
    ),
    _lowerBound(std::numeric_limits<decltype(_lowerBound)>::max()),
    _upperBound(std::numeric_limits<decltype(_upperBound)>::min()) {
}

template <typename InputT, typename TransformedT>
void Details::RobustScalarNormTrainingOnlyPolicy<InputT, TransformedT>::fit(InputType const &input) {
    if(_withCentering) {
        if(_smallerHalf.empty() || input <= _smallerHalf.top())
            _smallerHalf.emplace(input);
        else
            _greaterHalf.emplace(input);

        // Rebalance if necessary
        if(_smallerHalf.size() >= _greaterHalf.size() + 2) {
            _greaterHalf.emplace(_smallerHalf.top());
            _smallerHalf.pop();
        }
        else if(_greaterHalf.size() > _smallerHalf.size()) {
            _smallerHalf.emplace(_greaterHalf.top());
            _greaterHalf.pop();
        }
    }

    if(_optionalScalingParameters) {
        this->_lowerBound = std::min(this->_lowerBound, input);
        this->_upperBound = std::max(this->_upperBound, input);
    }
}

template <typename InputT, typename TransformedT>
RobustScalarNormAnnotationData<TransformedT> Details::RobustScalarNormTrainingOnlyPolicy<InputT, TransformedT>::complete_training(void) {
    TransformedT                            median(static_cast<TransformedT>(0.0));

    if(_withCentering) {
        size_t const                        heapSize(_smallerHalf.size() + _greaterHalf.size());

        if(heapSize & 1) {
            assert(_smallerHalf.empty() == false);
            assert(_smallerHalf.size() == _greaterHalf.size() + 1);

            median = static_cast<TransformedT>(_smallerHalf.top());
        }
        else {
            InputT const                    greater(_greaterHalf.empty() ? 0 : _greaterHalf.top());

            assert(_smallerHalf.empty() == false);
            median = static_cast<TransformedT>(_smallerHalf.top() + greater) / 2;
        }

        // Clean up after ourselves
        _smallerHalf = MaxHeapType();
        _greaterHalf = MinHeapType();
    }

    assert(_smallerHalf.empty());
    assert(_greaterHalf.empty());

    TransformedT                            scale(static_cast<TransformedT>(1.0));

    if(_optionalScalingParameters) {
        float const                         qRangeRatio((std::get<1>(*_optionalScalingParameters) - std::get<0>(*_optionalScalingParameters)) / 100.0f);

        assert(qRangeRatio >= 0.0f && qRangeRatio <= 1.0f);

        scale = static_cast<TransformedT>(_upperBound - _lowerBound) * static_cast<TransformedT>(qRangeRatio);
    }

    return RobustScalarNormAnnotationData<TransformedT>(std::move(median), std::move(scale));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
