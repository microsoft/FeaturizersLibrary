// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../TestHelpers.h"
#include "../GlobalMinimumFrequencyEstimator.h"

namespace NS = Microsoft::Featurizer;

std::chrono::system_clock::time_point AddDays(std::chrono::system_clock::time_point tp, int daysToAdd){
    return tp + std::chrono::minutes(daysToAdd * (60 * 24));
}

std::chrono::system_clock::time_point AddMinutes(std::chrono::system_clock::time_point tp, int minutesToAdd){
    return tp + std::chrono::minutes(minutesToAdd);
}

template <typename T>
typename NS::Featurizers::Components::GlobalMinimumFrequencyAnnotation::FrequencyType Test(std::vector<T> const &input) {
    std::vector<std::vector<T>> const       batchedInput(NS::TestHelpers::make_vector<std::vector<T>>(input));
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    // GlobalMinimumFrequencyEstimator requires GrainedFrequencyEstimator annotation
    NS::Featurizers::Components::GlobalMinimumFrequencyEstimator<>   tempGlobalMinimumFrequencyEstimator(pAllColumnAnnotations, 0);

    CHECK_THROWS_WITH(NS::TestHelpers::Train(tempGlobalMinimumFrequencyEstimator, batchedInput), "Annotation data was not found for this column");

    // Standard tests
    NS::Featurizers::Components::GrainedFrequencyEstimator<>       grainedFrequencyEstimator(NS::Featurizers::Components::GrainedFrequencyEstimatorName,
                                                                                             pAllColumnAnnotations, 
                                                                                             [](NS::AnnotationMapsPtr pAllColumnAnnotationsParam) {
                                                                                                 return NS::Featurizers::Components::FrequencyEstimator<>(std::move(pAllColumnAnnotationsParam), 0);
                                                                                             });
    NS::Featurizers::Components::GlobalMinimumFrequencyEstimator<> globalMinimumFrequencyEstimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(grainedFrequencyEstimator, batchedInput);
    NS::TestHelpers::Train(globalMinimumFrequencyEstimator, batchedInput);

    return globalMinimumFrequencyEstimator.get_annotation_data().Value;
}

using inputType = std::tuple<std::vector<std::string> const &, std::chrono::system_clock::time_point const &>;

TEST_CASE("GlobalMinimumFrequencyEstimator - one grain without gap") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    const std::vector<std::string> grain({"one"});
    const std::chrono::system_clock::time_point tp1 (AddDays(now, 0));
    const std::chrono::system_clock::time_point tp2 (AddDays(now, 1));
    const std::chrono::system_clock::time_point tp3 (AddDays(now, 2));

    const auto tup1 = std::make_tuple(grain, tp1);
    const auto tup2 = std::make_tuple(grain, tp2);
    const auto tup3 = std::make_tuple(grain, tp3);

    const std::vector<inputType> input = {tup1, tup2, tup3};

    CHECK(Test(input) == std::chrono::minutes(60 * 24));
}

TEST_CASE("GlobalMinimumFrequencyEstimator - one grain with gap") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    const std::vector<std::string> grain({"one"});
    const std::chrono::system_clock::time_point tp1 (AddDays(now, 0));
    const std::chrono::system_clock::time_point tp2 (AddDays(now, 1));
    const std::chrono::system_clock::time_point tp3 (AddDays(now, 3));

    const auto tup1 = std::make_tuple(grain, tp1);
    const auto tup2 = std::make_tuple(grain, tp2);
    const auto tup3 = std::make_tuple(grain, tp3);

    const std::vector<inputType> input = {tup1, tup2, tup3};

    CHECK(Test(input) == std::chrono::minutes(60 * 24));                       
}

TEST_CASE("GlobalMinimumFrequencyEstimator - two grains with different frequencies") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    const std::vector<std::string> grain1({"one"});
    const std::vector<std::string> grain2({"two"});

    const std::chrono::system_clock::time_point tp1 (AddDays(now, 0));
    const std::chrono::system_clock::time_point tp2 (AddDays(now, 1));
    const std::chrono::system_clock::time_point tp3 (AddDays(now, 2));
    const std::chrono::system_clock::time_point tp4 (AddDays(now, 4));

    const auto grain1Tup1 = std::make_tuple(grain1, tp1);
    const auto grain1Tup2 = std::make_tuple(grain1, tp2);
    const auto grain1Tup3 = std::make_tuple(grain1, tp3);
    const auto grain2Tup1 = std::make_tuple(grain2, tp1);
    const auto grain2Tup2 = std::make_tuple(grain2, tp3);
    const auto grain2Tup3 = std::make_tuple(grain2, tp4);

    const std::vector<inputType> input = {grain1Tup1, grain1Tup2, grain1Tup3, grain2Tup1, grain2Tup2, grain2Tup3};

    CHECK(Test(input) == std::chrono::minutes(60 * 24));   
}

