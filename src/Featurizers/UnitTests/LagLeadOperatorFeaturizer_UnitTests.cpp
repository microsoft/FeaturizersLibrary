// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../LagLeadOperatorFeaturizer.h"
#include "../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

TEST_CASE("Invalid constructor parameter") {
    using InputType = std::double_t;using InputType = std::double_t;
    CHECK_THROWS_WITH(NS::Featurizers::LagLeadOperatorTransformer<InputType>(0, {-1}), "Horizon cannot be 0!");
    std::vector<std::int64_t> offset{};
    CHECK_THROWS_WITH(NS::Featurizers::LagLeadOperatorTransformer<InputType>(1, offset), "Offsets is empty!");
}

TEST_CASE("Test with one grain - horizon 2, lag 0") {
    using InputType = std::double_t;
    using TransformedType = NS::ColMajMatrix<std::double_t>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(2, {0});
    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );

    transformer.execute(10, callback);
    transformer.execute(11, callback);
    transformer.execute(12, callback);
    transformer.execute(13, callback);
    transformer.execute(14, callback);
    transformer.execute(15, callback);
    transformer.flush(callback);
    CHECK(std::isnan(ret[0](0,0)));
    CHECK(ret[0](0,1) == 10);
    CHECK(ret[1](0,0) == 10);
    CHECK(ret[1](0,1) == 11);
    CHECK(ret[2](0,0) == 11);
    CHECK(ret[2](0,1) == 12);
    CHECK(ret[3](0,0) == 12);
    CHECK(ret[3](0,1) == 13);
    CHECK(ret[4](0,0) == 13);
    CHECK(ret[4](0,1) == 14);
    CHECK(ret[5](0,0) == 14);
    CHECK(ret[5](0,1) == 15);
}

TEST_CASE("Test with one grain - horizon 2, lag 1") {
    using InputType = std::double_t;
    using TransformedType = NS::ColMajMatrix<std::double_t>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(2, {-1});
    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );

    transformer.execute(10, callback);
    CHECK(std::isnan(ret[0](0,0)));
    CHECK(std::isnan(ret[0](0,1)));
    transformer.execute(11, callback);
    CHECK(std::isnan(ret[1](0,0)));
    CHECK(ret[1](0,1) == 10);
    transformer.execute(12, callback);
    CHECK(ret[2](0,0) == 10);
    CHECK(ret[2](0,1) == 11);
    transformer.execute(13, callback);
    CHECK(ret[3](0,0) == 11);
    CHECK(ret[3](0,1) == 12);
    transformer.execute(14, callback);
    CHECK(ret[4](0,0) == 12);
    CHECK(ret[4](0,1) == 13);
    transformer.execute(15, callback);
    CHECK(ret[5](0,0) == 13);
    CHECK(ret[5](0,1) == 14);
    transformer.execute(16, callback);
    CHECK(ret[6](0,0) == 14);
    CHECK(ret[6](0,1) == 15);
    transformer.execute(17, callback);
    CHECK(ret[7](0,0) == 15);
    CHECK(ret[7](0,1) == 16);
}

TEST_CASE("Test with one grain - horizon 1, lag 2 lag 1") {
    using InputType = std::double_t;
    using TransformedType = NS::ColMajMatrix<std::double_t>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(1, {-3, -1});
    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );

    transformer.execute(10, callback);
    CHECK(std::isnan(ret[0](0,0)));
    CHECK(std::isnan(ret[0](1,0)));
    transformer.execute(11, callback);
    CHECK(std::isnan(ret[1](0,0)));
    CHECK(ret[1](1,0) == 10);
    transformer.execute(12, callback);
    CHECK(std::isnan(ret[2](0,0)));
    CHECK(ret[2](1,0) == 11);
    transformer.execute(13, callback);
    CHECK(ret[3](0,0) == 10);
    CHECK(ret[3](1,0) == 12);
    transformer.execute(14, callback);
    CHECK(ret[4](0,0) == 11);
    CHECK(ret[4](1,0) == 13);
    transformer.execute(15, callback);
    CHECK(ret[5](0,0) == 12);
    CHECK(ret[5](1,0) == 14);
    transformer.execute(16, callback);
    CHECK(ret[6](0,0) == 13);
    CHECK(ret[6](1,0) == 15);
    transformer.execute(17, callback);
    CHECK(ret[7](0,0) == 14);
    CHECK(ret[7](1,0) == 16);
}

