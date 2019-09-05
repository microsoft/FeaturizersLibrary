// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../../Archive.h"
#include "../../Featurizer.h"
#include "../../Traits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

/////////////////////////////////////////////////////////////////////////
///  \class         InferenceOnlyTransformerImpl
///  \brief         Implements functionality common to a `Transformer`
///                 associated with a `Estimator` that doesn't generate
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

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(InferenceOnlyTransformerImpl);

    void save(Archive &ar) const override;
};

/////////////////////////////////////////////////////////////////////////
///  \class         InferenceOnlyEstimatorImpl
///  \brief         Estimator that only participates in inferencing
///                 activities - no training is required. This class implement
///                 the scaffolding necessary to produce a transformer.
///
template <
    typename TransformerT,
    typename InputT=typename TransformerT::InputType,
    typename TransformedT=typename TransformerT::TransformedType
>
class InferenceOnlyEstimatorImpl : public TransformerEstimator<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TransformerType                   = TransformerT;
    using InputType                         = InputT;
    using TransformedType                   = TransformedT;

    using ThisType                          = InferenceOnlyEstimatorImpl<TransformerType, InputType, TransformedType>;
    using BaseType                          = TransformerEstimator<InputType, TransformedType>;

    using FitBufferInputType                = typename BaseType::FitBufferInputType;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    InferenceOnlyEstimatorImpl(std::string name, AnnotationMapsPtr pAllColumnAnnotations);
    ~InferenceOnlyEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(InferenceOnlyEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // Note that the following training methods aren't used, but need to be overridden as
    // the base implementations are abstract. The noop definitions are below.
    Estimator::FitResult fit_impl(FitBufferInputType const *pBuffer, size_t cBuffer) override;
    Estimator::FitResult complete_training_impl(void) override;

    // MSVC has problems when the definition for the func is separated from its declaration.
    inline typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return std::make_unique<TransformerT>();
    }
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
InferenceOnlyTransformerImpl<InputT, TransformedT>::InferenceOnlyTransformerImpl(Archive &ar) {
    if(Traits<std::uint8_t>::deserialize(ar) != 1)
        throw std::runtime_error("Invalid transformer version");
}

template <typename InputT, typename TransformedT>
void InferenceOnlyTransformerImpl<InputT, TransformedT>::save(Archive &ar) const /*override*/ {
    Traits<std::uint8_t>::serialize(ar, 1); // Current version
}

// ----------------------------------------------------------------------
// |
// |  InferenceOnlyEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename TransformerT, typename InputT, typename TransformedT>
InferenceOnlyEstimatorImpl<TransformerT, InputT, TransformedT>::InferenceOnlyEstimatorImpl(std::string name, AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType(std::move(name), std::move(pAllColumnAnnotations), true) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename TransformerT, typename InputT, typename TransformedT>
Estimator::FitResult InferenceOnlyEstimatorImpl<TransformerT, InputT, TransformedT>::fit_impl(FitBufferInputType const *, size_t) /*override*/ {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

template <typename TransformerT, typename InputT, typename TransformedT>
Estimator::FitResult InferenceOnlyEstimatorImpl<TransformerT, InputT, TransformedT>::complete_training_impl(void) /*override*/ {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

} // namespace Components
} // namespace Featruziers
} // namespace Featurizer
} // namespace Microsoft
