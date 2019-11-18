// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Traits.h"
#include "Components/InferenceOnlyFeaturizerImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         MissingDummiesTransformer
///  \brief         if input is Null, return 1. Otherwise return 0
///
///                 Considering this transformer is almost identical to ImputationMarkerTransformer,
///                 there are several ways to do this
///                 1. Combine these two transformers into one and implement execute() based on the output type,
///                    if the output type is bool, return true or false, if the output type is int, return 0 or 1
///
///                    However, we would want two different names for these two different transformers so this won't work
///
///                 2. Create a common base class for these two transformers
///
///                    This is a overkill for such a simple feature we want so we would create a lot unnecessary complications
///
///
///                 As a result, we would just create another class with a slightly different return
///
template <typename T>
class MissingDummiesTransformer : public Components::InferenceOnlyTransformerImpl<T, std::int8_t> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(std::is_same<T, typename Traits<T>::nullable_type>::value, "Input should be Nullable Type");

    using Type                              = T;
    using BaseType                          = Components::InferenceOnlyTransformerImpl<Type, std::int8_t>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MissingDummiesTransformer(void) = default;
    MissingDummiesTransformer(Archive &ar);

    ~MissingDummiesTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MissingDummiesTransformer);
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems when the function is defined outside of the declaration
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        callback(Traits<T>::IsNull(input) ? 1 : 0);
    }
};

template <typename T>
class MissingDummiesEstimator : public Components::InferenceOnlyEstimatorImpl<MissingDummiesTransformer<typename Traits<T>::nullable_type>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = typename Traits<T>::nullable_type;
    using BaseType                          = Components::InferenceOnlyEstimatorImpl<MissingDummiesTransformer<Type>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MissingDummiesEstimator(AnnotationMapsPtr pAllCoumnAnnotations);
    ~MissingDummiesEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MissingDummiesEstimator);
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
// |  MissingDummiesEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
MissingDummiesTransformer<T>::MissingDummiesTransformer(Archive &ar) :
    BaseType(ar) {
}

// ----------------------------------------------------------------------
// |
// |  MissingDummiesEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
MissingDummiesEstimator<T>::MissingDummiesEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("MissingDummiesEstimator", std::move(pAllColumnAnnotations)) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
