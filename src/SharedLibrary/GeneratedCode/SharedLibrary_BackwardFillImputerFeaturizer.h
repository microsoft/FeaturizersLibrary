/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <int8> */
struct BackwardFillImputerFeaturizer_int8_EstimatorHandle {};
struct BackwardFillImputerFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_GetState(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_Fit(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_Transform(/*in*/ BackwardFillImputerFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t const * input, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_Flush(/*in*/ BackwardFillImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_DestroyTransformedData(/*in*/ int8_t const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <int16> */
struct BackwardFillImputerFeaturizer_int16_EstimatorHandle {};
struct BackwardFillImputerFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_GetState(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_Fit(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_Transform(/*in*/ BackwardFillImputerFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t const * input, /*out*/ int16_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_Flush(/*in*/ BackwardFillImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ int16_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_DestroyTransformedData(/*in*/ int16_t const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <int32> */
struct BackwardFillImputerFeaturizer_int32_EstimatorHandle {};
struct BackwardFillImputerFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_GetState(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_Fit(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_Transform(/*in*/ BackwardFillImputerFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t const * input, /*out*/ int32_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_Flush(/*in*/ BackwardFillImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ int32_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_DestroyTransformedData(/*in*/ int32_t const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <int64> */
struct BackwardFillImputerFeaturizer_int64_EstimatorHandle {};
struct BackwardFillImputerFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_GetState(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_Fit(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_Transform(/*in*/ BackwardFillImputerFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t const * input, /*out*/ int64_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_Flush(/*in*/ BackwardFillImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ int64_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_DestroyTransformedData(/*in*/ int64_t const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <uint8> */
struct BackwardFillImputerFeaturizer_uint8_EstimatorHandle {};
struct BackwardFillImputerFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_GetState(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_Fit(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_Transform(/*in*/ BackwardFillImputerFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ uint8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_Flush(/*in*/ BackwardFillImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ uint8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_DestroyTransformedData(/*in*/ uint8_t const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <uint16> */
struct BackwardFillImputerFeaturizer_uint16_EstimatorHandle {};
struct BackwardFillImputerFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_GetState(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_Fit(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_Transform(/*in*/ BackwardFillImputerFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ uint16_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_Flush(/*in*/ BackwardFillImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ uint16_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_DestroyTransformedData(/*in*/ uint16_t const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <uint32> */
struct BackwardFillImputerFeaturizer_uint32_EstimatorHandle {};
struct BackwardFillImputerFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_GetState(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_Fit(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_Transform(/*in*/ BackwardFillImputerFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ uint32_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_Flush(/*in*/ BackwardFillImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ uint32_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_DestroyTransformedData(/*in*/ uint32_t const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <uint64> */
struct BackwardFillImputerFeaturizer_uint64_EstimatorHandle {};
struct BackwardFillImputerFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_GetState(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_Fit(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_Transform(/*in*/ BackwardFillImputerFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ uint64_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_Flush(/*in*/ BackwardFillImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_DestroyTransformedData(/*in*/ uint64_t const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <float> */
struct BackwardFillImputerFeaturizer_float_EstimatorHandle {};
struct BackwardFillImputerFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_GetState(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_Fit(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_Transform(/*in*/ BackwardFillImputerFeaturizer_float_TransformerHandle *pHandle, /*in*/ float const * input, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_Flush(/*in*/ BackwardFillImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_DestroyTransformedData(/*in*/ float const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <double> */
struct BackwardFillImputerFeaturizer_double_EstimatorHandle {};
struct BackwardFillImputerFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_GetState(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_Fit(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_Transform(/*in*/ BackwardFillImputerFeaturizer_double_TransformerHandle *pHandle, /*in*/ double const * input, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_Flush(/*in*/ BackwardFillImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_DestroyTransformedData(/*in*/ double const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <bool> */
struct BackwardFillImputerFeaturizer_bool_EstimatorHandle {};
struct BackwardFillImputerFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_GetState(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_Fit(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_Transform(/*in*/ BackwardFillImputerFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool const * input, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_Flush(/*in*/ BackwardFillImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_DestroyTransformedData(/*in*/ bool const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <string> */
struct BackwardFillImputerFeaturizer_string_EstimatorHandle {};
struct BackwardFillImputerFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_GetState(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_Fit(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_Transform(/*in*/ BackwardFillImputerFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const * input, /*out*/ char const *** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_Flush(/*in*/ BackwardFillImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ char const *** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_DestroyTransformedData(/*in*/ char const * const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
