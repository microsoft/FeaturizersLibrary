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
    std::vector<std::int16_t> v{1,2,3,4,5};
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter(&v[0], v.size());
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
    std::vector<std::int16_t> v{1,2,3,4,5};
    
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(&v[0], v.size());
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter2(&v[0], v.size());

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
    
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter(&v[0], v.size());

    // Start deference should equal one
    CHECK(*iter == 1);

    // Post increment check
    CHECK(*iter++ == 1);
    CHECK(*iter == 2);

    // Pre increment check
    CHECK(*++iter == 3);

    // Addition check
    CHECK(*(iter + 2) == 5);

    // Addition check with looping
    CHECK(*(iter + 3) == 1);    
}

TEST_CASE("String Test") {
    std::vector<std::string> v{"1","2","3","4","5"};
    
    NS::Featurizers::Components::CircularIterator<std::string> iter(&v[0], v.size());

    // Start deference should equal one
    CHECK(*iter == "1");

    // Post increment check
    CHECK(*iter++ == "1");
    CHECK(*iter == "2");

    // Pre increment check
    CHECK(*++iter == "3");

    // Addition check
    CHECK(*(iter + 2) == "5");

    // Addition check with looping
    CHECK(*(iter + 3) == "1");

    // Check -> operator
    CHECK(iter->length() == 1);
}

TEST_CASE("Array Test") {
    std::int16_t v[]{1,2,3,4,5};

    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(&v[0], 5);
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter2(&v[0], 5);

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

    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(&v, 1);
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter2(&v, 1);

    // Should start out being equal
    CHECK(iter1 == iter2);

    // Since only 1 value, increment should keep the same value
    CHECK(++iter1 == iter2);
    
    // Since only 1 value, increment should keep the same value
    CHECK(iter1 == ++iter2);

}

TEST_CASE("Starting offset Test") {
    std::vector<std::int16_t> v{1,2,3,4,5};

    NS::Featurizers::Components::CircularIterator<std::int16_t> iter1(&v[0], v.size(), 2);
    NS::Featurizers::Components::CircularIterator<std::int16_t> iter2(&v[0], v.size());

    // Should NOT start out being equal since iter1 has an offset of 2
    CHECK(iter1 != iter2);

    CHECK(*iter1 == 3);

    // Increment iter2 twice to equal iter1
    CHECK(iter1 == (iter2 + 2));

}
