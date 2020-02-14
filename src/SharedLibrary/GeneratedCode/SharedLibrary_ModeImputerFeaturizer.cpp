/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_ModeImputerFeaturizer.h"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "ModeImputerFeaturizer.h"

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
/* |  ModeImputerFeaturizer <int8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int8_CreateEstimator(/*out*/ ModeImputerFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ModeImputerFeaturizer_int8_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int8_DestroyEstimator(/*in*/ ModeImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int8_GetState(/*in*/ ModeImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int8_IsTrainingComplete(/*in*/ ModeImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int8_Fit(/*in*/ ModeImputerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int8_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int8_FitBuffer(/*in*/ ModeImputerFeaturizer_int8_EstimatorHandle *pHandle, /*in*/ int8_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
            input_buffer.push_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int8_t>::CreateNullValue());
        #else
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int8_t>::CreateNullValue());
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int8_OnDataCompleted(/*in*/ ModeImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int8_CompleteTraining(/*in*/ ModeImputerFeaturizer_int8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int8_CreateTransformerFromEstimator(/*in*/ ModeImputerFeaturizer_int8_EstimatorHandle *pEstimatorHandle, /*out*/ ModeImputerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ModeImputerFeaturizer_int8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_int8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int8_DestroyTransformer(/*in*/ ModeImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int8_CreateTransformerSaveData(/*in*/ ModeImputerFeaturizer_int8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int8_Transform(/*in*/ ModeImputerFeaturizer_int8_TransformerHandle *pHandle, /*in*/ int8_t const * input, /*out*/ int8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  ModeImputerFeaturizer <int16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int16_CreateEstimator(/*out*/ ModeImputerFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ModeImputerFeaturizer_int16_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int16_DestroyEstimator(/*in*/ ModeImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int16_GetState(/*in*/ ModeImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int16_IsTrainingComplete(/*in*/ ModeImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int16_Fit(/*in*/ ModeImputerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int16_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int16_FitBuffer(/*in*/ ModeImputerFeaturizer_int16_EstimatorHandle *pHandle, /*in*/ int16_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
            input_buffer.push_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int16_t>::CreateNullValue());
        #else
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int16_t>::CreateNullValue());
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int16_OnDataCompleted(/*in*/ ModeImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int16_CompleteTraining(/*in*/ ModeImputerFeaturizer_int16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int16_CreateTransformerFromEstimator(/*in*/ ModeImputerFeaturizer_int16_EstimatorHandle *pEstimatorHandle, /*out*/ ModeImputerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ModeImputerFeaturizer_int16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_int16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int16_DestroyTransformer(/*in*/ ModeImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int16_CreateTransformerSaveData(/*in*/ ModeImputerFeaturizer_int16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int16_Transform(/*in*/ ModeImputerFeaturizer_int16_TransformerHandle *pHandle, /*in*/ int16_t const * input, /*out*/ int16_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  ModeImputerFeaturizer <int32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int32_CreateEstimator(/*out*/ ModeImputerFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ModeImputerFeaturizer_int32_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int32_DestroyEstimator(/*in*/ ModeImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int32_GetState(/*in*/ ModeImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int32_IsTrainingComplete(/*in*/ ModeImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int32_Fit(/*in*/ ModeImputerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int32_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int32_FitBuffer(/*in*/ ModeImputerFeaturizer_int32_EstimatorHandle *pHandle, /*in*/ int32_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
            input_buffer.push_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int32_t>::CreateNullValue());
        #else
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int32_t>::CreateNullValue());
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int32_OnDataCompleted(/*in*/ ModeImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int32_CompleteTraining(/*in*/ ModeImputerFeaturizer_int32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int32_CreateTransformerFromEstimator(/*in*/ ModeImputerFeaturizer_int32_EstimatorHandle *pEstimatorHandle, /*out*/ ModeImputerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ModeImputerFeaturizer_int32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_int32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int32_DestroyTransformer(/*in*/ ModeImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int32_CreateTransformerSaveData(/*in*/ ModeImputerFeaturizer_int32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int32_Transform(/*in*/ ModeImputerFeaturizer_int32_TransformerHandle *pHandle, /*in*/ int32_t const * input, /*out*/ int32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  ModeImputerFeaturizer <int64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int64_CreateEstimator(/*out*/ ModeImputerFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ModeImputerFeaturizer_int64_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int64_DestroyEstimator(/*in*/ ModeImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int64_GetState(/*in*/ ModeImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int64_IsTrainingComplete(/*in*/ ModeImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int64_Fit(/*in*/ ModeImputerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::int64_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int64_FitBuffer(/*in*/ ModeImputerFeaturizer_int64_EstimatorHandle *pHandle, /*in*/ int64_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
            input_buffer.push_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int64_t>::CreateNullValue());
        #else
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::int64_t>::CreateNullValue());
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int64_OnDataCompleted(/*in*/ ModeImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int64_CompleteTraining(/*in*/ ModeImputerFeaturizer_int64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int64_CreateTransformerFromEstimator(/*in*/ ModeImputerFeaturizer_int64_EstimatorHandle *pEstimatorHandle, /*out*/ ModeImputerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ModeImputerFeaturizer_int64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_int64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int64_DestroyTransformer(/*in*/ ModeImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int64_CreateTransformerSaveData(/*in*/ ModeImputerFeaturizer_int64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_int64_Transform(/*in*/ ModeImputerFeaturizer_int64_TransformerHandle *pHandle, /*in*/ int64_t const * input, /*out*/ int64_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::int64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  ModeImputerFeaturizer <uint8> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint8_CreateEstimator(/*out*/ ModeImputerFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ModeImputerFeaturizer_uint8_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint8_DestroyEstimator(/*in*/ ModeImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint8_GetState(/*in*/ ModeImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint8_IsTrainingComplete(/*in*/ ModeImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint8_Fit(/*in*/ ModeImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint8_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint8_FitBuffer(/*in*/ ModeImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*in*/ uint8_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
            input_buffer.push_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint8_t>::CreateNullValue());
        #else
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint8_t>::CreateNullValue());
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint8_OnDataCompleted(/*in*/ ModeImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint8_CompleteTraining(/*in*/ ModeImputerFeaturizer_uint8_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint8_CreateTransformerFromEstimator(/*in*/ ModeImputerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle, /*out*/ ModeImputerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint8_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ModeImputerFeaturizer_uint8_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_uint8_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint8_DestroyTransformer(/*in*/ ModeImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint8_CreateTransformerSaveData(/*in*/ ModeImputerFeaturizer_uint8_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint8_Transform(/*in*/ ModeImputerFeaturizer_uint8_TransformerHandle *pHandle, /*in*/ uint8_t const * input, /*out*/ uint8_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint8_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  ModeImputerFeaturizer <uint16> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint16_CreateEstimator(/*out*/ ModeImputerFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ModeImputerFeaturizer_uint16_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint16_DestroyEstimator(/*in*/ ModeImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint16_GetState(/*in*/ ModeImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint16_IsTrainingComplete(/*in*/ ModeImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint16_Fit(/*in*/ ModeImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint16_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint16_FitBuffer(/*in*/ ModeImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*in*/ uint16_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
            input_buffer.push_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint16_t>::CreateNullValue());
        #else
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint16_t>::CreateNullValue());
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint16_OnDataCompleted(/*in*/ ModeImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint16_CompleteTraining(/*in*/ ModeImputerFeaturizer_uint16_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint16_CreateTransformerFromEstimator(/*in*/ ModeImputerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle, /*out*/ ModeImputerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint16_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ModeImputerFeaturizer_uint16_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_uint16_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint16_DestroyTransformer(/*in*/ ModeImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint16_CreateTransformerSaveData(/*in*/ ModeImputerFeaturizer_uint16_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint16_Transform(/*in*/ ModeImputerFeaturizer_uint16_TransformerHandle *pHandle, /*in*/ uint16_t const * input, /*out*/ uint16_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint16_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  ModeImputerFeaturizer <uint32> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint32_CreateEstimator(/*out*/ ModeImputerFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ModeImputerFeaturizer_uint32_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint32_DestroyEstimator(/*in*/ ModeImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint32_GetState(/*in*/ ModeImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint32_IsTrainingComplete(/*in*/ ModeImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint32_Fit(/*in*/ ModeImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint32_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint32_FitBuffer(/*in*/ ModeImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*in*/ uint32_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
            input_buffer.push_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint32_t>::CreateNullValue());
        #else
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint32_t>::CreateNullValue());
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint32_OnDataCompleted(/*in*/ ModeImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint32_CompleteTraining(/*in*/ ModeImputerFeaturizer_uint32_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint32_CreateTransformerFromEstimator(/*in*/ ModeImputerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle, /*out*/ ModeImputerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint32_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ModeImputerFeaturizer_uint32_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_uint32_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint32_DestroyTransformer(/*in*/ ModeImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint32_CreateTransformerSaveData(/*in*/ ModeImputerFeaturizer_uint32_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint32_Transform(/*in*/ ModeImputerFeaturizer_uint32_TransformerHandle *pHandle, /*in*/ uint32_t const * input, /*out*/ uint32_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint32_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  ModeImputerFeaturizer <uint64> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint64_CreateEstimator(/*out*/ ModeImputerFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ModeImputerFeaturizer_uint64_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint64_DestroyEstimator(/*in*/ ModeImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint64_GetState(/*in*/ ModeImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint64_IsTrainingComplete(/*in*/ ModeImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint64_Fit(/*in*/ ModeImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::uint64_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint64_FitBuffer(/*in*/ ModeImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*in*/ uint64_t const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
            input_buffer.push_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint64_t>::CreateNullValue());
        #else
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::uint64_t>::CreateNullValue());
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint64_OnDataCompleted(/*in*/ ModeImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint64_CompleteTraining(/*in*/ ModeImputerFeaturizer_uint64_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint64_CreateTransformerFromEstimator(/*in*/ ModeImputerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle, /*out*/ ModeImputerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint64_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ModeImputerFeaturizer_uint64_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_uint64_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint64_DestroyTransformer(/*in*/ ModeImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint64_CreateTransformerSaveData(/*in*/ ModeImputerFeaturizer_uint64_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_uint64_Transform(/*in*/ ModeImputerFeaturizer_uint64_TransformerHandle *pHandle, /*in*/ uint64_t const * input, /*out*/ uint64_t * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::uint64_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  ModeImputerFeaturizer <float> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_float_CreateEstimator(/*out*/ ModeImputerFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ModeImputerFeaturizer_float_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_float_DestroyEstimator(/*in*/ ModeImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_float_GetState(/*in*/ ModeImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_float_IsTrainingComplete(/*in*/ ModeImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_float_Fit(/*in*/ ModeImputerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_float_FitBuffer(/*in*/ ModeImputerFeaturizer_float_EstimatorHandle *pHandle, /*in*/ float const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
            input_buffer.push_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());
        #else
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::float_t>::CreateNullValue());
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_float_OnDataCompleted(/*in*/ ModeImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_float_CompleteTraining(/*in*/ ModeImputerFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_float_CreateTransformerFromEstimator(/*in*/ ModeImputerFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ ModeImputerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ModeImputerFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_float_DestroyTransformer(/*in*/ ModeImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_float_CreateTransformerSaveData(/*in*/ ModeImputerFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_float_Transform(/*in*/ ModeImputerFeaturizer_float_TransformerHandle *pHandle, /*in*/ float const * input, /*out*/ float * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::float_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  ModeImputerFeaturizer <double> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_double_CreateEstimator(/*out*/ ModeImputerFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>* pEstimator = new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ModeImputerFeaturizer_double_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_double_DestroyEstimator(/*in*/ ModeImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_double_GetState(/*in*/ ModeImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_double_IsTrainingComplete(/*in*/ ModeImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_double_Fit(/*in*/ ModeImputerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<std::double_t>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_double_FitBuffer(/*in*/ ModeImputerFeaturizer_double_EstimatorHandle *pHandle, /*in*/ double const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
            input_buffer.push_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::double_t>::CreateNullValue());
        #else
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<std::double_t>::CreateNullValue());
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_double_OnDataCompleted(/*in*/ ModeImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_double_CompleteTraining(/*in*/ ModeImputerFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_double_CreateTransformerFromEstimator(/*in*/ ModeImputerFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ ModeImputerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ModeImputerFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_double_DestroyTransformer(/*in*/ ModeImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_double_CreateTransformerSaveData(/*in*/ ModeImputerFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_double_Transform(/*in*/ ModeImputerFeaturizer_double_TransformerHandle *pHandle, /*in*/ double const * input, /*out*/ double * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::double_t>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  ModeImputerFeaturizer <bool> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_bool_CreateEstimator(/*out*/ ModeImputerFeaturizer_bool_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>* pEstimator = new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ModeImputerFeaturizer_bool_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_bool_DestroyEstimator(/*in*/ ModeImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_bool_GetState(/*in*/ ModeImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_bool_IsTrainingComplete(/*in*/ ModeImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_bool_Fit(/*in*/ ModeImputerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input != nullptr ? *input : Microsoft::Featurizer::Traits<bool>::CreateNullValue()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_bool_FitBuffer(/*in*/ ModeImputerFeaturizer_bool_EstimatorHandle *pHandle, /*in*/ bool const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
            input_buffer.push_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<bool>::CreateNullValue());
        #else
            input_buffer.emplace_back(*input_ptr ? **input_ptr : Microsoft::Featurizer::Traits<bool>::CreateNullValue());
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_bool_OnDataCompleted(/*in*/ ModeImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_bool_CompleteTraining(/*in*/ ModeImputerFeaturizer_bool_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_bool_CreateTransformerFromEstimator(/*in*/ ModeImputerFeaturizer_bool_EstimatorHandle *pEstimatorHandle, /*out*/ ModeImputerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_bool_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_bool_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ModeImputerFeaturizer_bool_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_bool_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_bool_DestroyTransformer(/*in*/ ModeImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_bool_CreateTransformerSaveData(/*in*/ ModeImputerFeaturizer_bool_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_bool_Transform(/*in*/ ModeImputerFeaturizer_bool_TransformerHandle *pHandle, /*in*/ bool const * input, /*out*/ bool * output, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output == nullptr) throw std::invalid_argument("'output' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<bool>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

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
/* |  ModeImputerFeaturizer <string> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_CreateEstimator(/*out*/ ModeImputerFeaturizer_string_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>* pEstimator = new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<ModeImputerFeaturizer_string_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_DestroyEstimator(/*in*/ ModeImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_GetState(/*in*/ ModeImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_IsTrainingComplete(/*in*/ ModeImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_Fit(/*in*/ ModeImputerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        // No validation

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input ? std::string(input) : nonstd::optional<std::string>()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_FitBuffer(/*in*/ ModeImputerFeaturizer_string_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
            input_buffer.push_back(*input_ptr ? *input_ptr : nonstd::optional<std::string>());
        #else
            input_buffer.emplace_back(*input_ptr ? *input_ptr : nonstd::optional<std::string>());
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_OnDataCompleted(/*in*/ ModeImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_CompleteTraining(/*in*/ ModeImputerFeaturizer_string_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_CreateTransformerFromEstimator(/*in*/ ModeImputerFeaturizer_string_EstimatorHandle *pEstimatorHandle, /*out*/ ModeImputerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_string_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ModeImputerFeaturizer_string_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<ModeImputerFeaturizer_string_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_DestroyTransformer(/*in*/ ModeImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_CreateTransformerSaveData(/*in*/ ModeImputerFeaturizer_string_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_Transform(/*in*/ ModeImputerFeaturizer_string_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ char const ** output_ptr, /*out*/ std::size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        // No input validation
        if(output_ptr == nullptr) throw std::invalid_argument("'output_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::ModeImputerEstimator<std::string>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input ? std::string(input) : nonstd::optional<std::string>()));

        // Output
        if(result.empty()) {
            *output_ptr = nullptr;
            *output_items = 0;
        }
        else {
            char * string_buffer(new char[result.size() + 1]);

            std::copy(result.begin(), result.end(), string_buffer);
            string_buffer[result.size()] = 0;

            *output_ptr = string_buffer;
            *output_items = result.size();
        }
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool ModeImputerFeaturizer_string_DestroyTransformedData(/*in*/ char const *result_ptr, /*in*/ std::size_t result_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_ptr == nullptr && result_items != 0) throw std::invalid_argument("Invalid buffer");
        if(result_ptr != nullptr && result_items == 0) throw std::invalid_argument("Invalid buffer");

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
