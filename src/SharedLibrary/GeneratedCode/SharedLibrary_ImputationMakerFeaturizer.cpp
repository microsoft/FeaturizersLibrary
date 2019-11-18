/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_ImputationMakerFeaturizer.h"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "ImputationMakerFeaturizer.h"

// These method(s) are defined in SharedLibrary_Common.cpp
ErrorInfoHandle * CreateErrorInfo(std::exception const &ex);

extern "C" {

// I don't know why MSVC thinks that there is unreachable
// code in these methods during release builds.
#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4702) // Unreachable code
#endif

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  ImputationMakerFeaturizer <int8_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );
        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ImputationMakerFeaturizer_int8_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));


        *pIsTrainingComplete = estimator.is_training_complete();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_Fit(/*in*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int8_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        std::int8_t const * const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int8_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.complete_training());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_int8_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>::TransformerType>(archive).release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_int8_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int8_t_Transform(/*in*/ ImputationMakerFeaturizer_int8_t_TransformerHandle *pHandle, /*in*/ int8_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int8_t>::CreateNullValue()));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  ImputationMakerFeaturizer <int16_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );
        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ImputationMakerFeaturizer_int16_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));


        *pIsTrainingComplete = estimator.is_training_complete();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_Fit(/*in*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int16_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        std::int16_t const * const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int16_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.complete_training());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_int16_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>::TransformerType>(archive).release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_int16_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int16_t_Transform(/*in*/ ImputationMakerFeaturizer_int16_t_TransformerHandle *pHandle, /*in*/ int16_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int16_t>::CreateNullValue()));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  ImputationMakerFeaturizer <int32_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );
        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ImputationMakerFeaturizer_int32_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));


        *pIsTrainingComplete = estimator.is_training_complete();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_Fit(/*in*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int32_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        std::int32_t const * const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int32_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.complete_training());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_int32_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>::TransformerType>(archive).release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_int32_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int32_t_Transform(/*in*/ ImputationMakerFeaturizer_int32_t_TransformerHandle *pHandle, /*in*/ int32_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int32_t>::CreateNullValue()));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  ImputationMakerFeaturizer <int64_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );
        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ImputationMakerFeaturizer_int64_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));


        *pIsTrainingComplete = estimator.is_training_complete();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_Fit(/*in*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int64_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        std::int64_t const * const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int64_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.complete_training());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_int64_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>::TransformerType>(archive).release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_int64_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_int64_t_Transform(/*in*/ ImputationMakerFeaturizer_int64_t_TransformerHandle *pHandle, /*in*/ int64_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::int64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int64_t>::CreateNullValue()));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  ImputationMakerFeaturizer <uint8_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );
        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ImputationMakerFeaturizer_uint8_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));


        *pIsTrainingComplete = estimator.is_training_complete();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_Fit(/*in*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint8_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        std::uint8_t const * const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint8_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.complete_training());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_uint8_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>::TransformerType>(archive).release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_uint8_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint8_t_Transform(/*in*/ ImputationMakerFeaturizer_uint8_t_TransformerHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint8_t>::CreateNullValue()));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  ImputationMakerFeaturizer <uint16_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );
        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ImputationMakerFeaturizer_uint16_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));


        *pIsTrainingComplete = estimator.is_training_complete();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_Fit(/*in*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint16_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        std::uint16_t const * const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint16_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.complete_training());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_uint16_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>::TransformerType>(archive).release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_uint16_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint16_t_Transform(/*in*/ ImputationMakerFeaturizer_uint16_t_TransformerHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint16_t>::CreateNullValue()));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  ImputationMakerFeaturizer <uint32_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );
        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ImputationMakerFeaturizer_uint32_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));


        *pIsTrainingComplete = estimator.is_training_complete();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_Fit(/*in*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint32_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        std::uint32_t const * const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint32_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.complete_training());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_uint32_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>::TransformerType>(archive).release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_uint32_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint32_t_Transform(/*in*/ ImputationMakerFeaturizer_uint32_t_TransformerHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint32_t>::CreateNullValue()));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  ImputationMakerFeaturizer <uint64_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );
        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ImputationMakerFeaturizer_uint64_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));


        *pIsTrainingComplete = estimator.is_training_complete();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_Fit(/*in*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint64_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        std::uint64_t const * const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint64_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.complete_training());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_uint64_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>::TransformerType>(archive).release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_uint64_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_uint64_t_Transform(/*in*/ ImputationMakerFeaturizer_uint64_t_TransformerHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::uint64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint64_t>::CreateNullValue()));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  ImputationMakerFeaturizer <float_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_float_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );
        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ImputationMakerFeaturizer_float_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));


        *pIsTrainingComplete = estimator.is_training_complete();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_Fit(/*in*/ ImputationMakerFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Microsoft::Featurizer::Traits<std::float_t>::nullable_type> input_buffer;

        input_buffer.reserve(input_items);

        std::float_t const * const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.complete_training());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_float_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_float_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>::TransformerType>(archive).release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_float_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_float_t_Transform(/*in*/ ImputationMakerFeaturizer_float_t_TransformerHandle *pHandle, /*in*/ float const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue()));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  ImputationMakerFeaturizer <double_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_CreateEstimator(/*out*/ ImputationMakerFeaturizer_double_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );
        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ImputationMakerFeaturizer_double_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));


        *pIsTrainingComplete = estimator.is_training_complete();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_Fit(/*in*/ ImputationMakerFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::double_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_FitBuffer(/*in*/ ImputationMakerFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<Microsoft::Featurizer::Traits<std::double_t>::nullable_type> input_buffer;

        input_buffer.reserve(input_items);

        std::double_t const * const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::double_t>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_CompleteTraining(/*in*/ ImputationMakerFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.complete_training());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_double_t_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_double_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>::TransformerType>(archive).release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_double_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_double_t_Transform(/*in*/ ImputationMakerFeaturizer_double_t_TransformerHandle *pHandle, /*in*/ double const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::double_t>::CreateNullValue()));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  ImputationMakerFeaturizer <bool> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_CreateEstimator(/*out*/ ImputationMakerFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>* pEstimator = new Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );
        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ImputationMakerFeaturizer_bool_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));


        *pIsTrainingComplete = estimator.is_training_complete();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_Fit(/*in*/ ImputationMakerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<bool>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_FitBuffer(/*in*/ ImputationMakerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        bool const * const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<bool>::CreateNullValue());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_CompleteTraining(/*in*/ ImputationMakerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.complete_training());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_bool_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>::TransformerType>(archive).release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_bool_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_bool_Transform(/*in*/ ImputationMakerFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<bool>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input != nullptr ? *input : Microsoft::Featurizer::Traits<bool>::CreateNullValue()));

        // Output
        *output = result;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  ImputationMakerFeaturizer <string> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_CreateEstimator(/*out*/ ImputationMakerFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>* pEstimator = new Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1) );
        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ImputationMakerFeaturizer_string_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_DestroyEstimator(/*in*/ ImputationMakerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_IsTrainingComplete(/*in*/ ImputationMakerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));


        *pIsTrainingComplete = estimator.is_training_complete();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_Fit(/*in*/ ImputationMakerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input ? std::string(input) : nonstd::optional<std::string>()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_FitBuffer(/*in*/ ImputationMakerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        char const * const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
            input_buffer.emplace_back(*input_ptr ? *input_ptr : nonstd::optional<std::string>());
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_CompleteTraining(/*in*/ ImputationMakerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.complete_training());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_CreateTransformerFromEstimator(/*in*/ ImputationMakerFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ ImputationMakerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_string_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ImputationMakerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>::TransformerType* pTransformer= (std::make_unique<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>::TransformerType>(archive).release());

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ImputationMakerFeaturizer_string_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_DestroyTransformer(/*in*/ ImputationMakerFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_CreateTransformerSaveData(/*in*/ ImputationMakerFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ImputationMakerFeaturizer_string_Transform(/*in*/ ImputationMakerFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ImputationMakerEstimator<std::string>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input ? std::string(input) : nonstd::optional<std::string>()));

        // Output
        *output = result;
    
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
