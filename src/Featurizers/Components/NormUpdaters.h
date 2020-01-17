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

/////////////////////////////////////////////////////////////////////////
///  \enum          NormType
///  \brief         Training state associated with an `Estimator`.
///
enum class NormType : unsigned char {
    L1 = 1,                            ///> l1 norm
    L2,                               ///> l2 norm
    MAX                               ///> max norm
};

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

} // namespace TypeSelector

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

namespace Updaters{

/////////////////////////////////////////////////////////////////////////
///  \class         L1NormUpdater
///  \brief         L1NormUpdater updates l1 norm
///                 l1 norm is the sum of elements absolute value
///
template <typename T>
class L1NormUpdater {
public:

    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = T;

    // input type can only be integer or numeric
    static_assert(Traits<T>::IsIntOrNumeric::value, "Input type to norm updater has to be integer or numerical types!");

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    L1NormUpdater(void);

    void reset(void);

    void update(InputType input);

    long double commit(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    long double _l1_norm;

    // flags to check if update function is called
    // an error will be thrown if no update(input) is called before commit
    // since it doesn't make sense to create an updater and commit without any update
    bool        _update_flag;
};

/////////////////////////////////////////////////////////////////////////
///  \class         L2NormUpdater
///  \brief         L2NormUpdater updates l2 norm
///                 l2 norm is the sum of square of elements absolute value
///
template <typename T>
class L2NormUpdater {
public:

    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = T;

    // input type can only be integer or numeric
    static_assert(Traits<T>::IsIntOrNumeric::value, "Input type to norm updater has to be integer or numerical types!");

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    L2NormUpdater(void);

    void reset(void);

    void update(InputType input);

    long double commit(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    long double _l2_norm;

    // flags to check if update functions are called
    // an error will be thrown if no update(input) is called before commit
    // since it doesn't make sense to create an updater and commit without any update
    bool        _update_flag;
};


/////////////////////////////////////////////////////////////////////////
///  \class         MaxNormUpdater
///  \brief         MaxNormUpdater updates max norm
///                 max norm is the maximum absolute value of input data elements
///
template <typename T>
class MaxNormUpdater {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = T;

    // input type can only be integer or numeric
    static_assert(Traits<T>::IsIntOrNumeric::value, "Input type to norm updater has to be integer or numerical types!");

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------

    MaxNormUpdater(void);

    void reset(void);

    void update(InputType input);

    typename TypeSelector::MaxNormTypeSelector<T>::type commit(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    typename TypeSelector::MaxNormTypeSelector<T>::type _max_norm;

    // flags to check if update functions are called
    // an error will be thrown if no update(input) is called before commit
    // since it doesn't make sense to create an updater and commit without any update
    bool                                                _update_flag;
};

} // Updaters

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
// |  Updaters::L1NormUpdater
// |
// ----------------------------------------------------------------------
template <typename T>
Updaters::L1NormUpdater<T>::L1NormUpdater() {
    reset();
}

template <typename T>
void Updaters::L1NormUpdater<T>::reset() {
    _l1_norm = 0;
    _update_flag = false;
}
template <typename T>
void Updaters::L1NormUpdater<T>::update(T input) {
    if (!_update_flag) {
        _update_flag = true;
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
long double Updaters::L1NormUpdater<T>::commit(void) {
    assert(_l1_norm >= 0);
    if (!_update_flag) {
        throw std::runtime_error("update is not called before l1 is committed!");
    }
    return _l1_norm;
}
// ----------------------------------------------------------------------
// |
// |  Updaters::L2NormUpdater
// |
// ----------------------------------------------------------------------
template <typename T>
Updaters::L2NormUpdater<T>::L2NormUpdater() {
    reset();
}

template <typename T>
void Updaters::L2NormUpdater<T>::reset() {
    _l2_norm = 0;
    _update_flag = false;
}
template <typename T>
void Updaters::L2NormUpdater<T>::update(T input) {
    if (!_update_flag) {
        _update_flag = true;
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
long double Updaters::L2NormUpdater<T>::commit(void) {
    assert(_l2_norm >= 0);
    if (!_update_flag) {
        throw std::runtime_error("update is not called before l2 is committed!");
    }
    return std::sqrt(_l2_norm);
}
// ----------------------------------------------------------------------
// |
// |  Updaters::MaxNormUpdater
// |
// ----------------------------------------------------------------------
template <typename T>
Updaters::MaxNormUpdater<T>::MaxNormUpdater() {
    reset();
}

template <typename T>
void Updaters::MaxNormUpdater<T>::reset() {
    _max_norm = 0;
    _update_flag = false;
}
template <typename T>
void Updaters::MaxNormUpdater<T>::update(T input) {
    if (!_update_flag) {
        _max_norm = static_cast<typename TypeSelector::MaxNormTypeSelector<T>::type>(std::abs(input));
        _update_flag = true;
    } else {
        _max_norm = std::max(static_cast<typename TypeSelector::MaxNormTypeSelector<T>::type>(std::abs(input)), _max_norm);
    }
}


template <typename T>
typename TypeSelector::MaxNormTypeSelector<T>::type Updaters::MaxNormUpdater<T>::commit(void) {
    assert(_max_norm >= 0);
    if (!_update_flag) {
        throw std::runtime_error("update is not called before max is committed!");
    }
    return _max_norm;
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
