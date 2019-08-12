// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Featurizer.h"

namespace Microsoft {
namespace Featurizer {

/////////////////////////////////////////////////////////////////////////
///  \class         SampleAddFeaturizer
///  \brief         A Transformer and Estimator that add values. This is a
///                 sample intended to demonstrate patterns within the
///                 implementation of these types.
///
class SampleAddFeaturizer : public TransformerEstimator<std::uint16_t, std::uint32_t> {
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
    SampleAddFeaturizer(AnnotationMapsPtr pAllColumnAnnotations);
    ~SampleAddFeaturizer(void) override = default;

    SampleAddFeaturizer(SampleAddFeaturizer const &) = delete;
    SampleAddFeaturizer & operator =(SampleAddFeaturizer const &) = delete;

    SampleAddFeaturizer(SampleAddFeaturizer &&) = default;
    SampleAddFeaturizer & operator =(SampleAddFeaturizer &&) = delete;

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
    FitResult fit_impl(InputType const *pBuffer, size_t cBuffer, boost::optional<std::uint64_t> const &optionalNumTrailingNulls) override;
    void complete_training_impl(void) override;
    TransformerPtr create_transformer_impl(void) override;
};

} // namespace Featurizer
} // namespace Microsoft
