/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_TruncatedSVDFeaturizer.h"
#include "SharedLibrary_Common.hpp"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "TruncatedSVDFeaturizer.h"

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
/* |  TruncatedSVDFeaturizer <float> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_CreateEstimator(/*out*/ TruncatedSVDFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>* pEstimator = new Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<TruncatedSVDFeaturizer_float_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_DestroyEstimator(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_GetState(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_IsTrainingComplete(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_Fit(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ float const * input_ptr, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_cols == 0) throw std::invalid_argument("'input_cols' is 0");
        if(input_rows == 0) throw std::invalid_argument("'input_rows' is 0");
        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(Eigen::Map<Eigen::MatrixX<std::float_t>>(const_cast<float *>(input_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols))));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_FitBuffer(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ float const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_cols == 0) throw std::invalid_argument("'input_cols' is 0");
        if(input_rows == 0) throw std::invalid_argument("'input_rows' is 0");
        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Eigen::Map<Eigen::MatrixX<std::float_t>>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
        #if (defined __apple_build_verion__)
            input_buffer.push_back(Eigen::Map<Eigen::MatrixX<std::float_t>>(const_cast<float *>(*input_values_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols)));
        #else
            input_buffer.emplace_back(Eigen::Map<Eigen::MatrixX<std::float_t>>(const_cast<float *>(*input_values_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols)));
        #endif
            ++input_values_ptr;
        }

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_OnDataCompleted(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_CompleteTraining(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_CreateTransformerFromEstimator(/*in*/ TruncatedSVDFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ TruncatedSVDFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<TruncatedSVDFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ TruncatedSVDFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<TruncatedSVDFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_DestroyTransformer(/*in*/ TruncatedSVDFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_CreateTransformerSaveData(/*in*/ TruncatedSVDFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_Transform(/*in*/ TruncatedSVDFeaturizer_float_TransformerHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ float const * input_ptr, /*out*/ size_t * output_cols, /*out*/ size_t * output_rows, /*out*/ float ** output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_cols == 0) throw std::invalid_argument("'input_cols' is 0");
        if(input_rows == 0) throw std::invalid_argument("'input_rows' is 0");
        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(output_cols == nullptr) throw std::invalid_argument("'output_cols' is null");
        if(output_rows == nullptr) throw std::invalid_argument("'output_rows' is null");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformedType;

        // Input
        TransformedType result(transformer.execute(Eigen::Map<Eigen::MatrixX<std::float_t>>(const_cast<float *>(input_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols))));

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

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_Flush(/*in*/ TruncatedSVDFeaturizer_float_TransformerHandle *pHandle, /*out*/ size_t ** output_item_cols_ptr, /*out*/ size_t ** output_item_rows_ptr, /*out*/ float *** output_item_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_cols_ptr == nullptr) throw std::invalid_argument("'output_item_cols_ptr' is null");
        if(output_item_rows_ptr == nullptr) throw std::invalid_argument("'output_item_rows_ptr' is null");
        if(output_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_ptr_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::float_t>>>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_cols_ptr = new size_t[result.size()];
        *output_item_rows_ptr = new size_t[result.size()];
        *output_item_ptr_ptr = new float *[result.size()];
        *output_items = result.size();

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
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_float_DestroyTransformedData(/*out*/ size_t result_cols, /*out*/ size_t result_rows, /*out*/ float * result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
/* |  TruncatedSVDFeaturizer <double> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_CreateEstimator(/*out*/ TruncatedSVDFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>* pEstimator = new Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<TruncatedSVDFeaturizer_double_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_DestroyEstimator(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_GetState(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_IsTrainingComplete(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_Fit(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ double const * input_ptr, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_cols == 0) throw std::invalid_argument("'input_cols' is 0");
        if(input_rows == 0) throw std::invalid_argument("'input_rows' is 0");
        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(Eigen::Map<Eigen::MatrixX<std::double_t>>(const_cast<double *>(input_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols))));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_FitBuffer(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ double const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_cols == 0) throw std::invalid_argument("'input_cols' is 0");
        if(input_rows == 0) throw std::invalid_argument("'input_rows' is 0");
        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Eigen::Map<Eigen::MatrixX<std::double_t>>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
        #if (defined __apple_build_verion__)
            input_buffer.push_back(Eigen::Map<Eigen::MatrixX<std::double_t>>(const_cast<double *>(*input_values_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols)));
        #else
            input_buffer.emplace_back(Eigen::Map<Eigen::MatrixX<std::double_t>>(const_cast<double *>(*input_values_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols)));
        #endif
            ++input_values_ptr;
        }

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_OnDataCompleted(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_CompleteTraining(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_CreateTransformerFromEstimator(/*in*/ TruncatedSVDFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ TruncatedSVDFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<TruncatedSVDFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ TruncatedSVDFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<TruncatedSVDFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_DestroyTransformer(/*in*/ TruncatedSVDFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_CreateTransformerSaveData(/*in*/ TruncatedSVDFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_Transform(/*in*/ TruncatedSVDFeaturizer_double_TransformerHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ double const * input_ptr, /*out*/ size_t * output_cols, /*out*/ size_t * output_rows, /*out*/ double ** output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_cols == 0) throw std::invalid_argument("'input_cols' is 0");
        if(input_rows == 0) throw std::invalid_argument("'input_rows' is 0");
        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(output_cols == nullptr) throw std::invalid_argument("'output_cols' is null");
        if(output_rows == nullptr) throw std::invalid_argument("'output_rows' is null");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformedType;

        // Input
        TransformedType result(transformer.execute(Eigen::Map<Eigen::MatrixX<std::double_t>>(const_cast<double *>(input_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols))));

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

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_Flush(/*in*/ TruncatedSVDFeaturizer_double_TransformerHandle *pHandle, /*out*/ size_t ** output_item_cols_ptr, /*out*/ size_t ** output_item_rows_ptr, /*out*/ double *** output_item_ptr_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_cols_ptr == nullptr) throw std::invalid_argument("'output_item_cols_ptr' is null");
        if(output_item_rows_ptr == nullptr) throw std::invalid_argument("'output_item_rows_ptr' is null");
        if(output_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_ptr_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::TruncatedSVDEstimator<Eigen::Map<Eigen::MatrixX<std::double_t>>>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        // TODO: There are potential memory leaks if allocation fails
        *output_item_cols_ptr = new size_t[result.size()];
        *output_item_rows_ptr = new size_t[result.size()];
        *output_item_ptr_ptr = new double *[result.size()];
        *output_items = result.size();

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
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TruncatedSVDFeaturizer_double_DestroyTransformedData(/*out*/ size_t result_cols, /*out*/ size_t result_rows, /*out*/ double * result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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


#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

} // extern "C"
