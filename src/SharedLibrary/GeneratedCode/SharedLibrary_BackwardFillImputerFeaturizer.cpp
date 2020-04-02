/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_BackwardFillImputerFeaturizer.h"
#include "SharedLibrary_Common.hpp"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "BackwardFillImputerFeaturizer.h"

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
/* |  BackwardFillImputerFeaturizer <int8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>* pEstimator = new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<BackwardFillImputerFeaturizer_int8_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_GetState(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_Fit(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::InputType;

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int8_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Microsoft::Featurizer::Traits<std::int8_t>::nullable_type> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int8_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_Transform(/*in*/ BackwardFillImputerFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t const * input, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int8_t>::CreateNullValue(), callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new int8_t[result.size()];

            int8_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_Flush(/*in*/ BackwardFillImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ int8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int8_t>::TransformedType;

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
            *output_item_ptr = new int8_t[result.size()];

            int8_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int8_DestroyTransformedData(/*out*/ int8_t * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_items) != bool(result_item_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_ptr != nullptr) {
            // No destroy statements

            delete [] result_item_ptr;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  BackwardFillImputerFeaturizer <int16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>* pEstimator = new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<BackwardFillImputerFeaturizer_int16_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_GetState(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_Fit(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::InputType;

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int16_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Microsoft::Featurizer::Traits<std::int16_t>::nullable_type> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int16_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_Transform(/*in*/ BackwardFillImputerFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t const * input, /*out*/ int16_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int16_t>::CreateNullValue(), callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new int16_t[result.size()];

            int16_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_Flush(/*in*/ BackwardFillImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ int16_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int16_t>::TransformedType;

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
            *output_item_ptr = new int16_t[result.size()];

            int16_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int16_DestroyTransformedData(/*out*/ int16_t * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_items) != bool(result_item_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_ptr != nullptr) {
            // No destroy statements

            delete [] result_item_ptr;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  BackwardFillImputerFeaturizer <int32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>* pEstimator = new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<BackwardFillImputerFeaturizer_int32_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_GetState(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_Fit(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::InputType;

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int32_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Microsoft::Featurizer::Traits<std::int32_t>::nullable_type> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int32_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_Transform(/*in*/ BackwardFillImputerFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t const * input, /*out*/ int32_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int32_t>::CreateNullValue(), callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new int32_t[result.size()];

            int32_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_Flush(/*in*/ BackwardFillImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ int32_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int32_t>::TransformedType;

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
            *output_item_ptr = new int32_t[result.size()];

            int32_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int32_DestroyTransformedData(/*out*/ int32_t * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_items) != bool(result_item_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_ptr != nullptr) {
            // No destroy statements

            delete [] result_item_ptr;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  BackwardFillImputerFeaturizer <int64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>* pEstimator = new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<BackwardFillImputerFeaturizer_int64_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_GetState(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_Fit(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::InputType;

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int64_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Microsoft::Featurizer::Traits<std::int64_t>::nullable_type> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int64_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_Transform(/*in*/ BackwardFillImputerFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t const * input, /*out*/ int64_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int64_t>::CreateNullValue(), callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new int64_t[result.size()];

            int64_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_Flush(/*in*/ BackwardFillImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ int64_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::int64_t>::TransformedType;

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
            *output_item_ptr = new int64_t[result.size()];

            int64_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_int64_DestroyTransformedData(/*out*/ int64_t * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_items) != bool(result_item_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_ptr != nullptr) {
            // No destroy statements

            delete [] result_item_ptr;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  BackwardFillImputerFeaturizer <uint8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>* pEstimator = new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<BackwardFillImputerFeaturizer_uint8_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_GetState(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_Fit(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::InputType;

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint8_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint8_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_Transform(/*in*/ BackwardFillImputerFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ uint8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint8_t>::CreateNullValue(), callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new uint8_t[result.size()];

            uint8_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_Flush(/*in*/ BackwardFillImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ uint8_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint8_t>::TransformedType;

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
            *output_item_ptr = new uint8_t[result.size()];

            uint8_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint8_DestroyTransformedData(/*out*/ uint8_t * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_items) != bool(result_item_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_ptr != nullptr) {
            // No destroy statements

            delete [] result_item_ptr;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  BackwardFillImputerFeaturizer <uint16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>* pEstimator = new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<BackwardFillImputerFeaturizer_uint16_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_GetState(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_Fit(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::InputType;

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint16_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint16_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_Transform(/*in*/ BackwardFillImputerFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ uint16_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint16_t>::CreateNullValue(), callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new uint16_t[result.size()];

            uint16_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_Flush(/*in*/ BackwardFillImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ uint16_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint16_t>::TransformedType;

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
            *output_item_ptr = new uint16_t[result.size()];

            uint16_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint16_DestroyTransformedData(/*out*/ uint16_t * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_items) != bool(result_item_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_ptr != nullptr) {
            // No destroy statements

            delete [] result_item_ptr;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  BackwardFillImputerFeaturizer <uint32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>* pEstimator = new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<BackwardFillImputerFeaturizer_uint32_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_GetState(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_Fit(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::InputType;

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint32_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint32_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_Transform(/*in*/ BackwardFillImputerFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ uint32_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint32_t>::CreateNullValue(), callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new uint32_t[result.size()];

            uint32_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_Flush(/*in*/ BackwardFillImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ uint32_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint32_t>::TransformedType;

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
            *output_item_ptr = new uint32_t[result.size()];

            uint32_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint32_DestroyTransformedData(/*out*/ uint32_t * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_items) != bool(result_item_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_ptr != nullptr) {
            // No destroy statements

            delete [] result_item_ptr;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  BackwardFillImputerFeaturizer <uint64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>* pEstimator = new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<BackwardFillImputerFeaturizer_uint64_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_GetState(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_Fit(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::InputType;

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint64_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint64_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_Transform(/*in*/ BackwardFillImputerFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ uint64_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint64_t>::CreateNullValue(), callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new uint64_t[result.size()];

            uint64_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_Flush(/*in*/ BackwardFillImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::uint64_t>::TransformedType;

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
            *output_item_ptr = new uint64_t[result.size()];

            uint64_t * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_uint64_DestroyTransformedData(/*out*/ uint64_t * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_items) != bool(result_item_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_ptr != nullptr) {
            // No destroy statements

            delete [] result_item_ptr;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  BackwardFillImputerFeaturizer <float> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<BackwardFillImputerFeaturizer_float_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_GetState(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_Fit(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::InputType;

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_Transform(/*in*/ BackwardFillImputerFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(input, callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new float[result.size()];

            float * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_Flush(/*in*/ BackwardFillImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::float_t>::TransformedType;

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
            *output_item_ptr = new float[result.size()];

            float * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_float_DestroyTransformedData(/*out*/ float * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_items) != bool(result_item_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_ptr != nullptr) {
            // No destroy statements

            delete [] result_item_ptr;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  BackwardFillImputerFeaturizer <double> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<BackwardFillImputerFeaturizer_double_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_GetState(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_Fit(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::InputType;

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_Transform(/*in*/ BackwardFillImputerFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(input, callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new double[result.size()];

            double * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_Flush(/*in*/ BackwardFillImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::double_t>::TransformedType;

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
            *output_item_ptr = new double[result.size()];

            double * output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_double_DestroyTransformedData(/*out*/ double * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_items) != bool(result_item_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_ptr != nullptr) {
            // No destroy statements

            delete [] result_item_ptr;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  BackwardFillImputerFeaturizer <bool> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>* pEstimator = new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<BackwardFillImputerFeaturizer_bool_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_GetState(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_Fit(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::InputType;

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<bool>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Microsoft::Featurizer::Traits<bool>::nullable_type> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<bool>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_bool_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_bool_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_Transform(/*in*/ BackwardFillImputerFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool const * input, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.push_back(std::move(value));
            }
        );

        transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<bool>::CreateNullValue(), callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new bool[result.size()];

            bool * output_item(*output_item_ptr);

            for(bool result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_Flush(/*in*/ BackwardFillImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ bool ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<bool>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.push_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new bool[result.size()];

            bool * output_item(*output_item_ptr);

            for(bool result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                *output_item = result_item;

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_bool_DestroyTransformedData(/*out*/ bool * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_items) != bool(result_item_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_ptr != nullptr) {
            // No destroy statements

            delete [] result_item_ptr;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  BackwardFillImputerFeaturizer <string> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_CreateEstimator(/*out*/ BackwardFillImputerFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>* pEstimator = new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<BackwardFillImputerFeaturizer_string_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_DestroyEstimator(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_GetState(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_IsTrainingComplete(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_Fit(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::InputType;

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input ? std::string(input) : nonstd::optional<std::string>()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_FitBuffer(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<nonstd::optional<std::string>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            input_buffer.emplace_back(*input_ptr ? *input_ptr : nonstd::optional<std::string>());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_OnDataCompleted(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_CompleteTraining(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_CreateTransformerFromEstimator(/*in*/ BackwardFillImputerFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ BackwardFillImputerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_string_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ BackwardFillImputerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<BackwardFillImputerFeaturizer_string_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_DestroyTransformer(/*in*/ BackwardFillImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_CreateTransformerSaveData(/*in*/ BackwardFillImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_Transform(/*in*/ BackwardFillImputerFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const * input, /*out*/ char const *** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(input ? std::string(input) : nonstd::optional<std::string>(), callback);

        // Output
        if(result.empty()) {
            *output_item_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_ptr = new char const *[result.size()];

            char const ** output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                if(result_item.empty()) {
                    *output_item = nullptr;
                }
                else {
                    char * string_buffer(new char[result_item.size() + 1]);

                    std::copy(result_item.begin(), result_item.end(), string_buffer);
                    string_buffer[result_item.size()] = 0;

                    *output_item = string_buffer;
                }

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_Flush(/*in*/ BackwardFillImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ char const *** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::BackwardFillImputerEstimator<std::string>::TransformedType;

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
            *output_item_ptr = new char const *[result.size()];

            char const ** output_item(*output_item_ptr);

            for(auto const & result_item : result) {
                if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

                if(result_item.empty()) {
                    *output_item = nullptr;
                }
                else {
                    char * string_buffer(new char[result_item.size() + 1]);

                    std::copy(result_item.begin(), result_item.end(), string_buffer);
                    string_buffer[result_item.size()] = 0;

                    *output_item = string_buffer;
                }

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

FEATURIZER_LIBRARY_API bool BackwardFillImputerFeaturizer_string_DestroyTransformedData(/*out*/ char const ** result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_items) != bool(result_item_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_ptr != nullptr) {
            char const ** this_result_item_ptr(result_item_ptr);

            while(result_items--) {
                char const * const & result_destroy_item(*this_result_item_ptr);

                // No validation statements

                if(result_destroy_item)
                    delete [] result_destroy_item;

                ++this_result_item_ptr;
            }

            delete [] result_item_ptr;
        }
    
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
