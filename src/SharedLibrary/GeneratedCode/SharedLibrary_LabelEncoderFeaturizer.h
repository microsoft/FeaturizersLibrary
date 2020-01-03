/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <int8> */
struct LabelEncoderFeaturizer_int8_EstimatorHandle {};
struct LabelEncoderFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_GetState(/*in*/ LabelEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_Fit(/*in*/ LabelEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_FitBuffer(/*in*/ LabelEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_OnDataCompleted(/*in*/ LabelEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_CompleteTraining(/*in*/ LabelEncoderFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_Transform(/*in*/ LabelEncoderFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <int16> */
struct LabelEncoderFeaturizer_int16_EstimatorHandle {};
struct LabelEncoderFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_GetState(/*in*/ LabelEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_Fit(/*in*/ LabelEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_FitBuffer(/*in*/ LabelEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_OnDataCompleted(/*in*/ LabelEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_CompleteTraining(/*in*/ LabelEncoderFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_Transform(/*in*/ LabelEncoderFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <int32> */
struct LabelEncoderFeaturizer_int32_EstimatorHandle {};
struct LabelEncoderFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_GetState(/*in*/ LabelEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_Fit(/*in*/ LabelEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_FitBuffer(/*in*/ LabelEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_OnDataCompleted(/*in*/ LabelEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_CompleteTraining(/*in*/ LabelEncoderFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_Transform(/*in*/ LabelEncoderFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <int64> */
struct LabelEncoderFeaturizer_int64_EstimatorHandle {};
struct LabelEncoderFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_GetState(/*in*/ LabelEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_Fit(/*in*/ LabelEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_FitBuffer(/*in*/ LabelEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_OnDataCompleted(/*in*/ LabelEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_CompleteTraining(/*in*/ LabelEncoderFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_Transform(/*in*/ LabelEncoderFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <uint8> */
struct LabelEncoderFeaturizer_uint8_EstimatorHandle {};
struct LabelEncoderFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_GetState(/*in*/ LabelEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_Fit(/*in*/ LabelEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_FitBuffer(/*in*/ LabelEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_OnDataCompleted(/*in*/ LabelEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_CompleteTraining(/*in*/ LabelEncoderFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_Transform(/*in*/ LabelEncoderFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <uint16> */
struct LabelEncoderFeaturizer_uint16_EstimatorHandle {};
struct LabelEncoderFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_GetState(/*in*/ LabelEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_Fit(/*in*/ LabelEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_FitBuffer(/*in*/ LabelEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_OnDataCompleted(/*in*/ LabelEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_CompleteTraining(/*in*/ LabelEncoderFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_Transform(/*in*/ LabelEncoderFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <uint32> */
struct LabelEncoderFeaturizer_uint32_EstimatorHandle {};
struct LabelEncoderFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_GetState(/*in*/ LabelEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_Fit(/*in*/ LabelEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_FitBuffer(/*in*/ LabelEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_OnDataCompleted(/*in*/ LabelEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_CompleteTraining(/*in*/ LabelEncoderFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_Transform(/*in*/ LabelEncoderFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <uint64> */
struct LabelEncoderFeaturizer_uint64_EstimatorHandle {};
struct LabelEncoderFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_GetState(/*in*/ LabelEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_Fit(/*in*/ LabelEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_FitBuffer(/*in*/ LabelEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_OnDataCompleted(/*in*/ LabelEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_CompleteTraining(/*in*/ LabelEncoderFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_Transform(/*in*/ LabelEncoderFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <float> */
struct LabelEncoderFeaturizer_float_EstimatorHandle {};
struct LabelEncoderFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_GetState(/*in*/ LabelEncoderFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_Fit(/*in*/ LabelEncoderFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_FitBuffer(/*in*/ LabelEncoderFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_OnDataCompleted(/*in*/ LabelEncoderFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_CompleteTraining(/*in*/ LabelEncoderFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_Transform(/*in*/ LabelEncoderFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <double> */
struct LabelEncoderFeaturizer_double_EstimatorHandle {};
struct LabelEncoderFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_GetState(/*in*/ LabelEncoderFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_Fit(/*in*/ LabelEncoderFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_FitBuffer(/*in*/ LabelEncoderFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_OnDataCompleted(/*in*/ LabelEncoderFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_CompleteTraining(/*in*/ LabelEncoderFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_Transform(/*in*/ LabelEncoderFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <bool> */
struct LabelEncoderFeaturizer_bool_EstimatorHandle {};
struct LabelEncoderFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_GetState(/*in*/ LabelEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_Fit(/*in*/ LabelEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_FitBuffer(/*in*/ LabelEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_OnDataCompleted(/*in*/ LabelEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_CompleteTraining(/*in*/ LabelEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_Transform(/*in*/ LabelEncoderFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <string> */
struct LabelEncoderFeaturizer_string_EstimatorHandle {};
struct LabelEncoderFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_GetState(/*in*/ LabelEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_Fit(/*in*/ LabelEncoderFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_FitBuffer(/*in*/ LabelEncoderFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_OnDataCompleted(/*in*/ LabelEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_CompleteTraining(/*in*/ LabelEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_Transform(/*in*/ LabelEncoderFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
