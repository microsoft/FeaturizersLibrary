// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Featurizers/NormalizeFeaturizer.h"
#include "../TestHelpers.h"
#include "../../Traits.h"
#include "../Structs.h"
namespace NS = Microsoft::Featurizer;

template <typename T>
using Range = std::pair<typename std::vector<T>::iterator, typename std::vector<T>::iterator>;

TEST_CASE("invalid input iterators") {
    using ValueType       = std::int16_t;
    using InputType       = Range<ValueType>;
    using TransformedType = std::vector<std::double_t>;

    std::vector<ValueType> row1({4, 1, 2, 2});


    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(InputType(row1.begin(), row1.end())));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(InputType(row1.end(), row1.begin()));

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        NS::TestHelpers::make_vector<std::double_t>(0.8, 0.2, 0.4, 0.4)
    );

    NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK_THROWS_WITH(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::L2NormalizeEstimator<InputType>(pAllColumnAnnotations, 0),
            trainingBatches,
            inferencingInput
        ), "Input iterators to VectorNormsEstimator are invalid!"
    );
}

TEST_CASE("invalid input norms") {
    using ValueType       = std::int16_t;
    using InputType       = Range<ValueType>;
    using TransformerType = NS::Featurizers::NormalizeTransformer<InputType>;

    std::vector<std::double_t> norms;
    CHECK_THROWS_WITH(std::make_shared<TransformerType>(norms), "Norms input to NormalizeTransformer is empty!");

    norms.emplace_back(1);
    norms.emplace_back(-5);
    CHECK_THROWS_WITH(std::make_shared<TransformerType>(norms), "Norms shouldn't be less than 0!");
}

TEST_CASE("double_t - max norm") {
    using ValueType       = std::double_t;
    using InputType       = Range<ValueType>;
    using TransformedType = std::vector<std::double_t>;

    std::vector<ValueType> row1({7.9, 4.37,  6,  10});


    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(InputType(row1.begin(), row1.end())));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(InputType(row1.begin(), row1.end()));

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        NS::TestHelpers::make_vector<std::double_t>(0.79, 0.437,  0.6, 1.0)
    );

    NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::MaxNormalizeEstimator<InputType>(pAllColumnAnnotations, 0),
            trainingBatches,
            inferencingInput
        ) == inferencingOutput
    );
}

TEST_CASE("int16_t - l2 norm") {
    using ValueType       = std::int16_t;
    using InputType       = Range<ValueType>;
    using TransformedType = std::vector<std::double_t>;

    std::vector<ValueType> row1({4, 1, 2, 2});
    std::vector<ValueType> row2({1, 3, 9, 3});
    std::vector<ValueType> row3({5, 7, 5, 1});


    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(InputType(row1.begin(), row1.end())),
                                    NS::TestHelpers::make_vector<InputType>(InputType(row2.begin(), row2.end())),
                                    NS::TestHelpers::make_vector<InputType>(InputType(row3.begin(), row3.end())));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(InputType(row1.begin(), row1.end()),
                                                                     InputType(row2.begin(), row2.end()),
                                                                     InputType(row3.begin(), row3.end()));

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        NS::TestHelpers::make_vector<std::double_t>(0.8, 0.2, 0.4, 0.4),
        NS::TestHelpers::make_vector<std::double_t>(0.1, 0.3, 0.9, 0.3),
        NS::TestHelpers::make_vector<std::double_t>(0.5, 0.7, 0.5, 0.1)
    );

    NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::L2NormalizeEstimator<InputType>(pAllColumnAnnotations, 0),
            trainingBatches,
            inferencingInput
        ) == inferencingOutput
    );
}


TEST_CASE("nonstd::optional<int> - l1 norm") {
    using ValueType       = nonstd::optional<int>;
    using InputType       = Range<ValueType>;
    using TransformedType = std::vector<std::double_t>;

    ValueType inputNull = NS::Traits<ValueType>::CreateNullValue();
    std::double_t outputNull = NS::Traits<std::double_t>::CreateNullValue();


    std::vector<ValueType> row1({1, inputNull, 2, inputNull, 3, 4});


    auto trainingBatches  = NS::TestHelpers::make_vector<std::vector<InputType>>(
                                    NS::TestHelpers::make_vector<InputType>(InputType(row1.begin(), row1.end())));

    auto inferencingInput  = NS::TestHelpers::make_vector<InputType>(InputType(row1.begin(), row1.end()));

    auto inferencingOutput = NS::TestHelpers::make_vector<TransformedType>(
        NS::TestHelpers::make_vector<std::double_t>(0.1, outputNull, 0.2, outputNull, 0.3, 0.4)
    );

    NS::AnnotationMapsPtr const                                          pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(NS::TestHelpers::FuzzyCheck(
        NS::TestHelpers::TransformerEstimatorTest(
            NS::Featurizers::L1NormalizeEstimator<InputType>(pAllColumnAnnotations, 0),
            trainingBatches,
            inferencingInput
        )[0], inferencingOutput[0]
    ));
}
TEST_CASE("Serialization/Deserialization") {
    using ValueType       = std::int16_t;
    using InputType       = Range<ValueType>;
    using TransformerType = NS::Featurizers::NormalizeTransformer<InputType>;

    std::vector<std::double_t> norms({1,2,3});
    auto model = std::make_shared<TransformerType>(norms);

    NS::Archive archive;
    model->save(archive);
    std::vector<unsigned char> vec = archive.commit();

    NS::Archive loader(vec);
    TransformerType modelLoaded(loader);
    CHECK(modelLoaded == *model);
}

TEST_CASE("Serialization Version Error") {
    using ValueType       = std::int16_t;
    using InputType       = Range<ValueType>;

    NS::Archive                             out;

    out.serialize(static_cast<std::uint16_t>(2));
    out.serialize(static_cast<std::uint16_t>(0));

    NS::Archive                             in(out.commit());

    CHECK_THROWS_WITH(
        (NS::Featurizers::NormalizeTransformer<InputType>(in)),
        Catch::Contains("Unsupported archive version")
    );
}
