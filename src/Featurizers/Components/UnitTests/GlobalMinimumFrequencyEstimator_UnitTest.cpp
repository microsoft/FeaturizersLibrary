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


TEST_CASE("GlobalMinimumFrequencyEstimator - one grain without gap") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::tuple<std::vector<std::string>,std::chrono::system_clock::time_point>;

    std::vector<std::string> grain({"one"});

    CHECK(Test<inputType>({std::make_tuple(grain,AddDays(now, 0)),
                           std::make_tuple(grain,AddDays(now, 1)),
                           std::make_tuple(grain,AddDays(now, 2))}) == std::chrono::minutes(60 * 24));
}

TEST_CASE("GlobalMinimumFrequencyEstimator - one grain with gap") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::tuple<std::vector<std::string>,std::chrono::system_clock::time_point>;
    
    std::vector<std::string> grain({"one"});

    CHECK(Test<inputType>({std::make_tuple(grain,AddDays(now, 0)),
                           std::make_tuple(grain,AddDays(now, 1)),
                           std::make_tuple(grain,AddDays(now, 3))}) == std::chrono::minutes(60 * 24));
}

TEST_CASE("GlobalMinimumFrequencyEstimator - two grains with different frequencies") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::tuple<std::vector<std::string>,std::chrono::system_clock::time_point>;
    
    std::vector<std::string> grain1({"one"});
    std::vector<std::string> grain2({"two"});

    CHECK(Test<inputType>({std::make_tuple(grain1,AddDays(now, 0)),
                           std::make_tuple(grain1,AddDays(now, 1)),
                           std::make_tuple(grain1,AddDays(now, 2)),
                           std::make_tuple(grain2,AddDays(now, 0)),
                           std::make_tuple(grain2,AddDays(now, 2)),
                           std::make_tuple(grain2,AddDays(now, 4))}) == std::chrono::minutes(60 * 24));
}

TEST_CASE("GlobalMinimumFrequencyEstimator - two grains with mixed frequencies") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::tuple<std::vector<std::string>,std::chrono::system_clock::time_point>;
    
    std::vector<std::string> grain1({"one"});
    std::vector<std::string> grain2({"two"});

    CHECK(Test<inputType>({std::make_tuple(grain1,AddMinutes(now, 0)),
                           std::make_tuple(grain1,AddMinutes(now, 1)),
                           std::make_tuple(grain1,AddDays(now, 2)),
                           std::make_tuple(grain2,AddDays(now, 0)),
                           std::make_tuple(grain2,AddDays(now, 2)),
                           std::make_tuple(grain2,AddDays(now, 4))}) == std::chrono::minutes(1));
}

TEST_CASE("GlobalMinimumFrequencyEstimator - two vector of string grains") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::tuple<std::vector<std::string>,std::chrono::system_clock::time_point>;
    
    std::vector<std::string> grain1({"one", "two"});
    std::vector<std::string> grain2({"one", "three"});

    CHECK(Test<inputType>({std::make_tuple(grain1,AddMinutes(now, 0)),
                           std::make_tuple(grain1,AddMinutes(now, 1)),
                           std::make_tuple(grain1,AddDays(now, 2)),
                           std::make_tuple(grain2,AddDays(now, 0)),
                           std::make_tuple(grain2,AddDays(now, 2)),
                           std::make_tuple(grain2,AddDays(now, 4))}) == std::chrono::minutes(1));
}

TEST_CASE("GlobalMinimumFrequencyEstimator - Not in chronological order") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::tuple<std::vector<std::string>,std::chrono::system_clock::time_point>;
    
    std::vector<std::string> grain1({"one"});
    std::vector<std::string> grain2({"two"});

    CHECK_THROWS_WITH(Test<inputType>({std::make_tuple(grain1,AddMinutes(now, 0)),
                           std::make_tuple(grain1,AddDays(now, 1)),
                           std::make_tuple(grain1,AddMinutes(now, 2)),
                           std::make_tuple(grain2,AddDays(now, 0)),
                           std::make_tuple(grain2,AddMinutes(now, 2)),
                           std::make_tuple(grain2,AddDays(now, 4))}), "Input stream not in chronological order.");
}

TEST_CASE("GlobalMinimumFrequencyEstimator - Not enough rows") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::tuple<std::vector<std::string>,std::chrono::system_clock::time_point>;
    
    std::vector<std::string> grain1({"one"});

    CHECK_THROWS_WITH(Test<inputType>({std::make_tuple(grain1,AddMinutes(now, 0))}), "Need to provide more than one value to get a frequency");
}
