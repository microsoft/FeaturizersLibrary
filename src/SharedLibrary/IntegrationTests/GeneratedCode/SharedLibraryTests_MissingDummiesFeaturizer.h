/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_MissingDummiesFeaturizer.h"
#include "Traits.h"

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int8_t> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_int8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int8_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_int8_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<int8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int8_t>::GetNullableValue(input), &result, &pErrorInfo));
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

    MissingDummiesFeaturizer_int8_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_int8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_int8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_int8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int8_t result;

        REQUIRE(MissingDummiesFeaturizer_int8_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<int8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int8_t>::GetNullableValue(input), &result, &pErrorInfo));
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
    REQUIRE(MissingDummiesFeaturizer_int8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int16_t> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_int16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int16_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_int16_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<int16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int16_t>::GetNullableValue(input), &result, &pErrorInfo));
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

    MissingDummiesFeaturizer_int16_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_int16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_int16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_int16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int8_t result;

        REQUIRE(MissingDummiesFeaturizer_int16_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<int16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int16_t>::GetNullableValue(input), &result, &pErrorInfo));
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
    REQUIRE(MissingDummiesFeaturizer_int16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int32_t> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_int32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int32_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_int32_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<int32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int32_t>::GetNullableValue(input), &result, &pErrorInfo));
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

    MissingDummiesFeaturizer_int32_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_int32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_int32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_int32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int8_t result;

        REQUIRE(MissingDummiesFeaturizer_int32_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<int32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int32_t>::GetNullableValue(input), &result, &pErrorInfo));
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
    REQUIRE(MissingDummiesFeaturizer_int32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <int64_t> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_int64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int64_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_int64_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<int64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int64_t>::GetNullableValue(input), &result, &pErrorInfo));
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

    MissingDummiesFeaturizer_int64_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_int64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_int64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_int64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_int64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int8_t result;

        REQUIRE(MissingDummiesFeaturizer_int64_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<int64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int64_t>::GetNullableValue(input), &result, &pErrorInfo));
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
    REQUIRE(MissingDummiesFeaturizer_int64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint8_t> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_uint8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint8_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_uint8_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<uint8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint8_t>::GetNullableValue(input), &result, &pErrorInfo));
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

    MissingDummiesFeaturizer_uint8_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_uint8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_uint8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_uint8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int8_t result;

        REQUIRE(MissingDummiesFeaturizer_uint8_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<uint8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint8_t>::GetNullableValue(input), &result, &pErrorInfo));
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
    REQUIRE(MissingDummiesFeaturizer_uint8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint16_t> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_uint16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint16_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_uint16_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<uint16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint16_t>::GetNullableValue(input), &result, &pErrorInfo));
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

    MissingDummiesFeaturizer_uint16_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_uint16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_uint16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_uint16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int8_t result;

        REQUIRE(MissingDummiesFeaturizer_uint16_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<uint16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint16_t>::GetNullableValue(input), &result, &pErrorInfo));
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
    REQUIRE(MissingDummiesFeaturizer_uint16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint32_t> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_uint32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint32_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_uint32_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<uint32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint32_t>::GetNullableValue(input), &result, &pErrorInfo));
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

    MissingDummiesFeaturizer_uint32_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_uint32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_uint32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_uint32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int8_t result;

        REQUIRE(MissingDummiesFeaturizer_uint32_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<uint32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint32_t>::GetNullableValue(input), &result, &pErrorInfo));
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
    REQUIRE(MissingDummiesFeaturizer_uint32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <uint64_t> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_uint64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint64_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_uint64_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<uint64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint64_t>::GetNullableValue(input), &result, &pErrorInfo));
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

    MissingDummiesFeaturizer_uint64_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_uint64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_uint64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_uint64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_uint64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int8_t result;

        REQUIRE(MissingDummiesFeaturizer_uint64_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<uint64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint64_t>::GetNullableValue(input), &result, &pErrorInfo));
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
    REQUIRE(MissingDummiesFeaturizer_uint64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <float_t> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_float_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_float_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_float_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_float_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<float>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<float>::GetNullableValue(input), &result, &pErrorInfo));
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

    MissingDummiesFeaturizer_float_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_float_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_float_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_float_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_float_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int8_t result;

        REQUIRE(MissingDummiesFeaturizer_float_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<float>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<float>::GetNullableValue(input), &result, &pErrorInfo));
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
    REQUIRE(MissingDummiesFeaturizer_float_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <double_t> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_double_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    MissingDummiesFeaturizer_double_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_double_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_double_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<double>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<double>::GetNullableValue(input), &result, &pErrorInfo));
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

    MissingDummiesFeaturizer_double_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(MissingDummiesFeaturizer_double_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    MissingDummiesFeaturizer_double_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(MissingDummiesFeaturizer_double_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(MissingDummiesFeaturizer_double_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int8_t result;

        REQUIRE(MissingDummiesFeaturizer_double_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<double>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<double>::GetNullableValue(input), &result, &pErrorInfo));
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
    REQUIRE(MissingDummiesFeaturizer_double_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  MissingDummiesFeaturizer <bool> */
template <typename VectorInputT>
void MissingDummiesFeaturizer_bool_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int8_t> const &)> const &verify_func
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
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_bool_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<bool>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<bool>::GetNullableValue(input), &result, &pErrorInfo));
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
    std::vector<int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int8_t result;

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
    std::function<bool (std::vector<int8_t> const &)> const &verify_func
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
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(MissingDummiesFeaturizer_string_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::string>::IsNull(input) ? nullptr : input->c_str(), &result, &pErrorInfo));
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
    std::vector<int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int8_t result;

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

