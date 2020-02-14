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

TEST_CASE("ForwardFill on first value with default") {
    NS::Featurizers::ForwardFillImputerTransformer<double>                  transformer(0.0);

    CHECK(transformer.execute(NS::Traits<double>::CreateNullValue()) == 0.0); // Use the default value
    CHECK(transformer.execute(1.0) == 1.0);
    CHECK(transformer.execute(NS::Traits<double>::CreateNullValue()) == 1.0);
    CHECK(transformer.execute(2.0) == 2.0);
    CHECK(transformer.execute(3.0) == 3.0);
    CHECK(transformer.execute(NS::Traits<double>::CreateNullValue()) == 3.0);
    CHECK(transformer.execute(NS::Traits<double>::CreateNullValue()) == 3.0);
    CHECK(transformer.execute(4) == 4.0);
}

TEST_CASE("Comparison") {
    // ----------------------------------------------------------------------
    using Transformer                       = NS::Featurizers::ForwardFillImputerTransformer<double>;
    // ----------------------------------------------------------------------

    CHECK(Transformer() == Transformer());
    CHECK(Transformer(1.0) == Transformer(1.0));
    CHECK(Transformer() != Transformer(1.0));
    CHECK(Transformer(1.0) != Transformer(2.0));

    Transformer                             transformer;

    CHECK(transformer == Transformer());
    CHECK(transformer != Transformer(1.0));

    transformer.execute(1.0);

    CHECK(transformer != Transformer());
    CHECK(transformer == Transformer(1.0));
}

TEST_CASE("Serialization") {
    size_t                                  defaultArchiveSize(0);
    size_t                                  valueArchiveSize(0);

    {
        NS::Featurizers::ForwardFillImputerTransformer<double>              transformer;
        NS::Archive                                                         out;

        transformer.save(out);

        NS::Archive::ByteArray              bytes(out.commit());

        defaultArchiveSize = bytes.size();
        CHECK(defaultArchiveSize != 0);

        NS::Archive                                                         in(std::move(bytes));
        NS::Featurizers::ForwardFillImputerTransformer<double>              other(in);

        CHECK(other == transformer);
    }

    {
        NS::Featurizers::ForwardFillImputerTransformer<double>              transformer(1.0);
        NS::Archive                                                         out;

        transformer.save(out);

        NS::Archive::ByteArray              bytes(out.commit());

        valueArchiveSize = bytes.size();
        CHECK(valueArchiveSize != 0);

        NS::Archive                                                         in(std::move(bytes));
        NS::Featurizers::ForwardFillImputerTransformer<double>              other(in);

        CHECK(other == transformer);
    }

    CHECK(defaultArchiveSize < valueArchiveSize);
}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        (NS::Featurizers::ForwardFillImputerTransformer<double>(in)),
        Catch::Contains("Unsupported archive version")
    );
}
