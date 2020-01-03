// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_OneHotEncoderFeaturizer.h"


TEST_CASE("int8") {
    OneHotEncoderFeaturizer_int8_Test(
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
        [](std::vector<OneHotStruct> const &args) {
            UNSCOPED_INFO(args.size());
            if(args.size() != 5)
                return false;

            // First value
            UNSCOPED_INFO("First value");
            OneHotStruct ohs1(args[0]);
            if(ohs1.index != 3) return false;
            if(ohs1.size != 8) return false;
            if(ohs1.appearances != 1) return false;

            // Second value
            UNSCOPED_INFO("Second value");
            OneHotStruct ohs2(args[1]);
            if(ohs2.index != 1) return false;
            if(ohs2.size != 8) return false;
            if(ohs2.appearances != 1) return false;

            // Third value
            UNSCOPED_INFO("Third value");
            OneHotStruct ohs3(args[2]);
            if(ohs3.index != 2) return false;
            if(ohs3.size != 8) return false;
            if(ohs3.appearances != 1) return false;

            // Fourth value
            UNSCOPED_INFO("Fourth value");
            OneHotStruct ohs4(args[3]);
            if(ohs4.index != 4) return false;
            if(ohs4.size != 8) return false;
            if(ohs4.appearances != 1) return false;

            // Fifth value
            UNSCOPED_INFO("Fifth value");
            OneHotStruct ohs5(args[4]);
            if(ohs5.index != 6) return false;
            if(ohs5.size != 8) return false;
            if(ohs5.appearances != 1) return false;

            return true;

        },
        bool(true)
    );
}

