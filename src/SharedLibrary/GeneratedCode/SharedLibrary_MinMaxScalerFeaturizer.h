/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalerFeaturizer <int8> */
struct MinMaxScalerFeaturizer_int8_EstimatorHandle {};
struct MinMaxScalerFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_CreateEstimator(/*out*/ MinMaxScalerFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_DestroyEstimator(/*in*/ MinMaxScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_GetState(/*in*/ MinMaxScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_IsTrainingComplete(/*in*/ MinMaxScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_Fit(/*in*/ MinMaxScalerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_FitBuffer(/*in*/ MinMaxScalerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_OnDataCompleted(/*in*/ MinMaxScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_CompleteTraining(/*in*/ MinMaxScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ MinMaxScalerFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxScalerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_DestroyTransformer(/*in*/ MinMaxScalerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_CreateTransformerSaveData(/*in*/ MinMaxScalerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_Transform(/*in*/ MinMaxScalerFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int8_Flush(/*in*/ MinMaxScalerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalerFeaturizer <int16> */
struct MinMaxScalerFeaturizer_int16_EstimatorHandle {};
struct MinMaxScalerFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_CreateEstimator(/*out*/ MinMaxScalerFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_DestroyEstimator(/*in*/ MinMaxScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_GetState(/*in*/ MinMaxScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_IsTrainingComplete(/*in*/ MinMaxScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_Fit(/*in*/ MinMaxScalerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_FitBuffer(/*in*/ MinMaxScalerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_OnDataCompleted(/*in*/ MinMaxScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_CompleteTraining(/*in*/ MinMaxScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ MinMaxScalerFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxScalerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_DestroyTransformer(/*in*/ MinMaxScalerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_CreateTransformerSaveData(/*in*/ MinMaxScalerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_Transform(/*in*/ MinMaxScalerFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int16_Flush(/*in*/ MinMaxScalerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalerFeaturizer <int32> */
struct MinMaxScalerFeaturizer_int32_EstimatorHandle {};
struct MinMaxScalerFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_CreateEstimator(/*out*/ MinMaxScalerFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_DestroyEstimator(/*in*/ MinMaxScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_GetState(/*in*/ MinMaxScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_IsTrainingComplete(/*in*/ MinMaxScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_Fit(/*in*/ MinMaxScalerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_FitBuffer(/*in*/ MinMaxScalerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_OnDataCompleted(/*in*/ MinMaxScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_CompleteTraining(/*in*/ MinMaxScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ MinMaxScalerFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxScalerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_DestroyTransformer(/*in*/ MinMaxScalerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_CreateTransformerSaveData(/*in*/ MinMaxScalerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_Transform(/*in*/ MinMaxScalerFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int32_Flush(/*in*/ MinMaxScalerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalerFeaturizer <int64> */
struct MinMaxScalerFeaturizer_int64_EstimatorHandle {};
struct MinMaxScalerFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_CreateEstimator(/*out*/ MinMaxScalerFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_DestroyEstimator(/*in*/ MinMaxScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_GetState(/*in*/ MinMaxScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_IsTrainingComplete(/*in*/ MinMaxScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_Fit(/*in*/ MinMaxScalerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_FitBuffer(/*in*/ MinMaxScalerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_OnDataCompleted(/*in*/ MinMaxScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_CompleteTraining(/*in*/ MinMaxScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ MinMaxScalerFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxScalerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_DestroyTransformer(/*in*/ MinMaxScalerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_CreateTransformerSaveData(/*in*/ MinMaxScalerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_Transform(/*in*/ MinMaxScalerFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_int64_Flush(/*in*/ MinMaxScalerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalerFeaturizer <uint8> */
struct MinMaxScalerFeaturizer_uint8_EstimatorHandle {};
struct MinMaxScalerFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_CreateEstimator(/*out*/ MinMaxScalerFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_DestroyEstimator(/*in*/ MinMaxScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_GetState(/*in*/ MinMaxScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_IsTrainingComplete(/*in*/ MinMaxScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_Fit(/*in*/ MinMaxScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_FitBuffer(/*in*/ MinMaxScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_OnDataCompleted(/*in*/ MinMaxScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_CompleteTraining(/*in*/ MinMaxScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ MinMaxScalerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxScalerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_DestroyTransformer(/*in*/ MinMaxScalerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_CreateTransformerSaveData(/*in*/ MinMaxScalerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_Transform(/*in*/ MinMaxScalerFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint8_Flush(/*in*/ MinMaxScalerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalerFeaturizer <uint16> */
struct MinMaxScalerFeaturizer_uint16_EstimatorHandle {};
struct MinMaxScalerFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_CreateEstimator(/*out*/ MinMaxScalerFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_DestroyEstimator(/*in*/ MinMaxScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_GetState(/*in*/ MinMaxScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_IsTrainingComplete(/*in*/ MinMaxScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_Fit(/*in*/ MinMaxScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_FitBuffer(/*in*/ MinMaxScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_OnDataCompleted(/*in*/ MinMaxScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_CompleteTraining(/*in*/ MinMaxScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ MinMaxScalerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxScalerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_DestroyTransformer(/*in*/ MinMaxScalerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_CreateTransformerSaveData(/*in*/ MinMaxScalerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_Transform(/*in*/ MinMaxScalerFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint16_Flush(/*in*/ MinMaxScalerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalerFeaturizer <uint32> */
struct MinMaxScalerFeaturizer_uint32_EstimatorHandle {};
struct MinMaxScalerFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_CreateEstimator(/*out*/ MinMaxScalerFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_DestroyEstimator(/*in*/ MinMaxScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_GetState(/*in*/ MinMaxScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_IsTrainingComplete(/*in*/ MinMaxScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_Fit(/*in*/ MinMaxScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_FitBuffer(/*in*/ MinMaxScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_OnDataCompleted(/*in*/ MinMaxScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_CompleteTraining(/*in*/ MinMaxScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ MinMaxScalerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxScalerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_DestroyTransformer(/*in*/ MinMaxScalerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_CreateTransformerSaveData(/*in*/ MinMaxScalerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_Transform(/*in*/ MinMaxScalerFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint32_Flush(/*in*/ MinMaxScalerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalerFeaturizer <uint64> */
struct MinMaxScalerFeaturizer_uint64_EstimatorHandle {};
struct MinMaxScalerFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_CreateEstimator(/*out*/ MinMaxScalerFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_DestroyEstimator(/*in*/ MinMaxScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_GetState(/*in*/ MinMaxScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_IsTrainingComplete(/*in*/ MinMaxScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_Fit(/*in*/ MinMaxScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_FitBuffer(/*in*/ MinMaxScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_OnDataCompleted(/*in*/ MinMaxScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_CompleteTraining(/*in*/ MinMaxScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ MinMaxScalerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxScalerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_DestroyTransformer(/*in*/ MinMaxScalerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_CreateTransformerSaveData(/*in*/ MinMaxScalerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_Transform(/*in*/ MinMaxScalerFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_uint64_Flush(/*in*/ MinMaxScalerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalerFeaturizer <float> */
struct MinMaxScalerFeaturizer_float_EstimatorHandle {};
struct MinMaxScalerFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_CreateEstimator(/*out*/ MinMaxScalerFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_DestroyEstimator(/*in*/ MinMaxScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_GetState(/*in*/ MinMaxScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_IsTrainingComplete(/*in*/ MinMaxScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_Fit(/*in*/ MinMaxScalerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_FitBuffer(/*in*/ MinMaxScalerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_OnDataCompleted(/*in*/ MinMaxScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_CompleteTraining(/*in*/ MinMaxScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_CreateTransformerFromEstimator(/*in*/ MinMaxScalerFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxScalerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_DestroyTransformer(/*in*/ MinMaxScalerFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_CreateTransformerSaveData(/*in*/ MinMaxScalerFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_Transform(/*in*/ MinMaxScalerFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_float_Flush(/*in*/ MinMaxScalerFeaturizer_float_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalerFeaturizer <double> */
struct MinMaxScalerFeaturizer_double_EstimatorHandle {};
struct MinMaxScalerFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_CreateEstimator(/*out*/ MinMaxScalerFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_DestroyEstimator(/*in*/ MinMaxScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_GetState(/*in*/ MinMaxScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_IsTrainingComplete(/*in*/ MinMaxScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_Fit(/*in*/ MinMaxScalerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_FitBuffer(/*in*/ MinMaxScalerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_OnDataCompleted(/*in*/ MinMaxScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_CompleteTraining(/*in*/ MinMaxScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_CreateTransformerFromEstimator(/*in*/ MinMaxScalerFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxScalerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_DestroyTransformer(/*in*/ MinMaxScalerFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_CreateTransformerSaveData(/*in*/ MinMaxScalerFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_Transform(/*in*/ MinMaxScalerFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalerFeaturizer_double_Flush(/*in*/ MinMaxScalerFeaturizer_double_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
