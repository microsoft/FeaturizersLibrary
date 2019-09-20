/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */

// Note that most of the shared code is generated for each Featurizer. The
// DateTimeFeaturizer has additional functionality that is exposed here manually.

#define DLL_EXPORT_COMPILE

#include "SharedLibrary_DateTimeFeaturizerCustom.h"
#include "DateTimeFeaturizer.h"

// These method(s) are defined in SharedLibrary_Common.cpp
ErrorInfoHandle * CreateErrorInfo(std::exception const &ex);

extern "C" {

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_IsValidCountry(/*in*/ char const *countryName, /*out*/ bool *isValid, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(countryName == nullptr) throw std::invalid_argument("'countryName' is null");
        if(isValid == nullptr) throw std::invalid_argument("'isValid' is null");

        *isValid = Microsoft::Featurizer::Featurizers::DateTimeEstimator::IsValidCountry(countryName);

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_GetSupportedCountries(/*out*/ StringBuffer ** ppStringBuffers, /*out*/ std::size_t * pNumStringBuffers, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(ppStringBuffers == nullptr) throw std::invalid_argument("'ppStringBuffers' is null");
        if(pNumStringBuffers == nullptr) throw std::invalid_argument("'pNumStringBuffers' is null");

        std::vector<std::string> const      countries(Microsoft::Featurizer::Featurizers::DateTimeEstimator::GetSupportedCountries());

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

            static void StringBufferDeleter(StringBuffer *pData) {
                delete [] pData;
            }
        };

        using StringUniquePtr               = std::unique_ptr<char, void (*)(char *)>;
        using StringUniquePtrs              = std::vector<std::pair<StringUniquePtr, size_t>>;
        using StringBufferUniquePtr         = std::unique_ptr<StringBuffer, void (*)(StringBuffer *)>;
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
        StringBufferUniquePtr               pStringBuffers(new StringBuffer[countries.size()], Internal::StringBufferDeleter);
        StringBuffer *                      pStringBuffersPtr(pStringBuffers.get());

        for(auto const & rawInfo : rawStringInfo) {
            pStringBuffersPtr->pString = std::get<0>(rawInfo).get();
            pStringBuffersPtr->cCharacters = std::get<1>(rawInfo);
            ++pStringBuffersPtr;
        }

        // If here, all memory was successfully allocated and we can release all pointers
        for(auto & rawInfo : rawStringInfo)
            std::get<0>(rawInfo).release();

        *ppStringBuffers = pStringBuffers.release();
        *pNumStringBuffers = countries.size();

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool DateTimeFeaturizer_DestroyStringBuffers(/*in*/ StringBuffer *pStringBuffer, /*in*/ std::size_t numStringBuffers, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pStringBuffer == nullptr && numStringBuffers != 0) throw std::invalid_argument("Invalid buffer");
        if(pStringBuffer != nullptr && numStringBuffers == 0) throw std::invalid_argument("Invalid buffer");

        if(pStringBuffer == nullptr)
            return true;

        StringBuffer const *                ptr(pStringBuffer);
        StringBuffer const * const          pEnd(ptr + numStringBuffers);

        while(ptr != pEnd) {
            if(ptr->pString == nullptr || ptr->cCharacters == 0) throw std::invalid_argument("Invalid string element");

            delete [] ptr->pString;
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
