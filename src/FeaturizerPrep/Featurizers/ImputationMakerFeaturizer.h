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
///  \class         ImputationMakerTransformer
///  \brief         if input is Null, return true. Otherwise return false
///
template <typename T>
class ImputationMakerTransformer : public Components::InferenceOnlyTransformerImpl<T, bool> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(std::is_same<T, typename Traits<T>::nullable_type>::value, "Input should be Nullable Type");
    using Type                              = T;
    using ThisType                          = ImputationMakerTransformer<Type>;
    using BaseType                          = Components::InferenceOnlyTransformerImpl<Type, bool>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ImputationMakerTransformer(void) = default;
    ImputationMakerTransformer(Archive &ar);

    ~ImputationMakerTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ImputationMakerTransformer);

    // MSVC has problems when the function is defined outside of the declaration
    typename BaseType::TransformedType execute(typename BaseType::InputType input) override {
        if(Traits<T>::IsNull(input)) 
            return true;

        return false;
    }
};

template <typename T>
class ImputationMakerEstimator : public Components::InferenceOnlyEstimatorImpl<ImputationMakerTransformer<typename Traits<T>::nullable_type>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = typename Traits<T>::nullable_type;
    using ThisType                          = ImputationMakerEstimator<Type>;
    using BaseType                          = Components::InferenceOnlyEstimatorImpl<ImputationMakerTransformer<Type>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ImputationMakerEstimator(AnnotationMapsPtr pAllCoumnAnnotations);
    ~ImputationMakerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ImputationMakerEstimator);
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
// |  ImputationMakerEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
ImputationMakerTransformer<T>::ImputationMakerTransformer(Archive &ar) :
    BaseType(ar) {
}

// ----------------------------------------------------------------------
// |
// |  ImputationMakerEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
ImputationMakerEstimator<T>::ImputationMakerEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("ImputationMakerEstimator", std::move(pAllColumnAnnotations)) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
