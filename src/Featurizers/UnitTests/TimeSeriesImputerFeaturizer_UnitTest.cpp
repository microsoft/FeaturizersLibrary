// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#include "../../Traits.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Components/TimeSeriesImputerTransformer.h"
#include "../TimeSeriesImputerFeaturizer.h"
#include "../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunused-local-typedef"
#endif

std::chrono::system_clock::time_point GetTimePoint(std::chrono::system_clock::time_point tp, int unitsToAdd, std::string = "days"){
    return tp + std::chrono::minutes(unitsToAdd * (60*24));
}

using InputType = std::tuple<
    std::chrono::system_clock::time_point,
    std::vector<std::string>,
    std::vector<nonstd::optional<std::string>>
>;

using TransformedType = std::vector<
    std::tuple<
        bool,
        std::chrono::system_clock::time_point,
        std::vector<std::string>,
        std::vector<nonstd::optional<std::string>>
    >
>;

TransformedType Test(std::vector<std::vector<InputType>> const &trainingBatches, std::vector<InputType> const &inferenceBatches
,std::vector<NS::TypeId> colsToImputeDataTypes, bool supressError, NS::Featurizers::Components::TimeSeriesImputeStrategy tsImputeStrategy) {
    using KeyT                      = std::vector<std::string>;
    using ColsToImputeT             = std::vector<nonstd::optional<std::string>>;
    using InputBatchesType          = std::vector<std::vector<InputType>>;
    using TSImputerEstimator        = NS::Featurizers::TimeSeriesImputerEstimator;

    NS::AnnotationMapsPtr const     pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    TSImputerEstimator              estimator(pAllColumnAnnotations,colsToImputeDataTypes,supressError,tsImputeStrategy);

    NS::TestHelpers::Train<TSImputerEstimator, InputType>(estimator, trainingBatches);
    TSImputerEstimator::TransformerUniquePtr                  pTransformer(estimator.create_transformer());
    TransformedType   	  output;
    auto const              callback(
        [&output](typename TransformedType::value_type value) {
            output.emplace_back(std::move(value));
        }
    );

    for(auto const &item : inferenceBatches)
        pTransformer->execute(item, callback);

    pTransformer->flush(callback);

    return output;
}

TEST_CASE("RowImputation: 1 grain, No Gaps") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                        std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","12"}),
                        std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0","12"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0",nonstd::optional<std::string>{}})
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0",nonstd::optional<std::string>{}})

                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
    }

TEST_CASE("RowImputation: 1 grain, 1 Gap") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                        std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(true,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0","18"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0",nonstd::optional<std::string>{}})

                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
    }

