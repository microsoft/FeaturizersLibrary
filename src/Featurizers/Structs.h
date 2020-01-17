// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Featurizer.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         SparseVectorEncoding
///  \brief         Object that contains information that can be used to
///                 create a sparse vector without creating the vector
///                 itself.
///
template <typename T>
class SparseVectorEncoding {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using value_type                        = T;

    struct ValueEncoding {
        // ----------------------------------------------------------------------
        // |  Public Data
        value_type const                    Value;
        std::uint64_t const                 Index;

        // ----------------------------------------------------------------------
        // |  Public Methods
        ValueEncoding(value_type value, std::uint64_t index);

        bool operator==(ValueEncoding const &other) const;
        bool operator!=(ValueEncoding const &other) const;
    };

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    std::uint64_t const                     NumElements;
    std::vector<ValueEncoding> const        Values;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SparseVectorEncoding(std::uint64_t numElements, std::vector<ValueEncoding> values);

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SparseVectorEncoding);

    bool operator==(SparseVectorEncoding const &other) const;
    bool operator!=(SparseVectorEncoding const &other) const;
};

/////////////////////////////////////////////////////////////////////////
///  \class         SingleValueSparseVectorEncoding
///  \brief         Object that contains information that can be used to create
///                 a sparse vector with only a single value set without creating
///                 the vector itself.
///
template <typename T>
class SingleValueSparseVectorEncoding {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using value_type                        = T;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    std::uint64_t const                     NumElements;
    value_type const                        Value;
    std::uint64_t const                     Index;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SingleValueSparseVectorEncoding(std::uint64_t numElements, value_type value, std::uint64_t index);

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SingleValueSparseVectorEncoding);

    bool operator==(SingleValueSparseVectorEncoding const &other) const;
    bool operator!=(SingleValueSparseVectorEncoding const &other) const;
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
// |  SparseVectorEncoding::ValueEncoding
// |
// ----------------------------------------------------------------------
template <typename T>
SparseVectorEncoding<T>::ValueEncoding::ValueEncoding(value_type value, std::uint64_t index) :
    Value(std::move(value)),
    Index(std::move(index)) {
}

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

template <typename T>
bool SparseVectorEncoding<T>::ValueEncoding::operator==(ValueEncoding const &other) const {
    return Value == other.Value
        && Index == other.Index;
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

template <typename T>
bool SparseVectorEncoding<T>::ValueEncoding::operator!=(ValueEncoding const &other) const {
    return (*this == other) == false;
}

// ----------------------------------------------------------------------
// |
// |  SparseVectorEncoding
// |
// ----------------------------------------------------------------------
template <typename T>
SparseVectorEncoding<T>::SparseVectorEncoding(std::uint64_t numElements, std::vector<ValueEncoding> values) :
    NumElements(
        std::move(
            [&numElements, &values](void) -> std::uint64_t & {
                if(numElements == 0)
                    throw std::invalid_argument("'numElements' is 0");

                if(numElements < values.size())
                    throw std::invalid_argument("'numElements' is invalid");

                return numElements;
            }()
        )
    ),
    Values(
        std::move(
            [&values](void) -> std::vector<ValueEncoding> & {
                if(values.empty())
                    throw std::invalid_argument("'values' is empty");

                // Ensure that the values are ordered by index
                std::uint64_t               prevIndex(0);

                for(auto iter = values.cbegin(); iter != values.cend(); ++iter) {
                    if(iter->Index <= prevIndex && iter != values.cbegin())
                        throw std::invalid_argument("'values' is not ordered");

                    prevIndex = iter->Index;
                }

                return values;
            }()
        )
    ) {
}

template <typename T>
bool SparseVectorEncoding<T>::operator==(SparseVectorEncoding const &other) const {
    return NumElements == other.NumElements
        && Values == other.Values;
}

template <typename T>
bool SparseVectorEncoding<T>::operator!=(SparseVectorEncoding const &other) const {
    return (*this == other) == false;
}

// ----------------------------------------------------------------------
// |
// |  SingleValueSparseVectorEncoding
// |
// ----------------------------------------------------------------------
template <typename T>
SingleValueSparseVectorEncoding<T>::SingleValueSparseVectorEncoding(std::uint64_t numElements, value_type value, std::uint64_t index) :
    NumElements(
        std::move(
            [&numElements](void) -> std::uint64_t & {
                if(numElements == 0)
                    throw std::invalid_argument("'numElements' is 0");

                return numElements;
            }()
        )
    ),
    Value(std::move(value)),
    Index(
        std::move(
            [this, &index](void) -> std::uint64_t & {
                if(index >= this->NumElements)
                    throw std::invalid_argument("'index' is invalid");

                return index;
            }()
        )
    ) {
}

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

template <typename T>
bool SingleValueSparseVectorEncoding<T>::operator==(SingleValueSparseVectorEncoding const &other) const {
    return NumElements == other.NumElements
        && Value == other.Value
        && Index == other.Index;
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

template <typename T>
bool SingleValueSparseVectorEncoding<T>::operator!=(SingleValueSparseVectorEncoding const &other) const {
    return (*this == other) == false;
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