TEST_CASE("GlobalMinimumFrequencyEstimator - two grains with mixed frequencies") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    const std::vector<std::string> grain1({"one"});
    const std::vector<std::string> grain2({"two"});

    const std::chrono::system_clock::time_point tp1 (AddMinutes(now, 0));
    const std::chrono::system_clock::time_point tp2 (AddMinutes(now, 1));
    const std::chrono::system_clock::time_point tp3 (AddDays(now, 2));
    const std::chrono::system_clock::time_point tp4 (AddDays(now, 0));
    const std::chrono::system_clock::time_point tp5 (AddDays(now, 2));
    const std::chrono::system_clock::time_point tp6 (AddDays(now, 4));

    const auto grain1Tup1 = std::make_tuple(grain1, tp1);
    const auto grain1Tup2 = std::make_tuple(grain1, tp2);
    const auto grain1Tup3 = std::make_tuple(grain1, tp3);
    const auto grain2Tup1 = std::make_tuple(grain2, tp4);
    const auto grain2Tup2 = std::make_tuple(grain2, tp5);
    const auto grain2Tup3 = std::make_tuple(grain2, tp6);

    const std::vector<inputType> input = {grain1Tup1, grain1Tup2, grain1Tup3, grain2Tup1, grain2Tup2, grain2Tup3};

    CHECK(Test(input) == std::chrono::minutes(1));   
}

TEST_CASE("GlobalMinimumFrequencyEstimator - two vector of string grains") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    const std::vector<std::string> grain1({"one", "two"});
    const std::vector<std::string> grain2({"two", "three"});

    const std::chrono::system_clock::time_point tp1 (AddMinutes(now, 0));
    const std::chrono::system_clock::time_point tp2 (AddMinutes(now, 1));
    const std::chrono::system_clock::time_point tp3 (AddDays(now, 2));
    const std::chrono::system_clock::time_point tp4 (AddDays(now, 0));
    const std::chrono::system_clock::time_point tp5 (AddDays(now, 2));
    const std::chrono::system_clock::time_point tp6 (AddDays(now, 4));

    const auto grain1Tup1 = std::make_tuple(grain1, tp1);
    const auto grain1Tup2 = std::make_tuple(grain1, tp2);
    const auto grain1Tup3 = std::make_tuple(grain1, tp3);
    const auto grain2Tup1 = std::make_tuple(grain2, tp4);
    const auto grain2Tup2 = std::make_tuple(grain2, tp5);
    const auto grain2Tup3 = std::make_tuple(grain2, tp6);

    const std::vector<inputType> input = {grain1Tup1, grain1Tup2, grain1Tup3, grain2Tup1, grain2Tup2, grain2Tup3};

    CHECK(Test(input) == std::chrono::minutes(1));   
}

TEST_CASE("GlobalMinimumFrequencyEstimator - Not in chronological order") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    const std::vector<std::string> grain({"one"});
    const std::chrono::system_clock::time_point tp1 (AddDays(now, 0));
    const std::chrono::system_clock::time_point tp2 (AddDays(now, 2));
    const std::chrono::system_clock::time_point tp3 (AddDays(now, 1));

    const auto tup1 = std::make_tuple(grain, tp1);
    const auto tup2 = std::make_tuple(grain, tp2);
    const auto tup3 = std::make_tuple(grain, tp3);

    const std::vector<inputType> input = {tup1, tup2, tup3};

    CHECK_THROWS_WITH(Test(input), "Input stream not in chronological order.");
}

TEST_CASE("GlobalMinimumFrequencyEstimator - Not enough rows") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    const std::vector<std::string> grain({"one"});
    const std::chrono::system_clock::time_point tp1 (AddDays(now, 0));

    const auto tup1 = std::make_tuple(grain, tp1);

    const std::vector<inputType> input = {tup1};

    CHECK_THROWS_WITH(Test(input), "Need to provide more than one value to get a frequency");
    
}
