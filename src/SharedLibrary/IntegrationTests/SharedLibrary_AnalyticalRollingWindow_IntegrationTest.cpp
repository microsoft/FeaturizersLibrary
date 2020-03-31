// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GeneratedCode/SharedLibraryTests_AnalyticalRollingWindowFeaturizer.h"
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

    AnalyticalRollingWindowFeaturizer_int32_Test(
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
        [](std::vector<std::vector<double>> const &args) {
            // NaN values always compare as false, so we have to creatively compare.
            std::vector<std::vector<double>> const      other{
                std::vector<double>{ Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue() },
                std::vector<double>{ Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1.0 },
                std::vector<double>{ Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1.0, 1.5 },
                std::vector<double>{ 1.0, 1.5, 2.5 },

                std::vector<double>{ Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue() },
                std::vector<double>{ Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1 },
                std::vector<double>{ Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1.0, 1.5 },

                std::vector<double>{ Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue() },
                std::vector<double>{ Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1 },

                std::vector<double>{ Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue() },

                std::vector<double>{ 1.0, 1.5, 2.5 },

                std::vector<double>{ Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1.0, 1.5 },
                std::vector<double>{ 1.0, 1.5, 2.5 },

                std::vector<double>{ Microsoft::Featurizer::Traits<double>::CreateNullValue(), Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1 },
                std::vector<double>{ Microsoft::Featurizer::Traits<double>::CreateNullValue(), 1.0, 1.5 },
                std::vector<double>{ 1.0, 1.5, 2.5 }
            };

            CHECK(args.size() == other.size());

            for(size_t row = 0; row < args.size(); ++row) {
                std::vector<double> const &             v1(args[row]);
                std::vector<double> const &             v2(other[row]);

                REQUIRE(v1.size() == v2.size());

                for(size_t col = 0; col < v1.size(); ++col) {
                    double const &          d1(v1[col]);
                    double const &          d2(v2[col]);

                    if(Microsoft::Featurizer::Traits<double>::IsNull(d1)) {
                        CHECK(Microsoft::Featurizer::Traits<double>::IsNull(d2));
                    }
                    else {
                        CHECK(Approx(d1) == d2);
                    }
                }
            }
            return true;
        },
        static_cast<AnalyticalRollingWindowFeaturizer_AnalyticalRollingWindowCalculationType>(AnalyticalRollingWindowFeaturizer_AnalyticalRollingWindowCalculation_Mean),
        3UL,
        2UL,
        1UL
    );
}
