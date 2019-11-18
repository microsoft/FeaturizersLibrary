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

namespace NS = Microsoft::Featurizer;

TEST_CASE("CreateIndexMap") {
    // ----------------------------------------------------------------------
    using Histogram                         = NS::Featurizers::Components::HistogramAnnotationData<int>::Histogram;
    using IndexMap                          = NS::Featurizers::Components::IndexMapAnnotationData<int>::IndexMap;
    // ----------------------------------------------------------------------

    IndexMap const                          result(NS::Featurizers::Components::CreateIndexMap<int>(Histogram{ {5, 1u}, {3, 1u}, {1, 1u}, {2, 1u} }, IndexMap()));

    // Values should be indexed in order
    CHECK(result == IndexMap{ {1, 0u}, {2, 1u}, {3, 2u}, {5, 3u} });

    // Values appended should appear at the end of the list
    CHECK(NS::Featurizers::Components::CreateIndexMap<int>(Histogram{ {4, 1u}, {5, 1u}, {3, 1u}, {1, 1u}, {2, 1u} }, result) == IndexMap{ {1, 0u}, {2, 1u}, {3, 2u}, {5, 3u}, {4, 4u} });

    // In-order index when previous values aren't provided
    CHECK(NS::Featurizers::Components::CreateIndexMap<int>(Histogram{ {4, 1u}, {5, 1u}, {3, 1u}, {1, 1u}, {2, 1u} }, IndexMap()) == IndexMap{ {1, 0u}, {2, 1u}, {3, 2u}, {4, 3u}, {5, 4u}, {4, 4u} });
}

template <typename T>
typename NS::Featurizers::Components::IndexMapAnnotationData<T>::IndexMap Test(std::vector<T> const &input) {
    std::vector<std::vector<T>> const       batchedInput(NS::TestHelpers::make_vector<std::vector<T>>(input));
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    // Index map requires Histogram annotations
    NS::Featurizers::Components::IndexMapEstimator<T>   tempIndexMapEstimator(pAllColumnAnnotations, 0);

    CHECK_THROWS_WITH(NS::TestHelpers::Train(tempIndexMapEstimator, batchedInput), "Annotation data was not found for this column");

    // Standard tests
    NS::Featurizers::Components::HistogramEstimator<T>  histoEstimator(pAllColumnAnnotations, 0);
    NS::Featurizers::Components::IndexMapEstimator<T>   indexMapEstimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(histoEstimator, batchedInput);
    NS::TestHelpers::Train(indexMapEstimator, batchedInput);

    return indexMapEstimator.get_annotation_data().Value;
}

TEST_CASE("Integers") {
    CHECK(Test<int>({5, 3, 1, 2, 100, 4}) == NS::Featurizers::Components::IndexMapAnnotationData<int>::IndexMap{ {1, 0u}, {2, 1u}, {3, 2u}, {4, 3u}, {5, 4u}, {100, 5u} });
}

TEST_CASE("Strings") {
    CHECK(Test<std::string>({"one", "two", "three", "four"}) == NS::Featurizers::Components::IndexMapAnnotationData<std::string>::IndexMap{ {"four", 0u}, {"one", 1u}, {"three", 2u}, {"two", 3u} });
}
