/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"
#include "SharedLibrary_RobustScalerFeaturizer.h"

extern "C" {

/* This file exposes non-standard functionality in the RobustScalerFeaturizer */

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
