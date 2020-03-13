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
///  \class         SimpleRollingWindowFeaturizer
///  \brief         Creates the `SimpleRollingWindowTransformer` object.
///
template <
    typename InputT,
    typename TransformedT=std::vector<InputT>,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class SimpleRollingWindowEstimator :
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
    SimpleRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~SimpleRollingWindowEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SimpleRollingWindowEstimator);
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
// |  SimpleRollingWindowEstimator
// |
// ----------------------------------------------------------------------

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
SimpleRollingWindowEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::SimpleRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "SimpleRollingWindowEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::FilterEstimatorImpl<Components::GrainedFrequencyEstimator<MaxNumTrainingItemsV>, InputT, 1, 0>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}


} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
