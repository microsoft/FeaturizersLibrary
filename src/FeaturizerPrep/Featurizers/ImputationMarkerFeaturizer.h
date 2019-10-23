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
class ImputationMarkerTransformer : public Components::InferenceOnlyTransformerImpl<T, bool> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(std::is_same<T, typename Traits<T>::nullable_type>::value, "Input should be Nullable Type");
    using Type                              = T;
    using ThisType                          = ImputationMarkerTransformer<Type>;
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
    typename BaseType::TransformedType execute(typename BaseType::InputType input) override {
        if(Traits<T>::IsNull(input)) 
            return true;

        return false;
    }
};

template <typename T>
class ImputationMarkerEstimator : public Components::InferenceOnlyEstimatorImpl<ImputationMarkerTransformer<typename Traits<T>::nullable_type>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = typename Traits<T>::nullable_type;
    using ThisType                          = ImputationMarkerEstimator<Type>;
    using BaseType                          = Components::InferenceOnlyEstimatorImpl<ImputationMarkerTransformer<Type>>;
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
