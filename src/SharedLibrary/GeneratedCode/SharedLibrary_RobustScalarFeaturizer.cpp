/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_RobustScalarFeaturizer.h"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "RobustScalarFeaturizer.h"

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
/* |  RobustScalarFeaturizer <int8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_int8_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_GetState(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_Fit(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_FitBuffer(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_OnDataCompleted(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_CompleteTraining(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_Transform(/*in*/ RobustScalarFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, float>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input));

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
/* |  RobustScalarFeaturizer <int16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_int16_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_GetState(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_Fit(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_FitBuffer(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_OnDataCompleted(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_CompleteTraining(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_Transform(/*in*/ RobustScalarFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, float>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input));

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
/* |  RobustScalarFeaturizer <uint8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_uint8_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_GetState(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_Fit(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_FitBuffer(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_OnDataCompleted(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_Transform(/*in*/ RobustScalarFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, float>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input));

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
/* |  RobustScalarFeaturizer <uint16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_uint16_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_GetState(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_Fit(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_FitBuffer(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_OnDataCompleted(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_Transform(/*in*/ RobustScalarFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, float>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input));

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
/* |  RobustScalarFeaturizer <float> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_float_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_DestroyEstimator(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_GetState(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_Fit(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_FitBuffer(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_OnDataCompleted(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_CompleteTraining(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_DestroyTransformer(/*in*/ RobustScalarFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_Transform(/*in*/ RobustScalarFeaturizer_float_TransformerHandle *pHandle, /*in*/ float input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, float>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input));

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
/* |  RobustScalarFeaturizer <int32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_int32_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_GetState(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_Fit(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_FitBuffer(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_OnDataCompleted(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_CompleteTraining(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_Transform(/*in*/ RobustScalarFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, double>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input));

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
/* |  RobustScalarFeaturizer <int64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_int64_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_GetState(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_Fit(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_FitBuffer(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_OnDataCompleted(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_CompleteTraining(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_Transform(/*in*/ RobustScalarFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, double>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input));

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
/* |  RobustScalarFeaturizer <uint32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_uint32_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_GetState(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_Fit(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_FitBuffer(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_OnDataCompleted(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_Transform(/*in*/ RobustScalarFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, double>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input));

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
/* |  RobustScalarFeaturizer <uint64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_uint64_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_GetState(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_Fit(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_FitBuffer(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_OnDataCompleted(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_Transform(/*in*/ RobustScalarFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, double>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input));

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
/* |  RobustScalarFeaturizer <double> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_double_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_DestroyEstimator(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_GetState(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_Fit(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_FitBuffer(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_OnDataCompleted(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_CompleteTraining(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_DestroyTransformer(/*in*/ RobustScalarFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_Transform(/*in*/ RobustScalarFeaturizer_double_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, double>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input));

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
