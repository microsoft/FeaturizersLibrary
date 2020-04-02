// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_SimpleRollingWindowFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("Max - double, window size 2, horizon 3") {
    std::vector<std::string> const          grain1{ "one" };
    std::vector<std::string> const          grain2{ "one", "two" };
    std::vector<std::string> const          grain3{ "one", "two", "three" };
    std::vector<std::string> const          grain4{ "completely_different" };
    double const                            value1(1);
    double const                            value2(2);
    double const                            value3(3);
    double const                            value4(4);
    uint32_t const                          horizon(3);

    SimpleRollingWindowFeaturizer_double_Test(
        std::vector<std::tuple<std::vector<std::string> const &, double const &>>(),
        std::vector<std::tuple<std::vector<std::string> const &, double const &>>{
            std::make_tuple(grain1, value1),
            std::make_tuple(grain1, value2),
            std::make_tuple(grain1, value3),
            std::make_tuple(grain1, value4),

            std::make_tuple(grain2, value1),
            std::make_tuple(grain2, value2),
            std::make_tuple(grain2, value3),

            std::make_tuple(grain3, value1),
            std::make_tuple(grain3, value2),

            std::make_tuple(grain4, value1),

            std::make_tuple(grain2, value4),

            std::make_tuple(grain3, value3),
            std::make_tuple(grain3, value4),

            std::make_tuple(grain4, value2),
            std::make_tuple(grain4, value3),
            std::make_tuple(grain4, value4)
        },
        [&horizon](std::vector<Microsoft::Featurizer::RowMajMatrix<double>> const &args) -> bool {
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
            REQUIRE(args.size() == 16);

            CHECK(args[0].rows() == 1);
            CHECK(args[0].cols() == horizon);
            CHECK(
                compareFunc(
                    args[0],
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue()
                        }
                    )
                )
            );
            
            CHECK(args[1].rows() == 1);
            CHECK(args[1].cols() == horizon);
            CHECK(
                compareFunc(
                    args[1],
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1
                        }
                    )
                )
            );

            CHECK(args[2].rows() == 1);
            CHECK(args[2].cols() == horizon);
            CHECK(
                compareFunc(
                    args[2],
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1, 2
                        }
                    )
                )
            );
            
            CHECK(args[3].rows() == 1);
            CHECK(args[3].cols() == horizon);
            CHECK(
                compareFunc(
                    args[3],
                    createMatrixFunc(
                        {
                            1, 2, 3
                        }
                    )
                )
            );
            
            CHECK(args[4].rows() == 1);
            CHECK(args[4].cols() == horizon);
            CHECK(
                compareFunc(
                    args[4],
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue()
                        }
                    )
                )
            );
            
            CHECK(args[5].rows() == 1);
            CHECK(args[5].cols() == horizon);
            CHECK(
                compareFunc(
                    args[5],
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1
                        }
                    )
                )
            );

            CHECK(args[6].rows() == 1);
            CHECK(args[6].cols() == horizon);
            CHECK(
                compareFunc(
                    args[6],
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1.0, 2
                        }
                    )
                )
            );
            
            CHECK(args[7].rows() == 1);
            CHECK(args[7].cols() == horizon);
            CHECK(
                compareFunc(
                    args[7],
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue()
                        }
                    )
                )
            );
            
            CHECK(args[8].rows() == 1);
            CHECK(args[8].cols() == horizon);
            CHECK(
                compareFunc(
                    args[8],
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1
                        }
                    )
                )
            );
            
            CHECK(args[9].rows() == 1);
            CHECK(args[9].cols() == horizon);
            CHECK(
                compareFunc(
                    args[9],
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue()
                        }
                    )
                )
            );
            
            CHECK(args[10].rows() == 1);
            CHECK(args[10].cols() == horizon);
            CHECK(
                compareFunc(
                    args[10],
                    createMatrixFunc(
                        {
                            1.0, 2, 3
                        }
                    )
                )
            );
            
            CHECK(args[11].rows() == 1);
            CHECK(args[11].cols() == horizon);
            CHECK(
                compareFunc(
                    args[11],
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1.0, 2
                        }
                    )
                )
            );
            
            CHECK(args[12].rows() == 1);
            CHECK(args[12].cols() == horizon);
            CHECK(
                compareFunc(
                    args[12],
                    createMatrixFunc(
                        {
                            1.0, 2, 3
                        }
                    )
                )
            );
            
            CHECK(args[13].rows() == 1);
            CHECK(args[13].cols() == horizon);
            CHECK(
                compareFunc(
                    args[13],
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1
                        }
                    )
                )
            );
            
            CHECK(args[14].rows() == 1);
            CHECK(args[14].cols() == horizon);
            CHECK(
                compareFunc(
                    args[14],
                    createMatrixFunc(
                        {
                            Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1.0, 2
                        }
                    )
                )
            );
            
            CHECK(args[15].rows() == 1);
            CHECK(args[15].cols() == horizon);
            CHECK(
                compareFunc(
                    args[15],
                    createMatrixFunc(
                        {
                            1.0, 2, 3
                        }
                    )
                )
            );
            return true;
        },
        static_cast<SimpleRollingWindowFeaturizer_SimpleRollingWindowCalculationType>(SimpleRollingWindowFeaturizer_SimpleRollingWindowCalculation_Max),
        3UL,
        2UL,
        1UL
    );
}
