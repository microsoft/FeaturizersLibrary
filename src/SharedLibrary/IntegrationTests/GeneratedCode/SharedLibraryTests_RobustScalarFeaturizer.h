/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_RobustScalarFeaturizer.h"
#include "Traits.h"

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <int8_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void RobustScalarFeaturizer_int8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<float> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    RobustScalarFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_int8_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(RobustScalarFeaturizer_int8_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    RobustScalarFeaturizer_int8_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(RobustScalarFeaturizer_int8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    RobustScalarFeaturizer_int8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_int8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(RobustScalarFeaturizer_int8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<float> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        float result;

        REQUIRE(RobustScalarFeaturizer_int8_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(RobustScalarFeaturizer_int8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <int16_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void RobustScalarFeaturizer_int16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<float> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    RobustScalarFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_int16_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(RobustScalarFeaturizer_int16_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    RobustScalarFeaturizer_int16_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(RobustScalarFeaturizer_int16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    RobustScalarFeaturizer_int16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_int16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(RobustScalarFeaturizer_int16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<float> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        float result;

        REQUIRE(RobustScalarFeaturizer_int16_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(RobustScalarFeaturizer_int16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <uint8_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void RobustScalarFeaturizer_uint8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<float> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    RobustScalarFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_uint8_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(RobustScalarFeaturizer_uint8_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    RobustScalarFeaturizer_uint8_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(RobustScalarFeaturizer_uint8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    RobustScalarFeaturizer_uint8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_uint8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(RobustScalarFeaturizer_uint8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<float> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        float result;

        REQUIRE(RobustScalarFeaturizer_uint8_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(RobustScalarFeaturizer_uint8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <uint16_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void RobustScalarFeaturizer_uint16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<float> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    RobustScalarFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_uint16_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(RobustScalarFeaturizer_uint16_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    RobustScalarFeaturizer_uint16_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(RobustScalarFeaturizer_uint16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    RobustScalarFeaturizer_uint16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_uint16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(RobustScalarFeaturizer_uint16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<float> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        float result;

        REQUIRE(RobustScalarFeaturizer_uint16_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(RobustScalarFeaturizer_uint16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <float_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void RobustScalarFeaturizer_float_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<float> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    RobustScalarFeaturizer_float_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_float_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(RobustScalarFeaturizer_float_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    RobustScalarFeaturizer_float_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(RobustScalarFeaturizer_float_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    RobustScalarFeaturizer_float_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_float_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(RobustScalarFeaturizer_float_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<float> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        float result;

        REQUIRE(RobustScalarFeaturizer_float_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(RobustScalarFeaturizer_float_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <int32_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void RobustScalarFeaturizer_int32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<double> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    RobustScalarFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_int32_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(RobustScalarFeaturizer_int32_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    RobustScalarFeaturizer_int32_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(RobustScalarFeaturizer_int32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    RobustScalarFeaturizer_int32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_int32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(RobustScalarFeaturizer_int32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<double> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        double result;

        REQUIRE(RobustScalarFeaturizer_int32_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(RobustScalarFeaturizer_int32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <int64_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void RobustScalarFeaturizer_int64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<double> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    RobustScalarFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_int64_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(RobustScalarFeaturizer_int64_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    RobustScalarFeaturizer_int64_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(RobustScalarFeaturizer_int64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    RobustScalarFeaturizer_int64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_int64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(RobustScalarFeaturizer_int64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<double> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        double result;

        REQUIRE(RobustScalarFeaturizer_int64_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(RobustScalarFeaturizer_int64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <uint32_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void RobustScalarFeaturizer_uint32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<double> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    RobustScalarFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_uint32_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(RobustScalarFeaturizer_uint32_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    RobustScalarFeaturizer_uint32_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(RobustScalarFeaturizer_uint32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    RobustScalarFeaturizer_uint32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_uint32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(RobustScalarFeaturizer_uint32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<double> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        double result;

        REQUIRE(RobustScalarFeaturizer_uint32_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(RobustScalarFeaturizer_uint32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <uint64_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void RobustScalarFeaturizer_uint64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<double> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    RobustScalarFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_uint64_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(RobustScalarFeaturizer_uint64_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    RobustScalarFeaturizer_uint64_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(RobustScalarFeaturizer_uint64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    RobustScalarFeaturizer_uint64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_uint64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(RobustScalarFeaturizer_uint64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<double> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        double result;

        REQUIRE(RobustScalarFeaturizer_uint64_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(RobustScalarFeaturizer_uint64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  RobustScalarFeaturizer <double_t> */
template <typename VectorInputT, typename... ConstructorArgTs>
void RobustScalarFeaturizer_double_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<double> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    RobustScalarFeaturizer_double_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_double_t_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(RobustScalarFeaturizer_double_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

    RobustScalarFeaturizer_double_t_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(RobustScalarFeaturizer_double_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    RobustScalarFeaturizer_double_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_double_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(RobustScalarFeaturizer_double_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<double> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        double result;

        REQUIRE(RobustScalarFeaturizer_double_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(RobustScalarFeaturizer_double_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

