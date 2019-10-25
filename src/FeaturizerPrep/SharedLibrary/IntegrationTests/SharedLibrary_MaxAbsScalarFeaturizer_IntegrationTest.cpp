// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_MaxAbsScalarFeaturizer.h"
#include "../../3rdParty/optional.h"

template <typename T>
bool FuzzyCheck(std::vector<T> const & vec1, std::vector<T> const & vec2, std::double_t epsilon = 0.000001) {
    assert(vec1.size() == vec2.size());

    size_t vec_size = vec1.size();
    for (size_t idx = 0; idx < vec_size; ++idx) {
        if (abs(vec1[idx] - vec2[idx]) > static_cast<T>(epsilon)) {
            return false;
        }
    }
    return true;
}

TEST_CASE("standard-int8_t-float_t") {
    MaxAbsScalarFeaturizer_int8_t_Test(
        std::vector<std::int8_t>{
            static_cast<std::int8_t>(1),
            static_cast<std::int8_t>(3),
            static_cast<std::int8_t>(10),
            static_cast<std::int8_t>(-2),
            static_cast<std::int8_t>(-4)
        },
        std::vector<std::int8_t>{
            static_cast<std::int8_t>(1),
            static_cast<std::int8_t>(3),
            static_cast<std::int8_t>(10),
            static_cast<std::int8_t>(-2),
            static_cast<std::int8_t>(-4)
        },
        [](std::vector<std::float_t> const &args) {
            return FuzzyCheck(args, std::vector<std::float_t>{static_cast<std::float_t>( 0.1), 
                                                              static_cast<std::float_t>( 0.3), 
                                                              static_cast<std::float_t>( 1.0), 
                                                              static_cast<std::float_t>(-0.2), 
                                                              static_cast<std::float_t>(-0.4)});
        }
    );
}


