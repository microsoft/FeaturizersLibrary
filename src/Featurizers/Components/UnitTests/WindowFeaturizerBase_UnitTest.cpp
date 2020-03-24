// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../WindowFeaturizerBase.h"

namespace NS = Microsoft::Featurizer;

TEST_CASE("CircularIterator - Constructor Exceptions") {
    std::vector<std::int16_t> v{1,2,3,4,5};

    CHECK_THROWS_WITH(NS::Featurizers::Components::CircularIterator<std::int16_t>(nullptr, 0, 0, 0), "Input data cannot be a nullptr");
    CHECK_THROWS_WITH(NS::Featurizers::Components::CircularIterator<std::int16_t>(v.data(), 0, 0, 0), "Container max size cannot be 0");
    CHECK_THROWS_WITH(NS::Featurizers::Components::CircularIterator<std::int16_t>(v.data(), v.size(), 20, 0), "Cannot increment more than max_size times");
}

TEST_CASE("CircularIterator - Simple Test") {
    std::vector<std::int16_t> v{1,2,3,4,5};
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter(v.data(), v.size(), 5);
    CHECK(*iter == 1);
    iter++;
    CHECK(*iter == 2);
    iter++;
    CHECK(*iter == 3);
    iter++;
    CHECK(*iter == 4);
    iter++;
    CHECK(*iter == 5);
}

TEST_CASE("CircularIterator - Comparison Test") {
    std::vector<std::int16_t> v{1,2,3,4,5};
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(v.data(), v.size(), 5);
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter2(v.data(), v.size(), 5);

    // Should start out being equal
    CHECK(iter1 == iter2);

    // After update shouldn't be equal
    iter2++;
    CHECK(iter1 != iter2);

    // Should be equal again
    iter1++;
    CHECK(iter1 == iter2);
}

TEST_CASE("CircularIterator - Operations Test") {
    std::vector<std::int16_t> v{1,2,3,4,5};

    NS::Featurizers::Components::CircularIterator<std::int16_t> iter(v.data(), v.size(), 5);

    // Start deference should equal one
    CHECK(*iter == 1);

    // Post increment check
    CHECK(*iter++ == 1);
    CHECK(*iter == 2);

    // Pre increment check
    CHECK(*++iter == 3);
}

TEST_CASE("CircularIterator - String Test") {
    std::vector<std::string> v{"1","2","3","4","5"};

    NS::Featurizers::Components::CircularIterator<std::string> iter(v.data(), v.size(), 5);

    // Start deference should equal one
    CHECK(*iter == "1");

    // Post increment check
    CHECK(*iter++ == "1");
    CHECK(*iter == "2");

    // Pre increment check
    CHECK(*++iter == "3");

    // Check -> operator
    CHECK(iter->length() == 1);
}

TEST_CASE("CircularIterator - Array Test") {
    std::int16_t v[]{1,2,3,4,5};

    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(&v[0], 5, 5);
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter2(&v[0], 5, 5);

    // Should start out being equal
    CHECK(iter1 == iter2);

    // After update shouldn't be equal
    iter2++;
    CHECK(iter1 != iter2);

    // Should be equal again
    iter1++;
    CHECK(iter1 == iter2);
}

TEST_CASE("CircularIterator - Starting offset Test") {
    std::vector<std::int16_t> v{1,2,3,4,5};

    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(v.data(), v.size(), 5, 2);
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter2(v.data(), v.size(), 5);

    // Should NOT start out being equal since iter1 has an offset of 2
    CHECK(iter1 != iter2);

    CHECK(*iter1 == 3);

    // Increment iter2 twice to equal iter1
    CHECK(iter1 == ++(++iter2));

}

TEST_CASE("CircularIterator - End iterator Test") {
    std::vector<std::int16_t> v{1,2,3,4,5};

    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(v.data(), v.size(), 1, 2);
    NS::Featurizers::Components::CircularIterator<std::int16_t> end_iter(v.data(), v.size(), 0, 3);

    // Should NOT start out being equal since iter1 is not at end but end_iter is.
    CHECK(iter1 != end_iter);

    CHECK(*iter1 == 3);

    // Increment iter1 to equal end_iter
    CHECK(++iter1 == end_iter);
}

TEST_CASE("CircularIterator - End iterator Test While Loop") {
    std::vector<std::int16_t> v{1,2,3,4,5};

    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(v.data(), v.size(), v.size());
    NS::Featurizers::Components::CircularIterator<std::int16_t> end_iter(v.data(), v.size(), 0);

    // Should NOT start out being equal since iter1 is not at end but end_iter is.
    CHECK(iter1 != end_iter);

    // Loop till iter1 equals end_iter. Should loop 5 times.
    size_t count = 0;
    while(iter1 != end_iter) {
        ++iter1;
        ++count;
    }

    // Make sure it looped the correct number of times.
    CHECK(count == 5);

    // After while loop iterators should be the same
    CHECK(iter1 == end_iter);
}

