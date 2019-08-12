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
class StringTransformer : public TransformerEstimator<T, std::string>::Transformer {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = T;
    using ThisType                          = StringTransformer<Type>;
    using BaseType                          = typename TransformerEstimator<Type, std::string>::Transformer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StringTransformer(void) = default;
    ~StringTransformer(void) override = default;

    StringTransformer(StringTransformer const &) = delete;
    StringTransformer & operator =(StringTransformer const &) = delete;

    StringTransformer(StringTransformer && other) = default;
    StringTransformer & operator =(StringTransformer &&) = delete;

    typename BaseType::TransformedType execute(typename BaseType::InputType input) override;
};

template <typename T>
class StringFeaturizer : public InferenceOnlyFeaturizerImpl<StringTransformer<T>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = T;
    using ThisType                          = StringFeaturizer<Type>;
    using BaseType                          = InferenceOnlyFeaturizerImpl<StringTransformer<Type>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StringFeaturizer(AnnotationMapsPtr pAllCoumnAnnotations);
    ~StringFeaturizer(void) override = default;

    StringFeaturizer(StringFeaturizer const &) = delete;
    StringFeaturizer & operator =(StringFeaturizer const &) = delete;

    StringFeaturizer(StringFeaturizer &&) = default;
    StringFeaturizer & operator =(StringFeaturizer &&) = delete;
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
typename StringTransformer<T>::BaseType::TransformedType StringTransformer<T>::execute(typename BaseType::InputType input) /*override*/ {
    return Traits::Traits<T>::ToString(input);
}

// ----------------------------------------------------------------------
// |
// |  StringFeaturizer
// |
// ----------------------------------------------------------------------
template <typename T>
StringFeaturizer<T>::StringFeaturizer(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("StringFeaturizer", std::move(pAllColumnAnnotations)) {
}

} // namespace Featurizer
} // namespace Microsoft
