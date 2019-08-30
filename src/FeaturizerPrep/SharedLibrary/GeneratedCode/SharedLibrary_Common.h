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

typedef unsigned char FitResult;

static FitResult const Complete = 0;
static FitResult const Continue = 1;
static FitResult const ResetAndContinue = 2;

} // extern "C"

