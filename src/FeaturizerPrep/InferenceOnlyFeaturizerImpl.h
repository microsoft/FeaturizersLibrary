// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Featurizer.h"

namespace Microsoft {
namespace Featurizer {

/////////////////////////////////////////////////////////////////////////
///  \class         InferenceOnlyTransformerImpl
///  \brief         Implements functionality common to a `Transformer`
///                 associated with a `Featurizer` that doesn't generate
///                 state during training.
///
template <typename InputT, typename TransformedT>
class InferenceOnlyTransformerImpl : public TransformerEstimator<InputT, TransformedT>::Transformer {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = InputT;
    using TransformedType                   = TransformedT;

    using ThisType                          = InferenceOnlyTransformerImpl<InputType, TransformedType>;
    using BaseType                          = typename TransformerEstimator<InputType, TransformedType>::Transformer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    InferenceOnlyTransformerImpl(void) = default;
    InferenceOnlyTransformerImpl(Archive &ar);

    ~InferenceOnlyTransformerImpl(void) override = default;

    InferenceOnlyTransformerImpl(InferenceOnlyTransformerImpl const &) = delete;
    InferenceOnlyTransformerImpl & operator =(InferenceOnlyTransformerImpl const &) = delete;

    InferenceOnlyTransformerImpl(InferenceOnlyTransformerImpl &&) = default;
    InferenceOnlyTransformerImpl & operator =(InferenceOnlyTransformerImpl &&) = delete;

    void save(Archive &ar) const override;
};

/////////////////////////////////////////////////////////////////////////
///  \class         InferenceOnlyFeaturizerImpl
///  \brief         Featurizer that only participates in inferencing
///                 activities - no training is required. This class implement
///                 the scaffolding necessary to produce a transformer.
///
template <
    typename TransformerT,
    typename InputT=typename TransformerT::InputType,
    typename TransformedT=typename TransformerT::TransformedType
>
class InferenceOnlyFeaturizerImpl : public TransformerEstimator<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TransformerType                   = TransformerT;
    using InputType                         = InputT;
    using TransformedType                   = TransformedT;

    using ThisType                          = InferenceOnlyFeaturizerImpl<TransformerType, InputType, TransformedType>;
    using BaseType                          = TransformerEstimator<InputType, TransformedType>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    InferenceOnlyFeaturizerImpl(std::string name, AnnotationMapsPtr pAllColumnAnnotations);
    ~InferenceOnlyFeaturizerImpl(void) override = default;

    InferenceOnlyFeaturizerImpl(InferenceOnlyFeaturizerImpl const &) = delete;
    InferenceOnlyFeaturizerImpl & operator =(InferenceOnlyFeaturizerImpl const &) = delete;

    InferenceOnlyFeaturizerImpl(InferenceOnlyFeaturizerImpl &&) = default;
    InferenceOnlyFeaturizerImpl & operator =(InferenceOnlyFeaturizerImpl &&) = delete;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    typename BaseType::FitResult fit_impl(InputType const *pBuffer, size_t cBuffer, boost::optional<std::uint64_t> const &optionalNumTrailingNulls) override;
    void complete_training_impl(void) override;
    typename BaseType::TransformerPtr create_transformer_impl(void) override;
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
// |  InferenceOnlyTransformerImpl
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
InferenceOnlyTransformerImpl<InputT, TransformedT>::InferenceOnlyTransformerImpl(Archive &) {
    // Nothing to do here
}

template <typename InputT, typename TransformedT>
void InferenceOnlyTransformerImpl<InputT, TransformedT>::save(Archive &) const /*override*/ {
    // Nothing to do here
}

// ----------------------------------------------------------------------
// |
// |  InferenceOnlyFeaturizerImpl
// |
// ----------------------------------------------------------------------
template <typename TransformerT, typename InputT, typename TransformedT>
InferenceOnlyFeaturizerImpl<TransformerT, InputT, TransformedT>::InferenceOnlyFeaturizerImpl(std::string name, AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType(std::move(name), std::move(pAllColumnAnnotations), true) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename TransformerT, typename InputT, typename TransformedT>
typename InferenceOnlyFeaturizerImpl<TransformerT, InputT, TransformedT>::BaseType::FitResult InferenceOnlyFeaturizerImpl<TransformerT, InputT, TransformedT>::fit_impl(InputType const *, size_t, boost::optional<std::uint64_t> const &) /*override*/ {
    throw std::runtime_error("This should never be called");
}

template <typename TransformerT, typename InputT, typename TransformedT>
void InferenceOnlyFeaturizerImpl<TransformerT, InputT, TransformedT>::complete_training_impl(void) /*override*/ {
    throw std::runtime_error("This should never be called");
}

template <typename TransformerT, typename InputT, typename TransformedT>
typename InferenceOnlyFeaturizerImpl<TransformerT, InputT, TransformedT>::BaseType::TransformerPtr InferenceOnlyFeaturizerImpl<TransformerT, InputT, TransformedT>::create_transformer_impl(void) /*override*/ {
    return std::make_shared<TransformerT>();
}

} // namespace Featurizer
} // namespace Microsoft
