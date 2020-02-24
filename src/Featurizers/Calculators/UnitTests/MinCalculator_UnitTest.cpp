// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN

#include <limits>

#include "catch.hpp"
#include "../MinCalculator.h"

namespace NS = Microsoft::Featurizer::Featurizers::Calculators;

TEST_CASE("Standard - int") {
    NS::MinCalculator<int>                      calc;

    calc.update(5);
    calc.update(3);

    CHECK(calc.commit() == 3);

    calc.update(4);
    CHECK(calc.commit() == 3);

    calc.update(1);
    CHECK(calc.commit() == 1);

    calc.reset();
    CHECK(calc.commit() == std::numeric_limits<int>::max());

    calc.update(10);
    CHECK(calc.commit() == 10);
}

TEST_CASE("Standard - double") {
    NS::MinCalculator<double>                   calc;

    calc.update(5.0);
    calc.update(3.0);

    CHECK(calc.commit() == Approx(3.0));

    calc.update(4.0);
    CHECK(calc.commit() == Approx(3.0));

    calc.update(1.0);
    CHECK(calc.commit() == Approx(1.0));

    calc.reset();
    CHECK(calc.commit() == Approx(std::numeric_limits<double>::max()));

    calc.update(10);
    CHECK(calc.commit() == Approx(10.0));
}

TEST_CASE("All negative - int") {
    NS::MinCalculator<int>                      calc;

    calc.update(-10);
    calc.update(-20);

    CHECK(calc.commit() == -20);

    calc.update(-1);
    CHECK(calc.commit() == -20);

    calc.reset();
    CHECK(calc.commit() == std::numeric_limits<int>::max());

    calc.update(-3);
    CHECK(calc.commit() == -3);
}

TEST_CASE("execute") {
    std::vector<int> const                  values{1, 10, -1, 20, 3};

    CHECK(NS::MinCalculator<int>::execute(values.begin(), values.end()) == -1);
}
