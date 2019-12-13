/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_LabelEncoderFeaturizer.h"
#include "Traits.h"

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <int8_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LabelEncoderFeaturizer_int8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint32_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LabelEncoderFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_int8_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(LabelEncoderFeaturizer_int8_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    LabelEncoderFeaturizer_int8_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LabelEncoderFeaturizer_int8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LabelEncoderFeaturizer_int8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_int8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LabelEncoderFeaturizer_int8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint32_t result;

        REQUIRE(LabelEncoderFeaturizer_int8_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
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
    REQUIRE(LabelEncoderFeaturizer_int8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <int16_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LabelEncoderFeaturizer_int16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint32_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LabelEncoderFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_int16_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(LabelEncoderFeaturizer_int16_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    LabelEncoderFeaturizer_int16_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LabelEncoderFeaturizer_int16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LabelEncoderFeaturizer_int16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_int16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LabelEncoderFeaturizer_int16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint32_t result;

        REQUIRE(LabelEncoderFeaturizer_int16_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
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
    REQUIRE(LabelEncoderFeaturizer_int16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <int32_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LabelEncoderFeaturizer_int32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint32_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LabelEncoderFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_int32_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(LabelEncoderFeaturizer_int32_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    LabelEncoderFeaturizer_int32_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LabelEncoderFeaturizer_int32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LabelEncoderFeaturizer_int32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_int32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LabelEncoderFeaturizer_int32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint32_t result;

        REQUIRE(LabelEncoderFeaturizer_int32_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
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
    REQUIRE(LabelEncoderFeaturizer_int32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <int64_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LabelEncoderFeaturizer_int64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint32_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LabelEncoderFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_int64_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(LabelEncoderFeaturizer_int64_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    LabelEncoderFeaturizer_int64_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LabelEncoderFeaturizer_int64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LabelEncoderFeaturizer_int64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_int64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LabelEncoderFeaturizer_int64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint32_t result;

        REQUIRE(LabelEncoderFeaturizer_int64_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
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
    REQUIRE(LabelEncoderFeaturizer_int64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <uint8_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LabelEncoderFeaturizer_uint8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint32_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LabelEncoderFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_uint8_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(LabelEncoderFeaturizer_uint8_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    LabelEncoderFeaturizer_uint8_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LabelEncoderFeaturizer_uint8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LabelEncoderFeaturizer_uint8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_uint8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LabelEncoderFeaturizer_uint8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint32_t result;

        REQUIRE(LabelEncoderFeaturizer_uint8_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
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
    REQUIRE(LabelEncoderFeaturizer_uint8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <uint16_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LabelEncoderFeaturizer_uint16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint32_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LabelEncoderFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_uint16_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(LabelEncoderFeaturizer_uint16_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    LabelEncoderFeaturizer_uint16_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LabelEncoderFeaturizer_uint16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LabelEncoderFeaturizer_uint16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_uint16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LabelEncoderFeaturizer_uint16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint32_t result;

        REQUIRE(LabelEncoderFeaturizer_uint16_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
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
    REQUIRE(LabelEncoderFeaturizer_uint16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <uint32_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LabelEncoderFeaturizer_uint32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint32_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LabelEncoderFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_uint32_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(LabelEncoderFeaturizer_uint32_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    LabelEncoderFeaturizer_uint32_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LabelEncoderFeaturizer_uint32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LabelEncoderFeaturizer_uint32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_uint32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LabelEncoderFeaturizer_uint32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint32_t result;

        REQUIRE(LabelEncoderFeaturizer_uint32_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
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
    REQUIRE(LabelEncoderFeaturizer_uint32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <uint64_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LabelEncoderFeaturizer_uint64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint32_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LabelEncoderFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_uint64_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(LabelEncoderFeaturizer_uint64_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    LabelEncoderFeaturizer_uint64_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LabelEncoderFeaturizer_uint64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LabelEncoderFeaturizer_uint64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_uint64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LabelEncoderFeaturizer_uint64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint32_t result;

        REQUIRE(LabelEncoderFeaturizer_uint64_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
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
    REQUIRE(LabelEncoderFeaturizer_uint64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <float_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LabelEncoderFeaturizer_float_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint32_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LabelEncoderFeaturizer_float_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_float_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(LabelEncoderFeaturizer_float_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    LabelEncoderFeaturizer_float_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LabelEncoderFeaturizer_float_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LabelEncoderFeaturizer_float_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_float_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LabelEncoderFeaturizer_float_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint32_t result;

        REQUIRE(LabelEncoderFeaturizer_float_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
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
    REQUIRE(LabelEncoderFeaturizer_float_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <double_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LabelEncoderFeaturizer_double_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint32_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LabelEncoderFeaturizer_double_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_double_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(LabelEncoderFeaturizer_double_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    LabelEncoderFeaturizer_double_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LabelEncoderFeaturizer_double_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LabelEncoderFeaturizer_double_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_double_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LabelEncoderFeaturizer_double_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint32_t result;

        REQUIRE(LabelEncoderFeaturizer_double_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
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
    REQUIRE(LabelEncoderFeaturizer_double_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <bool> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LabelEncoderFeaturizer_bool_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint32_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LabelEncoderFeaturizer_bool_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_bool_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(LabelEncoderFeaturizer_bool_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    LabelEncoderFeaturizer_bool_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LabelEncoderFeaturizer_bool_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LabelEncoderFeaturizer_bool_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_bool_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LabelEncoderFeaturizer_bool_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint32_t result;

        REQUIRE(LabelEncoderFeaturizer_bool_Transform(pTransformerHandle, input, &result, &pErrorInfo));
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
    REQUIRE(LabelEncoderFeaturizer_bool_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  LabelEncoderFeaturizer <string> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LabelEncoderFeaturizer_string_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint32_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LabelEncoderFeaturizer_string_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_string_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(LabelEncoderFeaturizer_string_Fit(pEstimatorHandle, input.c_str(), &result, &pErrorInfo));
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

    LabelEncoderFeaturizer_string_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LabelEncoderFeaturizer_string_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LabelEncoderFeaturizer_string_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LabelEncoderFeaturizer_string_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LabelEncoderFeaturizer_string_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint32_t result;

        REQUIRE(LabelEncoderFeaturizer_string_Transform(pTransformerHandle, input.c_str(), &result, &pErrorInfo));
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
    REQUIRE(LabelEncoderFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

