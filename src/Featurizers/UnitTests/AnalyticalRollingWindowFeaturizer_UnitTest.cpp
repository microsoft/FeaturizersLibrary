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

TEST_CASE("Mean - int32, window size 1, horizon 1") {
    // Since we are doing the mean of one value and a horizon of one, the result should always be equal to the prior value passed into execute.
    
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(1, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1);

    OutputType results = transformer.execute(1);

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN}
    CHECK(results.size() == 1);
    CHECK(std::isnan(results[0]));

    results = transformer.execute(2);

    // Correct result is now {1}
    CHECK(results.size() == 1);
    CHECK(results[0] == 1.0);

    results = transformer.execute(3);

    // Correct result is now {2}
    CHECK(results.size() == 1);
    CHECK(results[0] == 2.0);

    results = transformer.execute(4);

    // Correct result is now {3}
    CHECK(results.size() == 1);
    CHECK(results[0] == 3.0);
}

TEST_CASE("Mean - int32, window size 2, horizon 1") {    
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(2, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1);

    OutputType results = transformer.execute(1);

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN}
    CHECK(results.size() == 1);
    CHECK(std::isnan(results[0]));

    results = transformer.execute(2);

    // Correct result is now {1}
    CHECK(results.size() == 1);
    CHECK(results[0] == 1.0);

    results = transformer.execute(3);

    // Correct result is now {1.5} because the mean of 1 + 2 is 1.5
    CHECK(results.size() == 1);
    CHECK(results[0] == 1.5);

    results = transformer.execute(4);

    // Correct result is now {2.5} because the mean of 2 + 3 is 2.5
    CHECK(results.size() == 1);
    CHECK(results[0] == 2.5);
}

TEST_CASE("Mean - int32, window size 2, horizon 1, min window size 2") {    
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(2, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1, 2);

    OutputType results = transformer.execute(1);

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN}
    CHECK(results.size() == 1);
    CHECK(std::isnan(results[0]));

    results = transformer.execute(2);

    // Correct result is still {NaN} due to min window size of 2
    CHECK(results.size() == 1);
    CHECK(std::isnan(results[0]));

    results = transformer.execute(3);

    // Correct result is now {1.5} because the mean of 1 + 2 is 1.5
    CHECK(results.size() == 1);
    CHECK(results[0] == 1.5);

    results = transformer.execute(4);

    // Correct result is now {2.5} because the mean of 2 + 3 is 2.5
    CHECK(results.size() == 1);
    CHECK(results[0] == 2.5);
}

TEST_CASE("Mean - int32, window size 1, horizon 2") {
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(1, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2);

    OutputType results = transformer.execute(1);

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN, NaN}
    CHECK(results.size() == 2);
    CHECK(std::isnan(results[0]));
    CHECK(std::isnan(results[1]));

    results = transformer.execute(2);

    // Correct result is now {NaN, 1}
    CHECK(results.size() == 2);
    CHECK(std::isnan(results[0]));
    CHECK(results[1] == 1.0);

    results = transformer.execute(3);

    // Correct result is now {1, 2}
    CHECK(results.size() == 2);
    CHECK(results[0] == 1.0);
    CHECK(results[1] == 2.0);

    results = transformer.execute(4);

    // Correct result is now {2, 3}
    CHECK(results.size() == 2);
    CHECK(results[0] == 2.0);
    CHECK(results[1] == 3.0);
}

TEST_CASE("Mean - int32, window size 2, horizon 2") {
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(2, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2);

    OutputType results = transformer.execute(1);

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN, NaN}
    CHECK(results.size() == 2);
    CHECK(std::isnan(results[0]));
    CHECK(std::isnan(results[1]));

    results = transformer.execute(2);

    // Correct result is now {NaN, 1}
    CHECK(results.size() == 2);
    CHECK(std::isnan(results[0]));
    CHECK(results[1] == 1.0);

    results = transformer.execute(3);

    // Correct result is now {1, 1.5}
    CHECK(results.size() == 2);
    CHECK(results[0] == 1.0);
    CHECK(results[1] == 1.5);

    results = transformer.execute(4);

    // Correct result is now {1.5, 2.5}
    CHECK(results.size() == 2);
    CHECK(results[0] == 1.5);
    CHECK(results[1] == 2.5);
}

