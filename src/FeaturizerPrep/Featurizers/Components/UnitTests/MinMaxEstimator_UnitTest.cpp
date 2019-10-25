// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"
#include "../MinMaxEstimator.h"

namespace NS = Microsoft::Featurizer;

template <typename InputT>
std::vector<InputT> FindMinMax(std::vector<std::vector<InputT>> const &inputBatches) {
    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::MinMaxEstimator<InputT, 0> estimator(pAllColumnAnnotations);

    NS::TestHelpers::Train< NS::Featurizers::Components::MinMaxEstimator<InputT, 0>, InputT>(estimator, inputBatches);
    NS::AnnotationMap::const_iterator const &           iterAnnotations(estimator.get_column_annotations()[0].find("MinMaxEstimator"));

    return std::vector<InputT>({
                                (static_cast<NS::Featurizers::Components::MinMaxAnnotation<InputT> const &>(*iterAnnotations->second[0])).Min,
                                (static_cast<NS::Featurizers::Components::MinMaxAnnotation<InputT> const &>(*iterAnnotations->second[0])).Max
                               }
    );
}


TEST_CASE("int") {
    using inputType = int;
    
    std::vector<std::vector<inputType>> const list({{10,
                                                    20,
                                                    8,
                                                    10,
                                                    30}});
    std::vector<inputType> toCheck = FindMinMax<inputType>(list);
    CHECK(toCheck == std::vector<inputType>({8,30}));
}


TEST_CASE("float") {
    using inputType = std::float_t;
    
    std::vector<std::vector<inputType>> const list({{
                                                    static_cast<inputType>(10.3),
                                                    static_cast<inputType>(20.1),
                                                    static_cast<inputType>(8.4),
                                                    static_cast<inputType>(8.2),
                                                    static_cast<inputType>(10.3),
                                                    static_cast<inputType>(30.1),
                                                    static_cast<inputType>(30.4)}});
    std::vector<inputType> toCheck = FindMinMax<inputType>(list);
    
    CHECK(toCheck == std::vector<inputType>({static_cast<inputType>(8.2),static_cast<inputType>(30.4)}));
    
}

TEST_CASE("double") {
    using inputType = std::double_t;
    
    std::vector<std::vector<inputType>> const list({{
                                                    static_cast<inputType>(-1),
                                                    static_cast<inputType>(-0.5),
                                                    static_cast<inputType>(1),
                                                    static_cast<inputType>(0)}});
    std::vector<inputType> toCheck = FindMinMax<inputType>(list);

    CHECK(toCheck == std::vector<inputType>({static_cast<inputType>(-1),static_cast<inputType>(1)}));
    
}
