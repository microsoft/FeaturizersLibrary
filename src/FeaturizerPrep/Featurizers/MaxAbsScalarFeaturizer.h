// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/MaxAbsValueEstimator.h"
#include "Components/MaxAbsScalarTransformer.h"
#include "Components/PipelineExecutionEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         MaxAbsScalarEstimator
///  \brief         This class 'chains' MaxAbsValueEstimator and MaxAbsScalarEstimator.
///
template <typename InputT, typename TransformedT>
class MaxAbsScalarEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::MaxAbsValueEstimator<InputT, TransformedT, 0>,
        Components::MaxAbsScalarEstimator<InputT, TransformedT>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::PipelineExecutionEstimatorImpl<
        Components::MaxAbsValueEstimator<InputT, TransformedT, 0>,
        Components::MaxAbsScalarEstimator<InputT, TransformedT>
    >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MaxAbsScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations);

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MaxAbsScalarEstimator);
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
// |  MaxAbsScalarEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
MaxAbsScalarEstimator<InputT, TransformedT>::MaxAbsScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("RobustScalarEstimator", 
        pAllColumnAnnotations,
        [&pAllColumnAnnotations](void) { return Components::MaxAbsValueEstimator<InputT, TransformedT, 0>(pAllColumnAnnotations); },
        [&pAllColumnAnnotations](void) { return Components::MaxAbsScalarEstimator<InputT, TransformedT>(pAllColumnAnnotations); }
    ) {     
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
