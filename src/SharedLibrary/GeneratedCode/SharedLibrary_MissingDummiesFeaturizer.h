/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int8> */
struct MissingDummiesFeaturizer_int8_EstimatorHandle {};
struct MissingDummiesFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_CreateEstimator(/*out*/ MissingDummiesFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_GetState(/*in*/ MissingDummiesFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_Fit(/*in*/ MissingDummiesFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_FitBuffer(/*in*/ MissingDummiesFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_OnDataCompleted(/*in*/ MissingDummiesFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_CompleteTraining(/*in*/ MissingDummiesFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_Transform(/*in*/ MissingDummiesFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_Flush(/*in*/ MissingDummiesFeaturizer_int8_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int16> */
struct MissingDummiesFeaturizer_int16_EstimatorHandle {};
struct MissingDummiesFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_CreateEstimator(/*out*/ MissingDummiesFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_GetState(/*in*/ MissingDummiesFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_Fit(/*in*/ MissingDummiesFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_FitBuffer(/*in*/ MissingDummiesFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_OnDataCompleted(/*in*/ MissingDummiesFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_CompleteTraining(/*in*/ MissingDummiesFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_Transform(/*in*/ MissingDummiesFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_Flush(/*in*/ MissingDummiesFeaturizer_int16_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int32> */
struct MissingDummiesFeaturizer_int32_EstimatorHandle {};
struct MissingDummiesFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_CreateEstimator(/*out*/ MissingDummiesFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_GetState(/*in*/ MissingDummiesFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_Fit(/*in*/ MissingDummiesFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_FitBuffer(/*in*/ MissingDummiesFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_OnDataCompleted(/*in*/ MissingDummiesFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_CompleteTraining(/*in*/ MissingDummiesFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_Transform(/*in*/ MissingDummiesFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_Flush(/*in*/ MissingDummiesFeaturizer_int32_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int64> */
struct MissingDummiesFeaturizer_int64_EstimatorHandle {};
struct MissingDummiesFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_CreateEstimator(/*out*/ MissingDummiesFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_GetState(/*in*/ MissingDummiesFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_Fit(/*in*/ MissingDummiesFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_FitBuffer(/*in*/ MissingDummiesFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_OnDataCompleted(/*in*/ MissingDummiesFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_CompleteTraining(/*in*/ MissingDummiesFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_Transform(/*in*/ MissingDummiesFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_Flush(/*in*/ MissingDummiesFeaturizer_int64_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint8> */
struct MissingDummiesFeaturizer_uint8_EstimatorHandle {};
struct MissingDummiesFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_CreateEstimator(/*out*/ MissingDummiesFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_GetState(/*in*/ MissingDummiesFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_Fit(/*in*/ MissingDummiesFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_FitBuffer(/*in*/ MissingDummiesFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_OnDataCompleted(/*in*/ MissingDummiesFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_CompleteTraining(/*in*/ MissingDummiesFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_Transform(/*in*/ MissingDummiesFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_Flush(/*in*/ MissingDummiesFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint16> */
struct MissingDummiesFeaturizer_uint16_EstimatorHandle {};
struct MissingDummiesFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_CreateEstimator(/*out*/ MissingDummiesFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_GetState(/*in*/ MissingDummiesFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_Fit(/*in*/ MissingDummiesFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_FitBuffer(/*in*/ MissingDummiesFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_OnDataCompleted(/*in*/ MissingDummiesFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_CompleteTraining(/*in*/ MissingDummiesFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_Transform(/*in*/ MissingDummiesFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_Flush(/*in*/ MissingDummiesFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint32> */
struct MissingDummiesFeaturizer_uint32_EstimatorHandle {};
struct MissingDummiesFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_CreateEstimator(/*out*/ MissingDummiesFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_GetState(/*in*/ MissingDummiesFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_Fit(/*in*/ MissingDummiesFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_FitBuffer(/*in*/ MissingDummiesFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_OnDataCompleted(/*in*/ MissingDummiesFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_CompleteTraining(/*in*/ MissingDummiesFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_Transform(/*in*/ MissingDummiesFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_Flush(/*in*/ MissingDummiesFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint64> */
struct MissingDummiesFeaturizer_uint64_EstimatorHandle {};
struct MissingDummiesFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_CreateEstimator(/*out*/ MissingDummiesFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_GetState(/*in*/ MissingDummiesFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_Fit(/*in*/ MissingDummiesFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_FitBuffer(/*in*/ MissingDummiesFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_OnDataCompleted(/*in*/ MissingDummiesFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_CompleteTraining(/*in*/ MissingDummiesFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_Transform(/*in*/ MissingDummiesFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_Flush(/*in*/ MissingDummiesFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <float> */
struct MissingDummiesFeaturizer_float_EstimatorHandle {};
struct MissingDummiesFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_CreateEstimator(/*out*/ MissingDummiesFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_GetState(/*in*/ MissingDummiesFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_Fit(/*in*/ MissingDummiesFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_FitBuffer(/*in*/ MissingDummiesFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_OnDataCompleted(/*in*/ MissingDummiesFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_CompleteTraining(/*in*/ MissingDummiesFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_Transform(/*in*/ MissingDummiesFeaturizer_float_TransformerHandle *pHandle, /*in*/ float const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_Flush(/*in*/ MissingDummiesFeaturizer_float_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <double> */
struct MissingDummiesFeaturizer_double_EstimatorHandle {};
struct MissingDummiesFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_CreateEstimator(/*out*/ MissingDummiesFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_GetState(/*in*/ MissingDummiesFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_Fit(/*in*/ MissingDummiesFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_FitBuffer(/*in*/ MissingDummiesFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_OnDataCompleted(/*in*/ MissingDummiesFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_CompleteTraining(/*in*/ MissingDummiesFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_Transform(/*in*/ MissingDummiesFeaturizer_double_TransformerHandle *pHandle, /*in*/ double const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_Flush(/*in*/ MissingDummiesFeaturizer_double_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <bool> */
struct MissingDummiesFeaturizer_bool_EstimatorHandle {};
struct MissingDummiesFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_CreateEstimator(/*out*/ MissingDummiesFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_GetState(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_Fit(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_FitBuffer(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_OnDataCompleted(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_CompleteTraining(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_Transform(/*in*/ MissingDummiesFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_Flush(/*in*/ MissingDummiesFeaturizer_bool_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <string> */
struct MissingDummiesFeaturizer_string_EstimatorHandle {};
struct MissingDummiesFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_CreateEstimator(/*out*/ MissingDummiesFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_GetState(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_Fit(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_FitBuffer(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_OnDataCompleted(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_CompleteTraining(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_Transform(/*in*/ MissingDummiesFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_Flush(/*in*/ MissingDummiesFeaturizer_string_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
