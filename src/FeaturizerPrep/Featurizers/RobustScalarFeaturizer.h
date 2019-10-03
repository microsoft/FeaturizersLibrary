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

    using QRangeType = std::tuple<std::float_t, std::float_t>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    RobustScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool with_centering,
                          QRangeType quantile_range = std::make_tuple<std::float_t, std::float_t>(-1.0, -1.0));

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
RobustScalarEstimator<InputT, TransformedT>::RobustScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool with_centering, QRangeType quantile_range) :
    BaseType("RobustScalarEstimator", 
        pAllColumnAnnotations,
        [&pAllColumnAnnotations, &with_centering, &quantile_range](void) { return Components::RobustScalarNormEstimator<InputT, TransformedT, 0>(pAllColumnAnnotations, with_centering, quantile_range); },
        [&pAllColumnAnnotations](void) { return Components::RobustScalarEstimator<InputT, TransformedT>(pAllColumnAnnotations); }
    ) {     
}

template <typename InputT, typename TransformedT>
RobustScalarEstimator<InputT, TransformedT> RobustScalarEstimator<InputT, TransformedT>::CreateWithDefaultScaling(AnnotationMapsPtr pAllColumnAnnotations, bool with_centering) {
    if (with_centering) {
        return RobustScalarEstimator(pAllColumnAnnotations, true, std::make_tuple<std::float_t, std::float_t>(25.0, 75.0));
    } 
    return RobustScalarEstimator(pAllColumnAnnotations, false, std::make_tuple<std::float_t, std::float_t>(25.0, 75.0));
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
