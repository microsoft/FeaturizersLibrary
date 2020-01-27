/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_OneHotEncoderFeaturizer.h"

#include "Traits.h"
#include "Featurizers/Structs.h"

#include "SharedLibrary_Common.hpp"

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int8> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_int8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_int8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int8_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(OneHotEncoderFeaturizer_int8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_int8_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(OneHotEncoderFeaturizer_int8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    OneHotEncoderFeaturizer_int8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_int8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_int8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_int8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t result_numElements(0);
        std::uint8_t result_value;
        uint64_t result_index(0);

        REQUIRE(OneHotEncoderFeaturizer_int8_Transform(pTransformerHandle, input, &result_numElements, &result_value, &result_index, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>(result_numElements, result_value, result_index));
        #else
        results.emplace_back(result_numElements, result_value, result_index);
        #endif
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_int8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int16> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_int16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_int16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int16_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(OneHotEncoderFeaturizer_int16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_int16_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(OneHotEncoderFeaturizer_int16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    OneHotEncoderFeaturizer_int16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_int16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_int16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_int16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t result_numElements(0);
        std::uint8_t result_value;
        uint64_t result_index(0);

        REQUIRE(OneHotEncoderFeaturizer_int16_Transform(pTransformerHandle, input, &result_numElements, &result_value, &result_index, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>(result_numElements, result_value, result_index));
        #else
        results.emplace_back(result_numElements, result_value, result_index);
        #endif
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_int16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int32> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_int32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_int32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int32_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(OneHotEncoderFeaturizer_int32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_int32_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(OneHotEncoderFeaturizer_int32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    OneHotEncoderFeaturizer_int32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_int32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_int32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_int32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t result_numElements(0);
        std::uint8_t result_value;
        uint64_t result_index(0);

        REQUIRE(OneHotEncoderFeaturizer_int32_Transform(pTransformerHandle, input, &result_numElements, &result_value, &result_index, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>(result_numElements, result_value, result_index));
        #else
        results.emplace_back(result_numElements, result_value, result_index);
        #endif
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_int32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int64> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_int64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_int64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int64_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(OneHotEncoderFeaturizer_int64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_int64_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(OneHotEncoderFeaturizer_int64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    OneHotEncoderFeaturizer_int64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_int64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_int64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_int64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t result_numElements(0);
        std::uint8_t result_value;
        uint64_t result_index(0);

        REQUIRE(OneHotEncoderFeaturizer_int64_Transform(pTransformerHandle, input, &result_numElements, &result_value, &result_index, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>(result_numElements, result_value, result_index));
        #else
        results.emplace_back(result_numElements, result_value, result_index);
        #endif
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_int64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint8> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_uint8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_uint8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint8_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(OneHotEncoderFeaturizer_uint8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_uint8_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(OneHotEncoderFeaturizer_uint8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    OneHotEncoderFeaturizer_uint8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_uint8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_uint8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_uint8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t result_numElements(0);
        std::uint8_t result_value;
        uint64_t result_index(0);

        REQUIRE(OneHotEncoderFeaturizer_uint8_Transform(pTransformerHandle, input, &result_numElements, &result_value, &result_index, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>(result_numElements, result_value, result_index));
        #else
        results.emplace_back(result_numElements, result_value, result_index);
        #endif
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_uint8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint16> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_uint16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_uint16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint16_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(OneHotEncoderFeaturizer_uint16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_uint16_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(OneHotEncoderFeaturizer_uint16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    OneHotEncoderFeaturizer_uint16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_uint16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_uint16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_uint16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t result_numElements(0);
        std::uint8_t result_value;
        uint64_t result_index(0);

        REQUIRE(OneHotEncoderFeaturizer_uint16_Transform(pTransformerHandle, input, &result_numElements, &result_value, &result_index, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>(result_numElements, result_value, result_index));
        #else
        results.emplace_back(result_numElements, result_value, result_index);
        #endif
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_uint16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint32> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_uint32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_uint32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint32_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(OneHotEncoderFeaturizer_uint32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_uint32_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(OneHotEncoderFeaturizer_uint32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    OneHotEncoderFeaturizer_uint32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_uint32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_uint32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_uint32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t result_numElements(0);
        std::uint8_t result_value;
        uint64_t result_index(0);

        REQUIRE(OneHotEncoderFeaturizer_uint32_Transform(pTransformerHandle, input, &result_numElements, &result_value, &result_index, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>(result_numElements, result_value, result_index));
        #else
        results.emplace_back(result_numElements, result_value, result_index);
        #endif
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_uint32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint64> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_uint64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_uint64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint64_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(OneHotEncoderFeaturizer_uint64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_uint64_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(OneHotEncoderFeaturizer_uint64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    OneHotEncoderFeaturizer_uint64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_uint64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_uint64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_uint64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t result_numElements(0);
        std::uint8_t result_value;
        uint64_t result_index(0);

        REQUIRE(OneHotEncoderFeaturizer_uint64_Transform(pTransformerHandle, input, &result_numElements, &result_value, &result_index, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>(result_numElements, result_value, result_index));
        #else
        results.emplace_back(result_numElements, result_value, result_index);
        #endif
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_uint64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <float> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_float_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(OneHotEncoderFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_float_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(OneHotEncoderFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    OneHotEncoderFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t result_numElements(0);
        std::uint8_t result_value;
        uint64_t result_index(0);

        REQUIRE(OneHotEncoderFeaturizer_float_Transform(pTransformerHandle, input, &result_numElements, &result_value, &result_index, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>(result_numElements, result_value, result_index));
        #else
        results.emplace_back(result_numElements, result_value, result_index);
        #endif
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <double> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_double_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(OneHotEncoderFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_double_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(OneHotEncoderFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    OneHotEncoderFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t result_numElements(0);
        std::uint8_t result_value;
        uint64_t result_index(0);

        REQUIRE(OneHotEncoderFeaturizer_double_Transform(pTransformerHandle, input, &result_numElements, &result_value, &result_index, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>(result_numElements, result_value, result_index));
        #else
        results.emplace_back(result_numElements, result_value, result_index);
        #endif
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <bool> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_bool_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_bool_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_bool_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(OneHotEncoderFeaturizer_bool_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_bool_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(OneHotEncoderFeaturizer_bool_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    OneHotEncoderFeaturizer_bool_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_bool_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_bool_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_bool_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_bool_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t result_numElements(0);
        std::uint8_t result_value;
        uint64_t result_index(0);

        REQUIRE(OneHotEncoderFeaturizer_bool_Transform(pTransformerHandle, input, &result_numElements, &result_value, &result_index, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>(result_numElements, result_value, result_index));
        #else
        results.emplace_back(result_numElements, result_value, result_index);
        #endif
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_bool_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <string> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_string_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_string_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_string_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(OneHotEncoderFeaturizer_string_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_string_Fit(pEstimatorHandle, input.c_str(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(OneHotEncoderFeaturizer_string_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    OneHotEncoderFeaturizer_string_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_string_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_string_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_string_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_string_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t result_numElements(0);
        std::uint8_t result_value;
        uint64_t result_index(0);

        REQUIRE(OneHotEncoderFeaturizer_string_Transform(pTransformerHandle, input.c_str(), &result_numElements, &result_value, &result_index, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>(result_numElements, result_value, result_index));
        #else
        results.emplace_back(result_numElements, result_value, result_index);
        #endif
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

