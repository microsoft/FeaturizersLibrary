// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../ForecastingPivotFeaturizer.h"
#include "../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

TEST_CASE("Invalid execute argument") {
    using InputType       = std::double_t;
    using NullableType    = NS::Traits<InputType>::nullable_type;
    using TransformedType = std::vector<InputType>;
    using MatrixType      = NS::RowMajMatrix<NullableType>;

    MatrixType matrix1(3, 4);
    MatrixType matrix2(2, 3);

    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );
    
    CHECK_THROWS_WITH(NS::Featurizers::ForecastingPivotTransformer<InputType>().execute({}, callback), "There's no input matrix passed in!");
    CHECK_THROWS_WITH(NS::Featurizers::ForecastingPivotTransformer<InputType>().execute(NS::TestHelpers::make_vector<MatrixType>(matrix1, matrix2), callback), "All input matrixes should have the same number of columns!");
}


TEST_CASE("One matrix of double") {
    using InputType       = std::double_t;
    using NullableType    = NS::Traits<InputType>::nullable_type;
    using TransformedType = std::vector<InputType>;
    using MatrixType      = NS::RowMajMatrix<NullableType>;

    MatrixType                                  matrix(3, 4);

    // 1    4    6 null
    // 2    5 null null
    // 3 null null    7
    matrix(0, 0) = 1;
    matrix(0, 1) = 4;
    matrix(0, 2) = 6;
    matrix(0, 3) = NS::Traits<NullableType>::CreateNullValue();
    matrix(1, 0) = 2;
    matrix(1, 1) = 5;
    matrix(1, 2) = NS::Traits<NullableType>::CreateNullValue();
    matrix(1, 3) = NS::Traits<NullableType>::CreateNullValue();
    matrix(2, 0) = 3;
    matrix(2, 1) = NS::Traits<NullableType>::CreateNullValue();
    matrix(2, 2) = NS::Traits<NullableType>::CreateNullValue();
    matrix(2, 3) = 7;

    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );

    NS::Featurizers::ForecastingPivotTransformer<InputType>().execute(NS::TestHelpers::make_vector<MatrixType>(matrix), callback);

    CHECK(ret.size()    == 1);
    CHECK(ret[0].size() == 3);
    CHECK(ret[0][0]     == 1);
    CHECK(ret[0][1]     == 2);
    CHECK(ret[0][2]     == 3);
}

TEST_CASE("Two matrixes of string") {
    using InputType       = std::string;
    using NullableType    = NS::Traits<InputType>::nullable_type;
    using TransformedType = std::vector<InputType>;
    using MatrixType      = NS::RowMajMatrix<NullableType>;

    MatrixType                                  matrix1(3, 4);
    MatrixType                                  matrix2(2, 4);

    // matrix1
    // "one"   "six" "three"  "nine"
    // "two"  "four"  "five" "eight"
    //  null    null "seven"   "ten"
    matrix1(0, 0) = "one";
    matrix1(0, 1) = "six";
    matrix1(0, 2) = "three";
    matrix1(0, 3) = "nine";
    matrix1(1, 0) = "two";
    matrix1(1, 1) = "four";
    matrix1(1, 2) = "five";
    matrix1(1, 3) = "eight";
    matrix1(2, 0) = NS::Traits<NullableType>::CreateNullValue();
    matrix1(2, 1) = NS::Traits<NullableType>::CreateNullValue();
    matrix1(2, 2) = "seven";
    matrix1(2, 3) = "ten";

    // matrix2
    //    "1"  null    "5"      "6"
    //    "2"  null    "3"      "4"
    matrix2(0, 0) = "1";
    matrix2(0, 1) = NS::Traits<NullableType>::CreateNullValue();
    matrix2(0, 2) = "5";
    matrix2(0, 3) = "6";
    matrix2(1, 0) = "2";
    matrix2(1, 1) = NS::Traits<NullableType>::CreateNullValue();
    matrix2(1, 2) = "3";
    matrix2(1, 3) = "4";

    std::vector<TransformedType> ret;
    auto const              callback(
        [&ret](TransformedType value) {
            ret.emplace_back(value);
        }
    );

    NS::Featurizers::ForecastingPivotTransformer<InputType>().execute(NS::TestHelpers::make_vector<MatrixType>(matrix1, matrix2), callback);

    CHECK(ret.size()    == 2);
    CHECK(ret[0].size() == 5);
    CHECK(ret[1].size() == 5);

    CHECK(ret[0][0]     == "three");
    CHECK(ret[0][1]     == "five");
    CHECK(ret[0][2]     == "seven");
    CHECK(ret[0][3]     == "5");
    CHECK(ret[0][4]     == "3");

    CHECK(ret[1][0]     == "nine");
    CHECK(ret[1][1]     == "eight");
    CHECK(ret[1][2]     == "ten");
    CHECK(ret[1][3]     == "6");
    CHECK(ret[1][4]     == "4");
}

TEST_CASE("Transformer serialization") {
    NS::Featurizers::ForecastingPivotTransformer<int>   original;
    NS::Archive                                         out;

    original.save(out);

    NS::Archive                                         in(out.commit());

    NS::Featurizers::ForecastingPivotTransformer<int>   other(in);

    CHECK(other == original);
}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        NS::Featurizers::ForecastingPivotTransformer<int>(in),
        Catch::Contains("Unsupported archive version")
    );
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
