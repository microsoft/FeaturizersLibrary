// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Traits.h"
#include "Components/TimeSeriesFrequencyEstimator.h"
#include "Components/TimeSeriesMedianEstimator.h"
#include "Components/TimeSeriesImputerTransformer.h"
#include "Components/PipelineExecutionEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         TimeSeriesImputerEstimator
///  \brief         This class 'chains' TimeSeriesFrequencyEstimator and TimeSeriesImputerEstimator.
///                 TimeSeriesFrequencyEstimator generates Frequency Annotation which is consumed by
///                 TimeSeriesImputerEstimator to Impute data.
///
class TimeSeriesImputerEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::TimeSeriesFrequencyEstimator,
        Components::TimeSeriesMedianEstimator,
        Components::TimeSeriesImputerEstimator
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::PipelineExecutionEstimatorImpl<
        Components::TimeSeriesFrequencyEstimator,
        Components::TimeSeriesMedianEstimator,
        Components::TimeSeriesImputerEstimator
    >;

    TimeSeriesImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations,std::vector<TypeId> colsToImputeDataTypes, bool suppresserror = false, Components::TimeSeriesImputeStrategy tsImputeStrategy= Components::TimeSeriesImputeStrategy::Forward);

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TimeSeriesImputerEstimator);
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
inline TimeSeriesImputerEstimator::TimeSeriesImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::vector<TypeId> colsToImputeDataTypes, bool suppresserror, Components::TimeSeriesImputeStrategy tsImputeStrategy) :
    BaseType("TimeSeriesImputerEstimator",
        pAllColumnAnnotations,
        [&pAllColumnAnnotations](void) { return Components::TimeSeriesFrequencyEstimator(pAllColumnAnnotations); },
        [&pAllColumnAnnotations,&colsToImputeDataTypes](void) { return Components::TimeSeriesMedianEstimator(pAllColumnAnnotations,colsToImputeDataTypes); },
        [&pAllColumnAnnotations,&colsToImputeDataTypes,&tsImputeStrategy,&suppresserror](void) { return Components::TimeSeriesImputerEstimator(pAllColumnAnnotations,colsToImputeDataTypes,tsImputeStrategy,suppresserror); }
    ) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
