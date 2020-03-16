// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/FilterFeaturizerImpl.h"
#include "Components/FrequencyEstimator.h"
#include "Components/PipelineExecutionEstimatorImpl.h"

#include <vector>

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {



/////////////////////////////////////////////////////////////////////////
///  \class         AnalyticalRollingWindowFeaturizer
///  \brief         Creates the `AnalyticalRollingWindowTransformer` object.
///
template <
    typename InputT, #TODO: put this in the right format. Tuple of stuff.
    typename TransformedT=std::vector<InputT>,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class AnalyticalRollingWindowEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::FilterEstimatorImpl<Components::GrainedFrequencyEstimator<MaxNumTrainingItemsV>, InputT, 1, 0>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = 
        Components::PipelineExecutionEstimatorImpl<
            Components::FilterEstimatorImpl<Components::GrainedFrequencyEstimator<MaxNumTrainingItemsV>, InputT, 1, 0>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    AnalyticalRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~AnalyticalRollingWindowEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(AnalyticalRollingWindowEstimator);
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
// |  AnalyticalRollingWindowEstimator
// |
// ----------------------------------------------------------------------

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
AnalyticalRollingWindowEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::AnalyticalRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "AnalyticalRollingWindowEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::FilterEstimatorImpl<Components::GrainedFrequencyEstimator<MaxNumTrainingItemsV>, InputT, 1, 0>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}


} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
