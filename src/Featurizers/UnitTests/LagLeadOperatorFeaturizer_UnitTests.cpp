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
    using InputType = std::int16_t;
    NS::AnnotationMapsPtr pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    CHECK_THROWS_WITH(NS::Featurizers::LagLeadOperatorEstimator<InputType>(pAllColumnAnnotations, 0, {-1}), "Horizon cannot be 0!");
    CHECK_THROWS_WITH(NS::Featurizers::GrainedLagLeadOperatorEstimator<InputType>(pAllColumnAnnotations, 0, {-1}), "Horizon cannot be 0!");

    std::vector<std::int64_t> offset{};
    CHECK_THROWS_WITH(NS::Featurizers::LagLeadOperatorEstimator<InputType>(pAllColumnAnnotations, 1, offset), "Offsets is empty!");
    CHECK_THROWS_WITH(NS::Featurizers::GrainedLagLeadOperatorEstimator<InputType>(pAllColumnAnnotations, 1, offset), "Offsets is empty!");
}
TEST_CASE("Invalid transformer constructor parameter") {
    using InputType = std::int16_t;
    CHECK_THROWS_WITH(NS::Featurizers::LagLeadOperatorTransformer<InputType>(0, {-1}), "Horizon cannot be 0!");
    std::vector<std::int64_t> offset{};
    CHECK_THROWS_WITH(NS::Featurizers::LagLeadOperatorTransformer<InputType>(1, offset), "Offsets is empty!");
}

TEST_CASE("Transformer Test - horizon 2, lag 0") {
    using InputType = std::double_t;
    using OutputMatrixDataType = NS::Traits<InputType>::nullable_type;
    using TransformedType = NS::RowMajMatrix<OutputMatrixDataType>;
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
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](0,1)) == 10);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](0,0)) == 10);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](0,1)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](0,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](0,1)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,1)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,0)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,1)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,0)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,1)) == 15);
}

TEST_CASE("Transformer Test - horizon 2, lag 1") {
    using InputType = std::double_t;
    using OutputMatrixDataType = NS::Traits<InputType>::nullable_type;
    using TransformedType = NS::RowMajMatrix<OutputMatrixDataType>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(2, {-1});
    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );

    transformer.execute(10, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](0,1)));
    transformer.execute(11, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](0,1)) == 10);
    transformer.execute(12, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](0,0)) == 10);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](0,1)) == 11);
    transformer.execute(13, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,1)) == 12);
    transformer.execute(14, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,1)) == 13);
    transformer.execute(15, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,0)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,1)) == 14);
    transformer.execute(16, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[6](0,0)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[6](0,1)) == 15);
    transformer.execute(17, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[7](0,0)) == 15);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[7](0,1)) == 16);
}

TEST_CASE("Transformer Test - horizon 1, lag 3 lag 1") {
    using InputType = std::double_t;
    using OutputMatrixDataType = NS::Traits<InputType>::nullable_type;
    using TransformedType = NS::RowMajMatrix<OutputMatrixDataType>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(1, {-3, -1});
    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );

    transformer.execute(10, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](1,0)));
    transformer.execute(11, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](1,0)) == 10);
    transformer.execute(12, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[2](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](1,0)) == 11);
    transformer.execute(13, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,0)) == 10);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,0)) == 12);
    transformer.execute(14, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](1,0)) == 13);
    transformer.execute(15, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](1,0)) == 14);
    transformer.execute(16, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[6](0,0)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[6](1,0)) == 15);
    transformer.execute(17, callback);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[7](0,0)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[7](1,0)) == 16);
}

TEST_CASE("Transformer Test - horizon 2, lag 1 lag 1") {
    using InputType = std::double_t;
    using OutputMatrixDataType = NS::Traits<InputType>::nullable_type;
    using TransformedType = NS::RowMajMatrix<OutputMatrixDataType>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(2, {-1, -1});
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
    transformer.execute(16, callback);
    transformer.execute(17, callback);
    transformer.flush(callback);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](0,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](1,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](1,1)));

    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](0,1)) == 10);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](1,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](1,1)) == 10);

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](0,0)) == 10);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](0,1)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](1,0)) == 10);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](1,1)) == 11);

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,1)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,1)) == 12);

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,1)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](1,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](1,1)) == 13);

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,0)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,1)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](1,0)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](1,1)) == 14);

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[6](0,0)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[6](0,1)) == 15);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[6](1,0)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[6](1,1)) == 15);

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[7](0,0)) == 15);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[7](0,1)) == 16);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[7](1,0)) == 15);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[7](1,1)) == 16);
}

