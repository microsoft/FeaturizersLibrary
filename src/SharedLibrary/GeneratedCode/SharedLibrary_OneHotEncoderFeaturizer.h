/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int8> */
struct OneHotEncoderFeaturizer_int8_EstimatorHandle {};
struct OneHotEncoderFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_GetState(/*in*/ OneHotEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_Fit(/*in*/ OneHotEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_FitBuffer(/*in*/ OneHotEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_Transform(/*in*/ OneHotEncoderFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t * output_value, /*out*/ uint64_t * output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_Flush(/*in*/ OneHotEncoderFeaturizer_int8_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint8_t ** output_item_value_ptr, /*out*/ uint64_t ** output_item_index_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int16> */
struct OneHotEncoderFeaturizer_int16_EstimatorHandle {};
struct OneHotEncoderFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_GetState(/*in*/ OneHotEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_Fit(/*in*/ OneHotEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_FitBuffer(/*in*/ OneHotEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_Transform(/*in*/ OneHotEncoderFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t * output_value, /*out*/ uint64_t * output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_Flush(/*in*/ OneHotEncoderFeaturizer_int16_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint8_t ** output_item_value_ptr, /*out*/ uint64_t ** output_item_index_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int32> */
struct OneHotEncoderFeaturizer_int32_EstimatorHandle {};
struct OneHotEncoderFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_GetState(/*in*/ OneHotEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_Fit(/*in*/ OneHotEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_FitBuffer(/*in*/ OneHotEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_Transform(/*in*/ OneHotEncoderFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t * output_value, /*out*/ uint64_t * output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_Flush(/*in*/ OneHotEncoderFeaturizer_int32_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint8_t ** output_item_value_ptr, /*out*/ uint64_t ** output_item_index_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int64> */
struct OneHotEncoderFeaturizer_int64_EstimatorHandle {};
struct OneHotEncoderFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_GetState(/*in*/ OneHotEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_Fit(/*in*/ OneHotEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_FitBuffer(/*in*/ OneHotEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_Transform(/*in*/ OneHotEncoderFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t * output_value, /*out*/ uint64_t * output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_Flush(/*in*/ OneHotEncoderFeaturizer_int64_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint8_t ** output_item_value_ptr, /*out*/ uint64_t ** output_item_index_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint8> */
struct OneHotEncoderFeaturizer_uint8_EstimatorHandle {};
struct OneHotEncoderFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_GetState(/*in*/ OneHotEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_Fit(/*in*/ OneHotEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_FitBuffer(/*in*/ OneHotEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_Transform(/*in*/ OneHotEncoderFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t * output_value, /*out*/ uint64_t * output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_Flush(/*in*/ OneHotEncoderFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint8_t ** output_item_value_ptr, /*out*/ uint64_t ** output_item_index_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint16> */
struct OneHotEncoderFeaturizer_uint16_EstimatorHandle {};
struct OneHotEncoderFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_GetState(/*in*/ OneHotEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_Fit(/*in*/ OneHotEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_FitBuffer(/*in*/ OneHotEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_Transform(/*in*/ OneHotEncoderFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t * output_value, /*out*/ uint64_t * output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_Flush(/*in*/ OneHotEncoderFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint8_t ** output_item_value_ptr, /*out*/ uint64_t ** output_item_index_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint32> */
struct OneHotEncoderFeaturizer_uint32_EstimatorHandle {};
struct OneHotEncoderFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_GetState(/*in*/ OneHotEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_Fit(/*in*/ OneHotEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_FitBuffer(/*in*/ OneHotEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_Transform(/*in*/ OneHotEncoderFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t * output_value, /*out*/ uint64_t * output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_Flush(/*in*/ OneHotEncoderFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint8_t ** output_item_value_ptr, /*out*/ uint64_t ** output_item_index_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint64> */
struct OneHotEncoderFeaturizer_uint64_EstimatorHandle {};
struct OneHotEncoderFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_GetState(/*in*/ OneHotEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_Fit(/*in*/ OneHotEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_FitBuffer(/*in*/ OneHotEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_Transform(/*in*/ OneHotEncoderFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t * output_value, /*out*/ uint64_t * output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_Flush(/*in*/ OneHotEncoderFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint8_t ** output_item_value_ptr, /*out*/ uint64_t ** output_item_index_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <float> */
struct OneHotEncoderFeaturizer_float_EstimatorHandle {};
struct OneHotEncoderFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_GetState(/*in*/ OneHotEncoderFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_Fit(/*in*/ OneHotEncoderFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_FitBuffer(/*in*/ OneHotEncoderFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_Transform(/*in*/ OneHotEncoderFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t * output_value, /*out*/ uint64_t * output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_Flush(/*in*/ OneHotEncoderFeaturizer_float_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint8_t ** output_item_value_ptr, /*out*/ uint64_t ** output_item_index_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <double> */
struct OneHotEncoderFeaturizer_double_EstimatorHandle {};
struct OneHotEncoderFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_GetState(/*in*/ OneHotEncoderFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_Fit(/*in*/ OneHotEncoderFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_FitBuffer(/*in*/ OneHotEncoderFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_Transform(/*in*/ OneHotEncoderFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t * output_value, /*out*/ uint64_t * output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_Flush(/*in*/ OneHotEncoderFeaturizer_double_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint8_t ** output_item_value_ptr, /*out*/ uint64_t ** output_item_index_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <bool> */
struct OneHotEncoderFeaturizer_bool_EstimatorHandle {};
struct OneHotEncoderFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_GetState(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_Fit(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_FitBuffer(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_Transform(/*in*/ OneHotEncoderFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t * output_value, /*out*/ uint64_t * output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_Flush(/*in*/ OneHotEncoderFeaturizer_bool_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint8_t ** output_item_value_ptr, /*out*/ uint64_t ** output_item_index_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <string> */
struct OneHotEncoderFeaturizer_string_EstimatorHandle {};
struct OneHotEncoderFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_GetState(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_Fit(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_FitBuffer(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_Transform(/*in*/ OneHotEncoderFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const * input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t * output_value, /*out*/ uint64_t * output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_Flush(/*in*/ OneHotEncoderFeaturizer_string_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint8_t ** output_item_value_ptr, /*out*/ uint64_t ** output_item_index_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
