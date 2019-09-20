/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_DateTimeFeaturizer.h"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "DateTimeFeaturizer.h"

// These method(s) are defined in SharedLibrary_Common.cpp
ErrorInfoHandle * CreateErrorInfo(std::exception const &ex);

extern "C" {

// I don't know why MSVC thinks that there is unreachable
// code in these methods during release builds.
#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4702) // Unreachable code
#endif

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  DateTimeFeaturizer */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateEstimator(/*in*/ char const *optionalCountryName, /*out*/ DateTimeFeaturizer_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::DateTimeEstimator* pEstimator = new Microsoft::Featurizer::Featurizers::DateTimeEstimator(optionalCountryName ? std::string(optionalCountryName) : nonstd::optional<std::string>(), std::make_shared<Microsoft::Featurizer::AnnotationMaps>(21));
        size_t index(sg_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<DateTimeFeaturizer_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_DestroyEstimator(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::DateTimeEstimator * pEstimator = sg_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(index);
        sg_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_IsTrainingComplete(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::DateTimeEstimator const & estimator(*sg_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(reinterpret_cast<size_t>(pHandle)));


        *pIsTrainingComplete = estimator.is_training_complete();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_Fit(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::DateTimeEstimator & estimator(*sg_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_FitBuffer(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::DateTimeEstimator & estimator(*sg_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CompleteTraining(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        Microsoft::Featurizer::Featurizers::DateTimeEstimator & estimator(*sg_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.complete_training());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateTransformerFromEstimator(/*in*/ DateTimeFeaturizer_EstimatorHandle *pEstimatorHandle, /*out*/ DateTimeFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::DateTimeEstimator & estimator(*sg_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType*>(estimator.create_transformer().release());


        size_t index = sg_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<DateTimeFeaturizer_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ DateTimeFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType>(archive).release());

        size_t index = sg_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<DateTimeFeaturizer_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_DestroyTransformer(/*in*/ DateTimeFeaturizer_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType* pTransformer = sg_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType>(index);
        sg_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateTransformerSaveData(/*in*/ DateTimeFeaturizer_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType & transformer(*sg_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType>(reinterpret_cast<size_t>(pHandle)));
        Microsoft::Featurizer::Archive archive;

        transformer.save(archive);

        Microsoft::Featurizer::Archive::ByteArray const buffer(archive.commit());

        unsigned char * new_buffer(new unsigned char[buffer.size()]);

        std::copy(buffer.begin(), buffer.end(), new_buffer);

        *ppBuffer = new_buffer;
        *pBufferSize = buffer.size();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");

        delete [] pBuffer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_Transform(/*in*/ DateTimeFeaturizer_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ TimePoint ** output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType & transformer(*sg_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input));

        // Output
        TimePoint output_item;

        output_item.year = result.year;
        output_item.month = result.month;
        output_item.day = result.day;
        output_item.hour = result.hour;
        output_item.minute = result.minute;
        output_item.second = result.second;
        output_item.amPm = result.amPm;
        output_item.hour12 = result.hour12;
        output_item.dayOfWeek = result.dayOfWeek;
        output_item.dayOfQuarter = result.dayOfQuarter;
        output_item.dayOfYear = result.dayOfYear;
        output_item.weekOfMonth = result.weekOfMonth;
        output_item.quarterOfYear = result.quarterOfYear;
        output_item.halfOfYear = result.halfOfYear;
        output_item.weekIso = result.weekIso;
        output_item.yearIso = result.yearIso;
        if(result.monthLabel.empty()) {
            output_item.monthLabel_ptr = nullptr;
            output_item.monthLabel_items = 0;
        } else {
            char * string_buffer(new char[result.monthLabel.size() + 1]);

            std::copy(result.monthLabel.begin(), result.monthLabel.end(), string_buffer);
            string_buffer[result.monthLabel.size()] = 0;

            output_item.monthLabel_ptr = string_buffer;
            output_item.monthLabel_items = result.monthLabel.size();
        }

        if(result.amPmLabel.empty()) {
            output_item.amPmLabel_ptr = nullptr;
            output_item.amPmLabel_items = 0;
        } else {
            char * string_buffer(new char[result.amPmLabel.size() + 1]);

            std::copy(result.amPmLabel.begin(), result.amPmLabel.end(), string_buffer);
            string_buffer[result.amPmLabel.size()] = 0;

            output_item.amPmLabel_ptr = string_buffer;
            output_item.amPmLabel_items = result.amPmLabel.size();
        }

        if(result.dayOfWeekLabel.empty()) {
            output_item.dayOfWeekLabel_ptr = nullptr;
            output_item.dayOfWeekLabel_items = 0;
        } else {
            char * string_buffer(new char[result.dayOfWeekLabel.size() + 1]);

            std::copy(result.dayOfWeekLabel.begin(), result.dayOfWeekLabel.end(), string_buffer);
            string_buffer[result.dayOfWeekLabel.size()] = 0;

            output_item.dayOfWeekLabel_ptr = string_buffer;
            output_item.dayOfWeekLabel_items = result.dayOfWeekLabel.size();
        }

        if(result.holidayName.empty()) {
            output_item.holidayName_ptr = nullptr;
            output_item.holidayName_items = 0;
        } else {
            char * string_buffer(new char[result.holidayName.size() + 1]);

            std::copy(result.holidayName.begin(), result.holidayName.end(), string_buffer);
            string_buffer[result.holidayName.size()] = 0;

            output_item.holidayName_ptr = string_buffer;
            output_item.holidayName_items = result.holidayName.size();
        }

        output_item.isPaidTimeOff = result.isPaidTimeOff;

        *output = std::make_unique<TimePoint>(std::move(output_item)).release();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_DestroyTransformedData(/*in*/ TimePoint * result, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result->monthLabel_ptr == nullptr && result->monthLabel_items != 0) throw std::invalid_argument("Invalid buffer");
        if(result->monthLabel_ptr != nullptr && result->monthLabel_items == 0) throw std::invalid_argument("Invalid buffer");

        if(result->amPmLabel_ptr == nullptr && result->amPmLabel_items != 0) throw std::invalid_argument("Invalid buffer");
        if(result->amPmLabel_ptr != nullptr && result->amPmLabel_items == 0) throw std::invalid_argument("Invalid buffer");

        if(result->dayOfWeekLabel_ptr == nullptr && result->dayOfWeekLabel_items != 0) throw std::invalid_argument("Invalid buffer");
        if(result->dayOfWeekLabel_ptr != nullptr && result->dayOfWeekLabel_items == 0) throw std::invalid_argument("Invalid buffer");

        if(result->holidayName_ptr == nullptr && result->holidayName_items != 0) throw std::invalid_argument("Invalid buffer");
        if(result->holidayName_ptr != nullptr && result->holidayName_items == 0) throw std::invalid_argument("Invalid buffer");

        if(result->monthLabel_ptr)
            delete [] result->monthLabel_ptr;

        if(result->amPmLabel_ptr)
            delete [] result->amPmLabel_ptr;

        if(result->dayOfWeekLabel_ptr)
            delete [] result->dayOfWeekLabel_ptr;

        if(result->holidayName_ptr)
            delete [] result->holidayName_ptr;

        delete result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}


#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

} // extern "C"
