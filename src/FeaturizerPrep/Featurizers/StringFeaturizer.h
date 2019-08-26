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

    StringTransformer(StringTransformer const &) = delete;
    StringTransformer & operator =(StringTransformer const &) = delete;

    StringTransformer(StringTransformer && other) = default;
    StringTransformer & operator =(StringTransformer &&) = delete;

    typename BaseType::TransformedType execute(typename BaseType::InputType input) override;
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

    StringEstimator(StringEstimator const &) = delete;
    StringEstimator & operator =(StringEstimator const &) = delete;

    StringEstimator(StringEstimator &&) = default;
    StringEstimator & operator =(StringEstimator &&) = delete;
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

template <typename T>
typename StringTransformer<T>::BaseType::TransformedType StringTransformer<T>::execute(typename BaseType::InputType input) /*override*/ {
    return Traits<T>::ToString(input);
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
