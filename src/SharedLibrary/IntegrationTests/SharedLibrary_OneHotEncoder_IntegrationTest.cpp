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
        [](std::vector<Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t>> const &args) {
            UNSCOPED_INFO(args.size());
            if(args.size() != 5)
                return false;

            // First value
            UNSCOPED_INFO("First value");
            Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t> const & ohs1(args[0]);

            if(ohs1.NumElements != 8) return false;
            if(ohs1.Value != 1) return false;
            if(ohs1.Index != 3) return false;

            // Second value
            UNSCOPED_INFO("Second value");
            Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t> const & ohs2(args[1]);

            if(ohs2.NumElements != 8) return false;
            if(ohs2.Value != 1) return false;
            if(ohs2.Index != 1) return false;

            // Third value
            UNSCOPED_INFO("Third value");
            Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t> const & ohs3(args[2]);

            if(ohs3.NumElements != 8) return false;
            if(ohs3.Value != 1) return false;
            if(ohs3.Index != 2) return false;

            // Fourth value
            UNSCOPED_INFO("Fourth value");
            Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t> const & ohs4(args[3]);

            if(ohs4.NumElements != 8) return false;
            if(ohs4.Value != 1) return false;
            if(ohs4.Index != 4) return false;

            // Fifth value
            UNSCOPED_INFO("Fifth value");
            Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<std::uint8_t> const & ohs5(args[4]);

            if(ohs5.NumElements != 8) return false;
            if(ohs5.Value != 1) return false;
            if(ohs5.Index != 6) return false;

            return true;

        },
        bool(true)
    );
}
