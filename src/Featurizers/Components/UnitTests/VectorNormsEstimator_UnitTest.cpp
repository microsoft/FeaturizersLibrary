// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"
#include "../VectorNormsEstimator.h"
#include "../../Structs.h"

namespace NS = Microsoft::Featurizer;

TEST_CASE("all zeros - l1 norm") {
    using ValueType = std::uint16_t;
    using InputType = std::vector<ValueType>;

    std::vector<std::vector<InputType>> const list({{{0, 0, 0, 0},
                                                     {0, 0, 0, 0},
                                                     {0, 0, 0, 0},
                                                     {0, 0, 0, 0}}});

    NS::AnnotationMapsPtr                                                                       pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::VectorNormsEstimator<InputType, NS::Featurizers::NormType::L1> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);

    NS::Featurizers::Components::VectorNormsAnnotationData const &       annotation(estimator.get_annotation_data());

    std::vector<long double> norms({0, 0, 0, 0});
    CHECK(annotation.Norms   == norms);
    CHECK(annotation.Type    == NS::Featurizers::NormType::L1);
}

TEST_CASE("1D matrix - l2 norm") {
    using ValueType = std::uint16_t;
    using InputType = std::vector<ValueType>;

    std::vector<std::vector<InputType>> const list({{{0, 5, 12, 0}}});

    NS::AnnotationMapsPtr                                                                       pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::VectorNormsEstimator<InputType, NS::Featurizers::NormType::L2> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);

    NS::Featurizers::Components::VectorNormsAnnotationData const &       annotation(estimator.get_annotation_data());

    std::vector<long double> norms({13});
    CHECK(annotation.Norms   == norms);
    CHECK(annotation.Type    == NS::Featurizers::NormType::L2);
}

TEST_CASE("int16_t - l2 norm") {
    using ValueType = std::int16_t;
    using InputType = std::vector<ValueType>;

    std::vector<std::vector<InputType>> const list({{{0, 0, 0, 0},
                                                     {3, 4, 0, 0},
                                                     {0, 0, 3, 0},
                                                     {0, 6, 0, 0}}});

    NS::AnnotationMapsPtr                                                                       pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::VectorNormsEstimator<InputType, NS::Featurizers::NormType::L2> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);

    NS::Featurizers::Components::VectorNormsAnnotationData const &       annotation(estimator.get_annotation_data());

    std::vector<long double> norms({0, 5, 3, 6});
    CHECK(annotation.Norms   == norms);
    CHECK(annotation.Type    == NS::Featurizers::NormType::L2);
}


TEST_CASE("double - max norm") {
    using ValueType = std::double_t;
    using InputType = std::vector<ValueType>;

    std::vector<std::vector<InputType>> const list({{{10.5,   20,    0,  0,    0,    0},
                                                     {   0, 30.7,    0, 45,    0,    0},
                                                     {   0,    0, 56.5, 46, 78.3,    0},
                                                     {   0,    0,    0,  0,    0, 87.9}}});

    NS::AnnotationMapsPtr                                                                        pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::VectorNormsEstimator<InputType, NS::Featurizers::NormType::MAX> estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);

    NS::Featurizers::Components::VectorNormsAnnotationData const &       annotation(estimator.get_annotation_data());

    std::vector<long double> norms({static_cast<long double>(20.0),
                                    static_cast<long double>(45.0),
                                    static_cast<long double>(78.3),
                                    static_cast<long double>(87.9)});
    CHECK(annotation.Norms   == norms);
    CHECK(annotation.Type    == NS::Featurizers::NormType::MAX);
}
