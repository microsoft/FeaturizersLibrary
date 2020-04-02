/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_DateTimeFeaturizer.h"
#include "SharedLibrary_Common.hpp"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "DateTimeFeaturizer.h"

// These method(s) are defined in SharedLibrary_Common.cpp
ErrorInfoHandle * CreateErrorInfo(std::exception const &ex);
std::chrono::system_clock::time_point CreateDateTime(DateTimeParameter const &param);

extern "C" {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunused-local-typedef"
#endif

#if (defined _MSC_VER)
#   pragma warning(push)

    // I don't know why MSVC thinks that there is unreachable
    // code in these methods during release builds.
#   pragma warning(disable: 4702) // Unreachable code

#   pragma warning(disable: 4701) // potentially uninitialized local variable '<name>' used
#   pragma warning(disable: 4703) // potentially uninitialized local pointer variable '<name>' used
#endif

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  DateTimeFeaturizer */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateEstimator(/*in*/ char const * optionalCountryName, /*in*/ char const * optionalDataRootDir, /*out*/ DateTimeFeaturizer_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_Fit(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*in*/ DateTimeParameter  input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::DateTimeEstimator::InputType;

        Microsoft::Featurizer::Featurizers::DateTimeEstimator & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(CreateDateTime(input)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_FitBuffer(/*in*/ DateTimeFeaturizer_EstimatorHandle *pHandle, /*in*/ DateTimeParameter const *  input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
            input_buffer.emplace_back(CreateDateTime(*input_ptr));
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

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ DateTimeFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateTransformerSaveData(/*in*/ DateTimeFeaturizer_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_Transform(/*in*/ DateTimeFeaturizer_TransformerHandle *pHandle, /*in*/ DateTimeParameter  input, /*out*/ TimePoint * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::DateTimeEstimator::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformedType;

        // Input
        TransformedType result(transformer.execute(CreateDateTime(input)));

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
            output->monthLabel = nullptr;
        }
        else {
            char * string_buffer(new char[result.monthLabel.size() + 1]);

            std::copy(result.monthLabel.begin(), result.monthLabel.end(), string_buffer);
            string_buffer[result.monthLabel.size()] = 0;

            output->monthLabel = string_buffer;
        }

        if(result.amPmLabel.empty()) {
            output->amPmLabel = nullptr;
        }
        else {
            char * string_buffer(new char[result.amPmLabel.size() + 1]);

            std::copy(result.amPmLabel.begin(), result.amPmLabel.end(), string_buffer);
            string_buffer[result.amPmLabel.size()] = 0;

            output->amPmLabel = string_buffer;
        }

        if(result.dayOfWeekLabel.empty()) {
            output->dayOfWeekLabel = nullptr;
        }
        else {
            char * string_buffer(new char[result.dayOfWeekLabel.size() + 1]);

            std::copy(result.dayOfWeekLabel.begin(), result.dayOfWeekLabel.end(), string_buffer);
            string_buffer[result.dayOfWeekLabel.size()] = 0;

            output->dayOfWeekLabel = string_buffer;
        }

        if(result.holidayName.empty()) {
            output->holidayName = nullptr;
        }
        else {
            char * string_buffer(new char[result.holidayName.size() + 1]);

            std::copy(result.holidayName.begin(), result.holidayName.end(), string_buffer);
            string_buffer[result.holidayName.size()] = 0;

            output->holidayName = string_buffer;
        }

        output->isPaidTimeOff = result.isPaidTimeOff;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_Flush(/*in*/ DateTimeFeaturizer_TransformerHandle *pHandle, /*out*/ TimePoint ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new TimePoint[result.size()];

            TimePoint * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                output_item->year = result_item.year;
                output_item->month = result_item.month;
                output_item->day = result_item.day;
                output_item->hour = result_item.hour;
                output_item->minute = result_item.minute;
                output_item->second = result_item.second;
                output_item->amPm = result_item.amPm;
                output_item->hour12 = result_item.hour12;
                output_item->dayOfWeek = result_item.dayOfWeek;
                output_item->dayOfQuarter = result_item.dayOfQuarter;
                output_item->dayOfYear = result_item.dayOfYear;
                output_item->weekOfMonth = result_item.weekOfMonth;
                output_item->quarterOfYear = result_item.quarterOfYear;
                output_item->halfOfYear = result_item.halfOfYear;
                output_item->weekIso = result_item.weekIso;
                output_item->yearIso = result_item.yearIso;
                if(result_item.monthLabel.empty()) {
                    output_item->monthLabel = nullptr;
                }
                else {
                    char * string_buffer(new char[result_item.monthLabel.size() + 1]);

                    std::copy(result_item.monthLabel.begin(), result_item.monthLabel.end(), string_buffer);
                    string_buffer[result_item.monthLabel.size()] = 0;

                    output_item->monthLabel = string_buffer;
                }

                if(result_item.amPmLabel.empty()) {
                    output_item->amPmLabel = nullptr;
                }
                else {
                    char * string_buffer(new char[result_item.amPmLabel.size() + 1]);

                    std::copy(result_item.amPmLabel.begin(), result_item.amPmLabel.end(), string_buffer);
                    string_buffer[result_item.amPmLabel.size()] = 0;

                    output_item->amPmLabel = string_buffer;
                }

                if(result_item.dayOfWeekLabel.empty()) {
                    output_item->dayOfWeekLabel = nullptr;
                }
                else {
                    char * string_buffer(new char[result_item.dayOfWeekLabel.size() + 1]);

                    std::copy(result_item.dayOfWeekLabel.begin(), result_item.dayOfWeekLabel.end(), string_buffer);
                    string_buffer[result_item.dayOfWeekLabel.size()] = 0;

                    output_item->dayOfWeekLabel = string_buffer;
                }

                if(result_item.holidayName.empty()) {
                    output_item->holidayName = nullptr;
                }
                else {
                    char * string_buffer(new char[result_item.holidayName.size() + 1]);

                    std::copy(result_item.holidayName.begin(), result_item.holidayName.end(), string_buffer);
                    string_buffer[result_item.holidayName.size()] = 0;

                    output_item->holidayName = string_buffer;
                }

                output_item->isPaidTimeOff = result_item.isPaidTimeOff;

                ++output_item;
            }
        }

        *output_items = result.size();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_DestroyTransformedData(/*out*/ TimePoint * result, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result == nullptr) throw std::invalid_argument("'result' is null");

        if(result->monthLabel)
            delete [] result->monthLabel;

        if(result->amPmLabel)
            delete [] result->amPmLabel;

        if(result->dayOfWeekLabel)
            delete [] result->dayOfWeekLabel;

        if(result->holidayName)
            delete [] result->holidayName;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}


#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

} // extern "C"
