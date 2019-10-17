// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"
#include "../IndexMapEstimator.h"
#include "../HistogramEstimator.h"
#include "../PipelineExecutionEstimatorImpl.h"

namespace NS = Microsoft::Featurizer;

template <typename KeyT, typename IndexT>
using IndexMap                            = std::map<KeyT, IndexT>;
template <typename T>
using Histogram                           = std::map<T, std::uint32_t>;



TEST_CASE("int") {
    using InputType = int;
    using TransformedType = std::uint32_t;
    Histogram<InputType> histogram({
                                    {10,4},
                                    {11,1},
                                    {18,1},
                                    {6,1},
                                    {7,1},
                                    {15,2},
                                    {30,2},
                                    {20,1},
                                    {8,2}
                                    
                                    });
    IndexMap<InputType, TransformedType> indexmap({
                                   {6, 1}, 
                                   {7, 2}, 
                                   {8, 3}, 
                                   {10, 4}, 
                                   {11, 5}, 
                                   {15, 6}, 
                                   {18, 7}, 
                                   {20, 8}, 
                                   {30, 9}
                                   });
    
    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::IndexMapEstimator<InputType, TransformedType,0> estimator(pAllColumnAnnotations);
    IndexMap<InputType, TransformedType> toCheck(estimator.create_index_map_from_histogram(histogram));
    CHECK(toCheck == indexmap);
}


TEST_CASE("string") {
    using InputType = std::string;
    using TransformedType = std::uint32_t;
    Histogram<InputType> histogram({
                                    {"apple",2},
                                    {"banana",1},
                                    {"grape",2},
                                    {"orange",2},
                                    {"peach",3}
                                    
                                    });
    IndexMap<InputType, TransformedType> indexmap({
                                    {"apple", 1},
                                    {"banana", 2},
                                    {"grape", 3},
                                    {"orange", 4},
                                    {"peach", 5}});
                                                    
    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::IndexMapEstimator<InputType, TransformedType,0> estimator(pAllColumnAnnotations);
    IndexMap<InputType, TransformedType> toCheck(estimator.create_index_map_from_histogram(histogram));
    CHECK(toCheck == indexmap);
}

