#include "../../../Featurizers/DateTimeFeaturizer.h"
#include "../DateTimeFeaturizerWrapper.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cstdio>

TEST_CASE("Create/DeleteDateTimeTransformer", "[DateTimeFeaturizer][Wrapper]") {
    // In order to test both the create and delete functions exposed by the wrapper, I cannot use 
    // a smart pointer here. That means this test code is not exception safe and will leak memory 
    // if an exception happens between the call to `CreateDateTimeTransofmer` and `DeleteDateTimeTransformer`

    Microsoft::Featurizer::DateTimeTransformer* transformer = CreateDateTimeTransformer();
    CHECK(transformer != nullptr);

    bool success = DeleteDateTimeTransformer(transformer);

    CHECK(success);
}

TEST_CASE("Create/DeleteDateTimeTransformProxy", "[DateTimeFeaturizer][Wrapper]") {
    // In order to test both the create and delete functions exposed by the wrapper, I cannot use 
    // a smart pointer here for the TimePoint. That means this test code is not exception safe and will leak memory 
    // if an exception happens between the call to `DateTimeTransformerProxy` and `DateTimeTransformerCleanup`

    std::unique_ptr<Microsoft::Featurizer::DateTimeTransformer, decltype(&DeleteDateTimeTransformer)> transformer(CreateDateTimeTransformer(), &DeleteDateTimeTransformer);

    // Ticks for 2019-06-29 12:01:00 AM starting from 1970
    std::int64_t ticks = 15617664600000000;

    // Initialize time point
    Microsoft::Featurizer::TimePoint * timePoint(nullptr);    
    bool success = CreateDateTimeTransformProxy(ticks, transformer.get(), &timePoint);

    CHECK(success == true);
    CHECK(timePoint != nullptr);
    CHECK(timePoint->year == 2019);
    CHECK(timePoint->month == 6);
    CHECK(timePoint->day == 29);
    CHECK(timePoint->hour == 0);
    CHECK(timePoint->minute == 1);
    CHECK(timePoint->second == 0);
    CHECK(timePoint->dayOfWeek == 6);
    CHECK(timePoint->dayOfYear == 179);
    CHECK(timePoint->quarterOfYear == 2);
    CHECK(timePoint->weekOfMonth == 4);

    success = DeleteDateTimeTransformProxy(timePoint);

    CHECK(success);
}
