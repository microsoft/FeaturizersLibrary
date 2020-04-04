/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  ForecastingPivotFeaturizer <float> */
struct ForecastingPivotFeaturizer_float_EstimatorHandle {};
struct ForecastingPivotFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_CreateEstimator(/*out*/ ForecastingPivotFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_DestroyEstimator(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_GetState(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_IsTrainingComplete(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_Fit(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*in*/ size_t const * input_cols_ptr, /*in*/ size_t const * input_rows_ptr, /*in*/ float const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_FitBuffer(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*in*/ size_t const * const * input_item_cols_ptr_ptr, /*in*/ size_t const * const * input_item_rows_ptr_ptr, /*in*/ float const ** const * input_item_values_ptr_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_OnDataCompleted(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_CompleteTraining(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_CreateTransformerFromEstimator(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ ForecastingPivotFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForecastingPivotFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_DestroyTransformer(/*in*/ ForecastingPivotFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_CreateTransformerSaveData(/*in*/ ForecastingPivotFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_Transform(/*in*/ ForecastingPivotFeaturizer_float_TransformerHandle *pHandle, /*in*/ size_t const * input_cols_ptr, /*in*/ size_t const * input_rows_ptr, /*in*/ float const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ float *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_Flush(/*in*/ ForecastingPivotFeaturizer_float_TransformerHandle *pHandle, /*out*/ float *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_DestroyTransformedData(/*in*/ float ** result_item_item_ptr_ptr, /*in*/ size_t * result_item_items_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  ForecastingPivotFeaturizer <double> */
struct ForecastingPivotFeaturizer_double_EstimatorHandle {};
struct ForecastingPivotFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_CreateEstimator(/*out*/ ForecastingPivotFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_DestroyEstimator(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_GetState(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_IsTrainingComplete(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_Fit(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*in*/ size_t const * input_cols_ptr, /*in*/ size_t const * input_rows_ptr, /*in*/ double const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_FitBuffer(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*in*/ size_t const * const * input_item_cols_ptr_ptr, /*in*/ size_t const * const * input_item_rows_ptr_ptr, /*in*/ double const ** const * input_item_values_ptr_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_OnDataCompleted(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_CompleteTraining(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_CreateTransformerFromEstimator(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ ForecastingPivotFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForecastingPivotFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_DestroyTransformer(/*in*/ ForecastingPivotFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_CreateTransformerSaveData(/*in*/ ForecastingPivotFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_Transform(/*in*/ ForecastingPivotFeaturizer_double_TransformerHandle *pHandle, /*in*/ size_t const * input_cols_ptr, /*in*/ size_t const * input_rows_ptr, /*in*/ double const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_Flush(/*in*/ ForecastingPivotFeaturizer_double_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_DestroyTransformedData(/*in*/ double ** result_item_item_ptr_ptr, /*in*/ size_t * result_item_items_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
