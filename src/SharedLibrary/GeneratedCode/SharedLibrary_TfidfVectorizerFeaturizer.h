/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

enum TfidfVectorizerFeaturizer_AnalyzerMethodValue {
    TfidfVectorizerFeaturizer_AnalyzerMethod_Word=1,
    TfidfVectorizerFeaturizer_AnalyzerMethod_Char=2,
    TfidfVectorizerFeaturizer_AnalyzerMethod_Charwb=3
};

typedef uint8_t TfidfVectorizerFeaturizer_AnalyzerMethodType;

enum TfidfVectorizerFeaturizer_NormMethodValue {
    TfidfVectorizerFeaturizer_NormMethod_L1=1,
    TfidfVectorizerFeaturizer_NormMethod_L2=2,
    TfidfVectorizerFeaturizer_NormMethod_None=3
};

typedef uint8_t TfidfVectorizerFeaturizer_NormMethodType;

enum TfidfVectorizerFeaturizer_TfidfPolicyValue {
    TfidfVectorizerFeaturizer_TfidfPolicy_Binary=1,
    TfidfVectorizerFeaturizer_TfidfPolicy_UseIdf=2,
    TfidfVectorizerFeaturizer_TfidfPolicy_SmoothIdf=4,
    TfidfVectorizerFeaturizer_TfidfPolicy_SublinearTf=8
};

typedef uint32_t TfidfVectorizerFeaturizer_TfidfPolicyType;


/* ---------------------------------------------------------------------- */
/* |  TfidfVectorizerFeaturizer */
struct TfidfVectorizerFeaturizer_EstimatorHandle {};
struct TfidfVectorizerFeaturizer_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_CreateEstimator(/*in*/ bool lowercase, /*in*/ uint8_t analyzer, /*in*/ char const * regexToken, /*in*/ uint8_t norm, /*in*/ uint32_t policy, /*in*/ float minDf, /*in*/ float maxDf, /*in*/ uint32_t const * topKTerms, /*in*/ uint32_t ngramRangeMin, /*in*/ uint32_t ngramRangeMax,/*out*/ TfidfVectorizerFeaturizer_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_DestroyEstimator(/*in*/ TfidfVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_GetState(/*in*/ TfidfVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_IsTrainingComplete(/*in*/ TfidfVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_Fit(/*in*/ TfidfVectorizerFeaturizer_EstimatorHandle *pHandle, /*in*/ char const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_FitBuffer(/*in*/ TfidfVectorizerFeaturizer_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_OnDataCompleted(/*in*/ TfidfVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_CompleteTraining(/*in*/ TfidfVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_CreateTransformerFromEstimator(/*in*/ TfidfVectorizerFeaturizer_EstimatorHandle *pEstimatorHandle, /*out*/ TfidfVectorizerFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ TfidfVectorizerFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_DestroyTransformer(/*in*/ TfidfVectorizerFeaturizer_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_CreateTransformerSaveData(/*in*/ TfidfVectorizerFeaturizer_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_Transform(/*in*/ TfidfVectorizerFeaturizer_TransformerHandle *pHandle, /*in*/ char const * input, /*out*/ uint64_t * output_numElements, /*out*/ uint64_t * output_numValues, /*out*/ float ** output_values, /*out*/ uint64_t ** output_indexes, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_Flush(/*in*/ TfidfVectorizerFeaturizer_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint64_t ** output_item_numValues_ptr, /*out*/ float *** output_item_values_ptr, /*out*/ uint64_t *** output_item_indexes_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TfidfVectorizerFeaturizer_DestroyTransformedData(/*in*/ uint64_t result_numElements, /*in*/ uint64_t result_numValues, /*in*/ float const * result_values, /*in*/ uint64_t const * result_indexes, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
