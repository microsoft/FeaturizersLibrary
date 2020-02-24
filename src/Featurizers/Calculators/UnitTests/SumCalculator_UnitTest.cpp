// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../SumCalculator.h"

namespace NS = Microsoft::Featurizer::Featurizers::Calculators;

TEST_CASE("Standard - int") {
    NS::SumCalculator<int>                      calc;

    calc.update(1);
    calc.update(2);

    CHECK(calc.commit() == 3);

    calc.update(3);
    CHECK(calc.commit() == 6);

    calc.reset();
    CHECK(calc.commit() == 0);

    calc.update(10);
    CHECK(calc.commit() == 10);
}

TEST_CASE("Standard - double") {
    NS::SumCalculator<double>                   calc;

    calc.update(1.0);
    calc.update(2.0);

    CHECK(calc.commit() == Approx(3.0));

    calc.update(3.0);
    CHECK(calc.commit() == Approx(6.0));

    calc.reset();
    CHECK(calc.commit() == Approx(0.0));

    calc.update(10);
    CHECK(calc.commit() == Approx(10.0));
}

TEST_CASE("With initial value") {
    NS::SumCalculator<int>                      calc(10);

    CHECK(calc.commit() == 10);

    calc.update(1);
    calc.update(2);

    CHECK(calc.commit() == 13);

    calc.reset();
    CHECK(calc.commit() == 10);

    calc.update(100);
    CHECK(calc.commit() == 110);
}

TEST_CASE("execute") {
    std::vector<int> const                  values{1, 2, 3, 4, 5};

    CHECK(NS::SumCalculator<int>::execute(values.begin(), values.end()) == 15);
}

TEST_CASE("execute with default") {
    std::vector<int> const                  values{1, 2, 3, 4, 5};

    CHECK(NS::SumCalculator<int>::execute(values.begin(), values.end(), 100) == 115);
}
