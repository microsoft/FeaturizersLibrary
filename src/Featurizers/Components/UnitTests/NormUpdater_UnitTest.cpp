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
    NS::Featurizers::Components::Details::NormUpdater<int>::L1NormResult l1_res(1);
    NS::Featurizers::Components::Details::NormUpdater<int>::L2NormResult l2_res(1);
    NS::Featurizers::Components::Details::NormUpdater<int>::MaxNormResult max_res(1);
    CHECK(l1_res.L1_norm == 1);
    CHECK(l2_res.L2_norm == 1);
    CHECK(max_res.Max_norm == 1);
}

TEST_CASE("invalid argument for norm result") {
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::NormUpdater<int>::L1NormResult(-1), "l1 norm shouldn't be less than 0!");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::NormUpdater<int>::L2NormResult(-1), "l2 norm shouldn't be less than 0!");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::NormUpdater<std::double_t>::MaxNormResult(-1), "max norm shouldn't be less than 0!");
}

// updater tests

TEST_CASE("l1 updater normal cases") {
    using inputType = int;
    NS::Featurizers::Components::Details::NormUpdater<inputType> updater;
    CHECK_THROWS_WITH(updater.commit_l1(), "update_l1 is not called before l1 is committed!");

    updater.update_l1(0);
    NS::Featurizers::Components::Details::NormUpdater<inputType>::L1NormResult const & r1(updater.commit_l1());
    CHECK(r1.L1_norm == 0);

    updater.update_l1(1);
    updater.update_l1(2);
    updater.update_l1(3);
    NS::Featurizers::Components::Details::NormUpdater<inputType>::L1NormResult const & r2(updater.commit_l1());
    CHECK(r2.L1_norm == 6);
}
TEST_CASE("l1 updater overflow") {
    using inputType = std::double_t;
    NS::Featurizers::Components::Details::NormUpdater<inputType> updater;
    updater.update_l1(std::numeric_limits<inputType>::max());
    CHECK_THROWS_WITH(updater.update_l1(1), "In l1 norm calculation, input is so small comparing to l1_norm that l1_norm is the same after long double addition!");
    CHECK_THROWS_WITH(updater.update_l1(std::numeric_limits<inputType>::max()), "Overflows occured during calculating l1_norm! Check your data!");
}

TEST_CASE("l2 updater normal cases") {
    using inputType = int;
    NS::Featurizers::Components::Details::NormUpdater<inputType> updater;
    CHECK_THROWS_WITH(updater.commit_l2(), "update_l2 is not called before l2 is committed!");

    updater.update_l2(2);
    NS::Featurizers::Components::Details::NormUpdater<inputType>::L2NormResult const & r1(updater.commit_l2());
    CHECK(r1.L2_norm == 2);

    updater.update_l2(1);
    updater.update_l2(2);
    updater.update_l2(4);
    NS::Featurizers::Components::Details::NormUpdater<inputType>::L2NormResult const & r2(updater.commit_l2());
    CHECK(r2.L2_norm == 5);
}
TEST_CASE("l2 updater overflow") {
    using inputType = std::double_t;
    NS::Featurizers::Components::Details::NormUpdater<inputType> updater;
    updater.update_l2(std::sqrt(std::numeric_limits<inputType>::max()));
    CHECK_THROWS_WITH(updater.update_l2(1), "In l2 norm calculation, square of input is so small comparing to l2_norm that l2_norm is the same after long double addition!");
    CHECK_THROWS_WITH(updater.update_l2(std::numeric_limits<inputType>::max()), "Overflows occured during calculating l2_norm! Check your data!");
}

TEST_CASE("max updater") {
    using inputType = int;
    NS::Featurizers::Components::Details::NormUpdater<inputType> updater;
    CHECK_THROWS_WITH(updater.commit_l1(), "update_l1 is not called before l1 is committed!");
    CHECK_THROWS_WITH(updater.commit_l2(), "update_l2 is not called before l2 is committed!");
    CHECK_THROWS_WITH(updater.commit_max(), "update_max is not called before max is committed!");

    updater.update_max(-10);
    NS::Featurizers::Components::Details::NormUpdater<inputType>::MaxNormResult const & r1(updater.commit_max());
    CHECK(r1.Max_norm == 10);

    updater.update_max(-10);
    updater.update_max(1);
    updater.update_max(100);
    NS::Featurizers::Components::Details::NormUpdater<inputType>::MaxNormResult const & r2(updater.commit_max());
    CHECK(r2.Max_norm == 100);

}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
