// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_LagLeadOperatorFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("Standard - double") {
    std::vector<std::string> const          grain1{ "one" };
    std::vector<std::string> const          grain2{ "one", "two" };
    std::vector<std::string> const          grain3{ "three" };
    std::vector<std::string> const          grain4{ "4", ".0", "0" };
    double const                            value10(10.0);
    double const                            value20(20.0);
    double const                            value30(30.0);
    double const                            value40(40.0);
    uint32_t const                          horizon(3);
    int64_t const                           offsets[] = {-1, 1};

    LagLeadOperatorFeaturizer_double_Test(
        std::vector<std::tuple<std::vector<std::string> const &, double const &>>(),
        std::vector<std::tuple<std::vector<std::string> const &, double const &>>{
            std::make_tuple(grain1, value10),   // 0
            std::make_tuple(grain1, value20),   // 1
            std::make_tuple(grain1, value30),   // 2
            std::make_tuple(grain1, value40),   // 3

            std::make_tuple(grain2, value10),   // 4
            std::make_tuple(grain2, value20),   // 5
            std::make_tuple(grain2, value30),   // 6

            std::make_tuple(grain3, value10),   // 7
            std::make_tuple(grain3, value20),   // 8

            std::make_tuple(grain4, value10)    // 9
        },
        [&grain1, &grain2, &grain3, &grain4, &horizon](std::vector<std::vector<std::tuple<std::vector<std::string>, Microsoft::Featurizer::RowMajMatrix<double>>>> const &args) -> bool {
            auto const                      createMatrixFunc(
                [&horizon](std::vector<double> values) {
                    assert(values.size() % horizon == 0);

                    size_t const                                            numRows(values.size() / horizon);
                    double const *                                          ptr(values.data());
                    Microsoft::Featurizer::RowMajMatrix<double>             result(numRows, horizon);

                    for(size_t row = 0; row < numRows; ++row) {
                        for(size_t col = 0; col < horizon; ++col) {
                            result(static_cast<Eigen::Index>(row), static_cast<Eigen::Index>(col)) = *ptr++;
                        }
                    }

                    return result;
                }
            );

            auto const                      compareFunc(
                [](Microsoft::Featurizer::RowMajMatrix<double> const &actualMatrix, Microsoft::Featurizer::RowMajMatrix<double> const &expectedMatrix) {
                    REQUIRE(actualMatrix.rows() == expectedMatrix.rows());
                    REQUIRE(actualMatrix.cols() == expectedMatrix.cols());

                    for(Eigen::Index row = 0; row < actualMatrix.rows(); ++row) {
                        for(Eigen::Index col = 0; col < actualMatrix.cols(); ++col) {
                            double const &  actual(actualMatrix(row, col));
                            double const &  expected(expectedMatrix(row, col));

                            if(
                                (Microsoft::Featurizer::Traits<double>::IsNull(actual) ^ Microsoft::Featurizer::Traits<double>::IsNull(expected))
                                || (Microsoft::Featurizer::Traits<double>::IsNull(actual) == false && Approx(actual) != expected)
                            ) {
                                // Compare using Catch2's matrix statement so that we get nice output
                                CHECK(actualMatrix == expectedMatrix);
                                return false;
                            }
                        }
                    }

                    return true;
                }
            );

            REQUIRE(args.size() == 11); // 10 values above, 1 for flush

            // grain1
            CHECK(args[0].empty());

            REQUIRE(args[1].size() == 1);
            CHECK(std::get<0>(args[1][0]) == grain1);
            CHECK(
                compareFunc(
                    std::get<1>(args[1][0]),
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(),
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), 10, 20
                        }
                    )
                )
            );

            REQUIRE(args[2].size() == 1);
            CHECK(std::get<0>(args[2][0]) == grain1);
            CHECK(
                compareFunc(
                    std::get<1>(args[2][0]),
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), 10,
                            10, 20, 30
                        }
                    )
                )
            );

            REQUIRE(args[3].size() == 1);
            CHECK(std::get<0>(args[3][0]) == grain1);
            CHECK(
                compareFunc(
                    std::get<1>(args[3][0]),
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), 10, 20,
                            20, 30, 40
                        }
                    )
                )
            );

            // grain2
            CHECK(args[4].empty());

            REQUIRE(args[5].size() == 1);
            CHECK(std::get<0>(args[5][0]) == grain2);
            CHECK(
                compareFunc(
                    std::get<1>(args[5][0]),
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(),
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), 10, 20
                        }
                    )
                )
            );

            REQUIRE(args[6].size() == 1);
            CHECK(std::get<0>(args[6][0]) == grain2);
            CHECK(
                compareFunc(
                    std::get<1>(args[6][0]),
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), 10,
                            10, 20, 30
                        }
                    )
                )
            );

            // grain3
            CHECK(args[7].empty());

            REQUIRE(args[8].size() == 1);
            CHECK(std::get<0>(args[8][0]) == grain3);
            CHECK(
                compareFunc(
                    std::get<1>(args[8][0]),
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(),
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), 10, 20
                        }
                    )
                )
            );

            // grain4
            CHECK(args[9].empty());

            // Flush
            REQUIRE(args[10].size() == 4);

            CHECK(std::get<0>(args[10][0]) == grain4);
            CHECK(
                compareFunc(
                    std::get<1>(args[10][0]),
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(),
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), 10, Microsoft::Featurizer::Traits<double>::CreateNullValue()
                        }
                    )
                )
            );

            CHECK(std::get<0>(args[10][1]) == grain1);
            CHECK(
                compareFunc(
                    std::get<1>(args[10][1]),
                    createMatrixFunc(
                        {
                            10, 20, 30,
                            30, 40, Microsoft::Featurizer::Traits<double>::CreateNullValue()
                        }
                    )
                )
            );

            CHECK(std::get<0>(args[10][2]) == grain2);
            CHECK(
                compareFunc(
                    std::get<1>(args[10][2]),
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), 10, 20,
                            20, 30, Microsoft::Featurizer::Traits<double>::CreateNullValue()
                        }
                    )
                )
            );

            CHECK(std::get<0>(args[10][3]) == grain3);
            CHECK(
                compareFunc(
                    std::get<1>(args[10][3]),
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), 10,
                            10, 20, Microsoft::Featurizer::Traits<double>::CreateNullValue()
                        }
                    )
                )
            );

            return true;
        },
        horizon,
        offsets,
        sizeof(offsets) / sizeof(*offsets)
    );
}
