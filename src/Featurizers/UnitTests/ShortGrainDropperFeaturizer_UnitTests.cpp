// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../Featurizers/ShortGrainDropperFeaturizer.h"
#include "../TestHelpers.h"
#include "../../Archive.h"

namespace NS = Microsoft::Featurizer;

void TestImpl(std::vector<std::vector<std::vector<std::string>>> trainingBatches,
              std::vector<std::vector<std::string>> inferencingInput,
              std::vector<bool> inferencingOutput,
              std::uint8_t windowSize,
              std::vector<std::uint8_t> lags,
              std::uint8_t maxHorizon,
              nonstd::optional<std::uint8_t> cv){

    using SGDEstimator = NS::Featurizers::ShortGrainDropperEstimator<std::numeric_limits<size_t>::max()>;
    SGDEstimator                                        estimator(NS::CreateTestAnnotationMapsPtr(1), 0, windowSize, lags, maxHorizon, cv);

    NS::TestHelpers::Train<SGDEstimator, std::vector<std::string>>(estimator, trainingBatches);
    SGDEstimator::TransformerUniquePtr                  pTransformer(estimator.create_transformer());
    std::vector<bool>   	                            output;

    auto const              callback(
        [&output](bool value) {
            //Use this workaround because C++11 on MacOS and CentOS doesn't support emplace() or emplace_back() for vector<bool>
            output.push_back(value);
        }
    );

    for(auto const &item : inferencingInput)
        pTransformer->execute(item, callback);

    pTransformer->flush(callback);

    CHECK(output == inferencingOutput);
}

TEST_CASE("Invalid Transformer/Estimator") {
    //parameter setting
    std::uint8_t windowSize = 0;
    std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>();
    std::uint8_t maxHorizon = 1;
    nonstd::optional<std::uint8_t> cv = static_cast<std::uint8_t>(1);

    CHECK_THROWS_WITH(NS::Featurizers::ShortGrainDropperEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 2, windowSize, lags, maxHorizon, cv), "colIndex");
    CHECK_THROWS_WITH(NS::Featurizers::ShortGrainDropperEstimator<std::numeric_limits<size_t>::max()>(NS::CreateTestAnnotationMapsPtr(1), 0, windowSize, lags, maxHorizon, cv), "lags");
}

TEST_CASE("Standard Test") {
    std::vector<std::vector<std::vector<std::string>>> trainingBatches = NS::TestHelpers::make_vector<std::vector<std::vector<std::string>>>(
        NS::TestHelpers::make_vector<std::vector<std::string>>(
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "c"),
            NS::TestHelpers::make_vector<std::string>("a", "c"),
            NS::TestHelpers::make_vector<std::string>("a", "c"),
            NS::TestHelpers::make_vector<std::string>("a", "c"),
            NS::TestHelpers::make_vector<std::string>("a", "d"),
            NS::TestHelpers::make_vector<std::string>("a", "d"),
            NS::TestHelpers::make_vector<std::string>("a", "d"),
            NS::TestHelpers::make_vector<std::string>("a", "e"),
            NS::TestHelpers::make_vector<std::string>("a", "e"),
            NS::TestHelpers::make_vector<std::string>("a", "f")
        )
    );

    std::vector<std::vector<std::string>> inferencingInput = NS::TestHelpers::make_vector<std::vector<std::string>>(
        NS::TestHelpers::make_vector<std::string>("a", "b"),
        NS::TestHelpers::make_vector<std::string>("a", "c"),
        NS::TestHelpers::make_vector<std::string>("a", "d"),
        NS::TestHelpers::make_vector<std::string>("a", "e"),
        NS::TestHelpers::make_vector<std::string>("a", "f"),
        NS::TestHelpers::make_vector<std::string>("a", "g")
    );

    std::vector<bool> inferencingOutput = {
        false,
        true,
        true,
        true,
        true,
        false
    };

    //parameter setting
    std::uint8_t windowSize = 0;
    std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(0));
    std::uint8_t maxHorizon = 1;
    nonstd::optional<std::uint8_t> cv = static_cast<std::uint8_t>(1);

    TestImpl(
        trainingBatches,
        inferencingInput,
        inferencingOutput,
        windowSize,
        lags,
        maxHorizon,
        cv
    );
}

