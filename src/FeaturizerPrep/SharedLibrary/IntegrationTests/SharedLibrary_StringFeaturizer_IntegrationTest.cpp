// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_StringFeaturizer.h"
#include "../GeneratedCode/SharedLibrary_StringFeaturizer.h"

TEST_CASE("int8") {
    StringFeaturizer_int8_t_Test(
        std::vector<std::int8_t>(),
        {1, 2, -3, 4},
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{"1", "2", "-3", "4"};
        }
    );
}

TEST_CASE("int16") {
    StringFeaturizer_int16_t_Test(
        std::vector<std::int16_t>(),
        {1000, 2000, -3000, 4000},
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{"1000", "2000", "-3000", "4000"};
        }
    );
}

TEST_CASE("int32") {
    StringFeaturizer_int32_t_Test(
        std::vector<std::int32_t>(),
        {1000, 2000, -3000, 4000},
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{"1000", "2000", "-3000", "4000"};
        }
    );
}

TEST_CASE("int64") {
    StringFeaturizer_int64_t_Test(
        std::vector<std::int64_t>(),
        {1000, 2000, -3000, 4000},
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{"1000", "2000", "-3000", "4000"};
        }
    );
}

TEST_CASE("uint8") {
    StringFeaturizer_uint8_t_Test(
        std::vector<std::uint8_t>(),
        {1, 2, 3, 4},
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{"1", "2", "3", "4"};
        }
    );
}

TEST_CASE("uint16") {
    StringFeaturizer_uint16_t_Test(
        std::vector<std::uint16_t>(),
        {1000, 2000, 3000, 4000},
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{"1000", "2000", "3000", "4000"};
        }
    );
}

TEST_CASE("uint32") {
    StringFeaturizer_uint32_t_Test(
        std::vector<std::uint32_t>(),
        {1000, 2000, 3000, 4000},
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{"1000", "2000", "3000", "4000"};
        }
    );
}

TEST_CASE("uint64") {
    StringFeaturizer_uint64_t_Test(
        std::vector<std::uint64_t>(),
        {1000, 2000, 3000, 4000},
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{"1000", "2000", "3000", "4000"};
        }
    );
}

TEST_CASE("float") {
    StringFeaturizer_float_t_Test(
        std::vector<std::float_t>(),
        {1.1f, 2.22f, -3.333f, 4.4444f},
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{"1.100000", "2.220000", "-3.333000", "4.444400"};
        }
    );
}

TEST_CASE("double") {
    StringFeaturizer_double_t_Test(
        std::vector<std::double_t>(),
        {1.1, 2.22, -3.333, 4.4444},
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{"1.100000", "2.220000", "-3.333000", "4.444400"};
        }
    );
}

// std::vector<bool> is a special beast, so the generated code doesn't work well for these types.
//
// TEST_CASE("bool") {
//     StringFeaturizer_bool_Test(
//         std::vector<bool>(),
//         {true, false, true},
//         [](std::vector<std::string> const &args) {
//             return args == std::vector<std::string>{"true", "false", "true"};
//         }
//     );
// }

TEST_CASE("string") {
    StringFeaturizer_string_Test(
        std::vector<std::string>(),
        {"one", "two", "three"},
        [](std::vector<std::string> const &args) {
            return args == std::vector<std::string>{"one", "two", "three"};
        }
    );
}
