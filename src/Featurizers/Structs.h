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
    std::uint32_t const Index;                                    // category index
    std::uint32_t const Size;                                     // category total size
    std::uint32_t const Appearances;                              // number of appearances

    OneHotStruct(std::uint32_t index, std::uint32_t size, std::uint32_t appearances);
    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(OneHotStruct);
    bool operator==(OneHotStruct const &other) const;
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
// |  OneHotStruct
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


}
}
}
