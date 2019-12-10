// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"
#include "../NormUpdater.h"
namespace NS = Microsoft::Featurizer;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

// norm result tests
TEST_CASE("valid argument for norm result") {
    NS::Featurizers::Components::Details::NormUpdater<int>::NormResult res(10, 100, 1);
    CHECK(res.L1_norm == 10);
    CHECK(res.L2_norm == 100);
    CHECK(res.Max_norm == 1);
}

TEST_CASE("invalid argument for norm result") {
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::NormUpdater<int>::NormResult(-1,              // l1
                                                                                          1,              // l2
                                                                                          1               // max
                                                                                        ), "l1 norm shouldn't be less than 0!");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::NormUpdater<int>::NormResult( 1,              // l1
                                                                                         -1,              // l2
                                                                                          1               // max
                                                                                        ), "l2 norm shouldn't be less than 0!");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::NormUpdater<std::double_t>::NormResult( 1,              // l1
                                                                                                    1,              // l2
                                                                                                    -1               // max
                                                                                                  ), "max norm shouldn't be less than 0!");
}

// updater tests

TEST_CASE("updater for statistic metrics usage") {
    using inputType = int;
    NS::Featurizers::Components::Details::NormUpdater<inputType> updater(
                                                                         5                     // average
                                                                         );
    NS::Featurizers::Components::Details::NormUpdater<inputType>::NormResult const & initial(updater.commit());
    CHECK(initial.L1_norm  == 0);
    CHECK(initial.L2_norm  == 0);
    CHECK(initial.Max_norm == 0);

    updater.update_max(1);
    updater.update_l1l2(1);
    updater.update_max(3);
    updater.update_l1l2(3);
    updater.update_max(5);
    updater.update_l1l2(5);
    updater.update_max(7);
    updater.update_l1l2(7);
    updater.update_max(9);
    updater.update_l1l2(9);
    NS::Featurizers::Components::Details::NormUpdater<inputType>::NormResult const & result(updater.commit());
    CHECK(result.L1_norm == 12);
    CHECK(NS::TestHelpers::FuzzyCheck<long double>({result.L2_norm}, {std::sqrt(40)}));
    CHECK(result.Max_norm == 9);
}

TEST_CASE("updater for vectors' l1 l2 norm") {
    using inputType = int;
    NS::Featurizers::Components::Details::NormUpdater<inputType> updater;
    NS::Featurizers::Components::Details::NormUpdater<inputType>::NormResult const & initial(updater.commit());
    CHECK(initial.L1_norm  == 0);
    CHECK(initial.L2_norm  == 0);
    CHECK(initial.Max_norm == 0);

    updater.update_max(1);
    updater.update_l1l2(1);
    updater.update_max(2);
    updater.update_l1l2(2);
    updater.update_max(2);
    updater.update_l1l2(2);
    updater.update_max(4);
    updater.update_l1l2(4);
    NS::Featurizers::Components::Details::NormUpdater<inputType>::NormResult const & result(updater.commit());
    CHECK(result.L1_norm  == 9);
    CHECK(result.L2_norm  == 5);
    CHECK(result.Max_norm == 4);
}

TEST_CASE("updater overflow") {
    using inputType = std::double_t;
    NS::Featurizers::Components::Details::NormUpdater<inputType> updater;
    updater.update_l1l2(std::sqrt(std::numeric_limits<inputType>::max()));
    CHECK_THROWS_WITH(updater.update_l1l2(1), "In l1 norm calculation, difference between input and average is so small comparing to l1_norm that l1_norm is the same after long double addition!");
    // create a condition so that l2 norm overflows
    CHECK_THROWS_WITH(updater.update_l1l2(std::sqrt(std::numeric_limits<inputType>::max()) /10 ), "Overflows occured during calculating l2_norm! Check your data!");
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
