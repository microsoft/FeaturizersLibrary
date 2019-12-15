// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"
#include "../StandardDeviationEstimator.h"
namespace NS = Microsoft::Featurizer;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

// test for annotation data

TEST_CASE("valid argument for annotation data") {
    NS::Featurizers::Components::StandardDeviationAnnotationData deviation(1,3);
    CHECK(deviation.StandardDeviation == 1);
    CHECK(deviation.Count == 3);
}

TEST_CASE("invalid argument for annotation data") {
    CHECK_THROWS_WITH(NS::Featurizers::Components::StandardDeviationAnnotationData(-1, 1), "Standard deviation shouldn't be less than 0!");
    CHECK_THROWS_WITH(NS::Featurizers::Components::StandardDeviationAnnotationData(3, 0), "Standard deviation is not 0 when count is 0!");
}



// test for overall estimator
TEST_CASE("one int input data") {
    using inputType = int;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::StandardDeviationEstimator<inputType> estimator(pAllColumnAnnotations, 0,
                                                                                 10                         // user defined average
                                                                                 );

    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{10}}));
    NS::Featurizers::Components::StandardDeviationAnnotationData const& stats(estimator.get_annotation_data());

    CHECK(stats.StandardDeviation == 0);
    CHECK(stats.Count             == 1);
}

TEST_CASE("N random double input data") {
    using inputType = std::double_t;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::StandardDeviationEstimator<inputType> estimator(pAllColumnAnnotations, 0,
                                                                                 16.7                         // user defined average
                                                                                 );

    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{
                                                                            10.3l,
                                                                            20.1l,
                                                                            8.4l,
                                                                            8.2l,
                                                                            10.3l,
                                                                            30.1l,
                                                                            30.4l,
                                                                            15.8l}}));
    NS::Featurizers::Components::StandardDeviationAnnotationData const& stats(estimator.get_annotation_data());

    CHECK(NS::TestHelpers::FuzzyCheck<long double>({stats.StandardDeviation}, {static_cast<long double>(8.679573)}));
    CHECK(stats.Count == 8);
}


TEST_CASE("all same input") {
    using inputType = int;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::StandardDeviationEstimator<inputType> estimator(pAllColumnAnnotations, 0,
                                                                                 15                         // user defined average
                                                                                 );

    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{15,
                                                                            15,
                                                                            15,
                                                                            15,
                                                                            15,
                                                                            15,
                                                                            15}}));
    NS::Featurizers::Components::StandardDeviationAnnotationData const& stats(estimator.get_annotation_data());

    CHECK(stats.StandardDeviation == 0);
    CHECK(stats.Count == 7);
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
