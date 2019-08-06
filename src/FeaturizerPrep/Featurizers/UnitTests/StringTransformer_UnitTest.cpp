// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------


#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../StringTransformer.h"
/////////////////////////////////////////////////////////////////////////
///  Tests are lighter for this featurizer because we are directly
///  leveraging functionality in the traits class
///

TEST_CASE("Transformer_Binary") {
    bool arg_false = false;
    bool arg_true = true;

    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<bool>().transform(arg_false) == "False");
    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<bool>().transform(arg_true) == "True");
}

TEST_CASE("Transformer_Strings") {
    std::string arg_s = "isstring";
    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::string>().transform(arg_s) == "isstring");
}

TEST_CASE("Transformer_Integers") {
    std::int8_t arg_8 = 20;
    std::int16_t arg_16 = -250;
    std::int32_t arg_32 = 480;
    std::int64_t arg_64 = -7799;

    std::uint8_t arg_u8 = 20;
    std::uint16_t arg_u16 = 250;
    std::uint32_t arg_u32 = 480;
    std::uint64_t arg_u64 = 7799;

    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::int8_t>().transform(arg_8) == "20");
    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::int16_t>().transform(arg_16) == "-250");
    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::int32_t>().transform(arg_32) == "480");
    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::int64_t>().transform(arg_64) == "-7799");

    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::uint8_t>().transform(arg_u8) == "20");
    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::uint16_t>().transform(arg_u16) == "250");
    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::uint32_t>().transform(arg_u32) == "480");
    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::uint64_t>().transform(arg_u64) == "7799");
}

TEST_CASE("Transformer_Numbers") {
    std::float_t arg_f = 123;
    std::double_t arg_d1 = 123.45;
    std::double_t arg_d2 = 135453984983490.5473;

    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::float_t>().transform(arg_f) == "123");
    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::double_t>().transform(arg_d1) == "123.45");
    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::double_t>().transform(arg_d2) == "1.35454e+14");
}

TEST_CASE("Transformer_Array") {
    std::array<std::double_t, 4> arr{ 1.3,2,-306.2,0.04 };
    std::string arr_s{ "[1.3,2,-306.2,0.04]" };
    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::array<std::double_t, 4>>().transform(arr) == arr_s);  
}

TEST_CASE("Transformer_Vector") {
    std::vector<std::double_t> vect{ 1.03, -20.1, 305.8 };
    std::string vect_s{ "[1.03,-20.1,305.8]" };
	CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::vector<std::double_t>>().transform(vect) == vect_s);  
}

TEST_CASE("Transformer_Maps") {
    std::map<std::int16_t, std::double_t> m;
    m.insert(std::pair<std::int16_t, std::double_t>(5, 35.8));
    m.insert(std::pair<std::int16_t, std::double_t>(93, 0.147));
    std::string map_s{ "{5:35.8,93:0.147}" };
    CHECK(Microsoft::Featurizer::StringTransformer::Transformer<std::map<std::int16_t, std::double_t>>().transform(m) == map_s);  
}



