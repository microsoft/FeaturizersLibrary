/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  LagLeadOperatorFeaturizer <float> */
struct LagLeadOperatorFeaturizer_float_EstimatorHandle {};
struct LagLeadOperatorFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_CreateEstimator(/*in*/ uint32_t horizon, /*in*/ int64_t const * deltas_ptr, /*in*/ size_t deltas_items,/*out*/ LagLeadOperatorFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_DestroyEstimator(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_GetState(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_IsTrainingComplete(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_Fit(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_FitBuffer(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ float const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_OnDataCompleted(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_CompleteTraining(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_CreateTransformerFromEstimator(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ LagLeadOperatorFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ LagLeadOperatorFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_DestroyTransformer(/*in*/ LagLeadOperatorFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_CreateTransformerSaveData(/*in*/ LagLeadOperatorFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_Transform(/*in*/ LagLeadOperatorFeaturizer_float_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ char **** output_item0_ptr_ptr, /*out*/ size_t ** output_item0_items_ptr, /*out*/ size_t ** output_item1_cols_ptr, /*out*/ size_t ** output_item1_rows_ptr, /*out*/ float *** output_item1_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_Flush(/*in*/ LagLeadOperatorFeaturizer_float_TransformerHandle *pHandle, /*out*/ char **** output_item0_ptr_ptr, /*out*/ size_t ** output_item0_items_ptr, /*out*/ size_t ** output_item1_cols_ptr, /*out*/ size_t ** output_item1_rows_ptr, /*out*/ float *** output_item1_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_DestroyTransformedData(/*in*/ char *** result_item0_ptr_ptr, /*in*/ size_t * result_item0_items_ptr, /*in*/ size_t * result_item1_cols_ptr, /*in*/ size_t * result_item1_rows_ptr, /*in*/ float ** result_item1_ptr_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  LagLeadOperatorFeaturizer <double> */
struct LagLeadOperatorFeaturizer_double_EstimatorHandle {};
struct LagLeadOperatorFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_CreateEstimator(/*in*/ uint32_t horizon, /*in*/ int64_t const * deltas_ptr, /*in*/ size_t deltas_items,/*out*/ LagLeadOperatorFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_DestroyEstimator(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_GetState(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_IsTrainingComplete(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_Fit(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_FitBuffer(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ double const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_OnDataCompleted(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_CompleteTraining(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_CreateTransformerFromEstimator(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ LagLeadOperatorFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ LagLeadOperatorFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_DestroyTransformer(/*in*/ LagLeadOperatorFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_CreateTransformerSaveData(/*in*/ LagLeadOperatorFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_Transform(/*in*/ LagLeadOperatorFeaturizer_double_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ char **** output_item0_ptr_ptr, /*out*/ size_t ** output_item0_items_ptr, /*out*/ size_t ** output_item1_cols_ptr, /*out*/ size_t ** output_item1_rows_ptr, /*out*/ double *** output_item1_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_Flush(/*in*/ LagLeadOperatorFeaturizer_double_TransformerHandle *pHandle, /*out*/ char **** output_item0_ptr_ptr, /*out*/ size_t ** output_item0_items_ptr, /*out*/ size_t ** output_item1_cols_ptr, /*out*/ size_t ** output_item1_rows_ptr, /*out*/ double *** output_item1_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_DestroyTransformedData(/*in*/ char *** result_item0_ptr_ptr, /*in*/ size_t * result_item0_items_ptr, /*in*/ size_t * result_item1_cols_ptr, /*in*/ size_t * result_item1_rows_ptr, /*in*/ double ** result_item1_ptr_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
