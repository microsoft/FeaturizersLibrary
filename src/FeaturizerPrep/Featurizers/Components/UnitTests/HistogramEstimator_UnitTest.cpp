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

template <typename T>
using Histogram = std::map<T, std::uint32_t>;


template <typename inputType>
Histogram<inputType> Test(std::vector<std::vector<inputType>> const &inputBatches) {
    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::HistogramEstimator<inputType, 0> estimator(pAllColumnAnnotations);

    NS::TestHelpers::Train< NS::Featurizers::Components::HistogramEstimator<inputType, 0>, inputType>(estimator, inputBatches);
    NS::AnnotationMap::const_iterator const &           iterAnnotations(estimator.get_column_annotations()[0].find("HistogramEstimator"));

    return (static_cast<NS::Featurizers::Components::HistogramAnnotation<inputType> const &>(*iterAnnotations->second[0])).Value;
}

TEST_CASE("int") {
    using inputType = int;
    
    Histogram<inputType> _histogram({{10,4}, {20, 1} , {8, 2}, {30, 2}, {7, 1}, {15, 2}, {11, 1}, {18, 1}, {6,1}});
    std::vector<std::vector<inputType>> const list({{10,20,8,10,30},
                                                    {7,10,10,15,11},
                                                    {15,30,18,8,6}});
    Histogram<inputType> toCheck = Test<inputType>(list);
    CHECK(toCheck == _histogram);
}


TEST_CASE("string") {
    using inputType = std::string;
    
    Histogram<inputType> _histogram({{"orange",2}, {"apple", 2}, {"peach", 3}, {"grape", 2}, {"banana",1}});
    std::vector<std::vector<inputType>> const list({{"orange", "apple", "apple", "peach", "grape"},
                                                    {"grape", "orange", "peach", "peach", "banana"}});
    Histogram<inputType> toCheck = Test<inputType>(list);
    CHECK(toCheck == _histogram);
}

