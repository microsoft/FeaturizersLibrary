/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_AnalyticalRollingWindowFeaturizer.h"

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
/* |  AnalyticalRollingWindowFeaturizer <float> */
template <typename VectorInputT, typename... ConstructorArgTs>
void AnalyticalRollingWindowFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const &)> const &verify_func,
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
    std::vector<Microsoft::Featurizer::RowMajMatrix<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        size_t results_cols;
        size_t results_rows;
        std::double_t * results_ptr;

        REQUIRE(AnalyticalRollingWindowFeaturizer_float_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &results_cols, &results_rows, &results_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(CreateMatrix(results_cols, results_rows, results_ptr));
        
        // Destroy the contents
        REQUIRE(AnalyticalRollingWindowFeaturizer_float_DestroyTransformedData(results_cols, results_rows, results_ptr, &pErrorInfo));
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
    std::function<bool (std::vector<Microsoft::Featurizer::RowMajMatrix<std::double_t>> const &)> const &verify_func,
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
    std::vector<Microsoft::Featurizer::RowMajMatrix<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        size_t results_cols;
        size_t results_rows;
        std::double_t * results_ptr;

        REQUIRE(AnalyticalRollingWindowFeaturizer_double_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &results_cols, &results_rows, &results_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(CreateMatrix(results_cols, results_rows, results_ptr));
        
        // Destroy the contents
        REQUIRE(AnalyticalRollingWindowFeaturizer_double_DestroyTransformedData(results_cols, results_rows, results_ptr, &pErrorInfo));
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
