/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <int8> */
struct ForwardFillImputerFeaturizer_int8_EstimatorHandle {};
struct ForwardFillImputerFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_CreateEstimator(/*out*/ ForwardFillImputerFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_DestroyEstimator(/*in*/ ForwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_GetState(/*in*/ ForwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_IsTrainingComplete(/*in*/ ForwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_Fit(/*in*/ ForwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_FitBuffer(/*in*/ ForwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_OnDataCompleted(/*in*/ ForwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_CompleteTraining(/*in*/ ForwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ ForwardFillImputerFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ ForwardFillImputerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForwardFillImputerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_DestroyTransformer(/*in*/ ForwardFillImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_CreateTransformerSaveData(/*in*/ ForwardFillImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_Transform(/*in*/ ForwardFillImputerFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int8_Flush(/*in*/ ForwardFillImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <int16> */
struct ForwardFillImputerFeaturizer_int16_EstimatorHandle {};
struct ForwardFillImputerFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_CreateEstimator(/*out*/ ForwardFillImputerFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_DestroyEstimator(/*in*/ ForwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_GetState(/*in*/ ForwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_IsTrainingComplete(/*in*/ ForwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_Fit(/*in*/ ForwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_FitBuffer(/*in*/ ForwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_OnDataCompleted(/*in*/ ForwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_CompleteTraining(/*in*/ ForwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ ForwardFillImputerFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ ForwardFillImputerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForwardFillImputerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_DestroyTransformer(/*in*/ ForwardFillImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_CreateTransformerSaveData(/*in*/ ForwardFillImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_Transform(/*in*/ ForwardFillImputerFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t const * input, /*out*/ int16_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int16_Flush(/*in*/ ForwardFillImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ int16_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <int32> */
struct ForwardFillImputerFeaturizer_int32_EstimatorHandle {};
struct ForwardFillImputerFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_CreateEstimator(/*out*/ ForwardFillImputerFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_DestroyEstimator(/*in*/ ForwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_GetState(/*in*/ ForwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_IsTrainingComplete(/*in*/ ForwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_Fit(/*in*/ ForwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_FitBuffer(/*in*/ ForwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_OnDataCompleted(/*in*/ ForwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_CompleteTraining(/*in*/ ForwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ ForwardFillImputerFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ ForwardFillImputerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForwardFillImputerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_DestroyTransformer(/*in*/ ForwardFillImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_CreateTransformerSaveData(/*in*/ ForwardFillImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_Transform(/*in*/ ForwardFillImputerFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t const * input, /*out*/ int32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int32_Flush(/*in*/ ForwardFillImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ int32_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <int64> */
struct ForwardFillImputerFeaturizer_int64_EstimatorHandle {};
struct ForwardFillImputerFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_CreateEstimator(/*out*/ ForwardFillImputerFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_DestroyEstimator(/*in*/ ForwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_GetState(/*in*/ ForwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_IsTrainingComplete(/*in*/ ForwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_Fit(/*in*/ ForwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_FitBuffer(/*in*/ ForwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_OnDataCompleted(/*in*/ ForwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_CompleteTraining(/*in*/ ForwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ ForwardFillImputerFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ ForwardFillImputerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForwardFillImputerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_DestroyTransformer(/*in*/ ForwardFillImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_CreateTransformerSaveData(/*in*/ ForwardFillImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_Transform(/*in*/ ForwardFillImputerFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t const * input, /*out*/ int64_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_int64_Flush(/*in*/ ForwardFillImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ int64_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <uint8> */
struct ForwardFillImputerFeaturizer_uint8_EstimatorHandle {};
struct ForwardFillImputerFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_CreateEstimator(/*out*/ ForwardFillImputerFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_DestroyEstimator(/*in*/ ForwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_GetState(/*in*/ ForwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_IsTrainingComplete(/*in*/ ForwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_Fit(/*in*/ ForwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_FitBuffer(/*in*/ ForwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_OnDataCompleted(/*in*/ ForwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_CompleteTraining(/*in*/ ForwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ ForwardFillImputerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ ForwardFillImputerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForwardFillImputerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_DestroyTransformer(/*in*/ ForwardFillImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_CreateTransformerSaveData(/*in*/ ForwardFillImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_Transform(/*in*/ ForwardFillImputerFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ uint8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint8_Flush(/*in*/ ForwardFillImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ uint8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <uint16> */
struct ForwardFillImputerFeaturizer_uint16_EstimatorHandle {};
struct ForwardFillImputerFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_CreateEstimator(/*out*/ ForwardFillImputerFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_DestroyEstimator(/*in*/ ForwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_GetState(/*in*/ ForwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_IsTrainingComplete(/*in*/ ForwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_Fit(/*in*/ ForwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_FitBuffer(/*in*/ ForwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_OnDataCompleted(/*in*/ ForwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_CompleteTraining(/*in*/ ForwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ ForwardFillImputerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ ForwardFillImputerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForwardFillImputerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_DestroyTransformer(/*in*/ ForwardFillImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_CreateTransformerSaveData(/*in*/ ForwardFillImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_Transform(/*in*/ ForwardFillImputerFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ uint16_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint16_Flush(/*in*/ ForwardFillImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ uint16_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <uint32> */
struct ForwardFillImputerFeaturizer_uint32_EstimatorHandle {};
struct ForwardFillImputerFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_CreateEstimator(/*out*/ ForwardFillImputerFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_DestroyEstimator(/*in*/ ForwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_GetState(/*in*/ ForwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_IsTrainingComplete(/*in*/ ForwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_Fit(/*in*/ ForwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_FitBuffer(/*in*/ ForwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_OnDataCompleted(/*in*/ ForwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_CompleteTraining(/*in*/ ForwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ ForwardFillImputerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ ForwardFillImputerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForwardFillImputerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_DestroyTransformer(/*in*/ ForwardFillImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_CreateTransformerSaveData(/*in*/ ForwardFillImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_Transform(/*in*/ ForwardFillImputerFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint32_Flush(/*in*/ ForwardFillImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ uint32_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <uint64> */
struct ForwardFillImputerFeaturizer_uint64_EstimatorHandle {};
struct ForwardFillImputerFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_CreateEstimator(/*out*/ ForwardFillImputerFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_DestroyEstimator(/*in*/ ForwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_GetState(/*in*/ ForwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_IsTrainingComplete(/*in*/ ForwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_Fit(/*in*/ ForwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_FitBuffer(/*in*/ ForwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_OnDataCompleted(/*in*/ ForwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_CompleteTraining(/*in*/ ForwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ ForwardFillImputerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ ForwardFillImputerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForwardFillImputerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_DestroyTransformer(/*in*/ ForwardFillImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_CreateTransformerSaveData(/*in*/ ForwardFillImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_Transform(/*in*/ ForwardFillImputerFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ uint64_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_uint64_Flush(/*in*/ ForwardFillImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <float> */
struct ForwardFillImputerFeaturizer_float_EstimatorHandle {};
struct ForwardFillImputerFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_CreateEstimator(/*out*/ ForwardFillImputerFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_DestroyEstimator(/*in*/ ForwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_GetState(/*in*/ ForwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_IsTrainingComplete(/*in*/ ForwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_Fit(/*in*/ ForwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_FitBuffer(/*in*/ ForwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_OnDataCompleted(/*in*/ ForwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_CompleteTraining(/*in*/ ForwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_CreateTransformerFromEstimator(/*in*/ ForwardFillImputerFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ ForwardFillImputerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForwardFillImputerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_DestroyTransformer(/*in*/ ForwardFillImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_CreateTransformerSaveData(/*in*/ ForwardFillImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_Transform(/*in*/ ForwardFillImputerFeaturizer_float_TransformerHandle *pHandle, /*in*/ float const * input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_float_Flush(/*in*/ ForwardFillImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <double> */
struct ForwardFillImputerFeaturizer_double_EstimatorHandle {};
struct ForwardFillImputerFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_CreateEstimator(/*out*/ ForwardFillImputerFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_DestroyEstimator(/*in*/ ForwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_GetState(/*in*/ ForwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_IsTrainingComplete(/*in*/ ForwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_Fit(/*in*/ ForwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_FitBuffer(/*in*/ ForwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_OnDataCompleted(/*in*/ ForwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_CompleteTraining(/*in*/ ForwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_CreateTransformerFromEstimator(/*in*/ ForwardFillImputerFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ ForwardFillImputerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForwardFillImputerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_DestroyTransformer(/*in*/ ForwardFillImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_CreateTransformerSaveData(/*in*/ ForwardFillImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_Transform(/*in*/ ForwardFillImputerFeaturizer_double_TransformerHandle *pHandle, /*in*/ double const * input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_double_Flush(/*in*/ ForwardFillImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <bool> */
struct ForwardFillImputerFeaturizer_bool_EstimatorHandle {};
struct ForwardFillImputerFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_CreateEstimator(/*out*/ ForwardFillImputerFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_DestroyEstimator(/*in*/ ForwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_GetState(/*in*/ ForwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_IsTrainingComplete(/*in*/ ForwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_Fit(/*in*/ ForwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_FitBuffer(/*in*/ ForwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_OnDataCompleted(/*in*/ ForwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_CompleteTraining(/*in*/ ForwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ ForwardFillImputerFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ ForwardFillImputerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForwardFillImputerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_DestroyTransformer(/*in*/ ForwardFillImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_CreateTransformerSaveData(/*in*/ ForwardFillImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_Transform(/*in*/ ForwardFillImputerFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_bool_Flush(/*in*/ ForwardFillImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <string> */
struct ForwardFillImputerFeaturizer_string_EstimatorHandle {};
struct ForwardFillImputerFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_CreateEstimator(/*out*/ ForwardFillImputerFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_DestroyEstimator(/*in*/ ForwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_GetState(/*in*/ ForwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_IsTrainingComplete(/*in*/ ForwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_Fit(/*in*/ ForwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_FitBuffer(/*in*/ ForwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_OnDataCompleted(/*in*/ ForwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_CompleteTraining(/*in*/ ForwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_CreateTransformerFromEstimator(/*in*/ ForwardFillImputerFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ ForwardFillImputerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForwardFillImputerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_DestroyTransformer(/*in*/ ForwardFillImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_CreateTransformerSaveData(/*in*/ ForwardFillImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_Transform(/*in*/ ForwardFillImputerFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const * input, /*out*/ char const ** output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_Flush(/*in*/ ForwardFillImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ char const *** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForwardFillImputerFeaturizer_string_DestroyTransformedData(/*in*/ char const * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
