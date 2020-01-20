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

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    L1NormUpdater(void);

    void reset(void);

    void update(T input);

    long double commit(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    long double _l1_norm;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void update_impl(InputType const &input, std::true_type /*is_nullable*/);
    void update_impl(InputType const &input, std::false_type /*is_nullable*/);

    template <typename U>
    void update_impl(U const &input);
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

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    L2NormUpdater(void);

    void reset(void);

    void update(T input);

    long double commit(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    long double _l2_norm;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void update_impl(InputType const &input, std::true_type /*is_nullable*/);
    void update_impl(InputType const &input, std::false_type /*is_nullable*/);

    template <typename U>
    void update_impl(U const &input);
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

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------

    MaxNormUpdater(void);

    void reset(void);

    void update(T input);

    typename TypeSelector::MaxNormTypeSelector<T>::type commit(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    typename TypeSelector::MaxNormTypeSelector<T>::type _max_norm;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void update_impl(InputType const &input, std::true_type /*is_nullable*/);
    void update_impl(InputType const &input, std::false_type /*is_nullable*/);

    template <typename U>
    void update_impl(U const &input);
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
}

template <typename T>
void Updaters::L1NormUpdater<T>::update(T const& input) {
    update_impl(input, std::integral_constant<bool, Traits<T>::IsNullableType>());
}

template <typename T>
void Updaters::L1NormUpdater<T>::update_impl(T const &input, std::true_type /*is_nullable*/) {
    if (Traits<T>::IsNull(input)) {
        return;
    }

    update_impl(Traits<T>::GetNullableValue(input));
}


template <typename T>
void Updaters::L1NormUpdater<T>::update_impl(T const &input, std::false_type /*is_nullable*/) {
    update_impl(input);
}

template <typename T>
template <typename U>
void Updaters::L1NormUpdater<T>::update_impl(U const &input) {
    
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
}
template <typename T>
void Updaters::L2NormUpdater<T>::update(T const& input) {
    update_impl(input, std::integral_constant<bool, Traits<T>::IsNullableType>());
}

template <typename T>
void Updaters::L2NormUpdater<T>::update_impl(T const &input, std::true_type /*is_nullable*/) {
    if (Traits<T>::IsNull(input)) {
        return;
    }

    update_impl(Traits<T>::GetNullableValue(input));
}


template <typename T>
void Updaters::L2NormUpdater<T>::update_impl(T const &input, std::false_type /*is_nullable*/) {
    update_impl(input);
}

template <typename T>
template <typename U>
void Updaters::L2NormUpdater<T>::update_impl(U const &input) {
    
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
}
template <typename T>
void Updaters::MaxNormUpdater<T>::update(T const& input) {
    update_impl(input, std::integral_constant<bool, Traits<T>::IsNullableType>());
}

template <typename T>
void Updaters::MaxNormUpdater<T>::update_impl(T const &input, std::true_type /*is_nullable*/) {
    if (Traits<T>::IsNull(input)) {
        return;
    }

    update_impl(Traits<T>::GetNullableValue(input));
}


template <typename T>
void Updaters::MaxNormUpdater<T>::update_impl(T const &input, std::false_type /*is_nullable*/) {
    update_impl(input);
}

template <typename T>
template <typename U>
void Updaters::MaxNormUpdater<T>::update_impl(U const &input) {
    _max_norm = std::max(static_cast<typename TypeSelector::MaxNormTypeSelector<T>::type>(std::abs(input)), _max_norm);
}


template <typename T>
typename TypeSelector::MaxNormTypeSelector<T>::type Updaters::MaxNormUpdater<T>::commit(void) {
    assert(_max_norm >= 0);
    return _max_norm;
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
