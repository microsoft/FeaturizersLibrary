// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../InferenceOnlyFeaturizerImpl.h"
#include "../Traits.h"

namespace Microsoft {
namespace Featurizer {

/////////////////////////////////////////////////////////////////////////
///  \class         StringTransformer
///  \brief         Converts input into strings.
///
template <typename T>
class StringTransformer : public InferenceOnlyTransformerImpl<T, std::string> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = T;
    using ThisType                          = StringTransformer<Type>;
    using BaseType                          = InferenceOnlyTransformerImpl<Type, std::string>;

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
class StringEstimator : public InferenceOnlyEstimatorImpl<StringTransformer<T>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = T;
    using ThisType                          = StringEstimator<Type>;
    using BaseType                          = InferenceOnlyEstimatorImpl<StringTransformer<Type>>;

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

} // namespace Featurizer
} // namespace Microsoft
