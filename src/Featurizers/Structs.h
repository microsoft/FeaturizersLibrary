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

    bool operator==(SingleValueSparseVectorEncoding const &other) const;
    bool operator!=(SingleValueSparseVectorEncoding const &other) const;
};


/////////////////////////////////////////////////////////////////////////

///  \class        CSREncoding
///  \brief         Struct that contains information that can be used to
///                 create a sparse matrix without creating the matrix
///                 itself. We are using Compressed Sparse Row form
///                 in this case.
///
///                 CSREncoding contains three vectors to express a
///                 sparse matrix:
///                 V contains all non-zero element values,
///                 ColIndex contains column indices of non-zero values,
///                 RowIndex has one element per row in the matrix and encodes
///                 the index in V where the given row starts
///

template <typename T>
class CSREncoding {
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

    std::vector<value_type>          Values;
    std::vector<std::uint64_t>       ColIndex;
    std::vector<std::uint64_t>       RowIndex;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CSREncoding();
    CSREncoding(std::vector<value_type> values, std::vector<std::uint64_t> col, std::vector<std::uint64_t> row);

    bool operator==(CSREncoding const &other) const;
    bool operator!=(CSREncoding const &other) const;
};

/////////////////////////////////////////////////////////////////////////
///  \enum          NormType
///  \brief         Training state associated with an `Estimator`.
///
enum class NormType : unsigned char {
    L1 = 1,                            ///> l1 norm
    L2,                               ///> l2 norm
    MAX                               ///> max norm
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


// ----------------------------------------------------------------------
// |
// |  CSREncoding
// |
// ----------------------------------------------------------------------
template <typename T>
CSREncoding<T>::CSREncoding() {
    RowIndex.push_back(0);
}

template <typename T>
CSREncoding<T>::CSREncoding(std::vector<value_type> values, std::vector<std::uint64_t> col, std::vector<std::uint64_t> row) :
    Values(std::move(values)),
    ColIndex(std::move(col)),
    RowIndex(std::move(row)) {
        if(RowIndex[0] != 0) {
            throw std::invalid_argument("Row index array should start with 0!");
        }

        if(Values.size() != ColIndex.size()) {
            throw std::invalid_argument("Non-zero values array and column index array should have same size!");
        }

        if(RowIndex.back() > ColIndex.size()) {
            throw std::invalid_argument("Last value of row index should be less than the size of column index array");
        }
}

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

template <typename T>
bool CSREncoding<T>::operator==(CSREncoding const &other) const {
    return Values == other.Values
        && ColIndex == other.ColIndex
        && RowIndex == other.RowIndex;
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

template <typename T>
bool CSREncoding<T>::operator!=(CSREncoding const &other) const {
    return (*this == other) == false;
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
