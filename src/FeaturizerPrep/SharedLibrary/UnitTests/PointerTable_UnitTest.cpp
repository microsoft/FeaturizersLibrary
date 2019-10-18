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

    size_t i0 = TestTable.Add<int>(&p0);
    CHECK(TestTable.Get<int>(i0) == &p0);
    CHECK(*TestTable.Get<int>(i0) == p0);

    size_t i1 = TestTable.Add<int>(&p1);
    CHECK(TestTable.Get<int>(i1) == &p1);
    CHECK(*TestTable.Get<int>(i1) == p1);



    TestTable.Remove(i1);
    // exceptions
    REQUIRE_THROWS_WITH(TestTable.Add<int>(nullptr),"Trying to add a null pointer to the table!");
    REQUIRE_THROWS_WITH(TestTable.Get<int>(i1),"Invalid query to the Pointer table, index incorrect!");
    REQUIRE_THROWS_WITH(TestTable.Get<int>(0),"Invalid query to the Pointer table, index cannot be zero!");
    REQUIRE_THROWS_WITH(TestTable.Remove(i1),"Invalid remove from the Pointer table, index pointer not found!");
    REQUIRE_THROWS_WITH(TestTable.Remove(0),"Invalid remove from the Pointer table, index cannot be zero!");


}

TEST_CASE("Check_Randomness_Given_Seed") {
    PointerTable TestTable(5);


    int p0 = 0;
    int p1 = 1;
    int p2 = 2;

    size_t i0 = TestTable.Add<int>(&p0);
    size_t i1 = TestTable.Add<int>(&p1);
    size_t i2 = TestTable.Add<int>(&p2);

#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127)           // conditional expression is constant
#endif

    if(sizeof(size_t) == 8) {
        // 64 bit
        CHECK(i0 == 4095051218741643471UL);
        CHECK(i1 == 16062175962503177918UL);
        CHECK(i2 == 3813295331020233847UL);
    }
    else {
        // 32 bit
        CHECK(i0 == 953453412);
        CHECK(i1 == 236996815);
        CHECK(i2 == 3739766768);
    }

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif
}
