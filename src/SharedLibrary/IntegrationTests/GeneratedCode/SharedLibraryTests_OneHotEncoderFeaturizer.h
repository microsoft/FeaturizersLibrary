/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_OneHotEncoderFeaturizer.h"
#include "Traits.h"

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int8_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_int8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int8_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_int8_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    OneHotEncoderFeaturizer_int8_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_int8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_int8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_int8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<OneHotStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        OneHotStruct result;

        REQUIRE(OneHotEncoderFeaturizer_int8_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(result);
        #else
        results.emplace_back(result);
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto & result: results) {
        REQUIRE(OneHotEncoderFeaturizer_int8_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_int8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int16_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_int16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int16_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_int16_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    OneHotEncoderFeaturizer_int16_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_int16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_int16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_int16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<OneHotStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        OneHotStruct result;

        REQUIRE(OneHotEncoderFeaturizer_int16_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(result);
        #else
        results.emplace_back(result);
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto & result: results) {
        REQUIRE(OneHotEncoderFeaturizer_int16_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_int16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int32_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_int32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int32_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_int32_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    OneHotEncoderFeaturizer_int32_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_int32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_int32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_int32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<OneHotStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        OneHotStruct result;

        REQUIRE(OneHotEncoderFeaturizer_int32_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(result);
        #else
        results.emplace_back(result);
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto & result: results) {
        REQUIRE(OneHotEncoderFeaturizer_int32_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_int32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int64_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_int64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int64_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_int64_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    OneHotEncoderFeaturizer_int64_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_int64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_int64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_int64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<OneHotStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        OneHotStruct result;

        REQUIRE(OneHotEncoderFeaturizer_int64_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(result);
        #else
        results.emplace_back(result);
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto & result: results) {
        REQUIRE(OneHotEncoderFeaturizer_int64_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_int64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint8_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_uint8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint8_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_uint8_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    OneHotEncoderFeaturizer_uint8_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_uint8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_uint8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_uint8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<OneHotStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        OneHotStruct result;

        REQUIRE(OneHotEncoderFeaturizer_uint8_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(result);
        #else
        results.emplace_back(result);
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto & result: results) {
        REQUIRE(OneHotEncoderFeaturizer_uint8_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_uint8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint16_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_uint16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint16_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_uint16_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    OneHotEncoderFeaturizer_uint16_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_uint16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_uint16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_uint16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<OneHotStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        OneHotStruct result;

        REQUIRE(OneHotEncoderFeaturizer_uint16_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(result);
        #else
        results.emplace_back(result);
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto & result: results) {
        REQUIRE(OneHotEncoderFeaturizer_uint16_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_uint16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint32_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_uint32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint32_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_uint32_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    OneHotEncoderFeaturizer_uint32_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_uint32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_uint32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_uint32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<OneHotStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        OneHotStruct result;

        REQUIRE(OneHotEncoderFeaturizer_uint32_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(result);
        #else
        results.emplace_back(result);
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto & result: results) {
        REQUIRE(OneHotEncoderFeaturizer_uint32_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_uint32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint64_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_uint64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint64_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_uint64_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    OneHotEncoderFeaturizer_uint64_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_uint64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_uint64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_uint64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<OneHotStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        OneHotStruct result;

        REQUIRE(OneHotEncoderFeaturizer_uint64_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(result);
        #else
        results.emplace_back(result);
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto & result: results) {
        REQUIRE(OneHotEncoderFeaturizer_uint64_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_uint64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <float_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_float_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_float_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_float_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_float_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    OneHotEncoderFeaturizer_float_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_float_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_float_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_float_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_float_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<OneHotStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        OneHotStruct result;

        REQUIRE(OneHotEncoderFeaturizer_float_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(result);
        #else
        results.emplace_back(result);
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto & result: results) {
        REQUIRE(OneHotEncoderFeaturizer_float_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_float_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <double_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_double_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_double_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_double_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_double_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    OneHotEncoderFeaturizer_double_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_double_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_double_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_double_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_double_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<OneHotStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        OneHotStruct result;

        REQUIRE(OneHotEncoderFeaturizer_double_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(result);
        #else
        results.emplace_back(result);
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto & result: results) {
        REQUIRE(OneHotEncoderFeaturizer_double_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_double_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <bool> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_bool_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_bool_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_bool_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_bool_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    OneHotEncoderFeaturizer_bool_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_bool_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_bool_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_bool_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_bool_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<OneHotStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        OneHotStruct result;

        REQUIRE(OneHotEncoderFeaturizer_bool_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(result);
        #else
        results.emplace_back(result);
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto & result: results) {
        REQUIRE(OneHotEncoderFeaturizer_bool_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_bool_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <string> */
template <typename VectorInputT, typename... ConstructorArgTs>
void OneHotEncoderFeaturizer_string_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_string_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_string_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(OneHotEncoderFeaturizer_string_Fit(pEstimatorHandle, input.c_str(), &result, &pErrorInfo));
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

    OneHotEncoderFeaturizer_string_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(OneHotEncoderFeaturizer_string_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    OneHotEncoderFeaturizer_string_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_string_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(OneHotEncoderFeaturizer_string_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<OneHotStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        OneHotStruct result;

        REQUIRE(OneHotEncoderFeaturizer_string_Transform(pTransformerHandle, input.c_str(), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(result);
        #else
        results.emplace_back(result);
        #endif

        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto & result: results) {
        REQUIRE(OneHotEncoderFeaturizer_string_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

