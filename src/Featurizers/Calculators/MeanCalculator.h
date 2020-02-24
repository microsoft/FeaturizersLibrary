// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Calculators.h"
#include "SumCalculator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Calculators {

/////////////////////////////////////////////////////////////////////////
///  \class         MeanCalculator
///  \brief         Calculator that finds the mean of all values 
///                 passed in to the update method. The mean is returned
///                 when commit is called. If commit is called when no values
///                 have been passed in then 0 is returned.
///

template <typename T>
class MeanCalculator : public CalculatorBase<MeanCalculator<T>, T, double> {
public:
    MeanCalculator() {
        this->reset();
    }

private:
    friend class CalculatorBase<MeanCalculator<T>, T, double>;
    SumCalculator<T>                            _sumCalc;
    size_t                                      _count;

    inline void update_impl(T value) {
        _sumCalc.update(value);
        _count++;
    }

    inline double commit_impl(void) {
        if (_count == 0){
            return 0;
        }
        return static_cast<double>(_sumCalc.commit()) / _count;
    }

    inline void reset_impl(void) {
        _sumCalc.reset();
        _count = 0;
    }
};

} // namespace Calculators
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
