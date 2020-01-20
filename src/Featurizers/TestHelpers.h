
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

template <typename EstimatorT, typename InputT>
void Train(EstimatorT &estimator, std::vector<std::vector<InputT>> const &inputBatches) {
    // ----------------------------------------------------------------------
    using Batches                           = std::vector<std::vector<InputT>>;
    // ----------------------------------------------------------------------

    estimator.begin_training();

    typename Batches::const_iterator        iter(inputBatches.begin());

    while(estimator.get_state() == NS::TrainingState::Training) {
        if(estimator.fit(iter->data(), iter->size()) == NS::FitResult::Reset) {
            iter = inputBatches.begin();
            continue;
        }

        ++iter;
        if(iter == inputBatches.end()) {
            estimator.on_data_completed();

            iter = inputBatches.begin();
        }
    }

    estimator.complete_training();
}

template <typename EstimatorT>
std::vector<typename EstimatorT::TransformedType> Predict(EstimatorT &estimator, std::vector<typename EstimatorT::InputType> const &data) {

    typename EstimatorT::TransformerUniquePtr           pTransformer(estimator.create_transformer());
    std::vector<typename EstimatorT::TransformedType>   output;

    output.reserve(data.size());

    auto const                              callback(
        [&output](typename EstimatorT::TransformedType value) {
            output.emplace_back(std::move(value));
        }
    );

    for(auto const &item : data)
        pTransformer->execute(item, callback);

    pTransformer->flush(callback);

    return output;
}

template <typename EstimatorT>
std::vector<typename EstimatorT::TransformedType> TransformerEstimatorTest(
    EstimatorT estimator,
    std::vector<std::vector<typename EstimatorT::InputType>> const &inputBatches,
    std::vector<typename EstimatorT::InputType> const &data
) {
    Train<EstimatorT>(estimator, inputBatches);
    return Predict(estimator, data);
}

template <typename EstimatorT>
std::vector<typename EstimatorT::TransformedType> TransformerEstimatorTest(
    EstimatorT estimator,
    std::vector<typename EstimatorT::InputType> const &inputBatch,
    std::vector<typename EstimatorT::InputType> const &data
) {
    return TransformerEstimatorTest(
        std::move(estimator),
        make_vector<std::vector<typename EstimatorT::InputType>>(inputBatch),
        data
    );
}

template <typename EstimatorT>
std::vector<typename EstimatorT::TransformedType> TransformerTest(
    EstimatorT estimator,
    std::vector<typename EstimatorT::InputType> const &data
) {
    estimator.begin_training();
    estimator.complete_training();

    return Predict(estimator, data);
}

// Fuzzy check is used to check if two vectors<double/float> are same considering precision loss
template <typename T>
bool FuzzyCheck(std::vector<T> const & vec1, std::vector<T> const & vec2, std::double_t epsilon = 0.000001) {
    if (vec1.size() != vec2.size())
        return false;

    size_t vec_size = vec1.size();
    for (size_t idx = 0; idx < vec_size; ++idx) {
        if (abs(vec1[idx] - vec2[idx]) > static_cast<T>(epsilon)) {
            return false;
        }
    }
    return true;
}
template<>
bool FuzzyCheck<std::float_t>(std::vector<std::float_t> const & vec1, std::vector<std::float_t> const & vec2, std::double_t epsilon) {
    if (vec1.size() != vec2.size())
        return false;

    size_t vec_size = vec1.size();
    for (size_t idx = 0; idx < vec_size; ++idx) {
        if (std::isnan(vec1[idx]) && std::isnan(vec2[idx])) {
            continue;
        }
        else if (std::isnan(vec1[idx]) || std::isnan(vec2[idx])) {
            return false;
        }
        if (abs(vec1[idx] - vec2[idx]) > static_cast<std::float_t>(epsilon)) {
            return false;
        }
    }
    return true;
}
template <>
bool FuzzyCheck<std::double_t>(std::vector<std::double_t> const & vec1, std::vector<std::double_t> const & vec2, std::double_t epsilon) {
    if (vec1.size() != vec2.size())
        return false;

    size_t vec_size = vec1.size();
    for (size_t idx = 0; idx < vec_size; ++idx) {
        if (std::isnan(vec1[idx]) && std::isnan(vec2[idx])) {
            continue;
        }
        else if (std::isnan(vec1[idx]) || std::isnan(vec2[idx])) {
            return false;
        }
        if (abs(vec1[idx] - vec2[idx]) > static_cast<std::double_t>(epsilon)) {
            return false;
        }
    }
    return true;
}


} // namespace TestHelpers
} // namespace Featurizer
} // namespace Microsoft
