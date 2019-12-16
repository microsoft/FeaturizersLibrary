/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {
FEATURIZER_LIBRARY_API_PACK_PREFIX

struct OneHotStruct {
    /*out*/ uint32_t index;
    /*out*/ uint32_t size;
    /*out*/ uint32_t appearances;
} FEATURIZER_LIBRARY_API_PACK_INLINE;

FEATURIZER_LIBRARY_API_PACK_SUFFIX


/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int8_t> */
struct OneHotEncoderFeaturizer_int8_t_EstimatorHandle {};
struct OneHotEncoderFeaturizer_int8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_int8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_GetState(/*in*/ OneHotEncoderFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_Fit(/*in*/ OneHotEncoderFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_FitBuffer(/*in*/ OneHotEncoderFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_Transform(/*in*/ OneHotEncoderFeaturizer_int8_t_TransformerHandle *pHandle, /*in*/ int8_t input, /*out via struct*/ OneHotStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int8_t_DestroyTransformedData(/*in*/ OneHotStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int16_t> */
struct OneHotEncoderFeaturizer_int16_t_EstimatorHandle {};
struct OneHotEncoderFeaturizer_int16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_int16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_GetState(/*in*/ OneHotEncoderFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_Fit(/*in*/ OneHotEncoderFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_FitBuffer(/*in*/ OneHotEncoderFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_Transform(/*in*/ OneHotEncoderFeaturizer_int16_t_TransformerHandle *pHandle, /*in*/ int16_t input, /*out via struct*/ OneHotStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int16_t_DestroyTransformedData(/*in*/ OneHotStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int32_t> */
struct OneHotEncoderFeaturizer_int32_t_EstimatorHandle {};
struct OneHotEncoderFeaturizer_int32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_int32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_GetState(/*in*/ OneHotEncoderFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_Fit(/*in*/ OneHotEncoderFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_FitBuffer(/*in*/ OneHotEncoderFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_Transform(/*in*/ OneHotEncoderFeaturizer_int32_t_TransformerHandle *pHandle, /*in*/ int32_t input, /*out via struct*/ OneHotStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int32_t_DestroyTransformedData(/*in*/ OneHotStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int64_t> */
struct OneHotEncoderFeaturizer_int64_t_EstimatorHandle {};
struct OneHotEncoderFeaturizer_int64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_int64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_GetState(/*in*/ OneHotEncoderFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_Fit(/*in*/ OneHotEncoderFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_FitBuffer(/*in*/ OneHotEncoderFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_Transform(/*in*/ OneHotEncoderFeaturizer_int64_t_TransformerHandle *pHandle, /*in*/ int64_t input, /*out via struct*/ OneHotStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_int64_t_DestroyTransformedData(/*in*/ OneHotStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint8_t> */
struct OneHotEncoderFeaturizer_uint8_t_EstimatorHandle {};
struct OneHotEncoderFeaturizer_uint8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_uint8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_GetState(/*in*/ OneHotEncoderFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_Fit(/*in*/ OneHotEncoderFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_FitBuffer(/*in*/ OneHotEncoderFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_Transform(/*in*/ OneHotEncoderFeaturizer_uint8_t_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out via struct*/ OneHotStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint8_t_DestroyTransformedData(/*in*/ OneHotStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint16_t> */
struct OneHotEncoderFeaturizer_uint16_t_EstimatorHandle {};
struct OneHotEncoderFeaturizer_uint16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_uint16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_GetState(/*in*/ OneHotEncoderFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_Fit(/*in*/ OneHotEncoderFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_FitBuffer(/*in*/ OneHotEncoderFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_Transform(/*in*/ OneHotEncoderFeaturizer_uint16_t_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out via struct*/ OneHotStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint16_t_DestroyTransformedData(/*in*/ OneHotStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint32_t> */
struct OneHotEncoderFeaturizer_uint32_t_EstimatorHandle {};
struct OneHotEncoderFeaturizer_uint32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_uint32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_GetState(/*in*/ OneHotEncoderFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_Fit(/*in*/ OneHotEncoderFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_FitBuffer(/*in*/ OneHotEncoderFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_Transform(/*in*/ OneHotEncoderFeaturizer_uint32_t_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out via struct*/ OneHotStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint32_t_DestroyTransformedData(/*in*/ OneHotStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint64_t> */
struct OneHotEncoderFeaturizer_uint64_t_EstimatorHandle {};
struct OneHotEncoderFeaturizer_uint64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_uint64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_GetState(/*in*/ OneHotEncoderFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_Fit(/*in*/ OneHotEncoderFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_FitBuffer(/*in*/ OneHotEncoderFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_Transform(/*in*/ OneHotEncoderFeaturizer_uint64_t_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out via struct*/ OneHotStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_uint64_t_DestroyTransformedData(/*in*/ OneHotStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <float_t> */
struct OneHotEncoderFeaturizer_float_t_EstimatorHandle {};
struct OneHotEncoderFeaturizer_float_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_float_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_GetState(/*in*/ OneHotEncoderFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_Fit(/*in*/ OneHotEncoderFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_FitBuffer(/*in*/ OneHotEncoderFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_float_t_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_Transform(/*in*/ OneHotEncoderFeaturizer_float_t_TransformerHandle *pHandle, /*in*/ float input, /*out via struct*/ OneHotStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_float_t_DestroyTransformedData(/*in*/ OneHotStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <double_t> */
struct OneHotEncoderFeaturizer_double_t_EstimatorHandle {};
struct OneHotEncoderFeaturizer_double_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_double_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_GetState(/*in*/ OneHotEncoderFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_Fit(/*in*/ OneHotEncoderFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_FitBuffer(/*in*/ OneHotEncoderFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_double_t_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_Transform(/*in*/ OneHotEncoderFeaturizer_double_t_TransformerHandle *pHandle, /*in*/ double input, /*out via struct*/ OneHotStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_double_t_DestroyTransformedData(/*in*/ OneHotStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <bool> */
struct OneHotEncoderFeaturizer_bool_EstimatorHandle {};
struct OneHotEncoderFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_GetState(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_Fit(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_FitBuffer(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_Transform(/*in*/ OneHotEncoderFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool input, /*out via struct*/ OneHotStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_bool_DestroyTransformedData(/*in*/ OneHotStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <string> */
struct OneHotEncoderFeaturizer_string_EstimatorHandle {};
struct OneHotEncoderFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_CreateEstimator(/*in*/ bool suppressUnrecognizedErrors,/*out*/ OneHotEncoderFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_DestroyEstimator(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_GetState(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_IsTrainingComplete(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_Fit(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_FitBuffer(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_OnDataCompleted(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_CompleteTraining(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_CreateTransformerFromEstimator(/*in*/ OneHotEncoderFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ OneHotEncoderFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ OneHotEncoderFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_DestroyTransformer(/*in*/ OneHotEncoderFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_CreateTransformerSaveData(/*in*/ OneHotEncoderFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_Transform(/*in*/ OneHotEncoderFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const *input, /*out via struct*/ OneHotStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool OneHotEncoderFeaturizer_string_DestroyTransformedData(/*in*/ OneHotStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
