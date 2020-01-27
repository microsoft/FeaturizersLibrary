/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <int8> */
struct HashOneHotVectorizerFeaturizer_int8_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_GetState(/*in*/ HashOneHotVectorizerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_Fit(/*in*/ HashOneHotVectorizerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_OnDataCompleted(/*in*/ HashOneHotVectorizerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_Transform(/*in*/ HashOneHotVectorizerFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t *output_value, /*out*/ uint64_t *output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <int16> */
struct HashOneHotVectorizerFeaturizer_int16_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_GetState(/*in*/ HashOneHotVectorizerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_Fit(/*in*/ HashOneHotVectorizerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_OnDataCompleted(/*in*/ HashOneHotVectorizerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_Transform(/*in*/ HashOneHotVectorizerFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t *output_value, /*out*/ uint64_t *output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <int32> */
struct HashOneHotVectorizerFeaturizer_int32_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_GetState(/*in*/ HashOneHotVectorizerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_Fit(/*in*/ HashOneHotVectorizerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_OnDataCompleted(/*in*/ HashOneHotVectorizerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_Transform(/*in*/ HashOneHotVectorizerFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t *output_value, /*out*/ uint64_t *output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <int64> */
struct HashOneHotVectorizerFeaturizer_int64_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_GetState(/*in*/ HashOneHotVectorizerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_Fit(/*in*/ HashOneHotVectorizerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_OnDataCompleted(/*in*/ HashOneHotVectorizerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_Transform(/*in*/ HashOneHotVectorizerFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t *output_value, /*out*/ uint64_t *output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <uint8> */
struct HashOneHotVectorizerFeaturizer_uint8_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_GetState(/*in*/ HashOneHotVectorizerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_Fit(/*in*/ HashOneHotVectorizerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_OnDataCompleted(/*in*/ HashOneHotVectorizerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_Transform(/*in*/ HashOneHotVectorizerFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t *output_value, /*out*/ uint64_t *output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <uint16> */
struct HashOneHotVectorizerFeaturizer_uint16_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_GetState(/*in*/ HashOneHotVectorizerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_Fit(/*in*/ HashOneHotVectorizerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_OnDataCompleted(/*in*/ HashOneHotVectorizerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_Transform(/*in*/ HashOneHotVectorizerFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t *output_value, /*out*/ uint64_t *output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <uint32> */
struct HashOneHotVectorizerFeaturizer_uint32_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_GetState(/*in*/ HashOneHotVectorizerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_Fit(/*in*/ HashOneHotVectorizerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_OnDataCompleted(/*in*/ HashOneHotVectorizerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_Transform(/*in*/ HashOneHotVectorizerFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t *output_value, /*out*/ uint64_t *output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <uint64> */
struct HashOneHotVectorizerFeaturizer_uint64_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_GetState(/*in*/ HashOneHotVectorizerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_Fit(/*in*/ HashOneHotVectorizerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_OnDataCompleted(/*in*/ HashOneHotVectorizerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_Transform(/*in*/ HashOneHotVectorizerFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t *output_value, /*out*/ uint64_t *output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <float> */
struct HashOneHotVectorizerFeaturizer_float_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_GetState(/*in*/ HashOneHotVectorizerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_Fit(/*in*/ HashOneHotVectorizerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_OnDataCompleted(/*in*/ HashOneHotVectorizerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_Transform(/*in*/ HashOneHotVectorizerFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t *output_value, /*out*/ uint64_t *output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <double> */
struct HashOneHotVectorizerFeaturizer_double_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_GetState(/*in*/ HashOneHotVectorizerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_Fit(/*in*/ HashOneHotVectorizerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_OnDataCompleted(/*in*/ HashOneHotVectorizerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_Transform(/*in*/ HashOneHotVectorizerFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t *output_value, /*out*/ uint64_t *output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <bool> */
struct HashOneHotVectorizerFeaturizer_bool_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_GetState(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_Fit(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_OnDataCompleted(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_Transform(/*in*/ HashOneHotVectorizerFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t *output_value, /*out*/ uint64_t *output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <string> */
struct HashOneHotVectorizerFeaturizer_string_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_GetState(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_Fit(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_OnDataCompleted(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_Transform(/*in*/ HashOneHotVectorizerFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ uint64_t * output_numElements, /*out*/ uint8_t *output_value, /*out*/ uint64_t *output_index, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
