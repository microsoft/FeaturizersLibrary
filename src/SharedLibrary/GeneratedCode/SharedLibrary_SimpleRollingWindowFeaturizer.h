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
/* |  SimpleRollingWindowFeaturizer <int8> */
struct SimpleRollingWindowFeaturizer_int8_EstimatorHandle {};
struct SimpleRollingWindowFeaturizer_int8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_GetState(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_Fit(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int8_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ int8_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_Transform(/*in*/ SimpleRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int8_t input1, /*out*/ int8_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_Flush(/*in*/ SimpleRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*out*/ int8_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_DestroyTransformedData(/*in*/ int8_t const * const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <int16> */
struct SimpleRollingWindowFeaturizer_int16_EstimatorHandle {};
struct SimpleRollingWindowFeaturizer_int16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_GetState(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_Fit(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int16_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ int16_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_Transform(/*in*/ SimpleRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int16_t input1, /*out*/ int16_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_Flush(/*in*/ SimpleRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*out*/ int16_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_DestroyTransformedData(/*in*/ int16_t const * const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <int32> */
struct SimpleRollingWindowFeaturizer_int32_EstimatorHandle {};
struct SimpleRollingWindowFeaturizer_int32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_GetState(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_Fit(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int32_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ int32_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_Transform(/*in*/ SimpleRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int32_t input1, /*out*/ int32_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_Flush(/*in*/ SimpleRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*out*/ int32_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_DestroyTransformedData(/*in*/ int32_t const * const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <int64> */
struct SimpleRollingWindowFeaturizer_int64_EstimatorHandle {};
struct SimpleRollingWindowFeaturizer_int64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_GetState(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_Fit(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int64_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ int64_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_Transform(/*in*/ SimpleRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int64_t input1, /*out*/ int64_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_Flush(/*in*/ SimpleRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*out*/ int64_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_DestroyTransformedData(/*in*/ int64_t const * const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <uint8> */
struct SimpleRollingWindowFeaturizer_uint8_EstimatorHandle {};
struct SimpleRollingWindowFeaturizer_uint8_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_GetState(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_Fit(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint8_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ uint8_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_Transform(/*in*/ SimpleRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint8_t input1, /*out*/ uint8_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_Flush(/*in*/ SimpleRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ uint8_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_DestroyTransformedData(/*in*/ uint8_t const * const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <uint16> */
struct SimpleRollingWindowFeaturizer_uint16_EstimatorHandle {};
struct SimpleRollingWindowFeaturizer_uint16_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_GetState(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_Fit(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint16_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ uint16_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_Transform(/*in*/ SimpleRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint16_t input1, /*out*/ uint16_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_Flush(/*in*/ SimpleRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ uint16_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_DestroyTransformedData(/*in*/ uint16_t const * const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <uint32> */
struct SimpleRollingWindowFeaturizer_uint32_EstimatorHandle {};
struct SimpleRollingWindowFeaturizer_uint32_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_GetState(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_Fit(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint32_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ uint32_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_Transform(/*in*/ SimpleRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint32_t input1, /*out*/ uint32_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_Flush(/*in*/ SimpleRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ uint32_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_DestroyTransformedData(/*in*/ uint32_t const * const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <uint64> */
struct SimpleRollingWindowFeaturizer_uint64_EstimatorHandle {};
struct SimpleRollingWindowFeaturizer_uint64_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_GetState(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_Fit(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint64_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ uint64_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_Transform(/*in*/ SimpleRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint64_t input1, /*out*/ uint64_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_Flush(/*in*/ SimpleRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ uint64_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_DestroyTransformedData(/*in*/ uint64_t const * const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

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
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ float const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_Transform(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_Flush(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ float *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_DestroyTransformedData(/*in*/ float const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

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
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ double const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_Transform(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_Flush(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_DestroyTransformedData(/*in*/ double const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <string> */
struct SimpleRollingWindowFeaturizer_string_EstimatorHandle {};
struct SimpleRollingWindowFeaturizer_string_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize,/*out*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_GetState(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_Fit(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ char const * input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ char const * const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_Transform(/*in*/ SimpleRollingWindowFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ char const * input1, /*out*/ char const *** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_Flush(/*in*/ SimpleRollingWindowFeaturizer_string_TransformerHandle *pHandle, /*out*/ char const **** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_DestroyTransformedData(/*in*/ char const * const * result_ptr, /*in*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
