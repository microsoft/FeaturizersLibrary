/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_ForecastingPivotFeaturizer.h"

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
/* |  ForecastingPivotFeaturizer <float> */
template <typename VectorInputT>
void ForecastingPivotFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::vector<std::float_t>>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForecastingPivotFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForecastingPivotFeaturizer_float_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForecastingPivotFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            std::vector<size_t> input_cols_buffer;
            std::vector<size_t> input_rows_buffer;
            std::vector<float const *> input_data_buffer;

            input_cols_buffer.reserve(input.size());
            input_rows_buffer.reserve(input.size());
            input_data_buffer.reserve(input.size());

            for(auto const & input_element : input) {
                input_cols_buffer.emplace_back(input_element.cols());
                input_rows_buffer.emplace_back(input_element.rows());
                input_data_buffer.emplace_back(input_element.data());
            }

            REQUIRE(ForecastingPivotFeaturizer_float_Fit(pEstimatorHandle, input_cols_buffer.data(), input_rows_buffer.data(), input_data_buffer.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForecastingPivotFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForecastingPivotFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForecastingPivotFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForecastingPivotFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForecastingPivotFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForecastingPivotFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::vector<std::float_t>>> results;

    for(auto const & input : inference_input) {
        std::vector<size_t> input_cols_buffer;
        std::vector<size_t> input_rows_buffer;
        std::vector<float const *> input_data_buffer;

        input_cols_buffer.reserve(input.size());
        input_rows_buffer.reserve(input.size());
        input_data_buffer.reserve(input.size());

        for(auto const & input_element : input) {
            input_cols_buffer.emplace_back(input_element.cols());
            input_rows_buffer.emplace_back(input_element.rows());
            input_data_buffer.emplace_back(input_element.data());
        }

        std::float_t** results_item_item_value_items_items;
        size_t* results_item_items_items;
        size_t results_items;

        REQUIRE(ForecastingPivotFeaturizer_float_Transform(pTransformerHandle, input_cols_buffer.data(), input_rows_buffer.data(), input_data_buffer.data(), input.size(), &results_item_item_value_items_items, &results_item_items_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::float_t** results_item_item_value_items_items_ptr(results_item_item_value_items_items);
        size_t* results_item_items_items_ptr(results_item_items_items);

        while(results_buffer.size() < results_items) {
            std::float_t* & results_item_item_value_items(*results_item_item_value_items_items_ptr);
            size_t & results_item_items(*results_item_items_items_ptr);

            typename decltype(results_buffer)::value_type results_item_buffer;

            results_item_buffer.reserve(results_item_items);

            std::float_t* results_item_item_value_items_ptr(results_item_item_value_items);

            while(results_item_buffer.size() < results_item_items) {
                std::float_t & results_item_item_value(*results_item_item_value_items_ptr);

                results_item_buffer.emplace_back(std::move(results_item_item_value));

                ++results_item_item_value_items_ptr;
            }

            results_buffer.emplace_back(std::move(results_item_buffer));

            ++results_item_item_value_items_items_ptr;
            ++results_item_items_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(ForecastingPivotFeaturizer_float_DestroyTransformedData(results_item_item_value_items_items, results_item_items_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(true) {
        std::float_t** results_item_item_value_items_items;
        size_t* results_item_items_items;
        size_t results_items;

        REQUIRE(ForecastingPivotFeaturizer_float_Flush(pTransformerHandle, &results_item_item_value_items_items, &results_item_items_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::float_t** results_item_item_value_items_items_ptr(results_item_item_value_items_items);
        size_t* results_item_items_items_ptr(results_item_items_items);

        while(results_buffer.size() < results_items) {
            std::float_t* & results_item_item_value_items(*results_item_item_value_items_items_ptr);
            size_t & results_item_items(*results_item_items_items_ptr);

            typename decltype(results_buffer)::value_type results_item_buffer;

            results_item_buffer.reserve(results_item_items);

            std::float_t* results_item_item_value_items_ptr(results_item_item_value_items);

            while(results_item_buffer.size() < results_item_items) {
                std::float_t & results_item_item_value(*results_item_item_value_items_ptr);

                results_item_buffer.emplace_back(std::move(results_item_item_value));

                ++results_item_item_value_items_ptr;
            }

            results_buffer.emplace_back(std::move(results_item_buffer));

            ++results_item_item_value_items_items_ptr;
            ++results_item_items_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(ForecastingPivotFeaturizer_float_DestroyTransformedData(results_item_item_value_items_items, results_item_items_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForecastingPivotFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  ForecastingPivotFeaturizer <double> */
template <typename VectorInputT>
void ForecastingPivotFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<std::vector<std::vector<std::double_t>>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ForecastingPivotFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ForecastingPivotFeaturizer_double_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ForecastingPivotFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            std::vector<size_t> input_cols_buffer;
            std::vector<size_t> input_rows_buffer;
            std::vector<double const *> input_data_buffer;

            input_cols_buffer.reserve(input.size());
            input_rows_buffer.reserve(input.size());
            input_data_buffer.reserve(input.size());

            for(auto const & input_element : input) {
                input_cols_buffer.emplace_back(input_element.cols());
                input_rows_buffer.emplace_back(input_element.rows());
                input_data_buffer.emplace_back(input_element.data());
            }

            REQUIRE(ForecastingPivotFeaturizer_double_Fit(pEstimatorHandle, input_cols_buffer.data(), input_rows_buffer.data(), input_data_buffer.data(), input.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ForecastingPivotFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ForecastingPivotFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ForecastingPivotFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ForecastingPivotFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ForecastingPivotFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ForecastingPivotFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<std::vector<std::vector<std::double_t>>> results;

    for(auto const & input : inference_input) {
        std::vector<size_t> input_cols_buffer;
        std::vector<size_t> input_rows_buffer;
        std::vector<double const *> input_data_buffer;

        input_cols_buffer.reserve(input.size());
        input_rows_buffer.reserve(input.size());
        input_data_buffer.reserve(input.size());

        for(auto const & input_element : input) {
            input_cols_buffer.emplace_back(input_element.cols());
            input_rows_buffer.emplace_back(input_element.rows());
            input_data_buffer.emplace_back(input_element.data());
        }

        std::double_t** results_item_item_value_items_items;
        size_t* results_item_items_items;
        size_t results_items;

        REQUIRE(ForecastingPivotFeaturizer_double_Transform(pTransformerHandle, input_cols_buffer.data(), input_rows_buffer.data(), input_data_buffer.data(), input.size(), &results_item_item_value_items_items, &results_item_items_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::double_t** results_item_item_value_items_items_ptr(results_item_item_value_items_items);
        size_t* results_item_items_items_ptr(results_item_items_items);

        while(results_buffer.size() < results_items) {
            std::double_t* & results_item_item_value_items(*results_item_item_value_items_items_ptr);
            size_t & results_item_items(*results_item_items_items_ptr);

            typename decltype(results_buffer)::value_type results_item_buffer;

            results_item_buffer.reserve(results_item_items);

            std::double_t* results_item_item_value_items_ptr(results_item_item_value_items);

            while(results_item_buffer.size() < results_item_items) {
                std::double_t & results_item_item_value(*results_item_item_value_items_ptr);

                results_item_buffer.emplace_back(std::move(results_item_item_value));

                ++results_item_item_value_items_ptr;
            }

            results_buffer.emplace_back(std::move(results_item_buffer));

            ++results_item_item_value_items_items_ptr;
            ++results_item_items_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(ForecastingPivotFeaturizer_double_DestroyTransformedData(results_item_item_value_items_items, results_item_items_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    if(true) {
        std::double_t** results_item_item_value_items_items;
        size_t* results_item_items_items;
        size_t results_items;

        REQUIRE(ForecastingPivotFeaturizer_double_Flush(pTransformerHandle, &results_item_item_value_items_items, &results_item_items_items, &results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        typename decltype(results)::value_type results_buffer;

        results_buffer.reserve(results_items);

        std::double_t** results_item_item_value_items_items_ptr(results_item_item_value_items_items);
        size_t* results_item_items_items_ptr(results_item_items_items);

        while(results_buffer.size() < results_items) {
            std::double_t* & results_item_item_value_items(*results_item_item_value_items_items_ptr);
            size_t & results_item_items(*results_item_items_items_ptr);

            typename decltype(results_buffer)::value_type results_item_buffer;

            results_item_buffer.reserve(results_item_items);

            std::double_t* results_item_item_value_items_ptr(results_item_item_value_items);

            while(results_item_buffer.size() < results_item_items) {
                std::double_t & results_item_item_value(*results_item_item_value_items_ptr);

                results_item_buffer.emplace_back(std::move(results_item_item_value));

                ++results_item_item_value_items_ptr;
            }

            results_buffer.emplace_back(std::move(results_item_buffer));

            ++results_item_item_value_items_items_ptr;
            ++results_item_items_items_ptr;
        }

        results.emplace_back(std::move(results_buffer));
        
        // Destroy the contents
        REQUIRE(ForecastingPivotFeaturizer_double_DestroyTransformedData(results_item_item_value_items_items, results_item_items_items, results_items, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ForecastingPivotFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
