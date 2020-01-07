/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_MissingDummiesFeaturizer.h"
#include "Traits.h"

#include "SharedLibrary_Common.hpp"

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int8> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_int8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_int8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MissingDummiesFeaturizer_int8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_int8_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::int8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::int8_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MissingDummiesFeaturizer_int8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MissingDummiesFeaturizer_int8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_int8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_int8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_int8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(MissingDummiesFeaturizer_int8_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<std::int8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::int8_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(std::move(result));
        #else
        results.emplace_back(std::move(result));
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MissingDummiesFeaturizer_int8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int16> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_int16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_int16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MissingDummiesFeaturizer_int16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_int16_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::int16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::int16_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MissingDummiesFeaturizer_int16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MissingDummiesFeaturizer_int16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_int16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_int16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_int16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(MissingDummiesFeaturizer_int16_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<std::int16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::int16_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(std::move(result));
        #else
        results.emplace_back(std::move(result));
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MissingDummiesFeaturizer_int16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int32> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_int32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_int32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MissingDummiesFeaturizer_int32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_int32_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::int32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::int32_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MissingDummiesFeaturizer_int32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MissingDummiesFeaturizer_int32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_int32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_int32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_int32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(MissingDummiesFeaturizer_int32_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<std::int32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::int32_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(std::move(result));
        #else
        results.emplace_back(std::move(result));
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MissingDummiesFeaturizer_int32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int64> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_int64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_int64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MissingDummiesFeaturizer_int64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_int64_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::int64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::int64_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MissingDummiesFeaturizer_int64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MissingDummiesFeaturizer_int64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_int64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_int64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_int64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(MissingDummiesFeaturizer_int64_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<std::int64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::int64_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(std::move(result));
        #else
        results.emplace_back(std::move(result));
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MissingDummiesFeaturizer_int64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint8> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_uint8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_uint8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MissingDummiesFeaturizer_uint8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_uint8_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::uint8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::uint8_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MissingDummiesFeaturizer_uint8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MissingDummiesFeaturizer_uint8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_uint8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_uint8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_uint8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(MissingDummiesFeaturizer_uint8_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<std::uint8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::uint8_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(std::move(result));
        #else
        results.emplace_back(std::move(result));
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MissingDummiesFeaturizer_uint8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint16> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_uint16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_uint16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MissingDummiesFeaturizer_uint16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_uint16_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::uint16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::uint16_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MissingDummiesFeaturizer_uint16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MissingDummiesFeaturizer_uint16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_uint16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_uint16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_uint16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(MissingDummiesFeaturizer_uint16_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<std::uint16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::uint16_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(std::move(result));
        #else
        results.emplace_back(std::move(result));
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MissingDummiesFeaturizer_uint16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint32> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_uint32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_uint32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MissingDummiesFeaturizer_uint32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_uint32_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::uint32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::uint32_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MissingDummiesFeaturizer_uint32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MissingDummiesFeaturizer_uint32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_uint32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_uint32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_uint32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(MissingDummiesFeaturizer_uint32_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<std::uint32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::uint32_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(std::move(result));
        #else
        results.emplace_back(std::move(result));
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MissingDummiesFeaturizer_uint32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint64> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_uint64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_uint64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MissingDummiesFeaturizer_uint64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_uint64_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::uint64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::uint64_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MissingDummiesFeaturizer_uint64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MissingDummiesFeaturizer_uint64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_uint64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_uint64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_uint64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(MissingDummiesFeaturizer_uint64_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<std::uint64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::uint64_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(std::move(result));
        #else
        results.emplace_back(std::move(result));
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MissingDummiesFeaturizer_uint64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <float> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_float_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MissingDummiesFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_float_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::float_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::float_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MissingDummiesFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MissingDummiesFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(MissingDummiesFeaturizer_float_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<std::float_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::float_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(std::move(result));
        #else
        results.emplace_back(std::move(result));
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MissingDummiesFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <double> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_double_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MissingDummiesFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_double_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::double_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::double_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MissingDummiesFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MissingDummiesFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(MissingDummiesFeaturizer_double_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<std::double_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<std::double_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(std::move(result));
        #else
        results.emplace_back(std::move(result));
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MissingDummiesFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <bool> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_bool_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_bool_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_bool_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MissingDummiesFeaturizer_bool_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_bool_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<bool>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<bool>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MissingDummiesFeaturizer_bool_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MissingDummiesFeaturizer_bool_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_bool_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_bool_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_bool_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_bool_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(MissingDummiesFeaturizer_bool_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<bool>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<bool>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(std::move(result));
        #else
        results.emplace_back(std::move(result));
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MissingDummiesFeaturizer_bool_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <string> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_string_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_string_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_string_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(MissingDummiesFeaturizer_string_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_string_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::string>::IsNull(input) ? nullptr : input->c_str(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(MissingDummiesFeaturizer_string_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    MissingDummiesFeaturizer_string_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_string_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_string_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_string_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_string_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(MissingDummiesFeaturizer_string_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<std::string>::IsNull(input) ? nullptr : input->c_str(), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(std::move(result));
        #else
        results.emplace_back(std::move(result));
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(MissingDummiesFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

