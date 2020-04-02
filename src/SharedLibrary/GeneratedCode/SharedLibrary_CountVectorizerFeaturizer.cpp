/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_CountVectorizerFeaturizer.h"
#include "SharedLibrary_Common.hpp"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "CountVectorizerFeaturizer.h"

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
/* |  CountVectorizerFeaturizer */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_CreateEstimator(/*in*/ bool lower, /*in*/ uint8_t analyzer, /*in*/ char const * regexToken, /*in*/ float maxDf, /*in*/ float minDf, /*in*/ uint32_t const * topKTerms, /*in*/ uint32_t ngramRangeMin, /*in*/ uint32_t ngramRangeMax, /*in*/ bool binary, /*out*/ CountVectorizerFeaturizer_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(regexToken == nullptr) throw std::invalid_argument("'regexToken' is null");
        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>* pEstimator = new Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 , lower, static_cast<typename Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::AnalyzerMethod>(analyzer), std::string(regexToken), maxDf, minDf, topKTerms != nullptr ? *topKTerms : Microsoft::Featurizer::Traits<std::uint32_t>::CreateNullValue(), ngramRangeMin, ngramRangeMax, binary);

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

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_Fit(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*in*/ char const * input, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        if(input == nullptr) throw std::invalid_argument("'input' is null");

        using InputType = typename Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::InputType;

        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(std::string(input)));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_FitBuffer(/*in*/ CountVectorizerFeaturizer_EstimatorHandle *pHandle, /*in*/ char const * const * input_ptr, /*in*/ size_t input_items, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        while(input_buffer.size() < input_items) {
            input_buffer.emplace_back(*input_ptr);
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

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ size_t cBufferSize, /*out*/ CountVectorizerFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_CreateTransformerSaveData(/*in*/ CountVectorizerFeaturizer_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_Transform(/*in*/ CountVectorizerFeaturizer_TransformerHandle *pHandle, /*in*/ char const * input, /*out*/ uint64_t * output_numElements, /*out*/ uint64_t * output_numValues, /*out*/ uint32_t ** output_values, /*out*/ uint64_t ** output_indexes, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        using InputType = typename Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::InputType;
        using TransformedType = typename Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformedType;

        // Input
        TransformedType result(transformer.execute(std::string(input)));

        // Output
        std::unique_ptr<std::uint32_t []> pValues(new std::uint32_t [result.Values.size()]);
        std::unique_ptr<uint64_t []> pIndexes(new uint64_t [result.Values.size()]);

        std::uint32_t * pValue(pValues.get());
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

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_Flush(/*in*/ CountVectorizerFeaturizer_TransformerHandle *pHandle, /*out*/ uint64_t ** output_item_numElements_ptr, /*out*/ uint64_t ** output_item_numValues_ptr, /*out*/ uint32_t *** output_item_values_ptr, /*out*/ uint64_t *** output_item_indexes_ptr, /*out*/ size_t * output_items, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        if(output_item_numElements_ptr == nullptr) throw std::invalid_argument("'output_item_numElements_ptr' is null");
        if(output_item_numValues_ptr == nullptr) throw std::invalid_argument("'output_item_numValues_ptr' is null");
        if(output_item_values_ptr == nullptr) throw std::invalid_argument("'output_item_values_ptr' is null");
        if(output_item_indexes_ptr == nullptr) throw std::invalid_argument("'output_item_indexes_ptr' is null");
        if(output_items == nullptr) throw std::invalid_argument("'output_items' is null");

        Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        using TransformedType = typename Microsoft::Featurizer::Featurizers::CountVectorizerEstimator<>::TransformedType;

        std::vector<TransformedType> result;

        auto const callback(
            [&result](TransformedType value) {
                result.emplace_back(std::move(value));
            }
        );

        transformer.flush(callback);

        // Output
        if(result.empty()) {
            *output_item_numElements_ptr = nullptr;
            *output_item_numValues_ptr = nullptr;
            *output_item_values_ptr = nullptr;
            *output_item_indexes_ptr = nullptr;
        }
        else {
            // TODO: There are potential memory leaks if allocation fails
            *output_item_numElements_ptr = new uint64_t[result.size()];
            *output_item_numValues_ptr = new uint64_t[result.size()];
            *output_item_values_ptr = new uint32_t *[result.size()];
            *output_item_indexes_ptr = new uint64_t *[result.size()];

            uint64_t * output_item_numElements(*output_item_numElements_ptr);
            uint64_t * output_item_numValues(*output_item_numValues_ptr);
            uint32_t ** output_item_values(*output_item_values_ptr);
            uint64_t ** output_item_indexes(*output_item_indexes_ptr);

            for(auto const & result_item : result) {
                if(output_item_numElements == nullptr) throw std::invalid_argument("'output_item_numElements' is null");
                if(output_item_numValues == nullptr) throw std::invalid_argument("'output_item_numValues' is null");
                if(output_item_values == nullptr) throw std::invalid_argument("'output_item_values' is null");
                if(output_item_indexes == nullptr) throw std::invalid_argument("'output_item_indexes' is null");

                std::unique_ptr<std::uint32_t []> pValues(new std::uint32_t [result_item.Values.size()]);
                std::unique_ptr<uint64_t []> pIndexes(new uint64_t [result_item.Values.size()]);

                std::uint32_t * pValue(pValues.get());
                uint64_t * pIndex(pIndexes.get());

                for(auto const & encoding : result_item.Values) {
                    *pValue++ = encoding.Value;
                    *pIndex++ = encoding.Index;
                }

                *output_item_numElements = result_item.NumElements;
                *output_item_numValues = result_item.Values.size();

                *output_item_values = pValues.release();
                *output_item_indexes = pIndexes.release();

                ++output_item_numElements;
                ++output_item_numValues;
                ++output_item_values;
                ++output_item_indexes;
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

FEATURIZER_LIBRARY_API bool CountVectorizerFeaturizer_DestroyTransformedData(/*out*/ uint64_t result_numElements, /*out*/ uint64_t result_numValues, /*out*/ uint32_t const * result_values, /*out*/ uint64_t const * result_indexes, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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


#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

} // extern "C"
