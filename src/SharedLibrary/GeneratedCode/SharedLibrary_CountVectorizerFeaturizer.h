/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

enum CountVectorizerFeaturizer_AnalyzerMethodValue {
    CountVectorizerFeaturizer_AnalyzerMethod_Word=1,
    CountVectorizerFeaturizer_AnalyzerMethod_Char=2,
    CountVectorizerFeaturizer_AnalyzerMethod_Charwb=3
};

typedef uint8_t CountVectorizerFeaturizer_AnalyzerMethodType;


/* ---------------------------------------------------------------------- */
/* |  CountVectorizerFeaturizer */
struct CountVectorizerFeaturizer_EstimatorHandle {};
struct CountVectorizerFeaturizer_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_CreateEstimator(/*in*/ bool lower, /*in*/ uint8_t analyzer, /*in*/ char const *regexToken, /*in*/ float maxDf, /*in*/ float minDf, /*in*/ uint32_t const * topKTerms, /*in*/ uint32_t ngramRangeMin, /*in*/ uint32_t ngramRangeMax, /*in*/ bool binary,/*out*/ CountVectorizerFeaturizer_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_DestroyEstimator(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_GetState(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_IsTrainingComplete(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_Fit(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_FitBuffer(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_OnDataCompleted(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_CompleteTraining(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_CreateTransformerFromEstimator(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pEstimatorHandle, /*out*/ CountVectorizerFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ CountVectorizerFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_DestroyTransformer(/*in*/ CountVectorizerFeaturizer_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_CreateTransformerSaveData(/*in*/ CountVectorizerFeaturizer_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_Transform(/*in*/ CountVectorizerFeaturizer_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ uint64_t * output_numElements, /*out*/ uint64_t * output_numValues, /*out*/ float **output_values, /*out*/ uint64_t **output_indexes, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_DestroyTransformedData(/*in*/ uint64_t result_numElements, /*in*/ uint64_t result_numValues, /*in*/ float const * result_values, /*in*/ uint64_t const * result_indexes, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
