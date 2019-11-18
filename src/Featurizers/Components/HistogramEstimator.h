// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <unordered_map>

#include "TrainingOnlyEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         HistogramEstimatorName("HistogramEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         HistogramAnnotationData
///  \brief         This is an annotation class which holds all the values and corresponding
///                 frequencies for an input column.
///
template <typename T>
class HistogramAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Histogram                         = std::unordered_map<T, std::uint32_t>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    Histogram const                         Value;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    HistogramAnnotationData(Histogram value);
    ~HistogramAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(HistogramAnnotationData);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         HistogramTrainingOnlyPolicy
///  \brief         `HistogramEstimator` implementation details.
///
template <typename T>
class HistogramTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = T;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = HistogramEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    void fit(InputType const &input);
    HistogramAnnotationData<T> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using Histogram                         = typename HistogramAnnotationData<T>::Histogram;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    Histogram                               _histogram;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \typedef       HistogramEstimator
///  \brief         This class computes the histogram for an input column
///                 and creates a HistogramAnnotationData.
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using HistogramEstimator                    = TrainingOnlyEstimatorImpl<Details::HistogramTrainingOnlyPolicy<InputT>, MaxNumTrainingItemsV>;

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
// |  HistogramAnnotationData
// |
// ----------------------------------------------------------------------
template <typename T>
HistogramAnnotationData<T>::HistogramAnnotationData(Histogram value) :
    Value(std::move(value)) {
}

// ----------------------------------------------------------------------
// |
// |  Details::HistogramTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
void Details::HistogramTrainingOnlyPolicy<T>::fit(InputType const &input) {
    typename Histogram::mapped_type &   count(
        [this, &input](void) -> typename Histogram::mapped_type & {
            typename Histogram::iterator                                    iter(_histogram.find(input));

            if(iter == _histogram.end()) {
                std::pair<typename Histogram::iterator, bool> const         result(_histogram.insert(std::make_pair(input, 0)));

                iter = result.first;
            }

            return iter->second;
        }()
    );

    count += 1;
}

template <typename T>
HistogramAnnotationData<T> Details::HistogramTrainingOnlyPolicy<T>::complete_training(void) {
    return HistogramAnnotationData<T>(std::move(_histogram));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
