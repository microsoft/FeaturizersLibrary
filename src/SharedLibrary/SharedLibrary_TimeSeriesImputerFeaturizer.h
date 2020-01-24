// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

// Note that most of the shared code is generated for each Featurizer. The
// TimeSeriesImputer is more complex than the other Featurizers, so this one
// is written by hand for now.

#include "SharedLibrary_Common.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/* |  TimeSeriesImputerFeaturizer <BinaryArchive> */

// Each "row" in this implementation is the serialized content of the row itself. Clients will serialize the data,
// pass it to these methods where it will be deserialized according to the type enumerations provided when creating
// the Estimator. Output will be serialized and passed back to the caller.

struct TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle {};
struct TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle {};

FEATURIZER_LIBRARY_API_PACK_PREFIX

struct BinaryArchiveData {
    unsigned char const * pBuffer;
    std::size_t cBuffer;
} FEATURIZER_LIBRARY_API_PACK_INLINE;

FEATURIZER_LIBRARY_API_PACK_SUFFIX

// These values should match those found in Featurizers/Components/TimeSeriesImputerTransformer.h
enum ImputationStrategyValue {
    Forward = 1,
    Backward,
    Median,
    Interpolate
};

typedef uint8_t ImputationStrategy;

/* Training Methods */
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_CreateEstimator(/*in*/ TypeId *pKeyColTypes, /*in*/ std::size_t numKeyColTypes, /*in*/ TypeId *pDataColTypes, /*in*/ std::size_t numDataColTypes, /*in*/ ImputationStrategy strategy, /*in*/ bool *pSuppressErrors, /*out*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_DestroyEstimator(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_IsTrainingComplete(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_GetState(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_Fit(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pHandle, /*in*/ BinaryArchiveData data, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_FitBuffer(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pHandle, /*in*/ BinaryArchiveData const *pData, /*in*/ std::size_t numDataElements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_OnDataCompleted(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_CompleteTraining(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_CreateTransformerFromEstimator(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pEstimatorHandle, /*out*/ TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_DestroyTransformer(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_CreateTransformerSaveData(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_CreateONNXSaveData(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_Transform(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *pHandle, /*in*/ BinaryArchiveData data, /*out*/ BinaryArchiveData **ppData, /*out*/ std::size_t *pNumDataElements, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_Flush(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *pHandle, /*out*/ BinaryArchiveData ** ppData, /*out*/ std::size_t *pNumDataElements, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_DestroyTransformedData(/*in*/ BinaryArchiveData const *pData, /*in*/ std::size_t numDataElements, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
