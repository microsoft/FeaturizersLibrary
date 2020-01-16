// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Structs.h"
#include "../TestHelpers.h"



namespace NS = Microsoft::Featurizer;

TEST_CASE("SparseVectorEncoding::ValueEncoding") {
    NS::Featurizers::SparseVectorEncoding<char>::ValueEncoding const        o1('a', 10);

    CHECK(o1.Value == 'a');
    CHECK(o1.Index == 10);

    CHECK(o1 == NS::Featurizers::SparseVectorEncoding<char>::ValueEncoding('a', 10));
    CHECK(o1 != NS::Featurizers::SparseVectorEncoding<char>::ValueEncoding('b', 10));
    CHECK(o1 != NS::Featurizers::SparseVectorEncoding<char>::ValueEncoding('a', 20));
}

TEST_CASE("SparseVectorEncoding::ValueEncoding - float") {
    NS::Featurizers::SparseVectorEncoding<float>::ValueEncoding const        o1(1.0f, 10);

    CHECK(o1.Value == 1.0f);
    CHECK(o1.Index == 10);

    CHECK(o1 == NS::Featurizers::SparseVectorEncoding<float>::ValueEncoding(1.0f, 10));
    CHECK(o1 != NS::Featurizers::SparseVectorEncoding<float>::ValueEncoding(2.0f, 10));
    CHECK(o1 != NS::Featurizers::SparseVectorEncoding<float>::ValueEncoding(1.0f, 20));
}

TEST_CASE("SparseVectorEncoding") {
    // ----------------------------------------------------------------------
    using VectorEncoding                    = NS::Featurizers::SparseVectorEncoding<char>;
    using ValueEncoding                     = typename VectorEncoding::ValueEncoding;
    // ----------------------------------------------------------------------

    VectorEncoding const                    o1(10, NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding('a', 10), ValueEncoding('b', 20), ValueEncoding('c', 30)));

    CHECK(o1.NumElements == 10);
    CHECK(o1.Values == NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding('a', 10), ValueEncoding('b', 20), ValueEncoding('c', 30)));
    CHECK(o1.Values != NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding('A', 10), ValueEncoding('b', 20), ValueEncoding('c', 30)));
    CHECK(o1.Values != NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding('a', 100), ValueEncoding('b', 20), ValueEncoding('c', 30)));
    CHECK(o1.Values != NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding('a', 10), ValueEncoding('B', 20), ValueEncoding('c', 30)));
    CHECK(o1.Values != NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding('a', 10), ValueEncoding('b', 20), ValueEncoding('c', 30), ValueEncoding('d', 40)));
}

TEST_CASE("SparseVectorEncoding - float") {
    // ----------------------------------------------------------------------
    using VectorEncoding                    = NS::Featurizers::SparseVectorEncoding<float>;
    using ValueEncoding                     = typename VectorEncoding::ValueEncoding;
    // ----------------------------------------------------------------------

    VectorEncoding const                    o1(10, NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding(1.0f, 10), ValueEncoding(2.0f, 20), ValueEncoding(3.0f, 30)));

    CHECK(o1.NumElements == 10);
    CHECK(o1.Values == NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding(1.0f, 10), ValueEncoding(2.0f, 20), ValueEncoding(3.0f, 30)));
    CHECK(o1.Values != NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding(100.0f, 10), ValueEncoding(2.0f, 20), ValueEncoding(3.0f, 30)));
    CHECK(o1.Values != NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding(1.0f, 100), ValueEncoding(2.0f, 20), ValueEncoding(3.0f, 30)));
    CHECK(o1.Values != NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding(1.0f, 10), ValueEncoding(200.0f, 20), ValueEncoding(3.0f, 30)));
    CHECK(o1.Values != NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding(1.0f, 10), ValueEncoding(2.0f, 20), ValueEncoding(3.0f, 30), ValueEncoding(4.0f, 40)));
}

TEST_CASE("SparseVectorEncoding - invalid construction") {
    // ----------------------------------------------------------------------
    using VectorEncoding                    = NS::Featurizers::SparseVectorEncoding<char>;
    using ValueEncoding                     = typename VectorEncoding::ValueEncoding;
    // ----------------------------------------------------------------------

    CHECK_THROWS_WITH(VectorEncoding(0, NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding('a', 10))), Catch::Matchers::Contains("is 0"));
    CHECK_THROWS_WITH(VectorEncoding(1, NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding('a', 10), ValueEncoding('b', 20))), Catch::Matchers::Contains("is invalid"));

    CHECK_THROWS_WITH(VectorEncoding(2, NS::TestHelpers::make_vector<ValueEncoding>()), Catch::Matchers::Contains("is empty"));
    CHECK_THROWS_WITH(VectorEncoding(2, NS::TestHelpers::make_vector<ValueEncoding>(ValueEncoding('a', 10), ValueEncoding('b', 1))), Catch::Matchers::Contains("is not ordered"));
}

