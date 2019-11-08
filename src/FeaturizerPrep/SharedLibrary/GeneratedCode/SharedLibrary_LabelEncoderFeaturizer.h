/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <int8_t> */
struct LabelEncoderFeaturizer_int8_t_EstimatorHandle {};
struct LabelEncoderFeaturizer_int8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_int8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_t_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_t_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_t_Fit(/*in*/ LabelEncoderFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_t_FitBuffer(/*in*/ LabelEncoderFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_t_CompleteTraining(/*in*/ LabelEncoderFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_t_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_t_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_t_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int8_t_Transform(/*in*/ LabelEncoderFeaturizer_int8_t_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <int16_t> */
struct LabelEncoderFeaturizer_int16_t_EstimatorHandle {};
struct LabelEncoderFeaturizer_int16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_int16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_t_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_t_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_t_Fit(/*in*/ LabelEncoderFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_t_FitBuffer(/*in*/ LabelEncoderFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_t_CompleteTraining(/*in*/ LabelEncoderFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_t_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_t_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_t_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int16_t_Transform(/*in*/ LabelEncoderFeaturizer_int16_t_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <int32_t> */
struct LabelEncoderFeaturizer_int32_t_EstimatorHandle {};
struct LabelEncoderFeaturizer_int32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_int32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_t_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_t_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_t_Fit(/*in*/ LabelEncoderFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_t_FitBuffer(/*in*/ LabelEncoderFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_t_CompleteTraining(/*in*/ LabelEncoderFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_t_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_t_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_t_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int32_t_Transform(/*in*/ LabelEncoderFeaturizer_int32_t_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <int64_t> */
struct LabelEncoderFeaturizer_int64_t_EstimatorHandle {};
struct LabelEncoderFeaturizer_int64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_int64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_t_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_t_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_t_Fit(/*in*/ LabelEncoderFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_t_FitBuffer(/*in*/ LabelEncoderFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_t_CompleteTraining(/*in*/ LabelEncoderFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_t_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_t_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_t_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_int64_t_Transform(/*in*/ LabelEncoderFeaturizer_int64_t_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <uint8_t> */
struct LabelEncoderFeaturizer_uint8_t_EstimatorHandle {};
struct LabelEncoderFeaturizer_uint8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_uint8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_t_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_t_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_t_Fit(/*in*/ LabelEncoderFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_t_FitBuffer(/*in*/ LabelEncoderFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_t_CompleteTraining(/*in*/ LabelEncoderFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_t_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_t_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_t_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint8_t_Transform(/*in*/ LabelEncoderFeaturizer_uint8_t_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <uint16_t> */
struct LabelEncoderFeaturizer_uint16_t_EstimatorHandle {};
struct LabelEncoderFeaturizer_uint16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_uint16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_t_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_t_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_t_Fit(/*in*/ LabelEncoderFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_t_FitBuffer(/*in*/ LabelEncoderFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_t_CompleteTraining(/*in*/ LabelEncoderFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_t_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_t_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_t_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint16_t_Transform(/*in*/ LabelEncoderFeaturizer_uint16_t_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <uint32_t> */
struct LabelEncoderFeaturizer_uint32_t_EstimatorHandle {};
struct LabelEncoderFeaturizer_uint32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_uint32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_t_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_t_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_t_Fit(/*in*/ LabelEncoderFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_t_FitBuffer(/*in*/ LabelEncoderFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_t_CompleteTraining(/*in*/ LabelEncoderFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_t_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_t_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_t_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint32_t_Transform(/*in*/ LabelEncoderFeaturizer_uint32_t_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <uint64_t> */
struct LabelEncoderFeaturizer_uint64_t_EstimatorHandle {};
struct LabelEncoderFeaturizer_uint64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_uint64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_t_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_t_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_t_Fit(/*in*/ LabelEncoderFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_t_FitBuffer(/*in*/ LabelEncoderFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_t_CompleteTraining(/*in*/ LabelEncoderFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_t_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_t_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_t_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_uint64_t_Transform(/*in*/ LabelEncoderFeaturizer_uint64_t_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <float_t> */
struct LabelEncoderFeaturizer_float_t_EstimatorHandle {};
struct LabelEncoderFeaturizer_float_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_float_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_t_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_t_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_t_Fit(/*in*/ LabelEncoderFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_t_FitBuffer(/*in*/ LabelEncoderFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_t_CompleteTraining(/*in*/ LabelEncoderFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_t_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_float_t_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_t_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_t_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_float_t_Transform(/*in*/ LabelEncoderFeaturizer_float_t_TransformerHandle *pHandle, /*in*/ float input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <double_t> */
struct LabelEncoderFeaturizer_double_t_EstimatorHandle {};
struct LabelEncoderFeaturizer_double_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_double_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_t_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_t_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_t_Fit(/*in*/ LabelEncoderFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_t_FitBuffer(/*in*/ LabelEncoderFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_t_CompleteTraining(/*in*/ LabelEncoderFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_t_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_double_t_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_t_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_t_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_double_t_Transform(/*in*/ LabelEncoderFeaturizer_double_t_TransformerHandle *pHandle, /*in*/ double input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <bool> */
struct LabelEncoderFeaturizer_bool_EstimatorHandle {};
struct LabelEncoderFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ LabelEncoderFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_DestroyEstimator(/*in*/ LabelEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_Fit(/*in*/ LabelEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_FitBuffer(/*in*/ LabelEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_bool_CompleteTraining(/*in*/ LabelEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

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

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_IsTrainingComplete(/*in*/ LabelEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_Fit(/*in*/ LabelEncoderFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_FitBuffer(/*in*/ LabelEncoderFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_CompleteTraining(/*in*/ LabelEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_CreateTransformerFromEstimator(/*in*/ LabelEncoderFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ LabelEncoderFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ LabelEncoderFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_DestroyTransformer(/*in*/ LabelEncoderFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_CreateTransformerSaveData(/*in*/ LabelEncoderFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LabelEncoderFeaturizer_string_Transform(/*in*/ LabelEncoderFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
