// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"

#include "../ForwardFillImputerFeaturizer.h"
#include "../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

TEST_CASE("Standard - string") {
    NS::Featurizers::ForwardFillImputerTransformer<std::string>             transformer;

    CHECK(transformer.execute(nonstd::optional<std::string>("1")) == "1");
    CHECK(transformer.execute(nonstd::optional<std::string>()) == "1");
    CHECK(transformer.execute(nonstd::optional<std::string>("2")) == "2");
    CHECK(transformer.execute(nonstd::optional<std::string>("3")) == "3");
    CHECK(transformer.execute(nonstd::optional<std::string>()) == "3");
    CHECK(transformer.execute(nonstd::optional<std::string>()) == "3");
    CHECK(transformer.execute(nonstd::optional<std::string>("4")) == "4");
}

TEST_CASE("Standard - int") {
    NS::Featurizers::ForwardFillImputerTransformer<int>                     transformer;

    CHECK(transformer.execute(nonstd::optional<int>(1)) == 1);
    CHECK(transformer.execute(nonstd::optional<int>()) == 1);
    CHECK(transformer.execute(nonstd::optional<int>(2)) == 2);
    CHECK(transformer.execute(nonstd::optional<int>(3)) == 3);
    CHECK(transformer.execute(nonstd::optional<int>()) == 3);
    CHECK(transformer.execute(nonstd::optional<int>()) == 3);
    CHECK(transformer.execute(nonstd::optional<int>(4)) == 4);
}

TEST_CASE("Standard - double") {
    NS::Featurizers::ForwardFillImputerTransformer<double>                  transformer;

    CHECK(transformer.execute(1.0) == 1.0);
    CHECK(transformer.execute(NS::Traits<double>::CreateNullValue()) == 1.0);
    CHECK(transformer.execute(2.0) == 2.0);
    CHECK(transformer.execute(3.0) == 3.0);
    CHECK(transformer.execute(NS::Traits<double>::CreateNullValue()) == 3.0);
    CHECK(transformer.execute(NS::Traits<double>::CreateNullValue()) == 3.0);
    CHECK(transformer.execute(4) == 4.0);
}

TEST_CASE("ForwardFill on first value") {
    NS::Featurizers::ForwardFillImputerTransformer<double>                  transformer;

    CHECK_THROWS_WITH(transformer.execute(NS::Traits<double>::CreateNullValue()), "No source value for forward fill");
}
