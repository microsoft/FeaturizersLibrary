// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"
#include "../StatisticalMetricsEstimator.h"

namespace NS = Microsoft::Featurizer;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif
// test for valid argument for constructors
TEST_CASE("valid argument for AnnotationData constructors") {
    NS::Featurizers::Components::BasicStatisticalAnnotationData<int> basics(10,              // min
                                                                            20,              // max
                                                                             3               // count
                                                                            );
    CHECK(basics.Min  == 10);
    CHECK(basics.Max  == 20);
    CHECK(basics.Count == 3);

    NS::Featurizers::Components::StandardStatisticalAnnotationData<int> standard(200,           // sum
                                                                                  50,           // average
                                                                                  10,           // min
                                                                                  90,           // max
                                                                                   4            // count
                                                                                );
    CHECK(standard.Sum  == 200);
    CHECK(standard.Average  == 50);
    CHECK(standard.Min  == 10);
    CHECK(standard.Max  == 90);
    CHECK(standard.Count == 4);
}
// test for invalid argument for constructors
TEST_CASE("invalid argument for AnnotationData constructors") {
    CHECK_THROWS_WITH(NS::Featurizers::Components::BasicStatisticalAnnotationData<int>(10,              // min
                                                                                        1,              // max
                                                                                        3               // count
                                                                                        ), "min is > max");
    // checks lower bound
    CHECK_THROWS_WITH(NS::Featurizers::Components::StandardStatisticalAnnotationData<int>(100,           // sum
                                                                                          17,           // average
                                                                                          18,           // min
                                                                                          30,           // max
                                                                                           3            // count
                                                                                         ), "average is not in the correct range");
    // checks upper bound
    CHECK_THROWS_WITH(NS::Featurizers::Components::StandardStatisticalAnnotationData<int>(100,           // sum
                                                                                          35,           // average
                                                                                          18,           // min
                                                                                          30,           // max
                                                                                           3            // count
                                                                                         ), "average is not in the correct range");
}
// test for updaters class specifically
TEST_CASE("updaters for integer types") {
    using inputType = int;

    NS::Featurizers::Components::Updaters::StandardStatsUpdater<inputType> standard_updater;
    standard_updater.update(1);
    standard_updater.update(3);
    standard_updater.update(5);
    standard_updater.update(7);
    NS::Featurizers::Components::StandardStatisticalAnnotationData<inputType> const& stats(standard_updater.commit());
    CHECK(stats.Sum     == 16);
    CHECK(stats.Average == 4);
    CHECK(stats.Min     == 1);
    CHECK(stats.Max     == 7);
    CHECK(stats.Count   == 4);
}

TEST_CASE("updaters for numerical types") {
    using inputType = std::double_t;

    NS::Featurizers::Components::Updaters::StandardStatsUpdater<inputType> standard_updater;
    standard_updater.update(1.41);
    standard_updater.update(3.76);
    standard_updater.update(5.39);
    standard_updater.update(7.89);
    NS::Featurizers::Components::StandardStatisticalAnnotationData<inputType> const& stats(standard_updater.commit());
    CHECK(NS::TestHelpers::FuzzyCheck<long double>({stats.Sum},       {18.45}));
    CHECK(NS::TestHelpers::FuzzyCheck<std::double_t>({stats.Average}, {4.6125}));
    CHECK(NS::TestHelpers::FuzzyCheck<inputType>({stats.Min},         {1.41}));
    CHECK(NS::TestHelpers::FuzzyCheck<inputType>({stats.Max},         {7.89}));
    CHECK(stats.Count == 4);
}

TEST_CASE("updaters for string") {
    using inputType = std::string;

    NS::Featurizers::Components::Updaters::BasicStatsUpdater<inputType> basic_updater;
    basic_updater.update("zed");
    basic_updater.update("xayah");
    basic_updater.update("tydamire");
    basic_updater.update("ryze");
    basic_updater.update("teemmo");
    NS::Featurizers::Components::BasicStatisticalAnnotationData<inputType> const& stats(basic_updater.commit());
    CHECK(stats.Min   == "ryze");
    CHECK(stats.Max   == "zed");
    CHECK(stats.Count == 5);
}

TEST_CASE("overflow for integer types") {
    using inputType = std::int64_t;

    // checks for upper bound
    NS::Featurizers::Components::Updaters::StandardStatsUpdater<inputType> standard_updater;
    standard_updater.update(std::numeric_limits<inputType>::max());
    CHECK_THROWS_WITH(standard_updater.update(1), "Overflow occured for sum during calculating statistic metrics! Check your data!");

    // checks for lower bound
    // reset the sum to 0
    standard_updater.update(std::numeric_limits<inputType>::lowest());
    standard_updater.update(1);

    standard_updater.update(std::numeric_limits<inputType>::lowest());
    standard_updater.update(5);
    CHECK_THROWS_WITH(standard_updater.update(-10), "Overflow occured for sum during calculating statistic metrics! Check your data!");
}

