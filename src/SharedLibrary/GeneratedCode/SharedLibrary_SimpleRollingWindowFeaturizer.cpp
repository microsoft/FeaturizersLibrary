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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ float const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_Transform(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ size_t * output_cols, /*out*/ size_t * output_rows, /*out*/ float ** output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        if(output_cols == nullptr) throw std::invalid_argument("'output_cols' is null");
        if(output_rows == nullptr) throw std::invalid_argument("'output_rows' is null");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::float_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(InputType(input0_buffer, input1)));

        // Output
        struct outputInternal {
            static void Deleter(float *pData) {
                delete [] pData;
            }
        };

        std::unique_ptr<float, void (*)(float *)> output_buffer(new float[static_cast<size_t>(result.size())], outputInternal::Deleter);

        memcpy(output_buffer.get(), result.data(), static_cast<size_t>(result.size()) * sizeof(float));

        *output_ptr = output_buffer.release();
        *output_cols = static_cast<size_t>(result.cols());
        *output_rows = static_cast<size_t>(result.rows());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_Flush(/*in*/ SimpleRollingWindowFeaturizer_float_TransformerHandle *pHandle, /*out*/ size_t ** output_item_cols_ptr, /*out*/ size_t ** output_item_rows_ptr, /*out*/ float *** output_item_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_cols_ptr == nullptr) throw std::invalid_argument("'output_item_cols_ptr' is null");
        if(output_item_rows_ptr == nullptr) throw std::invalid_argument("'output_item_rows_ptr' is null");
        if(output_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_ptr_ptr' is null");
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
        if(result.empty()) {
            *output_item_cols_ptr = nullptr;
            *output_item_rows_ptr = nullptr;
            *output_item_ptr_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_cols_ptr = new size_t[result.size()];
            *output_item_rows_ptr = new size_t[result.size()];
            *output_item_ptr_ptr = new float *[result.size()];

            size_t * output_item_cols(*output_item_cols_ptr);
            size_t * output_item_rows(*output_item_rows_ptr);
            float ** output_item_ptr(*output_item_ptr_ptr);

            for(auto const & result_item : result) {
                if(output_item_cols == nullptr) throw std::invalid_argument("'output_item_cols' is null");
                if(output_item_rows == nullptr) throw std::invalid_argument("'output_item_rows' is null");
                if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");

                struct output_itemInternal {
                    static void Deleter(float *pData) {
                        delete [] pData;
                    }
                };

                std::unique_ptr<float, void (*)(float *)> output_item_buffer(new float[static_cast<size_t>(result_item.size())], output_itemInternal::Deleter);

                memcpy(output_item_buffer.get(), result_item.data(), static_cast<size_t>(result_item.size()) * sizeof(float));

                *output_item_ptr = output_item_buffer.release();
                *output_item_cols = static_cast<size_t>(result_item.cols());
                *output_item_rows = static_cast<size_t>(result_item.rows());

                ++output_item_cols;
                ++output_item_rows;
                ++output_item_ptr;
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_float_DestroyTransformedData(/*out*/ size_t result_cols, /*out*/ size_t result_rows, /*out*/ float const * result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && (result_cols != 0 || result_rows != 0)) throw std::invalid_argument("Invalid buffer");
        if(result_ptr != nullptr && (result_cols == 0 || result_rows == 0)) throw std::invalid_argument("Invalid buffer");

        if(result_ptr)
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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_FitBuffer(/*in*/ SimpleRollingWindowFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ double const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_Transform(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ size_t * output_cols, /*out*/ size_t * output_rows, /*out*/ double ** output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        if(output_cols == nullptr) throw std::invalid_argument("'output_cols' is null");
        if(output_rows == nullptr) throw std::invalid_argument("'output_rows' is null");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");

        Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedSimpleRollingWindowEstimator<std::double_t>::TransformedType;

        // Input
        TransformedType result(transformer.execute(InputType(input0_buffer, input1)));

        // Output
        struct outputInternal {
            static void Deleter(double *pData) {
                delete [] pData;
            }
        };

        std::unique_ptr<double, void (*)(double *)> output_buffer(new double[static_cast<size_t>(result.size())], outputInternal::Deleter);

        memcpy(output_buffer.get(), result.data(), static_cast<size_t>(result.size()) * sizeof(double));

        *output_ptr = output_buffer.release();
        *output_cols = static_cast<size_t>(result.cols());
        *output_rows = static_cast<size_t>(result.rows());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_Flush(/*in*/ SimpleRollingWindowFeaturizer_double_TransformerHandle *pHandle, /*out*/ size_t ** output_item_cols_ptr, /*out*/ size_t ** output_item_rows_ptr, /*out*/ double *** output_item_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_cols_ptr == nullptr) throw std::invalid_argument("'output_item_cols_ptr' is null");
        if(output_item_rows_ptr == nullptr) throw std::invalid_argument("'output_item_rows_ptr' is null");
        if(output_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_ptr_ptr' is null");
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
        if(result.empty()) {
            *output_item_cols_ptr = nullptr;
            *output_item_rows_ptr = nullptr;
            *output_item_ptr_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_cols_ptr = new size_t[result.size()];
            *output_item_rows_ptr = new size_t[result.size()];
            *output_item_ptr_ptr = new double *[result.size()];

            size_t * output_item_cols(*output_item_cols_ptr);
            size_t * output_item_rows(*output_item_rows_ptr);
            double ** output_item_ptr(*output_item_ptr_ptr);

            for(auto const & result_item : result) {
                if(output_item_cols == nullptr) throw std::invalid_argument("'output_item_cols' is null");
                if(output_item_rows == nullptr) throw std::invalid_argument("'output_item_rows' is null");
                if(output_item_ptr == nullptr) throw std::invalid_argument("'output_item_ptr' is null");

                struct output_itemInternal {
                    static void Deleter(double *pData) {
                        delete [] pData;
                    }
                };

                std::unique_ptr<double, void (*)(double *)> output_item_buffer(new double[static_cast<size_t>(result_item.size())], output_itemInternal::Deleter);

                memcpy(output_item_buffer.get(), result_item.data(), static_cast<size_t>(result_item.size()) * sizeof(double));

                *output_item_ptr = output_item_buffer.release();
                *output_item_cols = static_cast<size_t>(result_item.cols());
                *output_item_rows = static_cast<size_t>(result_item.rows());

                ++output_item_cols;
                ++output_item_rows;
                ++output_item_ptr;
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

FEATURIZER_LIBRARY_API bool SimpleRollingWindowFeaturizer_double_DestroyTransformedData(/*out*/ size_t result_cols, /*out*/ size_t result_rows, /*out*/ double const * result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && (result_cols != 0 || result_rows != 0)) throw std::invalid_argument("Invalid buffer");
        if(result_ptr != nullptr && (result_cols == 0 || result_rows == 0)) throw std::invalid_argument("Invalid buffer");

        if(result_ptr)
            delete [] result_ptr;
    
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
