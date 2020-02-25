// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../WindowOperationBase.h"

namespace NS = Microsoft::Featurizer;


TEST_CASE("simple test") {
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

