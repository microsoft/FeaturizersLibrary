/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */
#define DLL_EXPORT_COMPILE

#include <memory>
#include <string>

#include "SharedLibrary_Common.h"

extern "C" {

FEATURIZER_LIBRARY_API bool GetErrorInfoString(/*in*/ ErrorInfoHandle *pHandle, /*out*/ char const **output_ptr, /*out*/ std::size_t *output_items) {
    if(pHandle == nullptr || output_ptr == nullptr || output_items == nullptr)
        return false;

    std::string const & str(*reinterpret_cast<std::string *>(pHandle));

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

    std::string & str(*reinterpret_cast<std::string *>(pHandle));

    delete &str;

    return true;
}

} // extern "C"

// These methods are used internally but not exported
ErrorInfoHandle * CreateErrorInfo(std::exception const &ex) {
    std::unique_ptr<std::string> result(std::make_unique<std::string>(ex.what()));

    return reinterpret_cast<ErrorInfoHandle *>(result.release());
}