TEST_CASE("RowImputation: 1 grain, 2 Gaps") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                        std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(true,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(true,GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(false,GetTimePoint(now,3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","15.0"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"15.0"})

                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
    }

TEST_CASE("RowImputation: 2 grains, No Gaps (input interleaved)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,5), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","12"}),
                    std::make_tuple(false,GetTimePoint(now,6), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","112"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,5), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                        std::make_tuple(GetTimePoint(now,6), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,5), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                    std::make_tuple(GetTimePoint(now,6), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"112"}),

                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
    }

TEST_CASE("RowImputation: 2 grains, 1 Gap (input interleaved)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,5), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(true,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","12"}),
                    std::make_tuple(true,GetTimePoint(now,6), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(false,GetTimePoint(now,7), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","112"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,5), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                        std::make_tuple(GetTimePoint(now,6), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,5), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                    std::make_tuple(GetTimePoint(now,7), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"112"}),

                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
    }

TEST_CASE("RowImputation: 2 grains, 2 Gaps (input interleaved)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,5), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(true,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(true,GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","12"}),
                    std::make_tuple(true,GetTimePoint(now,6), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(true,GetTimePoint(now,7), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(false,GetTimePoint(now,8), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","112"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,5), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                        std::make_tuple(GetTimePoint(now,6), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,5), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(GetTimePoint(now,3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                    std::make_tuple(GetTimePoint(now,8), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"112"}),

                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
    }

TEST_CASE("ColumnImputation (ffill): 1 grain (ValidRow, EmptyRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
    }

TEST_CASE("ColumnImputation (ffill): 1 grain (ValidRow, EmptyRow,EmptyRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
    }

TEST_CASE("ColumnImputation (ffill): 1 grain (EmptyRow, ValidRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
    }

TEST_CASE("ColumnImputation (ffill): 1 grain (EmptyRow,EmptyRow,ValidRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                };
    CHECK(Test({
                    {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
    }

TEST_CASE("ColumnImputation (ffill): 2 grains (ValidRow, EmptyRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})

                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
    }

TEST_CASE("ColumnImputation (ffill): 2 grains (ValidRow, EmptyRow, EmptyRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})

                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
    }

TEST_CASE("ColumnImputation (bfill): 1 grain (ValidRow, EmptyRow, ValidRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"}),
                    std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"})
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Backward) == output);
    }

TEST_CASE("ColumnImputation (bfill): 1 grain (ValidRow, EmptyRow, EmptyRow, ValidRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"}),
                    std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"}),
                    std::make_tuple(false,GetTimePoint(now,3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"})
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Backward) == output);
    }

TEST_CASE("ColumnImputation (bfill): 1 grain (EmptyRow, ValidRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Backward) == output);
    }

TEST_CASE("ColumnImputation (bfill): 1 grain (EmptyRow,EmptyRow,ValidRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                };
    CHECK(Test({
                    {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Backward) == output);
    }

TEST_CASE("ColumnImputation (bfill): 2 grains (ValidRow, EmptyRow, ValidRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"120.5","130.5"}),
                    std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"120.5","130.5"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"}),
                    std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"120.5","130.5"}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"})

                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"120.5","130.5"}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Backward) == output);
    }

TEST_CASE("ColumnImputation (bfill): 2 grains (ValidRow, EmptyRow, EmptyRow, ValidRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"120.5","130.5"}),
                    std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"120.5","130.5"}),
                    std::make_tuple(false,GetTimePoint(now,3), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"120.5","130.5"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"}),
                    std::make_tuple(false,GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"}),
                    std::make_tuple(false,GetTimePoint(now,3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,3), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"120.5","130.5"}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"})
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,3), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"120.5","130.5"}),
                    std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"20.5","30.5"})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Backward) == output);
    }

TEST_CASE("ColumnImputation (Median): 1 grain (EmptyRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.500000","50.000000"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"82"}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"16.5",nonstd::optional<std::string>{}}),
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Median) == output);
    }

TEST_CASE("ColumnImputation (Median): 1 grain (EmptyRow, EmptyRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.500000","50.000000"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.500000","50.000000"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"82"}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"16.5",nonstd::optional<std::string>{}}),
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Median) == output);
    }

TEST_CASE("ColumnImputation (Median): 2 grains (EmptyRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.500000","50.000000"}),
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.500000","150.000000"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"82"}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"16.5",nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"182"}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"116.5",nonstd::optional<std::string>{}}),
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Median) == output);
    }

TEST_CASE("ColumnImputation (Median): 2 grains (EmptyRow, EmptyRow)") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.500000","50.000000"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.500000","50.000000"}),
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.500000","150.000000"}),
                    std::make_tuple(false,GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.500000","150.000000"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"82"}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"16.5",nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"182"}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"116.5",nonstd::optional<std::string>{}}),
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Median) == output);
    }

TEST_CASE("Suppress Error: Median on unsupported column types") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    CHECK_THROWS_WITH(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","def"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"abc"}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"16.5",nonstd::optional<std::string>{}}),
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                },{NS::TypeId::Float64,NS::TypeId::String}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Median)
                , Catch::Contains("Only Numeric type columns are supported for ImputationStrategy median. (use suppressError flag to skip imputing non-numeric types)"));
    }

TEST_CASE("Suppress Error: Median on unsupported column types with suppress error flag turned on") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.500000",nonstd::optional<std::string>{}})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","def"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"abc"}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"16.5",nonstd::optional<std::string>{}}),
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                },{NS::TypeId::Float64,NS::TypeId::String}, true, NS::Featurizers::Components::TimeSeriesImputeStrategy::Median) == output);
    }

