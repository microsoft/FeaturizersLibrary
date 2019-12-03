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
// test for update_statistics specifically
TEST_CASE("correct cases") {
    using inputType = int;

    long double sum = 0;
    inputType min = 0;
    inputType max = 0;
    std::uint64_t count = 0;
    bool first_element_flag = true;
    NS::Featurizers::Components::update_basic_statistics<inputType>(3, min, max, count, first_element_flag);
    NS::Featurizers::Components::update_standard_statistics<inputType>(3, sum);
    CHECK(min == 3);
    CHECK(max == 3);
    CHECK(sum == 3);
    CHECK(count == 1);

    sum = 10;
    min = 0;
    max = 100;
    count = 5;
    first_element_flag = false;
    NS::Featurizers::Components::update_basic_statistics<inputType>(3, min, max, count, first_element_flag);
    NS::Featurizers::Components::update_standard_statistics<inputType>(3, sum);
    CHECK(min == 0);
    CHECK(max == 100);
    CHECK(sum == 13);
    CHECK(count == 6);

    NS::Featurizers::Components::update_basic_statistics<inputType>(-9, min, max, count, first_element_flag);
    NS::Featurizers::Components::update_standard_statistics<inputType>(-9, sum);
    CHECK(min == -9);
    CHECK(max == 100);
    CHECK(sum == 4);
    CHECK(count == 7);

    NS::Featurizers::Components::update_basic_statistics<inputType>(105, min, max, count, first_element_flag);
    NS::Featurizers::Components::update_standard_statistics<inputType>(105, sum);
    CHECK(min == -9);
    CHECK(max == 105);
    CHECK(sum == 109);
    CHECK(count == 8);

    std::string smin = "kat";
    std::string smax = "nadelle";
    std::string sinput = "zed";
    NS::Featurizers::Components::update_basic_statistics<std::string>(sinput, smin, smax, count, first_element_flag);
    CHECK(smin == "kat");
    CHECK(smax == "zed");
    CHECK(count == 9);
}

TEST_CASE("overflow") {
    // min max wouldn't need to be tested for overflow because if min, max are out of range, it would cause compile error
    using inputType = long double;

    long double sum = std::numeric_limits<long double>::max();
    inputType min = 0;
    inputType max = 100;
    std::uint64_t count = 5;
    bool first_element_flag = false;
    CHECK_THROWS_WITH(NS::Featurizers::Components::update_standard_statistics<inputType>(std::numeric_limits<long double>::max(), sum), "Overflow occured for sum during calculating statistic metrics! Check your data!");
    // when input cannot affect sum, an exception will be thrown
    CHECK_THROWS_WITH(NS::Featurizers::Components::update_standard_statistics<inputType>(1, sum), "Input is so small comparing to sum that sum is the same after long double addition!");


    sum = std::numeric_limits<long double>::lowest();
    CHECK_THROWS_WITH(NS::Featurizers::Components::update_standard_statistics<inputType>(std::numeric_limits<long double>::lowest(), sum), "Overflow occured for sum during calculating statistic metrics! Check your data!");

    sum = 10;
    count = std::numeric_limits<std::uint64_t>::max();
    CHECK_THROWS_WITH(NS::Featurizers::Components::update_basic_statistics<inputType>(4, min, max, count, first_element_flag), "Overflow occured for count during calculating statistic metrics! Check your data!");
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
                                                    static_cast<inputType>(10.3),
                                                    static_cast<inputType>(20.1),
                                                    static_cast<inputType>(8.4),
                                                    static_cast<inputType>(8.2),
                                                    static_cast<inputType>(10.3),
                                                    static_cast<inputType>(30.1),
                                                    static_cast<inputType>(30.4),
                                                    static_cast<inputType>(15.8)}});

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
