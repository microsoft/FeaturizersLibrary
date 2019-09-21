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

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    bool IsNumericTypeId(TypeId const & typeId);
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

TimeSeriesImputerEstimator::TimeSeriesImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::vector<TypeId> colsToImputeDataTypes, bool suppresserror, Components::TimeSeriesImputeStrategy tsImputeStrategy) :
    BaseType("TimeSeriesImputerEstimator", 
        pAllColumnAnnotations,
        [&pAllColumnAnnotations](void) { return Components::TimeSeriesFrequencyEstimator(pAllColumnAnnotations); },
        [&pAllColumnAnnotations](void) { return Components::TimeSeriesMedianEstimator(pAllColumnAnnotations); },
        [&pAllColumnAnnotations,colsToImputeDataTypes,tsImputeStrategy,suppresserror](void) { return Components::TimeSeriesImputerEstimator(pAllColumnAnnotations,colsToImputeDataTypes,tsImputeStrategy,suppresserror); }
    ){
        for(std::size_t i=0; i< colsToImputeDataTypes.size(); ++i) {
          if(
              tsImputeStrategy == Components::TimeSeriesImputeStrategy::Median &&
              !IsNumericTypeId(colsToImputeDataTypes[i]) &&
              suppresserror == false
            )
            throw std::runtime_error("Only Numeric type columns are supported for ImputationStrategy median. (use suppresserror flag to skip imputing non-numeric types)");                
        }
    }

bool TimeSeriesImputerEstimator::IsNumericTypeId(TypeId const & id) {
    if(
        !(
           id == TypeId::Int8
        || id == TypeId::Int16
        || id == TypeId::Int32
        || id == TypeId::Int64
        || id == TypeId::UInt8
        || id == TypeId::UInt16
        || id == TypeId::UInt32
        || id == TypeId::UInt64
        || id == TypeId::Float16
        || id == TypeId::Float32
        || id == TypeId::Float64
        || id == TypeId::Complex64
        || id == TypeId::Complex128
        || id == TypeId::BFloat16
        ))
        return false;

    return true;
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
