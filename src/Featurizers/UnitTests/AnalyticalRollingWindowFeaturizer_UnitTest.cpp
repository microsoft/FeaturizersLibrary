// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../AnalyticalRollingWindowFeaturizer.h"
#include "../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

using OutputType = NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>::TransformedType;
using MatrixMemberType = std::double_t;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

TEST_CASE("Mean - int32, window size 1, horizon 1") {
    // Since we are doing the mean of one value and a horizon of one, the result should always be equal to the prior value passed into execute.

    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1, 1);

    OutputType results = transformer.execute(1);

    CHECK(results.cols() == 1);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));

    results = transformer.execute(2);

    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 1);

    results = transformer.execute(3);

    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 2);

    results = transformer.execute(4);

    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 3);
}

TEST_CASE("Mean - int32, window size 2, horizon 1") {
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1, 2);

    OutputType results = transformer.execute(1);

    CHECK(results.cols() == 1);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));

    results = transformer.execute(2);

    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 1);

    results = transformer.execute(3);

    // Correct result is now {1.5} because the mean of 1 + 2 is 1.5
    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 1.5);

    results = transformer.execute(4);

    // Correct result is now {2.5} because the mean of 2 + 3 is 2.5
    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 2.5);
}

TEST_CASE("Mean - int32, window size 2, horizon 1, min window size 2") {
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1, 2, 2);

    OutputType results = transformer.execute(1);

    CHECK(results.cols() == 1);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    
    results = transformer.execute(2);
    CHECK(results.cols() == 1);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));

    results = transformer.execute(3);

    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 1.5);

    results = transformer.execute(4);

    CHECK(results.cols() == 1);
    CHECK(results(0, 0) == 2.5);
}

TEST_CASE("Mean - int32, window size 1, horizon 2") {
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 1);

    OutputType results = transformer.execute(1);

    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 1)));
    
    results = transformer.execute(2);
    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(results(0, 1) == 1);

    results = transformer.execute(3);

    CHECK(results.cols() == 2);
    CHECK(results(0, 0) == 1);
    CHECK(results(0, 1) == 2);

    results = transformer.execute(4);

    CHECK(results.cols() == 2);
    CHECK(results(0, 0) == 2);
    CHECK(results(0, 1) == 3);
}

TEST_CASE("Mean - int32, window size 2, horizon 2") {
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2);

    OutputType results = transformer.execute(1);

    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 1)));
    
    results = transformer.execute(2);
    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(results(0, 1) == 1);

    results = transformer.execute(3);

    CHECK(results.cols() == 2);
    CHECK(results(0, 0) == 1);
    CHECK(results(0, 1) == 1.5);

    results = transformer.execute(4);

    CHECK(results.cols() == 2);
    CHECK(results(0, 0) == 1.5);
    CHECK(results(0, 1) == 2.5);
}

TEST_CASE("Mean - int32, window size 2, horizon 2, min window size 2") {
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2, 2);

    OutputType results = transformer.execute(1);

    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 1)));
    
    results = transformer.execute(2);
    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 1)));

    results = transformer.execute(3);

    CHECK(results.cols() == 2);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(results(0, 0)));
    CHECK(results(0, 1) == 1.5);

    results = transformer.execute(4);

    CHECK(results.cols() == 2);
    CHECK(results(0, 0) == 1.5);
    CHECK(results(0, 1) == 2.5);
}

TEST_CASE("Estimator Mean - int32, window size 2, horizon 2, min window size 2") {
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::AnalyticalRollingWindowEstimator<std::int32_t>                 estimator(pAllColumnAnnotations, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2, 2);
    estimator.begin_training();
    estimator.complete_training();
    auto transformer = estimator.create_transformer();

    std::vector<OutputType>   output;
    auto const                              callback(
        [&output](OutputType value) {
            output.emplace_back(std::move(value));
        }
    );

    transformer->execute(1, callback);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[0](0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[0](0, 1)));

    transformer->execute(2, callback);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[1](0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[1](0, 1)));

    transformer->execute(3, callback);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[2](0, 0)));
    CHECK(output[2](0, 1) == 1.5);

    transformer->execute(4, callback);
    CHECK(output[3](0, 0) == 1.5);
    CHECK(output[3](0, 1) == 2.5);
}

using GrainType = std::vector<std::string>;

