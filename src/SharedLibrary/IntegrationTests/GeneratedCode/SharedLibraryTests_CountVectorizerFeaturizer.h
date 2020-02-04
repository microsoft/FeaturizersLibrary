/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_CountVectorizerFeaturizer.h"

#include "Traits.h"
#include "Featurizers/Structs.h"

#include "SharedLibrary_Common.hpp"

/* ---------------------------------------------------------------------- */
/* |  CountVectorizerFeaturizer */
template <typename VectorInputT, typename... ConstructorArgTs>
void CountVectorizerFeaturizer_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SparseVectorEncoding<std::uint32_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    CountVectorizerFeaturizer_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(CountVectorizerFeaturizer_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(CountVectorizerFeaturizer_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(CountVectorizerFeaturizer_Fit(pEstimatorHandle, input.c_str(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(CountVectorizerFeaturizer_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    CountVectorizerFeaturizer_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);


    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(CountVectorizerFeaturizer_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    CountVectorizerFeaturizer_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(CountVectorizerFeaturizer_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(CountVectorizerFeaturizer_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SparseVectorEncoding<std::uint32_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t numElements(0);
        uint64_t numValues(0);
        std::uint32_t * pValues(nullptr);
        uint64_t *pIndexes(nullptr);

        REQUIRE(CountVectorizerFeaturizer_Transform(pTransformerHandle, input.c_str(), &numElements, &numValues, &pValues, &pIndexes, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        std::vector<typename Microsoft::Featurizer::Featurizers::SparseVectorEncoding<std::uint32_t>::ValueEncoding> encodings;
        std::uint32_t const *pValue(pValues);
        uint64_t const *pIndex(pIndexes);

        while(numValues--) {
            encodings.emplace_back(*pValue++, *pIndex++);
        }

        results.emplace_back(numElements, std::move(encodings));
        
        // Destroy the contents
        REQUIRE(CountVectorizerFeaturizer_DestroyTransformedData(numElements, numValues, pValues, pIndexes, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(CountVectorizerFeaturizer_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

