/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_CatImputerFeaturizer.h"

#include "Traits.h"
#include "Featurizers/Structs.h"

#include "SharedLibrary_Common.hpp"

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <int8> */
template <typename VectorInputT>
void CatImputerFeaturizer_int8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_int8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(CatImputerFeaturizer_int8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_int8_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(CatImputerFeaturizer_int8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    CatImputerFeaturizer_int8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(CatImputerFeaturizer_int8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_int8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_int8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int8_t result;

        REQUIRE(CatImputerFeaturizer_int8_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_int8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <int16> */
template <typename VectorInputT>
void CatImputerFeaturizer_int16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int16_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_int16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(CatImputerFeaturizer_int16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_int16_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(CatImputerFeaturizer_int16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    CatImputerFeaturizer_int16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(CatImputerFeaturizer_int16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_int16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_int16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int16_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int16_t result;

        REQUIRE(CatImputerFeaturizer_int16_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_int16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <int32> */
template <typename VectorInputT>
void CatImputerFeaturizer_int32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int32_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_int32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(CatImputerFeaturizer_int32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_int32_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(CatImputerFeaturizer_int32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    CatImputerFeaturizer_int32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(CatImputerFeaturizer_int32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_int32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_int32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int32_t result;

        REQUIRE(CatImputerFeaturizer_int32_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_int32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <int64> */
template <typename VectorInputT>
void CatImputerFeaturizer_int64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::int64_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_int64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(CatImputerFeaturizer_int64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_int64_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(CatImputerFeaturizer_int64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    CatImputerFeaturizer_int64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(CatImputerFeaturizer_int64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_int64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_int64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::int64_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::int64_t result;

        REQUIRE(CatImputerFeaturizer_int64_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::int64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_int64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <uint8> */
template <typename VectorInputT>
void CatImputerFeaturizer_uint8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::uint8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_uint8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint8_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(CatImputerFeaturizer_uint8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_uint8_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(CatImputerFeaturizer_uint8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    CatImputerFeaturizer_uint8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(CatImputerFeaturizer_uint8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_uint8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_uint8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::uint8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::uint8_t result;

        REQUIRE(CatImputerFeaturizer_uint8_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint8_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_uint8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <uint16> */
template <typename VectorInputT>
void CatImputerFeaturizer_uint16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::uint16_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_uint16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint16_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(CatImputerFeaturizer_uint16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_uint16_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(CatImputerFeaturizer_uint16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    CatImputerFeaturizer_uint16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(CatImputerFeaturizer_uint16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_uint16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_uint16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::uint16_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::uint16_t result;

        REQUIRE(CatImputerFeaturizer_uint16_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint16_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_uint16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <uint32> */
template <typename VectorInputT>
void CatImputerFeaturizer_uint32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::uint32_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_uint32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint32_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(CatImputerFeaturizer_uint32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_uint32_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(CatImputerFeaturizer_uint32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    CatImputerFeaturizer_uint32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(CatImputerFeaturizer_uint32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_uint32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_uint32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::uint32_t result;

        REQUIRE(CatImputerFeaturizer_uint32_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint32_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_uint32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <uint64> */
template <typename VectorInputT>
void CatImputerFeaturizer_uint64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::uint64_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_uint64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint64_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(CatImputerFeaturizer_uint64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_uint64_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(CatImputerFeaturizer_uint64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    CatImputerFeaturizer_uint64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(CatImputerFeaturizer_uint64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_uint64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_uint64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::uint64_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::uint64_t result;

        REQUIRE(CatImputerFeaturizer_uint64_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::uint64_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_uint64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <float> */
template <typename VectorInputT>
void CatImputerFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::float_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_float_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(CatImputerFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_float_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::float_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::float_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(CatImputerFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    CatImputerFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(CatImputerFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::float_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::float_t result;

        REQUIRE(CatImputerFeaturizer_float_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::float_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::float_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <double> */
template <typename VectorInputT>
void CatImputerFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::double_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_double_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(CatImputerFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_double_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::double_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::double_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(CatImputerFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    CatImputerFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(CatImputerFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::double_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t result;

        REQUIRE(CatImputerFeaturizer_double_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::double_t>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<std::double_t>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <bool> */
template <typename VectorInputT>
void CatImputerFeaturizer_bool_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_bool_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_bool_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(CatImputerFeaturizer_bool_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_bool_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(CatImputerFeaturizer_bool_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    CatImputerFeaturizer_bool_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(CatImputerFeaturizer_bool_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_bool_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_bool_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_bool_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(bool input : inference_input) {
        bool result;

        REQUIRE(CatImputerFeaturizer_bool_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<typename Microsoft::Featurizer::Traits<bool>::nullable_type>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_bool_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <string> */
template <typename VectorInputT>
void CatImputerFeaturizer_string_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_string_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_string_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(CatImputerFeaturizer_string_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_string_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<nonstd::optional<std::string>>::IsNull(input) ? nullptr : input->c_str(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(CatImputerFeaturizer_string_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    CatImputerFeaturizer_string_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(CatImputerFeaturizer_string_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_string_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_string_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_string_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr(nullptr);

        REQUIRE(CatImputerFeaturizer_string_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<nonstd::optional<std::string>>::IsNull(input) ? nullptr : input->c_str(), &result_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result_ptr ? std::string(result_ptr) : std::string());
        
        // Destroy the contents
        REQUIRE(CatImputerFeaturizer_string_DestroyTransformedData(result_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

