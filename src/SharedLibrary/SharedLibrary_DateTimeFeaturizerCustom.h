/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#pragma once

#include "SharedLibrary_Common.h"
#include "SharedLibrary_DateTimeFeaturizer.h"

extern "C" {

/* This file exposes non-standard functionality in the DateTimeFeaturizer */

FEATURIZER_LIBRARY_API_PACK_PREFIX

struct StringBuffer {
    char const * pString;
    std::size_t cCharacters;
} FEATURIZER_LIBRARY_API_PACK_INLINE;

FEATURIZER_LIBRARY_API_PACK_SUFFIX

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateTransformerFromSavedDataWithDataRoot(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*in*/ char const *dataRootDir, /*out*/ DateTimeFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo);

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_IsValidCountry(/*in*/ char const *countryName, /*in*/ char const *optionalDataRootDir, /*out*/ bool *isValid, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_GetSupportedCountries(/*in*/ char const *optionalDataRootDir, /*out*/ StringBuffer ** ppStringBuffers, /*out*/ std::size_t * pNumStringBuffers, /*out*/ ErrorInfoHandle **ppErrorInfo);
FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_DestroyStringBuffers(/*in*/ StringBuffer *pStringBuffer, /*in*/ std::size_t numStringBuffers, /*out*/ ErrorInfoHandle **ppErrorInfo);

} // extern "C"
