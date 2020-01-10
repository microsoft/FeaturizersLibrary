/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_DateTimeFeaturizer.h"

#include "Traits.h"
#include "Featurizers/Structs.h"

#include "SharedLibrary_Common.hpp"

/* ---------------------------------------------------------------------- */
/* |  DateTimeFeaturizer */
template <typename VectorInputT, typename... ConstructorArgTs>
void DateTimeFeaturizer_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<TimePoint> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    DateTimeFeaturizer_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(DateTimeFeaturizer_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(DateTimeFeaturizer_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(DateTimeFeaturizer_Fit(pEstimatorHandle, CreateDateTimeParameter(input), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(DateTimeFeaturizer_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    DateTimeFeaturizer_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


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
    std::vector<TimePoint> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        TimePoint result;

        REQUIRE(DateTimeFeaturizer_Transform(pTransformerHandle, CreateDateTimeParameter(input), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        #if (defined __apple_build_version__)
        results.push_back(result);
        #else
        results.emplace_back(result);
        #endif
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    for(auto & result: results) {
        REQUIRE(DateTimeFeaturizer_DestroyTransformedData(&result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    // Destroy the transformer
    REQUIRE(DateTimeFeaturizer_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

