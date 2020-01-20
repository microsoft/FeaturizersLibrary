// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"
#include "../NormUpdaters.h"
namespace NS = Microsoft::Featurizer;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

// updater tests

TEST_CASE("l1 updater normal cases") {
    using inputType = int;
    NS::Featurizers::Components::Updaters::L1NormUpdater<inputType> updater;
    long double const r0(updater.commit());
    CHECK(r0 == 0);

    updater.update(0);
    long double const r1(updater.commit());
    CHECK(r1 == 0);

    updater.update(1);
    updater.update(2);
    updater.update(3);
    long double const r2(updater.commit());
    CHECK(r2 == 6);

    updater.reset();
    long double const r3(updater.commit());
    CHECK(r3 == 0);
}

TEST_CASE("l1 updater null values") {
    using inputType = nonstd::optional<int>;
    NS::Featurizers::Components::Updaters::L1NormUpdater<inputType> updater;
    long double const r0(updater.commit());
    CHECK(r0 == 0);

    updater.update(0);
    long double const r1(updater.commit());
    CHECK(r1 == 0);

    updater.update(1);
    updater.update(nonstd::optional<int>());
    updater.update(2);
    updater.update(3);
    long double const r2(updater.commit());
    CHECK(r2 == 6);
}


TEST_CASE("l1 updater overflow") {
    using inputType = std::double_t;
    NS::Featurizers::Components::Updaters::L1NormUpdater<inputType> updater;
    updater.update(std::numeric_limits<inputType>::max());
    CHECK_THROWS_WITH(updater.update(1), "In l1 norm calculation, input is so small comparing to l1_norm that l1_norm is the same after long double addition!");
}

TEST_CASE("l2 updater normal cases") {
    using inputType = int;
    NS::Featurizers::Components::Updaters::L2NormUpdater<inputType> updater;
    long double const r0(updater.commit());
    CHECK(r0 == 0);

    updater.update(2);
    long double const r1(updater.commit());
    CHECK(r1 == 2);

    updater.update(1);
    updater.update(2);
    updater.update(4);
    long double const r2(updater.commit());
    CHECK(r2 == 5);

    updater.reset();
    long double const r3(updater.commit());
    CHECK(r3 == 0);
}

TEST_CASE("l2 updater null values") {
    using inputType = nonstd::optional<int>;
    NS::Featurizers::Components::Updaters::L2NormUpdater<inputType> updater;
    long double const r0(updater.commit());
    CHECK(r0 == 0);

    updater.update(2);
    long double const r1(updater.commit());
    CHECK(r1 == 2);

    updater.update(1);
    updater.update(2);
    updater.update(nonstd::optional<int>());
    updater.update(4);
    long double const r2(updater.commit());
    CHECK(r2 == 5);

    updater.reset();
    long double const r3(updater.commit());
    CHECK(r3 == 0);
}

TEST_CASE("l2 updater overflow") {
    using inputType = std::double_t;
    NS::Featurizers::Components::Updaters::L2NormUpdater<inputType> updater;
    updater.update(std::sqrt(std::numeric_limits<inputType>::max()));
    CHECK_THROWS_WITH(updater.update(1), "In l2 norm calculation, square of input is so small comparing to l2_norm that l2_norm is the same after long double addition!");
}

TEST_CASE("max updater") {
    using inputType = int;
    NS::Featurizers::Components::Updaters::MaxNormUpdater<inputType> updater;
    long double const r0(updater.commit());
    CHECK(r0 == 0);

    updater.update(-10);
    std::uint64_t const r1(updater.commit());
    CHECK(r1 == 10);

    updater.update(-10);
    updater.update(1);
    updater.update(100);
    std::uint64_t const r2(updater.commit());
    CHECK(r2 == 100);

    updater.reset();
    long double const r3(updater.commit());
    CHECK(r3 == 0);
}
TEST_CASE("max updater null values") {
    using inputType = nonstd::optional<int>;
    NS::Featurizers::Components::Updaters::MaxNormUpdater<inputType> updater;
    long double const r0(updater.commit());
    CHECK(r0 == 0);

    updater.update(-10);
    std::uint64_t const r1(updater.commit());
    CHECK(r1 == 10);

    updater.update(-10);
    updater.update(1);
    updater.update(nonstd::optional<int>());
    updater.update(100);
    std::uint64_t const r2(updater.commit());
    CHECK(r2 == 100);

    updater.reset();
    long double const r3(updater.commit());
    CHECK(r3 == 0);
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
