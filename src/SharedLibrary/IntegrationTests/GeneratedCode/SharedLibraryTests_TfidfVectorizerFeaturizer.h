/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_TfidfVectorizerFeaturizer.h"

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
/* |  TfidfVectorizerFeaturizer */
template <typename VectorInputT, typename... ConstructorArgTs>
void TfidfVectorizerFeaturizer_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<Microsoft::Featurizer::Featurizers::SparseVectorEncoding<std::float_t>> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    TfidfVectorizerFeaturizer_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(TfidfVectorizerFeaturizer_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(TfidfVectorizerFeaturizer_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            REQUIRE(TfidfVectorizerFeaturizer_Fit(pEstimatorHandle, input.c_str(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(TfidfVectorizerFeaturizer_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    TfidfVectorizerFeaturizer_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(TfidfVectorizerFeaturizer_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    TfidfVectorizerFeaturizer_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(TfidfVectorizerFeaturizer_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(TfidfVectorizerFeaturizer_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<Microsoft::Featurizer::Featurizers::SparseVectorEncoding<std::float_t>> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        uint64_t results_numElements;
        uint64_t results_numValues;
        std::float_t * results_values;
        uint64_t * results_indexes;

        REQUIRE(TfidfVectorizerFeaturizer_Transform(pTransformerHandle, input.c_str(), &results_numElements, &results_numValues, &results_values, &results_indexes, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        std::vector<typename Microsoft::Featurizer::Featurizers::SparseVectorEncoding<std::float_t>::ValueEncoding> encodings;
        std::float_t const *pValue(results_values);
        uint64_t const *pIndex(results_indexes);

        while(results_numValues--) {
            encodings.emplace_back(*pValue++, *pIndex++);
        }

        results.emplace_back(results_numElements, std::move(encodings));
        
        // Destroy the contents
        REQUIRE(TfidfVectorizerFeaturizer_DestroyTransformedData(results_numElements, results_numValues, results_values, results_indexes, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(TfidfVectorizerFeaturizer_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
