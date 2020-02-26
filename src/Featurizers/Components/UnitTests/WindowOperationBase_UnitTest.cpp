// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../WindowOperationBase.h"

namespace NS = Microsoft::Featurizer;


TEST_CASE("Simple Test") {
    // 20 is longer than the input array. Testing looping capabilities.
    std::vector<std::int16_t> v{1,2,3,4,5};
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter(&v[0], v.size(), 20);
    CHECK(*iter == 1);
    iter++;
    CHECK(*iter == 2);
    iter++;
    CHECK(*iter == 3);
    iter++;
    CHECK(*iter == 4);
    iter++;
    CHECK(*iter == 5);
    iter++;
    CHECK(*iter == 1);
    iter++;
    CHECK(*iter == 2);
    iter++;
    CHECK(*iter == 3);
    iter++;
    CHECK(*iter == 4);
    iter++;
    CHECK(*iter == 5);
    iter++;
}

TEST_CASE("Comparison Test") {
    // 20 is longer than the input array. Testing looping capabilities while comparing iterators.
    std::vector<std::int16_t> v{1,2,3,4,5};
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(&v[0], v.size(), 20);
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter2(&v[0], v.size(), 20);

    // Should start out being equal
    CHECK(iter1 == iter2);

    // After update shouldn't be equal
    iter2++;
    CHECK(iter1 != iter2);

    // Should be equal again
    iter1++;
    CHECK(iter1 == iter2);

    // Doing a full loop should result in the iterators being equal
    // iter1 = 3, iter2 = 2
    CHECK(++iter1 != iter2);

    // iter1 = 4, iter2 = 2
    CHECK(++iter1 != iter2);

    // iter1 = 5, iter2 = 2
    CHECK(++iter1 != iter2);

    // iter1 = 1, iter2 = 2
    CHECK(++iter1 != iter2);
        
    // iter1 = 2, iter2 = 2
    CHECK(++iter1 == iter2);
}

TEST_CASE("Operations Test") {
    std::vector<std::int16_t> v{1,2,3,4,5};
    
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter(&v[0], v.size(), 5);

    // Start deference should equal one
    CHECK(*iter == 1);

    // Post increment check
    CHECK(*iter++ == 1);
    CHECK(*iter == 2);

    // Pre increment check
    CHECK(*++iter == 3);
}

TEST_CASE("String Test") {
    std::vector<std::string> v{"1","2","3","4","5"};
    
    NS::Featurizers::Components::CircularIterator<std::string> iter(&v[0], v.size(), 5);

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

TEST_CASE("Array Test") {
    // 20 is longer than the input array. Testing looping capabilities. Just validating it works with multiple containers.
    std::int16_t v[]{1,2,3,4,5};

    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(&v[0], 5, 20);
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter2(&v[0], 5, 20);

    // Should start out being equal
    CHECK(iter1 == iter2);

    // After update shouldn't be equal
    iter2++;
    CHECK(iter1 != iter2);

    // Should be equal again
    iter1++;
    CHECK(iter1 == iter2);

    // Doing a full loop should result in the iterators being equal
    // iter1 = 3, iter2 = 2
    CHECK(++iter1 != iter2);

    // iter1 = 4, iter2 = 2
    CHECK(++iter1 != iter2);

    // iter1 = 5, iter2 = 2
    CHECK(++iter1 != iter2);

    // iter1 = 1, iter2 = 2
    CHECK(++iter1 != iter2);
        
    // iter1 = 2, iter2 = 2
    CHECK(++iter1 == iter2);
}

TEST_CASE("Single Value Test") {
    std::int16_t v = 1;

    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(&v, 1, 2);
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter2(&v, 1, 2);

    // Should start out being equal
    CHECK(iter1 == iter2);

    // Since only 1 value, increment should keep the same value
    CHECK(++iter1 == iter2);
    
    // Since only 1 value, increment should keep the same value
    CHECK(iter1 == ++iter2);

}

TEST_CASE("Starting offset Test") {
    std::vector<std::int16_t> v{1,2,3,4,5};

    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(&v[0], v.size(), 5, 2);
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter2(&v[0], v.size(), 5);

    // Should NOT start out being equal since iter1 has an offset of 2
    CHECK(iter1 != iter2);

    CHECK(*iter1 == 3);

    // Increment iter2 twice to equal iter1
    CHECK(iter1 == ++(++iter2));

}

TEST_CASE("End iterator Test") {
    std::vector<std::int16_t> v{1,2,3,4,5};

    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(&v[0], v.size(), 1, 2);
    NS::Featurizers::Components::CircularIterator<std::int16_t> end_iter(&v[0], v.size(), 0, 3);

    // Should NOT start out being equal since iter1 is not at end but end_iter is.
    CHECK(iter1 != end_iter);

    CHECK(*iter1 == 3);

    // Increment iter1 to equal end_iter
    CHECK(++iter1 == end_iter);

}
