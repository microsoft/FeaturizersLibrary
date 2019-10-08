// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/RobustScalarNormEstimator.h"
#include "Components/RobustScalarTransformer.h"
#include "Components/PipelineExecutionEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         RobustScalarEstimator
///  \brief         This class 'chains' RobustScalarNormEstimator and RobustScalarEstimator.
///
template <typename InputT, typename TransformedT>
class RobustScalarEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::RobustScalarNormEstimator<InputT, TransformedT, 0>,
        Components::RobustScalarEstimator<InputT, TransformedT>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::PipelineExecutionEstimatorImpl<
        Components::RobustScalarNormEstimator<InputT, TransformedT, 0>,
        Components::RobustScalarEstimator<InputT, TransformedT>
    >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    RobustScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool withCentering,
                          std::float_t qRangeMin = -1.0, std::float_t qRangeMax = -1.0);

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(RobustScalarEstimator);

    static RobustScalarEstimator<InputT, TransformedT> CreateWithDefaultScaling(AnnotationMapsPtr pAllColumnAnnotations, bool with_centering);
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
// |  RobustScalarEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
RobustScalarEstimator<InputT, TransformedT>::RobustScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool withCentering, std::float_t qRangeMin, std::float_t qRangeMax) :
    BaseType("RobustScalarEstimator", 
        pAllColumnAnnotations,
        [&pAllColumnAnnotations, &withCentering, &qRangeMin, &qRangeMax](void) { return Components::RobustScalarNormEstimator<InputT, TransformedT, 0>(pAllColumnAnnotations, withCentering, qRangeMin, qRangeMax); },
        [&pAllColumnAnnotations](void) { return Components::RobustScalarEstimator<InputT, TransformedT>(pAllColumnAnnotations); }
    ) {     
}

template <typename InputT, typename TransformedT>
RobustScalarEstimator<InputT, TransformedT> RobustScalarEstimator<InputT, TransformedT>::CreateWithDefaultScaling(AnnotationMapsPtr pAllColumnAnnotations, bool withCentering) {
    if (withCentering) {
        return RobustScalarEstimator(pAllColumnAnnotations, true, 25.0, 75.0);
    } 
    return RobustScalarEstimator(pAllColumnAnnotations, false, 25.0, 75.0);
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
