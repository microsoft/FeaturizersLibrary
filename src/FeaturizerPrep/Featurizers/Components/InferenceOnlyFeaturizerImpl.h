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
class InferenceOnlyTransformerImpl : public StandardTransformer<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = InputT;
    using TransformedType                   = TransformedT;

    using BaseType                          = StandardTransformer<InputType, TransformedType>;

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

    using BaseType                          = TransformerEstimator<InputType, TransformedType>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    InferenceOnlyEstimatorImpl(char const *name, AnnotationMapsPtr pAllColumnAnnotations);
    ~InferenceOnlyEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(InferenceOnlyEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;

    // Note that the following training methods aren't used, but need to be overridden as
    // the base implementations are abstract. The noop definitions are below.
    FitResult fit_impl(InputType const *pBuffer, size_t cBuffer) override;

    void complete_training_impl(void) override;

    // MSVC has problems when the definition for the func is separated from its declaration.
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
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
InferenceOnlyTransformerImpl<InputT, TransformedT>::InferenceOnlyTransformerImpl(Archive &) {
    // Nothing to do here
}

template <typename InputT, typename TransformedT>
void InferenceOnlyTransformerImpl<InputT, TransformedT>::save(Archive &) const /*override*/ {
    // Nothing to do here
}

// ----------------------------------------------------------------------
// |
// |  InferenceOnlyEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename TransformerT, typename InputT, typename TransformedT>
InferenceOnlyEstimatorImpl<TransformerT, InputT, TransformedT>::InferenceOnlyEstimatorImpl(char const *name, AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType(name, std::move(pAllColumnAnnotations)) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename TransformerT, typename InputT, typename TransformedT>
bool InferenceOnlyEstimatorImpl<TransformerT, InputT, TransformedT>::begin_training_impl(void) /*override*/ {
    // Do not allow any further training
    return false;
}

template <typename TransformerT, typename InputT, typename TransformedT>
FitResult InferenceOnlyEstimatorImpl<TransformerT, InputT, TransformedT>::fit_impl(InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

template <typename TransformerT, typename InputT, typename TransformedT>
void InferenceOnlyEstimatorImpl<TransformerT, InputT, TransformedT>::complete_training_impl(void) /*override*/ {
}

} // namespace Components
} // namespace Featruziers
} // namespace Featurizer
} // namespace Microsoft