TEST_CASE("Transformer Test - horizon 3, lead 2 lead 2") {
    using InputType = std::double_t;
    using OutputMatrixDataType = NS::Traits<InputType>::nullable_type;
    using TransformedType = NS::RowMajMatrix<OutputMatrixDataType>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(3, {2, 2});
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
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](0,0)) == 10);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](0,1)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](0,2)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](1,0)) == 10);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](1,1)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](1,2)) == 12);

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](0,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](0,1)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](0,2)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](1,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](1,1)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](1,2)) == 13);

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](0,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](0,1)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](0,2)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](1,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](1,1)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](1,2)) == 14);

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,0)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,1)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,2)) == 15);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,0)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,1)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,2)) == 15);

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,0)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,1)) == 15);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[4](0,2)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](1,0)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](1,1)) == 15);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[4](1,2)));

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,0)) == 15);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[5](0,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[5](0,2)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](1,0)) == 15);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[5](1,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[5](1,2)));
}

TEST_CASE("Transformer Test - horizon 1, lead 1 lead 2") {
    using InputType = std::double_t;
    using OutputMatrixDataType = NS::Traits<InputType>::nullable_type;
    using TransformedType = NS::RowMajMatrix<OutputMatrixDataType>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(1, {1, 2});
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
    transformer.execute(16, callback);
    transformer.execute(17, callback);
    transformer.flush(callback);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](0,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](1,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](0,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](1,0)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](0,0)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](1,0)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,0)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,0)) == 15);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,0)) == 15);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](1,0)) == 16);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,0)) == 16);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](1,0)) == 17);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[6](0,0)) == 17);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[6](1,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[7](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[7](1,0)));
}

TEST_CASE("Transformer Test - horizon 1, lag 1 lead 1") {
    using InputType = std::double_t;
    using OutputMatrixDataType = NS::Traits<InputType>::nullable_type;
    using TransformedType = NS::RowMajMatrix<OutputMatrixDataType>;
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
    
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](1,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](0,0)) == 10);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](1,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](0,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](1,0)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,0)) == 14);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,0)) == 13);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[4](1,0)));
}

TEST_CASE("Transformer Test - horizon 2, lag 3 lag 2 lead 1 lead 3") {
    using InputType = std::string;
    using OutputMatrixDataType = NS::Traits<InputType>::nullable_type;
    using TransformedType = NS::RowMajMatrix<OutputMatrixDataType>;
    NS::Featurizers::LagLeadOperatorTransformer<InputType>             transformer(2, {-3, -2, 1, 3});
    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );

    transformer.execute("10", callback);
    transformer.execute("11", callback);
    transformer.execute("12", callback);
    transformer.execute("13", callback);
    transformer.execute("14", callback);
    transformer.execute("15", callback);
    transformer.flush(callback);
    // output matrix for row "1", 10
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](0,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](1,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](1,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](2,0)) == "10");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](2,1)) == "11");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](3,0)) == "12");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](3,1)) == "13");

    // output matrix for row "1", 11
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](0,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](1,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](1,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](2,0)) == "11");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](2,1)) == "12");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](3,0)) == "13");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](3,1)) == "14");

    // output matrix for row "1", 12
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[2](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[2](0,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[2](1,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](1,1)) == "10");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](2,0)) == "12");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](2,1)) == "13");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](3,0)) == "14");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](3,1)) == "15");

    // output matrix for row "1", 13
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[3](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,1)) == "10");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,0)) == "10");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,1)) == "11");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](2,0)) == "13");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](2,1)) == "14");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](3,0)) == "15");
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[3](3,1)));

    // output matrix for row "1", 14
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,0)) == "10");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,1)) == "11");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](1,0)) == "11");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](1,1)) == "12");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](2,0)) == "14");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](2,1)) == "15");
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[4](3,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[4](3,1)));

    // output matrix for row "1", 15
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,0)) == "11");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,1)) == "12");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](1,0)) == "12");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](1,1)) == "13");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](2,0)) == "15");
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[5](2,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[5](3,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[5](3,1)));
}


TEST_CASE("Estimator Test - horizon 2, lag 3 lag 2 lead 1 lead 3") {
    using InputType = std::string;
    using OutputMatrixDataType = NS::Traits<InputType>::nullable_type;
    using TransformedType = NS::RowMajMatrix<OutputMatrixDataType>;
    NS::AnnotationMapsPtr                                pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::LagLeadOperatorEstimator<InputType> estimator(pAllColumnAnnotations, 2, {-3, -2, 1, 3});
    estimator.begin_training();
    estimator.complete_training();
    auto transformer = estimator.create_transformer();

    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );

    transformer->execute("10", callback);
    transformer->execute("11", callback);
    transformer->execute("12", callback);
    transformer->execute("13", callback);
    transformer->execute("14", callback);
    transformer->execute("15", callback);
    transformer->flush(callback);
    // output matrix for row "1", 10
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](0,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](1,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[0](1,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](2,0)) == "10");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](2,1)) == "11");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](3,0)) == "12");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](3,1)) == "13");

    // output matrix for row "1", 11
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](0,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](1,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](1,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](2,0)) == "11");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](2,1)) == "12");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](3,0)) == "13");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](3,1)) == "14");

    // output matrix for row "1", 12
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[2](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[2](0,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[2](1,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](1,1)) == "10");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](2,0)) == "12");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](2,1)) == "13");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](3,0)) == "14");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](3,1)) == "15");

    // output matrix for row "1", 13
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[3](0,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,1)) == "10");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,0)) == "10");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,1)) == "11");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](2,0)) == "13");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](2,1)) == "14");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](3,0)) == "15");
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[3](3,1)));

    // output matrix for row "1", 14
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,0)) == "10");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,1)) == "11");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](1,0)) == "11");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](1,1)) == "12");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](2,0)) == "14");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](2,1)) == "15");
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[4](3,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[4](3,1)));

    // output matrix for row "1", 15
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,0)) == "11");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,1)) == "12");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](1,0)) == "12");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](1,1)) == "13");
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](2,0)) == "15");
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[5](2,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[5](3,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[5](3,1)));
}