TEST_CASE("Suppress Error: Median on unrecognized grain") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    CHECK_THROWS_WITH(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","12"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"82"}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"16.5",nonstd::optional<std::string>{}}),
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Median)
                , Catch::Contains("Invalid key"));
    }

TEST_CASE("Suppress Error: Median on unrecognized grain with suppress error flag turned on") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","def"}),
                        std::make_tuple(GetTimePoint(now,1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"abc"}),
                        std::make_tuple(GetTimePoint(now,2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"16.5",nonstd::optional<std::string>{}}),
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,0), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},nonstd::optional<std::string>{}})
                },{NS::TypeId::Float64,NS::TypeId::String}, true, NS::Featurizers::Components::TimeSeriesImputeStrategy::Median) == output);
    }

TEST_CASE("FFill- Add Rows and Impute") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                        std::make_tuple(false,GetTimePoint(now,-6), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18.8"}),
                        std::make_tuple(false,GetTimePoint(now,-6), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118.8"}),
                        std::make_tuple(true,GetTimePoint(now,-5), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118.8"}),
                        std::make_tuple(false,GetTimePoint(now,-4), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","120.5"}),
                        std::make_tuple(true,GetTimePoint(now,-5), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18.8"}),
                        std::make_tuple(false,GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","20.5"}),
                        std::make_tuple(false,GetTimePoint(now,-3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","20.5"}),
                        std::make_tuple(false,GetTimePoint(now,-3), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","120.5"}),
                        std::make_tuple(true,GetTimePoint(now,-2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","120.5"}),
                        std::make_tuple(false,GetTimePoint(now,-1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.0", "120.5"}),
                        std::make_tuple(true,GetTimePoint(now,-2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","20.5"}),
                        std::make_tuple(false,GetTimePoint(now,-1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0", "20.5"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,-8), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                        std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"112"}),
                        std::make_tuple(GetTimePoint(now,-3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                        std::make_tuple(GetTimePoint(now,-2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0",nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,-2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.0",nonstd::optional<std::string>{}})
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,-6), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5", "18.8"}),
                    std::make_tuple(GetTimePoint(now,-6), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5", "118.8"}),
                    std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}, "120.5"}),
                    std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}, "20.5"}),
                    std::make_tuple(GetTimePoint(now,-3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}, nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,-3), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}, nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,-1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.0",nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,-1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0",nonstd::optional<std::string>{}})

                },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
    }

TEST_CASE("BFill- Add Rows and Impute") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
                    std::make_tuple(false,GetTimePoint(now,-6), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","120.5"}),
                    std::make_tuple(false,GetTimePoint(now,-6), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","20.5"}),
                    std::make_tuple(true,GetTimePoint(now,-5), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.0","120.5"}),
                    std::make_tuple(false,GetTimePoint(now,-4), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.0","120.5"}),
                    std::make_tuple(false,GetTimePoint(now,-3), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.0","118.8"}),
                    std::make_tuple(true,GetTimePoint(now,-2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.0", "118.8"}),
                    std::make_tuple(false,GetTimePoint(now,-1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.0", "118.8"}),
                    std::make_tuple(true,GetTimePoint(now,-5), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0","20.5"}),
                    std::make_tuple(false,GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0","20.5"}),
                    std::make_tuple(false,GetTimePoint(now,-3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0","18.8"}),
                    std::make_tuple(true,GetTimePoint(now,-2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0", "18.8"}),
                    std::make_tuple(false,GetTimePoint(now,-1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0", "18.8"})
                };
    CHECK(Test({
                    {
                        std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,-8), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                        std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                        std::make_tuple(GetTimePoint(now,-3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                        std::make_tuple(GetTimePoint(now,-2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0",nonstd::optional<std::string>{}}),
                        std::make_tuple(GetTimePoint(now,-2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"15.0",nonstd::optional<std::string>{}})
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,-6), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5", nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,-6), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5", nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}, "120.5"}),
                    std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}, "20.5"}),
                    std::make_tuple(GetTimePoint(now,-3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}, nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,-3), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}, nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,-1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.0","118.8"}),
                    std::make_tuple(GetTimePoint(now,-1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0","18.8"})
               },{NS::TypeId::Float64,NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Backward) == output);
    }


TEST_CASE("MedianFill- Add Rows and Impute") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>>
        expected_output = {
                std::make_tuple(false,GetTimePoint(now,-6), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","15.000000"}),
                std::make_tuple(false,GetTimePoint(now,-6), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","115.000000"}),
                std::make_tuple(true,GetTimePoint(now,-5), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.750000","115.000000"}),
                std::make_tuple(false,GetTimePoint(now,-4), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.750000","120.5"}),
                std::make_tuple(true,GetTimePoint(now,-5), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.750000","15.000000"}),
                std::make_tuple(false,GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.750000","20.5"}),
                std::make_tuple(false,GetTimePoint(now,-3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.750000","15.000000"}),
                std::make_tuple(false,GetTimePoint(now,-3), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.750000","115.000000"}),
                std::make_tuple(true,GetTimePoint(now,-2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.750000", "115.000000"}),
                std::make_tuple(false,GetTimePoint(now,-1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.0", "118.8"}),
                std::make_tuple(true,GetTimePoint(now,-2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.750000", "15.000000"}),
                std::make_tuple(false,GetTimePoint(now,-1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0", "18.8"})
        };

    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>>
        actual_output = Test(
            {
                {
                    std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"}),
                    std::make_tuple(GetTimePoint(now,-3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"12"}),
                    std::make_tuple(GetTimePoint(now,-2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0",nonstd::optional<std::string>{}}),
                    std::make_tuple(GetTimePoint(now,-8), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5","118"}),
                    std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{},"112"}),
                    std::make_tuple(GetTimePoint(now,-2), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.0",nonstd::optional<std::string>{}})
                }
            },
            {
                std::make_tuple(GetTimePoint(now,-6), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5", nonstd::optional<std::string>{}}),
                std::make_tuple(GetTimePoint(now,-6), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"114.5", nonstd::optional<std::string>{}}),
                std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}, "120.5"}),
                std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}, "20.5"}),
                std::make_tuple(GetTimePoint(now,-3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}, nonstd::optional<std::string>{}}),
                std::make_tuple(GetTimePoint(now,-3), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>{}, nonstd::optional<std::string>{}}),
                std::make_tuple(GetTimePoint(now,-1), std::vector<std::string>{"b"}, std::vector<nonstd::optional<std::string>>{"115.0","118.8"}),
                std::make_tuple(GetTimePoint(now,-1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"15.0","18.8"})
            },
            {NS::TypeId::Float64, NS::TypeId::Float64},
            true,
            NS::Featurizers::Components::TimeSeriesImputeStrategy::Median
        );

    CHECK(actual_output == expected_output);
}

TEST_CASE("One Row input") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    CHECK_THROWS_WITH(Test({
                    {
                        std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                    }
                },
                {
                    std::make_tuple(GetTimePoint(now,-4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"14.5","18"})
                },{NS::TypeId::Float64, NS::TypeId::String}, true, NS::Featurizers::Components::TimeSeriesImputeStrategy::Median)
                , Catch::Contains("Frequency couldn't be inferred from training data."));
    }


    TEST_CASE("SerDe") {

    using transformerType = NS::Featurizers::Components::TimeSeriesImputerEstimator::Transformer;

    auto model = new transformerType(
            []()->std::chrono::system_clock::duration {
                std::chrono::system_clock::duration frequency;
                std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
                std::chrono::system_clock::time_point foo = now + std::chrono::minutes(24*60);
                frequency = (foo - now);
                return frequency;
            }(),
            std::vector<NS::TypeId>{NS::TypeId::Float64,NS::TypeId::Float64},
            NS::Featurizers::Components::TimeSeriesImputeStrategy::Median,
            true,
            std::map<std::vector<std::string>,std::vector<double>>{
                {{"a"},{14.75,15.0}},
                {{"b"},{114.75,115.0}}
            }
        );

    //Serialize
    NS::Archive archive;
    model->save(archive);
    std::vector<unsigned char> vec = archive.commit();

    //Deserialize
    NS::Archive loader(vec);
    transformerType modelLoaded(loader);

    //Validate post deserialization
    CHECK(std::chrono::duration_cast<std::chrono::hours>(modelLoaded._frequency).count() == 24);
    CHECK(modelLoaded._colsToImputeDataTypes == std::vector<NS::TypeId>{NS::TypeId::Float64,NS::TypeId::Float64});
    CHECK(modelLoaded._supressError == true);
    CHECK(modelLoaded._tsImputeStrategy == NS::Featurizers::Components::TimeSeriesImputeStrategy::Median);
    CHECK(modelLoaded._medianValues == std::map<std::vector<std::string>,std::vector<double>>{
                {{"a"},{14.75,15.0}},
                {{"b"},{114.75,115.0}}
            });
    }

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

TEST_CASE("SimpleMedianTest") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>>
        expected_output =
            {
                std::make_tuple(false, GetTimePoint(now, 0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000"}),
                std::make_tuple(false, GetTimePoint(now, 1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000"}),
                std::make_tuple(true, GetTimePoint(now, 2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000"}),
                std::make_tuple(false, GetTimePoint(now, 3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000"}),
                std::make_tuple(true, GetTimePoint(now, 4), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000"}),
                std::make_tuple(false, GetTimePoint(now, 5), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000"}),
                std::make_tuple(true, GetTimePoint(now, 6), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000"}),
                std::make_tuple(false, GetTimePoint(now, 7), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000"})
            };

    auto actual_output =
        Test(
            {
                {
                    std::make_tuple(GetTimePoint(now, 0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000"}),
                    std::make_tuple(GetTimePoint(now, 1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>()}),
                    std::make_tuple(GetTimePoint(now, 3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000"}),
                    std::make_tuple(GetTimePoint(now, 5), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>()}),
                    std::make_tuple(GetTimePoint(now, 7), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>()})
                }
            },
            {
                {
                    std::make_tuple(GetTimePoint(now, 0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000"}),
                    std::make_tuple(GetTimePoint(now, 1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>()}),
                    std::make_tuple(GetTimePoint(now, 3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000"}),
                    std::make_tuple(GetTimePoint(now, 5), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>()}),
                    std::make_tuple(GetTimePoint(now, 7), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>()})
                }
            },
            {NS::TypeId::Float64},
            true,
            NS::Featurizers::Components::TimeSeriesImputeStrategy::Median
        );

    CHECK(actual_output == expected_output);
}

TEST_CASE("Median Test - suppress error") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>>
        expected_output =
            {
                std::make_tuple(false, GetTimePoint(now, 0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000",nonstd::optional<std::string>()}),
                std::make_tuple(false, GetTimePoint(now, 1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000",nonstd::optional<std::string>()}),
                std::make_tuple(true, GetTimePoint(now, 2), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000",nonstd::optional<std::string>()}),
                std::make_tuple(false, GetTimePoint(now, 3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000","abc"})
            };
    auto actual_output =
        Test(
            {
                {
                    std::make_tuple(GetTimePoint(now, 0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000",nonstd::optional<std::string>()}),
                    std::make_tuple(GetTimePoint(now, 1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>(),nonstd::optional<std::string>()}),
                    std::make_tuple(GetTimePoint(now, 3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000", "abc"})
                }
            },
            {
                {
                    std::make_tuple(GetTimePoint(now, 0), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000",nonstd::optional<std::string>()}),
                    std::make_tuple(GetTimePoint(now, 1), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{nonstd::optional<std::string>(),nonstd::optional<std::string>()}),
                    std::make_tuple(GetTimePoint(now, 3), std::vector<std::string>{"a"}, std::vector<nonstd::optional<std::string>>{"2.000000", "abc"})
                }
            },
            {NS::TypeId::Float64, NS::TypeId::String},
            true,
            NS::Featurizers::Components::TimeSeriesImputeStrategy::Median
        );

    CHECK(actual_output == expected_output);
}
