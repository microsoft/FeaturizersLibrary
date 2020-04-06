/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_LagLeadOperatorFeaturizer.h"

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
/* |  LagLeadOperatorFeaturizer <float> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LagLeadOperatorFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::tuple<std::vector<std::string>, Microsoft::Featurizer::RowMajMatrix<std::float_t>>>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LagLeadOperatorFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LagLeadOperatorFeaturizer_float_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(LagLeadOperatorFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
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

            REQUIRE(LagLeadOperatorFeaturizer_float_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(LagLeadOperatorFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    LagLeadOperatorFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LagLeadOperatorFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LagLeadOperatorFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LagLeadOperatorFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LagLeadOperatorFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::tuple<std::vector<std::string>, Microsoft::Featurizer::RowMajMatrix<std::float_t>>>> results;

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        char *** results_item0_ptr_items;
        size_t* results_item0_items_items;
        size_t* results_item1_cols_items;
        size_t* results_item1_rows_items;
        std::float_t ** results_item1_ptr_items;
        size_t results_items;

        REQUIRE(LagLeadOperatorFeaturizer_float_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &results_item0_ptr_items, &results_item0_items_items, &results_item1_cols_items, &results_item1_rows_items, &results_item1_ptr_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        char *** results_item0_ptr_items_ptr(results_item0_ptr_items);
        size_t* results_item0_items_items_ptr(results_item0_items_items);
        size_t* results_item1_cols_items_ptr(results_item1_cols_items);
        size_t* results_item1_rows_items_ptr(results_item1_rows_items);
        std::float_t ** results_item1_ptr_items_ptr(results_item1_ptr_items);

        while(results_buffer.size() < results_items) {
            char ** & results_item0_ptr(*results_item0_ptr_items_ptr);
            size_t & results_item0_items(*results_item0_items_items_ptr);
            size_t & results_item1_cols(*results_item1_cols_items_ptr);
            size_t & results_item1_rows(*results_item1_rows_items_ptr);
            std::float_t * & results_item1_ptr(*results_item1_ptr_items_ptr);

            results_buffer.emplace_back(CreateUniqueId(results_item0_ptr, results_item0_items), CreateMatrix(results_item1_cols, results_item1_rows, results_item1_ptr));

            ++results_item0_ptr_items_ptr;
            ++results_item0_items_items_ptr;
            ++results_item1_cols_items_ptr;
            ++results_item1_rows_items_ptr;
            ++results_item1_ptr_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(LagLeadOperatorFeaturizer_float_DestroyTransformedData(results_item0_ptr_items, results_item0_items_items, results_item1_cols_items, results_item1_rows_items, results_item1_ptr_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(true) {
        char *** results_item0_ptr_items;
        size_t* results_item0_items_items;
        size_t* results_item1_cols_items;
        size_t* results_item1_rows_items;
        std::float_t ** results_item1_ptr_items;
        size_t results_items;

        REQUIRE(LagLeadOperatorFeaturizer_float_Flush(pTransformerHandle, &results_item0_ptr_items, &results_item0_items_items, &results_item1_cols_items, &results_item1_rows_items, &results_item1_ptr_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        char *** results_item0_ptr_items_ptr(results_item0_ptr_items);
        size_t* results_item0_items_items_ptr(results_item0_items_items);
        size_t* results_item1_cols_items_ptr(results_item1_cols_items);
        size_t* results_item1_rows_items_ptr(results_item1_rows_items);
        std::float_t ** results_item1_ptr_items_ptr(results_item1_ptr_items);

        while(results_buffer.size() < results_items) {
            char ** & results_item0_ptr(*results_item0_ptr_items_ptr);
            size_t & results_item0_items(*results_item0_items_items_ptr);
            size_t & results_item1_cols(*results_item1_cols_items_ptr);
            size_t & results_item1_rows(*results_item1_rows_items_ptr);
            std::float_t * & results_item1_ptr(*results_item1_ptr_items_ptr);

            results_buffer.emplace_back(CreateUniqueId(results_item0_ptr, results_item0_items), CreateMatrix(results_item1_cols, results_item1_rows, results_item1_ptr));

            ++results_item0_ptr_items_ptr;
            ++results_item0_items_items_ptr;
            ++results_item1_cols_items_ptr;
            ++results_item1_rows_items_ptr;
            ++results_item1_ptr_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(LagLeadOperatorFeaturizer_float_DestroyTransformedData(results_item0_ptr_items, results_item0_items_items, results_item1_cols_items, results_item1_rows_items, results_item1_ptr_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(LagLeadOperatorFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  LagLeadOperatorFeaturizer <double> */
