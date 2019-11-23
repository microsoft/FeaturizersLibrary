// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../Featurizers/Structs.h"



namespace NS = Microsoft::Featurizer;

TEST_CASE("check equal") {
    NS::Featurizers::OneHotStruct lhs(0,10,1);
    NS::Featurizers::OneHotStruct rhs1(0,10,1);
    CHECK(lhs == rhs1);

    NS::Featurizers::OneHotStruct rhs2(1,7,0);
    CHECK(!(lhs == rhs2));

}

TEST_CASE("invalid input parameters") {
    CHECK_THROWS_WITH(NS::Featurizers::OneHotStruct(10,8,1), "Category index should be smaller than total number of categories!");
}
