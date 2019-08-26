// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#include "SampleAddFeaturizer.h"

#include "../Archive.h"

namespace Microsoft {
namespace Featurizer {

/////////////////////////////////////////////////////////////////////////
///  \class         SampleAddTransformer
///  \brief         Adds a delta to the provided value.
///
class SampleAddTransformer : public SampleAddEstimator::BaseType::Transformer {
public:
    // ----------------------------------------------------------------------
    // |  Public Data
    std::uint32_t const                     Delta;

    // ----------------------------------------------------------------------
    // |  Public Methods
    SampleAddTransformer(std::uint32_t delta) :
        Delta(delta) {
    }

    SampleAddTransformer(Archive &ar) :
        Delta(ar.deserialize<decltype(Delta)>()) {
    }

    ~SampleAddTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SampleAddTransformer);

    TransformedType execute(InputType input) override {
        return input + Delta;
    }

    void save(Archive &ar) const override {
        ar.serialize(Delta);
    }
};

// ----------------------------------------------------------------------
// |
// |  SampleAddEstimator
// |
// ----------------------------------------------------------------------
SampleAddEstimator::SampleAddEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("SampleAddEstimator", std::move(pAllColumnAnnotations)) {
}

SampleAddEstimator::FitResult SampleAddEstimator::fit_impl(InputType const *pBuffer, size_t cBuffer) /*override*/ {
    InputType const * const                 pEndBuffer(pBuffer + cBuffer);

    while(pBuffer != pEndBuffer) {
        _accumulated_delta += *pBuffer;
        ++pBuffer;
    }

    return FitResult::Continue;
}

SampleAddEstimator::FitResult SampleAddEstimator::complete_training_impl(void) /*override*/ {
    return FitResult::Complete;
}

SampleAddEstimator::TransformerUniquePtr SampleAddEstimator::create_transformer_impl(void) /*override*/ {
    return std::make_unique<SampleAddTransformer>(_accumulated_delta);
}

} // namespace Featurizer
} // namespace Microsoft
