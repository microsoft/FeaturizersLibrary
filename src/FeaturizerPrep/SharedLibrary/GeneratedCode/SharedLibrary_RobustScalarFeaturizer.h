/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <int8_t> */
struct RobustScalarFeaturizer_int8_t_EstimatorHandle {};
struct RobustScalarFeaturizer_int8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_CreateEstimator(/*out*/ RobustScalarFeaturizer_int8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_Fit(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_FitBuffer(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_Transform(/*in*/ RobustScalarFeaturizer_int8_t_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <int16_t> */
struct RobustScalarFeaturizer_int16_t_EstimatorHandle {};
struct RobustScalarFeaturizer_int16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_CreateEstimator(/*out*/ RobustScalarFeaturizer_int16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_Fit(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_FitBuffer(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_Transform(/*in*/ RobustScalarFeaturizer_int16_t_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <uint8_t> */
struct RobustScalarFeaturizer_uint8_t_EstimatorHandle {};
struct RobustScalarFeaturizer_uint8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_CreateEstimator(/*out*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_Fit(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_FitBuffer(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_Transform(/*in*/ RobustScalarFeaturizer_uint8_t_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <uint16_t> */
struct RobustScalarFeaturizer_uint16_t_EstimatorHandle {};
struct RobustScalarFeaturizer_uint16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_CreateEstimator(/*out*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_Fit(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_FitBuffer(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_Transform(/*in*/ RobustScalarFeaturizer_uint16_t_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <float_t> */
struct RobustScalarFeaturizer_float_t_EstimatorHandle {};
struct RobustScalarFeaturizer_float_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_CreateEstimator(/*out*/ RobustScalarFeaturizer_float_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_Fit(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_FitBuffer(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_Transform(/*in*/ RobustScalarFeaturizer_float_t_TransformerHandle *pHandle, /*in*/ float input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <int32_t> */
struct RobustScalarFeaturizer_int32_t_EstimatorHandle {};
struct RobustScalarFeaturizer_int32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_CreateEstimator(/*out*/ RobustScalarFeaturizer_int32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_Fit(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_FitBuffer(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_Transform(/*in*/ RobustScalarFeaturizer_int32_t_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <int64_t> */
struct RobustScalarFeaturizer_int64_t_EstimatorHandle {};
struct RobustScalarFeaturizer_int64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_CreateEstimator(/*out*/ RobustScalarFeaturizer_int64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_Fit(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_FitBuffer(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_Transform(/*in*/ RobustScalarFeaturizer_int64_t_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <uint32_t> */
struct RobustScalarFeaturizer_uint32_t_EstimatorHandle {};
struct RobustScalarFeaturizer_uint32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_CreateEstimator(/*out*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_Fit(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_FitBuffer(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_Transform(/*in*/ RobustScalarFeaturizer_uint32_t_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <uint64_t> */
struct RobustScalarFeaturizer_uint64_t_EstimatorHandle {};
struct RobustScalarFeaturizer_uint64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_CreateEstimator(/*out*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_Fit(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_FitBuffer(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_Transform(/*in*/ RobustScalarFeaturizer_uint64_t_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <double_t> */
struct RobustScalarFeaturizer_double_t_EstimatorHandle {};
struct RobustScalarFeaturizer_double_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_CreateEstimator(/*out*/ RobustScalarFeaturizer_double_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_Fit(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_FitBuffer(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_Transform(/*in*/ RobustScalarFeaturizer_double_t_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
