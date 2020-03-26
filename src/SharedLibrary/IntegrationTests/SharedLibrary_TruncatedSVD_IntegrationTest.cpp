// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_TruncatedSVDFeaturizer.h"

TEST_CASE("double") {
    // ----------------------------------------------------------------------
    using InputMatrix                       = Eigen::Map<Eigen::MatrixX<double>>;
    using OutputMatrix                      = Eigen::MatrixX<double>;
    // ----------------------------------------------------------------------

    // Column-based data
    double                                  trainingData[]{
        -1, 0, -3,
        -1, -2, 0,
        0, -1, -2
    };
    InputMatrix                             trainingMatrix(trainingData, 3, 3);

    double                                  inferenceData[]{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
    InputMatrix                             inferenceMatrix(inferenceData, 3, 3);

    TruncatedSVDFeaturizer_double_Test(
        std::vector<InputMatrix>{trainingMatrix},
        std::vector<InputMatrix>{inferenceMatrix},
        [](std::vector<OutputMatrix> const &args) {
            REQUIRE(args.size() == 1);

            OutputMatrix const &            output(args[0]);
            OutputMatrix                    expected(3, 3);

            expected(0, 0) =  0.805055;
            expected(0, 1) = -0.315909;
            expected(0, 2) = -0.502083;
            expected(1, 0) =  0.204052;
            expected(1, 1) =  0.942224;
            expected(1, 2) = -0.265661;
            expected(2, 0) =  0.557;
            expected(2, 1) =  0.111421;
            expected(2, 2) =  0.823005;

            for (OutputMatrix::Index col=0; col < output.cols(); ++col) {
                for (OutputMatrix::Index row=0; row < output.rows(); ++row) {
                    CHECK(Approx(output(row, col)) == expected(row, col));
                }
            }

            return true;
        }
    );
}
