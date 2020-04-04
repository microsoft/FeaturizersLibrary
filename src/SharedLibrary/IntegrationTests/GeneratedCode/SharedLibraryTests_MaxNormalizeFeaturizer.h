/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_MaxNormalizeFeaturizer.h"

#include "Traits.h"
#include "Featurizers/Structs.h"

#include "SharedLibraryTests_Common.hpp"

#if (defined _MSC_VER)
#   pragma warning(push)

    // I don't know why MSVC thinks that there is unreachable
    // code in these methods during release builds.
#   pragma warning(disable: 4702) // Unreachable code

#   pragma warning(disable: 4701) // potentially uninitialized local variable '<name>' used
#   pragma warning(disable: 4703) // potentially uninitialized local pointer variable '<name>' used
#endif

/* ---------------------------------------------------------------------- */
/* |  MaxNormalizeFeaturizer <int8> */
template <typename VectorInputT>
void MaxNormalizeFeaturizer_int8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MaxNormalizeFeaturizer_int8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_int8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MaxNormalizeFeaturizer_int8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MaxNormalizeFeaturizer_int8_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MaxNormalizeFeaturizer_int8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MaxNormalizeFeaturizer_int8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MaxNormalizeFeaturizer_int8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MaxNormalizeFeaturizer_int8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_int8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MaxNormalizeFeaturizer_int8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t* results_item_value_items;
        size_t results_items;

        REQUIRE(MaxNormalizeFeaturizer_int8_Transform(pTransformerHandle, input.data(), input.size(), &results_item_value_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::double_t* results_item_value_items_ptr(results_item_value_items);

        while(results_buffer.size() < results_items) {
            std::double_t & results_item_value(*results_item_value_items_ptr);

            results_buffer.emplace_back(std::move(results_item_value));

            ++results_item_value_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(MaxNormalizeFeaturizer_int8_DestroyTransformedData(results_item_value_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MaxNormalizeFeaturizer_int8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MaxNormalizeFeaturizer <int16> */
template <typename VectorInputT>
void MaxNormalizeFeaturizer_int16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MaxNormalizeFeaturizer_int16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_int16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MaxNormalizeFeaturizer_int16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MaxNormalizeFeaturizer_int16_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MaxNormalizeFeaturizer_int16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MaxNormalizeFeaturizer_int16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MaxNormalizeFeaturizer_int16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MaxNormalizeFeaturizer_int16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_int16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MaxNormalizeFeaturizer_int16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t* results_item_value_items;
        size_t results_items;

        REQUIRE(MaxNormalizeFeaturizer_int16_Transform(pTransformerHandle, input.data(), input.size(), &results_item_value_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::double_t* results_item_value_items_ptr(results_item_value_items);

        while(results_buffer.size() < results_items) {
            std::double_t & results_item_value(*results_item_value_items_ptr);

            results_buffer.emplace_back(std::move(results_item_value));

            ++results_item_value_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(MaxNormalizeFeaturizer_int16_DestroyTransformedData(results_item_value_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MaxNormalizeFeaturizer_int16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MaxNormalizeFeaturizer <int32> */
template <typename VectorInputT>
void MaxNormalizeFeaturizer_int32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MaxNormalizeFeaturizer_int32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_int32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MaxNormalizeFeaturizer_int32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MaxNormalizeFeaturizer_int32_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MaxNormalizeFeaturizer_int32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MaxNormalizeFeaturizer_int32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MaxNormalizeFeaturizer_int32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MaxNormalizeFeaturizer_int32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_int32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MaxNormalizeFeaturizer_int32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t* results_item_value_items;
        size_t results_items;

        REQUIRE(MaxNormalizeFeaturizer_int32_Transform(pTransformerHandle, input.data(), input.size(), &results_item_value_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::double_t* results_item_value_items_ptr(results_item_value_items);

        while(results_buffer.size() < results_items) {
            std::double_t & results_item_value(*results_item_value_items_ptr);

            results_buffer.emplace_back(std::move(results_item_value));

            ++results_item_value_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(MaxNormalizeFeaturizer_int32_DestroyTransformedData(results_item_value_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MaxNormalizeFeaturizer_int32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MaxNormalizeFeaturizer <int64> */
template <typename VectorInputT>
void MaxNormalizeFeaturizer_int64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MaxNormalizeFeaturizer_int64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_int64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MaxNormalizeFeaturizer_int64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MaxNormalizeFeaturizer_int64_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MaxNormalizeFeaturizer_int64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MaxNormalizeFeaturizer_int64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MaxNormalizeFeaturizer_int64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MaxNormalizeFeaturizer_int64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_int64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MaxNormalizeFeaturizer_int64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t* results_item_value_items;
        size_t results_items;

        REQUIRE(MaxNormalizeFeaturizer_int64_Transform(pTransformerHandle, input.data(), input.size(), &results_item_value_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::double_t* results_item_value_items_ptr(results_item_value_items);

        while(results_buffer.size() < results_items) {
            std::double_t & results_item_value(*results_item_value_items_ptr);

            results_buffer.emplace_back(std::move(results_item_value));

            ++results_item_value_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(MaxNormalizeFeaturizer_int64_DestroyTransformedData(results_item_value_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MaxNormalizeFeaturizer_int64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MaxNormalizeFeaturizer <uint8> */
template <typename VectorInputT>
void MaxNormalizeFeaturizer_uint8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MaxNormalizeFeaturizer_uint8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_uint8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MaxNormalizeFeaturizer_uint8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MaxNormalizeFeaturizer_uint8_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MaxNormalizeFeaturizer_uint8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MaxNormalizeFeaturizer_uint8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MaxNormalizeFeaturizer_uint8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MaxNormalizeFeaturizer_uint8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_uint8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MaxNormalizeFeaturizer_uint8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t* results_item_value_items;
        size_t results_items;

        REQUIRE(MaxNormalizeFeaturizer_uint8_Transform(pTransformerHandle, input.data(), input.size(), &results_item_value_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::double_t* results_item_value_items_ptr(results_item_value_items);

        while(results_buffer.size() < results_items) {
            std::double_t & results_item_value(*results_item_value_items_ptr);

            results_buffer.emplace_back(std::move(results_item_value));

            ++results_item_value_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(MaxNormalizeFeaturizer_uint8_DestroyTransformedData(results_item_value_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MaxNormalizeFeaturizer_uint8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MaxNormalizeFeaturizer <uint16> */
template <typename VectorInputT>
void MaxNormalizeFeaturizer_uint16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MaxNormalizeFeaturizer_uint16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_uint16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MaxNormalizeFeaturizer_uint16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MaxNormalizeFeaturizer_uint16_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MaxNormalizeFeaturizer_uint16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MaxNormalizeFeaturizer_uint16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MaxNormalizeFeaturizer_uint16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MaxNormalizeFeaturizer_uint16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_uint16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MaxNormalizeFeaturizer_uint16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t* results_item_value_items;
        size_t results_items;

        REQUIRE(MaxNormalizeFeaturizer_uint16_Transform(pTransformerHandle, input.data(), input.size(), &results_item_value_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::double_t* results_item_value_items_ptr(results_item_value_items);

        while(results_buffer.size() < results_items) {
            std::double_t & results_item_value(*results_item_value_items_ptr);

            results_buffer.emplace_back(std::move(results_item_value));

            ++results_item_value_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(MaxNormalizeFeaturizer_uint16_DestroyTransformedData(results_item_value_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MaxNormalizeFeaturizer_uint16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MaxNormalizeFeaturizer <uint32> */
template <typename VectorInputT>
void MaxNormalizeFeaturizer_uint32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MaxNormalizeFeaturizer_uint32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_uint32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MaxNormalizeFeaturizer_uint32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MaxNormalizeFeaturizer_uint32_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MaxNormalizeFeaturizer_uint32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MaxNormalizeFeaturizer_uint32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MaxNormalizeFeaturizer_uint32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MaxNormalizeFeaturizer_uint32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_uint32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MaxNormalizeFeaturizer_uint32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t* results_item_value_items;
        size_t results_items;

        REQUIRE(MaxNormalizeFeaturizer_uint32_Transform(pTransformerHandle, input.data(), input.size(), &results_item_value_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::double_t* results_item_value_items_ptr(results_item_value_items);

        while(results_buffer.size() < results_items) {
            std::double_t & results_item_value(*results_item_value_items_ptr);

            results_buffer.emplace_back(std::move(results_item_value));

            ++results_item_value_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(MaxNormalizeFeaturizer_uint32_DestroyTransformedData(results_item_value_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MaxNormalizeFeaturizer_uint32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MaxNormalizeFeaturizer <uint64> */
template <typename VectorInputT>
void MaxNormalizeFeaturizer_uint64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MaxNormalizeFeaturizer_uint64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_uint64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MaxNormalizeFeaturizer_uint64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MaxNormalizeFeaturizer_uint64_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MaxNormalizeFeaturizer_uint64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MaxNormalizeFeaturizer_uint64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MaxNormalizeFeaturizer_uint64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MaxNormalizeFeaturizer_uint64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_uint64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MaxNormalizeFeaturizer_uint64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t* results_item_value_items;
        size_t results_items;

        REQUIRE(MaxNormalizeFeaturizer_uint64_Transform(pTransformerHandle, input.data(), input.size(), &results_item_value_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::double_t* results_item_value_items_ptr(results_item_value_items);

        while(results_buffer.size() < results_items) {
            std::double_t & results_item_value(*results_item_value_items_ptr);

            results_buffer.emplace_back(std::move(results_item_value));

            ++results_item_value_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(MaxNormalizeFeaturizer_uint64_DestroyTransformedData(results_item_value_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MaxNormalizeFeaturizer_uint64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MaxNormalizeFeaturizer <float> */
template <typename VectorInputT>
void MaxNormalizeFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MaxNormalizeFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_float_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MaxNormalizeFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MaxNormalizeFeaturizer_float_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MaxNormalizeFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MaxNormalizeFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MaxNormalizeFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MaxNormalizeFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MaxNormalizeFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t* results_item_value_items;
        size_t results_items;

        REQUIRE(MaxNormalizeFeaturizer_float_Transform(pTransformerHandle, input.data(), input.size(), &results_item_value_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::double_t* results_item_value_items_ptr(results_item_value_items);

        while(results_buffer.size() < results_items) {
            std::double_t & results_item_value(*results_item_value_items_ptr);

            results_buffer.emplace_back(std::move(results_item_value));

            ++results_item_value_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(MaxNormalizeFeaturizer_float_DestroyTransformedData(results_item_value_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MaxNormalizeFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MaxNormalizeFeaturizer <double> */
template <typename VectorInputT>
void MaxNormalizeFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MaxNormalizeFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_double_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MaxNormalizeFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MaxNormalizeFeaturizer_double_Fit(pEstimatorHandle, input.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MaxNormalizeFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MaxNormalizeFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MaxNormalizeFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MaxNormalizeFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MaxNormalizeFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MaxNormalizeFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t* results_item_value_items;
        size_t results_items;

        REQUIRE(MaxNormalizeFeaturizer_double_Transform(pTransformerHandle, input.data(), input.size(), &results_item_value_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::double_t* results_item_value_items_ptr(results_item_value_items);

        while(results_buffer.size() < results_items) {
            std::double_t & results_item_value(*results_item_value_items_ptr);

            results_buffer.emplace_back(std::move(results_item_value));

            ++results_item_value_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(MaxNormalizeFeaturizer_double_DestroyTransformedData(results_item_value_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MaxNormalizeFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
