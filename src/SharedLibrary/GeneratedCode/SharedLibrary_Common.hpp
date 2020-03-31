// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <string>
#include <tuple>

#include "SharedLibrary_Common.h"

template <typename T>
struct make_tuple_elements_const_references {};

template <typename... Ts>
struct make_tuple_elements_const_references<std::tuple<Ts...>> {
    using type              = std::tuple<typename std::add_lvalue_reference<typename std::add_const<Ts>::type>::type...>;
};

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
