// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"

#include "Components/InferenceOnlyFeaturizerImpl.h"

#include <vector>

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         AnalyticalRollingWindowTransformerName("AnalyticalRollingWindowTransformer");

/////////////////////////////////////////////////////////////////////////
///  \class         RollingWindowTransformer
///  \brief         RollingWindow class that is used for all window computations.
///
template <
    typename InputT,
    typename TransformedT=std::vector<InputT>,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class AnalyticalRollingWindowTransformer:
    public Components::InferenceOnlyTransformerImpl<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::InferenceOnlyTransformerImpl<InputT, TransformedT>;

    // Currently only one of calculation is supported. This will be expanded upon in the future,
    // so we are peparing by making this an enum from the get go.
    enum class AnalyticalRollingWindowCalculation : unsigned char {
        Mean = 1
    };

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    AnalyticalRollingWindowTransformer(std::uint32_t windowSize, AnalyticalRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowCount = 1) ;
    AnalyticalRollingWindowTransformer(Archive &ar);
    ~AnalyticalRollingWindowTransformer(void) override = default;


}



} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
