/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_TruncatedSVDFeaturizer.h"

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
/* |  TruncatedSVDFeaturizer <float> */
template <typename VectorInputT>
void TruncatedSVDFeaturizer_float_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Eigen::MatrixX<std::float_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    TruncatedSVDFeaturizer_float_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(TruncatedSVDFeaturizer_float_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(TruncatedSVDFeaturizer_float_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(TruncatedSVDFeaturizer_float_Fit(pEstimatorHandle, static_cast<size_t>(input.cols()), static_cast<size_t>(input.rows()), input.data(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(TruncatedSVDFeaturizer_float_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    TruncatedSVDFeaturizer_float_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(TruncatedSVDFeaturizer_float_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    TruncatedSVDFeaturizer_float_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(TruncatedSVDFeaturizer_float_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(TruncatedSVDFeaturizer_float_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Eigen::MatrixX<std::float_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        size_t result_cols;
        size_t result_rows;
        std::float_t * result_ptr;

        REQUIRE(TruncatedSVDFeaturizer_float_Transform(pTransformerHandle, static_cast<size_t>(input.cols()), static_cast<size_t>(input.rows()), input.data(), &result_cols, &result_rows, &result_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(Eigen::Map<Eigen::MatrixX<std::float_t>>(result_ptr, static_cast<Eigen::Index>(result_cols), static_cast<Eigen::Index>(result_rows)));
        
        // Destroy the contents
        REQUIRE(TruncatedSVDFeaturizer_float_DestroyTransformedData(result_cols, result_rows, result_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(TruncatedSVDFeaturizer_float_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

/* ---------------------------------------------------------------------- */
/* |  TruncatedSVDFeaturizer <double> */
template <typename VectorInputT>
void TruncatedSVDFeaturizer_double_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Eigen::MatrixX<std::double_t>> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    TruncatedSVDFeaturizer_double_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(TruncatedSVDFeaturizer_double_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(TruncatedSVDFeaturizer_double_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(TruncatedSVDFeaturizer_double_Fit(pEstimatorHandle, static_cast<size_t>(input.cols()), static_cast<size_t>(input.rows()), input.data(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(TruncatedSVDFeaturizer_double_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    TruncatedSVDFeaturizer_double_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(TruncatedSVDFeaturizer_double_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    TruncatedSVDFeaturizer_double_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(TruncatedSVDFeaturizer_double_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(TruncatedSVDFeaturizer_double_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Eigen::MatrixX<std::double_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        size_t result_cols;
        size_t result_rows;
        std::double_t * result_ptr;

        REQUIRE(TruncatedSVDFeaturizer_double_Transform(pTransformerHandle, static_cast<size_t>(input.cols()), static_cast<size_t>(input.rows()), input.data(), &result_cols, &result_rows, &result_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(Eigen::Map<Eigen::MatrixX<std::double_t>>(result_ptr, static_cast<Eigen::Index>(result_cols), static_cast<Eigen::Index>(result_rows)));
        
        // Destroy the contents
        REQUIRE(TruncatedSVDFeaturizer_double_DestroyTransformedData(result_cols, result_rows, result_ptr, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(TruncatedSVDFeaturizer_double_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
