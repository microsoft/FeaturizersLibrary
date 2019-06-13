// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include "../arithmetic.cpp"

using namespace DataPipelines::Arithmetic;

TEST_CASE("1+2=3", "[Add]") {
    CHECK(Add(int64_t(1), int64_t(2)) == int64_t(3));
    CHECK(Add(uint64_t(1), uint64_t(2)) == uint64_t(3));
    CHECK(Add(uint32_t(1), uint32_t(2)) == uint32_t(3));
    CHECK(Add(int32_t(1), int32_t(2)) == int32_t(3));
    CHECK(Add(uint16_t(1), uint16_t(2)) == uint16_t(3));
    CHECK(Add(double(1.0), double(2.0)) == Approx(3.0));
    CHECK(Add(float(1.0), float(2.0)) == Approx(3.0));
    CHECK(Addi32(1, 2) == 3);
    CHECK(Addu64(1, 2) == 3);
    CHECK(Addi64(1, 2) == 3);
    CHECK(Addu32(1, 2) == 3);
}
TEST_CASE("char a+b", "[Add]") {
    CHECK(Add('a', 'b') == char(0xC3));
}
TEST_CASE("string a+b", "[Add],[String]") {
    CHECK(Add(std::string("a"), std::string("b")) == "ab");
}
TEST_CASE("-10+3", "[Add][Negative]") {
    CHECK(Add<int32_t>(int32_t(-10), 3) == -7);
    CHECK(Add(int64_t(-10), 3) == -7);
    CHECK(Add(uint32_t(int32_t(-10)), 3) == 0xFFFFFFF9);
    CHECK(Add(uint64_t(int64_t(-10)), 3) == 0xFFFFFFFFFFFFFFF9);
    CHECK(Add<uint16_t>(uint16_t((INT16_C(-10))), 3) == uint16_t(0xFFF9));
    CHECK(Add(double(-10.0), 3.0) == Approx(-7.0));
    CHECK(Add<float>(float(-10.0), 3.0) == Approx(-7.0));
    CHECK(Addi32(int32_t(-10), 3) == -7);
}
TEST_CASE("Add Rollover", "[Add][Rollover]") {
    CHECK(Add(uint32_t(0xFFFFFFFE), uint32_t(4)) == 2);
    CHECK(Add(uint64_t(0xFFFFFFFE), uint64_t(4)) == 0x100000002);
    CHECK(Add(uint64_t(0xFFFFFFFFFFFFFFFE), uint64_t(4)) == 2);
    CHECK(Add<uint16_t>(uint16_t(0xFFFE), uint16_t(4)) == 2);
    CHECK(Add(INT64_MAX, INT64_MAX) == -2);
    CHECK(Add<int32_t>(INT32_MAX, INT32_MAX) == -2);
    CHECK(Addu64(uint64_t(0xFFFFFFFFFFFFFFFE), 4) == 2);
}
TEST_CASE("Add Struct", "[Add][struct]") {
    struct MyStruct s1(10, 25);
    struct MyStruct s2(-50, 1000);
    struct MyStruct sum = Add(s1, s2);
    CHECK(sum.a == -40);
    CHECK(sum.b == 1025);
}
