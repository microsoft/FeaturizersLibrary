// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "NormUpdaters.h"
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
///                 STDUpdater also keeps track of the count of input elements
///
template <typename T>
class STDUpdater {
public:

    /////////////////////////////////////////////////////////////////////////
    ///  \class         STDResult
    ///  \brief         A structure which contains the standard deviation
    ///                 and the count of input elements
    ///
    struct STDResult {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Data
        // |
        // ----------------------------------------------------------------------
        long double   const StandardDeviation;
        std::uint64_t const Count;
        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        STDResult(long double standard_deviation, std::uint64_t counter);
        ~STDResult(void) = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(STDResult);
    };

    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType              = T;


    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    STDUpdater(std::double_t average);

    void update(InputType input);

    STDResult commit(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::double_t const          _average;
    std::uint64_t                _counter;
    L2NormUpdater<std::double_t> _updater;
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
Details::STDUpdater<T>::STDResult::STDResult(long double standard_deviation, std::uint64_t counter) :
    StandardDeviation(std::move(standard_deviation)),
    Count(std::move(counter)) {
        // input type can only be integer or numeric
        static_assert(Traits<T>::IsIntOrNumeric::value, "Input type to standard deviation updater has to be integer or numerical types!");
        if (StandardDeviation < 0) {
            throw std::invalid_argument("Standard deviation shouldn't be less than 0!");
        }
        if ((Count == 0) && (StandardDeviation != 0)) {
            throw std::invalid_argument("Standard deviation is not 0 when count is 0!");
        }
}

// ----------------------------------------------------------------------
// |
// |  Details::STDUpdater
// |
// ----------------------------------------------------------------------

template <typename T>
Details::STDUpdater<T>::STDUpdater(std::double_t average) :
    _average(average),
    _counter(0),
    _updater(L2NormUpdater<std::double_t>()) {
        // input type can only be integer or numeric
        static_assert(Traits<T>::IsIntOrNumeric::value, "Input type to standard deviation updater has to be integer or numerical types!");
}

template <typename T>
void Details::STDUpdater<T>::update(T input) {
    _updater.update_l2(static_cast<std::double_t>(input) - _average);
    // check if count will be out of bounds
    if (std::numeric_limits<std::uint64_t>::max() == _counter) {
        throw std::runtime_error("Overflow occured for count during calculating standard deviation! You might input too much data");
    }
    ++_counter;
}

template <typename T>
typename Details::STDUpdater<T>::STDResult Details::STDUpdater<T>::commit(void) {
    long double const l2(_updater.commit_l2().L2_norm);
    return STDResult(std::move(l2/_counter), std::move(_counter));
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif



}
}
}
}
}
