/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <int8> */
struct MaxAbsScalarFeaturizer_int8_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_GetState(/*in*/ MaxAbsScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_Fit(/*in*/ MaxAbsScalarFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_OnDataCompleted(/*in*/ MaxAbsScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_Transform(/*in*/ MaxAbsScalarFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <int16> */
struct MaxAbsScalarFeaturizer_int16_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_GetState(/*in*/ MaxAbsScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_Fit(/*in*/ MaxAbsScalarFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_OnDataCompleted(/*in*/ MaxAbsScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_Transform(/*in*/ MaxAbsScalarFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <uint8> */
struct MaxAbsScalarFeaturizer_uint8_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_GetState(/*in*/ MaxAbsScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_Fit(/*in*/ MaxAbsScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_OnDataCompleted(/*in*/ MaxAbsScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_Transform(/*in*/ MaxAbsScalarFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <uint16> */
struct MaxAbsScalarFeaturizer_uint16_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_GetState(/*in*/ MaxAbsScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_Fit(/*in*/ MaxAbsScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_OnDataCompleted(/*in*/ MaxAbsScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_Transform(/*in*/ MaxAbsScalarFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <float> */
struct MaxAbsScalarFeaturizer_float_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_GetState(/*in*/ MaxAbsScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_Fit(/*in*/ MaxAbsScalarFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_OnDataCompleted(/*in*/ MaxAbsScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_Transform(/*in*/ MaxAbsScalarFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <int32> */
struct MaxAbsScalarFeaturizer_int32_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_GetState(/*in*/ MaxAbsScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_Fit(/*in*/ MaxAbsScalarFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_OnDataCompleted(/*in*/ MaxAbsScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_Transform(/*in*/ MaxAbsScalarFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <int64> */
struct MaxAbsScalarFeaturizer_int64_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_GetState(/*in*/ MaxAbsScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_Fit(/*in*/ MaxAbsScalarFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_OnDataCompleted(/*in*/ MaxAbsScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_Transform(/*in*/ MaxAbsScalarFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <uint32> */
struct MaxAbsScalarFeaturizer_uint32_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_GetState(/*in*/ MaxAbsScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_Fit(/*in*/ MaxAbsScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_OnDataCompleted(/*in*/ MaxAbsScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_Transform(/*in*/ MaxAbsScalarFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <uint64> */
struct MaxAbsScalarFeaturizer_uint64_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_GetState(/*in*/ MaxAbsScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_Fit(/*in*/ MaxAbsScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_OnDataCompleted(/*in*/ MaxAbsScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_Transform(/*in*/ MaxAbsScalarFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <double> */
struct MaxAbsScalarFeaturizer_double_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_GetState(/*in*/ MaxAbsScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_Fit(/*in*/ MaxAbsScalarFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_OnDataCompleted(/*in*/ MaxAbsScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_Transform(/*in*/ MaxAbsScalarFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
