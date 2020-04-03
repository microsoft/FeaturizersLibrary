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

bool TestLittleEndianess() {
    uint32_t u = 0x01020304;
    return (*(reinterpret_cast<uint8_t*>(&u))) == 4;
}

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

template <typename T>
bool SerializeOnly(T const &value) {
    NS::Archive                             out;

    out.serialize(value);

    NS::Archive                             in(out.commit());

    T const                                 other(in.template deserialize<T>());
    return value == other;
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

TEST_CASE("Endianess") {
    CHECK(TestLittleEndianess() == is_little_endian); // ISLITTLEENDIAN in Traits.h is set incorrectly!
}

TEST_CASE("Serialization_Based_On_Endianess") {
    // checks if serialized output == original
    // expected result would be true for little endian and false for big endian
    bool                                    expected_result(TestLittleEndianess());

    CHECK(SerializeOnly(static_cast<std::int16_t>(-23)) == expected_result);
    CHECK(SerializeOnly(static_cast<std::int32_t>(-23)) == expected_result);
    CHECK(SerializeOnly(static_cast<std::int64_t>(-23)) == expected_result);
    CHECK(SerializeOnly(static_cast<std::uint16_t>(-23)) == expected_result);
    CHECK(SerializeOnly(static_cast<std::uint32_t>(-23)) == expected_result);
    CHECK(SerializeOnly(static_cast<std::uint64_t>(-23)) == expected_result);
    CHECK(SerializeOnly(static_cast<std::double_t>(-23)) == expected_result);
    CHECK(SerializeOnly(static_cast<std::float_t>(-23)) == expected_result);
}

TEST_CASE("Clone") {
    NS::Archive                             out;

    out.serialize(10);
    out.serialize(20);
    out.serialize(30);

    NS::Archive                             in(out.commit());

    SECTION("Clone entire") {
        NS::Archive                         other(in.clone());

        CHECK(in.template deserialize<int>() == 10);
        CHECK(in.template deserialize<int>() == 20);
        CHECK(in.template deserialize<int>() == 30);

        CHECK(other.template deserialize<int>() == 10);
        CHECK(other.template deserialize<int>() == 20);
        CHECK(other.template deserialize<int>() == 30);
    }

    SECTION("Clone partial") {
        CHECK(in.template deserialize<int>() == 10);

        NS::Archive                         other(in.clone());

        CHECK(in.template deserialize<int>() == 20);
        CHECK(in.template deserialize<int>() == 30);

        CHECK(other.template deserialize<int>() == 20);
        CHECK(other.template deserialize<int>() == 30);
    }

    SECTION("Error cloning sink") {
        CHECK_THROWS_WITH(out.clone(), "Invalid mode");
    }

    SECTION("Error cloning complete archive") {
        CHECK(in.template deserialize<int>() == 10);
        CHECK(in.template deserialize<int>() == 20);
        CHECK(in.template deserialize<int>() == 30);

        CHECK_THROWS_WITH(in.clone(), "It isn't possible to clone a completed archive");
    }
}

TEST_CASE("Clone and movement") {
    NS::Archive                             out;

    out.serialize(10);
    out.serialize(20);
    out.serialize(30);

    NS::Archive                             in(out.commit());

    CHECK(in.Mode == NS::Archive::ModeValue::Deserializing);

    NS::Archive                             in2(in.clone());

    CHECK(in.Mode == NS::Archive::ModeValue::Deserializing);
    CHECK(in2.Mode == NS::Archive::ModeValue::Deserializing);

    NS::Archive                             in3(in.clone());

    CHECK(in.Mode == NS::Archive::ModeValue::Deserializing);
    CHECK(in2.Mode == NS::Archive::ModeValue::Deserializing);
    CHECK(in3.Mode == NS::Archive::ModeValue::Deserializing);

    NS::Archive                             movedIn1(std::move(in3));

    CHECK(in.Mode == NS::Archive::ModeValue::Deserializing);
    CHECK(in2.Mode == NS::Archive::ModeValue::Deserializing);
    CHECK(movedIn1.Mode == NS::Archive::ModeValue::Deserializing);

    NS::Archive                             movedIn2(std::move(movedIn1));

    CHECK(in.Mode == NS::Archive::ModeValue::Deserializing);
    CHECK(in2.Mode == NS::Archive::ModeValue::Deserializing);
    CHECK(movedIn2.Mode == NS::Archive::ModeValue::Deserializing);

    NS::Archive                             movedIn3(std::move(movedIn2));

    CHECK(in.Mode == NS::Archive::ModeValue::Deserializing);
    CHECK(in2.Mode == NS::Archive::ModeValue::Deserializing);
    CHECK(movedIn3.Mode == NS::Archive::ModeValue::Deserializing);
}
