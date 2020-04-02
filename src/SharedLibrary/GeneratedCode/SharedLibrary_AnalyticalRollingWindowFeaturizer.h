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
/* |  AnalyticalRollingWindowFeaturizer <int8> */
struct AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle {};
struct AnalyticalRollingWindowFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int8_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ int8_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int8_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_DestroyTransformedData(/*in*/ double * result_item_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <int16> */
struct AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle {};
struct AnalyticalRollingWindowFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int16_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ int16_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int16_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_DestroyTransformedData(/*in*/ double * result_item_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <int32> */
struct AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle {};
struct AnalyticalRollingWindowFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int32_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ int32_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int32_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_DestroyTransformedData(/*in*/ double * result_item_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <int64> */
struct AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle {};
struct AnalyticalRollingWindowFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int64_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ int64_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int64_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_DestroyTransformedData(/*in*/ double * result_item_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <uint8> */
struct AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle {};
struct AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint8_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ uint8_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint8_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_DestroyTransformedData(/*in*/ double * result_item_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <uint16> */
struct AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle {};
struct AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint16_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ uint16_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint16_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_DestroyTransformedData(/*in*/ double * result_item_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <uint32> */
struct AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle {};
struct AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint32_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ uint32_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint32_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_DestroyTransformedData(/*in*/ double * result_item_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <uint64> */
struct AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle {};
struct AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint64_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ uint64_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint64_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_DestroyTransformedData(/*in*/ double * result_item_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_DestroyTransformedData(/*in*/ double * result_item_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_DestroyTransformedData(/*in*/ double * result_item_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
