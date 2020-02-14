/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_L1NormalizeFeaturizer.h"

#include "Traits.h"
#include "Featurizers/Structs.h"

#include "SharedLibrary_Common.hpp"

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <int8> */
template <typename VectorInputT>
void L1NormalizeFeaturizer_int8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    L1NormalizeFeaturizer_int8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_int8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(L1NormalizeFeaturizer_int8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(L1NormalizeFeaturizer_int8_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(L1NormalizeFeaturizer_int8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    L1NormalizeFeaturizer_int8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(L1NormalizeFeaturizer_int8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    L1NormalizeFeaturizer_int8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_int8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(L1NormalizeFeaturizer_int8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t * result_ptr(nullptr);
        std::size_t result_elements(0);

        REQUIRE(L1NormalizeFeaturizer_int8_Transform(pTransformerHandle, input.data(), input.size(), &result_ptr, &result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
        results.push_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #else
        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #endif
        
        // Destroy the contents
        REQUIRE(L1NormalizeFeaturizer_int8_DestroyTransformedData(result_ptr, result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(L1NormalizeFeaturizer_int8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <int16> */
template <typename VectorInputT>
void L1NormalizeFeaturizer_int16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    L1NormalizeFeaturizer_int16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_int16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(L1NormalizeFeaturizer_int16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(L1NormalizeFeaturizer_int16_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(L1NormalizeFeaturizer_int16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    L1NormalizeFeaturizer_int16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(L1NormalizeFeaturizer_int16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    L1NormalizeFeaturizer_int16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_int16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(L1NormalizeFeaturizer_int16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t * result_ptr(nullptr);
        std::size_t result_elements(0);

        REQUIRE(L1NormalizeFeaturizer_int16_Transform(pTransformerHandle, input.data(), input.size(), &result_ptr, &result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
        results.push_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #else
        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #endif
        
        // Destroy the contents
        REQUIRE(L1NormalizeFeaturizer_int16_DestroyTransformedData(result_ptr, result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(L1NormalizeFeaturizer_int16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <int32> */
template <typename VectorInputT>
void L1NormalizeFeaturizer_int32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    L1NormalizeFeaturizer_int32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_int32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(L1NormalizeFeaturizer_int32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(L1NormalizeFeaturizer_int32_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(L1NormalizeFeaturizer_int32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    L1NormalizeFeaturizer_int32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(L1NormalizeFeaturizer_int32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    L1NormalizeFeaturizer_int32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_int32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(L1NormalizeFeaturizer_int32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t * result_ptr(nullptr);
        std::size_t result_elements(0);

        REQUIRE(L1NormalizeFeaturizer_int32_Transform(pTransformerHandle, input.data(), input.size(), &result_ptr, &result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
        results.push_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #else
        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #endif
        
        // Destroy the contents
        REQUIRE(L1NormalizeFeaturizer_int32_DestroyTransformedData(result_ptr, result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(L1NormalizeFeaturizer_int32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <int64> */
template <typename VectorInputT>
void L1NormalizeFeaturizer_int64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    L1NormalizeFeaturizer_int64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_int64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(L1NormalizeFeaturizer_int64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(L1NormalizeFeaturizer_int64_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(L1NormalizeFeaturizer_int64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    L1NormalizeFeaturizer_int64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(L1NormalizeFeaturizer_int64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    L1NormalizeFeaturizer_int64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_int64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(L1NormalizeFeaturizer_int64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t * result_ptr(nullptr);
        std::size_t result_elements(0);

        REQUIRE(L1NormalizeFeaturizer_int64_Transform(pTransformerHandle, input.data(), input.size(), &result_ptr, &result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
        results.push_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #else
        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #endif
        
        // Destroy the contents
        REQUIRE(L1NormalizeFeaturizer_int64_DestroyTransformedData(result_ptr, result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(L1NormalizeFeaturizer_int64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <uint8> */
template <typename VectorInputT>
void L1NormalizeFeaturizer_uint8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    L1NormalizeFeaturizer_uint8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_uint8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(L1NormalizeFeaturizer_uint8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(L1NormalizeFeaturizer_uint8_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(L1NormalizeFeaturizer_uint8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    L1NormalizeFeaturizer_uint8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(L1NormalizeFeaturizer_uint8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    L1NormalizeFeaturizer_uint8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_uint8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(L1NormalizeFeaturizer_uint8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t * result_ptr(nullptr);
        std::size_t result_elements(0);

        REQUIRE(L1NormalizeFeaturizer_uint8_Transform(pTransformerHandle, input.data(), input.size(), &result_ptr, &result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
        results.push_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #else
        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #endif
        
        // Destroy the contents
        REQUIRE(L1NormalizeFeaturizer_uint8_DestroyTransformedData(result_ptr, result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(L1NormalizeFeaturizer_uint8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <uint16> */
template <typename VectorInputT>
void L1NormalizeFeaturizer_uint16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    L1NormalizeFeaturizer_uint16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_uint16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(L1NormalizeFeaturizer_uint16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(L1NormalizeFeaturizer_uint16_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(L1NormalizeFeaturizer_uint16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    L1NormalizeFeaturizer_uint16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(L1NormalizeFeaturizer_uint16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    L1NormalizeFeaturizer_uint16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_uint16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(L1NormalizeFeaturizer_uint16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t * result_ptr(nullptr);
        std::size_t result_elements(0);

        REQUIRE(L1NormalizeFeaturizer_uint16_Transform(pTransformerHandle, input.data(), input.size(), &result_ptr, &result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
        results.push_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #else
        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #endif
        
        // Destroy the contents
        REQUIRE(L1NormalizeFeaturizer_uint16_DestroyTransformedData(result_ptr, result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(L1NormalizeFeaturizer_uint16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <uint32> */
template <typename VectorInputT>
void L1NormalizeFeaturizer_uint32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    L1NormalizeFeaturizer_uint32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_uint32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(L1NormalizeFeaturizer_uint32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(L1NormalizeFeaturizer_uint32_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(L1NormalizeFeaturizer_uint32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    L1NormalizeFeaturizer_uint32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(L1NormalizeFeaturizer_uint32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    L1NormalizeFeaturizer_uint32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_uint32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(L1NormalizeFeaturizer_uint32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t * result_ptr(nullptr);
        std::size_t result_elements(0);

        REQUIRE(L1NormalizeFeaturizer_uint32_Transform(pTransformerHandle, input.data(), input.size(), &result_ptr, &result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
        results.push_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #else
        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #endif
        
        // Destroy the contents
        REQUIRE(L1NormalizeFeaturizer_uint32_DestroyTransformedData(result_ptr, result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(L1NormalizeFeaturizer_uint32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <uint64> */
template <typename VectorInputT>
void L1NormalizeFeaturizer_uint64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    L1NormalizeFeaturizer_uint64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_uint64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(L1NormalizeFeaturizer_uint64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(L1NormalizeFeaturizer_uint64_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(L1NormalizeFeaturizer_uint64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    L1NormalizeFeaturizer_uint64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(L1NormalizeFeaturizer_uint64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    L1NormalizeFeaturizer_uint64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_uint64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(L1NormalizeFeaturizer_uint64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t * result_ptr(nullptr);
        std::size_t result_elements(0);

        REQUIRE(L1NormalizeFeaturizer_uint64_Transform(pTransformerHandle, input.data(), input.size(), &result_ptr, &result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
        results.push_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #else
        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #endif
        
        // Destroy the contents
        REQUIRE(L1NormalizeFeaturizer_uint64_DestroyTransformedData(result_ptr, result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(L1NormalizeFeaturizer_uint64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <float> */
template <typename VectorInputT>
void L1NormalizeFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    L1NormalizeFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_float_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(L1NormalizeFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(L1NormalizeFeaturizer_float_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(L1NormalizeFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    L1NormalizeFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(L1NormalizeFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    L1NormalizeFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(L1NormalizeFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t * result_ptr(nullptr);
        std::size_t result_elements(0);

        REQUIRE(L1NormalizeFeaturizer_float_Transform(pTransformerHandle, input.data(), input.size(), &result_ptr, &result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
        results.push_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #else
        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #endif
        
        // Destroy the contents
        REQUIRE(L1NormalizeFeaturizer_float_DestroyTransformedData(result_ptr, result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(L1NormalizeFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  L1NormalizeFeaturizer <double> */
template <typename VectorInputT>
void L1NormalizeFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    L1NormalizeFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_double_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(L1NormalizeFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(L1NormalizeFeaturizer_double_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(L1NormalizeFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    L1NormalizeFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(L1NormalizeFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    L1NormalizeFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(L1NormalizeFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(L1NormalizeFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t * result_ptr(nullptr);
        std::size_t result_elements(0);

        REQUIRE(L1NormalizeFeaturizer_double_Transform(pTransformerHandle, input.data(), input.size(), &result_ptr, &result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
        results.push_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #else
        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_elements));
        #endif
        
        // Destroy the contents
        REQUIRE(L1NormalizeFeaturizer_double_DestroyTransformedData(result_ptr, result_elements, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(L1NormalizeFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

