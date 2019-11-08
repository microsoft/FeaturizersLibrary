/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <int8_t> */
struct MaxAbsScalarFeaturizer_int8_t_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_int8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_t_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_int8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_t_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_t_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_t_Fit(/*in*/ MaxAbsScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_t_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_t_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_t_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_t_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_t_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int8_t_Transform(/*in*/ MaxAbsScalarFeaturizer_int8_t_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <int16_t> */
struct MaxAbsScalarFeaturizer_int16_t_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_int16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_t_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_int16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_t_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_t_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_t_Fit(/*in*/ MaxAbsScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_t_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_t_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_t_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_t_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_t_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int16_t_Transform(/*in*/ MaxAbsScalarFeaturizer_int16_t_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <uint8_t> */
struct MaxAbsScalarFeaturizer_uint8_t_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_uint8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_t_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_uint8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_t_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_t_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_t_Fit(/*in*/ MaxAbsScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_t_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_t_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_t_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_t_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_t_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint8_t_Transform(/*in*/ MaxAbsScalarFeaturizer_uint8_t_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <uint16_t> */
struct MaxAbsScalarFeaturizer_uint16_t_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_uint16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_t_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_uint16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_t_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_t_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_t_Fit(/*in*/ MaxAbsScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_t_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_t_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_t_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_t_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_t_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint16_t_Transform(/*in*/ MaxAbsScalarFeaturizer_uint16_t_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <float_t> */
struct MaxAbsScalarFeaturizer_float_t_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_float_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_t_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_float_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_t_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_t_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_t_Fit(/*in*/ MaxAbsScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_t_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_t_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_t_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_float_t_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_t_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_t_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_float_t_Transform(/*in*/ MaxAbsScalarFeaturizer_float_t_TransformerHandle *pHandle, /*in*/ float input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <int32_t> */
struct MaxAbsScalarFeaturizer_int32_t_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_int32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_t_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_int32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_t_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_t_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_t_Fit(/*in*/ MaxAbsScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_t_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_t_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_t_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_t_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_t_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int32_t_Transform(/*in*/ MaxAbsScalarFeaturizer_int32_t_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <int64_t> */
struct MaxAbsScalarFeaturizer_int64_t_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_int64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_t_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_int64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_t_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_t_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_t_Fit(/*in*/ MaxAbsScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_t_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_t_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_t_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_t_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_t_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_int64_t_Transform(/*in*/ MaxAbsScalarFeaturizer_int64_t_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <uint32_t> */
struct MaxAbsScalarFeaturizer_uint32_t_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_uint32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_t_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_uint32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_t_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_t_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_t_Fit(/*in*/ MaxAbsScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_t_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_t_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_t_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_t_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_t_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint32_t_Transform(/*in*/ MaxAbsScalarFeaturizer_uint32_t_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <uint64_t> */
struct MaxAbsScalarFeaturizer_uint64_t_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_uint64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_t_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_uint64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_t_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_t_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_t_Fit(/*in*/ MaxAbsScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_t_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_t_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_t_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_t_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_t_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_uint64_t_Transform(/*in*/ MaxAbsScalarFeaturizer_uint64_t_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MaxAbsScalarFeaturizer <double_t> */
struct MaxAbsScalarFeaturizer_double_t_EstimatorHandle {};
struct MaxAbsScalarFeaturizer_double_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_t_CreateEstimator(/*out*/ MaxAbsScalarFeaturizer_double_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_t_DestroyEstimator(/*in*/ MaxAbsScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_t_IsTrainingComplete(/*in*/ MaxAbsScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_t_Fit(/*in*/ MaxAbsScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_t_FitBuffer(/*in*/ MaxAbsScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_t_CompleteTraining(/*in*/ MaxAbsScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_t_CreateTransformerFromEstimator(/*in*/ MaxAbsScalarFeaturizer_double_t_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalarFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxAbsScalarFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_t_DestroyTransformer(/*in*/ MaxAbsScalarFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_t_CreateTransformerSaveData(/*in*/ MaxAbsScalarFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MaxAbsScalarFeaturizer_double_t_Transform(/*in*/ MaxAbsScalarFeaturizer_double_t_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