TEST_CASE("CircularIterator - Const check") {
    std::vector<std::int16_t> v{1,2,3,4,5};

    NS::Featurizers::Components::CircularIterator<const std::int16_t> iter1(v.data(), v.size(), v.size());
    NS::Featurizers::Components::CircularIterator<const std::int16_t> end_iter(v.data(), v.size(), 0);

    // Should NOT start out being equal since iter1 is not at end but end_iter is.
    CHECK(iter1 != end_iter);

    // Loop till iter1 equals end_iter. Should loop 5 times.
    size_t count = 0;
    while(iter1 != end_iter) {
        ++iter1;
        ++count;
    }

    // Make sure it looped the correct number of times.
    CHECK(count == 5);

    // After while loop iterators should be the same
    CHECK(iter1 == end_iter);
}

TEST_CASE("CircularIterator - Default constructor") {
    NS::Featurizers::Components::CircularIterator<std::string> iter1;
    NS::Featurizers::Components::CircularIterator<std::string> iter2;

    // Make sure 2 iterators that were default constructed compare as equal
    CHECK(iter1 == iter2);
}

TEST_CASE("CircularBuffer - Empty buffer") {
    NS::Featurizers::Components::CircularBuffer<std::string> circ_buf(5);

    auto start_iter = circ_buf.begin();
    auto end_iter = circ_buf.end();

    // Since there is no data, the start and end iterators should be equal.
    CHECK(start_iter == end_iter);
}

TEST_CASE("CircularBuffer - Size 0 buffer") {
    CHECK_THROWS_WITH(NS::Featurizers::Components::CircularBuffer<std::string>(0), "Max size cannot be zero");
}

TEST_CASE("CircularBuffer - Size capacity full") {
    NS::Featurizers::Components::CircularBuffer<std::string> circ_buf(5);
    // capacity should be 5
    CHECK(circ_buf.capacity() == 5);
    // size should start with 0
    CHECK(circ_buf.size() == 0);
    // buffer is not full
    CHECK(!circ_buf.is_full());
    // size would be incremented as data are pushed
    circ_buf.push("1");
    CHECK(circ_buf.size() == 1);
    
    // capacity remains the same after an element is pushed
    CHECK(circ_buf.capacity() == 5);
    
    circ_buf.push("2");
    CHECK(circ_buf.size() == 2);
    
    circ_buf.push("3");
    CHECK(circ_buf.size() == 3);
    
    circ_buf.push("4");
    CHECK(circ_buf.size() == 4);
    
    circ_buf.push("5");
    CHECK(circ_buf.size() == 5);
    // buffer is full
    CHECK(circ_buf.is_full());
    // size reaches the maximum of 5 and never changed
    circ_buf.push("6");
    CHECK(circ_buf.size() == 5);

    // capacity remains the same after more than 5 elements are pushed
    CHECK(circ_buf.capacity() == 5);
    // buffer is full
    CHECK(circ_buf.is_full());
}

TEST_CASE("CircularBuffer - Push") {
    NS::Featurizers::Components::CircularBuffer<std::string> circ_buf(5);

    circ_buf.push("1");

    auto start_iter = circ_buf.begin();
    auto end_iter = circ_buf.end();

    // Since there is data, the start and end iterators shouldn't be equal.
    CHECK(start_iter != end_iter);

    // Make sure the value is what we expect
    CHECK(*start_iter == "1");

    // Make sure after 1 increment start and end are equal
    CHECK(++start_iter == end_iter);
}

TEST_CASE("CircularBuffer - Circular Push") {
    NS::Featurizers::Components::CircularBuffer<std::string> circ_buf(5);

    circ_buf.push("1");
    circ_buf.push("2");
    circ_buf.push("3");
    circ_buf.push("4");
    circ_buf.push("5");
    circ_buf.push("6");

    auto start_iter = circ_buf.begin();
    auto end_iter = circ_buf.end();

    // Make sure after fully populated, new pushes will change the begin()
    CHECK(*start_iter == "2");

    size_t count = 0;
    auto it1 = start_iter;
    while(it1 != end_iter) {
        ++it1;
        ++count;
    }
    // Make sure it looped the correct number of times.
    CHECK(count == 5);

    auto it2 = start_iter;
    for (size_t i=0; i<4; i++) {
        ++it2;
    }

    // Make sure new value replaces
    CHECK(*it2 == "6");
}
TEST_CASE("CircularBuffer - Circular Clear") {
    NS::Featurizers::Components::CircularBuffer<std::string> circ_buf(5);

    CHECK(circ_buf.size() == 0);
    CHECK(circ_buf.capacity() == 5);
    CHECK(!circ_buf.is_full());

    circ_buf.push("1");
    circ_buf.push("2");
    circ_buf.push("3");
    circ_buf.push("4");
    circ_buf.push("5");
    circ_buf.push("6");

    CHECK(circ_buf.size() == 5);
    CHECK(circ_buf.is_full());

    // after clear is called, capacity should remain the same while size should be reset to 0
    circ_buf.clear();
    CHECK(circ_buf.capacity() == 5);
    CHECK(circ_buf.size() == 0);
    CHECK(!circ_buf.is_full());
}

