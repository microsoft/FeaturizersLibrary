/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int8_t> */
struct ImputationMarkerFeaturizer_int8_t_EstimatorHandle {};
struct ImputationMarkerFeaturizer_int8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_t_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_int8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_t_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_t_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_t_Fit(/*in*/ ImputationMarkerFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_t_FitBuffer(/*in*/ ImputationMarkerFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_t_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_t_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_t_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_t_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int8_t_Transform(/*in*/ ImputationMarkerFeaturizer_int8_t_TransformerHandle *pHandle, /*in*/ int8_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int16_t> */
struct ImputationMarkerFeaturizer_int16_t_EstimatorHandle {};
struct ImputationMarkerFeaturizer_int16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_t_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_int16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_t_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_t_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_t_Fit(/*in*/ ImputationMarkerFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_t_FitBuffer(/*in*/ ImputationMarkerFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_t_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_t_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_t_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_t_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int16_t_Transform(/*in*/ ImputationMarkerFeaturizer_int16_t_TransformerHandle *pHandle, /*in*/ int16_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int32_t> */
struct ImputationMarkerFeaturizer_int32_t_EstimatorHandle {};
struct ImputationMarkerFeaturizer_int32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_t_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_int32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_t_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_t_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_t_Fit(/*in*/ ImputationMarkerFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_t_FitBuffer(/*in*/ ImputationMarkerFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_t_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_t_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_t_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_t_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int32_t_Transform(/*in*/ ImputationMarkerFeaturizer_int32_t_TransformerHandle *pHandle, /*in*/ int32_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int64_t> */
struct ImputationMarkerFeaturizer_int64_t_EstimatorHandle {};
struct ImputationMarkerFeaturizer_int64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_t_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_int64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_t_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_t_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_t_Fit(/*in*/ ImputationMarkerFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_t_FitBuffer(/*in*/ ImputationMarkerFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_t_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_t_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_t_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_t_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_int64_t_Transform(/*in*/ ImputationMarkerFeaturizer_int64_t_TransformerHandle *pHandle, /*in*/ int64_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint8_t> */
struct ImputationMarkerFeaturizer_uint8_t_EstimatorHandle {};
struct ImputationMarkerFeaturizer_uint8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_t_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_uint8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_t_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_t_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_t_Fit(/*in*/ ImputationMarkerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_t_FitBuffer(/*in*/ ImputationMarkerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_t_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_t_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_t_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_t_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint8_t_Transform(/*in*/ ImputationMarkerFeaturizer_uint8_t_TransformerHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint16_t> */
struct ImputationMarkerFeaturizer_uint16_t_EstimatorHandle {};
struct ImputationMarkerFeaturizer_uint16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_t_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_uint16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_t_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_t_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_t_Fit(/*in*/ ImputationMarkerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_t_FitBuffer(/*in*/ ImputationMarkerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_t_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_t_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_t_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_t_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint16_t_Transform(/*in*/ ImputationMarkerFeaturizer_uint16_t_TransformerHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint32_t> */
struct ImputationMarkerFeaturizer_uint32_t_EstimatorHandle {};
struct ImputationMarkerFeaturizer_uint32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_t_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_uint32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_t_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_t_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_t_Fit(/*in*/ ImputationMarkerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_t_FitBuffer(/*in*/ ImputationMarkerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_t_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_t_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_t_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_t_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint32_t_Transform(/*in*/ ImputationMarkerFeaturizer_uint32_t_TransformerHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint64_t> */
struct ImputationMarkerFeaturizer_uint64_t_EstimatorHandle {};
struct ImputationMarkerFeaturizer_uint64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_t_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_uint64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_t_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_t_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_t_Fit(/*in*/ ImputationMarkerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_t_FitBuffer(/*in*/ ImputationMarkerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_t_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_t_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_t_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_t_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_uint64_t_Transform(/*in*/ ImputationMarkerFeaturizer_uint64_t_TransformerHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <float_t> */
struct ImputationMarkerFeaturizer_float_t_EstimatorHandle {};
struct ImputationMarkerFeaturizer_float_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_t_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_float_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_t_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_t_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_t_Fit(/*in*/ ImputationMarkerFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_t_FitBuffer(/*in*/ ImputationMarkerFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_t_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_t_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_float_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_t_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_t_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_float_t_Transform(/*in*/ ImputationMarkerFeaturizer_float_t_TransformerHandle *pHandle, /*in*/ float const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <double_t> */
struct ImputationMarkerFeaturizer_double_t_EstimatorHandle {};
struct ImputationMarkerFeaturizer_double_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_t_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_double_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_t_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_t_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_t_Fit(/*in*/ ImputationMarkerFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_t_FitBuffer(/*in*/ ImputationMarkerFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_t_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_t_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_double_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_t_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_t_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_double_t_Transform(/*in*/ ImputationMarkerFeaturizer_double_t_TransformerHandle *pHandle, /*in*/ double const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <bool> */
struct ImputationMarkerFeaturizer_bool_EstimatorHandle {};
struct ImputationMarkerFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_Fit(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_FitBuffer(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_bool_Transform(/*in*/ ImputationMarkerFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <string> */
struct ImputationMarkerFeaturizer_string_EstimatorHandle {};
struct ImputationMarkerFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_CreateEstimator(/*out*/ ImputationMarkerFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_DestroyEstimator(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_IsTrainingComplete(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_Fit(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_FitBuffer(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_CompleteTraining(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_CreateTransformerFromEstimator(/*in*/ ImputationMarkerFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMarkerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMarkerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_DestroyTransformer(/*in*/ ImputationMarkerFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_CreateTransformerSaveData(/*in*/ ImputationMarkerFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ImputationMarkerFeaturizer_string_Transform(/*in*/ ImputationMarkerFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
