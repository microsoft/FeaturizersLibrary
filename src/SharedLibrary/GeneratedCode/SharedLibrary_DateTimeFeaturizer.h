/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"

extern "C" {
FEATURIZER_LIBRARY_API_PACK_PREFIX

struct TimePoint {
    /*out*/ int32_t year;
    /*out*/ uint8_t month;
    /*out*/ uint8_t day;
    /*out*/ uint8_t hour;
    /*out*/ uint8_t minute;
    /*out*/ uint8_t second;
    /*out*/ uint8_t amPm;
    /*out*/ uint8_t hour12;
    /*out*/ uint8_t dayOfWeek;
    /*out*/ uint8_t dayOfQuarter;
    /*out*/ uint16_t dayOfYear;
    /*out*/ uint16_t weekOfMonth;
    /*out*/ uint8_t quarterOfYear;
    /*out*/ uint8_t halfOfYear;
    /*out*/ uint8_t weekIso;
    /*out*/ int32_t yearIso;
    /*out*/ char const * monthLabel_ptr;
    /*out*/ std::size_t monthLabel_items;
    /*out*/ char const * amPmLabel_ptr;
    /*out*/ std::size_t amPmLabel_items;
    /*out*/ char const * dayOfWeekLabel_ptr;
    /*out*/ std::size_t dayOfWeekLabel_items;
    /*out*/ char const * holidayName_ptr;
    /*out*/ std::size_t holidayName_items;
    /*out*/ uint8_t isPaidTimeOff;
} FEATURIZER_LIBRARY_API_PACK_INLINE;

FEATURIZER_LIBRARY_API_PACK_SUFFIX


/* ---------------------------------------------------------------------- */
/* |  DateTimeFeaturizer */
struct DateTimeFeaturizer_EstimatorHandle {};
struct DateTimeFeaturizer_TransformerHandle {};

/* Training Methods */
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateEstimator(/*in*/ char const *optionalCountryName, /*in*/ char const *optionalDataRootDir,/*out*/ DateTimeFeaturizer_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_DestroyEstimator(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_GetState(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_IsTrainingComplete(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_Fit(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_FitBuffer(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_OnDataCompleted(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*out*/ /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CompleteTraining(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

/* Inference Methods */
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateTransformerFromEstimator(/*in*/ DateTimeFeaturizer_EstimatorHandle *pEstimatorHandle, /*out*/ DateTimeFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ DateTimeFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_DestroyTransformer(/*in*/ DateTimeFeaturizer_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateTransformerSaveData(/*in*/ DateTimeFeaturizer_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_Transform(/*in*/ DateTimeFeaturizer_TransformerHandle *pHandle, /*in*/ int64_t input, /*out via struct*/ TimePoint * output, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_DestroyTransformedData(/*in*/ TimePoint * result, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
