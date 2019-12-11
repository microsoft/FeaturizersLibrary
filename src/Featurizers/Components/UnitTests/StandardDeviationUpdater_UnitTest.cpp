// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"
#include "../StandardDeviationUpdater.h"
namespace NS = Microsoft::Featurizer;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

// std result tests
TEST_CASE("valid argument for norm result") {
    NS::Featurizers::Components::Details::STDUpdater<int>::STDResult deviation(1,3);
    CHECK(deviation.StandardDeviation == 1);
    CHECK(deviation.Count == 3);
}

TEST_CASE("invalid argument for norm result") {
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::STDUpdater<int>::STDResult(-1, 1), "Standard deviation shouldn't be less than 0!");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::STDUpdater<int>::STDResult(3, 0), "Standard deviation is not 0 when count is 0!");
}

// updater tests

TEST_CASE("std updater normal cases") {
    using inputType = int;
    NS::Featurizers::Components::Details::STDUpdater<inputType> updater(2);
    // no input element
    CHECK_THROWS_WITH(updater.commit(), "update_l2 is not called before l2 is committed!");

    // 1 input element
    updater.update(0);
    NS::Featurizers::Components::Details::STDUpdater<inputType>::STDResult const r1(updater.commit());
    CHECK(NS::TestHelpers::FuzzyCheck<long double>({r1.StandardDeviation}, {2}));

    // 4 more input elements
    updater.update(1);
    updater.update(2);
    updater.update(3);
    updater.update(4);
    NS::Featurizers::Components::Details::STDUpdater<inputType>::STDResult const r2(updater.commit());
    CHECK(NS::TestHelpers::FuzzyCheck<long double>({r2.StandardDeviation}, {std::sqrt(10.0)/5.0}));
}
#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
