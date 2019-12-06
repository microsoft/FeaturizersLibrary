// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>

#include "../../Traits.h"
namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {
namespace Details{

/////////////////////////////////////////////////////////////////////////
///  \class         NormUpdater
///  \brief         NormUpdater updates l1 norm and l2 norm
///                 l1 norm is the sum of difference between elements and average
///                 l2 norm is the sum of square of difference between elements and average
///                 statistically, we have a average to calculate l2 norm for standard deviation
///                 for vectors, average is 0
///
template <typename T>
class NormUpdater {
public:
    /////////////////////////////////////////////////////////////////////////
    ///  \class         NormResult
    ///  \brief         A structure which contains the l1 norm, l2 norm and max norm
    ///
    struct NormResult {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Data
        // |
        // ----------------------------------------------------------------------
        long double const L1_norm;
        long double const L2_norm;
        T           const Max_norm;

        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        NormResult(long double l1_norm, long double l2_norm, T max_norm);
        ~NormResult(void) = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(NormResult);
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
    NormUpdater(InputType min, InputType max, std::double_t average);

    void update(InputType input);
    // commit returns the result of min, max and count
    NormResult commit(void);
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    long double                    _l1_norm;
    long double                    _l2_norm;
    InputType     const            _min;
    InputType     const            _max;
    std::double_t const            _average;
};
}

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
// |  Details::NormUpdater
// |
// ----------------------------------------------------------------------
template <typename T>
Details::NormUpdater<T>::NormResult::NormResult(long double l1_norm, long double l2_norm, T max_norm) :
    L1_norm(std::move(l1_norm)),
    L2_norm(std::move(l2_norm)),
    Max_norm(std::move(max_norm)) {
        if (L2_norm < 0) {
            throw std::invalid_argument("l2 norm shouldn't be less than 0!");
        }
}

template <typename T>
Details::NormUpdater<T>::NormUpdater(InputType min, InputType max, std::double_t average, std::uint64_t count) :
    _min(std::move(min)),
    _max(std::move(max)),
    _average(std::move(average)) {
        if (_average > _max || _average < _min) {
            throw std::invalid_argument("Average is not in the correct range!");
        }
}

template <typename T>
void Details::NormUpdater<T>::update(T input) {

}

template <typename T>
typename Details::NormUpdater<T>::NormResult Details::NormUpdater<T>::commit(void) {

}

}
}
}
}