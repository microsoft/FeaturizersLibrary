// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "SharedLibrary_Common.h"

DateTimeParameter CreateDateTimeParameter(int64_t const &value);
DateTimeParameter CreateDateTimeParameter(std::string const &value);

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
inline DateTimeParameter CreateDateTimeParameter(int64_t const &value) {
    DateTimeParameter       result;

    result.dataType = DateTimeParameter::DateTimeTypeValue::DateTimeInt64;
    result.data.posix = value;

    return result;
}

inline DateTimeParameter CreateDateTimeParameter(std::string const &value) {
    DateTimeParameter       result;

    result.dataType = DateTimeParameter::DateTimeTypeValue::DateTimeString;
    result.data.isoStr.pBuffer = value.c_str();
    result.data.isoStr.cBufferElements = value.size();

    return result;
}
