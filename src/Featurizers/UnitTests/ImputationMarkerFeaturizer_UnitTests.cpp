// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../ImputationMarkerFeaturizer.h"

/////////////////////////////////////////////////////////////////////////
///  Tests are lighter for this featurizer because we are directly
///  leveraging functionality in the traits class
///
namespace NS = Microsoft::Featurizer;

template <typename T>
void TestHelper(T const & input) {
    using Type = typename NS::Traits<T>::nullable_type;
    Type nullValue = NS::Traits<T>::CreateNullValue();
    CHECK(NS::Featurizers::ImputationMarkerTransformer<Type>().execute(input) == false);
    CHECK(NS::Featurizers::ImputationMarkerTransformer<Type>().execute(nullValue) == true);
}

TEST_CASE("ImputationMarkerEstimator") {

    CHECK(strcmp(NS::Featurizers::ImputationMarkerEstimator<int>(NS::CreateTestAnnotationMapsPtr(2)).Name, "ImputationMarkerEstimator") == 0);

    NS::Featurizers::ImputationMarkerEstimator<int>   estimator(NS::CreateTestAnnotationMapsPtr(1));

    estimator
        .begin_training()
        .complete_training();

    CHECK(dynamic_cast<NS::Featurizers::ImputationMarkerTransformer<nonstd::optional<int>> *>(estimator.create_transformer().get()));
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
    CHECK(NS::Featurizers::ImputationMarkerTransformer<std::float_t>().execute(std::numeric_limits<std::float_t>::quiet_NaN()) == true);
    CHECK(NS::Featurizers::ImputationMarkerTransformer<std::double_t>().execute(std::numeric_limits<std::double_t>::quiet_NaN()) == true);
}

TEST_CASE("Serialization") {
    NS::Featurizers::ImputationMarkerTransformer<std::double_t>             original;
    NS::Archive                                                             out;

    original.save(out);

    NS::Archive                             in(out.commit());

    NS::Featurizers::ImputationMarkerTransformer<std::double_t>             other(in);

    CHECK(other == original);
}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        NS::Featurizers::ImputationMarkerTransformer<std::double_t>(in),
        Catch::Contains("Unsupported archive version")
    );
}
