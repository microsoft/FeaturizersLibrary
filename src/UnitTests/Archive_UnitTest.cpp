// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Archive.h"

namespace NS                                = Microsoft::Featurizer;

TEST_CASE("Construct - Serialization") {
    CHECK(NS::Archive().Mode == NS::Archive::ModeValue::Serializing);
    CHECK(NS::Archive().commit().capacity() == 0);
    CHECK(NS::Archive(10).commit().capacity() == 10);
}

TEST_CASE("Construct - Deserialization") {
    CHECK(NS::Archive(NS::Archive::ByteArray()).Mode == NS::Archive::ModeValue::Deserializing);
    int const                               value(10);
    CHECK(NS::Archive(reinterpret_cast<unsigned char const *>(&value), sizeof(value)).Mode == NS::Archive::ModeValue::Deserializing);
    CHECK_THROWS_WITH(NS::Archive(nullptr, 1), "Invalid input buffer");
    CHECK_THROWS_WITH(NS::Archive(reinterpret_cast<unsigned char const *>(&value), 0), "Invalid input buffer");
}

TEST_CASE("Invalid Mode - Serialization") {
    NS::Archive                             archive;

    CHECK_THROWS_WITH(archive.deserialize<int>(), "Invalid mode");
    CHECK_THROWS_WITH(archive.get_buffer_ptr(), "Invalid mode");
    CHECK_THROWS_WITH(archive.update_buffer_ptr(10), "Invalid mode");
    CHECK_THROWS_WITH(archive.AtEnd(), "Invalid mode");
}

TEST_CASE("Invalid mode - Deserialization") {
    int const                               value(10);
    NS::Archive                             archive(reinterpret_cast<unsigned char const *>(&value), sizeof(value));

    CHECK_THROWS_WITH(archive.serialize(reinterpret_cast<unsigned char const *>(&value), sizeof(value)), "Invalid mode");
    CHECK_THROWS_WITH(archive.serialize(value), "Invalid mode");
    CHECK_THROWS_WITH(archive.commit(), "Invalid mode");
}

TEST_CASE("Serialize errors") {
    NS::Archive                             out;

    CHECK_THROWS_WITH(out.serialize(nullptr, 1), "Invalid buffer");
    CHECK_THROWS_WITH(out.serialize(reinterpret_cast<unsigned char const *>(&out), 0), "Invalid buffer");
}

TEST_CASE("Roundtrip") {
    NS::Archive                             out;

    // Serializing nothing should not be an error
    out.serialize(nullptr, 0);

    out.serialize(true);
    out.serialize(static_cast<int>(10));
    out.serialize(static_cast<double>(2.0));

    NS::Archive                             in(out.commit());
    bool const                              one(in.deserialize<bool>());
    int const                               two(in.deserialize<int>());
    double const                            three(in.deserialize<double>());

    CHECK(in.AtEnd());
    CHECK(one == true);
    CHECK(two == 10);
    CHECK(three == 2.0);
}

TEST_CASE("Deserialize errors") {
    NS::Archive                             out;

    out.serialize(true);

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(in.deserialize<int>(), "Invalid buffer");
    CHECK_THROWS_WITH(in.update_buffer_ptr(2), "Invalid delta");

    // The errors above shouldn't have moved the buffer ptr
    CHECK(in.deserialize<bool>() == true);
    CHECK(in.AtEnd());

    CHECK_THROWS_WITH(in.get_buffer_ptr(), "Invalid buffer");
}
