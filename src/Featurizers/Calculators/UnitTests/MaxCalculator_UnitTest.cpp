// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN

#include <limits>

#include "catch.hpp"
#include "../MaxCalculator.h"

namespace NS = Microsoft::Featurizer::Featurizers::Calculators;

TEST_CASE("Standard - int") {
    NS::MaxCalculator<int>                      calc;

    calc.update(1);
    calc.update(5);

    CHECK(calc.commit() == 5);

    calc.update(3);
    CHECK(calc.commit() == 5);

    calc.update(7);
    CHECK(calc.commit() == 7);

    calc.reset();
    CHECK(calc.commit() == std::numeric_limits<int>::min());

    calc.update(10);
    CHECK(calc.commit() == 10);
}

TEST_CASE("Standard - double") {
    NS::MaxCalculator<double>                   calc;

    calc.update(1.0);
    calc.update(5.0);

    CHECK(calc.commit() == 5.0);

    calc.update(3.0);
    CHECK(calc.commit() == 5.0);

    calc.update(7.0);
    CHECK(calc.commit() == 7.0);

    calc.reset();
    CHECK(calc.commit() == std::numeric_limits<double>::min());

    calc.update(10);
    CHECK(calc.commit() == 10.0);
}

TEST_CASE("All negative - int") {
    NS::MaxCalculator<int>                      calc;

    calc.update(-10);
    calc.update(-20);

    CHECK(calc.commit() == -10);

    calc.update(-1);
    CHECK(calc.commit() == -1);

    calc.reset();
    CHECK(calc.commit() == std::numeric_limits<int>::min());

    calc.update(-3);
    CHECK(calc.commit() == -3);
}

TEST_CASE("execute") {
    std::vector<int> const                  values{1, 10, 3, 20, -1};

    CHECK(NS::MaxCalculator<int>::execute(values.begin(), values.end()) == 20);
}
