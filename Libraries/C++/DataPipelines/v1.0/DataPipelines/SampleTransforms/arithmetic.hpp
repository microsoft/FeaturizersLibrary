// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#pragma once

#include <stdint.h>


/* Sample functions to add two things. 
 * Various signature types until we've got a handle on what we want to export. */

/* Using a namespace */
namespace DataPipelines {
    namespace Arithmetic {
        /* Overloaded function name */
        int64_t Add(const int64_t a, const int64_t b);
        uint64_t Add(const uint64_t a, const uint64_t b);
        uint32_t Add(const uint32_t a, const uint32_t b);
        double Add(const double a, const double b);

        /* Templated type, inline definition */
        template<typename T> T Add(const T a, const T b) { return a + b; };

        /* Using a struct */
        struct MyStruct {
            int64_t a;
            int64_t b;
            MyStruct(int64_t _a = 0, int64_t _b = 0) : a(_a), b(_b) {}
        };
        MyStruct Add(const MyStruct& s1, const MyStruct& s2);

        /* unique function name, still in a namespace */
        int32_t Addi32(const int32_t a, const int32_t b);

    }
}

/* C++ simple non-overloaded function */
uint64_t Addu64(const uint64_t a, const uint64_t b);

/* C declarations */
extern "C" {
    int64_t Addi64(const int64_t a, const int64_t b);
    uint32_t Addu32(const uint32_t a, const uint32_t b);
}