TEST_CASE("SingleValueSparseVectorEncoding") {
    NS::Featurizers::SingleValueSparseVectorEncoding<char>                  o1(10, 'a', 2);

    CHECK(o1.NumElements == 10);
    CHECK(o1.Value == 'a');
    CHECK(o1.Index == 2);

    CHECK(o1 == NS::Featurizers::SingleValueSparseVectorEncoding<char>(10, 'a', 2));
    CHECK(o1 != NS::Featurizers::SingleValueSparseVectorEncoding<char>(20, 'a', 2));
    CHECK(o1 != NS::Featurizers::SingleValueSparseVectorEncoding<char>(10, 'b', 2));
    CHECK(o1 != NS::Featurizers::SingleValueSparseVectorEncoding<char>(10, 'a', 3));
}

TEST_CASE("SingleValueSparseVectorEncoding - invalid construction") {
    CHECK_THROWS_WITH(NS::Featurizers::SingleValueSparseVectorEncoding<char>(0, 'a', 2), Catch::Matchers::Contains("is 0"));
    CHECK_THROWS_WITH(NS::Featurizers::SingleValueSparseVectorEncoding<char>(10, 'a', 10), Catch::Matchers::Contains("is invalid"));
    CHECK_THROWS_WITH(NS::Featurizers::SingleValueSparseVectorEncoding<char>(10, 'a', 20), Catch::Matchers::Contains("is invalid"));
}

TEST_CASE("SingleValueSparseVectorEncoding - float") {
    NS::Featurizers::SingleValueSparseVectorEncoding<float>                 o1(10, 1.0f, 2);

    CHECK(o1.NumElements == 10);
    CHECK(o1.Value == 1.0f);
    CHECK(o1.Index == 2);

    CHECK(o1 == NS::Featurizers::SingleValueSparseVectorEncoding<float>(10, 1.0f, 2));
    CHECK(o1 != NS::Featurizers::SingleValueSparseVectorEncoding<float>(20, 1.0f, 2));
    CHECK(o1 != NS::Featurizers::SingleValueSparseVectorEncoding<float>(10, 2.0f, 2));
    CHECK(o1 != NS::Featurizers::SingleValueSparseVectorEncoding<float>(10, 1.0f, 3));
}


TEST_CASE("CSREncoding") {
    std::vector<std::int16_t>  values({1, 2, 3, 4, 5});
    std::vector<std::uint64_t> col({0, 1, 1, 3, 2});
    std::vector<std::uint64_t> row({0, 2, 3, 3, 5});
    NS::Featurizers::CSREncoding<std::int16_t>                  csr(values, col, row);

    CHECK(csr.Values   == values);
    CHECK(csr.ColIndex == col);
    CHECK(csr.RowIndex == row);

    CHECK(csr == NS::Featurizers::CSREncoding<std::int16_t>({1, 2, 3, 4, 5}, {0, 1, 1, 3, 2}, {0, 2, 3, 3, 5}));
    CHECK(csr != NS::Featurizers::CSREncoding<std::int16_t>({1, 2, 3, 4, 7}, {0, 1, 1, 3, 2}, {0, 2, 3, 3, 5}));
    CHECK(csr != NS::Featurizers::CSREncoding<std::int16_t>({1, 2, 3, 4, 5}, {0, 1, 2, 3, 2}, {0, 2, 3, 3, 5}));
    CHECK(csr != NS::Featurizers::CSREncoding<std::int16_t>({1, 2, 3, 4, 5}, {0, 1, 1, 3, 2}, {0, 3, 3, 3, 5}));
}

TEST_CASE("CSREncoding - invalid construction") {
    std::vector<std::int16_t>  values({1, 2, 3, 4, 5});
    std::vector<std::uint64_t> col({0, 1, 1, 3, 2});
    std::vector<std::uint64_t> errorRow1({1, 2, 3, 3, 5});
    CHECK_THROWS_WITH(NS::Featurizers::CSREncoding<std::int16_t>(values, col, errorRow1), "Row index array should start with 0!");

    std::vector<std::uint64_t> row({0, 2, 3, 3, 5});
    std::vector<std::uint64_t> errorCol({0, 1, 1, 3});
    CHECK_THROWS_WITH(NS::Featurizers::CSREncoding<std::int16_t>(values, errorCol, row), "Non-zero values array and column index array should have same size!");

    std::vector<std::uint64_t> errorRow2({0, 1, 1, 3, 6});
    CHECK_THROWS_WITH(NS::Featurizers::CSREncoding<std::int16_t>(values, col, errorRow2), "Last value of row index should be less than the size of column index array");
}
