/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_LagLeadOperatorFeaturizer.h"
#include "SharedLibrary_Common.hpp"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "LagLeadOperatorFeaturizer.h"

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
/* |  LagLeadOperatorFeaturizer <float> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_CreateEstimator(/*in*/ uint32_t horizon, /*in*/ int64_t const * deltas_ptr, /*in*/ size_t deltas_items, /*out*/ LagLeadOperatorFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(deltas_ptr == nullptr) throw std::invalid_argument("'deltas_ptr' is null");
        if(deltas_items == 0) throw std::invalid_argument("'deltas_items' is 0");
        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , horizon, std::make_tuple(deltas_ptr, deltas_ptr + deltas_items));

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<LagLeadOperatorFeaturizer_float_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_DestroyEstimator(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_GetState(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_IsTrainingComplete(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_Fit(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_FitBuffer(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ float const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

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

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_OnDataCompleted(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_CompleteTraining(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_CreateTransformerFromEstimator(/*in*/ LagLeadOperatorFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ LagLeadOperatorFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<LagLeadOperatorFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ LagLeadOperatorFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<LagLeadOperatorFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_DestroyTransformer(/*in*/ LagLeadOperatorFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_CreateTransformerSaveData(/*in*/ LagLeadOperatorFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_Transform(/*in*/ LagLeadOperatorFeaturizer_float_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ float input1, /*out*/ char **** output_item0_ptr_ptr, /*out*/ size_t ** output_item0_items_ptr, /*out*/ size_t ** output_item1_cols_ptr, /*out*/ size_t ** output_item1_rows_ptr, /*out*/ float *** output_item1_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        if(output_item0_ptr_ptr == nullptr) throw std::invalid_argument("'output_item0_ptr_ptr' is null");
        if(output_item0_items_ptr == nullptr) throw std::invalid_argument("'output_item0_items_ptr' is null");
        if(output_item1_cols_ptr == nullptr) throw std::invalid_argument("'output_item1_cols_ptr' is null");
        if(output_item1_rows_ptr == nullptr) throw std::invalid_argument("'output_item1_rows_ptr' is null");
        if(output_item1_ptr_ptr == nullptr) throw std::invalid_argument("'output_item1_ptr_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(InputType(input0_buffer, input1), callback);

        // Output
        if(result.empty()) {
            *output_item0_ptr_ptr = nullptr;
            *output_item0_items_ptr = nullptr;
            *output_item1_cols_ptr = nullptr;
            *output_item1_rows_ptr = nullptr;
            *output_item1_ptr_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item0_ptr_ptr = new char **[result.size()];
            *output_item0_items_ptr = new size_t[result.size()];
            *output_item1_cols_ptr = new size_t[result.size()];
            *output_item1_rows_ptr = new size_t[result.size()];
            *output_item1_ptr_ptr = new float *[result.size()];

            char *** output_item0_ptr(*output_item0_ptr_ptr);
            size_t * output_item0_items(*output_item0_items_ptr);
            size_t * output_item1_cols(*output_item1_cols_ptr);
            size_t * output_item1_rows(*output_item1_rows_ptr);
            float ** output_item1_ptr(*output_item1_ptr_ptr);

            for(auto const & result_item : result) {
                if(output_item0_ptr == nullptr) throw std::invalid_argument("'output_item0_ptr' is null");
                if(output_item0_items == nullptr) throw std::invalid_argument("'output_item0_items' is null");

                if(output_item1_cols == nullptr) throw std::invalid_argument("'output_item1_cols' is null");
                if(output_item1_rows == nullptr) throw std::invalid_argument("'output_item1_rows' is null");
                if(output_item1_ptr == nullptr) throw std::invalid_argument("'output_item1_ptr' is null");

                // [0] std::vector<std::string>

                auto const & result_item0(std::get<0>(result_item));

                // TODO: There are potential memory leaks if allocation fails
                *output_item0_ptr = new char *[result_item0.size()];

                char ** output_item0_ptr_item(*output_item0_ptr);

                for(std::string const & result_item0_item : result_item0) {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item0_ptr_item = new char[result_item0_item.size() + 1];

                    std::copy(result_item0_item.begin(), result_item0_item.end(), *output_item0_ptr_item);
                    (*output_item0_ptr_item)[result_item0_item.size()] = 0;

                    ++output_item0_ptr_item;
                }

                *output_item0_items = result_item0.size();

                // [1] Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>>

                auto const & result_item1(std::get<1>(result_item));

                struct output_item1Internal {
                    static void Deleter(float *pData) {
                        delete [] pData;
                    }
                };

                std::unique_ptr<float, void (*)(float *)> output_item1_buffer(new float[static_cast<size_t>(result_item1.size())], output_item1Internal::Deleter);

                memcpy(output_item1_buffer.get(), result_item1.data(), static_cast<size_t>(result_item1.size()) * sizeof(float));

                *output_item1_ptr = output_item1_buffer.release();
                *output_item1_cols = static_cast<size_t>(result_item1.cols());
                *output_item1_rows = static_cast<size_t>(result_item1.rows());

                ++output_item0_ptr;
                ++output_item0_items;
                ++output_item1_cols;
                ++output_item1_rows;
                ++output_item1_ptr;
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

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_Flush(/*in*/ LagLeadOperatorFeaturizer_float_TransformerHandle *pHandle, /*out*/ char **** output_item0_ptr_ptr, /*out*/ size_t ** output_item0_items_ptr, /*out*/ size_t ** output_item1_cols_ptr, /*out*/ size_t ** output_item1_rows_ptr, /*out*/ float *** output_item1_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item0_ptr_ptr == nullptr) throw std::invalid_argument("'output_item0_ptr_ptr' is null");
        if(output_item0_items_ptr == nullptr) throw std::invalid_argument("'output_item0_items_ptr' is null");
        if(output_item1_cols_ptr == nullptr) throw std::invalid_argument("'output_item1_cols_ptr' is null");
        if(output_item1_rows_ptr == nullptr) throw std::invalid_argument("'output_item1_rows_ptr' is null");
        if(output_item1_ptr_ptr == nullptr) throw std::invalid_argument("'output_item1_ptr_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::float_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item0_ptr_ptr = nullptr;
            *output_item0_items_ptr = nullptr;
            *output_item1_cols_ptr = nullptr;
            *output_item1_rows_ptr = nullptr;
            *output_item1_ptr_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item0_ptr_ptr = new char **[result.size()];
            *output_item0_items_ptr = new size_t[result.size()];
            *output_item1_cols_ptr = new size_t[result.size()];
            *output_item1_rows_ptr = new size_t[result.size()];
            *output_item1_ptr_ptr = new float *[result.size()];

            char *** output_item0_ptr(*output_item0_ptr_ptr);
            size_t * output_item0_items(*output_item0_items_ptr);
            size_t * output_item1_cols(*output_item1_cols_ptr);
            size_t * output_item1_rows(*output_item1_rows_ptr);
            float ** output_item1_ptr(*output_item1_ptr_ptr);

            for(auto const & result_item : result) {
                if(output_item0_ptr == nullptr) throw std::invalid_argument("'output_item0_ptr' is null");
                if(output_item0_items == nullptr) throw std::invalid_argument("'output_item0_items' is null");

                if(output_item1_cols == nullptr) throw std::invalid_argument("'output_item1_cols' is null");
                if(output_item1_rows == nullptr) throw std::invalid_argument("'output_item1_rows' is null");
                if(output_item1_ptr == nullptr) throw std::invalid_argument("'output_item1_ptr' is null");

                // [0] std::vector<std::string>

                auto const & result_item0(std::get<0>(result_item));

                // TODO: There are potential memory leaks if allocation fails
                *output_item0_ptr = new char *[result_item0.size()];

                char ** output_item0_ptr_item(*output_item0_ptr);

                for(std::string const & result_item0_item : result_item0) {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item0_ptr_item = new char[result_item0_item.size() + 1];

                    std::copy(result_item0_item.begin(), result_item0_item.end(), *output_item0_ptr_item);
                    (*output_item0_ptr_item)[result_item0_item.size()] = 0;

                    ++output_item0_ptr_item;
                }

                *output_item0_items = result_item0.size();

                // [1] Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>>

                auto const & result_item1(std::get<1>(result_item));

                struct output_item1Internal {
                    static void Deleter(float *pData) {
                        delete [] pData;
                    }
                };

                std::unique_ptr<float, void (*)(float *)> output_item1_buffer(new float[static_cast<size_t>(result_item1.size())], output_item1Internal::Deleter);

                memcpy(output_item1_buffer.get(), result_item1.data(), static_cast<size_t>(result_item1.size()) * sizeof(float));

                *output_item1_ptr = output_item1_buffer.release();
                *output_item1_cols = static_cast<size_t>(result_item1.cols());
                *output_item1_rows = static_cast<size_t>(result_item1.rows());

                ++output_item0_ptr;
                ++output_item0_items;
                ++output_item1_cols;
                ++output_item1_rows;
                ++output_item1_ptr;
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

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_float_DestroyTransformedData(/*out*/ char *** result_item0_ptr_ptr, /*out*/ size_t * result_item0_items_ptr, /*out*/ size_t * result_item1_cols_ptr, /*out*/ size_t * result_item1_rows_ptr, /*out*/ float ** result_item1_ptr_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item0_ptr_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item0_ptr_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_item0_items_ptr) != bool(result_item0_ptr_ptr)) throw std::invalid_argument("'result_item0_items_ptr' is not internally consistent");
        if(bool(result_item1_cols_ptr) != bool(result_item0_ptr_ptr)) throw std::invalid_argument("'result_item1_cols_ptr' is not internally consistent");
        if(bool(result_item1_rows_ptr) != bool(result_item0_ptr_ptr)) throw std::invalid_argument("'result_item1_rows_ptr' is not internally consistent");
        if(bool(result_item1_ptr_ptr) != bool(result_item0_ptr_ptr)) throw std::invalid_argument("'result_item1_ptr_ptr' is not internally consistent");
        if(bool(result_items) != bool(result_item0_ptr_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item0_ptr_ptr != nullptr) {
            char *** this_result_item0_ptr_ptr(result_item0_ptr_ptr);
            size_t * this_result_item0_items_ptr(result_item0_items_ptr);
            size_t * this_result_item1_cols_ptr(result_item1_cols_ptr);
            size_t * this_result_item1_rows_ptr(result_item1_rows_ptr);
            float ** this_result_item1_ptr_ptr(result_item1_ptr_ptr);

            while(result_items--) {
                char const * const * const & result_destroy_item0_ptr(*this_result_item0_ptr_ptr);
                size_t const & result_destroy_item0_items(*this_result_item0_items_ptr);
                size_t const & result_destroy_item1_cols(*this_result_item1_cols_ptr);
                size_t const & result_destroy_item1_rows(*this_result_item1_rows_ptr);
                float const * const & result_destroy_item1_ptr(*this_result_item1_ptr_ptr);

                if(result_destroy_item0_ptr == nullptr && result_destroy_item0_items != 0) throw std::invalid_argument("'result_destroy_item0_items' is not 0");
                if(result_destroy_item0_ptr != nullptr && result_destroy_item0_items == 0) throw std::invalid_argument("'result_destroy_item0_items' is 0");

                if(result_destroy_item1_ptr == nullptr && (result_destroy_item1_cols != 0 || result_destroy_item1_rows != 0)) throw std::invalid_argument("Invalid buffer");
                if(result_destroy_item1_ptr != nullptr && (result_destroy_item1_cols == 0 || result_destroy_item1_rows == 0)) throw std::invalid_argument("Invalid buffer");

                // [0] std::vector<std::string>
                if(result_destroy_item0_ptr != nullptr) {
                    char const * const * result_destroy_item0_ptr_ptr(result_destroy_item0_ptr);
                    char const * const * const result_destroy_item0_ptr_end(result_destroy_item0_ptr_ptr + result_destroy_item0_items);

                    while(result_destroy_item0_ptr_ptr != result_destroy_item0_ptr_end) {
                        if(*result_destroy_item0_ptr_ptr == nullptr) throw std::invalid_argument("result_destroy_item0_ptr has an invalid element");

                        delete [] *result_destroy_item0_ptr_ptr;

                        ++result_destroy_item0_ptr_ptr;
                    }

                    delete [] result_destroy_item0_ptr;
                }

                // [1] Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>>
                if(result_destroy_item1_ptr)
                    delete [] result_destroy_item1_ptr;

                ++this_result_item0_ptr_ptr;
                ++this_result_item0_items_ptr;
                ++this_result_item1_cols_ptr;
                ++this_result_item1_rows_ptr;
                ++this_result_item1_ptr_ptr;
            }

            delete [] result_item0_ptr_ptr;
            delete [] result_item0_items_ptr;
            delete [] result_item1_cols_ptr;
            delete [] result_item1_rows_ptr;
            delete [] result_item1_ptr_ptr;
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
/* |  LagLeadOperatorFeaturizer <double> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_CreateEstimator(/*in*/ uint32_t horizon, /*in*/ int64_t const * deltas_ptr, /*in*/ size_t deltas_items, /*out*/ LagLeadOperatorFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(deltas_ptr == nullptr) throw std::invalid_argument("'deltas_ptr' is null");
        if(deltas_items == 0) throw std::invalid_argument("'deltas_items' is 0");
        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) , horizon, std::make_tuple(deltas_ptr, deltas_ptr + deltas_items));

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<LagLeadOperatorFeaturizer_double_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_DestroyEstimator(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_GetState(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_IsTrainingComplete(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_Fit(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::InputType;

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(InputType(input0_buffer, input1)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_FitBuffer(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*in*/ char const * const * const * input0_ptrs, /*in*/ size_t const * input0_ptr_items, /*in*/ double const * input1_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

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

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_OnDataCompleted(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_CompleteTraining(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_CreateTransformerFromEstimator(/*in*/ LagLeadOperatorFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ LagLeadOperatorFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<LagLeadOperatorFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ LagLeadOperatorFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<LagLeadOperatorFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_DestroyTransformer(/*in*/ LagLeadOperatorFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_CreateTransformerSaveData(/*in*/ LagLeadOperatorFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_Transform(/*in*/ LagLeadOperatorFeaturizer_double_TransformerHandle *pHandle, /*in*/ char const * const * input0_ptr, /*in*/ size_t input0_items, /*in*/ double input1, /*out*/ char **** output_item0_ptr_ptr, /*out*/ size_t ** output_item0_items_ptr, /*out*/ size_t ** output_item1_cols_ptr, /*out*/ size_t ** output_item1_rows_ptr, /*out*/ double *** output_item1_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        if(output_item0_ptr_ptr == nullptr) throw std::invalid_argument("'output_item0_ptr_ptr' is null");
        if(output_item0_items_ptr == nullptr) throw std::invalid_argument("'output_item0_items_ptr' is null");
        if(output_item1_cols_ptr == nullptr) throw std::invalid_argument("'output_item1_cols_ptr' is null");
        if(output_item1_rows_ptr == nullptr) throw std::invalid_argument("'output_item1_rows_ptr' is null");
        if(output_item1_ptr_ptr == nullptr) throw std::invalid_argument("'output_item1_ptr_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(InputType(input0_buffer, input1), callback);

        // Output
        if(result.empty()) {
            *output_item0_ptr_ptr = nullptr;
            *output_item0_items_ptr = nullptr;
            *output_item1_cols_ptr = nullptr;
            *output_item1_rows_ptr = nullptr;
            *output_item1_ptr_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item0_ptr_ptr = new char **[result.size()];
            *output_item0_items_ptr = new size_t[result.size()];
            *output_item1_cols_ptr = new size_t[result.size()];
            *output_item1_rows_ptr = new size_t[result.size()];
            *output_item1_ptr_ptr = new double *[result.size()];

            char *** output_item0_ptr(*output_item0_ptr_ptr);
            size_t * output_item0_items(*output_item0_items_ptr);
            size_t * output_item1_cols(*output_item1_cols_ptr);
            size_t * output_item1_rows(*output_item1_rows_ptr);
            double ** output_item1_ptr(*output_item1_ptr_ptr);

            for(auto const & result_item : result) {
                if(output_item0_ptr == nullptr) throw std::invalid_argument("'output_item0_ptr' is null");
                if(output_item0_items == nullptr) throw std::invalid_argument("'output_item0_items' is null");

                if(output_item1_cols == nullptr) throw std::invalid_argument("'output_item1_cols' is null");
                if(output_item1_rows == nullptr) throw std::invalid_argument("'output_item1_rows' is null");
                if(output_item1_ptr == nullptr) throw std::invalid_argument("'output_item1_ptr' is null");

                // [0] std::vector<std::string>

                auto const & result_item0(std::get<0>(result_item));

                // TODO: There are potential memory leaks if allocation fails
                *output_item0_ptr = new char *[result_item0.size()];

                char ** output_item0_ptr_item(*output_item0_ptr);

                for(std::string const & result_item0_item : result_item0) {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item0_ptr_item = new char[result_item0_item.size() + 1];

                    std::copy(result_item0_item.begin(), result_item0_item.end(), *output_item0_ptr_item);
                    (*output_item0_ptr_item)[result_item0_item.size()] = 0;

                    ++output_item0_ptr_item;
                }

                *output_item0_items = result_item0.size();

                // [1] Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>>

                auto const & result_item1(std::get<1>(result_item));

                struct output_item1Internal {
                    static void Deleter(double *pData) {
                        delete [] pData;
                    }
                };

                std::unique_ptr<double, void (*)(double *)> output_item1_buffer(new double[static_cast<size_t>(result_item1.size())], output_item1Internal::Deleter);

                memcpy(output_item1_buffer.get(), result_item1.data(), static_cast<size_t>(result_item1.size()) * sizeof(double));

                *output_item1_ptr = output_item1_buffer.release();
                *output_item1_cols = static_cast<size_t>(result_item1.cols());
                *output_item1_rows = static_cast<size_t>(result_item1.rows());

                ++output_item0_ptr;
                ++output_item0_items;
                ++output_item1_cols;
                ++output_item1_rows;
                ++output_item1_ptr;
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

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_Flush(/*in*/ LagLeadOperatorFeaturizer_double_TransformerHandle *pHandle, /*out*/ char **** output_item0_ptr_ptr, /*out*/ size_t ** output_item0_items_ptr, /*out*/ size_t ** output_item1_cols_ptr, /*out*/ size_t ** output_item1_rows_ptr, /*out*/ double *** output_item1_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item0_ptr_ptr == nullptr) throw std::invalid_argument("'output_item0_ptr_ptr' is null");
        if(output_item0_items_ptr == nullptr) throw std::invalid_argument("'output_item0_items_ptr' is null");
        if(output_item1_cols_ptr == nullptr) throw std::invalid_argument("'output_item1_cols_ptr' is null");
        if(output_item1_rows_ptr == nullptr) throw std::invalid_argument("'output_item1_rows_ptr' is null");
        if(output_item1_ptr_ptr == nullptr) throw std::invalid_argument("'output_item1_ptr_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::GrainedLagLeadOperatorEstimator<std::double_t>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item0_ptr_ptr = nullptr;
            *output_item0_items_ptr = nullptr;
            *output_item1_cols_ptr = nullptr;
            *output_item1_rows_ptr = nullptr;
            *output_item1_ptr_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item0_ptr_ptr = new char **[result.size()];
            *output_item0_items_ptr = new size_t[result.size()];
            *output_item1_cols_ptr = new size_t[result.size()];
            *output_item1_rows_ptr = new size_t[result.size()];
            *output_item1_ptr_ptr = new double *[result.size()];

            char *** output_item0_ptr(*output_item0_ptr_ptr);
            size_t * output_item0_items(*output_item0_items_ptr);
            size_t * output_item1_cols(*output_item1_cols_ptr);
            size_t * output_item1_rows(*output_item1_rows_ptr);
            double ** output_item1_ptr(*output_item1_ptr_ptr);

            for(auto const & result_item : result) {
                if(output_item0_ptr == nullptr) throw std::invalid_argument("'output_item0_ptr' is null");
                if(output_item0_items == nullptr) throw std::invalid_argument("'output_item0_items' is null");

                if(output_item1_cols == nullptr) throw std::invalid_argument("'output_item1_cols' is null");
                if(output_item1_rows == nullptr) throw std::invalid_argument("'output_item1_rows' is null");
                if(output_item1_ptr == nullptr) throw std::invalid_argument("'output_item1_ptr' is null");

                // [0] std::vector<std::string>

                auto const & result_item0(std::get<0>(result_item));

                // TODO: There are potential memory leaks if allocation fails
                *output_item0_ptr = new char *[result_item0.size()];

                char ** output_item0_ptr_item(*output_item0_ptr);

                for(std::string const & result_item0_item : result_item0) {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item0_ptr_item = new char[result_item0_item.size() + 1];

                    std::copy(result_item0_item.begin(), result_item0_item.end(), *output_item0_ptr_item);
                    (*output_item0_ptr_item)[result_item0_item.size()] = 0;

                    ++output_item0_ptr_item;
                }

                *output_item0_items = result_item0.size();

                // [1] Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>>

                auto const & result_item1(std::get<1>(result_item));

                struct output_item1Internal {
                    static void Deleter(double *pData) {
                        delete [] pData;
                    }
                };

                std::unique_ptr<double, void (*)(double *)> output_item1_buffer(new double[static_cast<size_t>(result_item1.size())], output_item1Internal::Deleter);

                memcpy(output_item1_buffer.get(), result_item1.data(), static_cast<size_t>(result_item1.size()) * sizeof(double));

                *output_item1_ptr = output_item1_buffer.release();
                *output_item1_cols = static_cast<size_t>(result_item1.cols());
                *output_item1_rows = static_cast<size_t>(result_item1.rows());

                ++output_item0_ptr;
                ++output_item0_items;
                ++output_item1_cols;
                ++output_item1_rows;
                ++output_item1_ptr;
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

FEATURIZER_LIBRARY_API bool LagLeadOperatorFeaturizer_double_DestroyTransformedData(/*out*/ char *** result_item0_ptr_ptr, /*out*/ size_t * result_item0_items_ptr, /*out*/ size_t * result_item1_cols_ptr, /*out*/ size_t * result_item1_rows_ptr, /*out*/ double ** result_item1_ptr_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item0_ptr_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item0_ptr_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_item0_items_ptr) != bool(result_item0_ptr_ptr)) throw std::invalid_argument("'result_item0_items_ptr' is not internally consistent");
        if(bool(result_item1_cols_ptr) != bool(result_item0_ptr_ptr)) throw std::invalid_argument("'result_item1_cols_ptr' is not internally consistent");
        if(bool(result_item1_rows_ptr) != bool(result_item0_ptr_ptr)) throw std::invalid_argument("'result_item1_rows_ptr' is not internally consistent");
        if(bool(result_item1_ptr_ptr) != bool(result_item0_ptr_ptr)) throw std::invalid_argument("'result_item1_ptr_ptr' is not internally consistent");
        if(bool(result_items) != bool(result_item0_ptr_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item0_ptr_ptr != nullptr) {
            char *** this_result_item0_ptr_ptr(result_item0_ptr_ptr);
            size_t * this_result_item0_items_ptr(result_item0_items_ptr);
            size_t * this_result_item1_cols_ptr(result_item1_cols_ptr);
            size_t * this_result_item1_rows_ptr(result_item1_rows_ptr);
            double ** this_result_item1_ptr_ptr(result_item1_ptr_ptr);

            while(result_items--) {
                char const * const * const & result_destroy_item0_ptr(*this_result_item0_ptr_ptr);
                size_t const & result_destroy_item0_items(*this_result_item0_items_ptr);
                size_t const & result_destroy_item1_cols(*this_result_item1_cols_ptr);
                size_t const & result_destroy_item1_rows(*this_result_item1_rows_ptr);
                double const * const & result_destroy_item1_ptr(*this_result_item1_ptr_ptr);

                if(result_destroy_item0_ptr == nullptr && result_destroy_item0_items != 0) throw std::invalid_argument("'result_destroy_item0_items' is not 0");
                if(result_destroy_item0_ptr != nullptr && result_destroy_item0_items == 0) throw std::invalid_argument("'result_destroy_item0_items' is 0");

                if(result_destroy_item1_ptr == nullptr && (result_destroy_item1_cols != 0 || result_destroy_item1_rows != 0)) throw std::invalid_argument("Invalid buffer");
                if(result_destroy_item1_ptr != nullptr && (result_destroy_item1_cols == 0 || result_destroy_item1_rows == 0)) throw std::invalid_argument("Invalid buffer");

                // [0] std::vector<std::string>
                if(result_destroy_item0_ptr != nullptr) {
                    char const * const * result_destroy_item0_ptr_ptr(result_destroy_item0_ptr);
                    char const * const * const result_destroy_item0_ptr_end(result_destroy_item0_ptr_ptr + result_destroy_item0_items);

                    while(result_destroy_item0_ptr_ptr != result_destroy_item0_ptr_end) {
                        if(*result_destroy_item0_ptr_ptr == nullptr) throw std::invalid_argument("result_destroy_item0_ptr has an invalid element");

                        delete [] *result_destroy_item0_ptr_ptr;

                        ++result_destroy_item0_ptr_ptr;
                    }

                    delete [] result_destroy_item0_ptr;
                }

                // [1] Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>>
                if(result_destroy_item1_ptr)
                    delete [] result_destroy_item1_ptr;

                ++this_result_item0_ptr_ptr;
                ++this_result_item0_items_ptr;
                ++this_result_item1_cols_ptr;
                ++this_result_item1_rows_ptr;
                ++this_result_item1_ptr_ptr;
            }

            delete [] result_item0_ptr_ptr;
            delete [] result_item0_items_ptr;
            delete [] result_item1_cols_ptr;
            delete [] result_item1_rows_ptr;
            delete [] result_item1_ptr_ptr;
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
