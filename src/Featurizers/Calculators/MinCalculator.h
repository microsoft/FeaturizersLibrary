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
///  \class         MinCalculator
///  \brief         Calculator that finds the minimum value of all values 
///                 passed in to the update method. The minimum value is returned
///                 when commit is called. The starting value is equal to
///                 std::numeric_limits<T>::max(), where T is the input type.
///

template <typename T>
class MinCalculator : public CalculatorBase<MinCalculator<T>, T, T> {
public:
    MinCalculator() {
        this->reset();
    }

private:
    friend class CalculatorBase<MinCalculator<T>, T, T>;

    T                                       _minValue;

    inline void update_impl(T value) {
        if(value < _minValue) {
            _minValue = value;
        }
    }

    inline T commit_impl(void) {
        return _minValue;
    }

    inline void reset_impl(void) {
        _minValue = std::numeric_limits<T>::max();
    }
};

} // namespace Calculators
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