TEST_CASE("CircularBuffer - Range") {
    using iterator = typename NS::Featurizers::Components::CircularBuffer<std::int16_t>::iterator;
    NS::Featurizers::Components::CircularBuffer<std::int16_t> circ_buf(5);

    circ_buf.push(1);
    circ_buf.push(2);
    circ_buf.push(3);

    // When the vector is not fully populated and the number of requested items is less than the current populated size
    std::tuple<iterator, iterator> range = circ_buf.range(2);

    auto start_iter = std::get<0>(range);
    auto end_iter = std::get<1>(range);

    size_t count = 0;
    while(start_iter != end_iter) {
        ++start_iter;
        ++count;
    }
    CHECK(count == 2);

    // When the vector is not fully populated and the number of requested items is greater than the current populated size
    // the end iterator should be bounded by the currect populated size
    std::tuple<iterator, iterator> range2 = circ_buf.range(4);

    auto start_iter2 = std::get<0>(range2);
    auto end_iter2 = std::get<1>(range2);

    count = 0;
    while(start_iter2 != end_iter2) {
        ++start_iter2;
        ++count;
    }
    CHECK(count == 3);
}

TEST_CASE("CircularBuffer - Empty buffer Range") {
    using iterator = typename NS::Featurizers::Components::CircularBuffer<std::int16_t>::iterator;
    NS::Featurizers::Components::CircularBuffer<std::int16_t> circ_buf(5);

    std::tuple<iterator, iterator> range = circ_buf.range(3);

    // when there's no data within the buffer, begin and iterators are both pointing to the start location
    auto start_iter = std::get<0>(range);
    auto end_iter = std::get<1>(range);

    CHECK(start_iter == end_iter);
}

TEST_CASE("CircularBuffer - Range 0") {
    using iterator = typename NS::Featurizers::Components::CircularBuffer<std::int16_t>::iterator;
    NS::Featurizers::Components::CircularBuffer<std::int16_t> circ_buf(5);

    circ_buf.push(1);
    circ_buf.push(2);
    circ_buf.push(3);

    std::tuple<iterator, iterator> range = circ_buf.range(0);

    auto start_iter = std::get<0>(range);
    auto end_iter = std::get<1>(range);

    CHECK(start_iter == end_iter);
}

TEST_CASE("CircularBuffer - range wrapping") {
    using iterator = typename NS::Featurizers::Components::CircularBuffer<std::int16_t>::iterator;
    NS::Featurizers::Components::CircularBuffer<std::int16_t> circ_buf(3);

    circ_buf.push(1);
    circ_buf.push(2);
    circ_buf.push(3);
    circ_buf.push(4);
    circ_buf.push(5);

    std::tuple<iterator, iterator> range = circ_buf.range(2);

    auto start_iter = std::get<0>(range);
    auto end_iter = std::get<1>(range);

    CHECK(start_iter != end_iter);
    CHECK(*start_iter == 3);

    CHECK(*(++start_iter) == 4);

    CHECK(++start_iter == end_iter);
}

TEST_CASE("CircularBuffer - range with offset") {
    using iterator = typename NS::Featurizers::Components::CircularBuffer<std::int16_t>::iterator;
    NS::Featurizers::Components::CircularBuffer<std::int16_t> circ_buf(5);

    circ_buf.push(1);
    circ_buf.push(2);
    circ_buf.push(3);

    std::tuple<iterator, iterator> range = circ_buf.range(1, 4);

    auto start_iter = std::get<0>(range);
    auto end_iter = std::get<1>(range);
    // when offset is greater than current size, return iterators are all end iterators
    CHECK(start_iter == end_iter);

    std::tuple<iterator, iterator> range2 = circ_buf.range(2,2);

    auto start_iter2 = std::get<0>(range2);
    auto end_iter2 = std::get<1>(range2);
    // when n + offset is greater than current size
    CHECK(++start_iter2 == end_iter2);

    std::tuple<iterator, iterator> range3 = circ_buf.range(2,1);

    auto start_iter3 = std::get<0>(range3);
    auto end_iter3 = std::get<1>(range3);
    // when n and offset are not out of bound
    CHECK(++(++start_iter3) == end_iter3);
}
