/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <int8> */
struct L1NormalizeFeaturizer_int8_EstimatorHandle {};
struct L1NormalizeFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_CreateEstimator(/*out*/ L1NormalizeFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_GetState(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_Fit(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_FitBuffer(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_CompleteTraining(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_Transform(/*in*/ L1NormalizeFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_Flush(/*in*/ L1NormalizeFeaturizer_int8_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_DestroyTransformedData(/*in*/ double const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <int16> */
struct L1NormalizeFeaturizer_int16_EstimatorHandle {};
struct L1NormalizeFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_CreateEstimator(/*out*/ L1NormalizeFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_GetState(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_Fit(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_FitBuffer(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_CompleteTraining(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_Transform(/*in*/ L1NormalizeFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_Flush(/*in*/ L1NormalizeFeaturizer_int16_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_DestroyTransformedData(/*in*/ double const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <int32> */
struct L1NormalizeFeaturizer_int32_EstimatorHandle {};
struct L1NormalizeFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_CreateEstimator(/*out*/ L1NormalizeFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_GetState(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_Fit(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_FitBuffer(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_CompleteTraining(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_Transform(/*in*/ L1NormalizeFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_Flush(/*in*/ L1NormalizeFeaturizer_int32_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_DestroyTransformedData(/*in*/ double const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <int64> */
struct L1NormalizeFeaturizer_int64_EstimatorHandle {};
struct L1NormalizeFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_CreateEstimator(/*out*/ L1NormalizeFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_GetState(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_Fit(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_FitBuffer(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_CompleteTraining(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_Transform(/*in*/ L1NormalizeFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_Flush(/*in*/ L1NormalizeFeaturizer_int64_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_DestroyTransformedData(/*in*/ double const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <uint8> */
struct L1NormalizeFeaturizer_uint8_EstimatorHandle {};
struct L1NormalizeFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_CreateEstimator(/*out*/ L1NormalizeFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_GetState(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_Fit(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_FitBuffer(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_CompleteTraining(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_Transform(/*in*/ L1NormalizeFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_Flush(/*in*/ L1NormalizeFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_DestroyTransformedData(/*in*/ double const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <uint16> */
struct L1NormalizeFeaturizer_uint16_EstimatorHandle {};
struct L1NormalizeFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_CreateEstimator(/*out*/ L1NormalizeFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_GetState(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_Fit(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_FitBuffer(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_CompleteTraining(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_Transform(/*in*/ L1NormalizeFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_Flush(/*in*/ L1NormalizeFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_DestroyTransformedData(/*in*/ double const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <uint32> */
struct L1NormalizeFeaturizer_uint32_EstimatorHandle {};
struct L1NormalizeFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_CreateEstimator(/*out*/ L1NormalizeFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_GetState(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_Fit(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_FitBuffer(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_CompleteTraining(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_Transform(/*in*/ L1NormalizeFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_Flush(/*in*/ L1NormalizeFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_DestroyTransformedData(/*in*/ double const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <uint64> */
struct L1NormalizeFeaturizer_uint64_EstimatorHandle {};
struct L1NormalizeFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_CreateEstimator(/*out*/ L1NormalizeFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_GetState(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_Fit(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_FitBuffer(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_CompleteTraining(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_Transform(/*in*/ L1NormalizeFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_Flush(/*in*/ L1NormalizeFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_DestroyTransformedData(/*in*/ double const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <float> */
struct L1NormalizeFeaturizer_float_EstimatorHandle {};
struct L1NormalizeFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_CreateEstimator(/*out*/ L1NormalizeFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_GetState(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_Fit(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_FitBuffer(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_CompleteTraining(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_Transform(/*in*/ L1NormalizeFeaturizer_float_TransformerHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_Flush(/*in*/ L1NormalizeFeaturizer_float_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_DestroyTransformedData(/*in*/ double const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <double> */
struct L1NormalizeFeaturizer_double_EstimatorHandle {};
struct L1NormalizeFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_CreateEstimator(/*out*/ L1NormalizeFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_GetState(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_Fit(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_FitBuffer(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_CompleteTraining(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_Transform(/*in*/ L1NormalizeFeaturizer_double_TransformerHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_Flush(/*in*/ L1NormalizeFeaturizer_double_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_DestroyTransformedData(/*in*/ double const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
