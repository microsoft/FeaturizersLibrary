// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../Featurizers/SampleSequenceSumFeaturizer.h"
#include "../TestHelpers.h"
#include "../../Traits.h"
#include "../Structs.h"

namespace NS = Microsoft::Featurizer;

template <typename T>
using Range = std::pair<typename std::vector<T>::const_iterator, typename std::vector<T>::const_iterator>;

TEST_CASE("double_t") {
    using ValueType       = std::double_t;
    using InputType       = Range<ValueType>;
    using TransformedType = std::double_t;

    std::vector<ValueType> row1({7., 4.,  6.,  10.});
    NS::Featurizers::SampleSequenceSumTransformer<InputType> transformer;

    std::double_t result = 0;
    auto callback = [&result](std::double_t v) {
        result = v;
    };

    transformer.execute(std::make_pair(row1.cbegin(), row1.cend()), callback);
    CHECK(result == 17.);
}

//TEST_CASE("Serialization/Deserialization") {
//    using ValueType       = std::int16_t;
//    using InputType       = Range<ValueType>;
//    using TransformerType = NS::Featurizers::SampleSequenceSumTransformer<InputType>;
//
//    TransformerType transformer;
//
//    NS::Archive archive;
//    transformer.save(archive);
//    std::vector<uint8_t> vec = archive.commit();
//
//    NS::Archive loader(vec);
//    TransformerType modelLoaded(loader);
//    CHECK(modelLoaded == transformer);
//}

//TEST_CASE("Serialization Version Error") {
//    using ValueType       = std::int16_t;
//    using InputType       = Range<ValueType>;
//
//    NS::Archive                             out;
//
//    out.serialize(static_cast<std::uint16_t>(2));
//    out.serialize(static_cast<std::uint16_t>(0));
//
//    NS::Archive                             in(out.commit());
//
//    CHECK_THROWS_WITH(
//        (NS::Featurizers::SampleSequenceSumTransformer<InputType>(in)),
//        Catch::Contains("Unsupported archive version")
//    );
//}
