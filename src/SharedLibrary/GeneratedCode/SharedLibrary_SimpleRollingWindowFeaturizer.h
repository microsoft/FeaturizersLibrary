/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {

enum SimpleRollingWindowFeaturizer_SimpleRollingWindowCalculationValue {
    SimpleRollingWindowFeaturizer_SimpleRollingWindowCalculation_Min=1,
    SimpleRollingWindowFeaturizer_SimpleRollingWindowCalculation_Max=2
};

typedef uint8_t SimpleRollingWindowFeaturizer_SimpleRollingWindowCalculationType;


/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <float> */
struct SimpleRollingWindowFeaturizer_float_EstimatorHandle {};
struct SimpleRollingWindowFeaturizer_float_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_GetState(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_Fit(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ float const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_Transform(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ size_t * output_cols, /*out*/ size_t * output_rows, /*out*/ float ** output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_Flush(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ size_t ** output_item_cols_ptr, /*out*/ size_t ** output_item_rows_ptr, /*out*/ float *** output_item_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_DestroyTransformedData(/*in*/ size_t result_cols, /*in*/ size_t result_rows, /*in*/ float const * result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <double> */
struct SimpleRollingWindowFeaturizer_double_EstimatorHandle {};
struct SimpleRollingWindowFeaturizer_double_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_GetState(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_Fit(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ double const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_Transform(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ size_t * output_cols, /*out*/ size_t * output_rows, /*out*/ double ** output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_Flush(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ size_t ** output_item_cols_ptr, /*out*/ size_t ** output_item_rows_ptr, /*out*/ double *** output_item_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_DestroyTransformedData(/*in*/ size_t result_cols, /*in*/ size_t result_rows, /*in*/ double const * result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
