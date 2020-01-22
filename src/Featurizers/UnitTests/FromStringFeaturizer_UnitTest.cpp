// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../FromStringFeaturizer.h"

namespace NS = Microsoft::Featurizer;

TEST_CASE("bool") {
    CHECK(NS::Featurizers::FromStringTransformer<bool>().execute("True") == true);
    CHECK(NS::Featurizers::FromStringTransformer<bool>().execute("False") == false);
    CHECK(NS::Featurizers::FromStringTransformer<bool>().execute("invalid") == false);
}

TEST_CASE("int") {
    CHECK(NS::Featurizers::FromStringTransformer<int>().execute("10") == 10);
    CHECK(NS::Featurizers::FromStringTransformer<int>().execute("-20") == -20);
    CHECK_THROWS_WITH(NS::Featurizers::FromStringTransformer<int>().execute("invalid"), Catch::Contains("invalid"));
}

TEST_CASE("Transformer serialization") {
    NS::Featurizers::FromStringTransformer<int>         original;
    NS::Archive                                         out;

    original.save(out);

    NS::Archive                                         in(out.commit());

    NS::Featurizers::FromStringTransformer<int>         other(in);

    CHECK(other == original);
}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        NS::Featurizers::FromStringTransformer<int>(in),
        Catch::Contains("Unsupported archive version")
    );
}