template <typename VectorInputT, typename... ConstructorArgTs>
void LagLeadOperatorFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::tuple<std::vector<std::string>, Microsoft::Featurizer::RowMajMatrix<std::double_t>>>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    LagLeadOperatorFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(LagLeadOperatorFeaturizer_double_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(LagLeadOperatorFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
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

            REQUIRE(LagLeadOperatorFeaturizer_double_Fit(pEstimatorHandle, input0_buffer.data(), input0_buffer.size(), input1, &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(LagLeadOperatorFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    LagLeadOperatorFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(LagLeadOperatorFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    LagLeadOperatorFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(LagLeadOperatorFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(LagLeadOperatorFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::tuple<std::vector<std::string>, Microsoft::Featurizer::RowMajMatrix<std::double_t>>>> results;

    for(auto const & input : inference_input) {
        auto const & input0(std::get<0>(input));

        std::vector<char const *> input0_buffer;

        input0_buffer.reserve(input0.size());

        for(std::string const &value : input0)
            input0_buffer.emplace_back(value.c_str());

        auto const & input1(std::get<1>(input));

        char *** results_item0_ptr_items;
        size_t* results_item0_items_items;
        size_t* results_item1_cols_items;
        size_t* results_item1_rows_items;
        std::double_t ** results_item1_ptr_items;
        size_t results_items;

        REQUIRE(LagLeadOperatorFeaturizer_double_Transform(pTransformerHandle, input0_buffer.data(), input0_buffer.size(), input1, &results_item0_ptr_items, &results_item0_items_items, &results_item1_cols_items, &results_item1_rows_items, &results_item1_ptr_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        char *** results_item0_ptr_items_ptr(results_item0_ptr_items);
        size_t* results_item0_items_items_ptr(results_item0_items_items);
        size_t* results_item1_cols_items_ptr(results_item1_cols_items);
        size_t* results_item1_rows_items_ptr(results_item1_rows_items);
        std::double_t ** results_item1_ptr_items_ptr(results_item1_ptr_items);

        while(results_buffer.size() < results_items) {
            char ** & results_item0_ptr(*results_item0_ptr_items_ptr);
            size_t & results_item0_items(*results_item0_items_items_ptr);
            size_t & results_item1_cols(*results_item1_cols_items_ptr);
            size_t & results_item1_rows(*results_item1_rows_items_ptr);
            std::double_t * & results_item1_ptr(*results_item1_ptr_items_ptr);

            results_buffer.emplace_back(CreateUniqueId(results_item0_ptr, results_item0_items), CreateMatrix(results_item1_cols, results_item1_rows, results_item1_ptr));

            ++results_item0_ptr_items_ptr;
            ++results_item0_items_items_ptr;
            ++results_item1_cols_items_ptr;
            ++results_item1_rows_items_ptr;
            ++results_item1_ptr_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(LagLeadOperatorFeaturizer_double_DestroyTransformedData(results_item0_ptr_items, results_item0_items_items, results_item1_cols_items, results_item1_rows_items, results_item1_ptr_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(true) {
        char *** results_item0_ptr_items;
        size_t* results_item0_items_items;
        size_t* results_item1_cols_items;
        size_t* results_item1_rows_items;
        std::double_t ** results_item1_ptr_items;
        size_t results_items;

        REQUIRE(LagLeadOperatorFeaturizer_double_Flush(pTransformerHandle, &results_item0_ptr_items, &results_item0_items_items, &results_item1_cols_items, &results_item1_rows_items, &results_item1_ptr_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        char *** results_item0_ptr_items_ptr(results_item0_ptr_items);
        size_t* results_item0_items_items_ptr(results_item0_items_items);
        size_t* results_item1_cols_items_ptr(results_item1_cols_items);
        size_t* results_item1_rows_items_ptr(results_item1_rows_items);
        std::double_t ** results_item1_ptr_items_ptr(results_item1_ptr_items);

        while(results_buffer.size() < results_items) {
            char ** & results_item0_ptr(*results_item0_ptr_items_ptr);
            size_t & results_item0_items(*results_item0_items_items_ptr);
            size_t & results_item1_cols(*results_item1_cols_items_ptr);
            size_t & results_item1_rows(*results_item1_rows_items_ptr);
            std::double_t * & results_item1_ptr(*results_item1_ptr_items_ptr);

            results_buffer.emplace_back(CreateUniqueId(results_item0_ptr, results_item0_items), CreateMatrix(results_item1_cols, results_item1_rows, results_item1_ptr));

            ++results_item0_ptr_items_ptr;
            ++results_item0_items_items_ptr;
            ++results_item1_cols_items_ptr;
            ++results_item1_rows_items_ptr;
            ++results_item1_ptr_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(LagLeadOperatorFeaturizer_double_DestroyTransformedData(results_item0_ptr_items, results_item0_items_items, results_item1_cols_items, results_item1_rows_items, results_item1_ptr_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(LagLeadOperatorFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
