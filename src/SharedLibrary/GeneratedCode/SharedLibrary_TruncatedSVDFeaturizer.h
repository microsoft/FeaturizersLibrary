/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  TruncatedSVDFeaturizer <float> */
struct TruncatedSVDFeaturizer_float_EstimatorHandle {};
struct TruncatedSVDFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_CreateEstimator(/*out*/ TruncatedSVDFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_DestroyEstimator(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_GetState(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_IsTrainingComplete(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_Fit(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ float const * input_ptr, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_FitBuffer(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ float const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_OnDataCompleted(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_CompleteTraining(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_CreateTransformerFromEstimator(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ TruncatedSVDFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ TruncatedSVDFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_DestroyTransformer(/*in*/ TruncatedSVDFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_CreateTransformerSaveData(/*in*/ TruncatedSVDFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_Transform(/*in*/ TruncatedSVDFeaturizer_float_TransformerHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ float const * input_ptr, /*out*/ size_t * output_cols, /*out*/ size_t * output_rows, /*out*/ float ** output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_Flush(/*in*/ TruncatedSVDFeaturizer_float_TransformerHandle *pHandle, /*out*/ size_t ** output_item_cols_ptr, /*out*/ size_t ** output_item_rows_ptr, /*out*/ float *** output_item_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_DestroyTransformedData(/*in*/ size_t result_cols, /*in*/ size_t result_rows, /*in*/ float const * result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  TruncatedSVDFeaturizer <double> */
struct TruncatedSVDFeaturizer_double_EstimatorHandle {};
struct TruncatedSVDFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_CreateEstimator(/*out*/ TruncatedSVDFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_DestroyEstimator(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_GetState(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_IsTrainingComplete(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_Fit(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ double const * input_ptr, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_FitBuffer(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ double const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_OnDataCompleted(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_CompleteTraining(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_CreateTransformerFromEstimator(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ TruncatedSVDFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ TruncatedSVDFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_DestroyTransformer(/*in*/ TruncatedSVDFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_CreateTransformerSaveData(/*in*/ TruncatedSVDFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_Transform(/*in*/ TruncatedSVDFeaturizer_double_TransformerHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ double const * input_ptr, /*out*/ size_t * output_cols, /*out*/ size_t * output_rows, /*out*/ double ** output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_Flush(/*in*/ TruncatedSVDFeaturizer_double_TransformerHandle *pHandle, /*out*/ size_t ** output_item_cols_ptr, /*out*/ size_t ** output_item_rows_ptr, /*out*/ double *** output_item_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_DestroyTransformedData(/*in*/ size_t result_cols, /*in*/ size_t result_rows, /*in*/ double const * result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
