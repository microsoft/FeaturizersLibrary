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
    CHECK(strcmp(NS::Featurizers::MissingDummiesEstimator<int>(NS::CreateTestAnnotationMapsPtr(2)).Name, "MissingDummiesEstimator") == 0);

    NS::Featurizers::MissingDummiesEstimator<int>   estimator(NS::CreateTestAnnotationMapsPtr(1));

    estimator
        .begin_training()
        .complete_training();

    CHECK(dynamic_cast<NS::Featurizers::MissingDummiesTransformer<nonstd::optional<int>> *>(estimator.create_transformer().get()));

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

TEST_CASE("Serialization") {
    NS::Featurizers::MissingDummiesTransformer<std::double_t>               original;
    NS::Archive                                                             out;

    original.save(out);

    NS::Archive                             in(out.commit());

    NS::Featurizers::MissingDummiesTransformer<std::double_t>               other(in);

    CHECK(other == original);
}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        (NS::Featurizers::MissingDummiesTransformer<std::double_t>(in)),
        Catch::Contains("Unsupported archive version")
    );
}
