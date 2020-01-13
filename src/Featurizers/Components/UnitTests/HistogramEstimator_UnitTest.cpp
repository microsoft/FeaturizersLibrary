// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"
#include "../HistogramEstimator.h"

namespace NS = Microsoft::Featurizer;

template <typename InputT>
typename NS::Featurizers::Components::HistogramAnnotationData<InputT>::Histogram Test(std::vector<std::vector<InputT>> const &inputBatches) {
    NS::AnnotationMapsPtr                                                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::HistogramEstimator<InputT>                 estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, inputBatches);

    NS::Featurizers::Components::HistogramAnnotationData<InputT> const &    annotation(estimator.get_annotation_data());

    return annotation.Value;
}

TEST_CASE("int") {
    using Histogram                         = NS::Featurizers::Components::HistogramAnnotationData<int>::Histogram;

    Histogram const                         histogram({{10,4}, {20, 1} , {8, 2}, {30, 2}, {7, 1}, {15, 2}, {11, 1}, {18, 1}, {6,1}});
    std::vector<std::vector<int>> const     list({{10,20,8,10,30},
                                                  {7,10,10,15,11},
                                                  {15,30,18,8,6}});
    Histogram const                         toCheck(Test(list));

    CHECK(toCheck == histogram);
}

TEST_CASE("optional int") {
    using Histogram                         = NS::Featurizers::Components::HistogramAnnotationData<nonstd::optional<int>>::Histogram;

    Histogram const                         histogram({{10,4}, {20, 1} , {8, 2}, {30, 2}, {7, 1}, {15, 2}, {11, 1}, {18, 1}, {6,1}, {nonstd::optional<int>(),4}});
    std::vector<std::vector<nonstd::optional<int>>> const                   list(
        {
            {10,20,8,10,30,nonstd::optional<int>()},
            {7,10,10,nonstd::optional<int>(),nonstd::optional<int>(),15,11},
            {nonstd::optional<int>(),15,30,18,8,6}
        }
    );
    Histogram const                         toCheck(Test(list));

    CHECK(toCheck == histogram);
}

TEST_CASE("string") {
    using Histogram                         = NS::Featurizers::Components::HistogramAnnotationData<std::string>::Histogram;

    Histogram const                                     histogram({{"orange",2}, {"apple", 2}, {"peach", 3}, {"grape", 2}, {"banana",1}});
    std::vector<std::vector<std::string>> const         list({{"orange", "apple", "apple", "peach", "grape"},
                                                              {"grape", "orange", "peach", "peach", "banana"}});
    Histogram const                                     toCheck(Test(list));

    CHECK(toCheck == histogram);
}
