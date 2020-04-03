// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../SimpleRollingWindowFeaturizer.h"
#include "../TestHelpers.h"
#include "../../Traits.h"

namespace NS = Microsoft::Featurizer;

using InputType = std::int32_t;
using OutputType = NS::Featurizers::SimpleRollingWindowTransformer<InputType>::TransformedType;
using MatrixMemberType = NS::Traits<InputType>::nullable_type;

TEST_CASE("Min - int32, window size 1, horizon 1") {

    NS::Featurizers::SimpleRollingWindowTransformer<InputType>                transformer(NS::Featurizers::SimpleRollingWindowCalculation::Min, 1, 1);

    OutputType results = transformer.execute(1);

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN}
    CHECK(results.cols() == 1);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));

    results = transformer.execute(2);

    // Correct result is now {1}
    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 1);

    results = transformer.execute(3);

    // Correct result is now {2}
    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 2);

    results = transformer.execute(4);

    // Correct result is now {3}
    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 3);
}

TEST_CASE("Min - int32, window size 2, horizon 1") {
    NS::Featurizers::SimpleRollingWindowTransformer<InputType>                transformer(NS::Featurizers::SimpleRollingWindowCalculation::Min, 1, 2);

    OutputType results = transformer.execute(1);

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN}
    CHECK(results.cols() == 1);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));

    results = transformer.execute(2);

    // Correct result is now {1}
    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 1);

    results = transformer.execute(3);

    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 1);

    results = transformer.execute(4);

    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 2);
}

TEST_CASE("Max - int32, window size 2, horizon 1, min window size 2") {
    NS::Featurizers::SimpleRollingWindowTransformer<InputType>                transformer(NS::Featurizers::SimpleRollingWindowCalculation::Max, 1, 2, 2);

    OutputType results = transformer.execute(1);

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN}
    CHECK(results.cols() == 1);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));

    results = transformer.execute(2);

    // Correct result is still {NaN} due to min window size of 2
    CHECK(results.cols() == 1);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));

    results = transformer.execute(3);

    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 2);

    results = transformer.execute(4);

    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 3);
}

TEST_CASE("Max - int32, window size 1, horizon 2") {
    NS::Featurizers::SimpleRollingWindowTransformer<InputType>                transformer(NS::Featurizers::SimpleRollingWindowCalculation::Max, 2, 1);

    OutputType results = transformer.execute(1);

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN, NaN}
    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 1)));

    results = transformer.execute(2);

    // Correct result is now {NaN, 1}
    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(results(0, 1) == 1);

    results = transformer.execute(3);

    // Correct result is now {1, 2}
    CHECK(results.cols() == 2);
    CHECK(results(0, 0) == 1);
    CHECK(results(0, 1) == 2);

    results = transformer.execute(4);

    // Correct result is now {2, 3}
    CHECK(results.cols() == 2);
    CHECK(results(0, 0) == 2);
    CHECK(results(0, 1) == 3);
}

TEST_CASE("Min - int32, window size 2, horizon 2") {
    NS::Featurizers::SimpleRollingWindowTransformer<InputType>                transformer(NS::Featurizers::SimpleRollingWindowCalculation::Min, 2, 2);

    OutputType results = transformer.execute(1);

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN, NaN}
    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 1)));

    results = transformer.execute(2);

    // Correct result is now {NaN, 1}
    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(results(0, 1) == 1);

    results = transformer.execute(3);

    // Correct result is now {1, 1}
    CHECK(results.cols() == 2);
    CHECK(results(0, 0) == 1);
    CHECK(results(0, 1) == 1);

    results = transformer.execute(4);

    // Correct result is now {1, 2}
    CHECK(results.cols() == 2);
    CHECK(results(0, 0) == 1);
    CHECK(results(0, 1) == 2);
}

TEST_CASE("Min - int32, window size 2, horizon 2, min window size 2") {
    NS::Featurizers::SimpleRollingWindowTransformer<InputType>                transformer(NS::Featurizers::SimpleRollingWindowCalculation::Min, 2, 2, 2);

    OutputType results = transformer.execute(1);

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN, NaN}
    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 1)));

    results = transformer.execute(2);

    // Correct result is now {NaN, NaN}
    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 1)));

    results = transformer.execute(3);

    // Correct result is now {NaN, 1}
    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(results(0, 1) == 1);

    results = transformer.execute(4);

    // Correct result is now {1, 2}
    CHECK(results.cols() == 2);
    CHECK(results(0, 0) == 1);
    CHECK(results(0, 1) == 2);
}

