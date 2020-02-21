// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Calculators.h"

namespace NS = Microsoft::Featurizer;

template <typename T>
class SumCalculator : public NS::Featurizers::Calculators::CalculatorBase<SumCalculator<T>, T, T> {
public:
    SumCalculator(T initialValue=static_cast<T>(0)) : _initialValue(std::move(initialValue)) {
        this->reset();
    }

private:
    friend class NS::Featurizers::Calculators::CalculatorBase<SumCalculator<T>, T, T>;

    T const                                 _initialValue;
    T                                       _sum;

    // Comment out any of the following methods to trigger a static_assert from CalculatorBase
    inline void update_impl(T value) {
        _sum += value;
    }

    inline T commit_impl(void) {
        return _initialValue + _sum;
    }

    inline void reset_impl(void) {
        _sum = static_cast<T>(0);
    }
};

TEST_CASE("Standard - int") {
    SumCalculator<int>                      calc;

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
    SumCalculator<double>                   calc;

    calc.update(1.0);
    calc.update(2.0);

    CHECK(calc.commit() == 3.0);

    calc.update(3.0);
    CHECK(calc.commit() == 6.0);

    calc.reset();
    CHECK(calc.commit() == 0.0);

    calc.update(10);
    CHECK(calc.commit() == 10.0);
}

TEST_CASE("With initial value") {
    SumCalculator<int>                      calc(10);

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

    CHECK(SumCalculator<int>::execute(values.begin(), values.end()) == 15);
}

TEST_CASE("execute with default") {
    std::vector<int> const                  values{1, 2, 3, 4, 5};

    CHECK(SumCalculator<int>::execute(values.begin(), values.end(), 100) == 115);
}
