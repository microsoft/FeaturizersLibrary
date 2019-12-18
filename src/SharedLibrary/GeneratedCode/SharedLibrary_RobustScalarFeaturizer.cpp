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

extern "C" {

// I don't know why MSVC thinks that there is unreachable
// code in these methods during release builds.
#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4702) // Unreachable code
#endif

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  RobustScalarFeaturizer <int8_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_int8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_int8_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_GetState(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_Fit(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_FitBuffer(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*in*/ int8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_OnDataCompleted(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int8_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int8_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int8_t_Transform(/*in*/ RobustScalarFeaturizer_int8_t_TransformerHandle *pHandle, /*in*/ int8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int8_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  RobustScalarFeaturizer <int16_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_int16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_int16_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_GetState(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_Fit(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_FitBuffer(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*in*/ int16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_OnDataCompleted(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int16_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int16_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int16_t_Transform(/*in*/ RobustScalarFeaturizer_int16_t_TransformerHandle *pHandle, /*in*/ int16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int16_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  RobustScalarFeaturizer <uint8_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_uint8_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_GetState(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_Fit(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_FitBuffer(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*in*/ uint8_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_OnDataCompleted(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint8_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint8_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint8_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint8_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint8_t_Transform(/*in*/ RobustScalarFeaturizer_uint8_t_TransformerHandle *pHandle, /*in*/ uint8_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint8_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  RobustScalarFeaturizer <uint16_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_uint16_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_GetState(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_Fit(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_FitBuffer(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*in*/ uint16_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_OnDataCompleted(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint16_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint16_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint16_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint16_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint16_t_Transform(/*in*/ RobustScalarFeaturizer_uint16_t_TransformerHandle *pHandle, /*in*/ uint16_t input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint16_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  RobustScalarFeaturizer <float_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_float_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_float_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_GetState(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_Fit(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_FitBuffer(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*in*/ float const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_OnDataCompleted(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_float_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_float_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_float_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_float_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_float_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_float_t_Transform(/*in*/ RobustScalarFeaturizer_float_t_TransformerHandle *pHandle, /*in*/ float input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::float_t, std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  RobustScalarFeaturizer <int32_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_int32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_int32_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_GetState(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_Fit(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_FitBuffer(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*in*/ int32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_OnDataCompleted(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int32_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int32_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int32_t_Transform(/*in*/ RobustScalarFeaturizer_int32_t_TransformerHandle *pHandle, /*in*/ int32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int32_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  RobustScalarFeaturizer <int64_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_int64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_int64_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_GetState(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_Fit(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_FitBuffer(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*in*/ int64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_OnDataCompleted(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int64_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_int64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_int64_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_int64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_int64_t_Transform(/*in*/ RobustScalarFeaturizer_int64_t_TransformerHandle *pHandle, /*in*/ int64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::int64_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  RobustScalarFeaturizer <uint32_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_uint32_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_GetState(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_Fit(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_FitBuffer(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*in*/ uint32_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_OnDataCompleted(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint32_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint32_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint32_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint32_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint32_t_Transform(/*in*/ RobustScalarFeaturizer_uint32_t_TransformerHandle *pHandle, /*in*/ uint32_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint32_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  RobustScalarFeaturizer <uint64_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_uint64_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_GetState(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_Fit(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_FitBuffer(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*in*/ uint64_t const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_OnDataCompleted(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint64_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_uint64_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_uint64_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_uint64_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_uint64_t_Transform(/*in*/ RobustScalarFeaturizer_uint64_t_TransformerHandle *pHandle, /*in*/ uint64_t input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::uint64_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  RobustScalarFeaturizer <double_t> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_CreateEstimator(/*in*/ bool withCentering, /*in*/ float const * qRangeMin, /*in*/ float const * qRangeMax, /*out*/ RobustScalarFeaturizer_double_t_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , withCentering, qRangeMin != nullptr ? *qRangeMin : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue(), qRangeMax != nullptr ? *qRangeMax : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<RobustScalarFeaturizer_double_t_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_DestroyEstimator(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_GetState(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_IsTrainingComplete(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_Fit(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_FitBuffer(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*in*/ double const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_ptr, input_items));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_OnDataCompleted(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_CompleteTraining(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_CreateTransformerFromEstimator(/*in*/ RobustScalarFeaturizer_double_t_EstimatorHandle *pEstimatorHandle, /*out*/ RobustScalarFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_double_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ RobustScalarFeaturizer_double_t_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<RobustScalarFeaturizer_double_t_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_DestroyTransformer(/*in*/ RobustScalarFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_CreateTransformerSaveData(/*in*/ RobustScalarFeaturizer_double_t_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool RobustScalarFeaturizer_double_t_Transform(/*in*/ RobustScalarFeaturizer_double_t_TransformerHandle *pHandle, /*in*/ double input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::RobustScalarEstimator<std::double_t, std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
