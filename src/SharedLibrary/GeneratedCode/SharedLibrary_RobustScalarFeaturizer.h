/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <int8> */
struct RobustScalarFeaturizer_int8_EstimatorHandle {};
struct RobustScalarFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax,/*out*/ RobustScalarFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_GetState(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_Fit(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_FitBuffer(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_OnDataCompleted(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_CompleteTraining(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_Transform(/*in*/ RobustScalarFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <int16> */
struct RobustScalarFeaturizer_int16_EstimatorHandle {};
struct RobustScalarFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax,/*out*/ RobustScalarFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_GetState(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_Fit(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_FitBuffer(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_OnDataCompleted(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_CompleteTraining(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_Transform(/*in*/ RobustScalarFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <uint8> */
struct RobustScalarFeaturizer_uint8_EstimatorHandle {};
struct RobustScalarFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax,/*out*/ RobustScalarFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_GetState(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_Fit(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_FitBuffer(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_OnDataCompleted(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_Transform(/*in*/ RobustScalarFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <uint16> */
struct RobustScalarFeaturizer_uint16_EstimatorHandle {};
struct RobustScalarFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax,/*out*/ RobustScalarFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_GetState(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_Fit(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_FitBuffer(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_OnDataCompleted(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_Transform(/*in*/ RobustScalarFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <float> */
struct RobustScalarFeaturizer_float_EstimatorHandle {};
struct RobustScalarFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax,/*out*/ RobustScalarFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_DestroyEstimator(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_GetState(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_Fit(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_FitBuffer(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_OnDataCompleted(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_CompleteTraining(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_DestroyTransformer(/*in*/ RobustScalarFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_Transform(/*in*/ RobustScalarFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <int32> */
struct RobustScalarFeaturizer_int32_EstimatorHandle {};
struct RobustScalarFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax,/*out*/ RobustScalarFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_GetState(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_Fit(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_FitBuffer(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_OnDataCompleted(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_CompleteTraining(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_Transform(/*in*/ RobustScalarFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <int64> */
struct RobustScalarFeaturizer_int64_EstimatorHandle {};
struct RobustScalarFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax,/*out*/ RobustScalarFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_GetState(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_Fit(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_FitBuffer(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_OnDataCompleted(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_CompleteTraining(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_Transform(/*in*/ RobustScalarFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <uint32> */
struct RobustScalarFeaturizer_uint32_EstimatorHandle {};
struct RobustScalarFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax,/*out*/ RobustScalarFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_GetState(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_Fit(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_FitBuffer(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_OnDataCompleted(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_Transform(/*in*/ RobustScalarFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <uint64> */
struct RobustScalarFeaturizer_uint64_EstimatorHandle {};
struct RobustScalarFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax,/*out*/ RobustScalarFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_GetState(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_Fit(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_FitBuffer(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_OnDataCompleted(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_Transform(/*in*/ RobustScalarFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <double> */
struct RobustScalarFeaturizer_double_EstimatorHandle {};
struct RobustScalarFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax,/*out*/ RobustScalarFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_DestroyEstimator(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_GetState(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_Fit(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_FitBuffer(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_OnDataCompleted(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_CompleteTraining(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_DestroyTransformer(/*in*/ RobustScalarFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_Transform(/*in*/ RobustScalarFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
