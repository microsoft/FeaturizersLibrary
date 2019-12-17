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
///  \class         ImputationMarkerTransformer
///  \brief         if input is Null, return true. Otherwise return false
///
template <typename T>
class ImputationMarkerTransformer : public Components::InferenceOnlyTransformerImpl<typename MakeNullableType<T>::type, bool> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = typename MakeNullableType<T>::type;
    using BaseType                          = Components::InferenceOnlyTransformerImpl<Type, bool>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ImputationMarkerTransformer(void) = default;
    ImputationMarkerTransformer(Archive &ar);

    ~ImputationMarkerTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ImputationMarkerTransformer);

    // MSVC has problems when the function is defined outside of the declaration
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {

        callback(Traits<Type>::IsNull(input));
    }
};

template <typename T>
class ImputationMarkerEstimator : public Components::InferenceOnlyEstimatorImpl<ImputationMarkerTransformer<T>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = typename Traits<T>::nullable_type;
    using BaseType                          = Components::InferenceOnlyEstimatorImpl<ImputationMarkerTransformer<T>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ImputationMarkerEstimator(AnnotationMapsPtr pAllCoumnAnnotations);
    ~ImputationMarkerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ImputationMarkerEstimator);
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
// |  ImputationMarkerEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
ImputationMarkerTransformer<T>::ImputationMarkerTransformer(Archive &ar) :
    BaseType(ar) {
}

// ----------------------------------------------------------------------
// |
// |  ImputationMarkerEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
ImputationMarkerEstimator<T>::ImputationMarkerEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("ImputationMarkerEstimator", std::move(pAllColumnAnnotations)) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
