/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalerFeaturizer <int8> */
struct MaxAbsScalerFeaturizer_int8_EstimatorHandle {};
struct MaxAbsScalerFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_GetState(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_Fit(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_Transform(/*in*/ MaxAbsScalerFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_Flush(/*in*/ MaxAbsScalerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalerFeaturizer <int16> */
struct MaxAbsScalerFeaturizer_int16_EstimatorHandle {};
struct MaxAbsScalerFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_GetState(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_Fit(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_Transform(/*in*/ MaxAbsScalerFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_Flush(/*in*/ MaxAbsScalerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalerFeaturizer <uint8> */
struct MaxAbsScalerFeaturizer_uint8_EstimatorHandle {};
struct MaxAbsScalerFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_GetState(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_Fit(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_Transform(/*in*/ MaxAbsScalerFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_Flush(/*in*/ MaxAbsScalerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalerFeaturizer <uint16> */
struct MaxAbsScalerFeaturizer_uint16_EstimatorHandle {};
struct MaxAbsScalerFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_GetState(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_Fit(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_Transform(/*in*/ MaxAbsScalerFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_Flush(/*in*/ MaxAbsScalerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalerFeaturizer <float> */
struct MaxAbsScalerFeaturizer_float_EstimatorHandle {};
struct MaxAbsScalerFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_GetState(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_Fit(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_Transform(/*in*/ MaxAbsScalerFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_Flush(/*in*/ MaxAbsScalerFeaturizer_float_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalerFeaturizer <int32> */
struct MaxAbsScalerFeaturizer_int32_EstimatorHandle {};
struct MaxAbsScalerFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_GetState(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_Fit(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_Transform(/*in*/ MaxAbsScalerFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_Flush(/*in*/ MaxAbsScalerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalerFeaturizer <int64> */
struct MaxAbsScalerFeaturizer_int64_EstimatorHandle {};
struct MaxAbsScalerFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_GetState(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_Fit(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_Transform(/*in*/ MaxAbsScalerFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_Flush(/*in*/ MaxAbsScalerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalerFeaturizer <uint32> */
struct MaxAbsScalerFeaturizer_uint32_EstimatorHandle {};
struct MaxAbsScalerFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_GetState(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_Fit(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_Transform(/*in*/ MaxAbsScalerFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_Flush(/*in*/ MaxAbsScalerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalerFeaturizer <uint64> */
struct MaxAbsScalerFeaturizer_uint64_EstimatorHandle {};
struct MaxAbsScalerFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_GetState(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_Fit(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_Transform(/*in*/ MaxAbsScalerFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_Flush(/*in*/ MaxAbsScalerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalerFeaturizer <double> */
struct MaxAbsScalerFeaturizer_double_EstimatorHandle {};
struct MaxAbsScalerFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_GetState(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_Fit(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_Transform(/*in*/ MaxAbsScalerFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_Flush(/*in*/ MaxAbsScalerFeaturizer_double_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
