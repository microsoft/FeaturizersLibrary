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

namespace TypeSelector {
// max norm type selector is created for selecting different types for max norm based on input type
// when input type is integer, uint64 is chosen for performance
// when input type is numeric, long double is chosen
template <typename T>
struct MaxNormTypeSelector {
    using type = std::uint64_t;
};
template <>
struct MaxNormTypeSelector<std::float_t> {
    using type = long double;
};

template <>
struct MaxNormTypeSelector<std::double_t> {
    using type = long double;
};

}
namespace Details{

/////////////////////////////////////////////////////////////////////////
///  \class         NormUpdater
///  \brief         NormUpdater updates l1 norm and l2 norm
///                 l1 norm is the sum of difference between elements and average
///                 l2 norm is the sum of square of difference between elements and average
///                 statistically, we have a average to calculate l2 norm for standard deviation
///                 for vectors, average is 0
///
///                 for vectors, users should use NormUpdater(void), update_max and update_l1l2
///
///                 for statistical usage, such as standard deviation, users should use StatisticsMetricsEstimator first
///                 and NormUpdater(InputType min, InputType max, std::double_t average), update_l1l2
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
        long double                                         const L1_norm;
        long double                                         const L2_norm;
        typename TypeSelector::MaxNormTypeSelector<T>::type const Max_norm;

        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        NormResult(long double l1_norm, long double l2_norm, typename TypeSelector::MaxNormTypeSelector<T>::type max_norm);
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

    // NormUpdater(void), update_max, update_l1l2 will be used in calculating l1, l2 or max norm for vectors
    // NormUpdater(InputType min, InputType max, std::double_t average), update_l1l2 will be used in calculating standard deviation for statistics
    NormUpdater(void);
    NormUpdater(std::double_t average);

    void update_max(InputType input);
    void update_l1l2(InputType input);

    // commit returns the result of min, max and count
    NormResult commit(void);
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    long double                                         _l1_norm;
    long double                                         _l2_norm;
    typename TypeSelector::MaxNormTypeSelector<T>::type _max_norm;
    bool                                                _first_element_flag;
    std::double_t const                                 _average;
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
// |  Details::NormUpdater::NormResult
// |
// ----------------------------------------------------------------------
template <typename T>
Details::NormUpdater<T>::NormResult::NormResult(long double l1_norm, long double l2_norm, typename TypeSelector::MaxNormTypeSelector<T>::type max_norm) :
    L1_norm(std::move(l1_norm)),
    L2_norm(std::move(l2_norm)),
    Max_norm(std::move(max_norm)) {
        // input type can only be integer or numeric
        static_assert(Traits<T>::IsIntOrNumeric::value, "Input type to norm updater has to be integer or numerical types!");
        if (L1_norm < 0) {
            throw std::invalid_argument("l1 norm shouldn't be less than 0!");
        }
        if (L2_norm < 0) {
            throw std::invalid_argument("l2 norm shouldn't be less than 0!");
        }
        if (Max_norm < 0) {
            throw std::invalid_argument("max norm shouldn't be less than 0!");
        }
}

// ----------------------------------------------------------------------
// |
// |  Details::NormUpdater
// |
// ----------------------------------------------------------------------

template <typename T>
Details::NormUpdater<T>::NormUpdater() :
    _l1_norm(0),
    _l2_norm(0),
    _max_norm(0),
    _first_element_flag(true),
    _average(0) {
        // min, max will be updated with update
        // since this constructor will be used in vector l1, l2 and max norms, average is set to 0
}

template <typename T>
Details::NormUpdater<T>::NormUpdater(std::double_t average) :
    _l1_norm(0),
    _l2_norm(0),
    _max_norm(0),
    _first_element_flag(true),
    _average(std::move(average)) {
        // input type can only be integer or numeric
        static_assert(Traits<T>::IsIntOrNumeric::value, "Input type to norm updater has to be integer or numerical types!");
}

template <typename T>
void Details::NormUpdater<T>::update_max(T input) {
    if (_first_element_flag) {
        _max_norm = static_cast<typename TypeSelector::MaxNormTypeSelector<T>::type>(std::abs(input));
        _first_element_flag = false;
    } else {
        _max_norm = std::max(static_cast<typename TypeSelector::MaxNormTypeSelector<T>::type>(std::abs(input)), _max_norm);
    }
}

template <typename T>
void Details::NormUpdater<T>::update_l1l2(T input) {
    long double diff = std::abs(static_cast<long double>(input) - static_cast<long double>(_average));

    // check if diff is too small comparing to l1_norm
    if ((_l1_norm + diff == _l1_norm) && (diff != 0)) {
        throw std::runtime_error("In l1 norm calculation, difference between input and average is so small comparing to l1_norm that l1_norm is the same after long double addition!");
    }
    _l1_norm += diff;

    long double diff_square = std::pow(diff, 2);


    if ((_l2_norm + diff_square == _l2_norm) && (diff_square != 0)) {
        throw std::runtime_error("In l2 norm calculation, square of difference between input and average is so small comparing to l2_norm that l2_norm is the same after long double addition!");
    }
    _l2_norm += diff_square;

    // check if exceeds bound
    // only check for l2_norm and no checks for l1_norm is because if l1_norm is out of upper bound, l2_norm is definitely out of bound
    if (std::isinf(_l2_norm)) {
        throw std::runtime_error("Overflows occured during calculating l2_norm! Check your data!");
    }
}

template <typename T>
typename Details::NormUpdater<T>::NormResult Details::NormUpdater<T>::commit(void) {
    assert(_l1_norm >= 0);
    assert(_l2_norm >= 0);
    assert(_max_norm >= 0);
    return NormResult(std::move(_l1_norm), std::move(std::sqrt(_l2_norm)), std::move(_max_norm));
}

}
}
}
}