TEST_CASE("Standard Test_Parameter Combination") {
    std::vector<std::vector<std::vector<std::string>>> trainingBatches = NS::TestHelpers::make_vector<std::vector<std::vector<std::string>>>(
        NS::TestHelpers::make_vector<std::vector<std::string>>(
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "b"),
            NS::TestHelpers::make_vector<std::string>("a", "c"),
            NS::TestHelpers::make_vector<std::string>("a", "c"),
            NS::TestHelpers::make_vector<std::string>("a", "c"),
            NS::TestHelpers::make_vector<std::string>("a", "c"),
            NS::TestHelpers::make_vector<std::string>("a", "d"),
            NS::TestHelpers::make_vector<std::string>("a", "d"),
            NS::TestHelpers::make_vector<std::string>("a", "d"),
            NS::TestHelpers::make_vector<std::string>("a", "e"),
            NS::TestHelpers::make_vector<std::string>("a", "e"),
            NS::TestHelpers::make_vector<std::string>("a", "f")
        )
    );

    std::vector<std::vector<std::string>> inferencingInput = NS::TestHelpers::make_vector<std::vector<std::string>>(
        NS::TestHelpers::make_vector<std::string>("a", "b"),
        NS::TestHelpers::make_vector<std::string>("a", "c"),
        NS::TestHelpers::make_vector<std::string>("a", "d"),
        NS::TestHelpers::make_vector<std::string>("a", "e"),
        NS::TestHelpers::make_vector<std::string>("a", "f"),
        NS::TestHelpers::make_vector<std::string>("a", "g")
    );

    SECTION("windowSize=1/lags=[0,1]/maxHorizon=1/no cv") {
        //parameter setting
        std::uint8_t windowSize = 1;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(1));
        std::uint8_t maxHorizon = 1;
        nonstd::optional<std::uint8_t> cv = nonstd::optional<std::uint8_t>();

        std::vector<bool> inferencingOutput = {
            false,
            false,
            true,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=0/lags=[0,1]/maxHorizon=1/no cv") {
        //parameter setting
        std::uint8_t windowSize = 0;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(1));
        std::uint8_t maxHorizon = 1;
        nonstd::optional<std::uint8_t> cv = nonstd::optional<std::uint8_t>();

        std::vector<bool> inferencingOutput = {
            false,
            false,
            true,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=1/lags=[0,0]/maxHorizon=1/no cv") {
        //parameter setting
        std::uint8_t windowSize = 0;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(0));
        std::uint8_t maxHorizon = 1;
        nonstd::optional<std::uint8_t> cv = nonstd::optional<std::uint8_t>();

        std::vector<bool> inferencingOutput = {
            false,
            false,
            false,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=0/lags=[0,0]/maxHorizon=1/no cv") {
        //parameter setting
        std::uint8_t windowSize = 0;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(0));
        std::uint8_t maxHorizon = 1;
        nonstd::optional<std::uint8_t> cv = nonstd::optional<std::uint8_t>();

        std::vector<bool> inferencingOutput = {
            false,
            false,
            false,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=1/lags=[0,1]/maxHorizon=0/no cv") {
        //parameter setting
        std::uint8_t windowSize = 1;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(1));
        std::uint8_t maxHorizon = 0;
        nonstd::optional<std::uint8_t> cv = nonstd::optional<std::uint8_t>();

        std::vector<bool> inferencingOutput = {
            false,
            false,
            false,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=0/lags=[0,1]/maxHorizon=0/no cv") {
        //parameter setting
        std::uint8_t windowSize = 0;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(1));
        std::uint8_t maxHorizon = 0;
        nonstd::optional<std::uint8_t> cv = nonstd::optional<std::uint8_t>();

        std::vector<bool> inferencingOutput = {
            false,
            false,
            false,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=1/lags=[0,0]/maxHorizon=0/no cv") {
        //parameter setting
        std::uint8_t windowSize = 0;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(0));
        std::uint8_t maxHorizon = 0;
        nonstd::optional<std::uint8_t> cv = nonstd::optional<std::uint8_t>();

        std::vector<bool> inferencingOutput = {
            false,
            false,
            false,
            false,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=0/lags=[0,0]/maxHorizon=0/no cv") {
        //parameter setting
        std::uint8_t windowSize = 0;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(0));
        std::uint8_t maxHorizon = 0;
        nonstd::optional<std::uint8_t> cv = nonstd::optional<std::uint8_t>();

        std::vector<bool> inferencingOutput = {
            false,
            false,
            false,
            false,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=1/lags=[0,1]/maxHorizon=1/cv=1") {
        //parameter setting
        std::uint8_t windowSize = 1;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(1));
        std::uint8_t maxHorizon = 1;
        nonstd::optional<std::uint8_t> cv = static_cast<std::uint8_t>(1);

        std::vector<bool> inferencingOutput = {
            true,
            true,
            true,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=0/lags=[0,1]/maxHorizon=1/cv=1") {
        //parameter setting
        std::uint8_t windowSize = 0;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(1));
        std::uint8_t maxHorizon = 1;
        nonstd::optional<std::uint8_t> cv = static_cast<std::uint8_t>(1);

        std::vector<bool> inferencingOutput = {
            true,
            true,
            true,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=1/lags=[0,0]/maxHorizon=1/cv=1") {
        //parameter setting
        std::uint8_t windowSize = 0;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(0));
        std::uint8_t maxHorizon = 1;
        nonstd::optional<std::uint8_t> cv = static_cast<std::uint8_t>(1);

        std::vector<bool> inferencingOutput = {
            false,
            true,
            true,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=0/lags=[0,0]/maxHorizon=1/cv=1") {
        //parameter setting
        std::uint8_t windowSize = 0;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(0));
        std::uint8_t maxHorizon = 1;
        nonstd::optional<std::uint8_t> cv = static_cast<std::uint8_t>(1);

        std::vector<bool> inferencingOutput = {
            false,
            true,
            true,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=1/lags=[0,1]/maxHorizon=0/cv=1") {
        //parameter setting
        std::uint8_t windowSize = 1;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(1));
        std::uint8_t maxHorizon = 0;
        nonstd::optional<std::uint8_t> cv = static_cast<std::uint8_t>(1);

        std::vector<bool> inferencingOutput = {
            false,
            false,
            true,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=0/lags=[0,1]/maxHorizon=0/cv=1") {
        //parameter setting
        std::uint8_t windowSize = 0;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(1));
        std::uint8_t maxHorizon = 0;
        nonstd::optional<std::uint8_t> cv = static_cast<std::uint8_t>(1);

        std::vector<bool> inferencingOutput = {
            false,
            false,
            true,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=1/lags=[0,0]/maxHorizon=0/cv=1") {
        //parameter setting
        std::uint8_t windowSize = 0;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(0));
        std::uint8_t maxHorizon = 0;
        nonstd::optional<std::uint8_t> cv = static_cast<std::uint8_t>(1);

        std::vector<bool> inferencingOutput = {
            false,
            false,
            false,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }

    SECTION("windowSize=0/lags=[0,0]/maxHorizon=0/cv=1") {
        //parameter setting
        std::uint8_t windowSize = 0;
        std::vector<std::uint8_t> lags = NS::TestHelpers::make_vector<std::uint8_t>(static_cast<std::uint8_t>(0), static_cast<std::uint8_t>(0));
        std::uint8_t maxHorizon = 0;
        nonstd::optional<std::uint8_t> cv = static_cast<std::uint8_t>(1);

        std::vector<bool> inferencingOutput = {
            false,
            false,
            false,
            true,
            true,
            false
        };

        TestImpl(
            trainingBatches,
            inferencingInput,
            inferencingOutput,
            windowSize,
            lags,
            maxHorizon,
            cv
        );
    }
}

TEST_CASE("Serialization/Deserialization") {
    using TransformerType = NS::Featurizers::ShortGrainDropperTransformer;

    std::unordered_set<
        std::vector<std::string>,
        Microsoft::Featurizer::ContainerHash<std::vector<std::string>>
    >                                       grainsToDrop({{"aa"}, {"ab"}});

    TransformerType                         original(std::move(grainsToDrop));
    NS::Archive                             out;

    original.save(out);

    NS::Archive                             in(out.commit());
    TransformerType                         other(in);

    CHECK(other == original);
}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        NS::Featurizers::ShortGrainDropperTransformer(in),
        Catch::Contains("Unsupported archive version")
    );
}
