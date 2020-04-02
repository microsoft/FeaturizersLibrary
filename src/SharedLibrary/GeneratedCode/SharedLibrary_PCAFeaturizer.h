/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  PCAFeaturizer <float> */
struct PCAFeaturizer_float_EstimatorHandle {};
struct PCAFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_CreateEstimator(/*out*/ PCAFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_DestroyEstimator(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_GetState(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_IsTrainingComplete(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_Fit(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ float const * input_ptr, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_FitBuffer(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ float const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_OnDataCompleted(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_CompleteTraining(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_CreateTransformerFromEstimator(/*in*/ PCAFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ PCAFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ PCAFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_DestroyTransformer(/*in*/ PCAFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_CreateTransformerSaveData(/*in*/ PCAFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_Transform(/*in*/ PCAFeaturizer_float_TransformerHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ float const * input_ptr, /*out*/ size_t * output_cols, /*out*/ size_t * output_rows, /*out*/ float ** output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_Flush(/*in*/ PCAFeaturizer_float_TransformerHandle *pHandle, /*out*/ size_t ** output_item_cols_ptr, /*out*/ size_t ** output_item_rows_ptr, /*out*/ float *** output_item_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_DestroyTransformedData(/*in*/ size_t result_cols, /*in*/ size_t result_rows, /*in*/ float const * result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  PCAFeaturizer <double> */
struct PCAFeaturizer_double_EstimatorHandle {};
struct PCAFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_CreateEstimator(/*out*/ PCAFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_DestroyEstimator(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_GetState(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_IsTrainingComplete(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_Fit(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ double const * input_ptr, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_FitBuffer(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ double const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_OnDataCompleted(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_CompleteTraining(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_CreateTransformerFromEstimator(/*in*/ PCAFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ PCAFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ PCAFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_DestroyTransformer(/*in*/ PCAFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_CreateTransformerSaveData(/*in*/ PCAFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_Transform(/*in*/ PCAFeaturizer_double_TransformerHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ double const * input_ptr, /*out*/ size_t * output_cols, /*out*/ size_t * output_rows, /*out*/ double ** output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_Flush(/*in*/ PCAFeaturizer_double_TransformerHandle *pHandle, /*out*/ size_t ** output_item_cols_ptr, /*out*/ size_t ** output_item_rows_ptr, /*out*/ double *** output_item_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_DestroyTransformedData(/*in*/ size_t result_cols, /*in*/ size_t result_rows, /*in*/ double const * result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
