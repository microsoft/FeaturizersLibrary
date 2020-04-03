/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

enum AnalyticalRollingWindowFeaturizer_AnalyticalRollingWindowCalculationValue {
    AnalyticalRollingWindowFeaturizer_AnalyticalRollingWindowCalculation_Mean=1
};

typedef uint8_t AnalyticalRollingWindowFeaturizer_AnalyticalRollingWindowCalculationType;


/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <float> */
struct AnalyticalRollingWindowFeaturizer_float_EstimatorHandle {};
struct AnalyticalRollingWindowFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ float const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ size_t * output_cols, /*out*/ size_t * output_rows, /*out*/ double ** output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ size_t ** output_item_cols_ptr, /*out*/ size_t ** output_item_rows_ptr, /*out*/ double *** output_item_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_DestroyTransformedData(/*in*/ size_t result_cols, /*in*/ size_t result_rows, /*in*/ double const * result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <double> */
struct AnalyticalRollingWindowFeaturizer_double_EstimatorHandle {};
struct AnalyticalRollingWindowFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ double const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ size_t * output_cols, /*out*/ size_t * output_rows, /*out*/ double ** output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ size_t ** output_item_cols_ptr, /*out*/ size_t ** output_item_rows_ptr, /*out*/ double *** output_item_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_DestroyTransformedData(/*in*/ size_t result_cols, /*in*/ size_t result_rows, /*in*/ double const * result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
