/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {
FEATURIZER_LIBRARY_API_PACK_PREFIX

struct HashOneHotVectorizerStruct {
    /*out*/ uint32_t ColIndex;
    /*out*/ uint32_t NumCols;
    /*out*/ bool Val;
} FEATURIZER_LIBRARY_API_PACK_INLINE;

FEATURIZER_LIBRARY_API_PACK_SUFFIX


/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <int8_t> */
struct HashOneHotVectorizerFeaturizer_int8_t_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_int8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_t_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_int8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_t_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_t_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_t_Fit(/*in*/ HashOneHotVectorizerFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_t_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_t_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_t_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_t_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_t_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_t_Transform(/*in*/ HashOneHotVectorizerFeaturizer_int8_t_TransformerHandle *pHandle, /*in*/ int8_t input, /*out via struct*/ HashOneHotVectorizerStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int8_t_DestroyTransformedData(/*in*/ HashOneHotVectorizerStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <int16_t> */
struct HashOneHotVectorizerFeaturizer_int16_t_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_int16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_t_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_int16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_t_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_t_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_t_Fit(/*in*/ HashOneHotVectorizerFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_t_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_t_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_t_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_t_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_t_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_t_Transform(/*in*/ HashOneHotVectorizerFeaturizer_int16_t_TransformerHandle *pHandle, /*in*/ int16_t input, /*out via struct*/ HashOneHotVectorizerStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int16_t_DestroyTransformedData(/*in*/ HashOneHotVectorizerStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <int32_t> */
struct HashOneHotVectorizerFeaturizer_int32_t_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_int32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_t_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_int32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_t_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_t_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_t_Fit(/*in*/ HashOneHotVectorizerFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_t_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_t_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_t_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_t_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_t_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_t_Transform(/*in*/ HashOneHotVectorizerFeaturizer_int32_t_TransformerHandle *pHandle, /*in*/ int32_t input, /*out via struct*/ HashOneHotVectorizerStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int32_t_DestroyTransformedData(/*in*/ HashOneHotVectorizerStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <int64_t> */
struct HashOneHotVectorizerFeaturizer_int64_t_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_int64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_t_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_int64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_t_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_t_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_t_Fit(/*in*/ HashOneHotVectorizerFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_t_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_t_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_t_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_t_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_t_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_t_Transform(/*in*/ HashOneHotVectorizerFeaturizer_int64_t_TransformerHandle *pHandle, /*in*/ int64_t input, /*out via struct*/ HashOneHotVectorizerStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_int64_t_DestroyTransformedData(/*in*/ HashOneHotVectorizerStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <uint8_t> */
struct HashOneHotVectorizerFeaturizer_uint8_t_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_uint8_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_t_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_uint8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_t_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_t_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_t_Fit(/*in*/ HashOneHotVectorizerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_t_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_t_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_t_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_t_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_t_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_t_Transform(/*in*/ HashOneHotVectorizerFeaturizer_uint8_t_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out via struct*/ HashOneHotVectorizerStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint8_t_DestroyTransformedData(/*in*/ HashOneHotVectorizerStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <uint16_t> */
struct HashOneHotVectorizerFeaturizer_uint16_t_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_uint16_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_t_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_uint16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_t_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_t_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_t_Fit(/*in*/ HashOneHotVectorizerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_t_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_t_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_t_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_t_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_t_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_t_Transform(/*in*/ HashOneHotVectorizerFeaturizer_uint16_t_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out via struct*/ HashOneHotVectorizerStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint16_t_DestroyTransformedData(/*in*/ HashOneHotVectorizerStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <uint32_t> */
struct HashOneHotVectorizerFeaturizer_uint32_t_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_uint32_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_t_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_uint32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_t_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_t_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_t_Fit(/*in*/ HashOneHotVectorizerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_t_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_t_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_t_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_t_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_t_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_t_Transform(/*in*/ HashOneHotVectorizerFeaturizer_uint32_t_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out via struct*/ HashOneHotVectorizerStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint32_t_DestroyTransformedData(/*in*/ HashOneHotVectorizerStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <uint64_t> */
struct HashOneHotVectorizerFeaturizer_uint64_t_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_uint64_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_t_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_uint64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_t_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_t_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_t_Fit(/*in*/ HashOneHotVectorizerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_t_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_t_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_t_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_t_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_t_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_t_Transform(/*in*/ HashOneHotVectorizerFeaturizer_uint64_t_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out via struct*/ HashOneHotVectorizerStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_uint64_t_DestroyTransformedData(/*in*/ HashOneHotVectorizerStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <float_t> */
struct HashOneHotVectorizerFeaturizer_float_t_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_float_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_t_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_float_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_t_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_t_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_t_Fit(/*in*/ HashOneHotVectorizerFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_t_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_t_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_t_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_float_t_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_t_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_t_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_t_Transform(/*in*/ HashOneHotVectorizerFeaturizer_float_t_TransformerHandle *pHandle, /*in*/ float input, /*out via struct*/ HashOneHotVectorizerStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_float_t_DestroyTransformedData(/*in*/ HashOneHotVectorizerStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <double_t> */
struct HashOneHotVectorizerFeaturizer_double_t_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_double_t_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_t_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_double_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_t_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_t_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_t_Fit(/*in*/ HashOneHotVectorizerFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_t_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_t_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_t_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_double_t_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_t_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_t_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_t_Transform(/*in*/ HashOneHotVectorizerFeaturizer_double_t_TransformerHandle *pHandle, /*in*/ double input, /*out via struct*/ HashOneHotVectorizerStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_double_t_DestroyTransformedData(/*in*/ HashOneHotVectorizerStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <bool> */
struct HashOneHotVectorizerFeaturizer_bool_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_bool_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_Fit(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_Transform(/*in*/ HashOneHotVectorizerFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool input, /*out via struct*/ HashOneHotVectorizerStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_bool_DestroyTransformedData(/*in*/ HashOneHotVectorizerStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <string> */
struct HashOneHotVectorizerFeaturizer_string_EstimatorHandle {};
struct HashOneHotVectorizerFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_CreateEstimator(/*in*/ uint32_t hashingSeedVal, /*in*/ uint32_t numCols,/*out*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_DestroyEstimator(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_IsTrainingComplete(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_Fit(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_FitBuffer(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_CompleteTraining(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_CreateTransformerFromEstimator(/*in*/ HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ HashOneHotVectorizerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ HashOneHotVectorizerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_DestroyTransformer(/*in*/ HashOneHotVectorizerFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_CreateTransformerSaveData(/*in*/ HashOneHotVectorizerFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_Transform(/*in*/ HashOneHotVectorizerFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const *input, /*out via struct*/ HashOneHotVectorizerStruct * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool HashOneHotVectorizerFeaturizer_string_DestroyTransformedData(/*in*/ HashOneHotVectorizerStruct * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
