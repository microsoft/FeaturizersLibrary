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
///  \class        ImputationMarkerTraits
///  \brief         Traits for mapping the input/output types for the ImputationMarker.
///                 This allows us to only change one place if typings need to change.
///
template <typename TransformedT>
struct ImputationMarkerTraits{
    using InputType = typename Traits<TransformedT>::nullable_type;

    static_assert(Traits<InputType>::IsNullableType, "'InputT' must be a nullable type");
};

/////////////////////////////////////////////////////////////////////////
///  \class         ImputationMarkerTransformer
///  \brief         if input is Null, return true. Otherwise return false
///
template <typename TransformedT>
class ImputationMarkerTransformer : public Components::InferenceOnlyTransformerImpl<typename ImputationMarkerTraits<TransformedT>::InputType, bool> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = typename ImputationMarkerTraits<TransformedT>::InputType;
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
template <typename TransformedT>
ImputationMarkerTransformer<TransformedT>::ImputationMarkerTransformer(Archive &ar) :
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