TEST_CASE("overflow for numerical types") {
    using inputType = std::double_t;

    NS::Featurizers::Components::Updaters::StandardStatsUpdater<inputType> standard_updater;
    standard_updater.update(std::numeric_limits<inputType>::max());
    CHECK_THROWS_WITH(standard_updater.update(1), "Input is so small comparing to sum that sum is the same after long double addition!");
}


// test for overall estimator
TEST_CASE("int") {
    using inputType = int;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::StatisticalMetricsEstimator<inputType> estimator(pAllColumnAnnotations,0);

    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{10,
                                                                            20,
                                                                            30,
                                                                            40,
                                                                            50}}));
    NS::Featurizers::Components::StandardStatisticalAnnotationData<inputType> const& stats(estimator.get_annotation_data());

    CHECK(stats.Min     == 10);
    CHECK(stats.Max     == 50);
    CHECK(stats.Count   == 5);
    CHECK(stats.Sum     == 150);
    CHECK(stats.Average == 30);
}

TEST_CASE("double") {
    using inputType = std::double_t;

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::StatisticalMetricsEstimator<inputType> estimator(pAllColumnAnnotations, 0);
    // just have one input
    NS::TestHelpers::Train(estimator, std::vector<std::vector<inputType>>({{
                                                                            10.3
                                                                            }}));
    NS::Featurizers::Components::StandardStatisticalAnnotationData<inputType> const& stats(estimator.get_annotation_data());

    CHECK(NS::TestHelpers::FuzzyCheck<inputType>({stats.Min},         {10.3}));
    CHECK(NS::TestHelpers::FuzzyCheck<inputType>({stats.Max},         {10.3}));
    CHECK(stats.Count == 1);
    CHECK(NS::TestHelpers::FuzzyCheck<long double>({stats.Sum},       {10.3}));
    CHECK(NS::TestHelpers::FuzzyCheck<std::double_t>({stats.Average}, {10.3}));
}

TEST_CASE("string") {
    using inputType = std::string;

    std::vector<std::vector<inputType>> const list({{"hello",
                                                    "either",
                                                    "xayah",
                                                    "exceed",
                                                    "maximum"}});

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::StatisticalMetricsEstimator<inputType> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);
    NS::Featurizers::Components::BasicStatisticalAnnotationData<inputType> const& stats(estimator.get_annotation_data());

    CHECK(stats.Min == "either");
    CHECK(stats.Max == "xayah");
    CHECK(stats.Count == 5);
}

TEST_CASE("all same input") {
    using inputType = int;

    std::vector<std::vector<inputType>> const list({{10,
                                                    10,
                                                    10,
                                                    10,
                                                    10}});

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::StatisticalMetricsEstimator<inputType> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);
    NS::Featurizers::Components::StandardStatisticalAnnotationData<inputType> const& stats(estimator.get_annotation_data());

    CHECK(stats.Min == 10);
    CHECK(stats.Max == 10);
    CHECK(stats.Count == 5);
    CHECK(stats.Sum == 50);
    CHECK(stats.Average == 10);
}

TEST_CASE("null input for numerical types") {
    using inputType = std::double_t;

    inputType null = NS::Traits<inputType>::CreateNullValue();

    std::vector<std::vector<inputType>> const list({{
                                                    null,
                                                    null,
                                                    null,
                                                    null}});

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::StatisticalMetricsEstimator<inputType> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);
    NS::Featurizers::Components::StandardStatisticalAnnotationData<inputType> const& stats(estimator.get_annotation_data());

    CHECK(stats.Min == 0);
    CHECK(stats.Max == 0);
    CHECK(stats.Count == 0);
    CHECK(stats.Sum == 0);
    CHECK(stats.Average == 0);
}

TEST_CASE("null input for string") {
    using inputType = nonstd::optional<std::string>;

    inputType null = NS::Traits<inputType>::CreateNullValue();

    std::vector<std::vector<inputType>> const list({{
                                                    null,
                                                    null,
                                                    null,
                                                    null}});

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::StatisticalMetricsEstimator<inputType> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);
    NS::Featurizers::Components::BasicStatisticalAnnotationData<inputType> const& stats(estimator.get_annotation_data());

    CHECK(stats.Count == 0);
}
#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
