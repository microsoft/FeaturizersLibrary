/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_BackwardFillImputerFeaturizer.h"

#include "Traits.h"
#include "Featurizers/Structs.h"

#include "SharedLibrary_Common.hpp"

#if (defined _MSC_VER)
#   pragma warning(push)

    // I don't know why MSVC thinks that there is unreachable
    // code in these methods during release builds.
#   pragma warning(disable: 4702) // Unreachable code

#   pragma warning(disable: 4701) // potentially uninitialized local variable '<name>' used
#   pragma warning(disable: 4703) // potentially uninitialized local pointer variable '<name>' used
#endif

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <int8> */
template <typename VectorInputT>
void BackwardFillImputerFeaturizer_int8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::int8_t>> const &)> const &verify_func,
    bool flush=true
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    BackwardFillImputerFeaturizer_int8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_int8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(BackwardFillImputerFeaturizer_int8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(BackwardFillImputerFeaturizer_int8_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(BackwardFillImputerFeaturizer_int8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    BackwardFillImputerFeaturizer_int8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(BackwardFillImputerFeaturizer_int8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    BackwardFillImputerFeaturizer_int8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_int8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(BackwardFillImputerFeaturizer_int8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::int8_t>> results;

    for(auto const & input : inference_input) {
        std::int8_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_int8_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::GetNullableValue(input), &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::int8_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_int8_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(flush) {
        std::int8_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_int8_Flush(pTransformerHandle, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::int8_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_int8_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(BackwardFillImputerFeaturizer_int8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <int16> */
template <typename VectorInputT>
void BackwardFillImputerFeaturizer_int16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::int16_t>> const &)> const &verify_func,
    bool flush=true
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    BackwardFillImputerFeaturizer_int16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_int16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(BackwardFillImputerFeaturizer_int16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(BackwardFillImputerFeaturizer_int16_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(BackwardFillImputerFeaturizer_int16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    BackwardFillImputerFeaturizer_int16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(BackwardFillImputerFeaturizer_int16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    BackwardFillImputerFeaturizer_int16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_int16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(BackwardFillImputerFeaturizer_int16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::int16_t>> results;

    for(auto const & input : inference_input) {
        std::int16_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_int16_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::GetNullableValue(input), &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::int16_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_int16_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(flush) {
        std::int16_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_int16_Flush(pTransformerHandle, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::int16_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_int16_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(BackwardFillImputerFeaturizer_int16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <int32> */
template <typename VectorInputT>
void BackwardFillImputerFeaturizer_int32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::int32_t>> const &)> const &verify_func,
    bool flush=true
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    BackwardFillImputerFeaturizer_int32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_int32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(BackwardFillImputerFeaturizer_int32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(BackwardFillImputerFeaturizer_int32_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(BackwardFillImputerFeaturizer_int32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    BackwardFillImputerFeaturizer_int32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(BackwardFillImputerFeaturizer_int32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    BackwardFillImputerFeaturizer_int32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_int32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(BackwardFillImputerFeaturizer_int32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::int32_t>> results;

    for(auto const & input : inference_input) {
        std::int32_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_int32_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::GetNullableValue(input), &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::int32_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_int32_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(flush) {
        std::int32_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_int32_Flush(pTransformerHandle, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::int32_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_int32_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(BackwardFillImputerFeaturizer_int32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <int64> */
template <typename VectorInputT>
void BackwardFillImputerFeaturizer_int64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::int64_t>> const &)> const &verify_func,
    bool flush=true
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    BackwardFillImputerFeaturizer_int64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_int64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(BackwardFillImputerFeaturizer_int64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(BackwardFillImputerFeaturizer_int64_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(BackwardFillImputerFeaturizer_int64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    BackwardFillImputerFeaturizer_int64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(BackwardFillImputerFeaturizer_int64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    BackwardFillImputerFeaturizer_int64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_int64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(BackwardFillImputerFeaturizer_int64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::int64_t>> results;

    for(auto const & input : inference_input) {
        std::int64_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_int64_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::GetNullableValue(input), &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::int64_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_int64_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(flush) {
        std::int64_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_int64_Flush(pTransformerHandle, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::int64_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_int64_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(BackwardFillImputerFeaturizer_int64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <uint8> */
template <typename VectorInputT>
void BackwardFillImputerFeaturizer_uint8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::uint8_t>> const &)> const &verify_func,
    bool flush=true
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    BackwardFillImputerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_uint8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(BackwardFillImputerFeaturizer_uint8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(BackwardFillImputerFeaturizer_uint8_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(BackwardFillImputerFeaturizer_uint8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    BackwardFillImputerFeaturizer_uint8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(BackwardFillImputerFeaturizer_uint8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    BackwardFillImputerFeaturizer_uint8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_uint8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(BackwardFillImputerFeaturizer_uint8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::uint8_t>> results;

    for(auto const & input : inference_input) {
        std::uint8_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_uint8_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::GetNullableValue(input), &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::uint8_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_uint8_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(flush) {
        std::uint8_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_uint8_Flush(pTransformerHandle, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::uint8_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_uint8_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(BackwardFillImputerFeaturizer_uint8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <uint16> */
template <typename VectorInputT>
void BackwardFillImputerFeaturizer_uint16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::uint16_t>> const &)> const &verify_func,
    bool flush=true
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    BackwardFillImputerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_uint16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(BackwardFillImputerFeaturizer_uint16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(BackwardFillImputerFeaturizer_uint16_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(BackwardFillImputerFeaturizer_uint16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    BackwardFillImputerFeaturizer_uint16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(BackwardFillImputerFeaturizer_uint16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    BackwardFillImputerFeaturizer_uint16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_uint16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(BackwardFillImputerFeaturizer_uint16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::uint16_t>> results;

    for(auto const & input : inference_input) {
        std::uint16_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_uint16_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::GetNullableValue(input), &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::uint16_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_uint16_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(flush) {
        std::uint16_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_uint16_Flush(pTransformerHandle, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::uint16_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_uint16_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(BackwardFillImputerFeaturizer_uint16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <uint32> */
template <typename VectorInputT>
void BackwardFillImputerFeaturizer_uint32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::uint32_t>> const &)> const &verify_func,
    bool flush=true
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    BackwardFillImputerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_uint32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(BackwardFillImputerFeaturizer_uint32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(BackwardFillImputerFeaturizer_uint32_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(BackwardFillImputerFeaturizer_uint32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    BackwardFillImputerFeaturizer_uint32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(BackwardFillImputerFeaturizer_uint32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    BackwardFillImputerFeaturizer_uint32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_uint32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(BackwardFillImputerFeaturizer_uint32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::uint32_t>> results;

    for(auto const & input : inference_input) {
        std::uint32_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_uint32_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::GetNullableValue(input), &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::uint32_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_uint32_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(flush) {
        std::uint32_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_uint32_Flush(pTransformerHandle, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::uint32_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_uint32_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(BackwardFillImputerFeaturizer_uint32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <uint64> */
template <typename VectorInputT>
void BackwardFillImputerFeaturizer_uint64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::uint64_t>> const &)> const &verify_func,
    bool flush=true
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    BackwardFillImputerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_uint64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(BackwardFillImputerFeaturizer_uint64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(BackwardFillImputerFeaturizer_uint64_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(BackwardFillImputerFeaturizer_uint64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    BackwardFillImputerFeaturizer_uint64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(BackwardFillImputerFeaturizer_uint64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    BackwardFillImputerFeaturizer_uint64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_uint64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(BackwardFillImputerFeaturizer_uint64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::uint64_t>> results;

    for(auto const & input : inference_input) {
        std::uint64_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_uint64_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::GetNullableValue(input), &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::uint64_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_uint64_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(flush) {
        std::uint64_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_uint64_Flush(pTransformerHandle, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::uint64_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_uint64_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(BackwardFillImputerFeaturizer_uint64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <float> */
template <typename VectorInputT>
void BackwardFillImputerFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::float_t>> const &)> const &verify_func,
    bool flush=true
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    BackwardFillImputerFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_float_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(BackwardFillImputerFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(BackwardFillImputerFeaturizer_float_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(BackwardFillImputerFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    BackwardFillImputerFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(BackwardFillImputerFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    BackwardFillImputerFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(BackwardFillImputerFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::float_t>> results;

    for(auto const & input : inference_input) {
        std::float_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_float_Transform(pTransformerHandle, input, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::float_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_float_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(flush) {
        std::float_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_float_Flush(pTransformerHandle, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::float_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_float_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(BackwardFillImputerFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <double> */
template <typename VectorInputT>
void BackwardFillImputerFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func,
    bool flush=true
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    BackwardFillImputerFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_double_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(BackwardFillImputerFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(BackwardFillImputerFeaturizer_double_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(BackwardFillImputerFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    BackwardFillImputerFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(BackwardFillImputerFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    BackwardFillImputerFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(BackwardFillImputerFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    for(auto const & input : inference_input) {
        std::double_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_double_Transform(pTransformerHandle, input, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_double_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(flush) {
        std::double_t* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_double_Flush(pTransformerHandle, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_double_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(BackwardFillImputerFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <bool> */
template <typename VectorInputT>
void BackwardFillImputerFeaturizer_bool_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<bool>> const &)> const &verify_func,
    bool flush=true
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    BackwardFillImputerFeaturizer_bool_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_bool_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(BackwardFillImputerFeaturizer_bool_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(BackwardFillImputerFeaturizer_bool_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(BackwardFillImputerFeaturizer_bool_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    BackwardFillImputerFeaturizer_bool_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(BackwardFillImputerFeaturizer_bool_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    BackwardFillImputerFeaturizer_bool_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_bool_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(BackwardFillImputerFeaturizer_bool_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<bool>> results;

    for(bool input : inference_input) {
        bool* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_bool_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::GetNullableValue(input), &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<bool>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_bool_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(flush) {
        bool* result_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_bool_Flush(pTransformerHandle, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<bool>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_bool_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(BackwardFillImputerFeaturizer_bool_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  BackwardFillImputerFeaturizer <string> */
template <typename VectorInputT>
void BackwardFillImputerFeaturizer_string_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::string>> const &)> const &verify_func,
    bool flush=true
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    BackwardFillImputerFeaturizer_string_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_string_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(BackwardFillImputerFeaturizer_string_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(BackwardFillImputerFeaturizer_string_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<nonstd::optional<std::string>>::IsNull(input) ? nullptr : input->c_str(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(BackwardFillImputerFeaturizer_string_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    BackwardFillImputerFeaturizer_string_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(BackwardFillImputerFeaturizer_string_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    BackwardFillImputerFeaturizer_string_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(BackwardFillImputerFeaturizer_string_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(BackwardFillImputerFeaturizer_string_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::string>> results;

    for(auto const & input : inference_input) {
        char const ** result_ptr_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_string_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<nonstd::optional<std::string>>::IsNull(input) ? nullptr : input->c_str(), &result_ptr_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::string>(result_ptr_ptr, result_ptr_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_string_DestroyTransformedData(result_ptr_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(flush) {
        char const ** result_ptr_ptr;
        size_t result_items;

        REQUIRE(BackwardFillImputerFeaturizer_string_Flush(pTransformerHandle, &result_ptr_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::string>(result_ptr_ptr, result_ptr_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(BackwardFillImputerFeaturizer_string_DestroyTransformedData(result_ptr_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(BackwardFillImputerFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
