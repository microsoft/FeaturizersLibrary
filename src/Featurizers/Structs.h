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
///  \struct        OneHotStruct
///  \brief         Struct to hold return value of one hot encoder,
///                 consist of <category index, total size of category, # of appearances>
///
struct OneHotStruct {
    std::uint32_t const index;                                    // category index
    std::uint32_t const size;                                     // category total size
    std::uint32_t const appearances;                              // number of appearances

    OneHotStruct(std::uint32_t i, std::uint32_t s, std::uint32_t a);
    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(OneHotStruct);
    bool operator==(OneHotStruct const &other) const;
};

/////////////////////////////////////////////////////////////////////////
///  \struct        TFStruct
///  \brief         Struct to hold return value of count vectorizer,
///                 consist of <dictid, # of appearances>
///
struct TFStruct {
    std::uint32_t const dictionaryId;                              // dict id
    std::uint32_t const appearances;                               // number of appearances

    TFStruct(std::uint32_t d, std::uint32_t a);
    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TFStruct);
    bool operator==(TFStruct const &other) const;
};

/////////////////////////////////////////////////////////////////////////
///  \struct        TFIDFStruct
///  \brief         Struct to hold return value of tfidf vectorizer,
///                 consist of <dictid, tfidf value>
///
struct TFIDFStruct {
    std::uint32_t const dictionaryId;                              // dict id
    std::float_t const tfidf;                                      // freq

    TFIDFStruct(std::uint32_t d, std::float_t t);
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
// |  OneHotStruct
// |
// ----------------------------------------------------------------------

bool OneHotStruct::operator==(OneHotStruct const &other) const {
    return (appearances == other.appearances) && (index == other.index) && (size == other.size);
}
OneHotStruct::OneHotStruct(std::uint32_t i, std::uint32_t s, std::uint32_t a) :
    index(std::move(i)),
    size(std::move(s)),
    appearances(std::move(a)) {
        if (index >= size) {
            throw std::invalid_argument("Category index should be smaller than total number of categories!");
        }
}

// ----------------------------------------------------------------------
// |
// |  TFStruct
// |
// ----------------------------------------------------------------------

bool TFStruct::operator==(TFStruct const &other) const {
    return (appearances == other.appearances) && (dictionaryId == other.dictionaryId);
}
TFStruct::TFStruct(std::uint32_t d, std::uint32_t a) :
    dictionaryId(std::move(d)),
    appearances(std::move(a)) {
}

// ----------------------------------------------------------------------
// |
// |  TFIDFStruct
// |
// ----------------------------------------------------------------------

bool TFIDFStruct::operator==(TFIDFStruct const &other) const {
    return (dictionaryId == other.dictionaryId) && (abs(tfidf - other.tfidf) < 0.000001f);
}
TFIDFStruct::TFIDFStruct(std::uint32_t d, std::float_t t) :
    dictionaryId(std::move(d)),
    tfidf(std::move(t)) {
}

}
}
}
