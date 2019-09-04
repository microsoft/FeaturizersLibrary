/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_StringFeaturizer.h"
#include "Traits.h"

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <int8_t> */
template <typename VectorInputT>
void StringFeaturizer_int8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StringFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StringFeaturizer_int8_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(StringFeaturizer_int8_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(StringFeaturizer_int8_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(StringFeaturizer_int8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StringFeaturizer_int8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StringFeaturizer_int8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StringFeaturizer_int8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr(nullptr);
        std::size_t result_items(0);


        REQUIRE(StringFeaturizer_int8_t_Transform(pTransformerHandle, input, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::string(result_ptr));
        
        // Destroy the contents
        REQUIRE(StringFeaturizer_int8_t_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StringFeaturizer_int8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <int16_t> */
template <typename VectorInputT>
void StringFeaturizer_int16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StringFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StringFeaturizer_int16_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(StringFeaturizer_int16_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(StringFeaturizer_int16_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(StringFeaturizer_int16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StringFeaturizer_int16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StringFeaturizer_int16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StringFeaturizer_int16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr(nullptr);
        std::size_t result_items(0);


        REQUIRE(StringFeaturizer_int16_t_Transform(pTransformerHandle, input, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::string(result_ptr));
        
        // Destroy the contents
        REQUIRE(StringFeaturizer_int16_t_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StringFeaturizer_int16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <int32_t> */
template <typename VectorInputT>
void StringFeaturizer_int32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StringFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StringFeaturizer_int32_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(StringFeaturizer_int32_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(StringFeaturizer_int32_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(StringFeaturizer_int32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StringFeaturizer_int32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StringFeaturizer_int32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StringFeaturizer_int32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr(nullptr);
        std::size_t result_items(0);


        REQUIRE(StringFeaturizer_int32_t_Transform(pTransformerHandle, input, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::string(result_ptr));
        
        // Destroy the contents
        REQUIRE(StringFeaturizer_int32_t_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StringFeaturizer_int32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <int64_t> */
template <typename VectorInputT>
void StringFeaturizer_int64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StringFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StringFeaturizer_int64_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(StringFeaturizer_int64_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(StringFeaturizer_int64_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(StringFeaturizer_int64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StringFeaturizer_int64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StringFeaturizer_int64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StringFeaturizer_int64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr(nullptr);
        std::size_t result_items(0);


        REQUIRE(StringFeaturizer_int64_t_Transform(pTransformerHandle, input, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::string(result_ptr));
        
        // Destroy the contents
        REQUIRE(StringFeaturizer_int64_t_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StringFeaturizer_int64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <uint8_t> */
template <typename VectorInputT>
void StringFeaturizer_uint8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StringFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StringFeaturizer_uint8_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(StringFeaturizer_uint8_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(StringFeaturizer_uint8_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(StringFeaturizer_uint8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StringFeaturizer_uint8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StringFeaturizer_uint8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StringFeaturizer_uint8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr(nullptr);
        std::size_t result_items(0);


        REQUIRE(StringFeaturizer_uint8_t_Transform(pTransformerHandle, input, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::string(result_ptr));
        
        // Destroy the contents
        REQUIRE(StringFeaturizer_uint8_t_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StringFeaturizer_uint8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <uint16_t> */
template <typename VectorInputT>
void StringFeaturizer_uint16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StringFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StringFeaturizer_uint16_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(StringFeaturizer_uint16_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(StringFeaturizer_uint16_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(StringFeaturizer_uint16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StringFeaturizer_uint16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StringFeaturizer_uint16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StringFeaturizer_uint16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr(nullptr);
        std::size_t result_items(0);


        REQUIRE(StringFeaturizer_uint16_t_Transform(pTransformerHandle, input, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::string(result_ptr));
        
        // Destroy the contents
        REQUIRE(StringFeaturizer_uint16_t_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StringFeaturizer_uint16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <uint32_t> */
template <typename VectorInputT>
void StringFeaturizer_uint32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StringFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StringFeaturizer_uint32_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(StringFeaturizer_uint32_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(StringFeaturizer_uint32_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(StringFeaturizer_uint32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StringFeaturizer_uint32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StringFeaturizer_uint32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StringFeaturizer_uint32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr(nullptr);
        std::size_t result_items(0);


        REQUIRE(StringFeaturizer_uint32_t_Transform(pTransformerHandle, input, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::string(result_ptr));
        
        // Destroy the contents
        REQUIRE(StringFeaturizer_uint32_t_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StringFeaturizer_uint32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <uint64_t> */
template <typename VectorInputT>
void StringFeaturizer_uint64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StringFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StringFeaturizer_uint64_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(StringFeaturizer_uint64_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(StringFeaturizer_uint64_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(StringFeaturizer_uint64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StringFeaturizer_uint64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StringFeaturizer_uint64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StringFeaturizer_uint64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr(nullptr);
        std::size_t result_items(0);


        REQUIRE(StringFeaturizer_uint64_t_Transform(pTransformerHandle, input, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::string(result_ptr));
        
        // Destroy the contents
        REQUIRE(StringFeaturizer_uint64_t_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StringFeaturizer_uint64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <float_t> */
template <typename VectorInputT>
void StringFeaturizer_float_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StringFeaturizer_float_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StringFeaturizer_float_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(StringFeaturizer_float_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(StringFeaturizer_float_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(StringFeaturizer_float_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StringFeaturizer_float_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StringFeaturizer_float_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StringFeaturizer_float_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr(nullptr);
        std::size_t result_items(0);


        REQUIRE(StringFeaturizer_float_t_Transform(pTransformerHandle, input, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::string(result_ptr));
        
        // Destroy the contents
        REQUIRE(StringFeaturizer_float_t_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StringFeaturizer_float_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <double_t> */
template <typename VectorInputT>
void StringFeaturizer_double_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StringFeaturizer_double_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StringFeaturizer_double_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(StringFeaturizer_double_t_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(StringFeaturizer_double_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(StringFeaturizer_double_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StringFeaturizer_double_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StringFeaturizer_double_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StringFeaturizer_double_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr(nullptr);
        std::size_t result_items(0);


        REQUIRE(StringFeaturizer_double_t_Transform(pTransformerHandle, input, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::string(result_ptr));
        
        // Destroy the contents
        REQUIRE(StringFeaturizer_double_t_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StringFeaturizer_double_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <bool> */
template <typename VectorInputT>
void StringFeaturizer_bool_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StringFeaturizer_bool_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StringFeaturizer_bool_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(StringFeaturizer_bool_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(StringFeaturizer_bool_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(StringFeaturizer_bool_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StringFeaturizer_bool_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StringFeaturizer_bool_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StringFeaturizer_bool_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr(nullptr);
        std::size_t result_items(0);


        REQUIRE(StringFeaturizer_bool_Transform(pTransformerHandle, input, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::string(result_ptr));
        
        // Destroy the contents
        REQUIRE(StringFeaturizer_bool_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StringFeaturizer_bool_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StringFeaturizer <string> */
template <typename VectorInputT>
void StringFeaturizer_string_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::string> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StringFeaturizer_string_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StringFeaturizer_string_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(StringFeaturizer_string_Fit(pEstimatorHandle, input.c_str(), &result, &pErrorInfo));
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

                REQUIRE(StringFeaturizer_string_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(StringFeaturizer_string_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StringFeaturizer_string_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StringFeaturizer_string_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StringFeaturizer_string_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::string> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        char const * result_ptr(nullptr);
        std::size_t result_items(0);


        REQUIRE(StringFeaturizer_string_Transform(pTransformerHandle, input.c_str(), &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::string(result_ptr));
        
        // Destroy the contents
        REQUIRE(StringFeaturizer_string_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StringFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

