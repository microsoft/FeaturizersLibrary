/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int8> */
struct ImputationMarkerFeaturizer_int8_EstimatorHandle {};
struct ImputationMarkerFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_GetState(/*in*/ ImputationMarkerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_Fit(/*in*/ ImputationMarkerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_FitBuffer(/*in*/ ImputationMarkerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_OnDataCompleted(/*in*/ ImputationMarkerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_Transform(/*in*/ ImputationMarkerFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_Flush(/*in*/ ImputationMarkerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int16> */
struct ImputationMarkerFeaturizer_int16_EstimatorHandle {};
struct ImputationMarkerFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_GetState(/*in*/ ImputationMarkerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_Fit(/*in*/ ImputationMarkerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_FitBuffer(/*in*/ ImputationMarkerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_OnDataCompleted(/*in*/ ImputationMarkerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_Transform(/*in*/ ImputationMarkerFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_Flush(/*in*/ ImputationMarkerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int32> */
struct ImputationMarkerFeaturizer_int32_EstimatorHandle {};
struct ImputationMarkerFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_GetState(/*in*/ ImputationMarkerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_Fit(/*in*/ ImputationMarkerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_FitBuffer(/*in*/ ImputationMarkerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_OnDataCompleted(/*in*/ ImputationMarkerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_Transform(/*in*/ ImputationMarkerFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_Flush(/*in*/ ImputationMarkerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int64> */
struct ImputationMarkerFeaturizer_int64_EstimatorHandle {};
struct ImputationMarkerFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_GetState(/*in*/ ImputationMarkerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_Fit(/*in*/ ImputationMarkerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_FitBuffer(/*in*/ ImputationMarkerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_OnDataCompleted(/*in*/ ImputationMarkerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_Transform(/*in*/ ImputationMarkerFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_Flush(/*in*/ ImputationMarkerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint8> */
struct ImputationMarkerFeaturizer_uint8_EstimatorHandle {};
struct ImputationMarkerFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_GetState(/*in*/ ImputationMarkerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_Fit(/*in*/ ImputationMarkerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_FitBuffer(/*in*/ ImputationMarkerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_OnDataCompleted(/*in*/ ImputationMarkerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_Transform(/*in*/ ImputationMarkerFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_Flush(/*in*/ ImputationMarkerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint16> */
struct ImputationMarkerFeaturizer_uint16_EstimatorHandle {};
struct ImputationMarkerFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_GetState(/*in*/ ImputationMarkerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_Fit(/*in*/ ImputationMarkerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_FitBuffer(/*in*/ ImputationMarkerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_OnDataCompleted(/*in*/ ImputationMarkerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_Transform(/*in*/ ImputationMarkerFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_Flush(/*in*/ ImputationMarkerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint32> */
struct ImputationMarkerFeaturizer_uint32_EstimatorHandle {};
struct ImputationMarkerFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_GetState(/*in*/ ImputationMarkerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_Fit(/*in*/ ImputationMarkerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_FitBuffer(/*in*/ ImputationMarkerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_OnDataCompleted(/*in*/ ImputationMarkerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_Transform(/*in*/ ImputationMarkerFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_Flush(/*in*/ ImputationMarkerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint64> */
struct ImputationMarkerFeaturizer_uint64_EstimatorHandle {};
struct ImputationMarkerFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_GetState(/*in*/ ImputationMarkerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_Fit(/*in*/ ImputationMarkerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_FitBuffer(/*in*/ ImputationMarkerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_OnDataCompleted(/*in*/ ImputationMarkerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_Transform(/*in*/ ImputationMarkerFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_Flush(/*in*/ ImputationMarkerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <float> */
struct ImputationMarkerFeaturizer_float_EstimatorHandle {};
struct ImputationMarkerFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_GetState(/*in*/ ImputationMarkerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_Fit(/*in*/ ImputationMarkerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_FitBuffer(/*in*/ ImputationMarkerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_OnDataCompleted(/*in*/ ImputationMarkerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_Transform(/*in*/ ImputationMarkerFeaturizer_float_TransformerHandle *pHandle, /*in*/ float const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_Flush(/*in*/ ImputationMarkerFeaturizer_float_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <double> */
struct ImputationMarkerFeaturizer_double_EstimatorHandle {};
struct ImputationMarkerFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_GetState(/*in*/ ImputationMarkerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_Fit(/*in*/ ImputationMarkerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_FitBuffer(/*in*/ ImputationMarkerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_OnDataCompleted(/*in*/ ImputationMarkerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_Transform(/*in*/ ImputationMarkerFeaturizer_double_TransformerHandle *pHandle, /*in*/ double const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_Flush(/*in*/ ImputationMarkerFeaturizer_double_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <bool> */
struct ImputationMarkerFeaturizer_bool_EstimatorHandle {};
struct ImputationMarkerFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_GetState(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_Fit(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_FitBuffer(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_OnDataCompleted(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_Transform(/*in*/ ImputationMarkerFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_Flush(/*in*/ ImputationMarkerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <string> */
struct ImputationMarkerFeaturizer_string_EstimatorHandle {};
struct ImputationMarkerFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_GetState(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_Fit(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_FitBuffer(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_OnDataCompleted(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_Transform(/*in*/ ImputationMarkerFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_Flush(/*in*/ ImputationMarkerFeaturizer_string_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
