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
    using FitResult                 = NS::Estimator::FitResult;
    using KeyT                      = std::vector<std::string>;
    using ColsToImputeT             = std::vector<nonstd::optional<std::string>>;
    using InputBatchesType          = std::vector<std::vector<InputType>>;
    using TSImputerEstimator        = NS::Featurizers::TimeSeriesImputerEstimator;

    NS::AnnotationMapsPtr const     pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    TSImputerEstimator              estimator(pAllColumnAnnotations,colsToImputeDataTypes,supressError,tsImputeStrategy);
    

    typename InputBatchesType::const_iterator            iter(trainingBatches.begin());
    while(true) {
        FitResult const                     result(estimator.fit(iter->data(), iter->size()));
        if(result == FitResult::Complete)
            break;
        ++iter;

        if(iter == trainingBatches.end()) {
            if(estimator.complete_training() == FitResult::Complete)
                break;

            iter = trainingBatches.begin();
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

//TODO: Add tests for more atomic scenarios. For eg.
// Validate rows inserted for forward fill
// Validate rows inserted for backward fill
// Validate ffill col mputation
// Validate bfill col imputation
// Validate median col imputation


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

                },{NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Forward) == output);
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
               },{NS::TypeId::Float64}, false, NS::Featurizers::Components::TimeSeriesImputeStrategy::Backward) == output);
    }


TEST_CASE("MedianFill- Add Rows and Impute") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::vector<std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>> output = {
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
    CHECK(Test({
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
                },{NS::TypeId::Float64, NS::TypeId::String}, true, NS::Featurizers::Components::TimeSeriesImputeStrategy::Median) == output);
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

    auto model = std::make_unique<transformerType>(
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
