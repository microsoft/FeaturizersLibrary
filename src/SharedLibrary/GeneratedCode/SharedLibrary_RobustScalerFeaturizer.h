/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  RobustScalerFeaturizer <int8> */
struct RobustScalerFeaturizer_int8_EstimatorHandle {};
struct RobustScalerFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_CreateEstimator(/*in*/ bool withCentering, /*in*/ float qRangeMin, /*in*/ float qRangeMax,/*out*/ RobustScalerFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_DestroyEstimator(/*in*/ RobustScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_GetState(/*in*/ RobustScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_IsTrainingComplete(/*in*/ RobustScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_Fit(/*in*/ RobustScalerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_FitBuffer(/*in*/ RobustScalerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_OnDataCompleted(/*in*/ RobustScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_CompleteTraining(/*in*/ RobustScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ RobustScalerFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ RobustScalerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_DestroyTransformer(/*in*/ RobustScalerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_CreateTransformerSaveData(/*in*/ RobustScalerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_Transform(/*in*/ RobustScalerFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_Flush(/*in*/ RobustScalerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalerFeaturizer <int16> */
struct RobustScalerFeaturizer_int16_EstimatorHandle {};
struct RobustScalerFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_CreateEstimator(/*in*/ bool withCentering, /*in*/ float qRangeMin, /*in*/ float qRangeMax,/*out*/ RobustScalerFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_DestroyEstimator(/*in*/ RobustScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_GetState(/*in*/ RobustScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_IsTrainingComplete(/*in*/ RobustScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_Fit(/*in*/ RobustScalerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_FitBuffer(/*in*/ RobustScalerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_OnDataCompleted(/*in*/ RobustScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_CompleteTraining(/*in*/ RobustScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ RobustScalerFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ RobustScalerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_DestroyTransformer(/*in*/ RobustScalerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_CreateTransformerSaveData(/*in*/ RobustScalerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_Transform(/*in*/ RobustScalerFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_Flush(/*in*/ RobustScalerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalerFeaturizer <uint8> */
struct RobustScalerFeaturizer_uint8_EstimatorHandle {};
struct RobustScalerFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_CreateEstimator(/*in*/ bool withCentering, /*in*/ float qRangeMin, /*in*/ float qRangeMax,/*out*/ RobustScalerFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_DestroyEstimator(/*in*/ RobustScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_GetState(/*in*/ RobustScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_IsTrainingComplete(/*in*/ RobustScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_Fit(/*in*/ RobustScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_FitBuffer(/*in*/ RobustScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_OnDataCompleted(/*in*/ RobustScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_CompleteTraining(/*in*/ RobustScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ RobustScalerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ RobustScalerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_DestroyTransformer(/*in*/ RobustScalerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_CreateTransformerSaveData(/*in*/ RobustScalerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_Transform(/*in*/ RobustScalerFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_Flush(/*in*/ RobustScalerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalerFeaturizer <uint16> */
struct RobustScalerFeaturizer_uint16_EstimatorHandle {};
struct RobustScalerFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_CreateEstimator(/*in*/ bool withCentering, /*in*/ float qRangeMin, /*in*/ float qRangeMax,/*out*/ RobustScalerFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_DestroyEstimator(/*in*/ RobustScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_GetState(/*in*/ RobustScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_IsTrainingComplete(/*in*/ RobustScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_Fit(/*in*/ RobustScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_FitBuffer(/*in*/ RobustScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_OnDataCompleted(/*in*/ RobustScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_CompleteTraining(/*in*/ RobustScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ RobustScalerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ RobustScalerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_DestroyTransformer(/*in*/ RobustScalerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_CreateTransformerSaveData(/*in*/ RobustScalerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_Transform(/*in*/ RobustScalerFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_Flush(/*in*/ RobustScalerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalerFeaturizer <float> */
struct RobustScalerFeaturizer_float_EstimatorHandle {};
struct RobustScalerFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_CreateEstimator(/*in*/ bool withCentering, /*in*/ float qRangeMin, /*in*/ float qRangeMax,/*out*/ RobustScalerFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_DestroyEstimator(/*in*/ RobustScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_GetState(/*in*/ RobustScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_IsTrainingComplete(/*in*/ RobustScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_Fit(/*in*/ RobustScalerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_FitBuffer(/*in*/ RobustScalerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_OnDataCompleted(/*in*/ RobustScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_CompleteTraining(/*in*/ RobustScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_CreateTransformerFromEstimator(/*in*/ RobustScalerFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ RobustScalerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_DestroyTransformer(/*in*/ RobustScalerFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_CreateTransformerSaveData(/*in*/ RobustScalerFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_Transform(/*in*/ RobustScalerFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_Flush(/*in*/ RobustScalerFeaturizer_float_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalerFeaturizer <int32> */
struct RobustScalerFeaturizer_int32_EstimatorHandle {};
struct RobustScalerFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_CreateEstimator(/*in*/ bool withCentering, /*in*/ float qRangeMin, /*in*/ float qRangeMax,/*out*/ RobustScalerFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_DestroyEstimator(/*in*/ RobustScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_GetState(/*in*/ RobustScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_IsTrainingComplete(/*in*/ RobustScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_Fit(/*in*/ RobustScalerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_FitBuffer(/*in*/ RobustScalerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_OnDataCompleted(/*in*/ RobustScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_CompleteTraining(/*in*/ RobustScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ RobustScalerFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ RobustScalerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_DestroyTransformer(/*in*/ RobustScalerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_CreateTransformerSaveData(/*in*/ RobustScalerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_Transform(/*in*/ RobustScalerFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_Flush(/*in*/ RobustScalerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalerFeaturizer <int64> */
struct RobustScalerFeaturizer_int64_EstimatorHandle {};
struct RobustScalerFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_CreateEstimator(/*in*/ bool withCentering, /*in*/ float qRangeMin, /*in*/ float qRangeMax,/*out*/ RobustScalerFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_DestroyEstimator(/*in*/ RobustScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_GetState(/*in*/ RobustScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_IsTrainingComplete(/*in*/ RobustScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_Fit(/*in*/ RobustScalerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_FitBuffer(/*in*/ RobustScalerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_OnDataCompleted(/*in*/ RobustScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_CompleteTraining(/*in*/ RobustScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ RobustScalerFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ RobustScalerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_DestroyTransformer(/*in*/ RobustScalerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_CreateTransformerSaveData(/*in*/ RobustScalerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_Transform(/*in*/ RobustScalerFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_Flush(/*in*/ RobustScalerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalerFeaturizer <uint32> */
struct RobustScalerFeaturizer_uint32_EstimatorHandle {};
struct RobustScalerFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_CreateEstimator(/*in*/ bool withCentering, /*in*/ float qRangeMin, /*in*/ float qRangeMax,/*out*/ RobustScalerFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_DestroyEstimator(/*in*/ RobustScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_GetState(/*in*/ RobustScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_IsTrainingComplete(/*in*/ RobustScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_Fit(/*in*/ RobustScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_FitBuffer(/*in*/ RobustScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_OnDataCompleted(/*in*/ RobustScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_CompleteTraining(/*in*/ RobustScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ RobustScalerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ RobustScalerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_DestroyTransformer(/*in*/ RobustScalerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_CreateTransformerSaveData(/*in*/ RobustScalerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_Transform(/*in*/ RobustScalerFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_Flush(/*in*/ RobustScalerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalerFeaturizer <uint64> */
struct RobustScalerFeaturizer_uint64_EstimatorHandle {};
struct RobustScalerFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_CreateEstimator(/*in*/ bool withCentering, /*in*/ float qRangeMin, /*in*/ float qRangeMax,/*out*/ RobustScalerFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_DestroyEstimator(/*in*/ RobustScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_GetState(/*in*/ RobustScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_IsTrainingComplete(/*in*/ RobustScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_Fit(/*in*/ RobustScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_FitBuffer(/*in*/ RobustScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_OnDataCompleted(/*in*/ RobustScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_CompleteTraining(/*in*/ RobustScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ RobustScalerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ RobustScalerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_DestroyTransformer(/*in*/ RobustScalerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_CreateTransformerSaveData(/*in*/ RobustScalerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_Transform(/*in*/ RobustScalerFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_Flush(/*in*/ RobustScalerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalerFeaturizer <double> */
struct RobustScalerFeaturizer_double_EstimatorHandle {};
struct RobustScalerFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_CreateEstimator(/*in*/ bool withCentering, /*in*/ float qRangeMin, /*in*/ float qRangeMax,/*out*/ RobustScalerFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_DestroyEstimator(/*in*/ RobustScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_GetState(/*in*/ RobustScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_IsTrainingComplete(/*in*/ RobustScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_Fit(/*in*/ RobustScalerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_FitBuffer(/*in*/ RobustScalerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_OnDataCompleted(/*in*/ RobustScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_CompleteTraining(/*in*/ RobustScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_CreateTransformerFromEstimator(/*in*/ RobustScalerFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ RobustScalerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_DestroyTransformer(/*in*/ RobustScalerFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_CreateTransformerSaveData(/*in*/ RobustScalerFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_Transform(/*in*/ RobustScalerFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_Flush(/*in*/ RobustScalerFeaturizer_double_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
