// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../ModeEstimator.h"
#include "../OrderEstimator.h"

#include "../../TestHelpers.h"
#include "../../../3rdParty/optional.h"

namespace NS = Microsoft::Featurizer;

template <typename T>
T Test(std::vector<T> const &input) {
    std::vector<std::vector<T>> const       batchedInput(NS::TestHelpers::make_vector<std::vector<T>>(input));
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    // Mode requires Histogram annotations
    NS::Featurizers::Components::ModeEstimator<T>       tempEstimator(pAllColumnAnnotations, 0);

    CHECK_THROWS_WITH(NS::TestHelpers::Train(tempEstimator, batchedInput), "Annotation data was not found for this column");

    // Standard tests
    NS::Featurizers::Components::HistogramEstimator<T>  histoEstimator(pAllColumnAnnotations, 0);
    NS::Featurizers::Components::OrderEstimator<T>      orderEstimator(pAllColumnAnnotations, 0);
    NS::Featurizers::Components::ModeEstimator<T>       modeEstimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(histoEstimator, batchedInput);
    NS::TestHelpers::Train(orderEstimator, batchedInput);
    NS::TestHelpers::Train(modeEstimator, batchedInput);

    return modeEstimator.get_annotation_data().Value;
}

TEST_CASE("Integers") {
    CHECK(Test<int>({5, 3, 1, 2, 3, 5, 1, 5}) == 5);
}

TEST_CASE("Strings") {
    CHECK(Test<std::string>({"one", "two", "three", "one"}) == "one");
}

using OptionalString                        = nonstd::optional<std::string>;

template <bool AllowNullModeValueV>
OptionalString TestNullModeValues(void) {
    std::vector<std::vector<OptionalString>> const                                      batchedInput(NS::TestHelpers::make_vector<std::vector<OptionalString>>(NS::TestHelpers::make_vector<OptionalString>("one", "two", OptionalString(), OptionalString(), "two", OptionalString())));
    NS::AnnotationMapsPtr                                                               pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::HistogramEstimator<OptionalString>                     histoEstimator(pAllColumnAnnotations, 0);
    NS::Featurizers::Components::OrderEstimator<OptionalString>                         orderEstimator(pAllColumnAnnotations, 0);
    NS::Featurizers::Components::ModeEstimator<OptionalString, AllowNullModeValueV>     modeEstimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(histoEstimator, batchedInput);
    NS::TestHelpers::Train(orderEstimator, batchedInput);
    NS::TestHelpers::Train(modeEstimator, batchedInput);

    return modeEstimator.get_annotation_data().Value;
}

TEST_CASE("Nulls") {
    CHECK(TestNullModeValues<true>() == OptionalString());
    CHECK(TestNullModeValues<false>() == "two");
}
