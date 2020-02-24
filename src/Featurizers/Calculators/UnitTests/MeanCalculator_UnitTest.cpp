// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN

#include <limits>

#include "catch.hpp"
#include "../MeanCalculator.h"

namespace NS = Microsoft::Featurizer::Featurizers::Calculators;

TEST_CASE("Standard - int") {
    NS::MeanCalculator<int>                      calc;

    calc.update(5);
    calc.update(3);

    CHECK(calc.commit() == Approx(4.0));

    calc.update(1);
    CHECK(calc.commit() == Approx(3.0));

    calc.update(1);
    CHECK(calc.commit() == Approx(2.5));

    calc.reset();
    CHECK(calc.commit() == Approx(0.0));

    calc.update(10);
    CHECK(calc.commit() == Approx(10.0));
}

TEST_CASE("Standard - double") {
    NS::MeanCalculator<double>                   calc;

    calc.update(5.0);
    calc.update(3.0);

    CHECK(calc.commit() == Approx(4.0));

    calc.update(1.0);
    CHECK(calc.commit() == Approx(3.0));

    calc.update(1.0);
    CHECK(calc.commit() == Approx(2.5));

    calc.reset();
    CHECK(calc.commit() == Approx(0.0));

    calc.update(10);
    CHECK(calc.commit() == Approx(10.0));
}

TEST_CASE("execute") {
    std::vector<int> const                  values{1, 10, -1, 8, 7};

    CHECK(NS::MeanCalculator<int>::execute(values.begin(), values.end()) == Approx(5.0));
}
