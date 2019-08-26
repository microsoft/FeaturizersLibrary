// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../StringFeaturizer.h"

/////////////////////////////////////////////////////////////////////////
///  Tests are lighter for this featurizer because we are directly
///  leveraging functionality in the traits class
///
using namespace Microsoft::Featurizer;

TEST_CASE("StringEstimator") {
    CHECK(StringEstimator<int>(CreateTestAnnotationMapsPtr(2)).Name == "StringEstimator");
    CHECK(StringEstimator<int>(CreateTestAnnotationMapsPtr(2)).is_training_complete());
    CHECK(std::dynamic_pointer_cast<StringTransformer<int>>(StringEstimator<int>(CreateTestAnnotationMapsPtr(2)).create_transformer()));
}

TEST_CASE("Transformer_Binary") {
    CHECK(StringTransformer<bool>().execute(false) == "False");
    CHECK(StringTransformer<bool>().execute(true) == "True");
}

TEST_CASE("Transformer_Strings") {
    std::string const                       arg_s("isstring");

    CHECK(StringTransformer<std::string>().execute(arg_s) == arg_s);
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

    CHECK(StringTransformer<std::int8_t>().execute(arg_8) == "20");
    CHECK(StringTransformer<std::int16_t>().execute(arg_16) == "-250");
    CHECK(StringTransformer<std::int32_t>().execute(arg_32) == "480");
    CHECK(StringTransformer<std::int64_t>().execute(arg_64) == "-7799");

    CHECK(StringTransformer<std::uint8_t>().execute(arg_u8) == "20");
    CHECK(StringTransformer<std::uint16_t>().execute(arg_u16) == "250");
    CHECK(StringTransformer<std::uint32_t>().execute(arg_u32) == "480");
    CHECK(StringTransformer<std::uint64_t>().execute(arg_u64) == "7799");
}

TEST_CASE("Transformer_Numbers") {
    std::float_t arg_f = 123;
    std::double_t arg_d1 = 123.45;
    std::double_t arg_d2 = 135453984983490.5473;

    CHECK(StringTransformer<std::float_t>().execute(arg_f) == "123");
    CHECK(StringTransformer<std::double_t>().execute(arg_d1) == "123.45");
    CHECK(StringTransformer<std::double_t>().execute(arg_d2) == "1.35454e+14");
}

TEST_CASE("Transformer_Array") {
    std::array<std::double_t, 4> arr{ 1.3,2,-306.2,0.04 };
    std::string arr_s{ "[1.3,2,-306.2,0.04]" };
    CHECK(StringTransformer<std::array<std::double_t, 4>>().execute(arr) == arr_s);
}

TEST_CASE("Transformer_Vector") {
    std::vector<std::double_t> vect{ 1.03, -20.1, 305.8 };
    std::string vect_s{ "[1.03,-20.1,305.8]" };
	CHECK(StringTransformer<std::vector<std::double_t>>().execute(vect) == vect_s);
}

TEST_CASE("Transformer_Maps") {
    std::map<std::int16_t, std::double_t> m;
    m.insert(std::pair<std::int16_t, std::double_t>(5, 35.8));
    m.insert(std::pair<std::int16_t, std::double_t>(93, 0.147));
    std::string map_s{ "{5:35.8,93:0.147}" };
    CHECK(StringTransformer<std::map<std::int16_t, std::double_t>>().execute(m) == map_s);
}
