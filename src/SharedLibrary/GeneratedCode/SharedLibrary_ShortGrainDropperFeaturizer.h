/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  ShortGrainDropperFeaturizer */
struct ShortGrainDropperFeaturizer_EstimatorHandle {};
struct ShortGrainDropperFeaturizer_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_CreateEstimator(/*in*/ uint32_t minPoints,/*out*/ ShortGrainDropperFeaturizer_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_DestroyEstimator(/*in*/ ShortGrainDropperFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_GetState(/*in*/ ShortGrainDropperFeaturizer_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_IsTrainingComplete(/*in*/ ShortGrainDropperFeaturizer_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_Fit(/*in*/ ShortGrainDropperFeaturizer_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_FitBuffer(/*in*/ ShortGrainDropperFeaturizer_EstimatorHandle *pHandle, /*in*/ char const * const * const * input_ptrs, /*in*/ size_t const * input_ptr_items, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_OnDataCompleted(/*in*/ ShortGrainDropperFeaturizer_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_CompleteTraining(/*in*/ ShortGrainDropperFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_CreateTransformerFromEstimator(/*in*/ ShortGrainDropperFeaturizer_EstimatorHandle *pEstimatorHandle, /*out*/ ShortGrainDropperFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ShortGrainDropperFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_DestroyTransformer(/*in*/ ShortGrainDropperFeaturizer_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_CreateTransformerSaveData(/*in*/ ShortGrainDropperFeaturizer_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_Transform(/*in*/ ShortGrainDropperFeaturizer_TransformerHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ size_t input_items, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ShortGrainDropperFeaturizer_Flush(/*in*/ ShortGrainDropperFeaturizer_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
