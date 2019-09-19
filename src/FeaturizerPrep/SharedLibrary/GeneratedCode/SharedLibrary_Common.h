/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include <cstddef>
#include <stdint.h>

#if (defined _MSC_VER)
#   if (defined DLL_EXPORT_COMPILE)
#       define FEATURIZER_LIBRARY_API __declspec(dllexport)
#   else
#       define FEATURIZER_LIBRARY_API __declspec(dllimport)
#   endif

#   define FEATURIZER_LIBRARY_API_PACK_PREFIX               \
    __pragma(pack(push))                                    \
    __pragma(pack(1))

#   define FEATURIZER_LIBRARY_API_PACK_SUFFIX               __pragma(pack(pop))
#   define FEATURIZER_LIBRARY_API_PACK_INLINE

#elif (defined __GNUC__ || defined __clang__)
#   if (defined DLL_EXPORT_COMPILE)
#       define FEATURIZER_LIBRARY_API __attribute__((visibility("default")))
#   else
#       define FEATURIZER_LIBRARY_API
#   endif

#   define FEATURIZER_LIBRARY_API_PACK_PREFIX
#   define FEATURIZER_LIBRARY_API_PACK_SUFFIX
#   define FEATURIZER_LIBRARY_API_PACK_INLINE               __attribute__((packed))

#else
#   error Unrecognized compiler!
#endif

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wextern-c-compat" // empty struct has size 0 in C, size 1 in C++
#endif

extern "C" {

struct ErrorInfoHandle {};

FEATURIZER_LIBRARY_API bool GetErrorInfoString(/*in*/ ErrorInfoHandle *pHandle, /*out*/ char const **output_ptr, /*out*/ std::size_t *output_items);
FEATURIZER_LIBRARY_API bool DestroyErrorInfoString(/*in*/ char const *input_ptr, /*in*/ std::size_t input_items);
FEATURIZER_LIBRARY_API bool DestroyErrorInfo(/*in*/ ErrorInfoHandle *pHandle);

// These values should match the values in Featurizer.h
enum FitResultValue {
    Complete = 1,
    Continue,
    ResetAndContinue
};

typedef unsigned char FitResult;

// These values should match the values in Traits.h
enum TypeIdValue {
    StringId = 0x00000001,
    Int8Id,
    Int16Id,
    Int32Id,
    Int64Id,
    UInt8Id,
    UInt16Id,
    UInt32Id,
    UInt64Id,
    Float16Id,
    Float32Id,
    Float64Id,
    Complex64Id,
    Complex128Id,
    BFloat16Id,
    BoolId,
    TimepointId,
    DurationId,

    LastStaticValueId,

    TensorId = 0x1001 | LastStaticValueId + 1,
    SparseTensorId = 0x1001 | LastStaticValueId + 2,
    TabularId = 0x1001 | LastStaticValueId + 3,

    NullableId = 0x1001 | LastStaticValueId + 4,
    VectorId = 0x1001 | LastStaticValueId + 5,
    MapId = 0x1002 | LastStaticValueId + 6
};

typedef uint32_t TypeId;

} // extern "C"

