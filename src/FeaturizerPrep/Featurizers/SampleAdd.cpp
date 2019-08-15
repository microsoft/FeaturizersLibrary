// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#include "SampleAdd.h"

#include "../Archive.h"

namespace Microsoft {
namespace Featurizer {

/////////////////////////////////////////////////////////////////////////
///  \class         SampleAddTransformer
///  \brief         Adds a delta to the provided value.
///
class SampleAddTransformer : public SampleAddFeaturizer::BaseType::Transformer {
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

    SampleAddTransformer(SampleAddTransformer const &) = delete;
    SampleAddTransformer & operator =(SampleAddTransformer const &) = delete;

    SampleAddTransformer(SampleAddTransformer &&) = default;
    SampleAddTransformer & operator =(SampleAddTransformer &&) = delete;

    TransformedType execute(InputType input) override {
        return input + Delta;
    }

    void save(Archive &ar) const override {
        ar.serialize(Delta);
    }
};

// ----------------------------------------------------------------------
// |
// |  SampleAddFeaturizer
// |
// ----------------------------------------------------------------------
SampleAddFeaturizer::SampleAddFeaturizer(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("SampleAddFeaturizer", std::move(pAllColumnAnnotations)) {
}

SampleAddFeaturizer::FitResult SampleAddFeaturizer::fit_impl(InputType const *pBuffer, size_t cBuffer, nonstd::optional<std::uint64_t> const &) /*override*/ {
    InputType const * const                 pEndBuffer(pBuffer + cBuffer);

    while(pBuffer != pEndBuffer) {
        _accumulated_delta += *pBuffer;
        ++pBuffer;
    }

    return FitResult::Continue;
}

void SampleAddFeaturizer::complete_training_impl(void) /*override*/ {
    // Nothing to do here
}

SampleAddFeaturizer::TransformerPtr SampleAddFeaturizer::create_transformer_impl(void) /*override*/ {
    return std::make_shared<SampleAddTransformer>(_accumulated_delta);
}

} // namespace Featurizer
} // namespace Microsoft
