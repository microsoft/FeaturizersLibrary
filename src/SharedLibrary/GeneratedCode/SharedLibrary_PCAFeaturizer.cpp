/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include "SharedLibrary_PCAFeaturizer.h"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "PCAFeaturizer.h"

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
/* |  PCAFeaturizer <float> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_CreateEstimator(/*out*/ PCAFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>* pEstimator = new Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<PCAFeaturizer_float_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_DestroyEstimator(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_GetState(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_IsTrainingComplete(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_Fit(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ float const * input_ptr, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        if(input_cols == 0) throw std::invalid_argument("'input_cols' is 0");
        if(input_rows == 0) throw std::invalid_argument("'input_rows' is 0");
        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(Eigen::Map<Eigen::MatrixX<float>>(const_cast<float *>(input_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols))));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_FitBuffer(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ float const **input_values_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_cols == 0) throw std::invalid_argument("'input_cols' is 0");
        if(input_rows == 0) throw std::invalid_argument("'input_rows' is 0");
        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        std::vector<Eigen::Map<Eigen::MatrixX<float>>> input_buffer;

        input_buffer.reserve(input_elements);

        float const * const * const input_values_end(input_values_ptr + input_elements);

        while(input_values_ptr != input_values_end) {
        #if (defined __apple_build_verion__)
            input_buffer.push_back(Eigen::Map<Eigen::MatrixX<float>>(const_cast<float *>(*input_values_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols)));
        #else
            input_buffer.emplace_back(Eigen::Map<Eigen::MatrixX<float>>(const_cast<float *>(*input_values_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols)));
        #endif
            ++input_values_ptr;
        }

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_OnDataCompleted(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_CompleteTraining(/*in*/ PCAFeaturizer_float_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_CreateTransformerFromEstimator(/*in*/ PCAFeaturizer_float_EstimatorHandle *pEstimatorHandle, /*out*/ PCAFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<PCAFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ PCAFeaturizer_float_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<PCAFeaturizer_float_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_DestroyTransformer(/*in*/ PCAFeaturizer_float_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_CreateTransformerSaveData(/*in*/ PCAFeaturizer_float_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_Transform(/*in*/ PCAFeaturizer_float_TransformerHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ float const * input_ptr, /*out*/ size_t *output_cols, /*out*/ size_t *output_rows, /*out*/ float **output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<float>>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(Eigen::Map<Eigen::MatrixX<float>>(const_cast<float *>(input_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols))));

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

FEATURIZER_LIBRARY_API bool PCAFeaturizer_float_DestroyTransformedData(/*in*/ size_t result_cols, /*in*/ size_t result_rows, /*in*/ float *result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
/* |  PCAFeaturizer <double> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_CreateEstimator(/*out*/ PCAFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>* pEstimator = new Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0 );

        pEstimator->begin_training();

        size_t index(g_pointerTable.Add(pEstimator));
        *ppHandle = reinterpret_cast<PCAFeaturizer_double_EstimatorHandle*>(index);


    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_DestroyEstimator(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>> * pEstimator = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>>(index);
        g_pointerTable.Remove(index);

        delete pEstimator;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_GetState(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*out*/ TrainingState *pState, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pState == nullptr) throw std::invalid_argument("'pState' is null");

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>>(reinterpret_cast<size_t>(pHandle)));

        *pState = static_cast<TrainingState>(estimator.get_state());
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_IsTrainingComplete(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>> const & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_Fit(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ double const * input_ptr, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");


        if(input_cols == 0) throw std::invalid_argument("'input_cols' is 0");
        if(input_rows == 0) throw std::invalid_argument("'input_rows' is 0");
        if(input_ptr == nullptr) throw std::invalid_argument("'input_ptr' is null");

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>>(reinterpret_cast<size_t>(pHandle)));


        *pFitResult = static_cast<unsigned char>(estimator.fit(Eigen::Map<Eigen::MatrixX<double>>(const_cast<double *>(input_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols))));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_FitBuffer(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ double const **input_values_ptr, /*in*/ size_t input_elements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");



        if(input_cols == 0) throw std::invalid_argument("'input_cols' is 0");
        if(input_rows == 0) throw std::invalid_argument("'input_rows' is 0");
        if(input_values_ptr == nullptr) throw std::invalid_argument("'input_values_ptr' is null");
        if(input_elements == 0) throw std::invalid_argument("'input_elements' is 0");

        std::vector<Eigen::Map<Eigen::MatrixX<double>>> input_buffer;

        input_buffer.reserve(input_elements);

        double const * const * const input_values_end(input_values_ptr + input_elements);

        while(input_values_ptr != input_values_end) {
        #if (defined __apple_build_verion__)
            input_buffer.push_back(Eigen::Map<Eigen::MatrixX<double>>(const_cast<double *>(*input_values_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols)));
        #else
            input_buffer.emplace_back(Eigen::Map<Eigen::MatrixX<double>>(const_cast<double *>(*input_values_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols)));
        #endif
            ++input_values_ptr;
        }

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(estimator.fit(input_buffer.data(), input_buffer.size()));
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_OnDataCompleted(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.on_data_completed();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_CompleteTraining(/*in*/ PCAFeaturizer_double_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>>(reinterpret_cast<size_t>(pHandle)));

        estimator.complete_training();
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_CreateTransformerFromEstimator(/*in*/ PCAFeaturizer_double_EstimatorHandle *pEstimatorHandle, /*out*/ PCAFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");



        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>> & estimator(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>>(reinterpret_cast<size_t>(pEstimatorHandle)));

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>::TransformerType * pTransformer = reinterpret_cast<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>::TransformerType*>(estimator.create_transformer().release());


        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<PCAFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ PCAFeaturizer_double_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>::TransformerType(archive));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<PCAFeaturizer_double_TransformerHandle*>(index);
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_DestroyTransformer(/*in*/ PCAFeaturizer_double_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t index = reinterpret_cast<size_t>(pHandle);
        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>::TransformerType* pTransformer = g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>::TransformerType>(index);
        g_pointerTable.Remove(index);


        delete pTransformer;
    
        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_CreateTransformerSaveData(/*in*/ PCAFeaturizer_double_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));
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

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_Transform(/*in*/ PCAFeaturizer_double_TransformerHandle *pHandle, /*in*/ size_t input_cols, /*in*/ size_t input_rows, /*in*/ double const * input_ptr, /*out*/ size_t *output_cols, /*out*/ size_t *output_rows, /*out*/ double **output_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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

        Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>::TransformerType & transformer(*g_pointerTable.Get<Microsoft::Featurizer::Featurizers::PCAEstimator<Eigen::Map<Eigen::MatrixX<double>>>::TransformerType>(reinterpret_cast<size_t>(pHandle)));

        // Input
        auto result(transformer.execute(Eigen::Map<Eigen::MatrixX<double>>(const_cast<double *>(input_ptr), static_cast<Eigen::Index>(input_rows), static_cast<Eigen::Index>(input_cols))));

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

FEATURIZER_LIBRARY_API bool PCAFeaturizer_double_DestroyTransformedData(/*in*/ size_t result_cols, /*in*/ size_t result_rows, /*in*/ double *result_ptr, /*out*/ ErrorInfoHandle **ppErrorInfo) {
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
