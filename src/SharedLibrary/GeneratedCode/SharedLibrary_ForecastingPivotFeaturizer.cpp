/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_ForecastingPivotFeaturizer.h"
#include "SharedLibrary_Common.hpp"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "ForecastingPivotFeaturizer.h"

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
/* |  ForecastingPivotFeaturizer <float> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_CreateEstimator(/*out*/ ForecastingPivotFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>* pEstimator = new Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ForecastingPivotFeaturizer_float_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_DestroyEstimator(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_GetState(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_IsTrainingComplete(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_Fit(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*in*/ size_t const * input_cols_ptr, /*in*/ size_t const * input_rows_ptr, /*in*/ float const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_cols_ptr == nullptr) throw std::invalid_argument("'input_cols_ptr' is nullptr");
        if(input_rows_ptr == nullptr) throw std::invalid_argument("'input_rows_ptr' is nullptr");
        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            if(*input_cols_ptr == 0) throw std::invalid_argument("Invalid col element");
            if(*input_rows_ptr == 0) throw std::invalid_argument("Invalid row element");
            if(*input_values_ptr == nullptr) throw std::invalid_argument("Invalid values element");

            input_buffer.emplace_back(Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>>(const_cast<float *>(*input_values_ptr), static_cast<Eigen::Index>(*input_rows_ptr), static_cast<Eigen::Index>(*input_cols_ptr)));

            ++input_cols_ptr;
            ++input_rows_ptr;
            ++input_values_ptr;
        }

        using InputType = typename Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::InputType;

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input_buffer.data(), input_buffer.data() + input_buffer.size())));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_FitBuffer(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*in*/ size_t const * const * input_item_cols_ptr_ptr, /*in*/ size_t const * const * input_item_rows_ptr_ptr, /*in*/ float const ** const * input_item_values_ptr_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_item_cols_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_cols_ptr_ptr' is null");
        if(input_item_rows_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_rows_ptr_ptr' is null");
        if(input_item_values_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_values_ptr_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::vector<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>>>> input_temp_buffer;

        input_temp_buffer.reserve(input_items);

        while(input_temp_buffer.size() < input_items) {
            size_t const *input_item_cols_ptr(*input_item_cols_ptr_ptr);
            size_t const *input_item_rows_ptr(*input_item_rows_ptr_ptr);
            float const **input_item_values_ptr(*input_item_values_ptr_ptr);

            if(input_item_cols_ptr == nullptr) throw std::invalid_argument("'input_item_cols_ptr' is nullptr");
            if(input_item_rows_ptr == nullptr) throw std::invalid_argument("'input_item_rows_ptr' is nullptr");
            if(input_item_values_ptr == nullptr) throw std::invalid_argument("'input_item_values_ptr' is null");
            if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

            std::vector<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>>> input_item_buffer;

            input_item_buffer.reserve(input_items);

            while(input_item_buffer.size() < input_items) {
                if(*input_item_cols_ptr == 0) throw std::invalid_argument("Invalid col element");
                if(*input_item_rows_ptr == 0) throw std::invalid_argument("Invalid row element");
                if(*input_item_values_ptr == nullptr) throw std::invalid_argument("Invalid values element");

                input_item_buffer.emplace_back(Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>>(const_cast<float *>(*input_item_values_ptr), static_cast<Eigen::Index>(*input_item_rows_ptr), static_cast<Eigen::Index>(*input_item_cols_ptr)));

                ++input_item_cols_ptr;
                ++input_item_rows_ptr;
                ++input_item_values_ptr;
            }
            

            input_temp_buffer.emplace_back(std::move(input_item_buffer));

            ++input_item_cols_ptr_ptr;
            ++input_item_rows_ptr_ptr;
            ++input_item_values_ptr_ptr;
        }

        std::vector<std::tuple<typename std::vector<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>>>::const_pointer, typename std::vector<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>>>::const_pointer>> input_buffer;

        input_buffer.reserve(input_temp_buffer.size());

        for(auto const & input_temp_buffer_item : input_temp_buffer)
            input_buffer.emplace_back(input_temp_buffer_item.data(), input_temp_buffer_item.data() + input_temp_buffer_item.size());

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_OnDataCompleted(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_CompleteTraining(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_CreateTransformerFromEstimator(/*in*/ ForecastingPivotFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ ForecastingPivotFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ForecastingPivotFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForecastingPivotFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ForecastingPivotFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_DestroyTransformer(/*in*/ ForecastingPivotFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_CreateTransformerSaveData(/*in*/ ForecastingPivotFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_Transform(/*in*/ ForecastingPivotFeaturizer_float_TransformerHandle *pHandle, /*in*/ size_t const * input_cols_ptr, /*in*/ size_t const * input_rows_ptr, /*in*/ float const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ float *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_cols_ptr == nullptr) throw std::invalid_argument("'input_cols_ptr' is nullptr");
        if(input_rows_ptr == nullptr) throw std::invalid_argument("'input_rows_ptr' is nullptr");
        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            if(*input_cols_ptr == 0) throw std::invalid_argument("Invalid col element");
            if(*input_rows_ptr == 0) throw std::invalid_argument("Invalid row element");
            if(*input_values_ptr == nullptr) throw std::invalid_argument("Invalid values element");

            input_buffer.emplace_back(Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>>(const_cast<float *>(*input_values_ptr), static_cast<Eigen::Index>(*input_rows_ptr), static_cast<Eigen::Index>(*input_cols_ptr)));

            ++input_cols_ptr;
            ++input_rows_ptr;
            ++input_values_ptr;
        }
        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(std::make_tuple(input_buffer.data(), input_buffer.data() + input_buffer.size()), callback);

        // Output
        if(result.empty()) {
            *output_item_item_ptr_ptr = nullptr;
            *output_item_items_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_item_ptr_ptr = new float *[result.size()];
            *output_item_items_ptr = new size_t[result.size()];

            float ** output_item_item_ptr(*output_item_item_ptr_ptr);
            size_t * output_item_items(*output_item_items_ptr);

            for(auto const & result_item : result) {
                if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
                if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

                if(result_item.empty()) {
                    *output_item_item_ptr = nullptr;
                }
                else {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item_item_ptr = new float[result_item.size()];

                    float * output_item_item(*output_item_item_ptr);

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

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_Flush(/*in*/ ForecastingPivotFeaturizer_float_TransformerHandle *pHandle, /*out*/ float *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::float_t>> const *>>::TransformedType;

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
            *output_item_item_ptr_ptr = new float *[result.size()];
            *output_item_items_ptr = new size_t[result.size()];

            float ** output_item_item_ptr(*output_item_item_ptr_ptr);
            size_t * output_item_items(*output_item_items_ptr);

            for(auto const & result_item : result) {
                if(output_item_item_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr' is null");
                if(output_item_items == nullptr) throw std::invalid_argument("'output_item_items' is null");

                if(result_item.empty()) {
                    *output_item_item_ptr = nullptr;
                }
                else {
                    // TODO: There are potential memory leaks if allocation fails
                    *output_item_item_ptr = new float[result_item.size()];

                    float * output_item_item(*output_item_item_ptr);

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

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_float_DestroyTransformedData(/*out*/ float ** result_item_item_ptr_ptr, /*out*/ size_t * result_item_items_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_item_ptr_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_item_ptr_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_item_items_ptr) != bool(result_item_item_ptr_ptr)) throw std::invalid_argument("'result_item_items_ptr' is not internally consistent");
        if(bool(result_items) != bool(result_item_item_ptr_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_item_ptr_ptr != nullptr) {
            float ** this_result_item_item_ptr_ptr(result_item_item_ptr_ptr);
            size_t * this_result_item_items_ptr(result_item_items_ptr);

            while(result_items--) {
                float * const & result_destroy_item_item_ptr(*this_result_item_item_ptr_ptr);
                size_t const & result_destroy_item_items(*this_result_item_items_ptr);

                if(result_destroy_item_item_ptr != nullptr && result_destroy_item_items == 0) throw std::invalid_argument("'result_destroy_item_items' is 0");
                if(result_destroy_item_item_ptr == nullptr && result_destroy_item_items != 0) throw std::invalid_argument("'result_destroy_item_items' is not 0");
                if(bool(result_destroy_item_items) != bool(result_destroy_item_item_ptr)) throw std::invalid_argument("'result_destroy_item_items' is not internally consistent");

                if(result_destroy_item_item_ptr != nullptr) {
                    // No destroy statements

                    delete [] result_destroy_item_item_ptr;
                }

                ++this_result_item_item_ptr_ptr;
                ++this_result_item_items_ptr;
            }

            delete [] result_item_item_ptr_ptr;
            delete [] result_item_items_ptr;
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
/* |  ForecastingPivotFeaturizer <double> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_CreateEstimator(/*out*/ ForecastingPivotFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>* pEstimator = new Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ForecastingPivotFeaturizer_double_EstimatorHandle*>(index);

    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_DestroyEstimator(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_GetState(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_IsTrainingComplete(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_Fit(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*in*/ size_t const * input_cols_ptr, /*in*/ size_t const * input_rows_ptr, /*in*/ double const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_cols_ptr == nullptr) throw std::invalid_argument("'input_cols_ptr' is nullptr");
        if(input_rows_ptr == nullptr) throw std::invalid_argument("'input_rows_ptr' is nullptr");
        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            if(*input_cols_ptr == 0) throw std::invalid_argument("Invalid col element");
            if(*input_rows_ptr == 0) throw std::invalid_argument("Invalid row element");
            if(*input_values_ptr == nullptr) throw std::invalid_argument("Invalid values element");

            input_buffer.emplace_back(Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>>(const_cast<double *>(*input_values_ptr), static_cast<Eigen::Index>(*input_rows_ptr), static_cast<Eigen::Index>(*input_cols_ptr)));

            ++input_cols_ptr;
            ++input_rows_ptr;
            ++input_values_ptr;
        }

        using InputType = typename Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::InputType;

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(input_buffer.data(), input_buffer.data() + input_buffer.size())));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_FitBuffer(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*in*/ size_t const * const * input_item_cols_ptr_ptr, /*in*/ size_t const * const * input_item_rows_ptr_ptr, /*in*/ double const ** const * input_item_values_ptr_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input_item_cols_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_cols_ptr_ptr' is null");
        if(input_item_rows_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_rows_ptr_ptr' is null");
        if(input_item_values_ptr_ptr == nullptr) throw std::invalid_argument("'input_item_values_ptr_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::vector<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>>>> input_temp_buffer;

        input_temp_buffer.reserve(input_items);

        while(input_temp_buffer.size() < input_items) {
            size_t const *input_item_cols_ptr(*input_item_cols_ptr_ptr);
            size_t const *input_item_rows_ptr(*input_item_rows_ptr_ptr);
            double const **input_item_values_ptr(*input_item_values_ptr_ptr);

            if(input_item_cols_ptr == nullptr) throw std::invalid_argument("'input_item_cols_ptr' is nullptr");
            if(input_item_rows_ptr == nullptr) throw std::invalid_argument("'input_item_rows_ptr' is nullptr");
            if(input_item_values_ptr == nullptr) throw std::invalid_argument("'input_item_values_ptr' is null");
            if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

            std::vector<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>>> input_item_buffer;

            input_item_buffer.reserve(input_items);

            while(input_item_buffer.size() < input_items) {
                if(*input_item_cols_ptr == 0) throw std::invalid_argument("Invalid col element");
                if(*input_item_rows_ptr == 0) throw std::invalid_argument("Invalid row element");
                if(*input_item_values_ptr == nullptr) throw std::invalid_argument("Invalid values element");

                input_item_buffer.emplace_back(Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>>(const_cast<double *>(*input_item_values_ptr), static_cast<Eigen::Index>(*input_item_rows_ptr), static_cast<Eigen::Index>(*input_item_cols_ptr)));

                ++input_item_cols_ptr;
                ++input_item_rows_ptr;
                ++input_item_values_ptr;
            }
            

            input_temp_buffer.emplace_back(std::move(input_item_buffer));

            ++input_item_cols_ptr_ptr;
            ++input_item_rows_ptr_ptr;
            ++input_item_values_ptr_ptr;
        }

        std::vector<std::tuple<typename std::vector<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>>>::const_pointer, typename std::vector<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>>>::const_pointer>> input_buffer;

        input_buffer.reserve(input_temp_buffer.size());

        for(auto const & input_temp_buffer_item : input_temp_buffer)
            input_buffer.emplace_back(input_temp_buffer_item.data(), input_temp_buffer_item.data() + input_temp_buffer_item.size());

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_OnDataCompleted(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_CompleteTraining(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_CreateTransformerFromEstimator(/*in*/ ForecastingPivotFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ ForecastingPivotFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformerType*>(estimator.create_transformer().release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ForecastingPivotFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ ForecastingPivotFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ForecastingPivotFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_DestroyTransformer(/*in*/ ForecastingPivotFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformerType>(index);
        g_pointerTable.Remove(index);

        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_CreateTransformerSaveData(/*in*/ ForecastingPivotFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_Transform(/*in*/ ForecastingPivotFeaturizer_double_TransformerHandle *pHandle, /*in*/ size_t const * input_cols_ptr, /*in*/ size_t const * input_rows_ptr, /*in*/ double const ** input_values_ptr, /*in*/ size_t input_items, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(input_cols_ptr == nullptr) throw std::invalid_argument("'input_cols_ptr' is nullptr");
        if(input_rows_ptr == nullptr) throw std::invalid_argument("'input_rows_ptr' is nullptr");
        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>>> input_buffer;

        input_buffer.reserve(input_items);

        while(input_buffer.size() < input_items) {
            if(*input_cols_ptr == 0) throw std::invalid_argument("Invalid col element");
            if(*input_rows_ptr == 0) throw std::invalid_argument("Invalid row element");
            if(*input_values_ptr == nullptr) throw std::invalid_argument("Invalid values element");

            input_buffer.emplace_back(Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>>(const_cast<double *>(*input_values_ptr), static_cast<Eigen::Index>(*input_rows_ptr), static_cast<Eigen::Index>(*input_cols_ptr)));

            ++input_cols_ptr;
            ++input_rows_ptr;
            ++input_values_ptr;
        }
        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using InputType = typename Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformedType;

        // Input
        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.execute(std::make_tuple(input_buffer.data(), input_buffer.data() + input_buffer.size()), callback);

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

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_Flush(/*in*/ ForecastingPivotFeaturizer_double_TransformerHandle *pHandle, /*out*/ double *** output_item_item_ptr_ptr, /*out*/ size_t ** output_item_items_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_item_ptr_ptr == nullptr) throw std::invalid_argument("'output_item_item_ptr_ptr' is null");
        if(output_item_items_ptr == nullptr) throw std::invalid_argument("'output_item_items_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::ForecastingPivotEstimator<std::tuple<Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *, Eigen::Map<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const *>>::TransformedType;

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

FEATURIZER_LIBRARY_API bool ForecastingPivotFeaturizer_double_DestroyTransformedData(/*out*/ double ** result_item_item_ptr_ptr, /*out*/ size_t * result_item_items_ptr, /*out*/ size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_item_item_ptr_ptr != nullptr && result_items == 0) throw std::invalid_argument("'result_items' is 0");
        if(result_item_item_ptr_ptr == nullptr && result_items != 0) throw std::invalid_argument("'result_items' is not 0");
        if(bool(result_item_items_ptr) != bool(result_item_item_ptr_ptr)) throw std::invalid_argument("'result_item_items_ptr' is not internally consistent");
        if(bool(result_items) != bool(result_item_item_ptr_ptr)) throw std::invalid_argument("'result_items' is not internally consistent");

        if(result_item_item_ptr_ptr != nullptr) {
            double ** this_result_item_item_ptr_ptr(result_item_item_ptr_ptr);
            size_t * this_result_item_items_ptr(result_item_items_ptr);

            while(result_items--) {
                double * const & result_destroy_item_item_ptr(*this_result_item_item_ptr_ptr);
                size_t const & result_destroy_item_items(*this_result_item_items_ptr);

                if(result_destroy_item_item_ptr != nullptr && result_destroy_item_items == 0) throw std::invalid_argument("'result_destroy_item_items' is 0");
                if(result_destroy_item_item_ptr == nullptr && result_destroy_item_items != 0) throw std::invalid_argument("'result_destroy_item_items' is not 0");
                if(bool(result_destroy_item_items) != bool(result_destroy_item_item_ptr)) throw std::invalid_argument("'result_destroy_item_items' is not internally consistent");

                if(result_destroy_item_item_ptr != nullptr) {
                    // No destroy statements

                    delete [] result_destroy_item_item_ptr;
                }

                ++this_result_item_item_ptr_ptr;
                ++this_result_item_items_ptr;
            }

            delete [] result_item_item_ptr_ptr;
            delete [] result_item_items_ptr;
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
