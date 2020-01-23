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
///  \class         FromStringTransformer
///  \brief         Transforms a string into a corresponding type.
///
template <typename T>
class FromStringTransformer : public Components::InferenceOnlyTransformerImpl<std::string, T> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = Components::InferenceOnlyTransformerImpl<std::string, T>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    FromStringTransformer(void) = default;
    FromStringTransformer(Archive &ar);

    ~FromStringTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FromStringTransformer);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems with the function declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        callback(Traits<T>::FromString(input));
    }
};

template <typename T>
class FromStringEstimator : public Components::InferenceOnlyEstimatorImpl<FromStringTransformer<T>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = Components::InferenceOnlyEstimatorImpl<FromStringTransformer<T>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    FromStringEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~FromStringEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FromStringEstimator);
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
// |  FromStringTransformer
// |
// ----------------------------------------------------------------------
template <typename T>
FromStringTransformer<T>::FromStringTransformer(Archive &ar) :
    BaseType(ar) {
}

// ----------------------------------------------------------------------
// |
// |  FromStringEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
FromStringEstimator<T>::FromStringEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("FromStringEstimator", std::move(pAllColumnAnnotations)) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
