// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"
#include "../StatisticsMetricsEstimator.h"

namespace NS = Microsoft::Featurizer;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif
// test for invalid argument for constructors
TEST_CASE("invalid argument for constructors") {
    CHECK_THROWS_WITH(NS::Featurizers::Components::BasicStatisticalAnnotationData<int>(10,1,3), "min is > max");
    CHECK_THROWS_WITH(NS::Featurizers::Components::StandardStatisticalAnnotaionData<int>(100, 17, 18, 30, 3), "average is not in the correct range");
}
// test for updaters class specifically
TEST_CASE("updaters for integer types") {
    using inputType = int;

    NS::Featurizers::Components::Details::StandardStatsUpdater<inputType> standard_updater;
    standard_updater.update(1);
    standard_updater.update(3);
    standard_updater.update(5);
    standard_updater.update(7);
    std::tuple<std::int64_t, std::double_t, inputType, inputType, std::uint64_t> ret = standard_updater.commit();
    CHECK(std::get<0>(ret) == 16);       // sum
    CHECK(std::get<1>(ret) == 4);        // average
    CHECK(std::get<2>(ret) == 1);        // min
    CHECK(std::get<3>(ret) == 7);        // max
    CHECK(std::get<4>(ret) == 4);        // count
}

TEST_CASE("updaters for numerical types") {
    using inputType = std::double_t;

    NS::Featurizers::Components::Details::StandardStatsUpdater<inputType> standard_updater;
    standard_updater.update(1.41);
    standard_updater.update(3.76);
    standard_updater.update(5.39);
    standard_updater.update(7.89);
    std::tuple<long double, std::double_t, inputType, inputType, std::uint64_t> ret = standard_updater.commit();
    CHECK(NS::TestHelpers::FuzzyCheck<long double>({std::get<0>(ret)}, {18.45}));       // sum
    CHECK(NS::TestHelpers::FuzzyCheck<std::double_t>({std::get<1>(ret)}, {4.6125}));    // average
    CHECK(NS::TestHelpers::FuzzyCheck<inputType>({std::get<2>(ret)}, {1.41}));          // min
    CHECK(NS::TestHelpers::FuzzyCheck<inputType>({std::get<3>(ret)}, {7.89}));          // max
    CHECK(std::get<4>(ret) == 4);                                                       // count
}

TEST_CASE("updaters for string") {
    using inputType = std::string;

    NS::Featurizers::Components::Details::BasicStatsUpdater<inputType> basic_updater;
    basic_updater.update("zed");
    basic_updater.update("xayah");
    basic_updater.update("tydamire");
    basic_updater.update("ryze");
    basic_updater.update("teemmo");
    std::tuple<inputType, inputType, std::uint64_t> ret = basic_updater.commit();
    CHECK(std::get<0>(ret) == "ryze");     // min
    CHECK(std::get<1>(ret) == "zed");      // max
    CHECK(std::get<2>(ret) == 5);         // count
}

TEST_CASE("overflow for integer types") {
    using inputType = std::int64_t;

    // checks for upper bound
    NS::Featurizers::Components::Details::StandardStatsUpdater<inputType> standard_updater;
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

    NS::Featurizers::Components::Details::StandardStatsUpdater<inputType> standard_updater;
    standard_updater.update(std::numeric_limits<inputType>::max());
    CHECK_THROWS_WITH(standard_updater.update(1), "Input is so small comparing to sum that sum is the same after long double addition!");
}


// test for overall estimator
TEST_CASE("int") {
    using inputType = int;

    std::vector<std::vector<inputType>> const list({{10,
                                                    20,
                                                    8,
                                                    10,
                                                    30}});

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::StatisticalMetricsEstimator<inputType> estimator(pAllColumnAnnotations,0);

    NS::TestHelpers::Train(estimator, list);
    NS::Featurizers::Components::StandardStatisticalAnnotaionData<inputType> const& stats(estimator.get_annotation_data());

    CHECK(stats.Min == 8);
    CHECK(stats.Max == 30);
    CHECK(stats.Count == 5);
    CHECK(stats.Sum == 78);
    CHECK(stats.Average == 15.6);
}

TEST_CASE("double") {
    using inputType = std::double_t;

    std::vector<std::vector<inputType>> const list({{
                                                    10.3,
                                                    20.1,
                                                    8.4,
                                                    8.2,
                                                    10.3,
                                                    30.1,
                                                    30.4,
                                                    15.8}});

    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::StatisticalMetricsEstimator<inputType> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);
    NS::Featurizers::Components::StandardStatisticalAnnotaionData<inputType> const& stats(estimator.get_annotation_data());

    CHECK(NS::TestHelpers::FuzzyCheck<inputType>({stats.Min}, {8.2}));
    CHECK(NS::TestHelpers::FuzzyCheck<inputType>({stats.Max}, {30.4}));
    CHECK(stats.Count == 8);
    CHECK(NS::TestHelpers::FuzzyCheck<long double>({stats.Sum}, {133.6}));
    CHECK(NS::TestHelpers::FuzzyCheck<std::double_t>({stats.Average}, {16.7}));
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
    NS::Featurizers::Components::StandardStatisticalAnnotaionData<inputType> const& stats(estimator.get_annotation_data());

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
    NS::Featurizers::Components::StandardStatisticalAnnotaionData<inputType> const& stats(estimator.get_annotation_data());

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