TEST_CASE("Mean - int32, window size 2, horizon 2, min window size 2") {
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(2, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2);

    OutputType results = transformer.execute(1);

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN, NaN}
    CHECK(results.size() == 2);
    CHECK(std::isnan(results[0]));
    CHECK(std::isnan(results[1]));

    results = transformer.execute(2);

    // Correct result is now {NaN, NaN}
    CHECK(results.size() == 2);
    CHECK(std::isnan(results[0]));
    CHECK(std::isnan(results[1]));

    results = transformer.execute(3);

    // Correct result is now {NaN, 1.5}
    CHECK(results.size() == 2);
    CHECK(std::isnan(results[0]));
    CHECK(results[1] == 1.5);

    results = transformer.execute(4);

    // Correct result is now {1.5, 2.5}
    CHECK(results.size() == 2);
    CHECK(results[0] == 1.5);
    CHECK(results[1] == 2.5);
}

TEST_CASE("Estimator Mean - int32, window size 2, horizon 2, min window size 2") {
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::AnalyticalRollingWindowEstimator<std::int32_t>                 estimator(pAllColumnAnnotations, 2, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2);
    estimator.begin_training();
    estimator.complete_training();
    auto transformer = estimator.create_transformer();
    
    std::vector<OutputType>   output;
    auto const                              callback(
        [&output](std::vector<double> value) {
            output.emplace_back(std::move(value));
        }
    );

    transformer->execute(1, callback);
    OutputType results = output[0];

    // Since there are NaN values, cannot directly compare the vectors.
    // Correct result is {NaN, NaN}
    CHECK(results.size() == 2);
    CHECK(std::isnan(results[0]));
    CHECK(std::isnan(results[1]));

    transformer->execute(2, callback);
    results = output[1];

    // Correct result is now {NaN, NaN}
    CHECK(results.size() == 2);
    CHECK(std::isnan(results[0]));
    CHECK(std::isnan(results[1]));

    transformer->execute(3, callback);
    results = output[2];

    // Correct result is now {NaN, 1.5}
    CHECK(results.size() == 2);
    CHECK(std::isnan(results[0]));
    CHECK(results[1] == 1.5);

    transformer->execute(4, callback);
    results = output[3]; 

    // Correct result is now {1.5, 2.5}
    CHECK(results.size() == 2);
    CHECK(results[0] == 1.5);
    CHECK(results[1] == 2.5);
}

using GrainType = std::vector<std::string>;

TEST_CASE("Grained Mean - 1 grain, window size 1, horizon 1") {    
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>      estimator(pAllColumnAnnotations, 1, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1);

    using GrainedInputType = std::tuple<GrainType const &, std::int32_t const &>;
    //using TupleType = std::tuple<GrainType, std::int32_t>;


    const GrainType grain({"one"});
    const GrainedInputType tup1 = std::make_tuple(grain, 1);
    const std::vector<GrainedInputType> vec = {tup1};


    NS::TestHelpers::Train(estimator, vec);
    auto transformer = estimator.create_transformer();

    std::vector<std::tuple<std::vector<std::string>,std::vector<double>>>   output;
    auto const                              callback(
        [&output](std::tuple<std::vector<std::string>,std::vector<double>> value) {
            output.emplace_back(std::move(value));
        }
    );

    transformer->execute(tup1, callback);
    OutputType results = std::get<1>(output[0]);
    
    // Correct result is {NaN}
    CHECK(results.size() == 1);
    CHECK(std::isnan(results[0]));

    const GrainedInputType tup2 = std::make_tuple(grain, 2);

    transformer->execute(tup2, callback);
    results = std::get<1>(output[1]);

    // Correct result is now {1}
    CHECK(results.size() == 1);
    CHECK(results[0] == 1.0);

    const GrainedInputType tup3 = std::make_tuple(grain, 3);
    transformer->execute(tup3, callback);
    results = std::get<1>(output[2]);

    // Correct result is now {2}
    CHECK(results.size() == 1);
    CHECK(results[0] == 2.0);
}

TEST_CASE("Serialization/Deserialization") {
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>       transformer(2, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2);
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
