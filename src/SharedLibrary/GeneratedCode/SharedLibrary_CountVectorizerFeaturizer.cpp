/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_CountVectorizerFeaturizer.h"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "CountVectorizerFeaturizer.h"

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
/* |  CountVectorizerFeaturizer */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_CreateEstimator(/*in*/ bool lower, /*in*/ uint8_t analyzer, /*in*/ char const *regexToken, /*in*/ float maxDf, /*in*/ float minDf, /*in*/ uint32_t const * topKTerms, /*in*/ uint32_t ngramRangeMin, /*in*/ uint32_t ngramRangeMax, /*in*/ bool binary, /*out*/ CountVectorizerFeaturizer_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(regexToken == nullptr) throw std::invalid_argument("'regexToken' is null");
        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>* pEstimator = new Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , lower, static_cast<typename Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::AnalyzerMethod>(analyzer), regexToken, maxDf, minDf, topKTerms != nullptr ? *topKTerms : Microsoft::Featurizer::Traits<std::uint32_t>::CreateNullValue(), ngramRangeMin, ngramRangeMax, binary);

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<CountVectorizerFeaturizer_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_DestroyEstimator(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_GetState(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_IsTrainingComplete(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_Fit(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*in*/ char const *input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        if(input == nullptr) throw std::invalid_argument("'input' is null");

        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(input));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_FitBuffer(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ std::size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");
        if(input_items == 0) throw std::invalid_argument("'input_items' is 0");

        std::vector<std::string> input_buffer;

        input_buffer.reserve(input_items);

        char const * const * const input_end(input_ptr + input_items);

        while(input_ptr != input_end) {
        #if (defined __apple_build_version__)
            input_buffer.push_back(*input_ptr);
        #else
            input_buffer.emplace_back(*input_ptr);
        #endif
            ++input_ptr;
        }

        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_OnDataCompleted(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_CompleteTraining(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_CreateTransformerFromEstimator(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pEstimatorHandle, /*out*/ CountVectorizerFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<CountVectorizerFeaturizer_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ CountVectorizerFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<CountVectorizerFeaturizer_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_DestroyTransformer(/*in*/ CountVectorizerFeaturizer_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_CreateTransformerSaveData(/*in*/ CountVectorizerFeaturizer_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_Transform(/*in*/ CountVectorizerFeaturizer_TransformerHandle *pHandle, /*in*/ char const *input, /*out*/ uint64_t * output_numElements, /*out*/ uint64_t * output_numValues, /*out*/ float **output_values, /*out*/ uint64_t **output_indexes, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");


        if(input == nullptr) throw std::invalid_argument("'input' is null");
        if(output_numElements == nullptr) throw std::invalid_argument("'output_numElements' is null");
        if(output_numValues == nullptr) throw std::invalid_argument("'output_numValues' is null");
        if(output_values == nullptr) throw std::invalid_argument("'output_values' is null");
        if(output_indexes == nullptr) throw std::invalid_argument("'output_indexes' is null");

        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(input));

        // Output
        std::unique_ptr<std::float_t []> pValues(new std::float_t [result.Values.size()]);
        std::unique_ptr<uint64_t []> pIndexes(new uint64_t [result.Values.size()]);

        std::float_t * pValue(pValues.get());
        uint64_t * pIndex(pIndexes.get());

        for(auto const & encoding : result.Values) {
            *pValue++ = encoding.Value;
            *pIndex++ = encoding.Index;
        }

        *output_numElements = result.NumElements;
        *output_numValues = result.Values.size();

        *output_values = pValues.release();
        *output_indexes = pIndexes.release();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_DestroyTransformedData(/*in*/ uint64_t result_numElements, /*in*/ uint64_t result_numValues, /*in*/ float const * result_values, /*in*/ uint64_t const * result_indexes, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(result_numElements == 0) throw std::invalid_argument("'result_numElements' is 0");
        if(result_numValues == 0) throw std::invalid_argument("'result_numValues' is 0");
        if(result_values == nullptr) throw std::invalid_argument("'result_values' is null");
        if(result_indexes == nullptr) throw std::invalid_argument("'result_indexes' is null");

        delete [] result_values;
        delete [] result_indexes;
    
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
