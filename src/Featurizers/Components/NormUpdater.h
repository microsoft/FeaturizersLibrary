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

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

namespace Details{

/////////////////////////////////////////////////////////////////////////
///  \class         NormUpdater
///  \brief         NormUpdater updates l1 norm and l2 norm
///                 l1 norm is the sum of elements absolute value
///                 l2 norm is the sum of square of elements absolute value
///
template <typename T>
class NormUpdater {
public:

    /////////////////////////////////////////////////////////////////////////
    ///  \class         L1NormResult
    ///  \brief         A structure which contains the l1 norm
    ///
    struct L1NormResult {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Data
        // |
        // ----------------------------------------------------------------------
        long double                                         const L1_norm;

        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        L1NormResult(long double l1_norm);
        ~L1NormResult(void) = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(L1NormResult);
    };

    /////////////////////////////////////////////////////////////////////////
    ///  \class         L2NormResult
    ///  \brief         A structure which contains the l2 norm and max norm
    ///
    struct L2NormResult {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Data
        // |
        // ----------------------------------------------------------------------
        long double                                         const L2_norm;

        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        L2NormResult(long double l2_norm);
        ~L2NormResult(void) = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(L2NormResult);
    };


    /////////////////////////////////////////////////////////////////////////
    ///  \class         MaxNormResult
    ///  \brief         A structure which contains the max norm
    ///
    struct MaxNormResult {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Data
        // |
        // ----------------------------------------------------------------------
        typename TypeSelector::MaxNormTypeSelector<T>::type const Max_norm;

        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        MaxNormResult(typename TypeSelector::MaxNormTypeSelector<T>::type max_norm);
        ~MaxNormResult(void) = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MaxNormResult);
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

    NormUpdater(void);

    void update_l1(InputType input);
    void update_l2(InputType input);
    void update_max(InputType input);

    // commit returns the result of min, max and count
    L1NormResult commit_l1(void);
    L2NormResult commit_l2(void);
    MaxNormResult commit_max(void);
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    long double                                         _l1_norm;
    long double                                         _l2_norm;
    typename TypeSelector::MaxNormTypeSelector<T>::type _max_norm;

    // flags to check if update functions are called
    bool                                                _update_l1_flag;
    bool                                                _update_l2_flag;
    bool                                                _update_max_flag;
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
// |  Details::NormUpdater::L1NormResult
// |
// ----------------------------------------------------------------------
template <typename T>
Details::NormUpdater<T>::L1NormResult::L1NormResult(long double l1_norm) :
    L1_norm(std::move(l1_norm)) {
        // input type can only be integer or numeric
        static_assert(Traits<T>::IsIntOrNumeric::value, "Input type to norm updater has to be integer or numerical types!");
        if (L1_norm < 0) {
            throw std::invalid_argument("l1 norm shouldn't be less than 0!");
        }
}

// ----------------------------------------------------------------------
// |
// |  Details::NormUpdater::L2NormResult
// |
// ----------------------------------------------------------------------
template <typename T>
Details::NormUpdater<T>::L2NormResult::L2NormResult(long double l2_norm) :
    L2_norm(std::move(l2_norm)) {
        // input type can only be integer or numeric
        static_assert(Traits<T>::IsIntOrNumeric::value, "Input type to norm updater has to be integer or numerical types!");
        if (L2_norm < 0) {
            throw std::invalid_argument("l2 norm shouldn't be less than 0!");
        }
}

// ----------------------------------------------------------------------
// |
// |  Details::NormUpdater::MaxNormResult
// |
// ----------------------------------------------------------------------
template <typename T>
Details::NormUpdater<T>::MaxNormResult::MaxNormResult(typename TypeSelector::MaxNormTypeSelector<T>::type max_norm) :
    Max_norm(std::move(max_norm)) {
        // input type can only be integer or numeric
        static_assert(Traits<T>::IsIntOrNumeric::value, "Input type to norm updater has to be integer or numerical types!");
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
    _update_l1_flag(false),
    _update_l2_flag(false),
    _update_max_flag(false) {
        // input type can only be integer or numeric
        static_assert(Traits<T>::IsIntOrNumeric::value, "Input type to norm updater has to be integer or numerical types!");
}

template <typename T>
void Details::NormUpdater<T>::update_max(T input) {
    if (!_update_max_flag) {
        _max_norm = static_cast<typename TypeSelector::MaxNormTypeSelector<T>::type>(std::abs(input));
        _update_max_flag = true;
    } else {
        _max_norm = std::max(static_cast<typename TypeSelector::MaxNormTypeSelector<T>::type>(std::abs(input)), _max_norm);
    }
}
template <typename T>
void Details::NormUpdater<T>::update_l1(T input) {
    if (!_update_l1_flag) {
        _update_l1_flag = true;
    }
    long double diff = std::abs(static_cast<long double>(input));

    // check if diff is too small comparing to l1_norm
    if ((_l1_norm + diff == _l1_norm) && (diff != 0)) {
        throw std::runtime_error("In l1 norm calculation, input is so small comparing to l1_norm that l1_norm is the same after long double addition!");
    }
    _l1_norm += diff;

    // check if exceeds bound
    // only check for l2_norm and no checks for l1_norm is because if l1_norm is out of upper bound, l2_norm is definitely out of bound
    if (std::isinf(_l1_norm)) {
        throw std::runtime_error("Overflows occured during calculating l1_norm! Check your data!");
    }
}

template <typename T>
void Details::NormUpdater<T>::update_l2(T input) {
    if (!_update_l2_flag) {
        _update_l2_flag = true;
    }
    long double diff_square = std::pow(std::abs(static_cast<long double>(input)), 2);

    if ((_l2_norm + diff_square == _l2_norm) && (diff_square != 0)) {
        throw std::runtime_error("In l2 norm calculation, square of input is so small comparing to l2_norm that l2_norm is the same after long double addition!");
    }
    _l2_norm += diff_square;

    // check if exceeds bound
    // only check for l2_norm and no checks for l1_norm is because if l1_norm is out of upper bound, l2_norm is definitely out of bound
    if (std::isinf(_l2_norm)) {
        throw std::runtime_error("Overflows occured during calculating l2_norm! Check your data!");
    }
}

template <typename T>
typename Details::NormUpdater<T>::L1NormResult Details::NormUpdater<T>::commit_l1(void) {
    assert(_l1_norm >= 0);
    if (!_update_l1_flag) {
        throw std::runtime_error("update_l1 is not called before l1 is committed!");
    }
    return L1NormResult(std::move(_l1_norm));
}

template <typename T>
typename Details::NormUpdater<T>::L2NormResult Details::NormUpdater<T>::commit_l2(void) {
    assert(_l2_norm >= 0);
    if (!_update_l2_flag) {
        throw std::runtime_error("update_l2 is not called before l2 is committed!");
    }
    return L2NormResult(std::move(std::sqrt(_l2_norm)));
}
template <typename T>
typename Details::NormUpdater<T>::MaxNormResult Details::NormUpdater<T>::commit_max(void) {
    assert(_max_norm >= 0);
    if (!_update_max_flag) {
        throw std::runtime_error("update_max is not called before max is committed!");
    }
    return MaxNormResult(std::move(_max_norm));
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

}
}
}
}