TEST_CASE("Grained Mean - 1 grain, window size 1, horizon 1") {
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>      estimator(pAllColumnAnnotations, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1, 1);

    using GrainedInputType = typename NS::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::InputType;

    const GrainType grain({"one"});
    const std::int32_t value1(1);
    const GrainedInputType tup1(grain, value1);
    const std::vector<std::tuple<std::vector<std::string> const &, std::int32_t const &>> vec = {tup1};

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
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[0](0, 0)));

    const std::int32_t value2(2);
    const GrainedInputType tup2(grain, value2);

    transformer->execute(tup2, callback);
    CHECK(output[1](0, 0) == 1);

    const std::int32_t value3(3);
    const GrainedInputType tup3(grain, value3);
    transformer->execute(tup3, callback);
    CHECK(output[2](0, 0) == 2);
}

TEST_CASE("Grained Mean - 1 grain, window size 2, horizon 2, min window size 2") {
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>      estimator(pAllColumnAnnotations, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2, 2);

    using GrainedInputType = typename NS::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::InputType;

    const GrainType grain({"one"});
    const std::int32_t value1(1);
    const GrainedInputType tup1(grain, value1);
    const std::vector<std::tuple<std::vector<std::string> const &, std::int32_t const &>> vec = {tup1};

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
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[0](0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[0](0, 1)));

    const std::int32_t value2(2);
    const GrainedInputType tup2(grain, value2);
    transformer->execute(tup2, callback);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[1](0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[1](0, 1)));

    const std::int32_t value3(3);
    const GrainedInputType tup3(grain, value3);
    transformer->execute(tup3, callback);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[2](0, 0)));
    CHECK(output[2](0, 1) == 1.5);

    const std::int32_t value4(4);
    const GrainedInputType tup4(grain, value4);
    transformer->execute(tup4, callback);
    CHECK(output[3](0, 0) == 1.5);
    CHECK(output[3](0, 1) == 2.5);
}

TEST_CASE("Grained Mean - 2 grain, window size 2, horizon 2, min window size 1") {
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>      estimator(pAllColumnAnnotations, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2);

    using GrainedInputType = typename NS::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>::InputType;

    const GrainType grainOne({"one"});
    const GrainType grainTwo({"two"});
    const std::int32_t value1(1);
    const GrainedInputType tup1(grainOne, value1);
    const GrainedInputType tup2(grainTwo, value1);
    const std::vector<std::tuple<std::vector<std::string> const &, std::int32_t const &>> vec = {tup1, tup2};

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
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[0](0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[0](0, 1)));

    transformer->execute(tup2, callback);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[1](0, 0)));
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[1](0, 1)));

    const std::int32_t value2(2);
    const GrainedInputType tup3(grainOne, value2);
    transformer->execute(tup3, callback);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[2](0, 0)));
    CHECK(output[2](0, 1) == 1);

    const GrainedInputType tup4(grainTwo, value2);
    transformer->execute(tup4, callback);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[3](0, 0)));
    CHECK(output[3](0, 1) == 1);
}

TEST_CASE("Serialization/Deserialization") {
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>       transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2, 2);
    NS::Archive                                                 out;

    transformer.save(out);

    NS::Archive                         in(out.commit());
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>       other(in);

    CHECK(other == transformer);
}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>(in),
        Catch::Contains("Unsupported archive version")
    );
}

TEST_CASE("Invalid Constructor Args") {
    CHECK_THROWS_WITH(
        NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1, 0),
        Catch::Contains("maxWindowSize")
    );

    CHECK_THROWS_WITH(
        NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 0, 1),
        Catch::Contains("horizon")
    );

    CHECK_THROWS_WITH(
        NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1, 1, 0),
        Catch::Contains("minWindowSize")
    );

    CHECK_THROWS_WITH(
        NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1, 1, 2),
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

    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1, 1);

    transformer.execute(1, callback);
    transformer.execute(2, callback);
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[0](0, 0)));
    CHECK(output[1](0, 0) == 1);

    // Call flush. The next 2 calls with the same values from before the flush should return the same values.
    // Flush should also return no values.
    transformer.flush(callback);
    CHECK(output.size() == 2);

    transformer.execute(1, callback);
    transformer.execute(2, callback);
    
    CHECK(NS::Traits<MatrixMemberType>::IsNull(output[2](0, 0)));

    CHECK(output[3](0, 0) == 1);
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
