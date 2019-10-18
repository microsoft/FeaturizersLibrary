// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_LabelEncoderFeaturizer.h"


TEST_CASE("int8") {
    LabelEncoderFeaturizer_int8_t_Test(
        std::vector<std::int8_t>{
            static_cast<std::int8_t>(10),
            static_cast<std::int8_t>(20),
            static_cast<std::int8_t>(10),
            static_cast<std::int8_t>(30),
            static_cast<std::int8_t>(10),
            static_cast<std::int8_t>(10),
            static_cast<std::int8_t>(11),
            static_cast<std::int8_t>(15),
            static_cast<std::int8_t>(18),
            static_cast<std::int8_t>(8)
        },
        std::vector<std::int8_t>{
            static_cast<std::int8_t>(11),
            static_cast<std::int8_t>(8),
            static_cast<std::int8_t>(10),
            static_cast<std::int8_t>(15),
            static_cast<std::int8_t>(20)
        },
        [](std::vector<std::uint32_t> const &args) {
            return args == std::vector<std::uint32_t>{3, 1, 2, 4, 6};
        },
        bool(true)
    );
}


TEST_CASE("string") {
    LabelEncoderFeaturizer_string_Test(
        std::vector<std::string>{
            static_cast<std::string>("orange"),
            static_cast<std::string>("apple"),
            static_cast<std::string>("orange"),
            static_cast<std::string>("grape"),
            static_cast<std::string>("carrot"),
            static_cast<std::string>("carrot"),
            static_cast<std::string>("peach"),
            static_cast<std::string>("banana"),
            static_cast<std::string>("orange")
        },
        std::vector<std::string>{
            static_cast<std::string>("banana"),
            static_cast<std::string>("grape"),
            static_cast<std::string>("apple")
        },
        [](std::vector<std::uint32_t> const &args) {
            return args == std::vector<std::uint32_t>{2, 4, 1};
        },
        bool(true)
    );
}
