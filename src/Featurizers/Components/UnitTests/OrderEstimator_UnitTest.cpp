// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../OrderEstimator.h"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

TEST_CASE("int") {
    // ----------------------------------------------------------------------
    using OrderEstimator                    = NS::Featurizers::Components::OrderEstimator<int>;
    // ----------------------------------------------------------------------

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    OrderEstimator                          estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(
        estimator,
        std::vector<int>{10, 20, 30, 40, 10, 30, 20, 50}
    );

    NS::Featurizers::Components::OrderAnnotationData<int> const &           annotation(estimator.get_annotation_data());

    CHECK(annotation.Value == std::unordered_map<int, std::uint32_t>{{10, 0}, {20, 1}, {30, 2}, {40, 3}, {50, 4}});
}

TEST_CASE("optional int") {
    // ----------------------------------------------------------------------
    using OrderEstimator                    = NS::Featurizers::Components::OrderEstimator<nonstd::optional<int>>;
    // ----------------------------------------------------------------------

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    OrderEstimator                          estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(
        estimator,
        std::vector<nonstd::optional<int>>{
            10,
            20,
            nonstd::optional<int>(),
            30,
            40,
            10,
            nonstd::optional<int>(),
            30,
            20,
            50
        }
    );

    NS::Featurizers::Components::OrderAnnotationData<nonstd::optional<int>> const &     annotation(estimator.get_annotation_data());

    CHECK(
        annotation.Value == std::unordered_map<nonstd::optional<int>, std::uint32_t>{
            {10, 0},
            {20, 1},
            {nonstd::optional<int>(), 2},
            {30, 3},
            {40, 4},
            {50, 5}
        }
    );
}

TEST_CASE("float") {
    // ----------------------------------------------------------------------
    using OrderEstimator                    = NS::Featurizers::Components::OrderEstimator<float>;
    // ----------------------------------------------------------------------

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    OrderEstimator                          estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(
        estimator,
        std::vector<float>{
            10.0f,
            20.0f,
            NS::Traits<float>::CreateNullValue(),
            30.0f,
            40.0f,
            10.0f,
            NS::Traits<float>::CreateNullValue(),
            30.0f,
            20.0f,
            50.0f
        }
    );

    NS::Featurizers::Components::OrderAnnotationData<float> const &         annotation(estimator.get_annotation_data());

    // Older versions of GCC don't use key_equal for object comparison, so we can't just compare the result
    // to a new map.
    CHECK(annotation.Value.size() == 6);

    for(auto const &kvp : annotation.Value) {
        if(kvp.first == 10.0f)
            CHECK(kvp.second == 0);
        else if(kvp.first == 20.0f)
            CHECK(kvp.second == 1);
        else if(NS::Traits<float>::IsNull(kvp.first))
            CHECK(kvp.second == 2);
        else if(kvp.first == 30.0f)
            CHECK(kvp.second == 3);
        else if(kvp.first == 40.0f)
            CHECK(kvp.second == 4);
        else if(kvp.first == 50.0f)
            CHECK(kvp.second == 5);
        else
            CHECK(false);
    }
}

TEST_CASE("No inputs") {
    NS::Featurizers::Components::OrderEstimator<int>    estimator(NS::CreateTestAnnotationMapsPtr(1), 0);

    estimator.begin_training();
    CHECK_THROWS_WITH(estimator.complete_training(), "value");
}

TEST_CASE("All null inputs") {
    // ----------------------------------------------------------------------
    using OrderEstimator                    = NS::Featurizers::Components::OrderEstimator<float>;
    // ----------------------------------------------------------------------

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    OrderEstimator                          estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(
        estimator,
        std::vector<float>{
            NS::Traits<float>::CreateNullValue(),
            NS::Traits<float>::CreateNullValue()
        }
    );

    NS::Featurizers::Components::OrderAnnotationData<float> const &         annotation(estimator.get_annotation_data());

    // Older versions of GCC don't use key_equal for object comparison, so we can't just compare the result
    // to a new map.
    CHECK(annotation.Value.size() == 1);
    REQUIRE(annotation.Value.find(NS::Traits<float>::CreateNullValue()) != annotation.Value.end());
    CHECK(annotation.Value.find(NS::Traits<float>::CreateNullValue())->second == 0);
}

TEST_CASE("Existing values") {
    // ----------------------------------------------------------------------
    using OrderEstimator                    = NS::Featurizers::Components::OrderEstimator<int>;
    // ----------------------------------------------------------------------

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    OrderEstimator                          estimator(pAllColumnAnnotations, 0, std::unordered_map<int, std::uint32_t>{{300, 0}, {200, 1}, {400, 2}});

    NS::TestHelpers::Train(
        estimator,
        std::vector<int>{10, 20, 30, 40, 10, 30, 20, 50}
    );

    NS::Featurizers::Components::OrderAnnotationData<int> const &           annotation(estimator.get_annotation_data());

    CHECK(
        annotation.Value == std::unordered_map<int, std::uint32_t>{
            {300, 0},
            {200, 1},
            {400, 2},
            {10, 3},
            {20, 4},
            {30, 5},
            {40, 6},
            {50, 7}
        }
    );
}

TEST_CASE("Invalid OrderAnnotationData") {
    CHECK_THROWS_WITH(NS::Featurizers::Components::OrderAnnotationData<int>(std::unordered_map<int, std::uint32_t>()), "value");
}
