// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Traits.h"
#include "Components/TimeSeriesFrequencyEstimator.h"
#include "Components/TimeSeriesImputerTransformer.h"
#include "Components/PipelineExecutionEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         TimeSeriesImputerFeaturizerEstimator
///  \brief         This class 'chains' TimeSeriesFrequencyEstimator and TimeSeriesImputerEstimator.
///                 TimeSeriesFrequencyEstimator generates Frequency Annotation which is consumed by
///                 TimeSeriesImputerEstimator to Impute data.
///
class TimeSeriesImputerFeaturizerEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::TimeSeriesFrequencyEstimator,
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
        Components::TimeSeriesImputerEstimator
    >;
    
    TimeSeriesImputerFeaturizerEstimator(AnnotationMapsPtr pAllColumnAnnotations,std::vector<DataTypes> colsToImputeDataTypes, bool supressError = false, Components::TimeSeriesImputeStrategy tsImputeStrategy= Components::TimeSeriesImputeStrategy::Forward);

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TimeSeriesImputerFeaturizerEstimator);
};

TimeSeriesImputerFeaturizerEstimator::TimeSeriesImputerFeaturizerEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::vector<DataTypes> colsToImputeDataTypes, bool supressError, Components::TimeSeriesImputeStrategy tsImputeStrategy) :
    BaseType("TimeSeriesImputerFeaturizerEstimator", std::move(pAllColumnAnnotations)) {
        //Once PipelineExector enables instantiating templates types with ctor args- we'll make use of this.
        std::ignore = colsToImputeDataTypes;
        std::ignore = tsImputeStrategy;
        std::ignore = supressError;

}


} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
