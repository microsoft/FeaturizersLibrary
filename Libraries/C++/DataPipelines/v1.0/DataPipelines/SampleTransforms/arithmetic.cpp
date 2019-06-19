// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#include <stdint.h>
#include "arithmetic.hpp"

/* Defined in enclosed namespace */
namespace DataPipelines {
    namespace Arithmetic {
        int64_t Add(const int64_t a, const int64_t b) { return a + b; }
        uint64_t Add(const uint64_t a, const uint64_t b) { return a + b; }
        uint32_t Add(const uint32_t a, const uint32_t b) { return a + b; }

        MyStruct Add(const MyStruct& s1, const MyStruct& s2) {
            return MyStruct(s1.a + s2.a, s1.b + s2.b);
        }
    }
}

/* self defined namespace */
double  DataPipelines::Arithmetic::Add(const double a, const double b) { 
    return a + b; 
}
int32_t DataPipelines::Arithmetic::Addi32(const int32_t a, const int32_t b) {
    return Add<int32_t>(a, b);
}


/* C++ non-overloaded function */
uint64_t Addu64(const uint64_t a, const uint64_t b) {
    return DataPipelines::Arithmetic::Add(a, b);
}


/* C-export functions */
int64_t Addi64(const int64_t a, const int64_t b) {
    return DataPipelines::Arithmetic::Add(a, b);
}

uint32_t Addu32(const uint32_t a, const uint32_t b) {
    return DataPipelines::Arithmetic::Add(a, b);
}

