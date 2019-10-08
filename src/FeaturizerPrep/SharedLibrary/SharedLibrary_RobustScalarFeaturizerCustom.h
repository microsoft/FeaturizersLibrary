/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"
#include "SharedLibrary_RobustScalarFeaturizer.h"

extern "C" {

/* This file exposes non-standard functionality in the RobustScalarFeaturizer */

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_int8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_int16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_float_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_int32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_int64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_double_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
