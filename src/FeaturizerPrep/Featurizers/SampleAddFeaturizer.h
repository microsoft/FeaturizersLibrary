// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Featurizer.h"

namespace Microsoft {
namespace Featurizer {

/////////////////////////////////////////////////////////////////////////
///  \class         SampleAddEstimator
///  \brief         A Transformer and Estimator that add values. This is a
///                 sample intended to demonstrate patterns within the
///                 implementation of these types.
///
class SampleAddEstimator : public TransformerEstimator<std::uint16_t, std::uint32_t> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<std::uint16_t, std::uint32_t>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SampleAddEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~SampleAddEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SampleAddEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::uint32_t                           _accumulated_delta = 0;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    FitResult fit_impl(InputType const *pBuffer, size_t cBuffer) override;
    FitResult complete_training_impl(void) override;
    TransformerUniquePtr create_transformer_impl(void) override;
};

} // namespace Featurizer
} // namespace Microsoft
