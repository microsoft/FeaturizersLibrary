// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>

#include "Calculators.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Calculators {

/////////////////////////////////////////////////////////////////////////
///  \class         MaxCalculator
///  \brief         Calculator that finds the maximum value of all values 
///                 passed in to the update method. The maximum value is returned
///                 when commit is called. The starting value is equal to
///                 std::numeric_limits<T>::min(), where T is the input type.
///

template <typename T>
class MaxCalculator : public CalculatorBase<MaxCalculator<T>, T, T> {
public:
    MaxCalculator() {
        this->reset();
    }

private:
    friend class CalculatorBase<MaxCalculator<T>, T, T>;

    T                                       _maxValue;

    inline void update_impl(T value) {
        if(value > _maxValue) {
            _maxValue = value;
        }
    }

    inline T commit_impl(void) {
        return _maxValue;
    }

    inline void reset_impl(void) {
        _maxValue = std::numeric_limits<T>::min();
    }
};

} // namespace Calculators
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
