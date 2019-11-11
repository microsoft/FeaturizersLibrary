/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_CatImputerFeaturizer.h"
#include "Traits.h"

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <int8_t> */
template <typename VectorInputT>
void CatImputerFeaturizer_int8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_int8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int8_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_int8_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<int8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int8_t>::GetNullableValue(input), &result, &pErrorInfo));
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

                REQUIRE(CatImputerFeaturizer_int8_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(CatImputerFeaturizer_int8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_int8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_int8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int8_t result;

        REQUIRE(CatImputerFeaturizer_int8_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<int8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int8_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_int8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <int16_t> */
template <typename VectorInputT>
void CatImputerFeaturizer_int16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int16_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_int16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int16_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_int16_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<int16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int16_t>::GetNullableValue(input), &result, &pErrorInfo));
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

                REQUIRE(CatImputerFeaturizer_int16_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(CatImputerFeaturizer_int16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_int16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_int16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int16_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int16_t result;

        REQUIRE(CatImputerFeaturizer_int16_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<int16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int16_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_int16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <int32_t> */
template <typename VectorInputT>
void CatImputerFeaturizer_int32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int32_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_int32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int32_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_int32_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<int32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int32_t>::GetNullableValue(input), &result, &pErrorInfo));
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

                REQUIRE(CatImputerFeaturizer_int32_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(CatImputerFeaturizer_int32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_int32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_int32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int32_t result;

        REQUIRE(CatImputerFeaturizer_int32_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<int32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int32_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_int32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <int64_t> */
template <typename VectorInputT>
void CatImputerFeaturizer_int64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<int64_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_int64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int64_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_int64_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<int64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int64_t>::GetNullableValue(input), &result, &pErrorInfo));
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

                REQUIRE(CatImputerFeaturizer_int64_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(CatImputerFeaturizer_int64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_int64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_int64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_int64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<int64_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        int64_t result;

        REQUIRE(CatImputerFeaturizer_int64_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<int64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<int64_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_int64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <uint8_t> */
template <typename VectorInputT>
void CatImputerFeaturizer_uint8_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint8_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_uint8_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint8_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_uint8_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<uint8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint8_t>::GetNullableValue(input), &result, &pErrorInfo));
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

                REQUIRE(CatImputerFeaturizer_uint8_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(CatImputerFeaturizer_uint8_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_uint8_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint8_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_uint8_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint8_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint8_t result;

        REQUIRE(CatImputerFeaturizer_uint8_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<uint8_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint8_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_uint8_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <uint16_t> */
template <typename VectorInputT>
void CatImputerFeaturizer_uint16_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint16_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_uint16_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint16_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_uint16_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<uint16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint16_t>::GetNullableValue(input), &result, &pErrorInfo));
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

                REQUIRE(CatImputerFeaturizer_uint16_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(CatImputerFeaturizer_uint16_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_uint16_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint16_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_uint16_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint16_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint16_t result;

        REQUIRE(CatImputerFeaturizer_uint16_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<uint16_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint16_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_uint16_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <uint32_t> */
template <typename VectorInputT>
void CatImputerFeaturizer_uint32_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint32_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_uint32_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint32_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_uint32_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<uint32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint32_t>::GetNullableValue(input), &result, &pErrorInfo));
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

                REQUIRE(CatImputerFeaturizer_uint32_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(CatImputerFeaturizer_uint32_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_uint32_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint32_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_uint32_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint32_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint32_t result;

        REQUIRE(CatImputerFeaturizer_uint32_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<uint32_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint32_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_uint32_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <uint64_t> */
template <typename VectorInputT>
void CatImputerFeaturizer_uint64_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<uint64_t> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_uint64_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint64_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_uint64_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<uint64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint64_t>::GetNullableValue(input), &result, &pErrorInfo));
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

                REQUIRE(CatImputerFeaturizer_uint64_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(CatImputerFeaturizer_uint64_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_uint64_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_uint64_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_uint64_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<uint64_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t result;

        REQUIRE(CatImputerFeaturizer_uint64_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<uint64_t>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<uint64_t>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_uint64_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <float_t> */
template <typename VectorInputT>
void CatImputerFeaturizer_float_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<float> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_float_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_float_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_float_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<float>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<float>::GetNullableValue(input), &result, &pErrorInfo));
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

                REQUIRE(CatImputerFeaturizer_float_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(CatImputerFeaturizer_float_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_float_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_float_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_float_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<float> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        float result;

        REQUIRE(CatImputerFeaturizer_float_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<float>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<float>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_float_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  CatImputerFeaturizer <double_t> */
template <typename VectorInputT>
void CatImputerFeaturizer_double_t_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<double> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CatImputerFeaturizer_double_t_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_double_t_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_double_t_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<double>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<double>::GetNullableValue(input), &result, &pErrorInfo));
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

                REQUIRE(CatImputerFeaturizer_double_t_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(CatImputerFeaturizer_double_t_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CatImputerFeaturizer_double_t_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CatImputerFeaturizer_double_t_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CatImputerFeaturizer_double_t_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<double> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        double result;

        REQUIRE(CatImputerFeaturizer_double_t_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<double>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<double>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_double_t_DestroyTransformer(pTransformerHandle, &pErrorInfo));
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
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_bool_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<bool>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<bool>::GetNullableValue(input), &result, &pErrorInfo));
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

                REQUIRE(CatImputerFeaturizer_bool_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

    for(auto const & input : inference_input) {
        bool result;

        REQUIRE(CatImputerFeaturizer_bool_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<bool>::IsNull(input) ? nullptr : &Microsoft::Featurizer::Traits<bool>::GetNullableValue(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
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
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(CatImputerFeaturizer_string_Fit(pEstimatorHandle, Microsoft::Featurizer::Traits<std::string>::IsNull(input) ? nullptr : input->c_str(), &result, &pErrorInfo));
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

                REQUIRE(CatImputerFeaturizer_string_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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
        std::size_t result_items(0);


        REQUIRE(CatImputerFeaturizer_string_Transform(pTransformerHandle, Microsoft::Featurizer::Traits<std::string>::IsNull(input) ? nullptr : input->c_str(), &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::string(result_ptr));
        
        // Destroy the contents
        REQUIRE(CatImputerFeaturizer_string_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CatImputerFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

