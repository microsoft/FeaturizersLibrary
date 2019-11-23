/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  ImputationMakerFeaturizer <int8_t> */
struct ImputationMakerFeaturizer_int8_t_EstimatorHandle {};
struct ImputationMakerFeaturizer_int8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_Fit(/*in*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_Transform(/*in*/ ImputationMakerFeaturizer_int8_t_TransformerHandle *pHandle, /*in*/ int8_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMakerFeaturizer <int16_t> */
struct ImputationMakerFeaturizer_int16_t_EstimatorHandle {};
struct ImputationMakerFeaturizer_int16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_Fit(/*in*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_Transform(/*in*/ ImputationMakerFeaturizer_int16_t_TransformerHandle *pHandle, /*in*/ int16_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMakerFeaturizer <int32_t> */
struct ImputationMakerFeaturizer_int32_t_EstimatorHandle {};
struct ImputationMakerFeaturizer_int32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_Fit(/*in*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_Transform(/*in*/ ImputationMakerFeaturizer_int32_t_TransformerHandle *pHandle, /*in*/ int32_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMakerFeaturizer <int64_t> */
struct ImputationMakerFeaturizer_int64_t_EstimatorHandle {};
struct ImputationMakerFeaturizer_int64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_Fit(/*in*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_Transform(/*in*/ ImputationMakerFeaturizer_int64_t_TransformerHandle *pHandle, /*in*/ int64_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMakerFeaturizer <uint8_t> */
struct ImputationMakerFeaturizer_uint8_t_EstimatorHandle {};
struct ImputationMakerFeaturizer_uint8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_Fit(/*in*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_Transform(/*in*/ ImputationMakerFeaturizer_uint8_t_TransformerHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMakerFeaturizer <uint16_t> */
struct ImputationMakerFeaturizer_uint16_t_EstimatorHandle {};
struct ImputationMakerFeaturizer_uint16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_Fit(/*in*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_Transform(/*in*/ ImputationMakerFeaturizer_uint16_t_TransformerHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMakerFeaturizer <uint32_t> */
struct ImputationMakerFeaturizer_uint32_t_EstimatorHandle {};
struct ImputationMakerFeaturizer_uint32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_Fit(/*in*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_Transform(/*in*/ ImputationMakerFeaturizer_uint32_t_TransformerHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMakerFeaturizer <uint64_t> */
struct ImputationMakerFeaturizer_uint64_t_EstimatorHandle {};
struct ImputationMakerFeaturizer_uint64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_Fit(/*in*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_Transform(/*in*/ ImputationMakerFeaturizer_uint64_t_TransformerHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMakerFeaturizer <float_t> */
struct ImputationMakerFeaturizer_float_t_EstimatorHandle {};
struct ImputationMakerFeaturizer_float_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_float_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_Fit(/*in*/ ImputationMakerFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_float_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_Transform(/*in*/ ImputationMakerFeaturizer_float_t_TransformerHandle *pHandle, /*in*/ float const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMakerFeaturizer <double_t> */
struct ImputationMakerFeaturizer_double_t_EstimatorHandle {};
struct ImputationMakerFeaturizer_double_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_double_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_Fit(/*in*/ ImputationMakerFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_double_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_Transform(/*in*/ ImputationMakerFeaturizer_double_t_TransformerHandle *pHandle, /*in*/ double const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMakerFeaturizer <bool> */
struct ImputationMakerFeaturizer_bool_EstimatorHandle {};
struct ImputationMakerFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_CreateEstimator(/*out*/ ImputationMakerFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_Fit(/*in*/ ImputationMakerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_FitBuffer(/*in*/ ImputationMakerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_CompleteTraining(/*in*/ ImputationMakerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_Transform(/*in*/ ImputationMakerFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMakerFeaturizer <string> */
struct ImputationMakerFeaturizer_string_EstimatorHandle {};
struct ImputationMakerFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_CreateEstimator(/*out*/ ImputationMakerFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_Fit(/*in*/ ImputationMakerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_FitBuffer(/*in*/ ImputationMakerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_CompleteTraining(/*in*/ ImputationMakerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_Transform(/*in*/ ImputationMakerFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
