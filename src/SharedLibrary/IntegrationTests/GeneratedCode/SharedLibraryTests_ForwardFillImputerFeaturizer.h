/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_ForwardFillImputerFeaturizer.h"

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
/* |  ForwardFillImputerFeaturizer <int8> */
template <typename VectorInputT>
void ForwardFillImputerFeaturizer_int8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForwardFillImputerFeaturizer_int8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_int8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForwardFillImputerFeaturizer_int8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ForwardFillImputerFeaturizer_int8_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForwardFillImputerFeaturizer_int8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForwardFillImputerFeaturizer_int8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForwardFillImputerFeaturizer_int8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForwardFillImputerFeaturizer_int8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_int8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForwardFillImputerFeaturizer_int8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(ForwardFillImputerFeaturizer_int8_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForwardFillImputerFeaturizer_int8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <int16> */
template <typename VectorInputT>
void ForwardFillImputerFeaturizer_int16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int16_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForwardFillImputerFeaturizer_int16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_int16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForwardFillImputerFeaturizer_int16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ForwardFillImputerFeaturizer_int16_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForwardFillImputerFeaturizer_int16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForwardFillImputerFeaturizer_int16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForwardFillImputerFeaturizer_int16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForwardFillImputerFeaturizer_int16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_int16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForwardFillImputerFeaturizer_int16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int16_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int16_t result;

        REQUIRE(ForwardFillImputerFeaturizer_int16_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForwardFillImputerFeaturizer_int16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <int32> */
template <typename VectorInputT>
void ForwardFillImputerFeaturizer_int32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int32_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForwardFillImputerFeaturizer_int32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_int32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForwardFillImputerFeaturizer_int32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ForwardFillImputerFeaturizer_int32_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForwardFillImputerFeaturizer_int32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForwardFillImputerFeaturizer_int32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForwardFillImputerFeaturizer_int32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForwardFillImputerFeaturizer_int32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_int32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForwardFillImputerFeaturizer_int32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int32_t result;

        REQUIRE(ForwardFillImputerFeaturizer_int32_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForwardFillImputerFeaturizer_int32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <int64> */
template <typename VectorInputT>
void ForwardFillImputerFeaturizer_int64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int64_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForwardFillImputerFeaturizer_int64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_int64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForwardFillImputerFeaturizer_int64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ForwardFillImputerFeaturizer_int64_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForwardFillImputerFeaturizer_int64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForwardFillImputerFeaturizer_int64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForwardFillImputerFeaturizer_int64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForwardFillImputerFeaturizer_int64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_int64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForwardFillImputerFeaturizer_int64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int64_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int64_t result;

        REQUIRE(ForwardFillImputerFeaturizer_int64_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForwardFillImputerFeaturizer_int64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <uint8> */
template <typename VectorInputT>
void ForwardFillImputerFeaturizer_uint8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::uint8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForwardFillImputerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_uint8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForwardFillImputerFeaturizer_uint8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ForwardFillImputerFeaturizer_uint8_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForwardFillImputerFeaturizer_uint8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForwardFillImputerFeaturizer_uint8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForwardFillImputerFeaturizer_uint8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForwardFillImputerFeaturizer_uint8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_uint8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForwardFillImputerFeaturizer_uint8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::uint8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::uint8_t result;

        REQUIRE(ForwardFillImputerFeaturizer_uint8_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForwardFillImputerFeaturizer_uint8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <uint16> */
template <typename VectorInputT>
void ForwardFillImputerFeaturizer_uint16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::uint16_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForwardFillImputerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_uint16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForwardFillImputerFeaturizer_uint16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ForwardFillImputerFeaturizer_uint16_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForwardFillImputerFeaturizer_uint16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForwardFillImputerFeaturizer_uint16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForwardFillImputerFeaturizer_uint16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForwardFillImputerFeaturizer_uint16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_uint16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForwardFillImputerFeaturizer_uint16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::uint16_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::uint16_t result;

        REQUIRE(ForwardFillImputerFeaturizer_uint16_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForwardFillImputerFeaturizer_uint16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <uint32> */
template <typename VectorInputT>
void ForwardFillImputerFeaturizer_uint32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::uint32_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForwardFillImputerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_uint32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForwardFillImputerFeaturizer_uint32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ForwardFillImputerFeaturizer_uint32_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForwardFillImputerFeaturizer_uint32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForwardFillImputerFeaturizer_uint32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForwardFillImputerFeaturizer_uint32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForwardFillImputerFeaturizer_uint32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_uint32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForwardFillImputerFeaturizer_uint32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::uint32_t result;

        REQUIRE(ForwardFillImputerFeaturizer_uint32_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForwardFillImputerFeaturizer_uint32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <uint64> */
template <typename VectorInputT>
void ForwardFillImputerFeaturizer_uint64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::uint64_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForwardFillImputerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_uint64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForwardFillImputerFeaturizer_uint64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ForwardFillImputerFeaturizer_uint64_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForwardFillImputerFeaturizer_uint64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForwardFillImputerFeaturizer_uint64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForwardFillImputerFeaturizer_uint64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForwardFillImputerFeaturizer_uint64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_uint64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForwardFillImputerFeaturizer_uint64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::uint64_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::uint64_t result;

        REQUIRE(ForwardFillImputerFeaturizer_uint64_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForwardFillImputerFeaturizer_uint64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <float> */
template <typename VectorInputT>
void ForwardFillImputerFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::float_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForwardFillImputerFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_float_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForwardFillImputerFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ForwardFillImputerFeaturizer_float_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForwardFillImputerFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForwardFillImputerFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForwardFillImputerFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForwardFillImputerFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForwardFillImputerFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::float_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::float_t result;

        REQUIRE(ForwardFillImputerFeaturizer_float_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForwardFillImputerFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <double> */
template <typename VectorInputT>
void ForwardFillImputerFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::double_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForwardFillImputerFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_double_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForwardFillImputerFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ForwardFillImputerFeaturizer_double_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForwardFillImputerFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForwardFillImputerFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForwardFillImputerFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForwardFillImputerFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForwardFillImputerFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::double_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t result;

        REQUIRE(ForwardFillImputerFeaturizer_double_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForwardFillImputerFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <bool> */
template <typename VectorInputT>
void ForwardFillImputerFeaturizer_bool_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForwardFillImputerFeaturizer_bool_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_bool_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForwardFillImputerFeaturizer_bool_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ForwardFillImputerFeaturizer_bool_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForwardFillImputerFeaturizer_bool_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForwardFillImputerFeaturizer_bool_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForwardFillImputerFeaturizer_bool_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForwardFillImputerFeaturizer_bool_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_bool_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForwardFillImputerFeaturizer_bool_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(bool input : inference_input) {
        bool result;

        REQUIRE(ForwardFillImputerFeaturizer_bool_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForwardFillImputerFeaturizer_bool_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ForwardFillImputerFeaturizer <string> */
template <typename VectorInputT>
void ForwardFillImputerFeaturizer_string_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForwardFillImputerFeaturizer_string_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_string_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForwardFillImputerFeaturizer_string_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ForwardFillImputerFeaturizer_string_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<nonstd::optional<std::string>>::IsNull(input) ? nullptr : input->c_str(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForwardFillImputerFeaturizer_string_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForwardFillImputerFeaturizer_string_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForwardFillImputerFeaturizer_string_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForwardFillImputerFeaturizer_string_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForwardFillImputerFeaturizer_string_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForwardFillImputerFeaturizer_string_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr;

        REQUIRE(ForwardFillImputerFeaturizer_string_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<nonstd::optional<std::string>>::IsNull(input) ? nullptr : input->c_str(), &result_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result_ptr ? std::string(result_ptr) : std::string());
        
        // Destroy the contents
        REQUIRE(ForwardFillImputerFeaturizer_string_DestroyTransformedData(result_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForwardFillImputerFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
