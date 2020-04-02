/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_MaxAbsScalerFeaturizer.h"
#include "SharedLibrary_Common.hpp"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "MaxAbsScalerFeaturizer.h"

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
/* |  MaxAbsScalerFeaturizer <int8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxAbsScalerFeaturizer_int8_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_GetState(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_Fit(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::InputType;

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_Transform(/*in*/ MaxAbsScalerFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(input));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int8_Flush(/*in*/ MaxAbsScalerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int8_t, std::float_t>::TransformedType;

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

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  MaxAbsScalerFeaturizer <int16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxAbsScalerFeaturizer_int16_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_GetState(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_Fit(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::InputType;

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_Transform(/*in*/ MaxAbsScalerFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(input));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int16_Flush(/*in*/ MaxAbsScalerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int16_t, std::float_t>::TransformedType;

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

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  MaxAbsScalerFeaturizer <uint8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxAbsScalerFeaturizer_uint8_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_GetState(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_Fit(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::InputType;

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_Transform(/*in*/ MaxAbsScalerFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(input));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint8_Flush(/*in*/ MaxAbsScalerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint8_t, std::float_t>::TransformedType;

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

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  MaxAbsScalerFeaturizer <uint16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxAbsScalerFeaturizer_uint16_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_GetState(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_Fit(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::InputType;

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_Transform(/*in*/ MaxAbsScalerFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(input));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint16_Flush(/*in*/ MaxAbsScalerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint16_t, std::float_t>::TransformedType;

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

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  MaxAbsScalerFeaturizer <float> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxAbsScalerFeaturizer_float_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_GetState(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_Fit(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::InputType;

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_Transform(/*in*/ MaxAbsScalerFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(input));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_float_Flush(/*in*/ MaxAbsScalerFeaturizer_float_TransformerHandle *pHandle, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::float_t, std::float_t>::TransformedType;

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

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  MaxAbsScalerFeaturizer <int32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxAbsScalerFeaturizer_int32_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_GetState(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_Fit(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::InputType;

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_Transform(/*in*/ MaxAbsScalerFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(input));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int32_Flush(/*in*/ MaxAbsScalerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int32_t, std::double_t>::TransformedType;

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

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  MaxAbsScalerFeaturizer <int64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxAbsScalerFeaturizer_int64_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_GetState(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_Fit(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::InputType;

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_Transform(/*in*/ MaxAbsScalerFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(input));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_int64_Flush(/*in*/ MaxAbsScalerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::int64_t, std::double_t>::TransformedType;

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

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  MaxAbsScalerFeaturizer <uint32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxAbsScalerFeaturizer_uint32_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_GetState(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_Fit(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::InputType;

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_Transform(/*in*/ MaxAbsScalerFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(input));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint32_Flush(/*in*/ MaxAbsScalerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint32_t, std::double_t>::TransformedType;

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

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  MaxAbsScalerFeaturizer <uint64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxAbsScalerFeaturizer_uint64_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_GetState(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_Fit(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::InputType;

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_Transform(/*in*/ MaxAbsScalerFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(input));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_uint64_Flush(/*in*/ MaxAbsScalerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::uint64_t, std::double_t>::TransformedType;

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

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  MaxAbsScalerFeaturizer <double> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_CreateEstimator(/*out*/ MaxAbsScalerFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxAbsScalerFeaturizer_double_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_DestroyEstimator(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_GetState(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_IsTrainingComplete(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_Fit(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // No validation

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::InputType;

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_FitBuffer(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_OnDataCompleted(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_CompleteTraining(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_CreateTransformerFromEstimator(/*in*/ MaxAbsScalerFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ MaxAbsScalerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ MaxAbsScalerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxAbsScalerFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_DestroyTransformer(/*in*/ MaxAbsScalerFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_CreateTransformerSaveData(/*in*/ MaxAbsScalerFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_Transform(/*in*/ MaxAbsScalerFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(input));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxAbsScalerFeaturizer_double_Flush(/*in*/ MaxAbsScalerFeaturizer_double_TransformerHandle *pHandle, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::MaxAbsScalerEstimator<std::double_t, std::double_t>::TransformedType;

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


#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

} // extern "C"
