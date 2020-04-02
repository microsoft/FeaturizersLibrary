/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_StandardScaleWrapperFeaturizer.h"

#include "Traits.h"
#include "Featurizers/Structs.h"

#include "SharedLibraryTests_Common.hpp"

#if (defined _MSC_VER)
#   pragma warning(push)

    // I don't know why MSVC thinks that there is unreachable
    // code in these methods during release builds.
#   pragma warning(disable: 4702) // Unreachable code

#   pragma warning(disable: 4701) // potentially uninitialized local variable '<name>' used
#   pragma warning(disable: 4703) // potentially uninitialized local pointer variable '<name>' used
#endif

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <int8> */
template <typename VectorInputT, typename... ConstructorArgTs>
void StandardScaleWrapperFeaturizer_int8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::double_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StandardScaleWrapperFeaturizer_int8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_int8_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(StandardScaleWrapperFeaturizer_int8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(StandardScaleWrapperFeaturizer_int8_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(StandardScaleWrapperFeaturizer_int8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    StandardScaleWrapperFeaturizer_int8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(StandardScaleWrapperFeaturizer_int8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StandardScaleWrapperFeaturizer_int8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_int8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StandardScaleWrapperFeaturizer_int8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::double_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t result;

        REQUIRE(StandardScaleWrapperFeaturizer_int8_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StandardScaleWrapperFeaturizer_int8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <int16> */
template <typename VectorInputT, typename... ConstructorArgTs>
void StandardScaleWrapperFeaturizer_int16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::double_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StandardScaleWrapperFeaturizer_int16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_int16_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(StandardScaleWrapperFeaturizer_int16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(StandardScaleWrapperFeaturizer_int16_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(StandardScaleWrapperFeaturizer_int16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    StandardScaleWrapperFeaturizer_int16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(StandardScaleWrapperFeaturizer_int16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StandardScaleWrapperFeaturizer_int16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_int16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StandardScaleWrapperFeaturizer_int16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::double_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t result;

        REQUIRE(StandardScaleWrapperFeaturizer_int16_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StandardScaleWrapperFeaturizer_int16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <int32> */
template <typename VectorInputT, typename... ConstructorArgTs>
void StandardScaleWrapperFeaturizer_int32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::double_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StandardScaleWrapperFeaturizer_int32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_int32_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(StandardScaleWrapperFeaturizer_int32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(StandardScaleWrapperFeaturizer_int32_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(StandardScaleWrapperFeaturizer_int32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    StandardScaleWrapperFeaturizer_int32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(StandardScaleWrapperFeaturizer_int32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StandardScaleWrapperFeaturizer_int32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_int32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StandardScaleWrapperFeaturizer_int32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::double_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t result;

        REQUIRE(StandardScaleWrapperFeaturizer_int32_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StandardScaleWrapperFeaturizer_int32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <int64> */
template <typename VectorInputT, typename... ConstructorArgTs>
void StandardScaleWrapperFeaturizer_int64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::double_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StandardScaleWrapperFeaturizer_int64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_int64_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(StandardScaleWrapperFeaturizer_int64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(StandardScaleWrapperFeaturizer_int64_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(StandardScaleWrapperFeaturizer_int64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    StandardScaleWrapperFeaturizer_int64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(StandardScaleWrapperFeaturizer_int64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StandardScaleWrapperFeaturizer_int64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_int64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StandardScaleWrapperFeaturizer_int64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::double_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t result;

        REQUIRE(StandardScaleWrapperFeaturizer_int64_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StandardScaleWrapperFeaturizer_int64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <uint8> */
template <typename VectorInputT, typename... ConstructorArgTs>
void StandardScaleWrapperFeaturizer_uint8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::double_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StandardScaleWrapperFeaturizer_uint8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_uint8_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(StandardScaleWrapperFeaturizer_uint8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(StandardScaleWrapperFeaturizer_uint8_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(StandardScaleWrapperFeaturizer_uint8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    StandardScaleWrapperFeaturizer_uint8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(StandardScaleWrapperFeaturizer_uint8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StandardScaleWrapperFeaturizer_uint8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_uint8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StandardScaleWrapperFeaturizer_uint8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::double_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t result;

        REQUIRE(StandardScaleWrapperFeaturizer_uint8_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StandardScaleWrapperFeaturizer_uint8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <uint16> */
template <typename VectorInputT, typename... ConstructorArgTs>
void StandardScaleWrapperFeaturizer_uint16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::double_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StandardScaleWrapperFeaturizer_uint16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_uint16_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(StandardScaleWrapperFeaturizer_uint16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(StandardScaleWrapperFeaturizer_uint16_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(StandardScaleWrapperFeaturizer_uint16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    StandardScaleWrapperFeaturizer_uint16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(StandardScaleWrapperFeaturizer_uint16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StandardScaleWrapperFeaturizer_uint16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_uint16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StandardScaleWrapperFeaturizer_uint16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::double_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t result;

        REQUIRE(StandardScaleWrapperFeaturizer_uint16_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StandardScaleWrapperFeaturizer_uint16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <uint32> */
template <typename VectorInputT, typename... ConstructorArgTs>
void StandardScaleWrapperFeaturizer_uint32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::double_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StandardScaleWrapperFeaturizer_uint32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_uint32_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(StandardScaleWrapperFeaturizer_uint32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(StandardScaleWrapperFeaturizer_uint32_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(StandardScaleWrapperFeaturizer_uint32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    StandardScaleWrapperFeaturizer_uint32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(StandardScaleWrapperFeaturizer_uint32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StandardScaleWrapperFeaturizer_uint32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_uint32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StandardScaleWrapperFeaturizer_uint32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::double_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t result;

        REQUIRE(StandardScaleWrapperFeaturizer_uint32_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StandardScaleWrapperFeaturizer_uint32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <uint64> */
template <typename VectorInputT, typename... ConstructorArgTs>
void StandardScaleWrapperFeaturizer_uint64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::double_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StandardScaleWrapperFeaturizer_uint64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_uint64_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(StandardScaleWrapperFeaturizer_uint64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(StandardScaleWrapperFeaturizer_uint64_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(StandardScaleWrapperFeaturizer_uint64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    StandardScaleWrapperFeaturizer_uint64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(StandardScaleWrapperFeaturizer_uint64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StandardScaleWrapperFeaturizer_uint64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_uint64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StandardScaleWrapperFeaturizer_uint64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::double_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t result;

        REQUIRE(StandardScaleWrapperFeaturizer_uint64_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StandardScaleWrapperFeaturizer_uint64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <float> */
template <typename VectorInputT, typename... ConstructorArgTs>
void StandardScaleWrapperFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::double_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StandardScaleWrapperFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_float_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(StandardScaleWrapperFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(StandardScaleWrapperFeaturizer_float_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(StandardScaleWrapperFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    StandardScaleWrapperFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(StandardScaleWrapperFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StandardScaleWrapperFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StandardScaleWrapperFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::double_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t result;

        REQUIRE(StandardScaleWrapperFeaturizer_float_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StandardScaleWrapperFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  StandardScaleWrapperFeaturizer <double> */
template <typename VectorInputT, typename... ConstructorArgTs>
void StandardScaleWrapperFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::double_t> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    StandardScaleWrapperFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_double_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(StandardScaleWrapperFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(StandardScaleWrapperFeaturizer_double_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(StandardScaleWrapperFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    StandardScaleWrapperFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(StandardScaleWrapperFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    StandardScaleWrapperFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(StandardScaleWrapperFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(StandardScaleWrapperFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::double_t> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::double_t result;

        REQUIRE(StandardScaleWrapperFeaturizer_double_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::move(result));
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(StandardScaleWrapperFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
