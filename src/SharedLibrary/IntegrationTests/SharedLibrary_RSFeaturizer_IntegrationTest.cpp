// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_RobustScalarFeaturizer.h"
#include "../SharedLibrary_RobustScalarFeaturizerCustom.h"
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

TEST_CASE("standard-int8-float_t") {
    std::float_t const                      qMin(25.0f);
    std::float_t const                      qMax(75.0f);

    RobustScalarFeaturizer_int8_Test(
        std::vector<std::int8_t>{
            static_cast<std::int8_t>(1),
            static_cast<std::int8_t>(3),
            static_cast<std::int8_t>(5),
            static_cast<std::int8_t>(7),
            static_cast<std::int8_t>(9)
        },
        std::vector<std::int8_t>{
            static_cast<std::int8_t>(1),
            static_cast<std::int8_t>(3),
            static_cast<std::int8_t>(5),
            static_cast<std::int8_t>(7),
            static_cast<std::int8_t>(9)
        },
        [](std::vector<std::float_t> const &args) {
            return FuzzyCheck(args, std::vector<std::float_t>{-1.0, -0.5, 0.0, 0.5, 1.0});
        },
        true,
        &qMin,
        &qMax
    );
}

TEST_CASE("standard-int32-double") {
    std::float_t const                      qMin(25.0f);
    std::float_t const                      qMax(75.0f);

    RobustScalarFeaturizer_int32_Test(
        std::vector<std::int32_t>{
            static_cast<std::int32_t>(1),
            static_cast<std::int32_t>(3),
            static_cast<std::int32_t>(5),
            static_cast<std::int32_t>(7),
            static_cast<std::int32_t>(9)
        },
        std::vector<std::int32_t>{
            static_cast<std::int32_t>(1),
            static_cast<std::int32_t>(3),
            static_cast<std::int32_t>(5),
            static_cast<std::int32_t>(7),
            static_cast<std::int32_t>(9)
        },
        [](std::vector<std::double_t> const &args) {
            return FuzzyCheck(args, std::vector<std::double_t>{-1.0, -0.5, 0.0, 0.5, 1.0});
        },
        true,
        &qMin,
        &qMax
    );
}

TEST_CASE("CreateEstimatorWithDefault-int8") {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    RobustScalarFeaturizer_int8_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_int8_CreateEstimatorWithDefault(true, &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);
}

TEST_CASE("CreateEstimatorWithDefault-int32") {
    ErrorInfoHandle * pErrorInfo(nullptr);

    // Create the estimator
    RobustScalarFeaturizer_int32_EstimatorHandle *pEstimatorHandle(nullptr);

    REQUIRE(RobustScalarFeaturizer_int32_CreateEstimatorWithDefault(true, &pEstimatorHandle, &pErrorInfo));
    REQUIRE(pEstimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);
}
