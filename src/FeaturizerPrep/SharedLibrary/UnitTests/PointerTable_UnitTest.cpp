// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#define CATCH_CONFIG_MAIN
#include <string>
#include <iostream>

#include "catch.hpp"

#include "../PointerTable.h"

using Microsoft::Featurizer::PointerTable;
using namespace std;
using Catch::Matchers::EndsWith;

TEST_CASE("Add_Find_Remove") {

    PointerTable TestTable;
    

    int p0 = 0;
    int p1 = 1;

    uint32_t i0 = TestTable.Add<int>(&p0);
    CHECK(TestTable.Find<int>(i0) == &p0);
    CHECK(*TestTable.Find<int>(i0) == p0);
    
    uint32_t i1 = TestTable.Add<int>(&p1);
    CHECK(TestTable.Find<int>(i1) == &p1);
    CHECK(*TestTable.Find<int>(i1) == p1);



    TestTable.Remove(i1);
    // exceptions
    REQUIRE_THROWS_WITH(TestTable.Add<int>(nullptr),"Trying to add a null pointer to the table!");
    REQUIRE_THROWS_WITH(TestTable.Find<int>(i1),"Invalid query to the Pointer table, index incorrect!");
    REQUIRE_THROWS_WITH(TestTable.Find<int>(0),"Invalid query to the Pointer table, index cannot be zero!");
    REQUIRE_THROWS_WITH(TestTable.Remove(i1),"Invalid remove from the Pointer table, index pointer not found!");
    REQUIRE_THROWS_WITH(TestTable.Remove(0),"Invalid remove from the Pointer table, index cannot be zero!");


}

TEST_CASE("Check_Randomness_Given_Seed") {
    PointerTable TestTable(5);
    

    int p0 = 0;
    int p1 = 1;
    int p2 = 2;

    uint32_t i0 = TestTable.Add<int>(&p0);
    CHECK(i0 == 953453412);
    
    uint32_t i1 = TestTable.Add<int>(&p1);
    CHECK(i1 == 236996815);


    uint32_t i2 = TestTable.Add<int>(&p2);
    CHECK(i2 == 3739766768);
    

}
