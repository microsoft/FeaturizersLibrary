
// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Featurizer.h"

namespace Microsoft {
namespace Featurizer {
namespace TestHelpers {

namespace NS = Microsoft::Featurizer;
namespace {
template <typename T, typename ArgT>
void make_vector(std::vector<T> & v, ArgT && arg) {
    v.emplace_back(std::forward<ArgT>(arg));
}

template <typename T, typename ArgT, typename... ArgsT>
void make_vector(std::vector<T> &v, ArgT && arg, ArgsT &&...args) {
    make_vector(v, std::forward<ArgT>(arg));
    make_vector(v, std::forward<ArgsT>(args)...);
}

} // anonymous namespace

template <typename T, typename... ArgsT>
std::vector<T> make_vector(ArgsT &&... args) {
    std::vector<T>                          result;

    result.reserve(sizeof...(ArgsT));

    make_vector(result, std::forward<ArgsT>(args)...);
    return result;
}

template <typename T>
std::vector<T> make_vector(void) {
    return std::vector<T>();
}


template <typename PipelineT, typename InputT>
void Train(
    PipelineT& pipeline,
    std::vector<std::vector<std::remove_const_t<std::remove_reference_t<InputT>>>> const &inputBatches
) {
    using FitResult                         = typename NS::Estimator::FitResult;
    using Batches                           = std::vector<std::vector<std::remove_const_t<std::remove_reference_t<InputT>>>>;
    typename Batches::const_iterator iter(inputBatches.begin());
    while(true) {
        FitResult const                     result(pipeline.fit(iter->data(), iter->size()));
        
        
            if(result == FitResult::Complete)
                break;
            else if(result == FitResult::ResetAndContinue)
                iter = inputBatches.begin();
            else if(result == FitResult::Continue) {
                ++iter;

                if(iter == inputBatches.end()) {
                    if(pipeline.complete_training() == FitResult::Complete)
                        break;

                    iter = inputBatches.begin();
                }
            }
        }
    assert(pipeline.is_training_complete());
}
    



template <typename PipelineT>
std::vector<typename PipelineT::TransformedType> TransformerEstimatorTest(
    PipelineT &pipeline,
    std::vector<std::vector<std::remove_const_t<std::remove_reference_t<typename PipelineT::InputType>>>> const &inputBatches,
    std::vector<std::remove_const_t<std::remove_reference_t<typename PipelineT::InputType>>> const &data
) {
    Train<PipelineT, typename PipelineT::InputType>(pipeline, inputBatches);

    typename PipelineT::TransformerUniquePtr                  pTransformer(pipeline.create_transformer());
    std::vector<typename PipelineT::TransformedType>    	  output;

    output.reserve(data.size());

    for(auto const &item : data)
        output.emplace_back(pTransformer->execute(item));

    return output;
}
}
}
}
