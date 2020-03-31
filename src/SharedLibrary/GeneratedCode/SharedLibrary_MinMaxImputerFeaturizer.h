/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  MinMaxImputerFeaturizer <int8> */
struct MinMaxImputerFeaturizer_int8_EstimatorHandle {};
struct MinMaxImputerFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_CreateEstimator(/*in*/ bool useMin,/*out*/ MinMaxImputerFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_DestroyEstimator(/*in*/ MinMaxImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_GetState(/*in*/ MinMaxImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_IsTrainingComplete(/*in*/ MinMaxImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_Fit(/*in*/ MinMaxImputerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_FitBuffer(/*in*/ MinMaxImputerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_OnDataCompleted(/*in*/ MinMaxImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_CompleteTraining(/*in*/ MinMaxImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ MinMaxImputerFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxImputerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxImputerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_DestroyTransformer(/*in*/ MinMaxImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_CreateTransformerSaveData(/*in*/ MinMaxImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_Transform(/*in*/ MinMaxImputerFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int8_Flush(/*in*/ MinMaxImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxImputerFeaturizer <int16> */
struct MinMaxImputerFeaturizer_int16_EstimatorHandle {};
struct MinMaxImputerFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_CreateEstimator(/*in*/ bool useMin,/*out*/ MinMaxImputerFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_DestroyEstimator(/*in*/ MinMaxImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_GetState(/*in*/ MinMaxImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_IsTrainingComplete(/*in*/ MinMaxImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_Fit(/*in*/ MinMaxImputerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_FitBuffer(/*in*/ MinMaxImputerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_OnDataCompleted(/*in*/ MinMaxImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_CompleteTraining(/*in*/ MinMaxImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ MinMaxImputerFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxImputerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxImputerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_DestroyTransformer(/*in*/ MinMaxImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_CreateTransformerSaveData(/*in*/ MinMaxImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_Transform(/*in*/ MinMaxImputerFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t const * input, /*out*/ int16_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int16_Flush(/*in*/ MinMaxImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ int16_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxImputerFeaturizer <int32> */
struct MinMaxImputerFeaturizer_int32_EstimatorHandle {};
struct MinMaxImputerFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_CreateEstimator(/*in*/ bool useMin,/*out*/ MinMaxImputerFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_DestroyEstimator(/*in*/ MinMaxImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_GetState(/*in*/ MinMaxImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_IsTrainingComplete(/*in*/ MinMaxImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_Fit(/*in*/ MinMaxImputerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_FitBuffer(/*in*/ MinMaxImputerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_OnDataCompleted(/*in*/ MinMaxImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_CompleteTraining(/*in*/ MinMaxImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ MinMaxImputerFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxImputerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxImputerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_DestroyTransformer(/*in*/ MinMaxImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_CreateTransformerSaveData(/*in*/ MinMaxImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_Transform(/*in*/ MinMaxImputerFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t const * input, /*out*/ int32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int32_Flush(/*in*/ MinMaxImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ int32_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxImputerFeaturizer <int64> */
struct MinMaxImputerFeaturizer_int64_EstimatorHandle {};
struct MinMaxImputerFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_CreateEstimator(/*in*/ bool useMin,/*out*/ MinMaxImputerFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_DestroyEstimator(/*in*/ MinMaxImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_GetState(/*in*/ MinMaxImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_IsTrainingComplete(/*in*/ MinMaxImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_Fit(/*in*/ MinMaxImputerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_FitBuffer(/*in*/ MinMaxImputerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_OnDataCompleted(/*in*/ MinMaxImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_CompleteTraining(/*in*/ MinMaxImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ MinMaxImputerFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxImputerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxImputerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_DestroyTransformer(/*in*/ MinMaxImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_CreateTransformerSaveData(/*in*/ MinMaxImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_Transform(/*in*/ MinMaxImputerFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t const * input, /*out*/ int64_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_int64_Flush(/*in*/ MinMaxImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ int64_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxImputerFeaturizer <uint8> */
struct MinMaxImputerFeaturizer_uint8_EstimatorHandle {};
struct MinMaxImputerFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_CreateEstimator(/*in*/ bool useMin,/*out*/ MinMaxImputerFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_DestroyEstimator(/*in*/ MinMaxImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_GetState(/*in*/ MinMaxImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_IsTrainingComplete(/*in*/ MinMaxImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_Fit(/*in*/ MinMaxImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_FitBuffer(/*in*/ MinMaxImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_OnDataCompleted(/*in*/ MinMaxImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_CompleteTraining(/*in*/ MinMaxImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ MinMaxImputerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxImputerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxImputerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_DestroyTransformer(/*in*/ MinMaxImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_CreateTransformerSaveData(/*in*/ MinMaxImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_Transform(/*in*/ MinMaxImputerFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ uint8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint8_Flush(/*in*/ MinMaxImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ uint8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxImputerFeaturizer <uint16> */
struct MinMaxImputerFeaturizer_uint16_EstimatorHandle {};
struct MinMaxImputerFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_CreateEstimator(/*in*/ bool useMin,/*out*/ MinMaxImputerFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_DestroyEstimator(/*in*/ MinMaxImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_GetState(/*in*/ MinMaxImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_IsTrainingComplete(/*in*/ MinMaxImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_Fit(/*in*/ MinMaxImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_FitBuffer(/*in*/ MinMaxImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_OnDataCompleted(/*in*/ MinMaxImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_CompleteTraining(/*in*/ MinMaxImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ MinMaxImputerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxImputerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxImputerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_DestroyTransformer(/*in*/ MinMaxImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_CreateTransformerSaveData(/*in*/ MinMaxImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_Transform(/*in*/ MinMaxImputerFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ uint16_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint16_Flush(/*in*/ MinMaxImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ uint16_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxImputerFeaturizer <uint32> */
struct MinMaxImputerFeaturizer_uint32_EstimatorHandle {};
struct MinMaxImputerFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_CreateEstimator(/*in*/ bool useMin,/*out*/ MinMaxImputerFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_DestroyEstimator(/*in*/ MinMaxImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_GetState(/*in*/ MinMaxImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_IsTrainingComplete(/*in*/ MinMaxImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_Fit(/*in*/ MinMaxImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_FitBuffer(/*in*/ MinMaxImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_OnDataCompleted(/*in*/ MinMaxImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_CompleteTraining(/*in*/ MinMaxImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ MinMaxImputerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxImputerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxImputerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_DestroyTransformer(/*in*/ MinMaxImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_CreateTransformerSaveData(/*in*/ MinMaxImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_Transform(/*in*/ MinMaxImputerFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint32_Flush(/*in*/ MinMaxImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ uint32_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxImputerFeaturizer <uint64> */
struct MinMaxImputerFeaturizer_uint64_EstimatorHandle {};
struct MinMaxImputerFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_CreateEstimator(/*in*/ bool useMin,/*out*/ MinMaxImputerFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_DestroyEstimator(/*in*/ MinMaxImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_GetState(/*in*/ MinMaxImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_IsTrainingComplete(/*in*/ MinMaxImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_Fit(/*in*/ MinMaxImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_FitBuffer(/*in*/ MinMaxImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_OnDataCompleted(/*in*/ MinMaxImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_CompleteTraining(/*in*/ MinMaxImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ MinMaxImputerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxImputerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxImputerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_DestroyTransformer(/*in*/ MinMaxImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_CreateTransformerSaveData(/*in*/ MinMaxImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_Transform(/*in*/ MinMaxImputerFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ uint64_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_uint64_Flush(/*in*/ MinMaxImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxImputerFeaturizer <float> */
struct MinMaxImputerFeaturizer_float_EstimatorHandle {};
struct MinMaxImputerFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_CreateEstimator(/*in*/ bool useMin,/*out*/ MinMaxImputerFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_DestroyEstimator(/*in*/ MinMaxImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_GetState(/*in*/ MinMaxImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_IsTrainingComplete(/*in*/ MinMaxImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_Fit(/*in*/ MinMaxImputerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_FitBuffer(/*in*/ MinMaxImputerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_OnDataCompleted(/*in*/ MinMaxImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_CompleteTraining(/*in*/ MinMaxImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_CreateTransformerFromEstimator(/*in*/ MinMaxImputerFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxImputerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxImputerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_DestroyTransformer(/*in*/ MinMaxImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_CreateTransformerSaveData(/*in*/ MinMaxImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_Transform(/*in*/ MinMaxImputerFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_float_Flush(/*in*/ MinMaxImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxImputerFeaturizer <double> */
struct MinMaxImputerFeaturizer_double_EstimatorHandle {};
struct MinMaxImputerFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_CreateEstimator(/*in*/ bool useMin,/*out*/ MinMaxImputerFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_DestroyEstimator(/*in*/ MinMaxImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_GetState(/*in*/ MinMaxImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_IsTrainingComplete(/*in*/ MinMaxImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_Fit(/*in*/ MinMaxImputerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_FitBuffer(/*in*/ MinMaxImputerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_OnDataCompleted(/*in*/ MinMaxImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_CompleteTraining(/*in*/ MinMaxImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_CreateTransformerFromEstimator(/*in*/ MinMaxImputerFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxImputerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxImputerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_DestroyTransformer(/*in*/ MinMaxImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_CreateTransformerSaveData(/*in*/ MinMaxImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_Transform(/*in*/ MinMaxImputerFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_double_Flush(/*in*/ MinMaxImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxImputerFeaturizer <bool> */
struct MinMaxImputerFeaturizer_bool_EstimatorHandle {};
struct MinMaxImputerFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_CreateEstimator(/*in*/ bool useMin,/*out*/ MinMaxImputerFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_DestroyEstimator(/*in*/ MinMaxImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_GetState(/*in*/ MinMaxImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_IsTrainingComplete(/*in*/ MinMaxImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_Fit(/*in*/ MinMaxImputerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_FitBuffer(/*in*/ MinMaxImputerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_OnDataCompleted(/*in*/ MinMaxImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_CompleteTraining(/*in*/ MinMaxImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ MinMaxImputerFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxImputerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxImputerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_DestroyTransformer(/*in*/ MinMaxImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_CreateTransformerSaveData(/*in*/ MinMaxImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_Transform(/*in*/ MinMaxImputerFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_bool_Flush(/*in*/ MinMaxImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MinMaxImputerFeaturizer <string> */
struct MinMaxImputerFeaturizer_string_EstimatorHandle {};
struct MinMaxImputerFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_CreateEstimator(/*in*/ bool useMin,/*out*/ MinMaxImputerFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_DestroyEstimator(/*in*/ MinMaxImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_GetState(/*in*/ MinMaxImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_IsTrainingComplete(/*in*/ MinMaxImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_Fit(/*in*/ MinMaxImputerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_FitBuffer(/*in*/ MinMaxImputerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_OnDataCompleted(/*in*/ MinMaxImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_CompleteTraining(/*in*/ MinMaxImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_CreateTransformerFromEstimator(/*in*/ MinMaxImputerFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ MinMaxImputerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MinMaxImputerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_DestroyTransformer(/*in*/ MinMaxImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_CreateTransformerSaveData(/*in*/ MinMaxImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_Transform(/*in*/ MinMaxImputerFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const * input, /*out*/ char const ** output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_Flush(/*in*/ MinMaxImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ char const *** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MinMaxImputerFeaturizer_string_DestroyTransformedData(/*in*/ char const * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
