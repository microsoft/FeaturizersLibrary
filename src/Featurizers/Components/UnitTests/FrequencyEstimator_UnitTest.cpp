// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../TestHelpers.h"
#include "../FrequencyEstimator.h"

namespace NS = Microsoft::Featurizer;

std::chrono::system_clock::time_point GetTimePoint(std::chrono::system_clock::time_point tp, int unitsToAdd, std::string = "days"){
    return tp + std::chrono::minutes(unitsToAdd * (60*24));
}

// test for overall estimator
TEST_CASE("Simple Test") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::chrono::system_clock::time_point;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::FrequencyEstimator<> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{GetTimePoint(now, 0),
                                                                            GetTimePoint(now, 1),
                                                                            GetTimePoint(now, 2),
                                                                            GetTimePoint(now, 3),
                                                                            GetTimePoint(now, 4)}}));
    NS::Featurizers::Components::FrequencyAnnotation const& frequency(estimator.get_annotation_data());

    CHECK(frequency.Value     ==  std::chrono::minutes(60*24));
}