TEST_CASE("Estimator Min - int32, window size 2, horizon 2, min window size 2") {
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::SimpleRollingWindowEstimator<InputType>                 estimator(pAllColumnAnnotations, NS::Featurizers::SimpleRollingWindowCalculation::Min, 2, 2, 2);
    estimator.begin_training();
    estimator.complete_training();
    auto transformer = estimator.create_transformer();

    std::vector<OutputType>   output;
    auto const                              callback(
        [&output](OutputType value) {
            output.emplace_back(value);
        }
    );

    transformer->execute(1, callback);
    OutputType results = output[0];

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN, NaN}
    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 1)));

    transformer->execute(2, callback);
    results = output[1];

    // Correct result is now {NaN, NaN}
    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 1)));

    transformer->execute(3, callback);
    results = output[2];

    // Correct result is now {NaN, 1}
    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(results(0, 1) == 1);

    transformer->execute(4, callback);
    results = output[3];

    // Correct result is now {1, 2}
    CHECK(results.cols() == 2);
    CHECK(results(0, 0) == 1);
    CHECK(results(0, 1) == 2);
}

using GrainType = std::vector<std::string>;

TEST_CASE("Grained Min - 1 grain, window size 1, horizon 1") {
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::GrainedSimpleRollingWindowEstimator<InputType>      estimator(pAllColumnAnnotations, NS::Featurizers::SimpleRollingWindowCalculation::Min, 1, 1);

    using GrainedInputType = typename NS::Featurizers::GrainedSimpleRollingWindowEstimator<InputType>::InputType;

    const GrainType grain({"one"});
    const InputType value1(1);
    const GrainedInputType tup1(grain, value1);
    const std::vector<std::tuple<GrainType const &, InputType const &>> vec = {tup1};

    estimator.begin_training();
    CHECK(estimator.get_state() == NS::TrainingState::Finished);

    estimator.complete_training();
    CHECK(estimator.get_state() == NS::TrainingState::Completed);

    auto transformer = estimator.create_transformer();

    std::vector<OutputType>   output;
    auto const                              callback(
        [&output](OutputType value) {
            output.emplace_back(std::move(value));
        }
    );

    transformer->execute(tup1, callback);
    OutputType results = output[0];

    // Correct result is {NaN}
    CHECK(results.cols() == 1);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));

    const InputType value2(2);
    const GrainedInputType tup2(grain, value2);

    transformer->execute(tup2, callback);
    results = output[1];

    // Correct result is now {1}
    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 1);

    const InputType value3(3);
    const GrainedInputType tup3(grain, value3);
    transformer->execute(tup3, callback);
    results = output[2];

    // Correct result is now {2}
    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 2);
}

TEST_CASE("Serialization/Deserialization") {
    NS::Featurizers::SimpleRollingWindowTransformer<std::int32_t>       transformer(NS::Featurizers::SimpleRollingWindowCalculation::Min, 2, 2, 2);
    NS::Archive                                                 out;

    transformer.save(out);

    NS::Archive                         in(out.commit());
    NS::Featurizers::SimpleRollingWindowTransformer<std::int32_t>       other(in);

    CHECK(other == transformer);
}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        NS::Featurizers::SimpleRollingWindowTransformer<std::int32_t>(in),
        Catch::Contains("Unsupported archive version")
    );
}

TEST_CASE("Invalid Constructor Args") {
    CHECK_THROWS_WITH(
        NS::Featurizers::SimpleRollingWindowTransformer<std::int32_t>(NS::Featurizers::SimpleRollingWindowCalculation::Min, 1, 0),
        Catch::Contains("maxWindowSize")
    );

    CHECK_THROWS_WITH(
        NS::Featurizers::SimpleRollingWindowTransformer<std::int32_t>(NS::Featurizers::SimpleRollingWindowCalculation::Min, 0, 1),
        Catch::Contains("horizon")
    );

    CHECK_THROWS_WITH(
        NS::Featurizers::SimpleRollingWindowTransformer<std::int32_t>(NS::Featurizers::SimpleRollingWindowCalculation::Min, 1, 1, 0),
        Catch::Contains("minWindowSize")
    );

    CHECK_THROWS_WITH(
        NS::Featurizers::SimpleRollingWindowTransformer<std::int32_t>(NS::Featurizers::SimpleRollingWindowCalculation::Min, 1, 1, 2),
        Catch::Contains("minWindowSize must be smaller than maxWindowSize")
    );
}

TEST_CASE("Flush test") {

    std::vector<OutputType>   output;
    auto const                              callback(
        [&output](OutputType value) {
            output.emplace_back(std::move(value));
        }
    );

    NS::Featurizers::SimpleRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::SimpleRollingWindowCalculation::Min, 1, 1);

    OutputType results = transformer.execute(1);

    CHECK(results.cols() == 1);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));

    results = transformer.execute(2);

    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 1);

    // Call flush. The next 2 calls with the same values from before the flush should return the same values.
    // Flush should also return no values.
    transformer.flush(callback);
    CHECK(output.size() == 0);

    results = transformer.execute(1);

    CHECK(results.cols() == 1);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));

    results = transformer.execute(2);

    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 1);
}
