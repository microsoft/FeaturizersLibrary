/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <int8_t> */
struct MinMaxScalarFeaturizer_int8_t_EstimatorHandle {};
struct MinMaxScalarFeaturizer_int8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_t_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_int8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_t_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_t_GetState(/*in*/ MinMaxScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_t_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_t_Fit(/*in*/ MinMaxScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_t_FitBuffer(/*in*/ MinMaxScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_t_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_t_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_t_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_t_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_t_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int8_t_Transform(/*in*/ MinMaxScalarFeaturizer_int8_t_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <int16_t> */
struct MinMaxScalarFeaturizer_int16_t_EstimatorHandle {};
struct MinMaxScalarFeaturizer_int16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_t_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_int16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_t_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_t_GetState(/*in*/ MinMaxScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_t_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_t_Fit(/*in*/ MinMaxScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_t_FitBuffer(/*in*/ MinMaxScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_t_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_t_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_t_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_t_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_t_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int16_t_Transform(/*in*/ MinMaxScalarFeaturizer_int16_t_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <int32_t> */
struct MinMaxScalarFeaturizer_int32_t_EstimatorHandle {};
struct MinMaxScalarFeaturizer_int32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_t_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_int32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_t_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_t_GetState(/*in*/ MinMaxScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_t_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_t_Fit(/*in*/ MinMaxScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_t_FitBuffer(/*in*/ MinMaxScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_t_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_t_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_t_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_t_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_t_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int32_t_Transform(/*in*/ MinMaxScalarFeaturizer_int32_t_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <int64_t> */
struct MinMaxScalarFeaturizer_int64_t_EstimatorHandle {};
struct MinMaxScalarFeaturizer_int64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_t_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_int64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_t_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_t_GetState(/*in*/ MinMaxScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_t_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_t_Fit(/*in*/ MinMaxScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_t_FitBuffer(/*in*/ MinMaxScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_t_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_t_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_t_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_t_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_t_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_int64_t_Transform(/*in*/ MinMaxScalarFeaturizer_int64_t_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <uint8_t> */
struct MinMaxScalarFeaturizer_uint8_t_EstimatorHandle {};
struct MinMaxScalarFeaturizer_uint8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_t_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_uint8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_t_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_t_GetState(/*in*/ MinMaxScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_t_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_t_Fit(/*in*/ MinMaxScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_t_FitBuffer(/*in*/ MinMaxScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_t_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_t_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_t_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_t_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_t_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint8_t_Transform(/*in*/ MinMaxScalarFeaturizer_uint8_t_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <uint16_t> */
struct MinMaxScalarFeaturizer_uint16_t_EstimatorHandle {};
struct MinMaxScalarFeaturizer_uint16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_t_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_uint16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_t_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_t_GetState(/*in*/ MinMaxScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_t_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_t_Fit(/*in*/ MinMaxScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_t_FitBuffer(/*in*/ MinMaxScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_t_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_t_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_t_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_t_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_t_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint16_t_Transform(/*in*/ MinMaxScalarFeaturizer_uint16_t_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <uint32_t> */
struct MinMaxScalarFeaturizer_uint32_t_EstimatorHandle {};
struct MinMaxScalarFeaturizer_uint32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_t_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_uint32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_t_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_t_GetState(/*in*/ MinMaxScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_t_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_t_Fit(/*in*/ MinMaxScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_t_FitBuffer(/*in*/ MinMaxScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_t_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_t_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_t_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_t_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_t_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint32_t_Transform(/*in*/ MinMaxScalarFeaturizer_uint32_t_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <uint64_t> */
struct MinMaxScalarFeaturizer_uint64_t_EstimatorHandle {};
struct MinMaxScalarFeaturizer_uint64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_t_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_uint64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_t_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_t_GetState(/*in*/ MinMaxScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_t_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_t_Fit(/*in*/ MinMaxScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_t_FitBuffer(/*in*/ MinMaxScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_t_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_t_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_t_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_t_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_t_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_uint64_t_Transform(/*in*/ MinMaxScalarFeaturizer_uint64_t_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <float_t> */
struct MinMaxScalarFeaturizer_float_t_EstimatorHandle {};
struct MinMaxScalarFeaturizer_float_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_t_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_float_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_t_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_t_GetState(/*in*/ MinMaxScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_t_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_t_Fit(/*in*/ MinMaxScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_t_FitBuffer(/*in*/ MinMaxScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_t_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_t_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_t_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_float_t_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_t_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_t_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_float_t_Transform(/*in*/ MinMaxScalarFeaturizer_float_t_TransformerHandle *pHandle, /*in*/ float input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxScalarFeaturizer <double_t> */
struct MinMaxScalarFeaturizer_double_t_EstimatorHandle {};
struct MinMaxScalarFeaturizer_double_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_t_CreateEstimator(/*out*/ MinMaxScalarFeaturizer_double_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_t_DestroyEstimator(/*in*/ MinMaxScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_t_GetState(/*in*/ MinMaxScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_t_IsTrainingComplete(/*in*/ MinMaxScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_t_Fit(/*in*/ MinMaxScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_t_FitBuffer(/*in*/ MinMaxScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_t_OnDataCompleted(/*in*/ MinMaxScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_t_CompleteTraining(/*in*/ MinMaxScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_t_CreateTransformerFromEstimator(/*in*/ MinMaxScalarFeaturizer_double_t_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxScalarFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MinMaxScalarFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_t_DestroyTransformer(/*in*/ MinMaxScalarFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_t_CreateTransformerSaveData(/*in*/ MinMaxScalarFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxScalarFeaturizer_double_t_Transform(/*in*/ MinMaxScalarFeaturizer_double_t_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
