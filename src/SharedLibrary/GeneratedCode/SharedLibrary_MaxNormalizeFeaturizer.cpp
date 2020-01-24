/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_MaxNormalizeFeaturizer.h"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "MaxNormalizeFeaturizer.h"

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
/* |  MaxNormalizeFeaturizer <int8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_CreateEstimator(/*out*/ MaxNormalizeFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxNormalizeFeaturizer_int8_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_DestroyEstimator(/*in*/ MaxNormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_GetState(/*in*/ MaxNormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_IsTrainingComplete(/*in*/ MaxNormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_Fit(/*in*/ MaxNormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(const_cast<int8_t *>(input_ptr), const_cast<int8_t *>(input_ptr) + input_elements)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_FitBuffer(/*in*/ MaxNormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const **input_values_ptr, /*in*/ size_t const *input_sizes_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_sizes_ptr == nullptr) throw std::invalid_argument("'input_sizes_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>>(reinterpret_cast<size_t>(pHandle)));

        std::vector<std::tuple<int8_t *, int8_t *>> input_buffer;

        input_buffer.reserve(input_elements);

        int8_t const * const * const input_values_end_ptr(input_values_ptr + input_elements);

        while(input_values_ptr != input_values_end_ptr) {
            input_buffer.emplace_back(const_cast<int8_t *>(*input_values_ptr), const_cast<int8_t *>(*input_values_ptr) + *input_sizes_ptr);
            ++input_values_ptr;
            ++input_sizes_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_OnDataCompleted(/*in*/ MaxNormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_CompleteTraining(/*in*/ MaxNormalizeFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ MaxNormalizeFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ MaxNormalizeFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxNormalizeFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_DestroyTransformer(/*in*/ MaxNormalizeFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_CreateTransformerSaveData(/*in*/ MaxNormalizeFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_Transform(/*in*/ MaxNormalizeFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ double **output_ptr, /*out*/ size_t *output_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");
        if(output_elements == nullptr) throw std::invalid_argument("'output_elements' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int8_t *, std::int8_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(std::make_tuple(const_cast<int8_t *>(input_ptr), const_cast<int8_t *>(input_ptr) + input_elements)));

        // Output
        if(result.empty()) {
            *output_ptr = nullptr;
            *output_elements = 0;
        }
        else {
            struct outputInternal {
                static void Deleter(double *pData) {
                    delete [] pData;
                }
            };

            std::unique_ptr<double, void (*)(double *)> pBuffer(new double[result.size()], outputInternal::Deleter);
            double * ptr(pBuffer.get());

            for(auto &value : result)
                *ptr++ = std::move(value);

            *output_ptr = pBuffer.release();
            *output_elements = result.size();
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int8_DestroyTransformedData(/*in*/ double *result_ptr, /*in*/ size_t result_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_elements != 0) throw std::invalid_argument("Invalid buffer");
        if(result_ptr != nullptr && result_elements == 0) throw std::invalid_argument("Invalid buffer");

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
/* |  MaxNormalizeFeaturizer <int16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_CreateEstimator(/*out*/ MaxNormalizeFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxNormalizeFeaturizer_int16_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_DestroyEstimator(/*in*/ MaxNormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_GetState(/*in*/ MaxNormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_IsTrainingComplete(/*in*/ MaxNormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_Fit(/*in*/ MaxNormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(const_cast<int16_t *>(input_ptr), const_cast<int16_t *>(input_ptr) + input_elements)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_FitBuffer(/*in*/ MaxNormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const **input_values_ptr, /*in*/ size_t const *input_sizes_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_sizes_ptr == nullptr) throw std::invalid_argument("'input_sizes_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>>(reinterpret_cast<size_t>(pHandle)));

        std::vector<std::tuple<int16_t *, int16_t *>> input_buffer;

        input_buffer.reserve(input_elements);

        int16_t const * const * const input_values_end_ptr(input_values_ptr + input_elements);

        while(input_values_ptr != input_values_end_ptr) {
            input_buffer.emplace_back(const_cast<int16_t *>(*input_values_ptr), const_cast<int16_t *>(*input_values_ptr) + *input_sizes_ptr);
            ++input_values_ptr;
            ++input_sizes_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_OnDataCompleted(/*in*/ MaxNormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_CompleteTraining(/*in*/ MaxNormalizeFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ MaxNormalizeFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ MaxNormalizeFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxNormalizeFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_DestroyTransformer(/*in*/ MaxNormalizeFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_CreateTransformerSaveData(/*in*/ MaxNormalizeFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_Transform(/*in*/ MaxNormalizeFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ double **output_ptr, /*out*/ size_t *output_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");
        if(output_elements == nullptr) throw std::invalid_argument("'output_elements' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int16_t *, std::int16_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(std::make_tuple(const_cast<int16_t *>(input_ptr), const_cast<int16_t *>(input_ptr) + input_elements)));

        // Output
        if(result.empty()) {
            *output_ptr = nullptr;
            *output_elements = 0;
        }
        else {
            struct outputInternal {
                static void Deleter(double *pData) {
                    delete [] pData;
                }
            };

            std::unique_ptr<double, void (*)(double *)> pBuffer(new double[result.size()], outputInternal::Deleter);
            double * ptr(pBuffer.get());

            for(auto &value : result)
                *ptr++ = std::move(value);

            *output_ptr = pBuffer.release();
            *output_elements = result.size();
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int16_DestroyTransformedData(/*in*/ double *result_ptr, /*in*/ size_t result_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_elements != 0) throw std::invalid_argument("Invalid buffer");
        if(result_ptr != nullptr && result_elements == 0) throw std::invalid_argument("Invalid buffer");

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
/* |  MaxNormalizeFeaturizer <int32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_CreateEstimator(/*out*/ MaxNormalizeFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxNormalizeFeaturizer_int32_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_DestroyEstimator(/*in*/ MaxNormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_GetState(/*in*/ MaxNormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_IsTrainingComplete(/*in*/ MaxNormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_Fit(/*in*/ MaxNormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(const_cast<int32_t *>(input_ptr), const_cast<int32_t *>(input_ptr) + input_elements)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_FitBuffer(/*in*/ MaxNormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const **input_values_ptr, /*in*/ size_t const *input_sizes_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_sizes_ptr == nullptr) throw std::invalid_argument("'input_sizes_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>>(reinterpret_cast<size_t>(pHandle)));

        std::vector<std::tuple<int32_t *, int32_t *>> input_buffer;

        input_buffer.reserve(input_elements);

        int32_t const * const * const input_values_end_ptr(input_values_ptr + input_elements);

        while(input_values_ptr != input_values_end_ptr) {
            input_buffer.emplace_back(const_cast<int32_t *>(*input_values_ptr), const_cast<int32_t *>(*input_values_ptr) + *input_sizes_ptr);
            ++input_values_ptr;
            ++input_sizes_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_OnDataCompleted(/*in*/ MaxNormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_CompleteTraining(/*in*/ MaxNormalizeFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ MaxNormalizeFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ MaxNormalizeFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxNormalizeFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_DestroyTransformer(/*in*/ MaxNormalizeFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_CreateTransformerSaveData(/*in*/ MaxNormalizeFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_Transform(/*in*/ MaxNormalizeFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ double **output_ptr, /*out*/ size_t *output_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");
        if(output_elements == nullptr) throw std::invalid_argument("'output_elements' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int32_t *, std::int32_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(std::make_tuple(const_cast<int32_t *>(input_ptr), const_cast<int32_t *>(input_ptr) + input_elements)));

        // Output
        if(result.empty()) {
            *output_ptr = nullptr;
            *output_elements = 0;
        }
        else {
            struct outputInternal {
                static void Deleter(double *pData) {
                    delete [] pData;
                }
            };

            std::unique_ptr<double, void (*)(double *)> pBuffer(new double[result.size()], outputInternal::Deleter);
            double * ptr(pBuffer.get());

            for(auto &value : result)
                *ptr++ = std::move(value);

            *output_ptr = pBuffer.release();
            *output_elements = result.size();
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int32_DestroyTransformedData(/*in*/ double *result_ptr, /*in*/ size_t result_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_elements != 0) throw std::invalid_argument("Invalid buffer");
        if(result_ptr != nullptr && result_elements == 0) throw std::invalid_argument("Invalid buffer");

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
/* |  MaxNormalizeFeaturizer <int64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_CreateEstimator(/*out*/ MaxNormalizeFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxNormalizeFeaturizer_int64_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_DestroyEstimator(/*in*/ MaxNormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_GetState(/*in*/ MaxNormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_IsTrainingComplete(/*in*/ MaxNormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_Fit(/*in*/ MaxNormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(const_cast<int64_t *>(input_ptr), const_cast<int64_t *>(input_ptr) + input_elements)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_FitBuffer(/*in*/ MaxNormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const **input_values_ptr, /*in*/ size_t const *input_sizes_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_sizes_ptr == nullptr) throw std::invalid_argument("'input_sizes_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>>(reinterpret_cast<size_t>(pHandle)));

        std::vector<std::tuple<int64_t *, int64_t *>> input_buffer;

        input_buffer.reserve(input_elements);

        int64_t const * const * const input_values_end_ptr(input_values_ptr + input_elements);

        while(input_values_ptr != input_values_end_ptr) {
            input_buffer.emplace_back(const_cast<int64_t *>(*input_values_ptr), const_cast<int64_t *>(*input_values_ptr) + *input_sizes_ptr);
            ++input_values_ptr;
            ++input_sizes_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_OnDataCompleted(/*in*/ MaxNormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_CompleteTraining(/*in*/ MaxNormalizeFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ MaxNormalizeFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ MaxNormalizeFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxNormalizeFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_DestroyTransformer(/*in*/ MaxNormalizeFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_CreateTransformerSaveData(/*in*/ MaxNormalizeFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_Transform(/*in*/ MaxNormalizeFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ double **output_ptr, /*out*/ size_t *output_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");
        if(output_elements == nullptr) throw std::invalid_argument("'output_elements' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::int64_t *, std::int64_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(std::make_tuple(const_cast<int64_t *>(input_ptr), const_cast<int64_t *>(input_ptr) + input_elements)));

        // Output
        if(result.empty()) {
            *output_ptr = nullptr;
            *output_elements = 0;
        }
        else {
            struct outputInternal {
                static void Deleter(double *pData) {
                    delete [] pData;
                }
            };

            std::unique_ptr<double, void (*)(double *)> pBuffer(new double[result.size()], outputInternal::Deleter);
            double * ptr(pBuffer.get());

            for(auto &value : result)
                *ptr++ = std::move(value);

            *output_ptr = pBuffer.release();
            *output_elements = result.size();
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_int64_DestroyTransformedData(/*in*/ double *result_ptr, /*in*/ size_t result_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_elements != 0) throw std::invalid_argument("Invalid buffer");
        if(result_ptr != nullptr && result_elements == 0) throw std::invalid_argument("Invalid buffer");

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
/* |  MaxNormalizeFeaturizer <uint8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_CreateEstimator(/*out*/ MaxNormalizeFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxNormalizeFeaturizer_uint8_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_DestroyEstimator(/*in*/ MaxNormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_GetState(/*in*/ MaxNormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_IsTrainingComplete(/*in*/ MaxNormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_Fit(/*in*/ MaxNormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(const_cast<uint8_t *>(input_ptr), const_cast<uint8_t *>(input_ptr) + input_elements)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_FitBuffer(/*in*/ MaxNormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const **input_values_ptr, /*in*/ size_t const *input_sizes_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_sizes_ptr == nullptr) throw std::invalid_argument("'input_sizes_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>>(reinterpret_cast<size_t>(pHandle)));

        std::vector<std::tuple<uint8_t *, uint8_t *>> input_buffer;

        input_buffer.reserve(input_elements);

        uint8_t const * const * const input_values_end_ptr(input_values_ptr + input_elements);

        while(input_values_ptr != input_values_end_ptr) {
            input_buffer.emplace_back(const_cast<uint8_t *>(*input_values_ptr), const_cast<uint8_t *>(*input_values_ptr) + *input_sizes_ptr);
            ++input_values_ptr;
            ++input_sizes_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_OnDataCompleted(/*in*/ MaxNormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_CompleteTraining(/*in*/ MaxNormalizeFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ MaxNormalizeFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ MaxNormalizeFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxNormalizeFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_DestroyTransformer(/*in*/ MaxNormalizeFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_CreateTransformerSaveData(/*in*/ MaxNormalizeFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_Transform(/*in*/ MaxNormalizeFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ double **output_ptr, /*out*/ size_t *output_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");
        if(output_elements == nullptr) throw std::invalid_argument("'output_elements' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint8_t *, std::uint8_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(std::make_tuple(const_cast<uint8_t *>(input_ptr), const_cast<uint8_t *>(input_ptr) + input_elements)));

        // Output
        if(result.empty()) {
            *output_ptr = nullptr;
            *output_elements = 0;
        }
        else {
            struct outputInternal {
                static void Deleter(double *pData) {
                    delete [] pData;
                }
            };

            std::unique_ptr<double, void (*)(double *)> pBuffer(new double[result.size()], outputInternal::Deleter);
            double * ptr(pBuffer.get());

            for(auto &value : result)
                *ptr++ = std::move(value);

            *output_ptr = pBuffer.release();
            *output_elements = result.size();
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint8_DestroyTransformedData(/*in*/ double *result_ptr, /*in*/ size_t result_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_elements != 0) throw std::invalid_argument("Invalid buffer");
        if(result_ptr != nullptr && result_elements == 0) throw std::invalid_argument("Invalid buffer");

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
/* |  MaxNormalizeFeaturizer <uint16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_CreateEstimator(/*out*/ MaxNormalizeFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxNormalizeFeaturizer_uint16_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_DestroyEstimator(/*in*/ MaxNormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_GetState(/*in*/ MaxNormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_IsTrainingComplete(/*in*/ MaxNormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_Fit(/*in*/ MaxNormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(const_cast<uint16_t *>(input_ptr), const_cast<uint16_t *>(input_ptr) + input_elements)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_FitBuffer(/*in*/ MaxNormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const **input_values_ptr, /*in*/ size_t const *input_sizes_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_sizes_ptr == nullptr) throw std::invalid_argument("'input_sizes_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>>(reinterpret_cast<size_t>(pHandle)));

        std::vector<std::tuple<uint16_t *, uint16_t *>> input_buffer;

        input_buffer.reserve(input_elements);

        uint16_t const * const * const input_values_end_ptr(input_values_ptr + input_elements);

        while(input_values_ptr != input_values_end_ptr) {
            input_buffer.emplace_back(const_cast<uint16_t *>(*input_values_ptr), const_cast<uint16_t *>(*input_values_ptr) + *input_sizes_ptr);
            ++input_values_ptr;
            ++input_sizes_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_OnDataCompleted(/*in*/ MaxNormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_CompleteTraining(/*in*/ MaxNormalizeFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ MaxNormalizeFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ MaxNormalizeFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxNormalizeFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_DestroyTransformer(/*in*/ MaxNormalizeFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_CreateTransformerSaveData(/*in*/ MaxNormalizeFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_Transform(/*in*/ MaxNormalizeFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ double **output_ptr, /*out*/ size_t *output_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");
        if(output_elements == nullptr) throw std::invalid_argument("'output_elements' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint16_t *, std::uint16_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(std::make_tuple(const_cast<uint16_t *>(input_ptr), const_cast<uint16_t *>(input_ptr) + input_elements)));

        // Output
        if(result.empty()) {
            *output_ptr = nullptr;
            *output_elements = 0;
        }
        else {
            struct outputInternal {
                static void Deleter(double *pData) {
                    delete [] pData;
                }
            };

            std::unique_ptr<double, void (*)(double *)> pBuffer(new double[result.size()], outputInternal::Deleter);
            double * ptr(pBuffer.get());

            for(auto &value : result)
                *ptr++ = std::move(value);

            *output_ptr = pBuffer.release();
            *output_elements = result.size();
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint16_DestroyTransformedData(/*in*/ double *result_ptr, /*in*/ size_t result_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_elements != 0) throw std::invalid_argument("Invalid buffer");
        if(result_ptr != nullptr && result_elements == 0) throw std::invalid_argument("Invalid buffer");

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
/* |  MaxNormalizeFeaturizer <uint32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_CreateEstimator(/*out*/ MaxNormalizeFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxNormalizeFeaturizer_uint32_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_DestroyEstimator(/*in*/ MaxNormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_GetState(/*in*/ MaxNormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_IsTrainingComplete(/*in*/ MaxNormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_Fit(/*in*/ MaxNormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(const_cast<uint32_t *>(input_ptr), const_cast<uint32_t *>(input_ptr) + input_elements)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_FitBuffer(/*in*/ MaxNormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const **input_values_ptr, /*in*/ size_t const *input_sizes_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_sizes_ptr == nullptr) throw std::invalid_argument("'input_sizes_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>>(reinterpret_cast<size_t>(pHandle)));

        std::vector<std::tuple<uint32_t *, uint32_t *>> input_buffer;

        input_buffer.reserve(input_elements);

        uint32_t const * const * const input_values_end_ptr(input_values_ptr + input_elements);

        while(input_values_ptr != input_values_end_ptr) {
            input_buffer.emplace_back(const_cast<uint32_t *>(*input_values_ptr), const_cast<uint32_t *>(*input_values_ptr) + *input_sizes_ptr);
            ++input_values_ptr;
            ++input_sizes_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_OnDataCompleted(/*in*/ MaxNormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_CompleteTraining(/*in*/ MaxNormalizeFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ MaxNormalizeFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ MaxNormalizeFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxNormalizeFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_DestroyTransformer(/*in*/ MaxNormalizeFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_CreateTransformerSaveData(/*in*/ MaxNormalizeFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_Transform(/*in*/ MaxNormalizeFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ double **output_ptr, /*out*/ size_t *output_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");
        if(output_elements == nullptr) throw std::invalid_argument("'output_elements' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint32_t *, std::uint32_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(std::make_tuple(const_cast<uint32_t *>(input_ptr), const_cast<uint32_t *>(input_ptr) + input_elements)));

        // Output
        if(result.empty()) {
            *output_ptr = nullptr;
            *output_elements = 0;
        }
        else {
            struct outputInternal {
                static void Deleter(double *pData) {
                    delete [] pData;
                }
            };

            std::unique_ptr<double, void (*)(double *)> pBuffer(new double[result.size()], outputInternal::Deleter);
            double * ptr(pBuffer.get());

            for(auto &value : result)
                *ptr++ = std::move(value);

            *output_ptr = pBuffer.release();
            *output_elements = result.size();
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint32_DestroyTransformedData(/*in*/ double *result_ptr, /*in*/ size_t result_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_elements != 0) throw std::invalid_argument("Invalid buffer");
        if(result_ptr != nullptr && result_elements == 0) throw std::invalid_argument("Invalid buffer");

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
/* |  MaxNormalizeFeaturizer <uint64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_CreateEstimator(/*out*/ MaxNormalizeFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxNormalizeFeaturizer_uint64_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_DestroyEstimator(/*in*/ MaxNormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_GetState(/*in*/ MaxNormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_IsTrainingComplete(/*in*/ MaxNormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_Fit(/*in*/ MaxNormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(const_cast<uint64_t *>(input_ptr), const_cast<uint64_t *>(input_ptr) + input_elements)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_FitBuffer(/*in*/ MaxNormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const **input_values_ptr, /*in*/ size_t const *input_sizes_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_sizes_ptr == nullptr) throw std::invalid_argument("'input_sizes_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>>(reinterpret_cast<size_t>(pHandle)));

        std::vector<std::tuple<uint64_t *, uint64_t *>> input_buffer;

        input_buffer.reserve(input_elements);

        uint64_t const * const * const input_values_end_ptr(input_values_ptr + input_elements);

        while(input_values_ptr != input_values_end_ptr) {
            input_buffer.emplace_back(const_cast<uint64_t *>(*input_values_ptr), const_cast<uint64_t *>(*input_values_ptr) + *input_sizes_ptr);
            ++input_values_ptr;
            ++input_sizes_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_OnDataCompleted(/*in*/ MaxNormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_CompleteTraining(/*in*/ MaxNormalizeFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ MaxNormalizeFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ MaxNormalizeFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxNormalizeFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_DestroyTransformer(/*in*/ MaxNormalizeFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_CreateTransformerSaveData(/*in*/ MaxNormalizeFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_Transform(/*in*/ MaxNormalizeFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t const *input_ptr, /*in*/ size_t input_elements, /*out*/ double **output_ptr, /*out*/ size_t *output_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");
        if(output_elements == nullptr) throw std::invalid_argument("'output_elements' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::uint64_t *, std::uint64_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(std::make_tuple(const_cast<uint64_t *>(input_ptr), const_cast<uint64_t *>(input_ptr) + input_elements)));

        // Output
        if(result.empty()) {
            *output_ptr = nullptr;
            *output_elements = 0;
        }
        else {
            struct outputInternal {
                static void Deleter(double *pData) {
                    delete [] pData;
                }
            };

            std::unique_ptr<double, void (*)(double *)> pBuffer(new double[result.size()], outputInternal::Deleter);
            double * ptr(pBuffer.get());

            for(auto &value : result)
                *ptr++ = std::move(value);

            *output_ptr = pBuffer.release();
            *output_elements = result.size();
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_uint64_DestroyTransformedData(/*in*/ double *result_ptr, /*in*/ size_t result_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_elements != 0) throw std::invalid_argument("Invalid buffer");
        if(result_ptr != nullptr && result_elements == 0) throw std::invalid_argument("Invalid buffer");

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
/* |  MaxNormalizeFeaturizer <float> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_CreateEstimator(/*out*/ MaxNormalizeFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxNormalizeFeaturizer_float_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_DestroyEstimator(/*in*/ MaxNormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_GetState(/*in*/ MaxNormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_IsTrainingComplete(/*in*/ MaxNormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_Fit(/*in*/ MaxNormalizeFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const *input_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(const_cast<float *>(input_ptr), const_cast<float *>(input_ptr) + input_elements)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_FitBuffer(/*in*/ MaxNormalizeFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const **input_values_ptr, /*in*/ size_t const *input_sizes_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_sizes_ptr == nullptr) throw std::invalid_argument("'input_sizes_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>>(reinterpret_cast<size_t>(pHandle)));

        std::vector<std::tuple<float *, float *>> input_buffer;

        input_buffer.reserve(input_elements);

        float const * const * const input_values_end_ptr(input_values_ptr + input_elements);

        while(input_values_ptr != input_values_end_ptr) {
            input_buffer.emplace_back(const_cast<float *>(*input_values_ptr), const_cast<float *>(*input_values_ptr) + *input_sizes_ptr);
            ++input_values_ptr;
            ++input_sizes_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_OnDataCompleted(/*in*/ MaxNormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_CompleteTraining(/*in*/ MaxNormalizeFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_CreateTransformerFromEstimator(/*in*/ MaxNormalizeFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ MaxNormalizeFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxNormalizeFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_DestroyTransformer(/*in*/ MaxNormalizeFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_CreateTransformerSaveData(/*in*/ MaxNormalizeFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_Transform(/*in*/ MaxNormalizeFeaturizer_float_TransformerHandle *pHandle, /*in*/ float const *input_ptr, /*in*/ size_t input_elements, /*out*/ double **output_ptr, /*out*/ size_t *output_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");
        if(output_elements == nullptr) throw std::invalid_argument("'output_elements' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::float_t *, std::float_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(std::make_tuple(const_cast<float *>(input_ptr), const_cast<float *>(input_ptr) + input_elements)));

        // Output
        if(result.empty()) {
            *output_ptr = nullptr;
            *output_elements = 0;
        }
        else {
            struct outputInternal {
                static void Deleter(double *pData) {
                    delete [] pData;
                }
            };

            std::unique_ptr<double, void (*)(double *)> pBuffer(new double[result.size()], outputInternal::Deleter);
            double * ptr(pBuffer.get());

            for(auto &value : result)
                *ptr++ = std::move(value);

            *output_ptr = pBuffer.release();
            *output_elements = result.size();
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_float_DestroyTransformedData(/*in*/ double *result_ptr, /*in*/ size_t result_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_elements != 0) throw std::invalid_argument("Invalid buffer");
        if(result_ptr != nullptr && result_elements == 0) throw std::invalid_argument("Invalid buffer");

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
/* |  MaxNormalizeFeaturizer <double> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_CreateEstimator(/*out*/ MaxNormalizeFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>* pEstimator = new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<MaxNormalizeFeaturizer_double_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_DestroyEstimator(/*in*/ MaxNormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_GetState(/*in*/ MaxNormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_IsTrainingComplete(/*in*/ MaxNormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_Fit(/*in*/ MaxNormalizeFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const *input_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(std::make_tuple(const_cast<double *>(input_ptr), const_cast<double *>(input_ptr) + input_elements)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_FitBuffer(/*in*/ MaxNormalizeFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const **input_values_ptr, /*in*/ size_t const *input_sizes_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_sizes_ptr == nullptr) throw std::invalid_argument("'input_sizes_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>>(reinterpret_cast<size_t>(pHandle)));

        std::vector<std::tuple<double *, double *>> input_buffer;

        input_buffer.reserve(input_elements);

        double const * const * const input_values_end_ptr(input_values_ptr + input_elements);

        while(input_values_ptr != input_values_end_ptr) {
            input_buffer.emplace_back(const_cast<double *>(*input_values_ptr), const_cast<double *>(*input_values_ptr) + *input_sizes_ptr);
            ++input_values_ptr;
            ++input_sizes_ptr;
        }

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_OnDataCompleted(/*in*/ MaxNormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_CompleteTraining(/*in*/ MaxNormalizeFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_CreateTransformerFromEstimator(/*in*/ MaxNormalizeFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ MaxNormalizeFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ MaxNormalizeFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<MaxNormalizeFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_DestroyTransformer(/*in*/ MaxNormalizeFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_CreateTransformerSaveData(/*in*/ MaxNormalizeFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_Transform(/*in*/ MaxNormalizeFeaturizer_double_TransformerHandle *pHandle, /*in*/ double const *input_ptr, /*in*/ size_t input_elements, /*out*/ double **output_ptr, /*out*/ size_t *output_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");
        if(output_elements == nullptr) throw std::invalid_argument("'output_elements' is null");

        Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::MaxNormalizeEstimator<std::tuple<std::double_t *, std::double_t *>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(std::make_tuple(const_cast<double *>(input_ptr), const_cast<double *>(input_ptr) + input_elements)));

        // Output
        if(result.empty()) {
            *output_ptr = nullptr;
            *output_elements = 0;
        }
        else {
            struct outputInternal {
                static void Deleter(double *pData) {
                    delete [] pData;
                }
            };

            std::unique_ptr<double, void (*)(double *)> pBuffer(new double[result.size()], outputInternal::Deleter);
            double * ptr(pBuffer.get());

            for(auto &value : result)
                *ptr++ = std::move(value);

            *output_ptr = pBuffer.release();
            *output_elements = result.size();
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool MaxNormalizeFeaturizer_double_DestroyTransformedData(/*in*/ double *result_ptr, /*in*/ size_t result_elements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_elements != 0) throw std::invalid_argument("Invalid buffer");
        if(result_ptr != nullptr && result_elements == 0) throw std::invalid_argument("Invalid buffer");

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
