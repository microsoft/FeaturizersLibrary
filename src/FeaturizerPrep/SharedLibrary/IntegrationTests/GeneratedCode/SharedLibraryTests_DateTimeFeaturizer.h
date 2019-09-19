/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_DateTimeFeaturizer.h"
#include "Traits.h"

/* ---------------------------------------------------------------------- */
/* |  DateTimeFeaturizer */
template <typename VectorInputT>
void DateTimeFeaturizer_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<TimePoint *> const &)> const &verify_func
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    DateTimeFeaturizer_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(DateTimeFeaturizer_CreateEstimator(&pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            FitResult result(Continue);
            auto const & input(*iter);

            REQUIRE(DateTimeFeaturizer_Fit(pEstimatorHandle, input, &result, &pErrorInfo));
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

                REQUIRE(DateTimeFeaturizer_CompleteTraining(pEstimatorHandle, &result, &pErrorInfo));
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

        REQUIRE(DateTimeFeaturizer_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    DateTimeFeaturizer_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(DateTimeFeaturizer_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(DateTimeFeaturizer_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<TimePoint *> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        TimePoint * result(nullptr);

        REQUIRE(DateTimeFeaturizer_Transform(pTransformerHandle, input, &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.emplace_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto const & result : results) {
        REQUIRE(DateTimeFeaturizer_DestroyTransformedData(result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(DateTimeFeaturizer_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}
