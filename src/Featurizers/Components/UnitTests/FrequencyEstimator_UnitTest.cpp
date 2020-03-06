// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../TestHelpers.h"
#include "../FrequencyEstimator.h"

namespace NS = Microsoft::Featurizer;

std::chrono::system_clock::time_point AddDays(std::chrono::system_clock::time_point tp, int daysToAdd){
    return tp + std::chrono::minutes(daysToAdd * (60 * 24));
}

std::chrono::system_clock::time_point AddMinutes(std::chrono::system_clock::time_point tp, int minutesToAdd){
    return tp + std::chrono::minutes(minutesToAdd);
}

TEST_CASE("FrequencyEstimator - 1 Day Frequency") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::chrono::system_clock::time_point;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::FrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{AddDays(now, 0),
                                                                            AddDays(now, 1),
                                                                            AddDays(now, 2)}}));
    NS::Featurizers::Components::FrequencyAnnotation const& frequency(estimator.get_annotation_data());
    
    CHECK(frequency.Value == std::chrono::minutes(60 * 24));
}

TEST_CASE("FrequencyEstimator - 1 Day Frequency with gap") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::chrono::system_clock::time_point;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::FrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    // Should still have a frequency of 1 day even though there is a 2 day gap from 0 to 2
    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{AddDays(now, 0),
                                                                            AddDays(now, 2),
                                                                            AddDays(now, 3)}}));
    NS::Featurizers::Components::FrequencyAnnotation const& frequency(estimator.get_annotation_data());
    
    CHECK(frequency.Value == std::chrono::minutes(60 * 24));
}

TEST_CASE("FrequencyEstimator - 2 Day Frequency") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::chrono::system_clock::time_point;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::FrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    // Should still have a frequency of 2 days
    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{AddDays(now, 0),
                                                                            AddDays(now, 2),
                                                                            AddDays(now, 4)}}));
    NS::Featurizers::Components::FrequencyAnnotation const& frequency(estimator.get_annotation_data());
    
    CHECK(frequency.Value == std::chrono::minutes(2 * 60 * 24));
}

TEST_CASE("FrequencyEstimator - 1 Minute Frequency") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::chrono::system_clock::time_point;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::FrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    // Should have a frequency of 1 minute
    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{AddMinutes(now, 0),
                                                                            AddMinutes(now, 1),
                                                                            AddMinutes(now, 2)}}));
    NS::Featurizers::Components::FrequencyAnnotation const& frequency(estimator.get_annotation_data());
    
    CHECK(frequency.Value == std::chrono::minutes(1));
}

TEST_CASE("FrequencyEstimator - 2 Minute Frequency") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::chrono::system_clock::time_point;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::FrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    // Should have a frequency of 2 days
    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{AddMinutes(now, 0),
                                                                            AddMinutes(now, 2),
                                                                            AddMinutes(now, 4)}}));
    NS::Featurizers::Components::FrequencyAnnotation const& frequency(estimator.get_annotation_data());
    
    CHECK(frequency.Value == std::chrono::minutes(2));
}

TEST_CASE("FrequencyEstimator - 1 Minute Frequency with mixed input times") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::chrono::system_clock::time_point;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::FrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    // Should have a frequency of 1 minute even though there are days included too
    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{AddMinutes(now, 0),
                                                                            AddMinutes(now, 1),
                                                                            AddDays(now, 1),
                                                                            AddDays(now, 2)}}));
    NS::Featurizers::Components::FrequencyAnnotation const& frequency(estimator.get_annotation_data());
    
    CHECK(frequency.Value == std::chrono::minutes(1));
}

TEST_CASE("FrequencyEstimator - Not in Chronological Order") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::chrono::system_clock::time_point;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::FrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    // Should throw since time is not in the correct order.
    CHECK_THROWS_WITH(NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{AddMinutes(now, 0),
                                                                            AddMinutes(now, 2),
                                                                            AddMinutes(now, 1)}})),
                                                                            "Input stream not in chronological order.");
}

TEST_CASE("FrequencyEstimator - Not enough rows") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::chrono::system_clock::time_point;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::FrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    // Should throw since time is not in the correct order.
    CHECK_THROWS_WITH(NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{AddMinutes(now, 0)}})),
                                                                            "Need to provide more than one value to get a frequency");
}