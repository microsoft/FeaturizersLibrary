/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_SimpleRollingWindowFeaturizer.h"

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
/* |  SimpleRollingWindowFeaturizer <int8> */
template <typename VectorInputT, typename... ConstructorArgTs>
void SimpleRollingWindowFeaturizer_int8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<nonstd::optional<std::int8_t>>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    SimpleRollingWindowFeaturizer_int8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_int8_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(SimpleRollingWindowFeaturizer_int8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
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

            REQUIRE(SimpleRollingWindowFeaturizer_int8_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(SimpleRollingWindowFeaturizer_int8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    SimpleRollingWindowFeaturizer_int8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(SimpleRollingWindowFeaturizer_int8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    SimpleRollingWindowFeaturizer_int8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_int8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(SimpleRollingWindowFeaturizer_int8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<nonstd::optional<std::int8_t>>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::int8_t ** result_ptr;
        size_t result_items;

        REQUIRE(SimpleRollingWindowFeaturizer_int8_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        // Convert the pointers into optional values
        {
            std::vector<nonstd::optional<std::int8_t>> temp;

            temp.reserve(result_items);

            for(std::int8_t **ptr = result_ptr; ptr != result_ptr + result_items; ++ptr) {
                if(*ptr != nullptr)
                    temp.emplace_back(std::move(**ptr));
                else
                    temp.emplace_back(nonstd::optional<std::int8_t>());
            }

            results.emplace_back(std::move(temp));
        }
        
        // Destroy the contents
        REQUIRE(SimpleRollingWindowFeaturizer_int8_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(SimpleRollingWindowFeaturizer_int8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <int16> */
template <typename VectorInputT, typename... ConstructorArgTs>
void SimpleRollingWindowFeaturizer_int16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<nonstd::optional<std::int16_t>>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    SimpleRollingWindowFeaturizer_int16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_int16_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(SimpleRollingWindowFeaturizer_int16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
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

            REQUIRE(SimpleRollingWindowFeaturizer_int16_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(SimpleRollingWindowFeaturizer_int16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    SimpleRollingWindowFeaturizer_int16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(SimpleRollingWindowFeaturizer_int16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    SimpleRollingWindowFeaturizer_int16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_int16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(SimpleRollingWindowFeaturizer_int16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<nonstd::optional<std::int16_t>>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::int16_t ** result_ptr;
        size_t result_items;

        REQUIRE(SimpleRollingWindowFeaturizer_int16_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        // Convert the pointers into optional values
        {
            std::vector<nonstd::optional<std::int16_t>> temp;

            temp.reserve(result_items);

            for(std::int16_t **ptr = result_ptr; ptr != result_ptr + result_items; ++ptr) {
                if(*ptr != nullptr)
                    temp.emplace_back(std::move(**ptr));
                else
                    temp.emplace_back(nonstd::optional<std::int16_t>());
            }

            results.emplace_back(std::move(temp));
        }
        
        // Destroy the contents
        REQUIRE(SimpleRollingWindowFeaturizer_int16_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(SimpleRollingWindowFeaturizer_int16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <int32> */
template <typename VectorInputT, typename... ConstructorArgTs>
void SimpleRollingWindowFeaturizer_int32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<nonstd::optional<std::int32_t>>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    SimpleRollingWindowFeaturizer_int32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_int32_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(SimpleRollingWindowFeaturizer_int32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
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

            REQUIRE(SimpleRollingWindowFeaturizer_int32_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(SimpleRollingWindowFeaturizer_int32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    SimpleRollingWindowFeaturizer_int32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(SimpleRollingWindowFeaturizer_int32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    SimpleRollingWindowFeaturizer_int32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_int32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(SimpleRollingWindowFeaturizer_int32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<nonstd::optional<std::int32_t>>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::int32_t ** result_ptr;
        size_t result_items;

        REQUIRE(SimpleRollingWindowFeaturizer_int32_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        // Convert the pointers into optional values
        {
            std::vector<nonstd::optional<std::int32_t>> temp;

            temp.reserve(result_items);

            for(std::int32_t **ptr = result_ptr; ptr != result_ptr + result_items; ++ptr) {
                if(*ptr != nullptr)
                    temp.emplace_back(std::move(**ptr));
                else
                    temp.emplace_back(nonstd::optional<std::int32_t>());
            }

            results.emplace_back(std::move(temp));
        }
        
        // Destroy the contents
        REQUIRE(SimpleRollingWindowFeaturizer_int32_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(SimpleRollingWindowFeaturizer_int32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <int64> */
template <typename VectorInputT, typename... ConstructorArgTs>
void SimpleRollingWindowFeaturizer_int64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<nonstd::optional<std::int64_t>>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    SimpleRollingWindowFeaturizer_int64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_int64_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(SimpleRollingWindowFeaturizer_int64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
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

            REQUIRE(SimpleRollingWindowFeaturizer_int64_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(SimpleRollingWindowFeaturizer_int64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    SimpleRollingWindowFeaturizer_int64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(SimpleRollingWindowFeaturizer_int64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    SimpleRollingWindowFeaturizer_int64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_int64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(SimpleRollingWindowFeaturizer_int64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<nonstd::optional<std::int64_t>>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::int64_t ** result_ptr;
        size_t result_items;

        REQUIRE(SimpleRollingWindowFeaturizer_int64_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        // Convert the pointers into optional values
        {
            std::vector<nonstd::optional<std::int64_t>> temp;

            temp.reserve(result_items);

            for(std::int64_t **ptr = result_ptr; ptr != result_ptr + result_items; ++ptr) {
                if(*ptr != nullptr)
                    temp.emplace_back(std::move(**ptr));
                else
                    temp.emplace_back(nonstd::optional<std::int64_t>());
            }

            results.emplace_back(std::move(temp));
        }
        
        // Destroy the contents
        REQUIRE(SimpleRollingWindowFeaturizer_int64_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(SimpleRollingWindowFeaturizer_int64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <uint8> */
template <typename VectorInputT, typename... ConstructorArgTs>
void SimpleRollingWindowFeaturizer_uint8_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<nonstd::optional<std::uint8_t>>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    SimpleRollingWindowFeaturizer_uint8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_uint8_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(SimpleRollingWindowFeaturizer_uint8_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
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

            REQUIRE(SimpleRollingWindowFeaturizer_uint8_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(SimpleRollingWindowFeaturizer_uint8_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    SimpleRollingWindowFeaturizer_uint8_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(SimpleRollingWindowFeaturizer_uint8_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    SimpleRollingWindowFeaturizer_uint8_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_uint8_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(SimpleRollingWindowFeaturizer_uint8_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<nonstd::optional<std::uint8_t>>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::uint8_t ** result_ptr;
        size_t result_items;

        REQUIRE(SimpleRollingWindowFeaturizer_uint8_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        // Convert the pointers into optional values
        {
            std::vector<nonstd::optional<std::uint8_t>> temp;

            temp.reserve(result_items);

            for(std::uint8_t **ptr = result_ptr; ptr != result_ptr + result_items; ++ptr) {
                if(*ptr != nullptr)
                    temp.emplace_back(std::move(**ptr));
                else
                    temp.emplace_back(nonstd::optional<std::uint8_t>());
            }

            results.emplace_back(std::move(temp));
        }
        
        // Destroy the contents
        REQUIRE(SimpleRollingWindowFeaturizer_uint8_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(SimpleRollingWindowFeaturizer_uint8_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <uint16> */
template <typename VectorInputT, typename... ConstructorArgTs>
void SimpleRollingWindowFeaturizer_uint16_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<nonstd::optional<std::uint16_t>>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    SimpleRollingWindowFeaturizer_uint16_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_uint16_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(SimpleRollingWindowFeaturizer_uint16_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
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

            REQUIRE(SimpleRollingWindowFeaturizer_uint16_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(SimpleRollingWindowFeaturizer_uint16_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    SimpleRollingWindowFeaturizer_uint16_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(SimpleRollingWindowFeaturizer_uint16_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    SimpleRollingWindowFeaturizer_uint16_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_uint16_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(SimpleRollingWindowFeaturizer_uint16_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<nonstd::optional<std::uint16_t>>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::uint16_t ** result_ptr;
        size_t result_items;

        REQUIRE(SimpleRollingWindowFeaturizer_uint16_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        // Convert the pointers into optional values
        {
            std::vector<nonstd::optional<std::uint16_t>> temp;

            temp.reserve(result_items);

            for(std::uint16_t **ptr = result_ptr; ptr != result_ptr + result_items; ++ptr) {
                if(*ptr != nullptr)
                    temp.emplace_back(std::move(**ptr));
                else
                    temp.emplace_back(nonstd::optional<std::uint16_t>());
            }

            results.emplace_back(std::move(temp));
        }
        
        // Destroy the contents
        REQUIRE(SimpleRollingWindowFeaturizer_uint16_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(SimpleRollingWindowFeaturizer_uint16_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <uint32> */
template <typename VectorInputT, typename... ConstructorArgTs>
void SimpleRollingWindowFeaturizer_uint32_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<nonstd::optional<std::uint32_t>>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    SimpleRollingWindowFeaturizer_uint32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_uint32_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(SimpleRollingWindowFeaturizer_uint32_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
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

            REQUIRE(SimpleRollingWindowFeaturizer_uint32_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(SimpleRollingWindowFeaturizer_uint32_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    SimpleRollingWindowFeaturizer_uint32_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(SimpleRollingWindowFeaturizer_uint32_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    SimpleRollingWindowFeaturizer_uint32_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_uint32_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(SimpleRollingWindowFeaturizer_uint32_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<nonstd::optional<std::uint32_t>>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::uint32_t ** result_ptr;
        size_t result_items;

        REQUIRE(SimpleRollingWindowFeaturizer_uint32_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        // Convert the pointers into optional values
        {
            std::vector<nonstd::optional<std::uint32_t>> temp;

            temp.reserve(result_items);

            for(std::uint32_t **ptr = result_ptr; ptr != result_ptr + result_items; ++ptr) {
                if(*ptr != nullptr)
                    temp.emplace_back(std::move(**ptr));
                else
                    temp.emplace_back(nonstd::optional<std::uint32_t>());
            }

            results.emplace_back(std::move(temp));
        }
        
        // Destroy the contents
        REQUIRE(SimpleRollingWindowFeaturizer_uint32_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(SimpleRollingWindowFeaturizer_uint32_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <uint64> */
template <typename VectorInputT, typename... ConstructorArgTs>
void SimpleRollingWindowFeaturizer_uint64_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<nonstd::optional<std::uint64_t>>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    SimpleRollingWindowFeaturizer_uint64_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_uint64_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(SimpleRollingWindowFeaturizer_uint64_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
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

            REQUIRE(SimpleRollingWindowFeaturizer_uint64_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(SimpleRollingWindowFeaturizer_uint64_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    SimpleRollingWindowFeaturizer_uint64_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(SimpleRollingWindowFeaturizer_uint64_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    SimpleRollingWindowFeaturizer_uint64_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_uint64_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(SimpleRollingWindowFeaturizer_uint64_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<nonstd::optional<std::uint64_t>>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::uint64_t ** result_ptr;
        size_t result_items;

        REQUIRE(SimpleRollingWindowFeaturizer_uint64_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        // Convert the pointers into optional values
        {
            std::vector<nonstd::optional<std::uint64_t>> temp;

            temp.reserve(result_items);

            for(std::uint64_t **ptr = result_ptr; ptr != result_ptr + result_items; ++ptr) {
                if(*ptr != nullptr)
                    temp.emplace_back(std::move(**ptr));
                else
                    temp.emplace_back(nonstd::optional<std::uint64_t>());
            }

            results.emplace_back(std::move(temp));
        }
        
        // Destroy the contents
        REQUIRE(SimpleRollingWindowFeaturizer_uint64_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(SimpleRollingWindowFeaturizer_uint64_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <float> */
template <typename VectorInputT, typename... ConstructorArgTs>
void SimpleRollingWindowFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::float_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    SimpleRollingWindowFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_float_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(SimpleRollingWindowFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
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

            REQUIRE(SimpleRollingWindowFeaturizer_float_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(SimpleRollingWindowFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    SimpleRollingWindowFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(SimpleRollingWindowFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    SimpleRollingWindowFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(SimpleRollingWindowFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::float_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        std::float_t* result_ptr;
        size_t result_items;

        REQUIRE(SimpleRollingWindowFeaturizer_float_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::float_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(SimpleRollingWindowFeaturizer_float_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(SimpleRollingWindowFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <double> */
template <typename VectorInputT, typename... ConstructorArgTs>
void SimpleRollingWindowFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::double_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    SimpleRollingWindowFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_double_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(SimpleRollingWindowFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
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

            REQUIRE(SimpleRollingWindowFeaturizer_double_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(SimpleRollingWindowFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    SimpleRollingWindowFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(SimpleRollingWindowFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    SimpleRollingWindowFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(SimpleRollingWindowFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
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

        REQUIRE(SimpleRollingWindowFeaturizer_double_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &result_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(std::vector<std::double_t>(result_ptr, result_ptr + result_items));
        
        // Destroy the contents
        REQUIRE(SimpleRollingWindowFeaturizer_double_DestroyTransformedData(result_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(SimpleRollingWindowFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  SimpleRollingWindowFeaturizer <string> */
template <typename VectorInputT, typename... ConstructorArgTs>
void SimpleRollingWindowFeaturizer_string_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<nonstd::optional<std::string>>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    SimpleRollingWindowFeaturizer_string_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_string_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(SimpleRollingWindowFeaturizer_string_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
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

            REQUIRE(SimpleRollingWindowFeaturizer_string_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1.c_str(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(SimpleRollingWindowFeaturizer_string_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    SimpleRollingWindowFeaturizer_string_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(SimpleRollingWindowFeaturizer_string_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    SimpleRollingWindowFeaturizer_string_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(SimpleRollingWindowFeaturizer_string_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(SimpleRollingWindowFeaturizer_string_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<nonstd::optional<std::string>>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        char const ** result_ptr_ptr;
        size_t result_items;

        REQUIRE(SimpleRollingWindowFeaturizer_string_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1.c_str(), &result_ptr_ptr, &result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        // Convert the pointers into optional values
        {
            std::vector<nonstd::optional<std::string>> temp;

            temp.reserve(result_items);

            for(char const **ptr = result_ptr_ptr; ptr != result_ptr_ptr + result_items; ++ptr) {
                if(*ptr != nullptr)
                    temp.emplace_back(std::move(**ptr));
                else
                    temp.emplace_back(nonstd::optional<std::string>());
            }

            results.emplace_back(std::move(temp));
        }
        
        // Destroy the contents
        REQUIRE(SimpleRollingWindowFeaturizer_string_DestroyTransformedData(result_ptr_ptr, result_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(SimpleRollingWindowFeaturizer_string_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
