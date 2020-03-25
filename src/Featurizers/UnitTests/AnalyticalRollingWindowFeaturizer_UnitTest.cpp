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
    
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1, 1);

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(1), {std::nan("")}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(2), {1}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(3), {2}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(4), {3}));
}

TEST_CASE("Mean - int32, window size 2, horizon 1") {    
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1, 2);

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(1), {std::nan("")}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(2), {1}));

     // Correct result is now {1.5} because the mean of 1 + 2 is 1.5
    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(3), {1.5}));

    // Correct result is now {2.5} because the mean of 2 + 3 is 2.5
    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(4), {2.5}));
}

TEST_CASE("Mean - int32, window size 2, horizon 1, min window size 2") {    
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1, 2, 2);

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(1), {std::nan("")}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(2), {std::nan("")}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(3), {1.5}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(4), {2.5}));
}

TEST_CASE("Mean - int32, window size 1, horizon 2") {
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 1);

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(1), {std::nan(""), std::nan("")}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(2), {std::nan(""), 1.0}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(3), {1.0, 2.0}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(4), {2.0, 3.0}));

}

TEST_CASE("Mean - int32, window size 2, horizon 2") {
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2);

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(1), {std::nan(""), std::nan("")}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(2), {std::nan(""), 1.0}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(3), {1.0, 1.5}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(3), {1.5, 2.5}));
}

TEST_CASE("Mean - int32, window size 2, horizon 2, min window size 2") {
    NS::Featurizers::AnalyticalRollingWindowTransformer<std::int32_t>                transformer(NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2, 2);

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(1), {std::nan(""), std::nan("")}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(2), {std::nan(""), std::nan("")}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(3), {std::nan(""), 1.5}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(4), {1.5, 2.5}));
}

TEST_CASE("Estimator Mean - int32, window size 2, horizon 2, min window size 2") {
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::AnalyticalRollingWindowEstimator<std::int32_t>                 estimator(pAllColumnAnnotations, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2, 2);
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
    CHECK(NS::TestHelpers::FuzzyCheck(output[0], {std::nan(""), std::nan("")}));

    transformer->execute(2, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[1], {std::nan(""), std::nan("")}));

    transformer->execute(3, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[2], {std::nan(""), 1.5}));

    transformer->execute(4, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[3], {1.5, 2.5}));
}

using GrainType = std::vector<std::string>;

TEST_CASE("Grained Mean - 1 grain, window size 1, horizon 1") {    
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>      estimator(pAllColumnAnnotations, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 1, 1);

    using GrainedInputType = std::tuple<GrainType, std::int32_t>;

    const GrainType grain({"one"});
    const GrainedInputType tup1 = std::make_tuple(grain, 1);
    const std::vector<std::tuple<std::vector<std::string> const &, std::int32_t const &>> vec = {tup1};


    NS::TestHelpers::Train(estimator, vec);
    auto transformer = estimator.create_transformer();

    std::vector<OutputType>   output;
    auto const                              callback(
        [&output](std::vector<double> value) {
            output.emplace_back(std::move(value));
        }
    );

    transformer->execute(tup1, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[0], {std::nan("")}));

    const GrainedInputType tup2 = std::make_tuple(grain, 2);

    transformer->execute(tup2, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[1], {1.0}));

    const GrainedInputType tup3 = std::make_tuple(grain, 3);
    transformer->execute(tup3, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[2], {2.0}));
}

TEST_CASE("Grained Mean - 1 grain, window size 2, horizon 2, min window size 2") {
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>      estimator(pAllColumnAnnotations, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2, 2);

    using GrainedInputType = std::tuple<GrainType, std::int32_t>;

    const GrainType grain({"one"});
    const GrainedInputType tup1 = std::make_tuple(grain, 1);
    const std::vector<std::tuple<std::vector<std::string> const &, std::int32_t const &>> vec = {tup1};


    NS::TestHelpers::Train(estimator, vec);
    auto transformer = estimator.create_transformer();

    std::vector<OutputType>   output;
    auto const                              callback(
        [&output](std::vector<double> value) {
            output.emplace_back(std::move(value));
        }
    );

    transformer->execute(tup1, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[0], {std::nan(""), std::nan("")}));

    const GrainedInputType tup2 = std::make_tuple(grain, 2);
    transformer->execute(tup2, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[1], {std::nan(""), std::nan("")}));

    const GrainedInputType tup3 = std::make_tuple(grain, 3);
    transformer->execute(tup3, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[2], {std::nan(""), 1.5}));

    const GrainedInputType tup4 = std::make_tuple(grain, 4);
    transformer->execute(tup4, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[3], {1.5, 2.5}));
}

TEST_CASE("Grained Mean - 2 grain, window size 2, horizon 2, min window size 1") {
    NS::AnnotationMapsPtr                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::GrainedAnalyticalRollingWindowEstimator<std::int32_t>      estimator(pAllColumnAnnotations, NS::Featurizers::AnalyticalRollingWindowCalculation::Mean, 2, 2);

    using GrainedInputType = std::tuple<GrainType, std::int32_t>;

    const GrainType grainOne({"one"});
    const GrainType grainTwo({"two"});
    const GrainedInputType tup1 = std::make_tuple(grainOne, 1);
    const GrainedInputType tup2 = std::make_tuple(grainTwo, 1);
    const std::vector<std::tuple<std::vector<std::string> const &, std::int32_t const &>> vec = {tup1, tup2};


    NS::TestHelpers::Train(estimator, vec);
    auto transformer = estimator.create_transformer();

    std::vector<OutputType>   output;
    auto const                              callback(
        [&output](OutputType value) {
            output.emplace_back(std::move(value));
        }
    );

    transformer->execute(tup1, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[0], {std::nan(""), std::nan("")}));


    transformer->execute(tup2, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[1], {std::nan(""), std::nan("")}));


    const GrainedInputType tup3 = std::make_tuple(grainOne, 2);
    transformer->execute(tup3, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[2], {std::nan(""), 1}));


    const GrainedInputType tup4 = std::make_tuple(grainTwo, 2);
    transformer->execute(tup4, callback);
    CHECK(NS::TestHelpers::FuzzyCheck(output[3], {std::nan(""), 1}));
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

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(1), {std::nan("")}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(2), {1}));

    // Call flush. The next 2 calls with the same values from before the flush should return the same values.
    // Flush should also return no values.
    transformer.flush(callback);
    CHECK(output.size() == 0);
    
    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(1), {std::nan("")}));

    CHECK(NS::TestHelpers::FuzzyCheck(transformer.execute(2), {1}));
}
