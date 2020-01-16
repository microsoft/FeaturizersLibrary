// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "TrainingOnlyEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         MaxAbsValueEstimatorName("MaxAbsValueEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         MaxAbsValueAnnotationData
///  \brief         An annotation class which contains the maxAbsVal(maximum absolute value)
///                 for an input column
///
template <typename TransformedT>
class MaxAbsValueAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    TransformedT const                      Value;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    template <typename T>
    MaxAbsValueAnnotationData(T maxAbsVal);
    ~MaxAbsValueAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MaxAbsValueAnnotationData);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         MaxAbsValueTrainingOnlyPolicy
///  \brief         `MaxAbsValueEstimator` implementation details.
///
template <typename T, typename TransformedT>
class MaxAbsValueTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<T>::IsNullableType == false || Traits<T>::IsNativeNullableType, "Support for nullable types has not been implemented yet");
    static_assert(Traits<TransformedT>::IsNullableType == false || Traits<TransformedT>::IsNativeNullableType, "Support for nullable types has not been implemented yet");

    using InputType                         = T;
    using TransformedType                   = TransformedT;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = MaxAbsValueEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MaxAbsValueTrainingOnlyPolicy(void);

    void fit(InputType const &input);
    MaxAbsValueAnnotationData<TransformedType> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    TransformedType                         _max;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \typedef       MaxAbsValueEstimator
///  \brief         A training-only class that computes the maxAbsVal
///                 for an input column and creates a MaxAbsValueAnnotationData.
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using MaxAbsValueEstimator                  = TrainingOnlyEstimatorImpl<Details::MaxAbsValueTrainingOnlyPolicy<InputT, TransformedT>, MaxNumTrainingItemsV>;

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
// |  MaxAbsValueAnnotationData
// |
// ----------------------------------------------------------------------
template <typename TransformedT>
template <typename T>
MaxAbsValueAnnotationData<TransformedT>::MaxAbsValueAnnotationData(T maxAbsValue) :
    Value(
        [&maxAbsValue](void) -> TransformedT {
            if (maxAbsValue < 0)
                throw std::invalid_argument("maxAbsValue");

            if(maxAbsValue > static_cast<T>(std::numeric_limits<TransformedT>::max()))
                throw std::invalid_argument("maxAbsValue overflow");

            return static_cast<TransformedT>(maxAbsValue);
        }()
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::MaxAbsValueTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
Details::MaxAbsValueTrainingOnlyPolicy<InputT, TransformedT>::MaxAbsValueTrainingOnlyPolicy(void) :
    _max(0) {
}

template <typename InputT, typename TransformedT>
void Details::MaxAbsValueTrainingOnlyPolicy<InputT, TransformedT>::fit(InputType const &input) {

#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4146) // unary minus operator applied to unsigned type, result still unsigned
#endif

    _max = std::max(_max, static_cast<TransformedT>(input < 0 ? -input : input));

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
}

template <typename InputT, typename TransformedT>
MaxAbsValueAnnotationData<TransformedT> Details::MaxAbsValueTrainingOnlyPolicy<InputT, TransformedT>::complete_training(void) {
    return MaxAbsValueAnnotationData<TransformedT>(_max);
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
