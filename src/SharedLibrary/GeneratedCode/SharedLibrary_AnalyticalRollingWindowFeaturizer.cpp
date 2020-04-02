/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_AnalyticalRollingWindowFeaturizer.h"
#include "SharedLibrary_Common.hpp"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "AnalyticalRollingWindowFeaturizer.h"

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
/* |  AnalyticalRollingWindowFeaturizer <int8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::AnalyticalRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int8_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ int8_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input_items);

        while(input0_buffer.size() < input_items) {
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
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::int8_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::int8_t>>::type> input_buffer;

        input_buffer.reserve(input_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input_items) {
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int8_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(InputType(input0_buffer, input1)));

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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_int8_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int8_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item_item_ptr_ptr = nullptr;
            *output_item_items_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr_ptr = new double *[result.size()];
            *output_item_items_ptr = new size_t[result.size()];

            double ** output_item_item_ptr(*output_item_item_ptr_ptr);
            size_t * output_item_items(*output_item_items_ptr);

            for(auto const & result_item : result) {
                if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
                if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

                if(result_item.empty()) {
                    *output_item_item_ptr = nullptr;
                }
                else {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item_item_ptr = new double[result_item.size()];

                    double * output_item_item(*output_item_item_ptr);

                    for(auto const & result_item_item : result_item) {
                        if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");

                        *output_item_item = result_item_item;

                        ++output_item_item;
                    }
                }

                *output_item_items = result_item.size();

                ++output_item_item_ptr;
                ++output_item_items;
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int8_DestroyTransformedData(/*out*/ double * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
/* |  AnalyticalRollingWindowFeaturizer <int16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::AnalyticalRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int16_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ int16_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input_items);

        while(input0_buffer.size() < input_items) {
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
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::int16_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::int16_t>>::type> input_buffer;

        input_buffer.reserve(input_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input_items) {
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int16_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(InputType(input0_buffer, input1)));

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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_int16_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int16_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item_item_ptr_ptr = nullptr;
            *output_item_items_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr_ptr = new double *[result.size()];
            *output_item_items_ptr = new size_t[result.size()];

            double ** output_item_item_ptr(*output_item_item_ptr_ptr);
            size_t * output_item_items(*output_item_items_ptr);

            for(auto const & result_item : result) {
                if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
                if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

                if(result_item.empty()) {
                    *output_item_item_ptr = nullptr;
                }
                else {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item_item_ptr = new double[result_item.size()];

                    double * output_item_item(*output_item_item_ptr);

                    for(auto const & result_item_item : result_item) {
                        if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");

                        *output_item_item = result_item_item;

                        ++output_item_item;
                    }
                }

                *output_item_items = result_item.size();

                ++output_item_item_ptr;
                ++output_item_items;
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int16_DestroyTransformedData(/*out*/ double * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
/* |  AnalyticalRollingWindowFeaturizer <int32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::AnalyticalRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int32_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ int32_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input_items);

        while(input0_buffer.size() < input_items) {
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
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::int32_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::int32_t>>::type> input_buffer;

        input_buffer.reserve(input_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input_items) {
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int32_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(InputType(input0_buffer, input1)));

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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_int32_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item_item_ptr_ptr = nullptr;
            *output_item_items_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr_ptr = new double *[result.size()];
            *output_item_items_ptr = new size_t[result.size()];

            double ** output_item_item_ptr(*output_item_item_ptr_ptr);
            size_t * output_item_items(*output_item_items_ptr);

            for(auto const & result_item : result) {
                if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
                if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

                if(result_item.empty()) {
                    *output_item_item_ptr = nullptr;
                }
                else {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item_item_ptr = new double[result_item.size()];

                    double * output_item_item(*output_item_item_ptr);

                    for(auto const & result_item_item : result_item) {
                        if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");

                        *output_item_item = result_item_item;

                        ++output_item_item;
                    }
                }

                *output_item_items = result_item.size();

                ++output_item_item_ptr;
                ++output_item_items;
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int32_DestroyTransformedData(/*out*/ double * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
/* |  AnalyticalRollingWindowFeaturizer <int64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::AnalyticalRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int64_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ int64_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input_items);

        while(input0_buffer.size() < input_items) {
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
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::int64_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::int64_t>>::type> input_buffer;

        input_buffer.reserve(input_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input_items) {
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ int64_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(InputType(input0_buffer, input1)));

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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_int64_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int64_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item_item_ptr_ptr = nullptr;
            *output_item_items_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr_ptr = new double *[result.size()];
            *output_item_items_ptr = new size_t[result.size()];

            double ** output_item_item_ptr(*output_item_item_ptr_ptr);
            size_t * output_item_items(*output_item_items_ptr);

            for(auto const & result_item : result) {
                if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
                if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

                if(result_item.empty()) {
                    *output_item_item_ptr = nullptr;
                }
                else {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item_item_ptr = new double[result_item.size()];

                    double * output_item_item(*output_item_item_ptr);

                    for(auto const & result_item_item : result_item) {
                        if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");

                        *output_item_item = result_item_item;

                        ++output_item_item;
                    }
                }

                *output_item_items = result_item.size();

                ++output_item_item_ptr;
                ++output_item_items;
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_int64_DestroyTransformedData(/*out*/ double * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
/* |  AnalyticalRollingWindowFeaturizer <uint8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::AnalyticalRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint8_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ uint8_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input_items);

        while(input0_buffer.size() < input_items) {
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
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::uint8_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::uint8_t>>::type> input_buffer;

        input_buffer.reserve(input_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input_items) {
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint8_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(InputType(input0_buffer, input1)));

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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint8_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item_item_ptr_ptr = nullptr;
            *output_item_items_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr_ptr = new double *[result.size()];
            *output_item_items_ptr = new size_t[result.size()];

            double ** output_item_item_ptr(*output_item_item_ptr_ptr);
            size_t * output_item_items(*output_item_items_ptr);

            for(auto const & result_item : result) {
                if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
                if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

                if(result_item.empty()) {
                    *output_item_item_ptr = nullptr;
                }
                else {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item_item_ptr = new double[result_item.size()];

                    double * output_item_item(*output_item_item_ptr);

                    for(auto const & result_item_item : result_item) {
                        if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");

                        *output_item_item = result_item_item;

                        ++output_item_item;
                    }
                }

                *output_item_items = result_item.size();

                ++output_item_item_ptr;
                ++output_item_items;
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint8_DestroyTransformedData(/*out*/ double * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
/* |  AnalyticalRollingWindowFeaturizer <uint16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::AnalyticalRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint16_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ uint16_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input_items);

        while(input0_buffer.size() < input_items) {
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
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::uint16_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::uint16_t>>::type> input_buffer;

        input_buffer.reserve(input_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input_items) {
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint16_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(InputType(input0_buffer, input1)));

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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint16_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item_item_ptr_ptr = nullptr;
            *output_item_items_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr_ptr = new double *[result.size()];
            *output_item_items_ptr = new size_t[result.size()];

            double ** output_item_item_ptr(*output_item_item_ptr_ptr);
            size_t * output_item_items(*output_item_items_ptr);

            for(auto const & result_item : result) {
                if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
                if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

                if(result_item.empty()) {
                    *output_item_item_ptr = nullptr;
                }
                else {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item_item_ptr = new double[result_item.size()];

                    double * output_item_item(*output_item_item_ptr);

                    for(auto const & result_item_item : result_item) {
                        if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");

                        *output_item_item = result_item_item;

                        ++output_item_item;
                    }
                }

                *output_item_items = result_item.size();

                ++output_item_item_ptr;
                ++output_item_items;
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint16_DestroyTransformedData(/*out*/ double * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
/* |  AnalyticalRollingWindowFeaturizer <uint32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::AnalyticalRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint32_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ uint32_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input_items);

        while(input0_buffer.size() < input_items) {
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
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::uint32_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::uint32_t>>::type> input_buffer;

        input_buffer.reserve(input_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input_items) {
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint32_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(InputType(input0_buffer, input1)));

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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint32_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item_item_ptr_ptr = nullptr;
            *output_item_items_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr_ptr = new double *[result.size()];
            *output_item_items_ptr = new size_t[result.size()];

            double ** output_item_item_ptr(*output_item_item_ptr_ptr);
            size_t * output_item_items(*output_item_items_ptr);

            for(auto const & result_item : result) {
                if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
                if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

                if(result_item.empty()) {
                    *output_item_item_ptr = nullptr;
                }
                else {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item_item_ptr = new double[result_item.size()];

                    double * output_item_item(*output_item_item_ptr);

                    for(auto const & result_item_item : result_item) {
                        if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");

                        *output_item_item = result_item_item;

                        ++output_item_item;
                    }
                }

                *output_item_items = result_item.size();

                ++output_item_item_ptr;
                ++output_item_items;
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint32_DestroyTransformedData(/*out*/ double * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
/* |  AnalyticalRollingWindowFeaturizer <uint64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::AnalyticalRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint64_t input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ uint64_t const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input_items);

        while(input0_buffer.size() < input_items) {
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
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::uint64_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::uint64_t>>::type> input_buffer;

        input_buffer.reserve(input_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input_items) {
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ uint64_t input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(InputType(input0_buffer, input1)));

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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::uint64_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item_item_ptr_ptr = nullptr;
            *output_item_items_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr_ptr = new double *[result.size()];
            *output_item_items_ptr = new size_t[result.size()];

            double ** output_item_item_ptr(*output_item_item_ptr_ptr);
            size_t * output_item_items(*output_item_items_ptr);

            for(auto const & result_item : result) {
                if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
                if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

                if(result_item.empty()) {
                    *output_item_item_ptr = nullptr;
                }
                else {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item_item_ptr = new double[result_item.size()];

                    double * output_item_item(*output_item_item_ptr);

                    for(auto const & result_item_item : result_item) {
                        if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");

                        *output_item_item = result_item_item;

                        ++output_item_item;
                    }
                }

                *output_item_items = result_item.size();

                ++output_item_item_ptr;
                ++output_item_items;
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_uint64_DestroyTransformedData(/*out*/ double * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
/* |  AnalyticalRollingWindowFeaturizer <float> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::AnalyticalRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_float_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ float const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input_items);

        while(input0_buffer.size() < input_items) {
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
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::float_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::float_t>>::type> input_buffer;

        input_buffer.reserve(input_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input_items) {
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(InputType(input0_buffer, input1)));

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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::float_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item_item_ptr_ptr = nullptr;
            *output_item_items_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr_ptr = new double *[result.size()];
            *output_item_items_ptr = new size_t[result.size()];

            double ** output_item_item_ptr(*output_item_item_ptr_ptr);
            size_t * output_item_items(*output_item_items_ptr);

            for(auto const & result_item : result) {
                if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
                if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

                if(result_item.empty()) {
                    *output_item_item_ptr = nullptr;
                }
                else {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item_item_ptr = new double[result_item.size()];

                    double * output_item_item(*output_item_item_ptr);

                    for(auto const & result_item_item : result_item) {
                        if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");

                        *output_item_item = result_item_item;

                        ++output_item_item;
                    }
                }

                *output_item_items = result_item.size();

                ++output_item_item_ptr;
                ++output_item_items;
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_float_DestroyTransformedData(/*out*/ double * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
/* |  AnalyticalRollingWindowFeaturizer <double> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_CreateEstimator(/*in*/ uint8_t windowCalculation, /*in*/ uint32_t horizon, /*in*/ uint32_t maxWindowSize, /*in*/ uint32_t minWindowSize, /*out*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , static_cast<typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::AnalyticalRollingWindowCalculation>(windowCalculation), horizon, maxWindowSize, minWindowSize);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_double_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_DestroyEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_GetState(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_IsTrainingComplete(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_Fit(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_FitBuffer(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ double const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input0_ptrs == nullptr) throw std::invalid_argument("'input0_ptrs' is null");
        if(input0_ptr_items == nullptr) throw std::invalid_argument("'input0_ptr_items' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::vector<std::string>> input0_buffer;

        input0_buffer.reserve(input_items);

        while(input0_buffer.size() < input_items) {
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
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        // std::vector<std::string>


        // std::double_t

        std::vector<typename make_tuple_elements_const_references<std::tuple<std::vector<std::string>, std::double_t>>::type> input_buffer;

        input_buffer.reserve(input_items);

        auto * input0_creation_ptr(input0_buffer.data());
        auto * input1_creation_ptr(input1_ptr);

        while(input_buffer.size() < input_items) {
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_OnDataCompleted(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_CompleteTraining(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_CreateTransformerFromEstimator(/*in*/ AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<AnalyticalRollingWindowFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_DestroyTransformer(/*in*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_CreateTransformerSaveData(/*in*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_Transform(/*in*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ double ** output_item_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(InputType(input0_buffer, input1)));

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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_Flush(/*in*/ AnalyticalRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::double_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item_item_ptr_ptr = nullptr;
            *output_item_items_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr_ptr = new double *[result.size()];
            *output_item_items_ptr = new size_t[result.size()];

            double ** output_item_item_ptr(*output_item_item_ptr_ptr);
            size_t * output_item_items(*output_item_items_ptr);

            for(auto const & result_item : result) {
                if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
                if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

                if(result_item.empty()) {
                    *output_item_item_ptr = nullptr;
                }
                else {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item_item_ptr = new double[result_item.size()];

                    double * output_item_item(*output_item_item_ptr);

                    for(auto const & result_item_item : result_item) {
                        if(output_item_item == nullptr) throw std::invalid_argument("'output_item_item' is null");

                        *output_item_item = result_item_item;

                        ++output_item_item;
                    }
                }

                *output_item_items = result_item.size();

                ++output_item_item_ptr;
                ++output_item_items;
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

FEATURIZER_LIBRARY_API bool AnalyticalRollingWindowFeaturizer_double_DestroyTransformedData(/*out*/ double * result_item_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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


#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

} // extern "C"