TEST_CASE("Grained Estimator Test - 1 grain, horizon 2, lead 1 lead 2") {    
    using InputType = std::int64_t;
    using GrainType = std::vector<std::string>;
    using OutputMatrixDataType = NS::Traits<InputType>::nullable_type;
    using TransformedType = NS::RowMajMatrix<OutputMatrixDataType>;
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::GrainedLagLeadOperatorEstimator<InputType>      estimator(pAllColumnAnnotations, 2, {1, 2});

    using GrainedInputType = std::tuple<GrainType const &, InputType const &>;

    const GrainType grain({"one"});
    const GrainedInputType tup1 = std::make_tuple(grain, 10ll);
    const GrainedInputType tup2 = std::make_tuple(grain, 11ll);
    const GrainedInputType tup3 = std::make_tuple(grain, 12ll);

    NS::TestHelpers::Train(estimator, NS::TestHelpers::make_vector<GrainedInputType>(tup1, tup2, tup3));
    auto transformer = estimator.create_transformer();

    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );
    transformer->execute(tup1, callback);
    transformer->execute(tup2, callback);
    transformer->execute(tup3, callback);
    transformer->flush(callback);
    
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](0,0)) == 10);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](0,1)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](1,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](1,1)) == 12);

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](0,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](0,1)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](1,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](1,1)));
    
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](0,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[2](0,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[2](1,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[2](1,1)));
}


TEST_CASE("Grained Estimator - 2 grain, horizon 2, lead 1 lead 2") {    
    using InputType = std::int64_t;
    using GrainType = std::vector<std::string>;
    using OutputMatrixDataType = NS::Traits<InputType>::nullable_type;
    using TransformedType = NS::RowMajMatrix<OutputMatrixDataType>;
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::GrainedLagLeadOperatorEstimator<InputType>      estimator(pAllColumnAnnotations, 2, {1, 2});

    using GrainedInputType = std::tuple<GrainType const &, InputType const &>;

    const GrainType grain1({"one"});
    const GrainedInputType tup1 = std::make_tuple(grain1, 10ll);
    const GrainedInputType tup2 = std::make_tuple(grain1, 11ll);
    const GrainedInputType tup3 = std::make_tuple(grain1, 12ll);

    const GrainType grain2({"two"});
    const GrainedInputType tup4 = std::make_tuple(grain2, 20ll);
    const GrainedInputType tup5 = std::make_tuple(grain2, 21ll);
    const GrainedInputType tup6 = std::make_tuple(grain2, 22ll);

    NS::TestHelpers::Train(estimator, NS::TestHelpers::make_vector<GrainedInputType>(tup1, tup2, tup3, tup4, tup5, tup6));
    auto transformer = estimator.create_transformer();

    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );
    transformer->execute(tup1, callback);
    transformer->execute(tup2, callback);
    transformer->execute(tup3, callback);
    transformer->flush(callback);

    transformer->execute(tup4, callback);
    transformer->execute(tup5, callback);
    transformer->execute(tup6, callback);
    transformer->flush(callback);
    
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](0,0)) == 10);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](0,1)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](1,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[0](1,1)) == 12);

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](0,0)) == 11);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](0,1)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[1](1,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[1](1,1)));
    
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[2](0,0)) == 12);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[2](0,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[2](1,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[2](1,1)));

    
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,0)) == 20);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](0,1)) == 21);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,0)) == 21);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[3](1,1)) == 22);

    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,0)) == 21);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](0,1)) == 22);
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[4](1,0)) == 22);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[4](1,1)));
    
    CHECK(NS::Traits<OutputMatrixDataType>::GetNullableValue(ret[5](0,0)) == 22);
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[5](0,1)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[5](1,0)));
    CHECK(NS::Traits<OutputMatrixDataType>::IsNull(ret[5](1,1)));
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
