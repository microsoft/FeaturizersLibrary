/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_SimpleRollingWindowFeaturizer.h"
#include "SharedLibrary_Common.hpp"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "SimpleRollingWindowFeaturizer.h"

// These method(s) are defined in SharedLibrary_Common.cpp
ErrorInfoHandle * CreateErrorInfo(std::exception const &ex);
std::chrono::system_clock::time_point CreateDateTime(DateTimeParameter const &param);

extern "C" {

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
/* |  SimpleRollingWindowFeaturizer <int8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::SimpleRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_int8_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_GetState(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_Fit(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int8_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ int8_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            if(*input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' element is null");
            if(*input0_ptr_items == 0) throw std::invalid_argument("'input0_ptr_items' element is 0");

            std::vector<std::string> this_buffer;

            this_buffer.reserve(*input0_ptr_items);

            char const * const * strings_ptr(*input0_ptrs);

            while(this_buffer.size() < *input0_ptr_items) {
                this_buffer.emplace_back(*strings_ptr);
                ++strings_ptr;
            }

            input0_buffer.emplace_back(std::move(this_buffer));

            ++input0_ptrs;
            ++input0_ptr_items;
        }

        if(input1_ptr == nullptr) throw std::invalid_argument("'input1_ptr' is null");
        if(input1_items == 0) throw std::invalid_argument("'input1_items' is 0");


        if(input1_items != input0_items) throw std::invalid_argument("'input1_items' != 'input0_items'");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::int8_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::int8_t>>::type> input_buffer;

        input_buffer.reserve(input0_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input0_items) {
            input_buffer.emplace_back(*input0_creation_ptr, *input1_creation_ptr);
            ++input0_creation_ptr;
            ++input1_creation_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_Transform(/*in*/ SimpleRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int8_t input1, /*out*/ int8_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input0_buffer, input1)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new int8_t*[result.size()];
        *output_items = result.size();

        int8_t* * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item ? new int8_t(*result_item) : nullptr;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_Flush(/*in*/ SimpleRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*out*/ int8_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int8_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new int8_t* *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        int8_t* ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new int8_t*[result_item.size()];
            *output_item_items = result_item.size();

            int8_t* * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item ? new int8_t(*result_item_item) : nullptr;
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int8_DestroyTransformedData(/*out*/ int8_t const * const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        int8_t const * const * result_ptr_item(result_ptr);

        for(size_t ctr=0; ctr < result_items; ++ctr) {
            int8_t const * result_item(*result_ptr_item);

            if(result_item != nullptr)
                delete result_item;

            ++result_ptr_item;
        }

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
/* |  SimpleRollingWindowFeaturizer <int16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::SimpleRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_int16_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_GetState(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_Fit(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int16_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ int16_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            if(*input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' element is null");
            if(*input0_ptr_items == 0) throw std::invalid_argument("'input0_ptr_items' element is 0");

            std::vector<std::string> this_buffer;

            this_buffer.reserve(*input0_ptr_items);

            char const * const * strings_ptr(*input0_ptrs);

            while(this_buffer.size() < *input0_ptr_items) {
                this_buffer.emplace_back(*strings_ptr);
                ++strings_ptr;
            }

            input0_buffer.emplace_back(std::move(this_buffer));

            ++input0_ptrs;
            ++input0_ptr_items;
        }

        if(input1_ptr == nullptr) throw std::invalid_argument("'input1_ptr' is null");
        if(input1_items == 0) throw std::invalid_argument("'input1_items' is 0");


        if(input1_items != input0_items) throw std::invalid_argument("'input1_items' != 'input0_items'");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::int16_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::int16_t>>::type> input_buffer;

        input_buffer.reserve(input0_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input0_items) {
            input_buffer.emplace_back(*input0_creation_ptr, *input1_creation_ptr);
            ++input0_creation_ptr;
            ++input1_creation_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_Transform(/*in*/ SimpleRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int16_t input1, /*out*/ int16_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input0_buffer, input1)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new int16_t*[result.size()];
        *output_items = result.size();

        int16_t* * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item ? new int16_t(*result_item) : nullptr;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_Flush(/*in*/ SimpleRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*out*/ int16_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int16_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new int16_t* *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        int16_t* ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new int16_t*[result_item.size()];
            *output_item_items = result_item.size();

            int16_t* * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item ? new int16_t(*result_item_item) : nullptr;
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int16_DestroyTransformedData(/*out*/ int16_t const * const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        int16_t const * const * result_ptr_item(result_ptr);

        for(size_t ctr=0; ctr < result_items; ++ctr) {
            int16_t const * result_item(*result_ptr_item);

            if(result_item != nullptr)
                delete result_item;

            ++result_ptr_item;
        }

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
/* |  SimpleRollingWindowFeaturizer <int32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::SimpleRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_int32_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_GetState(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_Fit(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int32_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ int32_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            if(*input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' element is null");
            if(*input0_ptr_items == 0) throw std::invalid_argument("'input0_ptr_items' element is 0");

            std::vector<std::string> this_buffer;

            this_buffer.reserve(*input0_ptr_items);

            char const * const * strings_ptr(*input0_ptrs);

            while(this_buffer.size() < *input0_ptr_items) {
                this_buffer.emplace_back(*strings_ptr);
                ++strings_ptr;
            }

            input0_buffer.emplace_back(std::move(this_buffer));

            ++input0_ptrs;
            ++input0_ptr_items;
        }

        if(input1_ptr == nullptr) throw std::invalid_argument("'input1_ptr' is null");
        if(input1_items == 0) throw std::invalid_argument("'input1_items' is 0");


        if(input1_items != input0_items) throw std::invalid_argument("'input1_items' != 'input0_items'");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::int32_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::int32_t>>::type> input_buffer;

        input_buffer.reserve(input0_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input0_items) {
            input_buffer.emplace_back(*input0_creation_ptr, *input1_creation_ptr);
            ++input0_creation_ptr;
            ++input1_creation_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_Transform(/*in*/ SimpleRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int32_t input1, /*out*/ int32_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input0_buffer, input1)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new int32_t*[result.size()];
        *output_items = result.size();

        int32_t* * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item ? new int32_t(*result_item) : nullptr;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_Flush(/*in*/ SimpleRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*out*/ int32_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int32_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new int32_t* *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        int32_t* ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new int32_t*[result_item.size()];
            *output_item_items = result_item.size();

            int32_t* * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item ? new int32_t(*result_item_item) : nullptr;
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int32_DestroyTransformedData(/*out*/ int32_t const * const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        int32_t const * const * result_ptr_item(result_ptr);

        for(size_t ctr=0; ctr < result_items; ++ctr) {
            int32_t const * result_item(*result_ptr_item);

            if(result_item != nullptr)
                delete result_item;

            ++result_ptr_item;
        }

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
/* |  SimpleRollingWindowFeaturizer <int64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::SimpleRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_int64_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_GetState(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_Fit(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int64_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ int64_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            if(*input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' element is null");
            if(*input0_ptr_items == 0) throw std::invalid_argument("'input0_ptr_items' element is 0");

            std::vector<std::string> this_buffer;

            this_buffer.reserve(*input0_ptr_items);

            char const * const * strings_ptr(*input0_ptrs);

            while(this_buffer.size() < *input0_ptr_items) {
                this_buffer.emplace_back(*strings_ptr);
                ++strings_ptr;
            }

            input0_buffer.emplace_back(std::move(this_buffer));

            ++input0_ptrs;
            ++input0_ptr_items;
        }

        if(input1_ptr == nullptr) throw std::invalid_argument("'input1_ptr' is null");
        if(input1_items == 0) throw std::invalid_argument("'input1_items' is 0");


        if(input1_items != input0_items) throw std::invalid_argument("'input1_items' != 'input0_items'");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::int64_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::int64_t>>::type> input_buffer;

        input_buffer.reserve(input0_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input0_items) {
            input_buffer.emplace_back(*input0_creation_ptr, *input1_creation_ptr);
            ++input0_creation_ptr;
            ++input1_creation_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_Transform(/*in*/ SimpleRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int64_t input1, /*out*/ int64_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input0_buffer, input1)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new int64_t*[result.size()];
        *output_items = result.size();

        int64_t* * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item ? new int64_t(*result_item) : nullptr;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_Flush(/*in*/ SimpleRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*out*/ int64_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::int64_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new int64_t* *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        int64_t* ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new int64_t*[result_item.size()];
            *output_item_items = result_item.size();

            int64_t* * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item ? new int64_t(*result_item_item) : nullptr;
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_int64_DestroyTransformedData(/*out*/ int64_t const * const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        int64_t const * const * result_ptr_item(result_ptr);

        for(size_t ctr=0; ctr < result_items; ++ctr) {
            int64_t const * result_item(*result_ptr_item);

            if(result_item != nullptr)
                delete result_item;

            ++result_ptr_item;
        }

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
/* |  SimpleRollingWindowFeaturizer <uint8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::SimpleRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_uint8_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_GetState(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_Fit(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint8_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ uint8_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            if(*input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' element is null");
            if(*input0_ptr_items == 0) throw std::invalid_argument("'input0_ptr_items' element is 0");

            std::vector<std::string> this_buffer;

            this_buffer.reserve(*input0_ptr_items);

            char const * const * strings_ptr(*input0_ptrs);

            while(this_buffer.size() < *input0_ptr_items) {
                this_buffer.emplace_back(*strings_ptr);
                ++strings_ptr;
            }

            input0_buffer.emplace_back(std::move(this_buffer));

            ++input0_ptrs;
            ++input0_ptr_items;
        }

        if(input1_ptr == nullptr) throw std::invalid_argument("'input1_ptr' is null");
        if(input1_items == 0) throw std::invalid_argument("'input1_items' is 0");


        if(input1_items != input0_items) throw std::invalid_argument("'input1_items' != 'input0_items'");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::uint8_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::uint8_t>>::type> input_buffer;

        input_buffer.reserve(input0_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input0_items) {
            input_buffer.emplace_back(*input0_creation_ptr, *input1_creation_ptr);
            ++input0_creation_ptr;
            ++input1_creation_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_Transform(/*in*/ SimpleRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint8_t input1, /*out*/ uint8_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input0_buffer, input1)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new uint8_t*[result.size()];
        *output_items = result.size();

        uint8_t* * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item ? new uint8_t(*result_item) : nullptr;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_Flush(/*in*/ SimpleRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ uint8_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint8_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new uint8_t* *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        uint8_t* ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new uint8_t*[result_item.size()];
            *output_item_items = result_item.size();

            uint8_t* * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item ? new uint8_t(*result_item_item) : nullptr;
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint8_DestroyTransformedData(/*out*/ uint8_t const * const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        uint8_t const * const * result_ptr_item(result_ptr);

        for(size_t ctr=0; ctr < result_items; ++ctr) {
            uint8_t const * result_item(*result_ptr_item);

            if(result_item != nullptr)
                delete result_item;

            ++result_ptr_item;
        }

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
/* |  SimpleRollingWindowFeaturizer <uint16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::SimpleRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_uint16_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_GetState(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_Fit(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint16_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ uint16_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            if(*input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' element is null");
            if(*input0_ptr_items == 0) throw std::invalid_argument("'input0_ptr_items' element is 0");

            std::vector<std::string> this_buffer;

            this_buffer.reserve(*input0_ptr_items);

            char const * const * strings_ptr(*input0_ptrs);

            while(this_buffer.size() < *input0_ptr_items) {
                this_buffer.emplace_back(*strings_ptr);
                ++strings_ptr;
            }

            input0_buffer.emplace_back(std::move(this_buffer));

            ++input0_ptrs;
            ++input0_ptr_items;
        }

        if(input1_ptr == nullptr) throw std::invalid_argument("'input1_ptr' is null");
        if(input1_items == 0) throw std::invalid_argument("'input1_items' is 0");


        if(input1_items != input0_items) throw std::invalid_argument("'input1_items' != 'input0_items'");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::uint16_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::uint16_t>>::type> input_buffer;

        input_buffer.reserve(input0_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input0_items) {
            input_buffer.emplace_back(*input0_creation_ptr, *input1_creation_ptr);
            ++input0_creation_ptr;
            ++input1_creation_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_Transform(/*in*/ SimpleRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint16_t input1, /*out*/ uint16_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input0_buffer, input1)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new uint16_t*[result.size()];
        *output_items = result.size();

        uint16_t* * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item ? new uint16_t(*result_item) : nullptr;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_Flush(/*in*/ SimpleRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ uint16_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint16_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new uint16_t* *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        uint16_t* ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new uint16_t*[result_item.size()];
            *output_item_items = result_item.size();

            uint16_t* * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item ? new uint16_t(*result_item_item) : nullptr;
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint16_DestroyTransformedData(/*out*/ uint16_t const * const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        uint16_t const * const * result_ptr_item(result_ptr);

        for(size_t ctr=0; ctr < result_items; ++ctr) {
            uint16_t const * result_item(*result_ptr_item);

            if(result_item != nullptr)
                delete result_item;

            ++result_ptr_item;
        }

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
/* |  SimpleRollingWindowFeaturizer <uint32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::SimpleRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_uint32_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_GetState(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_Fit(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint32_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ uint32_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            if(*input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' element is null");
            if(*input0_ptr_items == 0) throw std::invalid_argument("'input0_ptr_items' element is 0");

            std::vector<std::string> this_buffer;

            this_buffer.reserve(*input0_ptr_items);

            char const * const * strings_ptr(*input0_ptrs);

            while(this_buffer.size() < *input0_ptr_items) {
                this_buffer.emplace_back(*strings_ptr);
                ++strings_ptr;
            }

            input0_buffer.emplace_back(std::move(this_buffer));

            ++input0_ptrs;
            ++input0_ptr_items;
        }

        if(input1_ptr == nullptr) throw std::invalid_argument("'input1_ptr' is null");
        if(input1_items == 0) throw std::invalid_argument("'input1_items' is 0");


        if(input1_items != input0_items) throw std::invalid_argument("'input1_items' != 'input0_items'");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::uint32_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::uint32_t>>::type> input_buffer;

        input_buffer.reserve(input0_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input0_items) {
            input_buffer.emplace_back(*input0_creation_ptr, *input1_creation_ptr);
            ++input0_creation_ptr;
            ++input1_creation_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_Transform(/*in*/ SimpleRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint32_t input1, /*out*/ uint32_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input0_buffer, input1)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new uint32_t*[result.size()];
        *output_items = result.size();

        uint32_t* * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item ? new uint32_t(*result_item) : nullptr;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_Flush(/*in*/ SimpleRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ uint32_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint32_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new uint32_t* *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        uint32_t* ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new uint32_t*[result_item.size()];
            *output_item_items = result_item.size();

            uint32_t* * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item ? new uint32_t(*result_item_item) : nullptr;
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint32_DestroyTransformedData(/*out*/ uint32_t const * const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        uint32_t const * const * result_ptr_item(result_ptr);

        for(size_t ctr=0; ctr < result_items; ++ctr) {
            uint32_t const * result_item(*result_ptr_item);

            if(result_item != nullptr)
                delete result_item;

            ++result_ptr_item;
        }

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
/* |  SimpleRollingWindowFeaturizer <uint64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::SimpleRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_uint64_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_GetState(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_Fit(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint64_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ uint64_t const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            if(*input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' element is null");
            if(*input0_ptr_items == 0) throw std::invalid_argument("'input0_ptr_items' element is 0");

            std::vector<std::string> this_buffer;

            this_buffer.reserve(*input0_ptr_items);

            char const * const * strings_ptr(*input0_ptrs);

            while(this_buffer.size() < *input0_ptr_items) {
                this_buffer.emplace_back(*strings_ptr);
                ++strings_ptr;
            }

            input0_buffer.emplace_back(std::move(this_buffer));

            ++input0_ptrs;
            ++input0_ptr_items;
        }

        if(input1_ptr == nullptr) throw std::invalid_argument("'input1_ptr' is null");
        if(input1_items == 0) throw std::invalid_argument("'input1_items' is 0");


        if(input1_items != input0_items) throw std::invalid_argument("'input1_items' != 'input0_items'");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::uint64_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::uint64_t>>::type> input_buffer;

        input_buffer.reserve(input0_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input0_items) {
            input_buffer.emplace_back(*input0_creation_ptr, *input1_creation_ptr);
            ++input0_creation_ptr;
            ++input1_creation_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_Transform(/*in*/ SimpleRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint64_t input1, /*out*/ uint64_t* ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input0_buffer, input1)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new uint64_t*[result.size()];
        *output_items = result.size();

        uint64_t* * output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");
            *output_item = result_item ? new uint64_t(*result_item) : nullptr;
            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_Flush(/*in*/ SimpleRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ uint64_t* *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::uint64_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new uint64_t* *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        uint64_t* ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new uint64_t*[result_item.size()];
            *output_item_items = result_item.size();

            uint64_t* * output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");
                *output_item_item = result_item_item ? new uint64_t(*result_item_item) : nullptr;
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_uint64_DestroyTransformedData(/*out*/ uint64_t const * const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        uint64_t const * const * result_ptr_item(result_ptr);

        for(size_t ctr=0; ctr < result_items; ++ctr) {
            uint64_t const * result_item(*result_ptr_item);

            if(result_item != nullptr)
                delete result_item;

            ++result_ptr_item;
        }

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
/* |  SimpleRollingWindowFeaturizer <float> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::SimpleRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_float_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_GetState(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_Fit(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ float const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            if(*input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' element is null");
            if(*input0_ptr_items == 0) throw std::invalid_argument("'input0_ptr_items' element is 0");

            std::vector<std::string> this_buffer;

            this_buffer.reserve(*input0_ptr_items);

            char const * const * strings_ptr(*input0_ptrs);

            while(this_buffer.size() < *input0_ptr_items) {
                this_buffer.emplace_back(*strings_ptr);
                ++strings_ptr;
            }

            input0_buffer.emplace_back(std::move(this_buffer));

            ++input0_ptrs;
            ++input0_ptr_items;
        }

        if(input1_ptr == nullptr) throw std::invalid_argument("'input1_ptr' is null");
        if(input1_items == 0) throw std::invalid_argument("'input1_items' is 0");


        if(input1_items != input0_items) throw std::invalid_argument("'input1_items' != 'input0_items'");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::float_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::float_t>>::type> input_buffer;

        input_buffer.reserve(input0_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input0_items) {
            input_buffer.emplace_back(*input0_creation_ptr, *input1_creation_ptr);
            ++input0_creation_ptr;
            ++input1_creation_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_Transform(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ float ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input0_buffer, input1)));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new float[result.size()];
        *output_items = result.size();

        float * output_item(*output_item_ptr);

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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_Flush(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ float *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new float *[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        float ** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new float[result_item.size()];
            *output_item_items = result_item.size();

            float * output_item_item(*output_item_item_ptr);

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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_DestroyTransformedData(/*out*/ float const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
/* |  SimpleRollingWindowFeaturizer <double> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::SimpleRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_double_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_GetState(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_Fit(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ double const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            if(*input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' element is null");
            if(*input0_ptr_items == 0) throw std::invalid_argument("'input0_ptr_items' element is 0");

            std::vector<std::string> this_buffer;

            this_buffer.reserve(*input0_ptr_items);

            char const * const * strings_ptr(*input0_ptrs);

            while(this_buffer.size() < *input0_ptr_items) {
                this_buffer.emplace_back(*strings_ptr);
                ++strings_ptr;
            }

            input0_buffer.emplace_back(std::move(this_buffer));

            ++input0_ptrs;
            ++input0_ptr_items;
        }

        if(input1_ptr == nullptr) throw std::invalid_argument("'input1_ptr' is null");
        if(input1_items == 0) throw std::invalid_argument("'input1_items' is 0");


        if(input1_items != input0_items) throw std::invalid_argument("'input1_items' != 'input0_items'");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::double_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::double_t>>::type> input_buffer;

        input_buffer.reserve(input0_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input0_items) {
            input_buffer.emplace_back(*input0_creation_ptr, *input1_creation_ptr);
            ++input0_creation_ptr;
            ++input1_creation_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_Transform(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input0_buffer, input1)));

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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_Flush(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformedType;

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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_DestroyTransformedData(/*out*/ double const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
/* |  SimpleRollingWindowFeaturizer <string> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::SimpleRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_string_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_DestroyEstimator(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_GetState(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_IsTrainingComplete(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_Fit(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ char const * input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }

        if(input1 == nullptr) throw std::invalid_argument("'input1' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input0_buffer, std::string(input1))));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ size_t input0_items, /*in*/ char const * const * input1_ptr, /*in*/ size_t input1_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            if(*input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' element is null");
            if(*input0_ptr_items == 0) throw std::invalid_argument("'input0_ptr_items' element is 0");

            std::vector<std::string> this_buffer;

            this_buffer.reserve(*input0_ptr_items);

            char const * const * strings_ptr(*input0_ptrs);

            while(this_buffer.size() < *input0_ptr_items) {
                this_buffer.emplace_back(*strings_ptr);
                ++strings_ptr;
            }

            input0_buffer.emplace_back(std::move(this_buffer));

            ++input0_ptrs;
            ++input0_ptr_items;
        }

        if(input1_ptr == nullptr) throw std::invalid_argument("'input1_ptr' is null");
        if(input1_items == 0) throw std::invalid_argument("'input1_items' is 0");

        std::vector<std::string> input1_buffer;

        input1_buffer.reserve(input1_items);

        while(input1_buffer.size() < input1_items) {
            input1_buffer.emplace_back(*input1_ptr);
            ++input1_ptr;
        }



        if(input1_items != input0_items) throw std::invalid_argument("'input1_items' != 'input0_items'");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::string

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::string>>::type> input_buffer;

        input_buffer.reserve(input0_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_buffer.data());

        while(input_buffer.size() < input0_items) {
            input_buffer.emplace_back(*input0_creation_ptr, *input1_creation_ptr);
            ++input0_creation_ptr;
            ++input1_creation_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_OnDataCompleted(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_CompleteTraining(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_CreateTransformerFromEstimator(/*in*/ SimpleRollingWindowFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ SimpleRollingWindowFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_string_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ SimpleRollingWindowFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<SimpleRollingWindowFeaturizer_string_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_DestroyTransformer(/*in*/ SimpleRollingWindowFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_CreateTransformerSaveData(/*in*/ SimpleRollingWindowFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_Transform(/*in*/ SimpleRollingWindowFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ char const * input1, /*out*/ char const *** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input0_ptr == nullptr) throw std::invalid_argument("'input0_ptr' is null");
        if(input0_items == 0) throw std::invalid_argument("'input0_items' is 0");

        std::vector<std::string> input0_buffer;

        input0_buffer.reserve(input0_items);

        while(input0_buffer.size() < input0_items) {
            input0_buffer.emplace_back(*input0_ptr);
            ++input0_ptr;
        }

        if(input1 == nullptr) throw std::invalid_argument("'input1' is null");
        if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::make_tuple(input0_buffer, std::string(input1))));

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_ptr = new char const *[result.size()];
        *output_items = result.size();

        char const ** output_item(*output_item_ptr);

        for(auto const & result_item : result) {
            if(output_item == nullptr) throw std::invalid_argument("'output_item' is null");

            if(!result_item) {
                *output_item = nullptr;
            }
            else {
                std::string const & result_item_temp(*result_item);
                char * string_buffer(new char[result_item_temp.size() + 1]);

                std::copy(result_item_temp.begin(), result_item_temp.end(), string_buffer);
                string_buffer[result_item_temp.size()] = 0;

                *output_item = string_buffer;
            }

            ++output_item;
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_Flush(/*in*/ SimpleRollingWindowFeaturizer_string_TransformerHandle *pHandle, /*out*/ char const **** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::string>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_item_ptr_ptr = new char const **[result.size()];
        *output_item_items_ptr = new size_t[result.size()];
        *output_items = result.size();

        char const *** output_item_item_ptr(*output_item_item_ptr_ptr);
        size_t * output_item_items(*output_item_items_ptr);

        for(auto const & result_item : result) {
            if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
            if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr = new char const *[result_item.size()];
            *output_item_items = result_item.size();

            char const ** output_item_item(*output_item_item_ptr);

            for(auto const & result_item_item : result_item) {
                if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");

                if(!result_item_item) {
                    *output_item_item = nullptr;
                }
                else {
                    std::string const & result_item_item_temp(*result_item_item);
                    char * string_buffer(new char[result_item_item_temp.size() + 1]);

                    std::copy(result_item_item_temp.begin(), result_item_item_temp.end(), string_buffer);
                    string_buffer[result_item_item_temp.size()] = 0;

                    *output_item_item = string_buffer;
                }

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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_string_DestroyTransformedData(/*out*/ char const * const * result_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");


        if(result_items == 0)
            return true;

        char const * const * result_ptr_item(result_ptr);

        for(size_t ctr=0; ctr < result_items; ++ctr) {
            char const * result_item(*result_ptr_item);

            if(result_item)
                delete [] result_item;

            ++result_ptr_item;
        }

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
