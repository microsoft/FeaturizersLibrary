/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  NumericalizeFeaturizer <int8> */
struct NumericalizeFeaturizer_int8_EstimatorHandle {};
struct NumericalizeFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_CreateEstimator(/*out*/ NumericalizeFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_DestroyEstimator(/*in*/ NumericalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_GetState(/*in*/ NumericalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_IsTrainingComplete(/*in*/ NumericalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_Fit(/*in*/ NumericalizeFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_FitBuffer(/*in*/ NumericalizeFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_OnDataCompleted(/*in*/ NumericalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_CompleteTraining(/*in*/ NumericalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ NumericalizeFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ NumericalizeFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ NumericalizeFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_DestroyTransformer(/*in*/ NumericalizeFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_CreateTransformerSaveData(/*in*/ NumericalizeFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_Transform(/*in*/ NumericalizeFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int8_Flush(/*in*/ NumericalizeFeaturizer_int8_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  NumericalizeFeaturizer <uint8> */
struct NumericalizeFeaturizer_uint8_EstimatorHandle {};
struct NumericalizeFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_CreateEstimator(/*out*/ NumericalizeFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_DestroyEstimator(/*in*/ NumericalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_GetState(/*in*/ NumericalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_IsTrainingComplete(/*in*/ NumericalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_Fit(/*in*/ NumericalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_FitBuffer(/*in*/ NumericalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_OnDataCompleted(/*in*/ NumericalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_CompleteTraining(/*in*/ NumericalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ NumericalizeFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ NumericalizeFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ NumericalizeFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_DestroyTransformer(/*in*/ NumericalizeFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_CreateTransformerSaveData(/*in*/ NumericalizeFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_Transform(/*in*/ NumericalizeFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint8_Flush(/*in*/ NumericalizeFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  NumericalizeFeaturizer <int16> */
struct NumericalizeFeaturizer_int16_EstimatorHandle {};
struct NumericalizeFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_CreateEstimator(/*out*/ NumericalizeFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_DestroyEstimator(/*in*/ NumericalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_GetState(/*in*/ NumericalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_IsTrainingComplete(/*in*/ NumericalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_Fit(/*in*/ NumericalizeFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_FitBuffer(/*in*/ NumericalizeFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_OnDataCompleted(/*in*/ NumericalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_CompleteTraining(/*in*/ NumericalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ NumericalizeFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ NumericalizeFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ NumericalizeFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_DestroyTransformer(/*in*/ NumericalizeFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_CreateTransformerSaveData(/*in*/ NumericalizeFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_Transform(/*in*/ NumericalizeFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int16_Flush(/*in*/ NumericalizeFeaturizer_int16_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  NumericalizeFeaturizer <uint16> */
struct NumericalizeFeaturizer_uint16_EstimatorHandle {};
struct NumericalizeFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_CreateEstimator(/*out*/ NumericalizeFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_DestroyEstimator(/*in*/ NumericalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_GetState(/*in*/ NumericalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_IsTrainingComplete(/*in*/ NumericalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_Fit(/*in*/ NumericalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_FitBuffer(/*in*/ NumericalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_OnDataCompleted(/*in*/ NumericalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_CompleteTraining(/*in*/ NumericalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ NumericalizeFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ NumericalizeFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ NumericalizeFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_DestroyTransformer(/*in*/ NumericalizeFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_CreateTransformerSaveData(/*in*/ NumericalizeFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_Transform(/*in*/ NumericalizeFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint16_Flush(/*in*/ NumericalizeFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  NumericalizeFeaturizer <int32> */
struct NumericalizeFeaturizer_int32_EstimatorHandle {};
struct NumericalizeFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_CreateEstimator(/*out*/ NumericalizeFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_DestroyEstimator(/*in*/ NumericalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_GetState(/*in*/ NumericalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_IsTrainingComplete(/*in*/ NumericalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_Fit(/*in*/ NumericalizeFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_FitBuffer(/*in*/ NumericalizeFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_OnDataCompleted(/*in*/ NumericalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_CompleteTraining(/*in*/ NumericalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ NumericalizeFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ NumericalizeFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ NumericalizeFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_DestroyTransformer(/*in*/ NumericalizeFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_CreateTransformerSaveData(/*in*/ NumericalizeFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_Transform(/*in*/ NumericalizeFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int32_Flush(/*in*/ NumericalizeFeaturizer_int32_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  NumericalizeFeaturizer <uint32> */
struct NumericalizeFeaturizer_uint32_EstimatorHandle {};
struct NumericalizeFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_CreateEstimator(/*out*/ NumericalizeFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_DestroyEstimator(/*in*/ NumericalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_GetState(/*in*/ NumericalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_IsTrainingComplete(/*in*/ NumericalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_Fit(/*in*/ NumericalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_FitBuffer(/*in*/ NumericalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_OnDataCompleted(/*in*/ NumericalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_CompleteTraining(/*in*/ NumericalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ NumericalizeFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ NumericalizeFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ NumericalizeFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_DestroyTransformer(/*in*/ NumericalizeFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_CreateTransformerSaveData(/*in*/ NumericalizeFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_Transform(/*in*/ NumericalizeFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint32_Flush(/*in*/ NumericalizeFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  NumericalizeFeaturizer <int64> */
struct NumericalizeFeaturizer_int64_EstimatorHandle {};
struct NumericalizeFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_CreateEstimator(/*out*/ NumericalizeFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_DestroyEstimator(/*in*/ NumericalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_GetState(/*in*/ NumericalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_IsTrainingComplete(/*in*/ NumericalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_Fit(/*in*/ NumericalizeFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_FitBuffer(/*in*/ NumericalizeFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_OnDataCompleted(/*in*/ NumericalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_CompleteTraining(/*in*/ NumericalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ NumericalizeFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ NumericalizeFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ NumericalizeFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_DestroyTransformer(/*in*/ NumericalizeFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_CreateTransformerSaveData(/*in*/ NumericalizeFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_Transform(/*in*/ NumericalizeFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_int64_Flush(/*in*/ NumericalizeFeaturizer_int64_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  NumericalizeFeaturizer <uint64> */
struct NumericalizeFeaturizer_uint64_EstimatorHandle {};
struct NumericalizeFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_CreateEstimator(/*out*/ NumericalizeFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_DestroyEstimator(/*in*/ NumericalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_GetState(/*in*/ NumericalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_IsTrainingComplete(/*in*/ NumericalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_Fit(/*in*/ NumericalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_FitBuffer(/*in*/ NumericalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_OnDataCompleted(/*in*/ NumericalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_CompleteTraining(/*in*/ NumericalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ NumericalizeFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ NumericalizeFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ NumericalizeFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_DestroyTransformer(/*in*/ NumericalizeFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_CreateTransformerSaveData(/*in*/ NumericalizeFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_Transform(/*in*/ NumericalizeFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_uint64_Flush(/*in*/ NumericalizeFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  NumericalizeFeaturizer <float> */
struct NumericalizeFeaturizer_float_EstimatorHandle {};
struct NumericalizeFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_CreateEstimator(/*out*/ NumericalizeFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_DestroyEstimator(/*in*/ NumericalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_GetState(/*in*/ NumericalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_IsTrainingComplete(/*in*/ NumericalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_Fit(/*in*/ NumericalizeFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_FitBuffer(/*in*/ NumericalizeFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_OnDataCompleted(/*in*/ NumericalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_CompleteTraining(/*in*/ NumericalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_CreateTransformerFromEstimator(/*in*/ NumericalizeFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ NumericalizeFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ NumericalizeFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_DestroyTransformer(/*in*/ NumericalizeFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_CreateTransformerSaveData(/*in*/ NumericalizeFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_Transform(/*in*/ NumericalizeFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_float_Flush(/*in*/ NumericalizeFeaturizer_float_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  NumericalizeFeaturizer <double> */
struct NumericalizeFeaturizer_double_EstimatorHandle {};
struct NumericalizeFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_CreateEstimator(/*out*/ NumericalizeFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_DestroyEstimator(/*in*/ NumericalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_GetState(/*in*/ NumericalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_IsTrainingComplete(/*in*/ NumericalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_Fit(/*in*/ NumericalizeFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_FitBuffer(/*in*/ NumericalizeFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_OnDataCompleted(/*in*/ NumericalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_CompleteTraining(/*in*/ NumericalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_CreateTransformerFromEstimator(/*in*/ NumericalizeFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ NumericalizeFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ NumericalizeFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_DestroyTransformer(/*in*/ NumericalizeFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_CreateTransformerSaveData(/*in*/ NumericalizeFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_Transform(/*in*/ NumericalizeFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_double_Flush(/*in*/ NumericalizeFeaturizer_double_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  NumericalizeFeaturizer <bool> */
struct NumericalizeFeaturizer_bool_EstimatorHandle {};
struct NumericalizeFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_CreateEstimator(/*out*/ NumericalizeFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_DestroyEstimator(/*in*/ NumericalizeFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_GetState(/*in*/ NumericalizeFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_IsTrainingComplete(/*in*/ NumericalizeFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_Fit(/*in*/ NumericalizeFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_FitBuffer(/*in*/ NumericalizeFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_OnDataCompleted(/*in*/ NumericalizeFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_CompleteTraining(/*in*/ NumericalizeFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ NumericalizeFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ NumericalizeFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ NumericalizeFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_DestroyTransformer(/*in*/ NumericalizeFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_CreateTransformerSaveData(/*in*/ NumericalizeFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_Transform(/*in*/ NumericalizeFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_bool_Flush(/*in*/ NumericalizeFeaturizer_bool_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  NumericalizeFeaturizer <string> */
struct NumericalizeFeaturizer_string_EstimatorHandle {};
struct NumericalizeFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_CreateEstimator(/*out*/ NumericalizeFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_DestroyEstimator(/*in*/ NumericalizeFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_GetState(/*in*/ NumericalizeFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_IsTrainingComplete(/*in*/ NumericalizeFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_Fit(/*in*/ NumericalizeFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_FitBuffer(/*in*/ NumericalizeFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_OnDataCompleted(/*in*/ NumericalizeFeaturizer_string_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_CompleteTraining(/*in*/ NumericalizeFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_CreateTransformerFromEstimator(/*in*/ NumericalizeFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ NumericalizeFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ NumericalizeFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_DestroyTransformer(/*in*/ NumericalizeFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_CreateTransformerSaveData(/*in*/ NumericalizeFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_Transform(/*in*/ NumericalizeFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const * input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool NumericalizeFeaturizer_string_Flush(/*in*/ NumericalizeFeaturizer_string_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
