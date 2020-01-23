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

template <typename T>
using Range = std::pair<typename std::vector<T>::iterator, typename std::vector<T>::iterator>;

TEST_CASE("invalid input types") {
    CHECK(NS::Featurizers::Components::IsIteratorPair<Range<int>>::value);
    CHECK(NS::Featurizers::Components::IsIteratorPair<std::pair<int, int>>::value);
    CHECK(NS::Featurizers::Components::IsIteratorPair<std::tuple<int, int>>::value);
    CHECK(!NS::Featurizers::Components::IsIteratorPair<std::tuple<int, int, int>>::value);
    CHECK(!NS::Featurizers::Components::IsIteratorPair<std::pair<int, std::double_t>>::value);
    CHECK(!NS::Featurizers::Components::IsIteratorPair<std::tuple<int, std::double_t>>::value);
}

TEST_CASE("invalid annotation") {
    CHECK_THROWS_WITH(NS::Featurizers::Components::VectorNormsAnnotationData<NS::Featurizers::Components::Updaters::L1NormUpdater<int>>({}), "No norm is passed in to VectorNormsAnnotationData!");

    CHECK_THROWS_WITH(NS::Featurizers::Components::VectorNormsAnnotationData<NS::Featurizers::Components::Updaters::L1NormUpdater<int>>({1, -1, 3}), "Norms shouldn't be less than 0!");
}

TEST_CASE("all zeros - l1 norm") {
    using ValueType = std::uint16_t;
    using InputType = Range<ValueType>;

    std::vector<ValueType> row1({0, 0, 0, 0});
    std::vector<ValueType> row2({0, 0, 0, 0});
    std::vector<ValueType> row3({0, 0, 0, 0});
    std::vector<ValueType> row4({0, 0, 0, 0});
    std::vector<std::vector<InputType>> const list({{InputType(row1.begin(), row1.end()),
                                                     InputType(row2.begin(), row2.end()),
                                                     InputType(row3.begin(), row3.end()),
                                                     InputType(row4.begin(), row4.end())}});

    NS::AnnotationMapsPtr                                                                                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::VectorNormsEstimator<InputType, NS::Featurizers::Components::Updaters::L1NormUpdater<ValueType>>  estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);

    NS::Featurizers::Components::VectorNormsAnnotationData<NS::Featurizers::Components::Updaters::L1NormUpdater<ValueType>> const &annotation(estimator.get_annotation_data());

    std::vector<std::double_t> norms({0, 0, 0, 0});
    CHECK(annotation.Norms   == norms);
}

TEST_CASE("1D matrix - l2 norm") {
    using ValueType = std::uint16_t;
    using InputType = Range<ValueType>;

    std::vector<ValueType> row({0, 5, 12, 0});
    std::vector<std::vector<InputType>> const list({{InputType(row.begin(), row.end())}});

    NS::AnnotationMapsPtr                                                                                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::VectorNormsEstimator<InputType, NS::Featurizers::Components::Updaters::L2NormUpdater<ValueType>>  estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);

    NS::Featurizers::Components::VectorNormsAnnotationData<NS::Featurizers::Components::Updaters::L2NormUpdater<ValueType>> const &annotation(estimator.get_annotation_data());

    std::vector<std::double_t> norms({13});
    CHECK(annotation.Norms   == norms);
}

TEST_CASE("int16_t - l2 norm") {
    using ValueType = std::int16_t;
    using InputType = Range<ValueType>;

    std::vector<ValueType> row1({0, 0, 0, 0});
    std::vector<ValueType> row2({3, 4, 0, 0});
    std::vector<ValueType> row3({0, 0, 3, 0});
    std::vector<ValueType> row4({0, 6, 0, 0});

    std::vector<std::vector<InputType>> const list({{InputType(row1.begin(), row1.end()),
                                                     InputType(row2.begin(), row2.end()),
                                                     InputType(row3.begin(), row3.end()),
                                                     InputType(row4.begin(), row4.end())}});

    NS::AnnotationMapsPtr                                                                                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::VectorNormsEstimator<InputType, NS::Featurizers::Components::Updaters::L2NormUpdater<ValueType>>  estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);

    NS::Featurizers::Components::VectorNormsAnnotationData<NS::Featurizers::Components::Updaters::L2NormUpdater<ValueType>> const &annotation(estimator.get_annotation_data());

    std::vector<std::double_t> norms({0, 5, 3, 6});
    CHECK(annotation.Norms   == norms);
}


