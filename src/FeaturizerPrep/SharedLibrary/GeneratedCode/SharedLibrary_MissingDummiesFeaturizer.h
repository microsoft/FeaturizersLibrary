/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int8_t> */
struct MissingDummiesFeaturizer_int8_t_EstimatorHandle {};
struct MissingDummiesFeaturizer_int8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_t_CreateEstimator(/*out*/ MissingDummiesFeaturizer_int8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_t_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_t_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_t_Fit(/*in*/ MissingDummiesFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_t_FitBuffer(/*in*/ MissingDummiesFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_t_CompleteTraining(/*in*/ MissingDummiesFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_t_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_t_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_t_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int8_t_Transform(/*in*/ MissingDummiesFeaturizer_int8_t_TransformerHandle *pHandle, /*in*/ int8_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int16_t> */
struct MissingDummiesFeaturizer_int16_t_EstimatorHandle {};
struct MissingDummiesFeaturizer_int16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_t_CreateEstimator(/*out*/ MissingDummiesFeaturizer_int16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_t_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_t_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_t_Fit(/*in*/ MissingDummiesFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_t_FitBuffer(/*in*/ MissingDummiesFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_t_CompleteTraining(/*in*/ MissingDummiesFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_t_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_t_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_t_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int16_t_Transform(/*in*/ MissingDummiesFeaturizer_int16_t_TransformerHandle *pHandle, /*in*/ int16_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int32_t> */
struct MissingDummiesFeaturizer_int32_t_EstimatorHandle {};
struct MissingDummiesFeaturizer_int32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_t_CreateEstimator(/*out*/ MissingDummiesFeaturizer_int32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_t_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_t_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_t_Fit(/*in*/ MissingDummiesFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_t_FitBuffer(/*in*/ MissingDummiesFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_t_CompleteTraining(/*in*/ MissingDummiesFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_t_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_t_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_t_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int32_t_Transform(/*in*/ MissingDummiesFeaturizer_int32_t_TransformerHandle *pHandle, /*in*/ int32_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int64_t> */
struct MissingDummiesFeaturizer_int64_t_EstimatorHandle {};
struct MissingDummiesFeaturizer_int64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_t_CreateEstimator(/*out*/ MissingDummiesFeaturizer_int64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_t_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_t_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_t_Fit(/*in*/ MissingDummiesFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_t_FitBuffer(/*in*/ MissingDummiesFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_t_CompleteTraining(/*in*/ MissingDummiesFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_t_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_t_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_t_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_int64_t_Transform(/*in*/ MissingDummiesFeaturizer_int64_t_TransformerHandle *pHandle, /*in*/ int64_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint8_t> */
struct MissingDummiesFeaturizer_uint8_t_EstimatorHandle {};
struct MissingDummiesFeaturizer_uint8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_t_CreateEstimator(/*out*/ MissingDummiesFeaturizer_uint8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_t_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_t_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_t_Fit(/*in*/ MissingDummiesFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_t_FitBuffer(/*in*/ MissingDummiesFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_t_CompleteTraining(/*in*/ MissingDummiesFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_t_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_t_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_t_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint8_t_Transform(/*in*/ MissingDummiesFeaturizer_uint8_t_TransformerHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint16_t> */
struct MissingDummiesFeaturizer_uint16_t_EstimatorHandle {};
struct MissingDummiesFeaturizer_uint16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_t_CreateEstimator(/*out*/ MissingDummiesFeaturizer_uint16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_t_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_t_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_t_Fit(/*in*/ MissingDummiesFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_t_FitBuffer(/*in*/ MissingDummiesFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_t_CompleteTraining(/*in*/ MissingDummiesFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_t_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_t_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_t_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint16_t_Transform(/*in*/ MissingDummiesFeaturizer_uint16_t_TransformerHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint32_t> */
struct MissingDummiesFeaturizer_uint32_t_EstimatorHandle {};
struct MissingDummiesFeaturizer_uint32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_t_CreateEstimator(/*out*/ MissingDummiesFeaturizer_uint32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_t_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_t_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_t_Fit(/*in*/ MissingDummiesFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_t_FitBuffer(/*in*/ MissingDummiesFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_t_CompleteTraining(/*in*/ MissingDummiesFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_t_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_t_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_t_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint32_t_Transform(/*in*/ MissingDummiesFeaturizer_uint32_t_TransformerHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint64_t> */
struct MissingDummiesFeaturizer_uint64_t_EstimatorHandle {};
struct MissingDummiesFeaturizer_uint64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_t_CreateEstimator(/*out*/ MissingDummiesFeaturizer_uint64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_t_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_t_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_t_Fit(/*in*/ MissingDummiesFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_t_FitBuffer(/*in*/ MissingDummiesFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_t_CompleteTraining(/*in*/ MissingDummiesFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_t_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_t_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_t_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_uint64_t_Transform(/*in*/ MissingDummiesFeaturizer_uint64_t_TransformerHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <float_t> */
struct MissingDummiesFeaturizer_float_t_EstimatorHandle {};
struct MissingDummiesFeaturizer_float_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_t_CreateEstimator(/*out*/ MissingDummiesFeaturizer_float_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_t_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_t_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_t_Fit(/*in*/ MissingDummiesFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_t_FitBuffer(/*in*/ MissingDummiesFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_t_CompleteTraining(/*in*/ MissingDummiesFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_t_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_float_t_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_t_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_t_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_float_t_Transform(/*in*/ MissingDummiesFeaturizer_float_t_TransformerHandle *pHandle, /*in*/ float const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <double_t> */
struct MissingDummiesFeaturizer_double_t_EstimatorHandle {};
struct MissingDummiesFeaturizer_double_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_t_CreateEstimator(/*out*/ MissingDummiesFeaturizer_double_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_t_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_t_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_t_Fit(/*in*/ MissingDummiesFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_t_FitBuffer(/*in*/ MissingDummiesFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_t_CompleteTraining(/*in*/ MissingDummiesFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_t_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_double_t_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_t_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_t_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_double_t_Transform(/*in*/ MissingDummiesFeaturizer_double_t_TransformerHandle *pHandle, /*in*/ double const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <bool> */
struct MissingDummiesFeaturizer_bool_EstimatorHandle {};
struct MissingDummiesFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_CreateEstimator(/*out*/ MissingDummiesFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_Fit(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_FitBuffer(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_CompleteTraining(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_bool_Transform(/*in*/ MissingDummiesFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <string> */
struct MissingDummiesFeaturizer_string_EstimatorHandle {};
struct MissingDummiesFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_CreateEstimator(/*out*/ MissingDummiesFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_DestroyEstimator(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_IsTrainingComplete(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_Fit(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_FitBuffer(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_CompleteTraining(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_CreateTransformerFromEstimator(/*in*/ MissingDummiesFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ MissingDummiesFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MissingDummiesFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_DestroyTransformer(/*in*/ MissingDummiesFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_CreateTransformerSaveData(/*in*/ MissingDummiesFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool MissingDummiesFeaturizer_string_Transform(/*in*/ MissingDummiesFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
