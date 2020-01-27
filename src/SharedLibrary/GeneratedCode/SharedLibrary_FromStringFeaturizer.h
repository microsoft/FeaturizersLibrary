/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  FromStringFeaturizer <int8> */
struct FromStringFeaturizer_int8_EstimatorHandle {};
struct FromStringFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int8_CreateEstimator(/*out*/ FromStringFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int8_DestroyEstimator(/*in*/ FromStringFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int8_GetState(/*in*/ FromStringFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int8_IsTrainingComplete(/*in*/ FromStringFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int8_Fit(/*in*/ FromStringFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int8_FitBuffer(/*in*/ FromStringFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int8_OnDataCompleted(/*in*/ FromStringFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int8_CompleteTraining(/*in*/ FromStringFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ FromStringFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ FromStringFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ FromStringFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int8_DestroyTransformer(/*in*/ FromStringFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int8_CreateTransformerSaveData(/*in*/ FromStringFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int8_Transform(/*in*/ FromStringFeaturizer_int8_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  FromStringFeaturizer <int16> */
struct FromStringFeaturizer_int16_EstimatorHandle {};
struct FromStringFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int16_CreateEstimator(/*out*/ FromStringFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int16_DestroyEstimator(/*in*/ FromStringFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int16_GetState(/*in*/ FromStringFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int16_IsTrainingComplete(/*in*/ FromStringFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int16_Fit(/*in*/ FromStringFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int16_FitBuffer(/*in*/ FromStringFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int16_OnDataCompleted(/*in*/ FromStringFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int16_CompleteTraining(/*in*/ FromStringFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ FromStringFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ FromStringFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ FromStringFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int16_DestroyTransformer(/*in*/ FromStringFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int16_CreateTransformerSaveData(/*in*/ FromStringFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int16_Transform(/*in*/ FromStringFeaturizer_int16_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ int16_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  FromStringFeaturizer <int32> */
struct FromStringFeaturizer_int32_EstimatorHandle {};
struct FromStringFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int32_CreateEstimator(/*out*/ FromStringFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int32_DestroyEstimator(/*in*/ FromStringFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int32_GetState(/*in*/ FromStringFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int32_IsTrainingComplete(/*in*/ FromStringFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int32_Fit(/*in*/ FromStringFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int32_FitBuffer(/*in*/ FromStringFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int32_OnDataCompleted(/*in*/ FromStringFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int32_CompleteTraining(/*in*/ FromStringFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ FromStringFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ FromStringFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ FromStringFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int32_DestroyTransformer(/*in*/ FromStringFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int32_CreateTransformerSaveData(/*in*/ FromStringFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int32_Transform(/*in*/ FromStringFeaturizer_int32_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ int32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  FromStringFeaturizer <int64> */
struct FromStringFeaturizer_int64_EstimatorHandle {};
struct FromStringFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int64_CreateEstimator(/*out*/ FromStringFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int64_DestroyEstimator(/*in*/ FromStringFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int64_GetState(/*in*/ FromStringFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int64_IsTrainingComplete(/*in*/ FromStringFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int64_Fit(/*in*/ FromStringFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int64_FitBuffer(/*in*/ FromStringFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int64_OnDataCompleted(/*in*/ FromStringFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int64_CompleteTraining(/*in*/ FromStringFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ FromStringFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ FromStringFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ FromStringFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int64_DestroyTransformer(/*in*/ FromStringFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int64_CreateTransformerSaveData(/*in*/ FromStringFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_int64_Transform(/*in*/ FromStringFeaturizer_int64_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ int64_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  FromStringFeaturizer <uint8> */
struct FromStringFeaturizer_uint8_EstimatorHandle {};
struct FromStringFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint8_CreateEstimator(/*out*/ FromStringFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint8_DestroyEstimator(/*in*/ FromStringFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint8_GetState(/*in*/ FromStringFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint8_IsTrainingComplete(/*in*/ FromStringFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint8_Fit(/*in*/ FromStringFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint8_FitBuffer(/*in*/ FromStringFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint8_OnDataCompleted(/*in*/ FromStringFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint8_CompleteTraining(/*in*/ FromStringFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ FromStringFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ FromStringFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ FromStringFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint8_DestroyTransformer(/*in*/ FromStringFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint8_CreateTransformerSaveData(/*in*/ FromStringFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint8_Transform(/*in*/ FromStringFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ uint8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  FromStringFeaturizer <uint16> */
struct FromStringFeaturizer_uint16_EstimatorHandle {};
struct FromStringFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint16_CreateEstimator(/*out*/ FromStringFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint16_DestroyEstimator(/*in*/ FromStringFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint16_GetState(/*in*/ FromStringFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint16_IsTrainingComplete(/*in*/ FromStringFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint16_Fit(/*in*/ FromStringFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint16_FitBuffer(/*in*/ FromStringFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint16_OnDataCompleted(/*in*/ FromStringFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint16_CompleteTraining(/*in*/ FromStringFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ FromStringFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ FromStringFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ FromStringFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint16_DestroyTransformer(/*in*/ FromStringFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint16_CreateTransformerSaveData(/*in*/ FromStringFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint16_Transform(/*in*/ FromStringFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ uint16_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  FromStringFeaturizer <uint32> */
struct FromStringFeaturizer_uint32_EstimatorHandle {};
struct FromStringFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint32_CreateEstimator(/*out*/ FromStringFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint32_DestroyEstimator(/*in*/ FromStringFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint32_GetState(/*in*/ FromStringFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint32_IsTrainingComplete(/*in*/ FromStringFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint32_Fit(/*in*/ FromStringFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint32_FitBuffer(/*in*/ FromStringFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint32_OnDataCompleted(/*in*/ FromStringFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint32_CompleteTraining(/*in*/ FromStringFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ FromStringFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ FromStringFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ FromStringFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint32_DestroyTransformer(/*in*/ FromStringFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint32_CreateTransformerSaveData(/*in*/ FromStringFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint32_Transform(/*in*/ FromStringFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  FromStringFeaturizer <uint64> */
struct FromStringFeaturizer_uint64_EstimatorHandle {};
struct FromStringFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint64_CreateEstimator(/*out*/ FromStringFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint64_DestroyEstimator(/*in*/ FromStringFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint64_GetState(/*in*/ FromStringFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint64_IsTrainingComplete(/*in*/ FromStringFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint64_Fit(/*in*/ FromStringFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint64_FitBuffer(/*in*/ FromStringFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint64_OnDataCompleted(/*in*/ FromStringFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint64_CompleteTraining(/*in*/ FromStringFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ FromStringFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ FromStringFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ FromStringFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint64_DestroyTransformer(/*in*/ FromStringFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint64_CreateTransformerSaveData(/*in*/ FromStringFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_uint64_Transform(/*in*/ FromStringFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ uint64_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  FromStringFeaturizer <float> */
struct FromStringFeaturizer_float_EstimatorHandle {};
struct FromStringFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_float_CreateEstimator(/*out*/ FromStringFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_float_DestroyEstimator(/*in*/ FromStringFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_float_GetState(/*in*/ FromStringFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_float_IsTrainingComplete(/*in*/ FromStringFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_float_Fit(/*in*/ FromStringFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_float_FitBuffer(/*in*/ FromStringFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_float_OnDataCompleted(/*in*/ FromStringFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_float_CompleteTraining(/*in*/ FromStringFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_float_CreateTransformerFromEstimator(/*in*/ FromStringFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ FromStringFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ FromStringFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_float_DestroyTransformer(/*in*/ FromStringFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_float_CreateTransformerSaveData(/*in*/ FromStringFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_float_Transform(/*in*/ FromStringFeaturizer_float_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  FromStringFeaturizer <double> */
struct FromStringFeaturizer_double_EstimatorHandle {};
struct FromStringFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_double_CreateEstimator(/*out*/ FromStringFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_double_DestroyEstimator(/*in*/ FromStringFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_double_GetState(/*in*/ FromStringFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_double_IsTrainingComplete(/*in*/ FromStringFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_double_Fit(/*in*/ FromStringFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_double_FitBuffer(/*in*/ FromStringFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_double_OnDataCompleted(/*in*/ FromStringFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_double_CompleteTraining(/*in*/ FromStringFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_double_CreateTransformerFromEstimator(/*in*/ FromStringFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ FromStringFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ FromStringFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_double_DestroyTransformer(/*in*/ FromStringFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_double_CreateTransformerSaveData(/*in*/ FromStringFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_double_Transform(/*in*/ FromStringFeaturizer_double_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  FromStringFeaturizer <bool> */
struct FromStringFeaturizer_bool_EstimatorHandle {};
struct FromStringFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_bool_CreateEstimator(/*out*/ FromStringFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_bool_DestroyEstimator(/*in*/ FromStringFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_bool_GetState(/*in*/ FromStringFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_bool_IsTrainingComplete(/*in*/ FromStringFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_bool_Fit(/*in*/ FromStringFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_bool_FitBuffer(/*in*/ FromStringFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_bool_OnDataCompleted(/*in*/ FromStringFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_bool_CompleteTraining(/*in*/ FromStringFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ FromStringFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ FromStringFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ FromStringFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_bool_DestroyTransformer(/*in*/ FromStringFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_bool_CreateTransformerSaveData(/*in*/ FromStringFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_bool_Transform(/*in*/ FromStringFeaturizer_bool_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  FromStringFeaturizer <string> */
struct FromStringFeaturizer_string_EstimatorHandle {};
struct FromStringFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_CreateEstimator(/*out*/ FromStringFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_DestroyEstimator(/*in*/ FromStringFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_GetState(/*in*/ FromStringFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_IsTrainingComplete(/*in*/ FromStringFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_Fit(/*in*/ FromStringFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_FitBuffer(/*in*/ FromStringFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_OnDataCompleted(/*in*/ FromStringFeaturizer_string_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_CompleteTraining(/*in*/ FromStringFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_CreateTransformerFromEstimator(/*in*/ FromStringFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ FromStringFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ FromStringFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_DestroyTransformer(/*in*/ FromStringFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_CreateTransformerSaveData(/*in*/ FromStringFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_Transform(/*in*/ FromStringFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool FromStringFeaturizer_string_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
