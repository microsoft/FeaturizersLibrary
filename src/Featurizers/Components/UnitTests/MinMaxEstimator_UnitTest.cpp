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
std::tuple<InputT, InputT> FindMinMax(std::vector<std::vector<InputT>> const &inputBatches) {
    NS::AnnotationMapsPtr                                                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::MinMaxEstimator<InputT>                    estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, inputBatches);

    NS::Featurizers::Components::MinMaxAnnotationData<InputT> const &       annotation(estimator.get_annotation_data());

    return std::make_tuple(annotation.Min, annotation.Max);
}

TEST_CASE("Invalid Annotation") {
    CHECK_THROWS_WITH(NS::Featurizers::Components::MinMaxAnnotationData<int>(100, -2), "min is > max");
}

TEST_CASE("int") {
    using InputType                         = int;

    std::vector<std::vector<InputType>> const           list({{10,
                                                               20,
                                                               8,
                                                               10,
                                                               30}});
    std::tuple<InputType, InputType> const              toCheck(FindMinMax(list));

    CHECK(toCheck == std::make_tuple(8, 30));
}


TEST_CASE("float") {
    using InputType                         = std::float_t;

    std::vector<std::vector<InputType>> const           list({{
                                                                static_cast<InputType>(10.3),
                                                                static_cast<InputType>(20.1),
                                                                static_cast<InputType>(8.4),
                                                                static_cast<InputType>(8.2),
                                                                static_cast<InputType>(10.3),
                                                                static_cast<InputType>(30.1),
                                                                static_cast<InputType>(30.4)}});
    std::tuple<InputType, InputType> const              toCheck(FindMinMax(list));

    CHECK(toCheck == std::tuple<InputType, InputType>(8.2f, 30.4f));
}

TEST_CASE("double") {
    using InputType                         = std::double_t;

    std::vector<std::vector<InputType>> const           list({{
                                                                static_cast<InputType>(-1),
                                                                static_cast<InputType>(-0.5),
                                                                static_cast<InputType>(1),
                                                                static_cast<InputType>(0)}});
    std::tuple<InputType, InputType> const              toCheck(FindMinMax(list));

    CHECK(toCheck == std::tuple<InputType, InputType>(-1, 1));
}
