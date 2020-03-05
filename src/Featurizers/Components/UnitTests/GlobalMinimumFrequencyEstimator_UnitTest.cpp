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


TEST_CASE("GlobalMinimumFrequencyEstimator - one grain without gap") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::tuple<std::string,std::chrono::system_clock::time_point>;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::GlobalMinimumFrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{std::make_tuple("one",AddDays(now, 0)),
                                                                            std::make_tuple("one",AddDays(now, 1)),
                                                                            std::make_tuple("one",AddDays(now, 2))}}));
    NS::Featurizers::Components::GlobalMinimumFrequencyAnnotation const& frequency(estimator.get_annotation_data());

    CHECK(frequency.Value == std::chrono::minutes(60 * 24));
}

TEST_CASE("GlobalMinimumFrequencyEstimator - one grain with gap") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::tuple<std::string,std::chrono::system_clock::time_point>;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::GlobalMinimumFrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{std::make_tuple("one",AddDays(now, 0)),
                                                                            std::make_tuple("one",AddDays(now, 1)),
                                                                            std::make_tuple("one",AddDays(now, 3))}}));
    NS::Featurizers::Components::GlobalMinimumFrequencyAnnotation const& frequency(estimator.get_annotation_data());

    CHECK(frequency.Value == std::chrono::minutes(60 * 24));
}

TEST_CASE("GlobalMinimumFrequencyEstimator - two grains with different frequencies") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::tuple<std::string,std::chrono::system_clock::time_point>;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::GlobalMinimumFrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{std::make_tuple("one",AddDays(now, 0)),
                                                                            std::make_tuple("one",AddDays(now, 1)),
                                                                            std::make_tuple("one",AddDays(now, 2)),
                                                                            std::make_tuple("two",AddDays(now, 0)),
                                                                            std::make_tuple("two",AddDays(now, 2)),
                                                                            std::make_tuple("two",AddDays(now, 4))}}));
    NS::Featurizers::Components::GlobalMinimumFrequencyAnnotation const& frequency(estimator.get_annotation_data());

    CHECK(frequency.Value == std::chrono::minutes(60 * 24));
}

TEST_CASE("GlobalMinimumFrequencyEstimator - two grains with mixed frequencies") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::tuple<std::string,std::chrono::system_clock::time_point>;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::GlobalMinimumFrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{std::make_tuple("one",AddMinutes(now, 0)),
                                                                            std::make_tuple("one",AddMinutes(now, 1)),
                                                                            std::make_tuple("one",AddDays(now, 2)),
                                                                            std::make_tuple("two",AddDays(now, 0)),
                                                                            std::make_tuple("two",AddDays(now, 2)),
                                                                            std::make_tuple("two",AddDays(now, 4))}}));
    NS::Featurizers::Components::GlobalMinimumFrequencyAnnotation const& frequency(estimator.get_annotation_data());

    CHECK(frequency.Value == std::chrono::minutes(1));
}

TEST_CASE("GlobalMinimumFrequencyEstimator - Not in chronological order") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::tuple<std::string,std::chrono::system_clock::time_point>;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::GlobalMinimumFrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    CHECK_THROWS_WITH(NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{std::make_tuple("one",AddMinutes(now, 0)),
                                                                                              std::make_tuple("one",AddDays(now, 1)),
                                                                                              std::make_tuple("one",AddMinutes(now, 2)),
                                                                                              std::make_tuple("two",AddDays(now, 0)),
                                                                                              std::make_tuple("two",AddMinutes(now, 2)),
                                                                                              std::make_tuple("two",AddDays(now, 4))}})),
                                                                                              "Input stream not in chronological order.");
}
