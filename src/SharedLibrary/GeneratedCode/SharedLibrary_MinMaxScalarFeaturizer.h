/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <int8> */
struct MinMaxScalarFeaturizer_int8_EstimatorHandle {};
struct MinMaxScalarFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_GetState(/*in*/ MinMaxScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_Fit(/*in*/ MinMaxScalarFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_FitBuffer(/*in*/ MinMaxScalarFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_Transform(/*in*/ MinMaxScalarFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <int16> */
struct MinMaxScalarFeaturizer_int16_EstimatorHandle {};
struct MinMaxScalarFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_GetState(/*in*/ MinMaxScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_Fit(/*in*/ MinMaxScalarFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_FitBuffer(/*in*/ MinMaxScalarFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_Transform(/*in*/ MinMaxScalarFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <int32> */
struct MinMaxScalarFeaturizer_int32_EstimatorHandle {};
struct MinMaxScalarFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_GetState(/*in*/ MinMaxScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_Fit(/*in*/ MinMaxScalarFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_FitBuffer(/*in*/ MinMaxScalarFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_Transform(/*in*/ MinMaxScalarFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <int64> */
struct MinMaxScalarFeaturizer_int64_EstimatorHandle {};
struct MinMaxScalarFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_GetState(/*in*/ MinMaxScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_Fit(/*in*/ MinMaxScalarFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_FitBuffer(/*in*/ MinMaxScalarFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_Transform(/*in*/ MinMaxScalarFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <uint8> */
struct MinMaxScalarFeaturizer_uint8_EstimatorHandle {};
struct MinMaxScalarFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_GetState(/*in*/ MinMaxScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_Fit(/*in*/ MinMaxScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_FitBuffer(/*in*/ MinMaxScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_Transform(/*in*/ MinMaxScalarFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <uint16> */
struct MinMaxScalarFeaturizer_uint16_EstimatorHandle {};
struct MinMaxScalarFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_GetState(/*in*/ MinMaxScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_Fit(/*in*/ MinMaxScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_FitBuffer(/*in*/ MinMaxScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_Transform(/*in*/ MinMaxScalarFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <uint32> */
struct MinMaxScalarFeaturizer_uint32_EstimatorHandle {};
struct MinMaxScalarFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_GetState(/*in*/ MinMaxScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_Fit(/*in*/ MinMaxScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_FitBuffer(/*in*/ MinMaxScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_Transform(/*in*/ MinMaxScalarFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <uint64> */
struct MinMaxScalarFeaturizer_uint64_EstimatorHandle {};
struct MinMaxScalarFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_GetState(/*in*/ MinMaxScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_Fit(/*in*/ MinMaxScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_FitBuffer(/*in*/ MinMaxScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_Transform(/*in*/ MinMaxScalarFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <float> */
struct MinMaxScalarFeaturizer_float_EstimatorHandle {};
struct MinMaxScalarFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_GetState(/*in*/ MinMaxScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_Fit(/*in*/ MinMaxScalarFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_FitBuffer(/*in*/ MinMaxScalarFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_Transform(/*in*/ MinMaxScalarFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <double> */
struct MinMaxScalarFeaturizer_double_EstimatorHandle {};
struct MinMaxScalarFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_GetState(/*in*/ MinMaxScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_Fit(/*in*/ MinMaxScalarFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_FitBuffer(/*in*/ MinMaxScalarFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_Transform(/*in*/ MinMaxScalarFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
