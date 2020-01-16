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
struct OneHotStruct {
    std::uint32_t const Index;                                    // category index
    std::uint32_t const Size;                                     // category total size
    std::uint32_t const Appearances;                              // number of appearances

    OneHotStruct(std::uint32_t index, std::uint32_t size, std::uint32_t appearances);
    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(OneHotStruct);
    bool operator==(OneHotStruct const &other) const;
}

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
///  \struct        TFStruct
///  \brief         Struct to hold return value of count vectorizer,
///                 consist of <dictid, # of appearances>
///
struct TFStruct {
    std::uint32_t const DictionaryId;                              // dict id
    std::uint32_t const Appearances;                               // number of appearances

    TFStruct(std::uint32_t dictionaryid, std::uint32_t appearances);
    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TFStruct);
    bool operator==(TFStruct const &other) const;
};

/////////////////////////////////////////////////////////////////////////
///  \struct        TFIDFStruct
///  \brief         Struct to hold return value of tfidf vectorizer,
///                 consist of <dictid, tfidf value>
///
struct TFIDFStruct {
    std::uint32_t const DictionaryId;                              // dict id
    std::float_t const Tfidf;                                      // freq

    TFIDFStruct(std::uint32_t dictionaryid, std::float_t tfidf);
    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TFIDFStruct);
    bool operator==(TFIDFStruct const &other) const;
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
  
OneHotStruct::OneHotStruct(std::uint32_t index, std::uint32_t size, std::uint32_t appearances) :
    Index(std::move(index)),
    Size(std::move(size)),
    Appearances(std::move(appearances)) {
        if (Index >= Size) {
            throw std::invalid_argument("Category index should be smaller than total number of categories!");
        }
}

bool OneHotStruct::operator==(OneHotStruct const &other) const {
    return (Appearances == other.Appearances) && (Index == other.Index) && (Size == other.Size);
}


// ----------------------------------------------------------------------
// |
// |  TFStruct
// |
// ----------------------------------------------------------------------
TFStruct::TFStruct(std::uint32_t dictionaryid, std::uint32_t appearances) :
    DictionaryId(std::move(dictionaryid)),
    Appearances(std::move(appearances)) {
}

bool TFStruct::operator==(TFStruct const &other) const {
    return (Appearances == other.Appearances) && (DictionaryId == other.DictionaryId);
}


// ----------------------------------------------------------------------
// |
// |  TFIDFStruct
// |
// ----------------------------------------------------------------------
TFIDFStruct::TFIDFStruct(std::uint32_t dictionaryid, std::float_t tfidf) :
    DictionaryId(std::move(dictionaryid)),
    Tfidf(std::move(tfidf)) {
}

bool TFIDFStruct::operator==(TFIDFStruct const &other) const {
    return (DictionaryId == other.DictionaryId) && (abs(Tfidf - other.Tfidf) < 0.000001f);
}



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
