/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_L1NormalizeFeaturizer.h"
#include "SharedLibrary_Common.hpp"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "L1NormalizeFeaturizer.h"

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
/* |  L1NormalizeFeaturizer <int8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_CreateEstimator(/*out*/ L1NormalizeFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>* pEstimator = new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<L1NormalizeFeaturizer_int8_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_GetState(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_Fit(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input_ptr, input_ptr + input_items)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_FitBuffer(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_item_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_ptr_ptr' is null");
        if(input_item_items_ptr == nullptr) throw std::invalid_argument("'input_item_items_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::tuple<int8_t const *, int8_t const *>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            int8_t const * const &input_item_ptr(*input_item_ptr_ptr);
            size_t const &input_item_items(*input_item_items_ptr);

            if(input_item_ptr == nullptr) throw std::invalid_argument("'input_item_ptr' is null");
            if(input_item_items == 0) throw std::invalid_argument("'input_item_items' is 0");
            

            input_buffer.emplace_back(input_item_ptr, input_item_ptr + input_item_items);

            ++input_item_ptr_ptr;
            ++input_item_items_ptr;
        }

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_CompleteTraining(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_Transform(/*in*/ L1NormalizeFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input_ptr, input_ptr + input_items)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new double[result.size()];
        *output_items = result.size();

        double * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_Flush(/*in*/ L1NormalizeFeaturizer_int8_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int8_t const *, std::int8_t const *>>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new double *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        double ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new double[result_item.size()];
            *output_item_items = result_item.size();

            double * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item;
                ++output_item_item;
            }

            ++output_item_item_ptr;
            ++output_item_items;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int8_DestroyTransformedData(/*out*/ double const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        delete [] result_ptr;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  L1NormalizeFeaturizer <int16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_CreateEstimator(/*out*/ L1NormalizeFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>* pEstimator = new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<L1NormalizeFeaturizer_int16_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_GetState(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_Fit(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input_ptr, input_ptr + input_items)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_FitBuffer(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_item_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_ptr_ptr' is null");
        if(input_item_items_ptr == nullptr) throw std::invalid_argument("'input_item_items_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::tuple<int16_t const *, int16_t const *>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            int16_t const * const &input_item_ptr(*input_item_ptr_ptr);
            size_t const &input_item_items(*input_item_items_ptr);

            if(input_item_ptr == nullptr) throw std::invalid_argument("'input_item_ptr' is null");
            if(input_item_items == 0) throw std::invalid_argument("'input_item_items' is 0");
            

            input_buffer.emplace_back(input_item_ptr, input_item_ptr + input_item_items);

            ++input_item_ptr_ptr;
            ++input_item_items_ptr;
        }

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_CompleteTraining(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_Transform(/*in*/ L1NormalizeFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input_ptr, input_ptr + input_items)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new double[result.size()];
        *output_items = result.size();

        double * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_Flush(/*in*/ L1NormalizeFeaturizer_int16_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int16_t const *, std::int16_t const *>>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new double *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        double ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new double[result_item.size()];
            *output_item_items = result_item.size();

            double * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item;
                ++output_item_item;
            }

            ++output_item_item_ptr;
            ++output_item_items;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int16_DestroyTransformedData(/*out*/ double const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        delete [] result_ptr;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  L1NormalizeFeaturizer <int32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_CreateEstimator(/*out*/ L1NormalizeFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>* pEstimator = new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<L1NormalizeFeaturizer_int32_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_GetState(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_Fit(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input_ptr, input_ptr + input_items)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_FitBuffer(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_item_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_ptr_ptr' is null");
        if(input_item_items_ptr == nullptr) throw std::invalid_argument("'input_item_items_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::tuple<int32_t const *, int32_t const *>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            int32_t const * const &input_item_ptr(*input_item_ptr_ptr);
            size_t const &input_item_items(*input_item_items_ptr);

            if(input_item_ptr == nullptr) throw std::invalid_argument("'input_item_ptr' is null");
            if(input_item_items == 0) throw std::invalid_argument("'input_item_items' is 0");
            

            input_buffer.emplace_back(input_item_ptr, input_item_ptr + input_item_items);

            ++input_item_ptr_ptr;
            ++input_item_items_ptr;
        }

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_CompleteTraining(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_Transform(/*in*/ L1NormalizeFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input_ptr, input_ptr + input_items)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new double[result.size()];
        *output_items = result.size();

        double * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_Flush(/*in*/ L1NormalizeFeaturizer_int32_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int32_t const *, std::int32_t const *>>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new double *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        double ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new double[result_item.size()];
            *output_item_items = result_item.size();

            double * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item;
                ++output_item_item;
            }

            ++output_item_item_ptr;
            ++output_item_items;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int32_DestroyTransformedData(/*out*/ double const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        delete [] result_ptr;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  L1NormalizeFeaturizer <int64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_CreateEstimator(/*out*/ L1NormalizeFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>* pEstimator = new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<L1NormalizeFeaturizer_int64_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_GetState(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_Fit(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input_ptr, input_ptr + input_items)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_FitBuffer(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_item_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_ptr_ptr' is null");
        if(input_item_items_ptr == nullptr) throw std::invalid_argument("'input_item_items_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::tuple<int64_t const *, int64_t const *>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            int64_t const * const &input_item_ptr(*input_item_ptr_ptr);
            size_t const &input_item_items(*input_item_items_ptr);

            if(input_item_ptr == nullptr) throw std::invalid_argument("'input_item_ptr' is null");
            if(input_item_items == 0) throw std::invalid_argument("'input_item_items' is 0");
            

            input_buffer.emplace_back(input_item_ptr, input_item_ptr + input_item_items);

            ++input_item_ptr_ptr;
            ++input_item_items_ptr;
        }

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_CompleteTraining(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_Transform(/*in*/ L1NormalizeFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input_ptr, input_ptr + input_items)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new double[result.size()];
        *output_items = result.size();

        double * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_Flush(/*in*/ L1NormalizeFeaturizer_int64_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::int64_t const *, std::int64_t const *>>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new double *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        double ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new double[result_item.size()];
            *output_item_items = result_item.size();

            double * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item;
                ++output_item_item;
            }

            ++output_item_item_ptr;
            ++output_item_items;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_int64_DestroyTransformedData(/*out*/ double const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        delete [] result_ptr;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  L1NormalizeFeaturizer <uint8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_CreateEstimator(/*out*/ L1NormalizeFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>* pEstimator = new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<L1NormalizeFeaturizer_uint8_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_GetState(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_Fit(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input_ptr, input_ptr + input_items)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_FitBuffer(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_item_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_ptr_ptr' is null");
        if(input_item_items_ptr == nullptr) throw std::invalid_argument("'input_item_items_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::tuple<uint8_t const *, uint8_t const *>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            uint8_t const * const &input_item_ptr(*input_item_ptr_ptr);
            size_t const &input_item_items(*input_item_items_ptr);

            if(input_item_ptr == nullptr) throw std::invalid_argument("'input_item_ptr' is null");
            if(input_item_items == 0) throw std::invalid_argument("'input_item_items' is 0");
            

            input_buffer.emplace_back(input_item_ptr, input_item_ptr + input_item_items);

            ++input_item_ptr_ptr;
            ++input_item_items_ptr;
        }

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_CompleteTraining(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_Transform(/*in*/ L1NormalizeFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input_ptr, input_ptr + input_items)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new double[result.size()];
        *output_items = result.size();

        double * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_Flush(/*in*/ L1NormalizeFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint8_t const *, std::uint8_t const *>>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new double *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        double ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new double[result_item.size()];
            *output_item_items = result_item.size();

            double * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item;
                ++output_item_item;
            }

            ++output_item_item_ptr;
            ++output_item_items;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint8_DestroyTransformedData(/*out*/ double const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        delete [] result_ptr;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  L1NormalizeFeaturizer <uint16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_CreateEstimator(/*out*/ L1NormalizeFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>* pEstimator = new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<L1NormalizeFeaturizer_uint16_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_GetState(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_Fit(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input_ptr, input_ptr + input_items)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_FitBuffer(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_item_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_ptr_ptr' is null");
        if(input_item_items_ptr == nullptr) throw std::invalid_argument("'input_item_items_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::tuple<uint16_t const *, uint16_t const *>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            uint16_t const * const &input_item_ptr(*input_item_ptr_ptr);
            size_t const &input_item_items(*input_item_items_ptr);

            if(input_item_ptr == nullptr) throw std::invalid_argument("'input_item_ptr' is null");
            if(input_item_items == 0) throw std::invalid_argument("'input_item_items' is 0");
            

            input_buffer.emplace_back(input_item_ptr, input_item_ptr + input_item_items);

            ++input_item_ptr_ptr;
            ++input_item_items_ptr;
        }

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_CompleteTraining(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_Transform(/*in*/ L1NormalizeFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input_ptr, input_ptr + input_items)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new double[result.size()];
        *output_items = result.size();

        double * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_Flush(/*in*/ L1NormalizeFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint16_t const *, std::uint16_t const *>>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new double *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        double ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new double[result_item.size()];
            *output_item_items = result_item.size();

            double * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item;
                ++output_item_item;
            }

            ++output_item_item_ptr;
            ++output_item_items;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint16_DestroyTransformedData(/*out*/ double const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        delete [] result_ptr;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  L1NormalizeFeaturizer <uint32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_CreateEstimator(/*out*/ L1NormalizeFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>* pEstimator = new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<L1NormalizeFeaturizer_uint32_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_GetState(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_Fit(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input_ptr, input_ptr + input_items)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_FitBuffer(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_item_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_ptr_ptr' is null");
        if(input_item_items_ptr == nullptr) throw std::invalid_argument("'input_item_items_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::tuple<uint32_t const *, uint32_t const *>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            uint32_t const * const &input_item_ptr(*input_item_ptr_ptr);
            size_t const &input_item_items(*input_item_items_ptr);

            if(input_item_ptr == nullptr) throw std::invalid_argument("'input_item_ptr' is null");
            if(input_item_items == 0) throw std::invalid_argument("'input_item_items' is 0");
            

            input_buffer.emplace_back(input_item_ptr, input_item_ptr + input_item_items);

            ++input_item_ptr_ptr;
            ++input_item_items_ptr;
        }

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_CompleteTraining(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_Transform(/*in*/ L1NormalizeFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input_ptr, input_ptr + input_items)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new double[result.size()];
        *output_items = result.size();

        double * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_Flush(/*in*/ L1NormalizeFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint32_t const *, std::uint32_t const *>>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new double *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        double ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new double[result_item.size()];
            *output_item_items = result_item.size();

            double * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item;
                ++output_item_item;
            }

            ++output_item_item_ptr;
            ++output_item_items;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint32_DestroyTransformedData(/*out*/ double const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        delete [] result_ptr;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  L1NormalizeFeaturizer <uint64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_CreateEstimator(/*out*/ L1NormalizeFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>* pEstimator = new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<L1NormalizeFeaturizer_uint64_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_GetState(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_Fit(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input_ptr, input_ptr + input_items)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_FitBuffer(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_item_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_ptr_ptr' is null");
        if(input_item_items_ptr == nullptr) throw std::invalid_argument("'input_item_items_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::tuple<uint64_t const *, uint64_t const *>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            uint64_t const * const &input_item_ptr(*input_item_ptr_ptr);
            size_t const &input_item_items(*input_item_items_ptr);

            if(input_item_ptr == nullptr) throw std::invalid_argument("'input_item_ptr' is null");
            if(input_item_items == 0) throw std::invalid_argument("'input_item_items' is 0");
            

            input_buffer.emplace_back(input_item_ptr, input_item_ptr + input_item_items);

            ++input_item_ptr_ptr;
            ++input_item_items_ptr;
        }

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_CompleteTraining(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_Transform(/*in*/ L1NormalizeFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input_ptr, input_ptr + input_items)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new double[result.size()];
        *output_items = result.size();

        double * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_Flush(/*in*/ L1NormalizeFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::uint64_t const *, std::uint64_t const *>>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new double *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        double ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new double[result_item.size()];
            *output_item_items = result_item.size();

            double * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item;
                ++output_item_item;
            }

            ++output_item_item_ptr;
            ++output_item_items;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_uint64_DestroyTransformedData(/*out*/ double const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        delete [] result_ptr;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  L1NormalizeFeaturizer <float> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_CreateEstimator(/*out*/ L1NormalizeFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>* pEstimator = new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<L1NormalizeFeaturizer_float_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_GetState(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_Fit(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input_ptr, input_ptr + input_items)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_FitBuffer(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_item_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_ptr_ptr' is null");
        if(input_item_items_ptr == nullptr) throw std::invalid_argument("'input_item_items_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::tuple<float const *, float const *>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            float const * const &input_item_ptr(*input_item_ptr_ptr);
            size_t const &input_item_items(*input_item_items_ptr);

            if(input_item_ptr == nullptr) throw std::invalid_argument("'input_item_ptr' is null");
            if(input_item_items == 0) throw std::invalid_argument("'input_item_items' is 0");
            

            input_buffer.emplace_back(input_item_ptr, input_item_ptr + input_item_items);

            ++input_item_ptr_ptr;
            ++input_item_items_ptr;
        }

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_CompleteTraining(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_Transform(/*in*/ L1NormalizeFeaturizer_float_TransformerHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input_ptr, input_ptr + input_items)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new double[result.size()];
        *output_items = result.size();

        double * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_Flush(/*in*/ L1NormalizeFeaturizer_float_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::float_t const *, std::float_t const *>>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new double *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        double ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new double[result_item.size()];
            *output_item_items = result_item.size();

            double * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item;
                ++output_item_item;
            }

            ++output_item_item_ptr;
            ++output_item_items;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_float_DestroyTransformedData(/*out*/ double const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        delete [] result_ptr;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  L1NormalizeFeaturizer <double> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_CreateEstimator(/*out*/ L1NormalizeFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>* pEstimator = new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<L1NormalizeFeaturizer_double_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_DestroyEstimator(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_GetState(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_IsTrainingComplete(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_Fit(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input_ptr, input_ptr + input_items)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_FitBuffer(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * const * input_item_ptr_ptr, /*in*/ size_t const * input_item_items_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_item_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_ptr_ptr' is null");
        if(input_item_items_ptr == nullptr) throw std::invalid_argument("'input_item_items_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::tuple<double const *, double const *>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            double const * const &input_item_ptr(*input_item_ptr_ptr);
            size_t const &input_item_items(*input_item_items_ptr);

            if(input_item_ptr == nullptr) throw std::invalid_argument("'input_item_ptr' is null");
            if(input_item_items == 0) throw std::invalid_argument("'input_item_items' is 0");
            

            input_buffer.emplace_back(input_item_ptr, input_item_ptr + input_item_items);

            ++input_item_ptr_ptr;
            ++input_item_items_ptr;
        }

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_OnDataCompleted(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_CompleteTraining(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_CreateTransformerFromEstimator(/*in*/ L1NormalizeFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ L1NormalizeFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ L1NormalizeFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<L1NormalizeFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_DestroyTransformer(/*in*/ L1NormalizeFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_CreateTransformerSaveData(/*in*/ L1NormalizeFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_Transform(/*in*/ L1NormalizeFeaturizer_double_TransformerHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ size_t input_items, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input_ptr, input_ptr + input_items)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new double[result.size()];
        *output_items = result.size();

        double * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_Flush(/*in*/ L1NormalizeFeaturizer_double_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::L1NormalizeEstimator<std::tuple<std::double_t const *, std::double_t const *>>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new double *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        double ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new double[result_item.size()];
            *output_item_items = result_item.size();

            double * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item;
                ++output_item_item;
            }

            ++output_item_item_ptr;
            ++output_item_items;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool L1NormalizeFeaturizer_double_DestroyTransformedData(/*out*/ double const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        delete [] result_ptr;
    
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
