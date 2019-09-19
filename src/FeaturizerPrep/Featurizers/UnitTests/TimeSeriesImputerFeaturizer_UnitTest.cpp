// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Components/TimeSeriesImputerTransformer.h"
#include "../TimeSeriesImputerFeaturizer.h"
#include "../../Traits.h"

namespace NS = Microsoft::Featurizer;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunused-local-typedef"
#endif

std::chrono::system_clock::time_point GetTimePoint(std::chrono::system_clock::time_point tp, int unitsToAdd, std::string = "days"){
    return tp + std::chrono::minutes(unitsToAdd * (60*24));
}

std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>>
 Test(std::vector<std::vector<std::tuple<std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>>> const &trainingBatches,
 std::vector<std::tuple<std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> const &inferenceBatches) {
    using FitResult                 = NS::Estimator::FitResult;
    using KeyT                      = std::vector<std::string>;
    using ColsToImputeT             = std::vector<nonstd::optional<std::string>>;
    using InputBatchesType          = std::vector<std::vector<std::tuple<std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>>>;
    using TSImputerEstimator        = NS::Featurizers::TimeSeriesImputerFeaturizerEstimator;
    using TransformedType           = std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>>;

    NS::AnnotationMapsPtr const     pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    TSImputerEstimator              estimator(pAllColumnAnnotations, {NS::DataTypes::Float64});

    typename InputBatchesType::const_iterator            iter(trainingBatches.begin());
    while(true) {
        FitResult const                     result(estimator.fit(iter->data(), iter->size()));
        if(result == FitResult::Complete)
            break;
        ++iter;
        if(iter == trainingBatches.end()) {
            FitResult const                 completeResult(estimator.complete_training());
            if(completeResult != FitResult::Complete)
                throw std::runtime_error("Unexpected fit result");
            break;
        }
    }

    assert(estimator.is_training_complete());

    TSImputerEstimator::TransformerUniquePtr                  pTransformer(estimator.create_transformer());
    TransformedType   	  output;

    for(auto const &item : inferenceBatches)
    {
        auto a = pTransformer->execute(item);
        output.insert(output.end(), a.begin(), a.end());
    }

    return output;
}

TEST_CASE("Interface-Test") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                        std::make_tuple(false,GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5"}),
                        std::make_tuple(false,GetTimePoint(now,-3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}}),
                        std::make_tuple(false,GetTimePoint(now,-2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5"}),
                        std::make_tuple(GetTimePoint(now,-3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,-2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0"})
                    }
                },
                {
                        std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5"}),
                        std::make_tuple(GetTimePoint(now,-3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,-2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0"})
                }) == output);
    }

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
