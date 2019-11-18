/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_ImputationMarkerFeaturizer.h"
#include "Traits.h"

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int8_t> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_int8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int8_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_int8_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<int8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int8_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == Complete)
                break;

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            if(result == Continue) {
                ++iter;

                if(iter != training_input.end())
                    continue;

                break;
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

    ImputationMarkerFeaturizer_int8_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_int8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_int8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_int8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_int8_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<int8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int8_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_int8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int16_t> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_int16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int16_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_int16_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<int16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int16_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == Complete)
                break;

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            if(result == Continue) {
                ++iter;

                if(iter != training_input.end())
                    continue;

                break;
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

    ImputationMarkerFeaturizer_int16_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_int16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_int16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_int16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_int16_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<int16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int16_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_int16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int32_t> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_int32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int32_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_int32_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<int32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int32_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == Complete)
                break;

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            if(result == Continue) {
                ++iter;

                if(iter != training_input.end())
                    continue;

                break;
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

    ImputationMarkerFeaturizer_int32_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_int32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_int32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_int32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_int32_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<int32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int32_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_int32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <int64_t> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_int64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int64_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_int64_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<int64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int64_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == Complete)
                break;

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            if(result == Continue) {
                ++iter;

                if(iter != training_input.end())
                    continue;

                break;
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

    ImputationMarkerFeaturizer_int64_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_int64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_int64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_int64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_int64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_int64_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<int64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int64_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_int64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint8_t> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_uint8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint8_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_uint8_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<uint8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint8_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == Complete)
                break;

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            if(result == Continue) {
                ++iter;

                if(iter != training_input.end())
                    continue;

                break;
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

    ImputationMarkerFeaturizer_uint8_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_uint8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_uint8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_uint8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_uint8_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<uint8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint8_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_uint8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint16_t> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_uint16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint16_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_uint16_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<uint16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint16_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == Complete)
                break;

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            if(result == Continue) {
                ++iter;

                if(iter != training_input.end())
                    continue;

                break;
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

    ImputationMarkerFeaturizer_uint16_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_uint16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_uint16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_uint16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_uint16_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<uint16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint16_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_uint16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint32_t> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_uint32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint32_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_uint32_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<uint32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint32_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == Complete)
                break;

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            if(result == Continue) {
                ++iter;

                if(iter != training_input.end())
                    continue;

                break;
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

    ImputationMarkerFeaturizer_uint32_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_uint32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_uint32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_uint32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_uint32_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<uint32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint32_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_uint32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <uint64_t> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_uint64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint64_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_uint64_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<uint64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint64_t>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == Complete)
                break;

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            if(result == Continue) {
                ++iter;

                if(iter != training_input.end())
                    continue;

                break;
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

    ImputationMarkerFeaturizer_uint64_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_uint64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_uint64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_uint64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_uint64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_uint64_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<uint64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint64_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_uint64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <float_t> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_float_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_float_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_float_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_float_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<float>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<float>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == Complete)
                break;

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            if(result == Continue) {
                ++iter;

                if(iter != training_input.end())
                    continue;

                break;
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

    ImputationMarkerFeaturizer_float_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_float_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_float_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_float_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_float_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_float_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<float>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<float>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_float_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ImputationMarkerFeaturizer <double_t> */
template <typename VectorInputT>
void ImputationMarkerFeaturizer_double_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ImputationMarkerFeaturizer_double_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_double_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_double_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<double>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<double>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == Complete)
                break;

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            if(result == Continue) {
                ++iter;

                if(iter != training_input.end())
                    continue;

                break;
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

    ImputationMarkerFeaturizer_double_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ImputationMarkerFeaturizer_double_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ImputationMarkerFeaturizer_double_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ImputationMarkerFeaturizer_double_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ImputationMarkerFeaturizer_double_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_double_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<double>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<double>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_double_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
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
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_bool_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<bool>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<bool>::GetNullableValue(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == Complete)
                break;

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            if(result == Continue) {
                ++iter;

                if(iter != training_input.end())
                    continue;

                break;
            }

            INFO("Value is " << result)
            REQUIRE(false);
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

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(ImputationMarkerFeaturizer_bool_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<bool>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<bool>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
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
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(ImputationMarkerFeaturizer_string_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::string>::IsNull(input) ? nullptr : input->c_str(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == Complete)
                break;

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            if(result == Continue) {
                ++iter;

                if(iter != training_input.end())
                    continue;

                break;
            }

            INFO("Value is " << result)
            REQUIRE(false);
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

        REQUIRE(ImputationMarkerFeaturizer_string_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<std::string>::IsNull(input) ? nullptr : input->c_str(), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ImputationMarkerFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

