// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../ImputerTransformer.h"
#include "../../TestHelpers.h"
#include "../../../3rdParty/optional.h"

namespace NS = Microsoft::Featurizer;
namespace Components = NS::Featurizers::Components;

TEST_CASE("Imputation") {
    Components::ImputerTransformer<nonstd::optional<int>, int>              transformer(10);

    CHECK(transformer.execute(1) == 1);
    CHECK(transformer.execute(nonstd::optional<int>()) == 10);
}

TEST_CASE("Comparison") {
    CHECK(Components::ImputerTransformer<nonstd::optional<int>, int>(10) == Components::ImputerTransformer<nonstd::optional<int>, int>(10));
    CHECK(Components::ImputerTransformer<nonstd::optional<int>, int>(10) != Components::ImputerTransformer<nonstd::optional<int>, int>(20));
}

TEST_CASE("Serialization/Deserialization- Numeric") {
    Components::ImputerTransformer<nonstd::optional<std::int64_t>, std::int64_t>    transformer(10);
    NS::Archive                                                                     out;

    transformer.save(out);

    NS::Archive                                                                     in(out.commit());
    Components::ImputerTransformer<nonstd::optional<std::int64_t>, std::int64_t>    other(in);

    CHECK(other == transformer);
}

TEST_CASE("Serialization/Deserialization- string") {
    Components::ImputerTransformer<nonstd::optional<std::string>, std::string>  transformer("one");
    NS::Archive                                                                 out;

    transformer.save(out);

    NS::Archive                                                                 in(out.commit());
    Components::ImputerTransformer<nonstd::optional<std::string>, std::string>  other(in);

    CHECK(other == transformer);
}

TEST_CASE("Serialization/Deserialization- float") {
    Components::ImputerTransformer<float, float>        transformer(1.0f);
    NS::Archive                                         out;

    transformer.save(out);

    NS::Archive                                         in(out.commit());
    Components::ImputerTransformer<float, float>        other(in);

    CHECK(other == transformer);
}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        (Components::ImputerTransformer<nonstd::optional<std::string>, std::string>(in)),
        Catch::Contains("Unsupported archive version")
    );
}
