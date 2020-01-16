// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Featurizers/CatImputerFeaturizer.h"
#include "../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

template<typename transformedType, typename castType = uint8_t>
void NumericTestWrapper(){
    using inputType = typename NS::Traits<transformedType>::nullable_type;

    inputType null = NS::Traits<transformedType>::CreateNullValue();

    // Passing int values to make_vector for an optional type gives following error
    // error: implicit conversion loses integer precision: 'int' to 'nonstd::optional_lite::
    // Hence explicit cast to uint8_t.
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<inputType>>(
                NS::TestHelpers::make_vector<inputType>(static_cast<castType>(10),static_cast<castType>(20),null),
                NS::TestHelpers::make_vector<inputType>(static_cast<castType>(10),static_cast<castType>(30),null),
                NS::TestHelpers::make_vector<inputType>(static_cast<castType>(10),static_cast<castType>(10),null),
                NS::TestHelpers::make_vector<inputType>(static_cast<castType>(11),static_cast<castType>(15),null),
                NS::TestHelpers::make_vector<inputType>(static_cast<castType>(18),static_cast<castType>(8),null));

    auto inferencingInput = NS::TestHelpers::make_vector<inputType>(static_cast<castType>(5),static_cast<castType>(8),static_cast<castType>(20)
                ,null,null,null,null);

    auto inferencingOutput = NS::TestHelpers::make_vector<transformedType>(
        static_cast<castType>(5),
        static_cast<castType>(8),
        static_cast<castType>(20),
        static_cast<castType>(10),
        static_cast<castType>(10),
        static_cast<castType>(10),
        static_cast<castType>(10)
    );

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::CatImputerEstimator<transformedType>(NS::CreateTestAnnotationMapsPtr(1), 0),
            trainingBatches,
            inferencingInput
        ) == inferencingOutput
    );
}

TEST_CASE("CatImputer- int8_t") {
    using transformedType = std::int8_t;

    // With default castType of uint8_t we get following error
    // error: implicit conversion changes signedness: 'unsigned char' to 'nonstd::optional_lite::detail::storage_t<signed char>::value_type' (aka 'signed char')
    NumericTestWrapper<transformedType,std::int8_t>();
}

TEST_CASE("CatImputer- uint8_t") {
    using transformedType = std::uint8_t;

    NumericTestWrapper<transformedType>();
}

TEST_CASE("CatImputer- uint16_t") {
    using transformedType = std::uint16_t;

    NumericTestWrapper<transformedType>();
}

TEST_CASE("CatImputer- int16_t") {
    using transformedType = std::int16_t;

    NumericTestWrapper<transformedType>();
}

TEST_CASE("CatImputer- uint32_t") {
    using transformedType = std::uint32_t;

    NumericTestWrapper<transformedType>();
}

TEST_CASE("CatImputer- int32_t") {
    using transformedType = std::int32_t;

    NumericTestWrapper<transformedType>();
}

TEST_CASE("CatImputer- uint64_t") {
    using transformedType = std::uint64_t;

    NumericTestWrapper<transformedType>();
}

TEST_CASE("CatImputer- int64_t") {
    using transformedType = std::int64_t;

    NumericTestWrapper<transformedType>();
}

TEST_CASE("CatImputer- float") {
    NumericTestWrapper<std::float_t>();
}

TEST_CASE("CatImputer- double") {
    NumericTestWrapper<std::double_t,std::double_t>();
}

TEST_CASE("CatImputer- string") {
    using type = nonstd::optional<std::string>;
    using transformedType = std::string;

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::CatImputerEstimator<transformedType>(NS::CreateTestAnnotationMapsPtr(1), 0),
            NS::TestHelpers::make_vector<std::vector<type>>(
                NS::TestHelpers::make_vector<type>("one", "one", "one", type(), type(), "two", type(), type(), "three")
            ),
            NS::TestHelpers::make_vector<type>("one", "two", "three",type())
        ) == NS::TestHelpers::make_vector<transformedType>("one","two","three","one")
    );
}

TEST_CASE("CatImputer- All values Null") {
    using type = nonstd::optional<std::int64_t>;
    using transformedType = std::int64_t;

    CHECK_THROWS_WITH(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::CatImputerEstimator<transformedType>(NS::CreateTestAnnotationMapsPtr(1), 0),
            NS::TestHelpers::make_vector<std::vector<type>>(
                NS::TestHelpers::make_vector<type>(type{},type{},type{},type{},type{},type{})),
                NS::TestHelpers::make_vector<type>(5, 8, 20,type{}))
                , Catch::Contains("The histogram does not contain any supported values"));
}

TEST_CASE("Serialization/Deserialization- Numeric") {
    using transformedType                   = std::int64_t;
    using transformerType                   = NS::Featurizers::CatImputerTransformer<transformedType>;

    auto model = std::make_shared<transformerType>(10);

    NS::Archive archive;
    model->save(archive);
    std::vector<unsigned char> vec = archive.commit();
    
    NS::Archive loader(vec);
    transformerType modelLoaded(loader);
    CHECK(modelLoaded.Value == model->Value);
}

TEST_CASE("Serialization/Deserialization- string") {
    using transformedType                   = std::string;
    using transformerType                   = NS::Featurizers::CatImputerTransformer<transformedType>;

    auto model = std::make_shared<transformerType>("one");

    NS::Archive archive;
    model->save(archive);
    std::vector<unsigned char> vec = archive.commit();

    NS::Archive loader(vec);
    transformerType modelLoaded(loader);
    CHECK(modelLoaded.Value == model->Value);

}

TEST_CASE("Serialization Version Error") {
    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        NS::Featurizers::CatImputerTransformer<std::string>(in),
        Catch::Contains("Unsupported archive version")
    );
}
