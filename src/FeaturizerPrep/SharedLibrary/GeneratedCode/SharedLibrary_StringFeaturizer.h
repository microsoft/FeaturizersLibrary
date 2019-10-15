/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <int8_t> */
struct StringFeaturizer_int8_t_EstimatorHandle {};
struct StringFeaturizer_int8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_int8_t_CreateEstimator(/*out*/ StringFeaturizer_int8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int8_t_DestroyEstimator(/*in*/ StringFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_int8_t_IsTrainingComplete(/*in*/ StringFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int8_t_Fit(/*in*/ StringFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int8_t_FitBuffer(/*in*/ StringFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int8_t_CompleteTraining(/*in*/ StringFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_int8_t_CreateTransformerFromEstimator(/*in*/ StringFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle, /*out*/ StringFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ StringFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int8_t_DestroyTransformer(/*in*/ StringFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_int8_t_CreateTransformerSaveData(/*in*/ StringFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_int8_t_Transform(/*in*/ StringFeaturizer_int8_t_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int8_t_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <int16_t> */
struct StringFeaturizer_int16_t_EstimatorHandle {};
struct StringFeaturizer_int16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_int16_t_CreateEstimator(/*out*/ StringFeaturizer_int16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int16_t_DestroyEstimator(/*in*/ StringFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_int16_t_IsTrainingComplete(/*in*/ StringFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int16_t_Fit(/*in*/ StringFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int16_t_FitBuffer(/*in*/ StringFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int16_t_CompleteTraining(/*in*/ StringFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_int16_t_CreateTransformerFromEstimator(/*in*/ StringFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle, /*out*/ StringFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ StringFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int16_t_DestroyTransformer(/*in*/ StringFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_int16_t_CreateTransformerSaveData(/*in*/ StringFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_int16_t_Transform(/*in*/ StringFeaturizer_int16_t_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int16_t_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <int32_t> */
struct StringFeaturizer_int32_t_EstimatorHandle {};
struct StringFeaturizer_int32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_int32_t_CreateEstimator(/*out*/ StringFeaturizer_int32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int32_t_DestroyEstimator(/*in*/ StringFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_int32_t_IsTrainingComplete(/*in*/ StringFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int32_t_Fit(/*in*/ StringFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int32_t_FitBuffer(/*in*/ StringFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int32_t_CompleteTraining(/*in*/ StringFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_int32_t_CreateTransformerFromEstimator(/*in*/ StringFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle, /*out*/ StringFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ StringFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int32_t_DestroyTransformer(/*in*/ StringFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_int32_t_CreateTransformerSaveData(/*in*/ StringFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_int32_t_Transform(/*in*/ StringFeaturizer_int32_t_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int32_t_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <int64_t> */
struct StringFeaturizer_int64_t_EstimatorHandle {};
struct StringFeaturizer_int64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_int64_t_CreateEstimator(/*out*/ StringFeaturizer_int64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int64_t_DestroyEstimator(/*in*/ StringFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_int64_t_IsTrainingComplete(/*in*/ StringFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int64_t_Fit(/*in*/ StringFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int64_t_FitBuffer(/*in*/ StringFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int64_t_CompleteTraining(/*in*/ StringFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_int64_t_CreateTransformerFromEstimator(/*in*/ StringFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle, /*out*/ StringFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ StringFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int64_t_DestroyTransformer(/*in*/ StringFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_int64_t_CreateTransformerSaveData(/*in*/ StringFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_int64_t_Transform(/*in*/ StringFeaturizer_int64_t_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_int64_t_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <uint8_t> */
struct StringFeaturizer_uint8_t_EstimatorHandle {};
struct StringFeaturizer_uint8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint8_t_CreateEstimator(/*out*/ StringFeaturizer_uint8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint8_t_DestroyEstimator(/*in*/ StringFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_uint8_t_IsTrainingComplete(/*in*/ StringFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint8_t_Fit(/*in*/ StringFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint8_t_FitBuffer(/*in*/ StringFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint8_t_CompleteTraining(/*in*/ StringFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint8_t_CreateTransformerFromEstimator(/*in*/ StringFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle, /*out*/ StringFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ StringFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint8_t_DestroyTransformer(/*in*/ StringFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_uint8_t_CreateTransformerSaveData(/*in*/ StringFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_uint8_t_Transform(/*in*/ StringFeaturizer_uint8_t_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint8_t_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <uint16_t> */
struct StringFeaturizer_uint16_t_EstimatorHandle {};
struct StringFeaturizer_uint16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint16_t_CreateEstimator(/*out*/ StringFeaturizer_uint16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint16_t_DestroyEstimator(/*in*/ StringFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_uint16_t_IsTrainingComplete(/*in*/ StringFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint16_t_Fit(/*in*/ StringFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint16_t_FitBuffer(/*in*/ StringFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint16_t_CompleteTraining(/*in*/ StringFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint16_t_CreateTransformerFromEstimator(/*in*/ StringFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle, /*out*/ StringFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ StringFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint16_t_DestroyTransformer(/*in*/ StringFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_uint16_t_CreateTransformerSaveData(/*in*/ StringFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_uint16_t_Transform(/*in*/ StringFeaturizer_uint16_t_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint16_t_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <uint32_t> */
struct StringFeaturizer_uint32_t_EstimatorHandle {};
struct StringFeaturizer_uint32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint32_t_CreateEstimator(/*out*/ StringFeaturizer_uint32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint32_t_DestroyEstimator(/*in*/ StringFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_uint32_t_IsTrainingComplete(/*in*/ StringFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint32_t_Fit(/*in*/ StringFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint32_t_FitBuffer(/*in*/ StringFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint32_t_CompleteTraining(/*in*/ StringFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint32_t_CreateTransformerFromEstimator(/*in*/ StringFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle, /*out*/ StringFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ StringFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint32_t_DestroyTransformer(/*in*/ StringFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_uint32_t_CreateTransformerSaveData(/*in*/ StringFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_uint32_t_Transform(/*in*/ StringFeaturizer_uint32_t_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint32_t_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <uint64_t> */
struct StringFeaturizer_uint64_t_EstimatorHandle {};
struct StringFeaturizer_uint64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint64_t_CreateEstimator(/*out*/ StringFeaturizer_uint64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint64_t_DestroyEstimator(/*in*/ StringFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_uint64_t_IsTrainingComplete(/*in*/ StringFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint64_t_Fit(/*in*/ StringFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint64_t_FitBuffer(/*in*/ StringFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint64_t_CompleteTraining(/*in*/ StringFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint64_t_CreateTransformerFromEstimator(/*in*/ StringFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle, /*out*/ StringFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ StringFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint64_t_DestroyTransformer(/*in*/ StringFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_uint64_t_CreateTransformerSaveData(/*in*/ StringFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_uint64_t_Transform(/*in*/ StringFeaturizer_uint64_t_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_uint64_t_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <float_t> */
struct StringFeaturizer_float_t_EstimatorHandle {};
struct StringFeaturizer_float_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_float_t_CreateEstimator(/*out*/ StringFeaturizer_float_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_float_t_DestroyEstimator(/*in*/ StringFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_float_t_IsTrainingComplete(/*in*/ StringFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_float_t_Fit(/*in*/ StringFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_float_t_FitBuffer(/*in*/ StringFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_float_t_CompleteTraining(/*in*/ StringFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_float_t_CreateTransformerFromEstimator(/*in*/ StringFeaturizer_float_t_EstimatorHandle *pEstimatorHandle, /*out*/ StringFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_float_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ StringFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_float_t_DestroyTransformer(/*in*/ StringFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_float_t_CreateTransformerSaveData(/*in*/ StringFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_float_t_Transform(/*in*/ StringFeaturizer_float_t_TransformerHandle *pHandle, /*in*/ float input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_float_t_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <double_t> */
struct StringFeaturizer_double_t_EstimatorHandle {};
struct StringFeaturizer_double_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_double_t_CreateEstimator(/*out*/ StringFeaturizer_double_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_double_t_DestroyEstimator(/*in*/ StringFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_double_t_IsTrainingComplete(/*in*/ StringFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_double_t_Fit(/*in*/ StringFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_double_t_FitBuffer(/*in*/ StringFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_double_t_CompleteTraining(/*in*/ StringFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_double_t_CreateTransformerFromEstimator(/*in*/ StringFeaturizer_double_t_EstimatorHandle *pEstimatorHandle, /*out*/ StringFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_double_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ StringFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_double_t_DestroyTransformer(/*in*/ StringFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_double_t_CreateTransformerSaveData(/*in*/ StringFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_double_t_Transform(/*in*/ StringFeaturizer_double_t_TransformerHandle *pHandle, /*in*/ double input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_double_t_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <bool> */
struct StringFeaturizer_bool_EstimatorHandle {};
struct StringFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_bool_CreateEstimator(/*out*/ StringFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_bool_DestroyEstimator(/*in*/ StringFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_bool_IsTrainingComplete(/*in*/ StringFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_bool_Fit(/*in*/ StringFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_bool_FitBuffer(/*in*/ StringFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_bool_CompleteTraining(/*in*/ StringFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ StringFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ StringFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ StringFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_bool_DestroyTransformer(/*in*/ StringFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_bool_CreateTransformerSaveData(/*in*/ StringFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_bool_Transform(/*in*/ StringFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_bool_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <string> */
struct StringFeaturizer_string_EstimatorHandle {};
struct StringFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_string_CreateEstimator(/*out*/ StringFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_string_DestroyEstimator(/*in*/ StringFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_string_IsTrainingComplete(/*in*/ StringFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_string_Fit(/*in*/ StringFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_string_FitBuffer(/*in*/ StringFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_string_CompleteTraining(/*in*/ StringFeaturizer_string_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool StringFeaturizer_string_CreateTransformerFromEstimator(/*in*/ StringFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ StringFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ StringFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_string_DestroyTransformer(/*in*/ StringFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_string_CreateTransformerSaveData(/*in*/ StringFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool StringFeaturizer_string_Transform(/*in*/ StringFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool StringFeaturizer_string_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
