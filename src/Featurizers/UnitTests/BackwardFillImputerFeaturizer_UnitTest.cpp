// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"

#include "../BackwardFillImputerFeaturizer.h"
#include "../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

TEST_CASE("Standard - string") {
    NS::Featurizers::BackwardFillImputerTransformer<std::string>            transformer;
    std::vector<std::string>                                                output;

    auto const callback =
        [&output](std::string value) {
            output.emplace_back(std::move(value));
        };

    SECTION("Single value") {
        transformer.execute("1", callback);
        CHECK(output == std::vector<std::string>{"1"});
        CHECK(transformer.has_pending() == false);
    }

    SECTION("Multiple values") {
        CHECK(transformer.has_pending() == false);

        transformer.execute(nonstd::optional<std::string>(), callback);
        CHECK(output.empty());
        CHECK(transformer.has_pending());

        transformer.execute(nonstd::optional<std::string>(), callback);
        CHECK(output.empty());
        CHECK(transformer.has_pending());

        transformer.execute("2", callback);
        CHECK(output == std::vector<std::string>{"2", "2", "2"});
        CHECK(transformer.has_pending() == false);

        output.clear();
        transformer.flush(callback);
        CHECK(output.empty());
    }
}

TEST_CASE("Standard - int") {
    NS::Featurizers::BackwardFillImputerTransformer<int>                    transformer;
    std::vector<int>                                                        output;

    auto const callback =
        [&output](int value) {
            output.emplace_back(std::move(value));
        };

    SECTION("Single value") {
        transformer.execute(1, callback);
        CHECK(output == std::vector<int>{1});
        CHECK(transformer.has_pending() == false);
    }

    SECTION("Multiple values") {
        CHECK(transformer.has_pending() == false);

        transformer.execute(nonstd::optional<int>(), callback);
        CHECK(output.empty());
        CHECK(transformer.has_pending());

        transformer.execute(nonstd::optional<int>(), callback);
        CHECK(output.empty());
        CHECK(transformer.has_pending());

        transformer.execute(2, callback);
        CHECK(output == std::vector<int>{2, 2, 2});
        CHECK(transformer.has_pending() == false);

        output.clear();
        transformer.flush(callback);
        CHECK(output.empty());
    }
}

TEST_CASE("Standard - double") {
    NS::Featurizers::BackwardFillImputerTransformer<double>                 transformer;
    std::vector<double>                                                     output;

    auto const callback =
        [&output](double value) {
            output.emplace_back(std::move(value));
        };

    SECTION("Single value") {
        transformer.execute(1.0, callback);
        CHECK(output == std::vector<double>{1.0});
        CHECK(transformer.has_pending() == false);
    }

    SECTION("Multiple values") {
        CHECK(transformer.has_pending() == false);

        transformer.execute(NS::Traits<double>::CreateNullValue(), callback);
        CHECK(output.empty());
        CHECK(transformer.has_pending());

        transformer.execute(NS::Traits<double>::CreateNullValue(), callback);
        CHECK(output.empty());
        CHECK(transformer.has_pending());

        transformer.execute(2.0, callback);
        CHECK(output == std::vector<double>{2.0, 2.0, 2.0});
        CHECK(transformer.has_pending() == false);

        output.clear();
        transformer.flush(callback);
        CHECK(output.empty());
    }
}

TEST_CASE("Pending and reset") {
    NS::Featurizers::BackwardFillImputerTransformer<double>                 transformer;
    std::vector<double>                                                     output;

    auto const callback =
        [&output](double value) {
            output.emplace_back(std::move(value));
        };

    CHECK(transformer.has_pending() == false);
    transformer.execute(NS::Traits<double>::CreateNullValue(), callback);

    CHECK(transformer.has_pending());
    CHECK_THROWS_WITH(transformer.flush(callback), "Pending backward fill items remain");
    CHECK(transformer.has_pending());

    transformer.reset();
    CHECK(transformer.has_pending() == false);

    transformer.flush(callback);
    CHECK(output.empty());
}

TEST_CASE("Serialization") {
    NS::Featurizers::BackwardFillImputerTransformer<double>                 transformer;
    NS::Archive                                                             out;

    transformer.save(out);

    NS::Archive                                                             in(out.commit());
    NS::Featurizers::BackwardFillImputerTransformer<double>                 other(in);

    CHECK(other == transformer);
}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        NS::Featurizers::BackwardFillImputerTransformer<std::string>(in),
        Catch::Contains("Unsupported archive version")
    );
}
