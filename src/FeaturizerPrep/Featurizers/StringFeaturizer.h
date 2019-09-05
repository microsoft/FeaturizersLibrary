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
///  \class         StringTransformer
///  \brief         Converts input into strings.
///
template <typename T>
class StringTransformer : public Components::InferenceOnlyTransformerImpl<T, std::string> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = T;
    using ThisType                          = StringTransformer<Type>;
    using BaseType                          = Components::InferenceOnlyTransformerImpl<Type, std::string>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StringTransformer(void) = default;
    StringTransformer(Archive &ar);

    ~StringTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StringTransformer);

    // MSVC has problems when the function is defined outside of the declaration
    typename BaseType::TransformedType execute(typename BaseType::InputType input) override {
        return Traits<T>::ToString(input);
    }
};

template <typename T>
class StringEstimator : public Components::InferenceOnlyEstimatorImpl<StringTransformer<T>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = T;
    using ThisType                          = StringEstimator<Type>;
    using BaseType                          = Components::InferenceOnlyEstimatorImpl<StringTransformer<Type>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StringEstimator(AnnotationMapsPtr pAllCoumnAnnotations);
    ~StringEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StringEstimator);
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
// |  StringTransformer
// |
// ----------------------------------------------------------------------
template <typename T>
StringTransformer<T>::StringTransformer(Archive &ar) :
    BaseType(ar) {
}

// ----------------------------------------------------------------------
// |
// |  StringEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
StringEstimator<T>::StringEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("StringEstimator", std::move(pAllColumnAnnotations)) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
