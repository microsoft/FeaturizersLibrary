/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.hpp"

#if (defined _MSC_VER)
#   pragma warning(push)

    // I don't know why MSVC thinks that there is unreachable
    // code in these methods during release builds.
#   pragma warning(disable: 4702) // Unreachable code

#   pragma warning(disable: 4701) // potentially uninitialized local variable '<name>' used
#   pragma warning(disable: 4703) // potentially uninitialized local pointer variable '<name>' used
#endif
template <typename T>
Microsoft::Featurizer::RowMajMatrix<T> CreateMatrix(size_t numCols, size_t numRows, T *pData) {
    if(numCols == 0) throw std::invalid_argument("numCols");
    if(numRows == 0) throw std::invalid_argument("numRows");
    if(pData == nullptr) throw std::invalid_argument("pData");

    Microsoft::Featurizer::RowMajMatrix<T> result(numRows, numCols);

    for(size_t row = 0; row < numRows; ++row) {
        for(size_t col = 0; col < numCols; ++col) {
            result(static_cast<Eigen::Index>(row), static_cast<Eigen::Index>(col)) = *pData++;
        }
    }

    return result;
}

std::vector<std::string> CreateUniqueId(char const * const *strings, size_t items) {
    if(strings == nullptr) throw std::invalid_argument("strings");
    if(items == 0) throw std::invalid_argument("items");

    std::vector<std::string> result;

    result.reserve(items);

    while(result.size() < items) {
        char const * const ptr(*strings++);

        if(ptr == nullptr) throw std::invalid_argument("'strings' element is null");

        result.emplace_back(ptr);
    }

    return result;
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
