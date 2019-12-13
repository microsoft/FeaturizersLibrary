/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include <memory>
#include <string>

#include "SharedLibrary_Common.h"
#include "SharedLibrary_PointerTable.h"

// Forward declaration for DestroyTransformerSaveData
ErrorInfoHandle* CreateErrorInfo(std::exception const &ex);

extern "C" {

FEATURIZER_LIBRARY_API bool GetErrorInfoString(/*in*/ ErrorInfoHandle *pHandle, /*out*/ char const **output_ptr, /*out*/ std::size_t *output_items) {
    if(pHandle == nullptr || output_ptr == nullptr || output_items == nullptr)
        return false;

    std::string const & str(*g_pointerTable.Get<std::string>(reinterpret_cast<size_t>(pHandle)));

    char * string_buffer(new char[str.size() + 1]);

    std::copy(str.begin(), str.end(), string_buffer);
    string_buffer[str.size()] = 0;

    *output_ptr = string_buffer;
    *output_items = str.size();

    return true;
}

FEATURIZER_LIBRARY_API bool DestroyErrorInfoString(/*in*/ char const *input_ptr, /*in*/ std::size_t input_items) {
    if(input_ptr == nullptr || input_items == 0)
        return false;

    delete [] input_ptr;

    return true;
}

FEATURIZER_LIBRARY_API bool DestroyErrorInfo(/*in*/ ErrorInfoHandle *pHandle) {
    if(pHandle == nullptr)
        return false;

    size_t index = reinterpret_cast<size_t>(pHandle);

    std::string & str(*g_pointerTable.Get<std::string>(index));

    g_pointerTable.Remove(index);

    delete &str;

    return true;
}

FEATURIZER_LIBRARY_API bool DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");

        delete [] pBuffer;

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

} // extern "C"

// These methods are used internally but not exported
ErrorInfoHandle * CreateErrorInfo(std::exception const &ex) {
    std::unique_ptr<std::string> result(new std::string(ex.what()));

    size_t index = g_pointerTable.Add(result.release());
    return reinterpret_cast<ErrorInfoHandle *>(index);
}

