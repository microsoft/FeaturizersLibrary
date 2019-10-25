// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../MissingDummiesFeaturizer.h"

/////////////////////////////////////////////////////////////////////////
///  Tests are lighter for this featurizer because we are directly
///  leveraging functionality in the traits class
///
namespace NS = Microsoft::Featurizer;

template <typename T>
void TestHelper(T const & input) {
    using Type = typename NS::Traits<T>::nullable_type;
    Type nullValue = NS::Traits<T>::CreateNullValue();
    CHECK(NS::Featurizers::MissingDummiesTransformer<Type>().execute(input) == 0);
    CHECK(NS::Featurizers::MissingDummiesTransformer<Type>().execute(nullValue) == 1);
}

TEST_CASE("MissingDummiesEstimator") {
    CHECK(NS::Featurizers::MissingDummiesEstimator<int>(NS::CreateTestAnnotationMapsPtr(1)).Name == "MissingDummiesEstimator");
    CHECK(NS::Featurizers::MissingDummiesEstimator<int>(NS::CreateTestAnnotationMapsPtr(1)).is_training_complete());
    CHECK(dynamic_cast<NS::Featurizers::MissingDummiesTransformer<nonstd::optional<int>> *>(NS::Featurizers::MissingDummiesEstimator<int>(NS::CreateTestAnnotationMapsPtr(1)).create_transformer().get()));
}

TEST_CASE("Single Tests") {
    TestHelper(static_cast<std::int8_t>(25));
    TestHelper(static_cast<std::uint8_t>(25));
    TestHelper(static_cast<std::int16_t>(25));
    TestHelper(static_cast<std::uint16_t>(25));
    TestHelper(static_cast<std::int32_t>(25));
    TestHelper(static_cast<std::uint32_t>(25));
    TestHelper(static_cast<std::int64_t>(25));
    TestHelper(static_cast<std::uint64_t>(25));
    TestHelper(static_cast<std::float_t>(2.5));
    TestHelper(static_cast<std::double_t>(2.5));
    TestHelper(static_cast<std::string>("hello"));
    TestHelper(static_cast<std::string>(""));
}

TEST_CASE("Numeric NaNs") {
    CHECK(NS::Featurizers::MissingDummiesTransformer<std::float_t>().execute(std::numeric_limits<std::float_t>::quiet_NaN()) == 1);
    CHECK(NS::Featurizers::MissingDummiesTransformer<std::double_t>().execute(std::numeric_limits<std::double_t>::quiet_NaN()) == 1);
}

