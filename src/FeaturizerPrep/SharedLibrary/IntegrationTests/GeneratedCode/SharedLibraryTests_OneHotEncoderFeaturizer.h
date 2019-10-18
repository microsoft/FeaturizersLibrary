/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_OneHotEncoderFeaturizer.h"
#include "Traits.h"

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int8_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void OneHotEncoderFeaturizer_int8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int8_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
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

                REQUIRE(OneHotEncoderFeaturizer_int8_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                if(result == Complete)
                    break;

                if(result == ResetAndContinue) {
                    iter = training_input.begin();
                    continue;
                }
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

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

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_int8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int16_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void OneHotEncoderFeaturizer_int16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int16_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
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

                REQUIRE(OneHotEncoderFeaturizer_int16_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                if(result == Complete)
                    break;

                if(result == ResetAndContinue) {
                    iter = training_input.begin();
                    continue;
                }
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

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

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_int16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int32_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void OneHotEncoderFeaturizer_int32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int32_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
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

                REQUIRE(OneHotEncoderFeaturizer_int32_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                if(result == Complete)
                    break;

                if(result == ResetAndContinue) {
                    iter = training_input.begin();
                    continue;
                }
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

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

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_int32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <int64_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void OneHotEncoderFeaturizer_int64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_int64_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
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

                REQUIRE(OneHotEncoderFeaturizer_int64_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                if(result == Complete)
                    break;

                if(result == ResetAndContinue) {
                    iter = training_input.begin();
                    continue;
                }
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

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

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_int64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint8_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void OneHotEncoderFeaturizer_uint8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint8_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
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

                REQUIRE(OneHotEncoderFeaturizer_uint8_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                if(result == Complete)
                    break;

                if(result == ResetAndContinue) {
                    iter = training_input.begin();
                    continue;
                }
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

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

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_uint8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint16_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void OneHotEncoderFeaturizer_uint16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint16_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
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

                REQUIRE(OneHotEncoderFeaturizer_uint16_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                if(result == Complete)
                    break;

                if(result == ResetAndContinue) {
                    iter = training_input.begin();
                    continue;
                }
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

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

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_uint16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint32_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void OneHotEncoderFeaturizer_uint32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint32_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
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

                REQUIRE(OneHotEncoderFeaturizer_uint32_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                if(result == Complete)
                    break;

                if(result == ResetAndContinue) {
                    iter = training_input.begin();
                    continue;
                }
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

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

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_uint32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <uint64_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void OneHotEncoderFeaturizer_uint64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_uint64_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
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

                REQUIRE(OneHotEncoderFeaturizer_uint64_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                if(result == Complete)
                    break;

                if(result == ResetAndContinue) {
                    iter = training_input.begin();
                    continue;
                }
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

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

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_uint64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <float_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void OneHotEncoderFeaturizer_float_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_float_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_float_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
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

                REQUIRE(OneHotEncoderFeaturizer_float_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                if(result == Complete)
                    break;

                if(result == ResetAndContinue) {
                    iter = training_input.begin();
                    continue;
                }
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

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

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_float_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <double_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void OneHotEncoderFeaturizer_double_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_double_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_double_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
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

                REQUIRE(OneHotEncoderFeaturizer_double_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                if(result == Complete)
                    break;

                if(result == ResetAndContinue) {
                    iter = training_input.begin();
                    continue;
                }
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

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

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_double_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <bool> */
template <typename VectorInputT, typename... ConstructorArgsT>
void OneHotEncoderFeaturizer_bool_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_bool_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_bool_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
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

                REQUIRE(OneHotEncoderFeaturizer_bool_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                if(result == Complete)
                    break;

                if(result == ResetAndContinue) {
                    iter = training_input.begin();
                    continue;
                }
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

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

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_bool_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  OneHotEncoderFeaturizer <string> */
template <typename VectorInputT, typename... ConstructorArgsT>
void OneHotEncoderFeaturizer_string_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<OneHotStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    OneHotEncoderFeaturizer_string_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(OneHotEncoderFeaturizer_string_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
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

                REQUIRE(OneHotEncoderFeaturizer_string_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                if(result == Complete)
                    break;

                if(result == ResetAndContinue) {
                    iter = training_input.begin();
                    continue;
                }
            }

            INFO("Value is " << result)
            REQUIRE(false);
        }
    }

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

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(OneHotEncoderFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

