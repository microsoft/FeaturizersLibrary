/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_ImputationMarkerFeaturizer.h"

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
/* |  ImputationMarkerFeaturizer <int8> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_int8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_int8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ImputationMarkerFeaturizer_int8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_int8_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ImputationMarkerFeaturizer_int8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ImputationMarkerFeaturizer_int8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_int8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_int8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_int8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_int8_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_int8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int16> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_int16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_int16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ImputationMarkerFeaturizer_int16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_int16_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ImputationMarkerFeaturizer_int16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ImputationMarkerFeaturizer_int16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_int16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_int16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_int16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_int16_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_int16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int32> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_int32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_int32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ImputationMarkerFeaturizer_int32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_int32_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ImputationMarkerFeaturizer_int32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ImputationMarkerFeaturizer_int32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_int32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_int32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_int32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_int32_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_int32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int64> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_int64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_int64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ImputationMarkerFeaturizer_int64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_int64_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ImputationMarkerFeaturizer_int64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ImputationMarkerFeaturizer_int64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_int64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_int64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_int64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_int64_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_int64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint8> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_uint8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ImputationMarkerFeaturizer_uint8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_uint8_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ImputationMarkerFeaturizer_uint8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ImputationMarkerFeaturizer_uint8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_uint8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_uint8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_uint8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_uint8_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_uint8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint16> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_uint16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ImputationMarkerFeaturizer_uint16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_uint16_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ImputationMarkerFeaturizer_uint16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ImputationMarkerFeaturizer_uint16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_uint16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_uint16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_uint16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_uint16_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_uint16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint32> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_uint32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ImputationMarkerFeaturizer_uint32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_uint32_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ImputationMarkerFeaturizer_uint32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ImputationMarkerFeaturizer_uint32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_uint32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_uint32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_uint32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_uint32_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_uint32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint64> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_uint64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ImputationMarkerFeaturizer_uint64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_uint64_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ImputationMarkerFeaturizer_uint64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ImputationMarkerFeaturizer_uint64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_uint64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_uint64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_uint64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_uint64_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_uint64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <float> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_float_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ImputationMarkerFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_float_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ImputationMarkerFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ImputationMarkerFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_float_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <double> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_double_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ImputationMarkerFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_double_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ImputationMarkerFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ImputationMarkerFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_double_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <bool> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_bool_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_bool_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_bool_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ImputationMarkerFeaturizer_bool_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_bool_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ImputationMarkerFeaturizer_bool_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ImputationMarkerFeaturizer_bool_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_bool_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_bool_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_bool_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_bool_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(bool input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_bool_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_bool_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <string> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_string_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_string_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_string_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ImputationMarkerFeaturizer_string_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_string_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<nonstd::optional<std::string>>::IsNull(input) ? nullptr : input->c_str(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ImputationMarkerFeaturizer_string_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ImputationMarkerFeaturizer_string_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_string_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_string_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_string_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_string_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_string_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<nonstd::optional<std::string>>::IsNull(input) ? nullptr : input->c_str(), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
