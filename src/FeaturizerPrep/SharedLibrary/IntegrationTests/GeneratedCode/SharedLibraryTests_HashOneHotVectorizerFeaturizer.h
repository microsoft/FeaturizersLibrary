/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_HashOneHotVectorizerFeaturizer.h"
#include "Traits.h"

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <int8_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void HashOneHotVectorizerFeaturizer_int8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<HashOneHotVectorizerStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    HashOneHotVectorizerFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_int8_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(HashOneHotVectorizerFeaturizer_int8_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(HashOneHotVectorizerFeaturizer_int8_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(HashOneHotVectorizerFeaturizer_int8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    HashOneHotVectorizerFeaturizer_int8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_int8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(HashOneHotVectorizerFeaturizer_int8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<HashOneHotVectorizerStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        HashOneHotVectorizerStruct result;

        REQUIRE(HashOneHotVectorizerFeaturizer_int8_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto &result : results) {
        REQUIRE(HashOneHotVectorizerFeaturizer_int8_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(HashOneHotVectorizerFeaturizer_int8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <int16_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void HashOneHotVectorizerFeaturizer_int16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<HashOneHotVectorizerStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    HashOneHotVectorizerFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_int16_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(HashOneHotVectorizerFeaturizer_int16_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(HashOneHotVectorizerFeaturizer_int16_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(HashOneHotVectorizerFeaturizer_int16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    HashOneHotVectorizerFeaturizer_int16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_int16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(HashOneHotVectorizerFeaturizer_int16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<HashOneHotVectorizerStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        HashOneHotVectorizerStruct result;

        REQUIRE(HashOneHotVectorizerFeaturizer_int16_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto &result : results) {
        REQUIRE(HashOneHotVectorizerFeaturizer_int16_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(HashOneHotVectorizerFeaturizer_int16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <int32_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void HashOneHotVectorizerFeaturizer_int32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<HashOneHotVectorizerStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    HashOneHotVectorizerFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_int32_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(HashOneHotVectorizerFeaturizer_int32_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(HashOneHotVectorizerFeaturizer_int32_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(HashOneHotVectorizerFeaturizer_int32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    HashOneHotVectorizerFeaturizer_int32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_int32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(HashOneHotVectorizerFeaturizer_int32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<HashOneHotVectorizerStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        HashOneHotVectorizerStruct result;

        REQUIRE(HashOneHotVectorizerFeaturizer_int32_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto &result : results) {
        REQUIRE(HashOneHotVectorizerFeaturizer_int32_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(HashOneHotVectorizerFeaturizer_int32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <int64_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void HashOneHotVectorizerFeaturizer_int64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<HashOneHotVectorizerStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    HashOneHotVectorizerFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_int64_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(HashOneHotVectorizerFeaturizer_int64_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(HashOneHotVectorizerFeaturizer_int64_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(HashOneHotVectorizerFeaturizer_int64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    HashOneHotVectorizerFeaturizer_int64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_int64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(HashOneHotVectorizerFeaturizer_int64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<HashOneHotVectorizerStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        HashOneHotVectorizerStruct result;

        REQUIRE(HashOneHotVectorizerFeaturizer_int64_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto &result : results) {
        REQUIRE(HashOneHotVectorizerFeaturizer_int64_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(HashOneHotVectorizerFeaturizer_int64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <uint8_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void HashOneHotVectorizerFeaturizer_uint8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<HashOneHotVectorizerStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    HashOneHotVectorizerFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_uint8_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(HashOneHotVectorizerFeaturizer_uint8_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(HashOneHotVectorizerFeaturizer_uint8_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(HashOneHotVectorizerFeaturizer_uint8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    HashOneHotVectorizerFeaturizer_uint8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_uint8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(HashOneHotVectorizerFeaturizer_uint8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<HashOneHotVectorizerStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        HashOneHotVectorizerStruct result;

        REQUIRE(HashOneHotVectorizerFeaturizer_uint8_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto &result : results) {
        REQUIRE(HashOneHotVectorizerFeaturizer_uint8_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(HashOneHotVectorizerFeaturizer_uint8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <uint16_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void HashOneHotVectorizerFeaturizer_uint16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<HashOneHotVectorizerStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    HashOneHotVectorizerFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_uint16_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(HashOneHotVectorizerFeaturizer_uint16_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(HashOneHotVectorizerFeaturizer_uint16_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(HashOneHotVectorizerFeaturizer_uint16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    HashOneHotVectorizerFeaturizer_uint16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_uint16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(HashOneHotVectorizerFeaturizer_uint16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<HashOneHotVectorizerStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        HashOneHotVectorizerStruct result;

        REQUIRE(HashOneHotVectorizerFeaturizer_uint16_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto &result : results) {
        REQUIRE(HashOneHotVectorizerFeaturizer_uint16_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(HashOneHotVectorizerFeaturizer_uint16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <uint32_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void HashOneHotVectorizerFeaturizer_uint32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<HashOneHotVectorizerStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    HashOneHotVectorizerFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_uint32_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(HashOneHotVectorizerFeaturizer_uint32_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(HashOneHotVectorizerFeaturizer_uint32_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(HashOneHotVectorizerFeaturizer_uint32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    HashOneHotVectorizerFeaturizer_uint32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_uint32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(HashOneHotVectorizerFeaturizer_uint32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<HashOneHotVectorizerStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        HashOneHotVectorizerStruct result;

        REQUIRE(HashOneHotVectorizerFeaturizer_uint32_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto &result : results) {
        REQUIRE(HashOneHotVectorizerFeaturizer_uint32_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(HashOneHotVectorizerFeaturizer_uint32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <uint64_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void HashOneHotVectorizerFeaturizer_uint64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<HashOneHotVectorizerStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    HashOneHotVectorizerFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_uint64_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(HashOneHotVectorizerFeaturizer_uint64_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(HashOneHotVectorizerFeaturizer_uint64_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(HashOneHotVectorizerFeaturizer_uint64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    HashOneHotVectorizerFeaturizer_uint64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_uint64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(HashOneHotVectorizerFeaturizer_uint64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<HashOneHotVectorizerStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        HashOneHotVectorizerStruct result;

        REQUIRE(HashOneHotVectorizerFeaturizer_uint64_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto &result : results) {
        REQUIRE(HashOneHotVectorizerFeaturizer_uint64_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(HashOneHotVectorizerFeaturizer_uint64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <float_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void HashOneHotVectorizerFeaturizer_float_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<HashOneHotVectorizerStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    HashOneHotVectorizerFeaturizer_float_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_float_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(HashOneHotVectorizerFeaturizer_float_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(HashOneHotVectorizerFeaturizer_float_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(HashOneHotVectorizerFeaturizer_float_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    HashOneHotVectorizerFeaturizer_float_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_float_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(HashOneHotVectorizerFeaturizer_float_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<HashOneHotVectorizerStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        HashOneHotVectorizerStruct result;

        REQUIRE(HashOneHotVectorizerFeaturizer_float_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto &result : results) {
        REQUIRE(HashOneHotVectorizerFeaturizer_float_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(HashOneHotVectorizerFeaturizer_float_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <double_t> */
template <typename VectorInputT, typename... ConstructorArgsT>
void HashOneHotVectorizerFeaturizer_double_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<HashOneHotVectorizerStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    HashOneHotVectorizerFeaturizer_double_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_double_t_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(HashOneHotVectorizerFeaturizer_double_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(HashOneHotVectorizerFeaturizer_double_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(HashOneHotVectorizerFeaturizer_double_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    HashOneHotVectorizerFeaturizer_double_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_double_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(HashOneHotVectorizerFeaturizer_double_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<HashOneHotVectorizerStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        HashOneHotVectorizerStruct result;

        REQUIRE(HashOneHotVectorizerFeaturizer_double_t_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto &result : results) {
        REQUIRE(HashOneHotVectorizerFeaturizer_double_t_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(HashOneHotVectorizerFeaturizer_double_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <bool> */
template <typename VectorInputT, typename... ConstructorArgsT>
void HashOneHotVectorizerFeaturizer_bool_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<HashOneHotVectorizerStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    HashOneHotVectorizerFeaturizer_bool_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_bool_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(HashOneHotVectorizerFeaturizer_bool_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(HashOneHotVectorizerFeaturizer_bool_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(HashOneHotVectorizerFeaturizer_bool_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    HashOneHotVectorizerFeaturizer_bool_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_bool_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(HashOneHotVectorizerFeaturizer_bool_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<HashOneHotVectorizerStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        HashOneHotVectorizerStruct result;

        REQUIRE(HashOneHotVectorizerFeaturizer_bool_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto &result : results) {
        REQUIRE(HashOneHotVectorizerFeaturizer_bool_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(HashOneHotVectorizerFeaturizer_bool_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  HashOneHotVectorizerFeaturizer <string> */
template <typename VectorInputT, typename... ConstructorArgsT>
void HashOneHotVectorizerFeaturizer_string_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<HashOneHotVectorizerStruct> const &)> const &verify_func,
    ConstructorArgsT &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    HashOneHotVectorizerFeaturizer_string_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_string_CreateEstimator(std::forward<ConstructorArgsT>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(HashOneHotVectorizerFeaturizer_string_Fit(pEstimatorHandle, input.c_str(), &result, &pErrorInfo));
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

                REQUIRE(HashOneHotVectorizerFeaturizer_string_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(HashOneHotVectorizerFeaturizer_string_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    HashOneHotVectorizerFeaturizer_string_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(HashOneHotVectorizerFeaturizer_string_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(HashOneHotVectorizerFeaturizer_string_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<HashOneHotVectorizerStruct> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        HashOneHotVectorizerStruct result;

        REQUIRE(HashOneHotVectorizerFeaturizer_string_Transform(pTransformerHandle, input.c_str(), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto &result : results) {
        REQUIRE(HashOneHotVectorizerFeaturizer_string_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(HashOneHotVectorizerFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

