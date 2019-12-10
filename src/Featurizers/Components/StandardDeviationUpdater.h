// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "NormUpdater.h"
namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

namespace Details{

/////////////////////////////////////////////////////////////////////////
///  \class         STDUpdater
///  \brief         STDUpdater uses NormUpdater to update standard deviation
///
template <typename T>
class STDUpdater {
public:

    /////////////////////////////////////////////////////////////////////////
    ///  \class         STDResult
    ///  \brief         A structure which contains the standard deviation
    ///
    struct STDResult {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Data
        // |
        // ----------------------------------------------------------------------
        long double const StandardDeviation;

        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        STDResult(long double standard_deviation);
        ~STDResult(void) = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(STDResult);
    };

    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = T;


    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    STDUpdater(std::double_t average, std::uint64_t count);

    void update(InputType input);

    STDResult commit(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::double_t  const _average;
    std::uint64_t  const _count;
    NormUpdater<std::double_t> _updater;
};

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Implementation
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// |
// |  Details::STDUpdater::STDResult
// |
// ----------------------------------------------------------------------

template <typename T>
Details::STDUpdater<T>::STDResult::STDResult(long double standard_deviation) :
    StandardDeviation(std::move(standard_deviation)) {
        // input type can only be integer or numeric
        static_assert(Traits<T>::IsIntOrNumeric::value, "Input type to standard deviation updater has to be integer or numerical types!");
        if (StandardDeviation < 0) {
            throw std::invalid_argument("Standard deviation shouldn't be less than 0!");
        }
}

// ----------------------------------------------------------------------
// |
// |  Details::STDUpdater
// |
// ----------------------------------------------------------------------

template <typename T>
Details::STDUpdater<T>::STDUpdater(std::double_t average, std::uint64_t count) :
    _average(average),
    _count(count),
    _updater(NormUpdater<std::double_t>()) {
        // input type can only be integer or numeric
        static_assert(Traits<T>::IsIntOrNumeric::value, "Input type to standard deviation updater has to be integer or numerical types!");
        if (_count == 0) {
            throw std::invalid_argument("Count is 0 when constructing STDUpdater to calculate standard deviation!");
        }
}

template <typename T>
void Details::STDUpdater<T>::update(T input) {
    _updater.update_l2(static_cast<std::double_t>(input) - _average);
}

template <typename T>
typename Details::STDUpdater<T>::STDResult Details::STDUpdater<T>::commit(void) {
    long double const & l2(_updater.commit_l2().L2_norm);
    return STDResult(std::move(l2/_count));
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif



}
}
}
}
}
