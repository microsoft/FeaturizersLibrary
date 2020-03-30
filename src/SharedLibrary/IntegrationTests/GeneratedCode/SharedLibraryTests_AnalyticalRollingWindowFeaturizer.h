/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_AnalyticalRollingWindowFeaturizer.h"

#include "Traits.h"
#include "Featurizers/Structs.h"

#include "SharedLibrary_Common.hpp"

#if (defined _MSC_VER)
#   pragma warning(push)

    // I don't know why MSVC thinks that there is unreachable
    // code in these methods during release builds.
#   pragma warning(disable: 4702) // Unreachable code

#   pragma warning(disable: 4701) // potentially uninitialized local variable '<name>' used
#   pragma warning(disable: 4703) // potentially uninitialized local pointer variable '<name>' used
#endif

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <int8> */
template <typename VectorInputT, typename... ConstructorArgTs>
void AnalyticalRollingWindowFeaturizer_int8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    AnalyticalRollingWindowFeaturizer_int8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_int8_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(AnalyticalRollingWindowFeaturizer_int8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            auto const & input0(std::get<0>(input));

            std::vector<char const *> input0_buffer;

            input0_buffer.reserve(input0.size());

            for(std::string const &value : input0)
                input0_buffer.emplace_back(value.c_str());

            auto const & input1(std::get<1>(input));

            REQUIRE(AnalyticalRollingWindowFeaturizer_int8_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(AnalyticalRollingWindowFeaturizer_int8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    AnalyticalRollingWindowFeaturizer_int8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(AnalyticalRollingWindowFeaturizer_int8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    AnalyticalRollingWindowFeaturizer_int8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_int8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(AnalyticalRollingWindowFeaturizer_int8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::double_t* result_ptr;
        size_t result_items;

        REQUIRE(AnalyticalRollingWindowFeaturizer_int8_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(AnalyticalRollingWindowFeaturizer_int8_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(AnalyticalRollingWindowFeaturizer_int8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <int16> */
template <typename VectorInputT, typename... ConstructorArgTs>
void AnalyticalRollingWindowFeaturizer_int16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    AnalyticalRollingWindowFeaturizer_int16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_int16_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(AnalyticalRollingWindowFeaturizer_int16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            auto const & input0(std::get<0>(input));

            std::vector<char const *> input0_buffer;

            input0_buffer.reserve(input0.size());

            for(std::string const &value : input0)
                input0_buffer.emplace_back(value.c_str());

            auto const & input1(std::get<1>(input));

            REQUIRE(AnalyticalRollingWindowFeaturizer_int16_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(AnalyticalRollingWindowFeaturizer_int16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    AnalyticalRollingWindowFeaturizer_int16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(AnalyticalRollingWindowFeaturizer_int16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    AnalyticalRollingWindowFeaturizer_int16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_int16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(AnalyticalRollingWindowFeaturizer_int16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::double_t* result_ptr;
        size_t result_items;

        REQUIRE(AnalyticalRollingWindowFeaturizer_int16_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(AnalyticalRollingWindowFeaturizer_int16_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(AnalyticalRollingWindowFeaturizer_int16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <int32> */
template <typename VectorInputT, typename... ConstructorArgTs>
void AnalyticalRollingWindowFeaturizer_int32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    AnalyticalRollingWindowFeaturizer_int32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_int32_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(AnalyticalRollingWindowFeaturizer_int32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            auto const & input0(std::get<0>(input));

            std::vector<char const *> input0_buffer;

            input0_buffer.reserve(input0.size());

            for(std::string const &value : input0)
                input0_buffer.emplace_back(value.c_str());

            auto const & input1(std::get<1>(input));

            REQUIRE(AnalyticalRollingWindowFeaturizer_int32_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(AnalyticalRollingWindowFeaturizer_int32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    AnalyticalRollingWindowFeaturizer_int32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(AnalyticalRollingWindowFeaturizer_int32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    AnalyticalRollingWindowFeaturizer_int32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_int32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(AnalyticalRollingWindowFeaturizer_int32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::double_t* result_ptr;
        size_t result_items;

        REQUIRE(AnalyticalRollingWindowFeaturizer_int32_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(AnalyticalRollingWindowFeaturizer_int32_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(AnalyticalRollingWindowFeaturizer_int32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <int64> */
template <typename VectorInputT, typename... ConstructorArgTs>
void AnalyticalRollingWindowFeaturizer_int64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    AnalyticalRollingWindowFeaturizer_int64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_int64_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(AnalyticalRollingWindowFeaturizer_int64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            auto const & input0(std::get<0>(input));

            std::vector<char const *> input0_buffer;

            input0_buffer.reserve(input0.size());

            for(std::string const &value : input0)
                input0_buffer.emplace_back(value.c_str());

            auto const & input1(std::get<1>(input));

            REQUIRE(AnalyticalRollingWindowFeaturizer_int64_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(AnalyticalRollingWindowFeaturizer_int64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    AnalyticalRollingWindowFeaturizer_int64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(AnalyticalRollingWindowFeaturizer_int64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    AnalyticalRollingWindowFeaturizer_int64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_int64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(AnalyticalRollingWindowFeaturizer_int64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::double_t* result_ptr;
        size_t result_items;

        REQUIRE(AnalyticalRollingWindowFeaturizer_int64_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(AnalyticalRollingWindowFeaturizer_int64_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(AnalyticalRollingWindowFeaturizer_int64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <uint8> */
template <typename VectorInputT, typename... ConstructorArgTs>
void AnalyticalRollingWindowFeaturizer_uint8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    AnalyticalRollingWindowFeaturizer_uint8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_uint8_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(AnalyticalRollingWindowFeaturizer_uint8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            auto const & input0(std::get<0>(input));

            std::vector<char const *> input0_buffer;

            input0_buffer.reserve(input0.size());

            for(std::string const &value : input0)
                input0_buffer.emplace_back(value.c_str());

            auto const & input1(std::get<1>(input));

            REQUIRE(AnalyticalRollingWindowFeaturizer_uint8_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(AnalyticalRollingWindowFeaturizer_uint8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    AnalyticalRollingWindowFeaturizer_uint8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(AnalyticalRollingWindowFeaturizer_uint8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    AnalyticalRollingWindowFeaturizer_uint8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_uint8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(AnalyticalRollingWindowFeaturizer_uint8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::double_t* result_ptr;
        size_t result_items;

        REQUIRE(AnalyticalRollingWindowFeaturizer_uint8_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(AnalyticalRollingWindowFeaturizer_uint8_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(AnalyticalRollingWindowFeaturizer_uint8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <uint16> */
template <typename VectorInputT, typename... ConstructorArgTs>
void AnalyticalRollingWindowFeaturizer_uint16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    AnalyticalRollingWindowFeaturizer_uint16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_uint16_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(AnalyticalRollingWindowFeaturizer_uint16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            auto const & input0(std::get<0>(input));

            std::vector<char const *> input0_buffer;

            input0_buffer.reserve(input0.size());

            for(std::string const &value : input0)
                input0_buffer.emplace_back(value.c_str());

            auto const & input1(std::get<1>(input));

            REQUIRE(AnalyticalRollingWindowFeaturizer_uint16_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(AnalyticalRollingWindowFeaturizer_uint16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    AnalyticalRollingWindowFeaturizer_uint16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(AnalyticalRollingWindowFeaturizer_uint16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    AnalyticalRollingWindowFeaturizer_uint16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_uint16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(AnalyticalRollingWindowFeaturizer_uint16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::double_t* result_ptr;
        size_t result_items;

        REQUIRE(AnalyticalRollingWindowFeaturizer_uint16_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(AnalyticalRollingWindowFeaturizer_uint16_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(AnalyticalRollingWindowFeaturizer_uint16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <uint32> */
template <typename VectorInputT, typename... ConstructorArgTs>
void AnalyticalRollingWindowFeaturizer_uint32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    AnalyticalRollingWindowFeaturizer_uint32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_uint32_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(AnalyticalRollingWindowFeaturizer_uint32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            auto const & input0(std::get<0>(input));

            std::vector<char const *> input0_buffer;

            input0_buffer.reserve(input0.size());

            for(std::string const &value : input0)
                input0_buffer.emplace_back(value.c_str());

            auto const & input1(std::get<1>(input));

            REQUIRE(AnalyticalRollingWindowFeaturizer_uint32_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(AnalyticalRollingWindowFeaturizer_uint32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    AnalyticalRollingWindowFeaturizer_uint32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(AnalyticalRollingWindowFeaturizer_uint32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    AnalyticalRollingWindowFeaturizer_uint32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_uint32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(AnalyticalRollingWindowFeaturizer_uint32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::double_t* result_ptr;
        size_t result_items;

        REQUIRE(AnalyticalRollingWindowFeaturizer_uint32_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(AnalyticalRollingWindowFeaturizer_uint32_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(AnalyticalRollingWindowFeaturizer_uint32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <uint64> */
template <typename VectorInputT, typename... ConstructorArgTs>
void AnalyticalRollingWindowFeaturizer_uint64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    AnalyticalRollingWindowFeaturizer_uint64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_uint64_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(AnalyticalRollingWindowFeaturizer_uint64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            auto const & input0(std::get<0>(input));

            std::vector<char const *> input0_buffer;

            input0_buffer.reserve(input0.size());

            for(std::string const &value : input0)
                input0_buffer.emplace_back(value.c_str());

            auto const & input1(std::get<1>(input));

            REQUIRE(AnalyticalRollingWindowFeaturizer_uint64_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(AnalyticalRollingWindowFeaturizer_uint64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    AnalyticalRollingWindowFeaturizer_uint64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(AnalyticalRollingWindowFeaturizer_uint64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    AnalyticalRollingWindowFeaturizer_uint64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_uint64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(AnalyticalRollingWindowFeaturizer_uint64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::double_t* result_ptr;
        size_t result_items;

        REQUIRE(AnalyticalRollingWindowFeaturizer_uint64_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(AnalyticalRollingWindowFeaturizer_uint64_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(AnalyticalRollingWindowFeaturizer_uint64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <float> */
template <typename VectorInputT, typename... ConstructorArgTs>
void AnalyticalRollingWindowFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    AnalyticalRollingWindowFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_float_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(AnalyticalRollingWindowFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            auto const & input0(std::get<0>(input));

            std::vector<char const *> input0_buffer;

            input0_buffer.reserve(input0.size());

            for(std::string const &value : input0)
                input0_buffer.emplace_back(value.c_str());

            auto const & input1(std::get<1>(input));

            REQUIRE(AnalyticalRollingWindowFeaturizer_float_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(AnalyticalRollingWindowFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    AnalyticalRollingWindowFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(AnalyticalRollingWindowFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    AnalyticalRollingWindowFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(AnalyticalRollingWindowFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::double_t* result_ptr;
        size_t result_items;

        REQUIRE(AnalyticalRollingWindowFeaturizer_float_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(AnalyticalRollingWindowFeaturizer_float_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(AnalyticalRollingWindowFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  AnalyticalRollingWindowFeaturizer <double> */
template <typename VectorInputT, typename... ConstructorArgTs>
void AnalyticalRollingWindowFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    AnalyticalRollingWindowFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_double_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(AnalyticalRollingWindowFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            auto const & input0(std::get<0>(input));

            std::vector<char const *> input0_buffer;

            input0_buffer.reserve(input0.size());

            for(std::string const &value : input0)
                input0_buffer.emplace_back(value.c_str());

            auto const & input1(std::get<1>(input));

            REQUIRE(AnalyticalRollingWindowFeaturizer_double_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(AnalyticalRollingWindowFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    AnalyticalRollingWindowFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(AnalyticalRollingWindowFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    AnalyticalRollingWindowFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(AnalyticalRollingWindowFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(AnalyticalRollingWindowFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::double_t* result_ptr;
        size_t result_items;

        REQUIRE(AnalyticalRollingWindowFeaturizer_double_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(AnalyticalRollingWindowFeaturizer_double_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(AnalyticalRollingWindowFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
