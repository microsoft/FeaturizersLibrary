// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#include "SampleAddFeaturizer.h"

#include "../Archive.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         SampleAddTransformer
///  \brief         Adds a delta to the provided value.
///
class SampleAddTransformer : public StandardTransformer<std::uint16_t, std::uint32_t> {
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
        SampleAddTransformer(
            [&ar](void) {
                // Version 
                std::uint16_t               majorVersion(Traits<std::uint16_t>::deserialize(ar));
                std::uint16_t               minorVersion(Traits<std::uint16_t>::deserialize(ar));

                if(majorVersion != 1 || minorVersion != 0)
                    throw std::runtime_error("Unsupported archive version");

                // Data
                return SampleAddTransformer(ar.deserialize<decltype(Delta)>());
            }()
        ) {
    }

    ~SampleAddTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SampleAddTransformer);

    void save(Archive &ar) const override {
        // Version
        Traits<std::uint16_t>::serialize(ar, 1);
        Traits<std::uint16_t>::serialize(ar, 0);

        // Data
        ar.serialize(Delta);
    }

private:
    // ----------------------------------------------------------------------
    // |  Private Methods
    void execute_impl(InputType const &input, CallbackFunction const &callback) override {
        callback(input + Delta);
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

bool SampleAddEstimator::begin_training_impl(void) /*override*/ {
    return true;
}

FitResult SampleAddEstimator::fit_impl(InputType const *pBuffer, size_t cBuffer) /*override*/ {
    InputType const * const                 pEndBuffer(pBuffer + cBuffer);

    while(pBuffer != pEndBuffer) {
        _accumulated_delta += *pBuffer;
        ++pBuffer;
    }

    return FitResult::Continue;
}

void SampleAddEstimator::complete_training_impl(void) /*override*/ {
}

SampleAddEstimator::TransformerUniquePtr SampleAddEstimator::create_transformer_impl(void) /*override*/ {
    return typename BaseType::TransformerUniquePtr(new SampleAddTransformer(_accumulated_delta));
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
