/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */

// Note that most of the shared code is generated for each Featurizer. The
// DateTimeFeaturizer has additional functionality that is exposed here manually.

#define DLL_EXPORT_COMPILE

#include "SharedLibrary_DateTimeFeaturizerCustom.h"
#include "SharedLibrary_PointerTable.h"

#include "DateTimeFeaturizer.h"

// These method(s) are defined in SharedLibrary_Common.cpp
ErrorInfoHandle * CreateErrorInfo(std::exception const &ex);

extern "C" {

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_CreateTransformerFromSavedDataWithDataRoot(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*in*/ char const *dataRootDir, /*out*/ DateTimeFeaturizer_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(dataRootDir == nullptr) throw std::invalid_argument("'dataRootDir' is null");

        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive archive(pBuffer, cBufferSize);

        Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType* pTransformer(new Microsoft::Featurizer::Featurizers::DateTimeEstimator::TransformerType(archive, std::string(dataRootDir)));

        size_t index = g_pointerTable.Add(pTransformer);
        *ppTransformerHandle = reinterpret_cast<DateTimeFeaturizer_TransformerHandle*>(index);

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_IsValidCountry(/*in*/ char const *countryName, /*in*/ char const *optionalDataRootDir, /*out*/ bool *isValid, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(countryName == nullptr) throw std::invalid_argument("'countryName' is null");
        if(isValid == nullptr) throw std::invalid_argument("'isValid' is null");

        *isValid = Microsoft::Featurizer::Featurizers::DateTimeEstimator::IsValidCountry(countryName, optionalDataRootDir ? std::string(optionalDataRootDir) : nonstd::optional<std::string>());

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_GetSupportedCountries(/*in*/ char const *optionalDataRootDir, /*out*/ char const * const ** ppStringBuffers, /*out*/ std::size_t * pNumStringBuffers, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(ppStringBuffers == nullptr) throw std::invalid_argument("'ppStringBuffers' is null");
        if(pNumStringBuffers == nullptr) throw std::invalid_argument("'pNumStringBuffers' is null");

        std::vector<std::string> const      countries(Microsoft::Featurizer::Featurizers::DateTimeEstimator::GetSupportedCountries(optionalDataRootDir ? std::string(optionalDataRootDir) : nonstd::optional<std::string>()));

        if(countries.empty()) {
            *ppStringBuffers = nullptr;
            *pNumStringBuffers = 0;

            return true;
        }

        // ----------------------------------------------------------------------
        struct Internal {
            static void StringDeleter(char *pData) {
                delete [] pData;
            }

            static void StringsDeleter(char const ** pStrings) {
                delete [] pStrings;
            };
        };

        using StringUniquePtr               = std::unique_ptr<char, void (*)(char *)>;
        using StringUniquePtrs              = std::vector<std::pair<StringUniquePtr, size_t>>;
        using StringsUniquePtr              = std::unique_ptr<char const *, void (*)(char const **)>;
        // ----------------------------------------------------------------------

        // Create the strings
        StringUniquePtrs                    rawStringInfo;

        rawStringInfo.reserve(countries.size());

        for(auto const & country : countries) {
            StringUniquePtr                 pCountry(new char[country.size() + 1], Internal::StringDeleter);

            memcpy(pCountry.get(), country.c_str(), country.size() + 1);

            rawStringInfo.emplace_back(std::move(pCountry), country.size() + 1);
        }

        // Create the string buffer and assign the strings
        StringsUniquePtr                    pStrings(new char const *[countries.size()], Internal::StringsDeleter);
        char const **                       pStringsPtr(pStrings.get());

        for(auto const & rawInfo : rawStringInfo) {
            *pStringsPtr = std::get<0>(rawInfo).get();
            ++pStringsPtr;
        }

        // If here, all memory was successfully allocated and we can release all pointers
        for(auto & rawInfo : rawStringInfo)
            std::get<0>(rawInfo).release();

        *ppStringBuffers = pStrings.release();
        *pNumStringBuffers = countries.size();

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_DestroyStringBuffers(/*in*/ char const * const * pStringBuffer, /*in*/ std::size_t numStringBuffers, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pStringBuffer == nullptr && numStringBuffers != 0) throw std::invalid_argument("Invalid buffer");
        if(pStringBuffer != nullptr && numStringBuffers == 0) throw std::invalid_argument("Invalid buffer");

        if(pStringBuffer == nullptr)
            return true;

        char const * const *                ptr(pStringBuffer);
        char const * const * const          pEnd(ptr + numStringBuffers);

        while(ptr != pEnd) {
            if(*ptr == nullptr) throw std::invalid_argument("Invalid string element");

            delete [] *ptr;
            ++ptr;
        }

        delete [] pStringBuffer;

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

} // extern "C"
