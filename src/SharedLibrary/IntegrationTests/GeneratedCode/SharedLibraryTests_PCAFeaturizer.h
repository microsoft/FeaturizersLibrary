/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_PCAFeaturizer.h"

#include "Traits.h"
#include "Featurizers/Structs.h"

#include "SharedLibrary_Common.hpp"

/* ---------------------------------------------------------------------- */
/* |  PCAFeaturizer <float> */
template <typename VectorInputT>
void PCAFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Eigen::MatrixX<std::float_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    PCAFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(PCAFeaturizer_float_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(PCAFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(PCAFeaturizer_float_Fit(pEstimatorHandle, static_cast<size_t>(input.cols()), static_cast<size_t>(input.rows()), input.data(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(PCAFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    PCAFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(PCAFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    PCAFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(PCAFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(PCAFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Eigen::MatrixX<std::float_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        size_t result_cols(0);
        size_t result_rows(0);
        std::float_t * result_ptr(nullptr);

        REQUIRE(PCAFeaturizer_float_Transform(pTransformerHandle, static_cast<size_t>(input.cols()), static_cast<size_t>(input.rows()), input.data(), &result_cols, &result_rows, &result_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
        results.push_back(Eigen::Map<Eigen::MatrixX<std::float_t>>(result_ptr, static_cast<Eigen::Index>(result_cols), static_cast<Eigen::Index>(result_rows)));
        #else
        results.emplace_back(Eigen::Map<Eigen::MatrixX<std::float_t>>(result_ptr, static_cast<Eigen::Index>(result_cols), static_cast<Eigen::Index>(result_rows)));
        #endif
        
        // Destroy the contents
        REQUIRE(PCAFeaturizer_float_DestroyTransformedData(result_cols, result_rows, result_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(PCAFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  PCAFeaturizer <double> */
template <typename VectorInputT>
void PCAFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Eigen::MatrixX<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    PCAFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(PCAFeaturizer_double_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(PCAFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(PCAFeaturizer_double_Fit(pEstimatorHandle, static_cast<size_t>(input.cols()), static_cast<size_t>(input.rows()), input.data(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(PCAFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    PCAFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(PCAFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    PCAFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(PCAFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(PCAFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Eigen::MatrixX<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        size_t result_cols(0);
        size_t result_rows(0);
        std::double_t * result_ptr(nullptr);

        REQUIRE(PCAFeaturizer_double_Transform(pTransformerHandle, static_cast<size_t>(input.cols()), static_cast<size_t>(input.rows()), input.data(), &result_cols, &result_rows, &result_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
        results.push_back(Eigen::Map<Eigen::MatrixX<std::double_t>>(result_ptr, static_cast<Eigen::Index>(result_cols), static_cast<Eigen::Index>(result_rows)));
        #else
        results.emplace_back(Eigen::Map<Eigen::MatrixX<std::double_t>>(result_ptr, static_cast<Eigen::Index>(result_cols), static_cast<Eigen::Index>(result_rows)));
        #endif
        
        // Destroy the contents
        REQUIRE(PCAFeaturizer_double_DestroyTransformedData(result_cols, result_rows, result_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(PCAFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

