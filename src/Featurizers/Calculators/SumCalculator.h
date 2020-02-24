// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <cmath>

#include "Calculators.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Calculators {

/////////////////////////////////////////////////////////////////////////
///  \class         SumCalculator
///  \brief         Calculator that sums all values passed in to the update
///                 method. The total sum is returned when commit is called.
///                 The starting value defaults to 0, but can be overwritten
///                 as needed. NaN values cause NaN to be returned.
///

template <typename T>
class SumCalculator : public CalculatorBase<SumCalculator<T>, T, T> {
public:
    SumCalculator(T initialValue=static_cast<T>(0)) : _initialValue(std::move(initialValue)) {
        this->reset();
    }

private:
    friend class CalculatorBase<SumCalculator<T>, T, T>;

    T const                                 _initialValue;
    T                                       _sum;

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


} // namespace Calculators
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
