/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"
#include "SharedLibrary_RobustScalarFeaturizer.h"

extern "C" {

/* This file exposes non-standard functionality in the RobustScalarFeaturizer */

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_CreateEstimatorWithDefault(/*in*/ bool withCentering, /*out*/ RobustScalarFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
