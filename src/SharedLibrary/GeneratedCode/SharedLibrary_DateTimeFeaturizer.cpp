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
std::chrono::system_clock::time_point CreateDateTime(DateTimeParameter const &param);

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
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateEstimator(/*in*/ char const *optionalCountryName, /*in*/ char const *optionalDataRootDir, /*out*/ DateTimeFeaturizer_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::DateTimeEstimator* pEstimator = new Microsoft::Featurizer::Featurizers::DateTimeEstimator(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(21) , optionalCountryName ? std::string(optionalCountryName) : nonstd::optional<std::string>(), optionalDataRootDir ? std::string(optionalDataRootDir) : nonstd::optional<std::string>());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
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
        Microsoft::Featurizer::Featurizers::DateTimeEstimator * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_GetState(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::DateTimeEstimator & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
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

        Microsoft::Featurizer::Featurizers::DateTimeEstimator const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_Fit(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*in*/ DateTimeParameter input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::DateTimeEstimator & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(CreateDateTime(input)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_FitBuffer(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*in*/ DateTimeParameter const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::chrono::system_clock::time_point> input_buffer;

        input_buffer.reserve(input_items);

        DateTimeParameter const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
            input_buffer.push_back(CreateDateTime(*input_ptr));
        #else
            input_buffer.emplace_back(CreateDateTime(*input_ptr));
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::DateTimeEstimator & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_OnDataCompleted(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::DateTimeEstimator & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CompleteTraining(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::DateTimeEstimator & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
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



        Microsoft::Featurizer::Featurizers::DateTimeEstimator & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
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

        Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
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
        Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType>(index);
        g_pointerTable.Remove(index);


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

        Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_Transform(/*in*/ DateTimeFeaturizer_TransformerHandle *pHandle, /*in*/ DateTimeParameter input, /*out via struct*/ TimePoint * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(CreateDateTime(input)));

        // Output
        output->year = result.year;
        output->month = result.month;
        output->day = result.day;
        output->hour = result.hour;
        output->minute = result.minute;
        output->second = result.second;
        output->amPm = result.amPm;
        output->hour12 = result.hour12;
        output->dayOfWeek = result.dayOfWeek;
        output->dayOfQuarter = result.dayOfQuarter;
        output->dayOfYear = result.dayOfYear;
        output->weekOfMonth = result.weekOfMonth;
        output->quarterOfYear = result.quarterOfYear;
        output->halfOfYear = result.halfOfYear;
        output->weekIso = result.weekIso;
        output->yearIso = result.yearIso;
        if(result.monthLabel.empty()) {
            output->monthLabel_ptr = nullptr;
            output->monthLabel_items = 0;
        }
        else {
            char * string_buffer(new char[result.monthLabel.size() + 1]);

            std::copy(result.monthLabel.begin(), result.monthLabel.end(), string_buffer);
            string_buffer[result.monthLabel.size()] = 0;

            output->monthLabel_ptr = string_buffer;
            output->monthLabel_items = result.monthLabel.size();
        }

        if(result.amPmLabel.empty()) {
            output->amPmLabel_ptr = nullptr;
            output->amPmLabel_items = 0;
        }
        else {
            char * string_buffer(new char[result.amPmLabel.size() + 1]);

            std::copy(result.amPmLabel.begin(), result.amPmLabel.end(), string_buffer);
            string_buffer[result.amPmLabel.size()] = 0;

            output->amPmLabel_ptr = string_buffer;
            output->amPmLabel_items = result.amPmLabel.size();
        }

        if(result.dayOfWeekLabel.empty()) {
            output->dayOfWeekLabel_ptr = nullptr;
            output->dayOfWeekLabel_items = 0;
        }
        else {
            char * string_buffer(new char[result.dayOfWeekLabel.size() + 1]);

            std::copy(result.dayOfWeekLabel.begin(), result.dayOfWeekLabel.end(), string_buffer);
            string_buffer[result.dayOfWeekLabel.size()] = 0;

            output->dayOfWeekLabel_ptr = string_buffer;
            output->dayOfWeekLabel_items = result.dayOfWeekLabel.size();
        }

        if(result.holidayName.empty()) {
            output->holidayName_ptr = nullptr;
            output->holidayName_items = 0;
        }
        else {
            char * string_buffer(new char[result.holidayName.size() + 1]);

            std::copy(result.holidayName.begin(), result.holidayName.end(), string_buffer);
            string_buffer[result.holidayName.size()] = 0;

            output->holidayName_ptr = string_buffer;
            output->holidayName_items = result.holidayName.size();
        }

        output->isPaidTimeOff = result.isPaidTimeOff;
    
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

        if(result == nullptr) throw std::invalid_argument("'result' is null");
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
