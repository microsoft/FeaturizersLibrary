/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <int8> */
struct StandardScaleWrapperFeaturizer_int8_EstimatorHandle {};
struct StandardScaleWrapperFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_CreateEstimator(/*in*/ bool withMean, /*in*/ bool withStd,/*out*/ StandardScaleWrapperFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_DestroyEstimator(/*in*/ StandardScaleWrapperFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_GetState(/*in*/ StandardScaleWrapperFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_IsTrainingComplete(/*in*/ StandardScaleWrapperFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_Fit(/*in*/ StandardScaleWrapperFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_FitBuffer(/*in*/ StandardScaleWrapperFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_OnDataCompleted(/*in*/ StandardScaleWrapperFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_CompleteTraining(/*in*/ StandardScaleWrapperFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ StandardScaleWrapperFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ StandardScaleWrapperFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ StandardScaleWrapperFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_DestroyTransformer(/*in*/ StandardScaleWrapperFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_CreateTransformerSaveData(/*in*/ StandardScaleWrapperFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_Transform(/*in*/ StandardScaleWrapperFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int8_Flush(/*in*/ StandardScaleWrapperFeaturizer_int8_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <int16> */
struct StandardScaleWrapperFeaturizer_int16_EstimatorHandle {};
struct StandardScaleWrapperFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_CreateEstimator(/*in*/ bool withMean, /*in*/ bool withStd,/*out*/ StandardScaleWrapperFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_DestroyEstimator(/*in*/ StandardScaleWrapperFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_GetState(/*in*/ StandardScaleWrapperFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_IsTrainingComplete(/*in*/ StandardScaleWrapperFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_Fit(/*in*/ StandardScaleWrapperFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_FitBuffer(/*in*/ StandardScaleWrapperFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_OnDataCompleted(/*in*/ StandardScaleWrapperFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_CompleteTraining(/*in*/ StandardScaleWrapperFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ StandardScaleWrapperFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ StandardScaleWrapperFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ StandardScaleWrapperFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_DestroyTransformer(/*in*/ StandardScaleWrapperFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_CreateTransformerSaveData(/*in*/ StandardScaleWrapperFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_Transform(/*in*/ StandardScaleWrapperFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int16_Flush(/*in*/ StandardScaleWrapperFeaturizer_int16_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <int32> */
struct StandardScaleWrapperFeaturizer_int32_EstimatorHandle {};
struct StandardScaleWrapperFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_CreateEstimator(/*in*/ bool withMean, /*in*/ bool withStd,/*out*/ StandardScaleWrapperFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_DestroyEstimator(/*in*/ StandardScaleWrapperFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_GetState(/*in*/ StandardScaleWrapperFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_IsTrainingComplete(/*in*/ StandardScaleWrapperFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_Fit(/*in*/ StandardScaleWrapperFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_FitBuffer(/*in*/ StandardScaleWrapperFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_OnDataCompleted(/*in*/ StandardScaleWrapperFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_CompleteTraining(/*in*/ StandardScaleWrapperFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ StandardScaleWrapperFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ StandardScaleWrapperFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ StandardScaleWrapperFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_DestroyTransformer(/*in*/ StandardScaleWrapperFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_CreateTransformerSaveData(/*in*/ StandardScaleWrapperFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_Transform(/*in*/ StandardScaleWrapperFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int32_Flush(/*in*/ StandardScaleWrapperFeaturizer_int32_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <int64> */
struct StandardScaleWrapperFeaturizer_int64_EstimatorHandle {};
struct StandardScaleWrapperFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_CreateEstimator(/*in*/ bool withMean, /*in*/ bool withStd,/*out*/ StandardScaleWrapperFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_DestroyEstimator(/*in*/ StandardScaleWrapperFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_GetState(/*in*/ StandardScaleWrapperFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_IsTrainingComplete(/*in*/ StandardScaleWrapperFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_Fit(/*in*/ StandardScaleWrapperFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_FitBuffer(/*in*/ StandardScaleWrapperFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_OnDataCompleted(/*in*/ StandardScaleWrapperFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_CompleteTraining(/*in*/ StandardScaleWrapperFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ StandardScaleWrapperFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ StandardScaleWrapperFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ StandardScaleWrapperFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_DestroyTransformer(/*in*/ StandardScaleWrapperFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_CreateTransformerSaveData(/*in*/ StandardScaleWrapperFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_Transform(/*in*/ StandardScaleWrapperFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_int64_Flush(/*in*/ StandardScaleWrapperFeaturizer_int64_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <uint8> */
struct StandardScaleWrapperFeaturizer_uint8_EstimatorHandle {};
struct StandardScaleWrapperFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_CreateEstimator(/*in*/ bool withMean, /*in*/ bool withStd,/*out*/ StandardScaleWrapperFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_DestroyEstimator(/*in*/ StandardScaleWrapperFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_GetState(/*in*/ StandardScaleWrapperFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_IsTrainingComplete(/*in*/ StandardScaleWrapperFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_Fit(/*in*/ StandardScaleWrapperFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_FitBuffer(/*in*/ StandardScaleWrapperFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_OnDataCompleted(/*in*/ StandardScaleWrapperFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_CompleteTraining(/*in*/ StandardScaleWrapperFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ StandardScaleWrapperFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ StandardScaleWrapperFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ StandardScaleWrapperFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_DestroyTransformer(/*in*/ StandardScaleWrapperFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_CreateTransformerSaveData(/*in*/ StandardScaleWrapperFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_Transform(/*in*/ StandardScaleWrapperFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint8_Flush(/*in*/ StandardScaleWrapperFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <uint16> */
struct StandardScaleWrapperFeaturizer_uint16_EstimatorHandle {};
struct StandardScaleWrapperFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_CreateEstimator(/*in*/ bool withMean, /*in*/ bool withStd,/*out*/ StandardScaleWrapperFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_DestroyEstimator(/*in*/ StandardScaleWrapperFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_GetState(/*in*/ StandardScaleWrapperFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_IsTrainingComplete(/*in*/ StandardScaleWrapperFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_Fit(/*in*/ StandardScaleWrapperFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_FitBuffer(/*in*/ StandardScaleWrapperFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_OnDataCompleted(/*in*/ StandardScaleWrapperFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_CompleteTraining(/*in*/ StandardScaleWrapperFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ StandardScaleWrapperFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ StandardScaleWrapperFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ StandardScaleWrapperFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_DestroyTransformer(/*in*/ StandardScaleWrapperFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_CreateTransformerSaveData(/*in*/ StandardScaleWrapperFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_Transform(/*in*/ StandardScaleWrapperFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint16_Flush(/*in*/ StandardScaleWrapperFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <uint32> */
struct StandardScaleWrapperFeaturizer_uint32_EstimatorHandle {};
struct StandardScaleWrapperFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_CreateEstimator(/*in*/ bool withMean, /*in*/ bool withStd,/*out*/ StandardScaleWrapperFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_DestroyEstimator(/*in*/ StandardScaleWrapperFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_GetState(/*in*/ StandardScaleWrapperFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_IsTrainingComplete(/*in*/ StandardScaleWrapperFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_Fit(/*in*/ StandardScaleWrapperFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_FitBuffer(/*in*/ StandardScaleWrapperFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_OnDataCompleted(/*in*/ StandardScaleWrapperFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_CompleteTraining(/*in*/ StandardScaleWrapperFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ StandardScaleWrapperFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ StandardScaleWrapperFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ StandardScaleWrapperFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_DestroyTransformer(/*in*/ StandardScaleWrapperFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_CreateTransformerSaveData(/*in*/ StandardScaleWrapperFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_Transform(/*in*/ StandardScaleWrapperFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint32_Flush(/*in*/ StandardScaleWrapperFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <uint64> */
struct StandardScaleWrapperFeaturizer_uint64_EstimatorHandle {};
struct StandardScaleWrapperFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_CreateEstimator(/*in*/ bool withMean, /*in*/ bool withStd,/*out*/ StandardScaleWrapperFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_DestroyEstimator(/*in*/ StandardScaleWrapperFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_GetState(/*in*/ StandardScaleWrapperFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_IsTrainingComplete(/*in*/ StandardScaleWrapperFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_Fit(/*in*/ StandardScaleWrapperFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_FitBuffer(/*in*/ StandardScaleWrapperFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_OnDataCompleted(/*in*/ StandardScaleWrapperFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_CompleteTraining(/*in*/ StandardScaleWrapperFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ StandardScaleWrapperFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ StandardScaleWrapperFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ StandardScaleWrapperFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_DestroyTransformer(/*in*/ StandardScaleWrapperFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_CreateTransformerSaveData(/*in*/ StandardScaleWrapperFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_Transform(/*in*/ StandardScaleWrapperFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_uint64_Flush(/*in*/ StandardScaleWrapperFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <float> */
struct StandardScaleWrapperFeaturizer_float_EstimatorHandle {};
struct StandardScaleWrapperFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_CreateEstimator(/*in*/ bool withMean, /*in*/ bool withStd,/*out*/ StandardScaleWrapperFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_DestroyEstimator(/*in*/ StandardScaleWrapperFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_GetState(/*in*/ StandardScaleWrapperFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_IsTrainingComplete(/*in*/ StandardScaleWrapperFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_Fit(/*in*/ StandardScaleWrapperFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_FitBuffer(/*in*/ StandardScaleWrapperFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_OnDataCompleted(/*in*/ StandardScaleWrapperFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_CompleteTraining(/*in*/ StandardScaleWrapperFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_CreateTransformerFromEstimator(/*in*/ StandardScaleWrapperFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ StandardScaleWrapperFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ StandardScaleWrapperFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_DestroyTransformer(/*in*/ StandardScaleWrapperFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_CreateTransformerSaveData(/*in*/ StandardScaleWrapperFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_Transform(/*in*/ StandardScaleWrapperFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_float_Flush(/*in*/ StandardScaleWrapperFeaturizer_float_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <double> */
struct StandardScaleWrapperFeaturizer_double_EstimatorHandle {};
struct StandardScaleWrapperFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_CreateEstimator(/*in*/ bool withMean, /*in*/ bool withStd,/*out*/ StandardScaleWrapperFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_DestroyEstimator(/*in*/ StandardScaleWrapperFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_GetState(/*in*/ StandardScaleWrapperFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_IsTrainingComplete(/*in*/ StandardScaleWrapperFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_Fit(/*in*/ StandardScaleWrapperFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_FitBuffer(/*in*/ StandardScaleWrapperFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_OnDataCompleted(/*in*/ StandardScaleWrapperFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_CompleteTraining(/*in*/ StandardScaleWrapperFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_CreateTransformerFromEstimator(/*in*/ StandardScaleWrapperFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ StandardScaleWrapperFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ StandardScaleWrapperFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_DestroyTransformer(/*in*/ StandardScaleWrapperFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_CreateTransformerSaveData(/*in*/ StandardScaleWrapperFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_Transform(/*in*/ StandardScaleWrapperFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StandardScaleWrapperFeaturizer_double_Flush(/*in*/ StandardScaleWrapperFeaturizer_double_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
