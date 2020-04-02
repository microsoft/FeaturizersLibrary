/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_ShortGrainDropperFeaturizer.h"

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
/* |  ShortGrainDropperFeaturizer */
template <typename VectorInputT, typename... ConstructorArgTs>
void ShortGrainDropperFeaturizer_Test(
    std::vector<VectorInputT> const &training_input,
    std::vector<VectorInputT> const &inference_input,
    std::function<bool (std::vector<bool> const &)> const &verify_func,
    ConstructorArgTs &&... constructor_args
) {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    ShortGrainDropperFeaturizer_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(ShortGrainDropperFeaturizer_CreateEstimator(std::forward<ConstructorArgTs>(constructor_args)..., &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Train
    if(training_input.empty() == false) {
        typename std::vector<VectorInputT>::const_iterator iter(training_input.begin());

        while(true) {
            TrainingState trainingState(0);

            REQUIRE(ShortGrainDropperFeaturizer_GetState(pEstimatorHandle, &trainingState, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(trainingState != Training)
                break;

            FitResult result(0);
            auto const & input(*iter);

            std::vector<char const *> input_buffer;

            input_buffer.reserve(input.size());

            for(std::string const &value : input)
                input_buffer.emplace_back(value.c_str());

            REQUIRE(ShortGrainDropperFeaturizer_Fit(pEstimatorHandle, input_buffer.data(), input_buffer.size(), &result, &pErrorInfo));
            REQUIRE(pErrorInfo == nullptr);

            if(result == ResetAndContinue) {
                iter = training_input.begin();
                continue;
            }

            ++iter;
            if(iter == training_input.end()) {
                REQUIRE(ShortGrainDropperFeaturizer_OnDataCompleted(pEstimatorHandle, &pErrorInfo));
                REQUIRE(pErrorInfo == nullptr);

                iter = training_input.begin();
            }
        }
    }

    ShortGrainDropperFeaturizer_CompleteTraining(pEstimatorHandle, &pErrorInfo);
    REQUIRE(pErrorInfo == nullptr);

    // Once here, training should be complete
    {
        bool is_complete(false);

        REQUIRE(ShortGrainDropperFeaturizer_IsTrainingComplete(pEstimatorHandle, &is_complete, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);
        REQUIRE(is_complete);
    }

    // Create the Transformer
    ShortGrainDropperFeaturizer_TransformerHandle * pTransformerHandle(nullptr);

    REQUIRE(ShortGrainDropperFeaturizer_CreateTransformerFromEstimator(pEstimatorHandle, &pTransformerHandle, &pErrorInfo));
    REQUIRE(pTransformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the estimator
    REQUIRE(ShortGrainDropperFeaturizer_DestroyEstimator(pEstimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Inference
    std::vector<bool> results;

    results.reserve(inference_input.size());

    for(auto const & input : inference_input) {
        std::vector<char const *> input_buffer;

        input_buffer.reserve(input.size());

        for(std::string const &value : input)
            input_buffer.emplace_back(value.c_str());

        bool result;

        REQUIRE(ShortGrainDropperFeaturizer_Transform(pTransformerHandle, input_buffer.data(), input_buffer.size(), &result, &pErrorInfo));
        REQUIRE(pErrorInfo == nullptr);

        results.push_back(result);
        // No inline destroy statement
    }

    REQUIRE(verify_func(results));

    // No trailing destroy statement

    // Destroy the transformer
    REQUIRE(ShortGrainDropperFeaturizer_DestroyTransformer(pTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
