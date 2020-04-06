// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_ForecastingPivotFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("Standard") {
    // ----------------------------------------------------------------------
    using Type                              = double;
    using NullableType                      = Microsoft::Featurizer::Traits<double>::nullable_type;
    using TransformedType                   = std::vector<Type>;
    using Matrix                            = Microsoft::Featurizer::RowMajMatrix<NullableType>;
    using Matrixes                          = std::vector<Matrix>;
    // ----------------------------------------------------------------------

    size_t const                            numRows(3);

    auto const                              createMatrixFunc(
        [&numRows](std::vector<double> values) {
            assert(values.size() % numRows == 0);

            size_t const                    numCols(values.size() / numRows);
            double const *                  ptr(values.data());
            Matrix                          result(numRows, numCols);

            for(size_t row = 0; row < numRows; ++row) {
                for(size_t col = 0; col < numCols; ++col) {
                    result(static_cast<Eigen::Index>(row), static_cast<Eigen::Index>(col)) = *ptr++;
                }
            }

            return result;
        }
    );

    Matrix                                  m1(
        createMatrixFunc(
            {
                1, 2, 3, Microsoft::Featurizer::Traits<double>::CreateNullValue(),
                5, 6, Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(),
                9, 10, Microsoft::Featurizer::Traits<double>::CreateNullValue(), 12
            }
        )
    );

    Matrix                                  m2(
        createMatrixFunc(
            {
                100, 200,  300,  400,
                500, 600,  700,  800,
                900, 1000, 1010, 1020
            }
        )
    );

    ForecastingPivotFeaturizer_double_Test(
        std::vector<Matrixes>(),
        std::vector<Matrixes>{
            Matrixes{ std::move(m1), std::move(m2) }
        },
        [](std::vector<std::vector<TransformedType>> const &args) {
            REQUIRE(args.size() == 2); // 1 for the first input, 1 for flush

            CHECK(args[1].empty());

            CHECK(args[0].size() == 2);
            CHECK(args[0][0] == TransformedType{ 1.0, 5.0, 9.0, 100.0, 500.0, 900.0 });
            CHECK(args[0][1] == TransformedType{ 2.0, 6.0, 10.0, 200.0, 600.0, 1000.0 });

            return true;
        }
    );
}
