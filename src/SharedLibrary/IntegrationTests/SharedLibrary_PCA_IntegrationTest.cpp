// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_PCAFeaturizer.h"

TEST_CASE("float") {
    // ----------------------------------------------------------------------
    using InputMatrix                       = Eigen::Map<Eigen::MatrixX<float>>;
    using OutputMatrix                      = Microsoft::Featurizer::RowMajMatrix<float>;
    // ----------------------------------------------------------------------

    // Row-based data
    float                                   trainingData[]{
        -1, -1, 0,
        0, -2, -1,
        -3, 0, -2
    };
    InputMatrix                             trainingMatrix(trainingData, 3, 3);

    float                                   inferenceData[]{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1

    };
    InputMatrix                             inferenceMatrix(inferenceData, 3, 3);

    PCAFeaturizer_float_Test(
        std::vector<InputMatrix>{trainingMatrix},
        std::vector<InputMatrix>{inferenceMatrix},
        [](std::vector<OutputMatrix> const &args) {
            REQUIRE(args.size() == 1);

            OutputMatrix const &            output(args[0]);
            OutputMatrix                    expected(3, 3);

            expected(0, 0) =  0.588348f;
            expected(0, 1) =  0.784465f;
            expected(0, 2) = -0.196116f;
            expected(1, 0) =  0.196583f;
            expected(1, 1) = -0.374023f;
            expected(1, 2) = -0.906345f;
            expected(2, 0) =  0.784348f;
            expected(2, 1) = -0.494694f;
            expected(2, 2) =  0.374268f;

            for (OutputMatrix::Index col=0; col < output.cols(); ++col) {
                for (OutputMatrix::Index row=0; row < output.rows(); ++row) {
                    CHECK(Approx(output(row, col)) == expected(row, col));
                }
            }

            return true;
        }
    );
}
