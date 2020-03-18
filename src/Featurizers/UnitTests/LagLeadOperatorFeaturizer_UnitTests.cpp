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

// TODO: change type in tuple to const &

TEST_CASE("Test with one grain - horizon 2, lag 1") {
    using InputType = std::tuple<std::vector<std::string> const &, std::double_t const &>;
    using TransformedType = NS::ColMajMatrix<std::double_t>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(2, {-1});
    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );
    const std::vector<std::string> grain({"one"});
    const std::double_t target1(10);
    const std::double_t target2(11);
    const std::double_t target3(12);
    const std::double_t target4(13);
    const std::double_t target5(14);
    const std::double_t target6(15);
    const std::double_t target7(16);
    const std::double_t target8(17);

    const auto tup1 = std::make_tuple(grain, target1);
    const auto tup2 = std::make_tuple(grain, target2);
    const auto tup3 = std::make_tuple(grain, target3);
    const auto tup4 = std::make_tuple(grain, target4);
    const auto tup5 = std::make_tuple(grain, target5);
    const auto tup6 = std::make_tuple(grain, target6);
    const auto tup7 = std::make_tuple(grain, target7);
    const auto tup8 = std::make_tuple(grain, target8);

    transformer.execute(tup1, callback);
    CHECK(std::isnan(ret[0](0,0)));
    CHECK(std::isnan(ret[0](0,1)));
    transformer.execute(tup2, callback);
    CHECK(std::isnan(ret[1](0,0)));
    CHECK(ret[1](0,1) == 10);
    transformer.execute(tup3, callback);
    CHECK(ret[2](0,0) == 10);
    CHECK(ret[2](0,1) == 11);
    transformer.execute(tup4, callback);
    CHECK(ret[3](0,0) == 11);
    CHECK(ret[3](0,1) == 12);
    transformer.execute(tup5, callback);
    CHECK(ret[4](0,0) == 12);
    CHECK(ret[4](0,1) == 13);
    transformer.execute(tup6, callback);
    CHECK(ret[5](0,0) == 13);
    CHECK(ret[5](0,1) == 14);
    transformer.execute(tup7, callback);
    CHECK(ret[6](0,0) == 14);
    CHECK(ret[6](0,1) == 15);
    transformer.execute(tup8, callback);
    CHECK(ret[7](0,0) == 15);
    CHECK(ret[7](0,1) == 16);
}

TEST_CASE("Test with one grain - horizon 1, lag 2 lag 1") {
    using InputType = std::tuple<std::vector<std::string> const &, std::double_t const &>;
    using TransformedType = NS::ColMajMatrix<std::double_t>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(1, {-3, -1});
    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );

    const std::vector<std::string> grain({"one"});
    const std::double_t target1(10);
    const std::double_t target2(11);
    const std::double_t target3(12);
    const std::double_t target4(13);
    const std::double_t target5(14);
    const std::double_t target6(15);
    const std::double_t target7(16);
    const std::double_t target8(17);

    const auto tup1 = std::make_tuple(grain, target1);
    const auto tup2 = std::make_tuple(grain, target2);
    const auto tup3 = std::make_tuple(grain, target3);
    const auto tup4 = std::make_tuple(grain, target4);
    const auto tup5 = std::make_tuple(grain, target5);
    const auto tup6 = std::make_tuple(grain, target6);
    const auto tup7 = std::make_tuple(grain, target7);
    const auto tup8 = std::make_tuple(grain, target8);

    transformer.execute(tup1, callback);
    CHECK(std::isnan(ret[0](0,0)));
    CHECK(std::isnan(ret[0](1,0)));
    transformer.execute(tup2, callback);
    CHECK(std::isnan(ret[1](0,0)));
    CHECK(ret[1](1,0) == 10);
    transformer.execute(tup3, callback);
    CHECK(std::isnan(ret[2](0,0)));
    CHECK(ret[2](1,0) == 11);
    transformer.execute(tup4, callback);
    CHECK(ret[3](0,0) == 10);
    CHECK(ret[3](1,0) == 12);
    transformer.execute(tup5, callback);
    CHECK(ret[4](0,0) == 11);
    CHECK(ret[4](1,0) == 13);
    transformer.execute(tup6, callback);
    CHECK(ret[5](0,0) == 12);
    CHECK(ret[5](1,0) == 14);
    transformer.execute(tup7, callback);
    CHECK(ret[6](0,0) == 13);
    CHECK(ret[6](1,0) == 15);
    transformer.execute(tup8, callback);
    CHECK(ret[7](0,0) == 14);
    CHECK(ret[7](1,0) == 16);
}

TEST_CASE("Test with one grain - horizon 1, lag 1 lead 1") {
    using InputType = std::tuple<std::vector<std::string> const &, std::double_t const &>;
    using TransformedType = NS::ColMajMatrix<std::double_t>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(1, {-1, 1});
    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );
    
    const std::vector<std::string> grain({"one"});
    const std::double_t target1(10);
    const std::double_t target2(11);
    const std::double_t target3(12);
    const std::double_t target4(13);
    const std::double_t target5(14);

    const auto tup1 = std::make_tuple(grain, target1);
    const auto tup2 = std::make_tuple(grain, target2);
    const auto tup3 = std::make_tuple(grain, target3);
    const auto tup4 = std::make_tuple(grain, target4);
    const auto tup5 = std::make_tuple(grain, target5);

    transformer.execute(tup1, callback);
    transformer.execute(tup2, callback);
    transformer.execute(tup3, callback);
    transformer.execute(tup4, callback);
    transformer.execute(tup5, callback);
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
    using InputType = std::tuple<std::vector<std::string> const &, std::double_t const &>;
    using TransformedType = NS::ColMajMatrix<std::double_t>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(2, {-3, -2, 1, 3});
    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );
    
    const std::vector<std::string> grain({"one"});
    const std::double_t target1(10);
    const std::double_t target2(11);
    const std::double_t target3(12);
    const std::double_t target4(13);
    const std::double_t target5(14);
    const std::double_t target6(15);

    const auto tup1 = std::make_tuple(grain, target1);
    const auto tup2 = std::make_tuple(grain, target2);
    const auto tup3 = std::make_tuple(grain, target3);
    const auto tup4 = std::make_tuple(grain, target4);
    const auto tup5 = std::make_tuple(grain, target5);
    const auto tup6 = std::make_tuple(grain, target6);

    transformer.execute(tup1, callback);
    transformer.execute(tup2, callback);
    transformer.execute(tup3, callback);
    transformer.execute(tup4, callback);
    transformer.execute(tup5, callback);
    transformer.execute(tup6, callback);
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
    using InputType = std::tuple<std::vector<std::string> const &, std::double_t const &>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>   original(2, {-3, -2, 1, 3});
    NS::Archive                                                             out;

    original.save(out);

    NS::Archive                                                             in(out.commit());
    NS::Featurizers::LagLeadOperatorTransformer<InputType>   other(in);

    CHECK(other == original);
}

TEST_CASE("Serialization Version Error") {
    using InputType = std::tuple<std::vector<std::string> const &, std::double_t const &>;
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