TEST_CASE("double - max norm") {
    using ValueType = std::double_t;
    using InputType = Range<ValueType>;

    std::vector<ValueType> row1({10.5,   20,    0,  0,    0,    0});
    std::vector<ValueType> row2({   0, 30.7,    0, 45,    0,    0});
    std::vector<ValueType> row3({   0,    0, 56.5, 46, 78.3,    0});
    std::vector<ValueType> row4({   0,    0,    0,  0,    0, 87.9});

    std::vector<std::vector<InputType>> const list({{InputType(row1.begin(), row1.end()),
                                                     InputType(row2.begin(), row2.end()),
                                                     InputType(row3.begin(), row3.end()),
                                                     InputType(row4.begin(), row4.end())}});

    NS::AnnotationMapsPtr                                                                                                           pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::VectorNormsEstimator<InputType, NS::Featurizers::Components::Updaters::MaxNormUpdater<ValueType>>  estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);

    NS::Featurizers::Components::VectorNormsAnnotationData<NS::Featurizers::Components::Updaters::MaxNormUpdater<ValueType>> const &annotation(estimator.get_annotation_data());

    std::vector<std::double_t> norms({static_cast<std::double_t>(20.0),
                                      static_cast<std::double_t>(45.0),
                                      static_cast<std::double_t>(78.3),
                                      static_cast<std::double_t>(87.9)});
    CHECK(annotation.Norms   == norms);
}


TEST_CASE("nonstd::optional<int> - l2 norm") {
    using ValueType = nonstd::optional<int>;
    using InputType = Range<ValueType>;

    std::vector<ValueType> row1({                      0, nonstd::optional<int>(), 0,                       0});
    std::vector<ValueType> row2({                      3,                       4, 0, nonstd::optional<int>()});
    std::vector<ValueType> row3({                      0, nonstd::optional<int>(), 3,                       0});
    std::vector<ValueType> row4({nonstd::optional<int>(),                       6, 0,                       0});

    std::vector<std::vector<InputType>> const list({{InputType(row1.begin(), row1.end()),
                                                     InputType(row2.begin(), row2.end()),
                                                     InputType(row3.begin(), row3.end()),
                                                     InputType(row4.begin(), row4.end())}});

    NS::AnnotationMapsPtr                                                                                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::VectorNormsEstimator<InputType, NS::Featurizers::Components::Updaters::L2NormUpdater<ValueType>>  estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, list);

    NS::Featurizers::Components::VectorNormsAnnotationData<NS::Featurizers::Components::Updaters::L2NormUpdater<ValueType>> const &annotation(estimator.get_annotation_data());

    std::vector<std::double_t> norms({0, 5, 3, 6});
    CHECK(annotation.Norms   == norms);
}

TEST_CASE("invalid input iterator") {
    using ValueType = std::uint16_t;
    using InputType = Range<ValueType>;

    std::vector<ValueType> row({0, 5, 12, 0});
    std::vector<std::vector<InputType>> const list({{InputType(row.end(), row.begin())}});

    NS::AnnotationMapsPtr                                                                                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::VectorNormsEstimator<InputType, NS::Featurizers::Components::Updaters::L2NormUpdater<ValueType>>  estimator(pAllColumnAnnotations, 0);

    CHECK_THROWS_WITH(NS::TestHelpers::Train(estimator, list), "Input iterators to VectorNormsEstimator are invalid!");
}
