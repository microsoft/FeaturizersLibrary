// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../TestHelpers.h"
#include "../FrequencyMinimumEstimator.h"

namespace NS = Microsoft::Featurizer;

std::chrono::system_clock::time_point AddDays(std::chrono::system_clock::time_point tp, int daysToAdd){
    return tp + std::chrono::minutes(daysToAdd * (60 * 24));
}


TEST_CASE("Simple test") {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    using inputType = std::tuple<std::string,std::chrono::system_clock::time_point>;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::FrequencyMinimumEstimator<> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{std::make_tuple("one",AddDays(now, 0)),
                                                                            std::make_tuple("one",AddDays(now, 1)),
                                                                            std::make_tuple("one",AddDays(now, 2))}}));
    NS::Featurizers::Components::FrequencyMinimumAnnotation const& frequency(estimator.get_annotation_data());

    CHECK(frequency.Value == std::chrono::minutes(60 * 24));
}
