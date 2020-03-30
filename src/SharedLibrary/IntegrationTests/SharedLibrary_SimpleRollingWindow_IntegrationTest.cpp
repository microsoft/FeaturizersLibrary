// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_SimpleRollingWindowFeaturizer.h"
#include "../../3rdParty/optional.h"

TEST_CASE("Min - int32, window size 2, horizon 3") {
    std::vector<std::string> const          grain1{ "one" };
    std::vector<std::string> const          grain2{ "one", "two" };
    std::vector<std::string> const          grain3{ "one", "two", "three" };
    std::vector<std::string> const          grain4{ "completely_different" };
    int32_t const                           value1(1);
    int32_t const                           value2(2);
    int32_t const                           value3(3);
    int32_t const                           value4(4);

    SimpleRollingWindowFeaturizer_int32_Test(
        std::vector<std::tuple<std::vector<std::string> const &, int32_t const &>>(),
        std::vector<std::tuple<std::vector<std::string> const &, int32_t const &>>{
            std::make_tuple(grain1, value1),
            std::make_tuple(grain1, value2),
            std::make_tuple(grain1, value3),
            std::make_tuple(grain1, value4),

            std::make_tuple(grain2, value1),
            std::make_tuple(grain2, value2),
            std::make_tuple(grain2, value3),

            std::make_tuple(grain3, value1),
            std::make_tuple(grain3, value2),

            std::make_tuple(grain4, value1),

            std::make_tuple(grain2, value4),

            std::make_tuple(grain3, value3),
            std::make_tuple(grain3, value4),

            std::make_tuple(grain4, value2),
            std::make_tuple(grain4, value3),
            std::make_tuple(grain4, value4)
        },
        [](std::vector<std::vector<nonstd::optional<int32_t>>> const &args) {
            CHECK(
                args == std::vector<std::vector<nonstd::optional<int32_t>>>{
                    std::vector<nonstd::optional<int32_t>>{ nonstd::optional<int32_t>(), nonstd::optional<int32_t>(), nonstd::optional<int32_t>() },
                    std::vector<nonstd::optional<int32_t>>{ nonstd::optional<int32_t>(), nonstd::optional<int32_t>(), 1 },
                    std::vector<nonstd::optional<int32_t>>{ nonstd::optional<int32_t>(), 1, 2 },
                    std::vector<nonstd::optional<int32_t>>{ 1, 2, 3 },

                    std::vector<nonstd::optional<int32_t>>{ nonstd::optional<int32_t>(), nonstd::optional<int32_t>(), nonstd::optional<int32_t>() },
                    std::vector<nonstd::optional<int32_t>>{ nonstd::optional<int32_t>(), nonstd::optional<int32_t>(), 1 },
                    std::vector<nonstd::optional<int32_t>>{ nonstd::optional<int32_t>(), 1, 2 },

                    std::vector<nonstd::optional<int32_t>>{ nonstd::optional<int32_t>(), nonstd::optional<int32_t>(), nonstd::optional<int32_t>() },
                    std::vector<nonstd::optional<int32_t>>{ nonstd::optional<int32_t>(), nonstd::optional<int32_t>(), 1 },

                    std::vector<nonstd::optional<int32_t>>{ nonstd::optional<int32_t>(), nonstd::optional<int32_t>(), nonstd::optional<int32_t>() },

                    std::vector<nonstd::optional<int32_t>>{ 1, 2, 3 },

                    std::vector<nonstd::optional<int32_t>>{ nonstd::optional<int32_t>(), 1, 2 },
                    std::vector<nonstd::optional<int32_t>>{ 1, 2, 3 },

                    std::vector<nonstd::optional<int32_t>>{ nonstd::optional<int32_t>(), nonstd::optional<int32_t>(), 1 },
                    std::vector<nonstd::optional<int32_t>>{ nonstd::optional<int32_t>(), 1, 2 },
                    std::vector<nonstd::optional<int32_t>>{ 1, 2, 3 }
                }
            );
            return true;
        },
        static_cast<SimpleRollingWindowFeaturizer_SimpleRollingWindowCalculationType>(SimpleRollingWindowFeaturizer_SimpleRollingWindowCalculation_Max),
        3UL,
        2UL,
        1UL
    );
}