TEST_CASE("Test with one grain - horizon 1, lag 1 lead 1") {
    using InputType = std::double_t;
    using TransformedType = NS::ColMajMatrix<std::double_t>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(1, {-1, 1});
    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );

    transformer.execute(10, callback);
    transformer.execute(11, callback);
    transformer.execute(12, callback);
    transformer.execute(13, callback);
    transformer.execute(14, callback);
    transformer.flush(callback);
    
    CHECK(std::isnan(ret[0](0,0)));
    CHECK(ret[0](1,0) == 11);
    CHECK(ret[1](0,0) == 10);
    CHECK(ret[1](1,0) == 12);
    CHECK(ret[2](0,0) == 11);
    CHECK(ret[2](1,0) == 13);
    CHECK(ret[3](0,0) == 12);
    CHECK(ret[3](1,0) == 14);
    CHECK(ret[4](0,0) == 13);
    CHECK(std::isnan(ret[4](1,0)));
}

TEST_CASE("Test with one grain - horizon 2, lag 3 lag 2 lead 1 lead 3") {
    using InputType = std::double_t;
    using TransformedType = NS::ColMajMatrix<std::double_t>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(2, {-3, -2, 1, 3});
    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );

    transformer.execute(10, callback);
    transformer.execute(11, callback);
    transformer.execute(12, callback);
    transformer.execute(13, callback);
    transformer.execute(14, callback);
    transformer.execute(15, callback);
    transformer.flush(callback);
    // output matrix for row "1", 10
    CHECK(std::isnan(ret[0](0,0)));
    CHECK(std::isnan(ret[0](0,1)));
    CHECK(std::isnan(ret[0](1,0)));
    CHECK(std::isnan(ret[0](1,1)));
    CHECK(ret[0](2,0) == 10);
    CHECK(ret[0](2,1) == 11);
    CHECK(ret[0](3,0) == 12);
    CHECK(ret[0](3,1) == 13);

    // output matrix for row "1", 11
    CHECK(std::isnan(ret[1](0,0)));
    CHECK(std::isnan(ret[1](0,1)));
    CHECK(std::isnan(ret[1](1,0)));
    CHECK(std::isnan(ret[1](1,1)));
    CHECK(ret[1](2,0) == 11);
    CHECK(ret[1](2,1) == 12);
    CHECK(ret[1](3,0) == 13);
    CHECK(ret[1](3,1) == 14);

    // output matrix for row "1", 12
    CHECK(std::isnan(ret[2](0,0)));
    CHECK(std::isnan(ret[2](0,1)));
    CHECK(std::isnan(ret[2](1,0)));
    CHECK(ret[2](1,1) == 10);
    CHECK(ret[2](2,0) == 12);
    CHECK(ret[2](2,1) == 13);
    CHECK(ret[2](3,0) == 14);
    CHECK(ret[2](3,1) == 15);

    // output matrix for row "1", 13
    CHECK(std::isnan(ret[3](0,0)));
    CHECK(ret[3](0,1) == 10);
    CHECK(ret[3](1,0) == 10);
    CHECK(ret[3](1,1) == 11);
    CHECK(ret[3](2,0) == 13);
    CHECK(ret[3](2,1) == 14);
    CHECK(ret[3](3,0) == 15);
    CHECK(std::isnan(ret[3](3,1)));

    // output matrix for row "1", 14
    CHECK(ret[4](0,0) == 10);
    CHECK(ret[4](0,1) == 11);
    CHECK(ret[4](1,0) == 11);
    CHECK(ret[4](1,1) == 12);
    CHECK(ret[4](2,0) == 14);
    CHECK(ret[4](2,1) == 15);
    CHECK(std::isnan(ret[4](3,0)));
    CHECK(std::isnan(ret[4](3,1)));

    // output matrix for row "1", 15
    CHECK(ret[5](0,0) == 11);
    CHECK(ret[5](0,1) == 12);
    CHECK(ret[5](1,0) == 12);
    CHECK(ret[5](1,1) == 13);
    CHECK(ret[5](2,0) == 15);
    CHECK(std::isnan(ret[5](2,1)));
    CHECK(std::isnan(ret[5](3,0)));
    CHECK(std::isnan(ret[5](3,1)));
}

TEST_CASE("Serialization") {
    using InputType = std::double_t;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>   original(2, {-3, -2, 1, 3});
    NS::Archive                                                             out;

    original.save(out);

    NS::Archive                                                             in(out.commit());
    NS::Featurizers::LagLeadOperatorTransformer<InputType>   other(in);

    CHECK(other == original);
}

TEST_CASE("Serialization Version Error") {
    using InputType = std::double_t;
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        (NS::Featurizers::LagLeadOperatorTransformer<InputType>(in)),
        Catch::Contains("Unsupported archive version")
    );
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
