// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../Shared/optional.h"
#include "../../Featurizers/CatImputerFeaturizer.h"

namespace NS = Microsoft::Featurizer;
namespace {

template <typename T, typename ArgT>
void make_vector(std::vector<T> & v, ArgT && arg) {
    v.emplace_back(std::forward<ArgT>(arg));
}

template <typename T, typename ArgT, typename... ArgsT>
void make_vector(std::vector<T> &v, ArgT && arg, ArgsT &&...args) {
    make_vector(v, std::forward<ArgT>(arg));
    make_vector(v, std::forward<ArgsT>(args)...);
}

} // anonymous namespace

template <typename T, typename... ArgsT>
std::vector<T> make_vector(ArgsT &&... args) {
    std::vector<T>                          result;

    result.reserve(sizeof...(ArgsT));

    make_vector(result, std::forward<ArgsT>(args)...);
    return result;
}

template <typename T>
std::vector<T> make_vector(void) {
    return std::vector<T>();
}

template <typename PipelineT>
std::vector<typename PipelineT::TransformedType> Test(
    PipelineT pipeline,
    std::vector<std::vector<std::remove_const_t<std::remove_reference_t<typename PipelineT::InputType>>>> const &inputBatches,
    std::vector<std::remove_const_t<std::remove_reference_t<typename PipelineT::InputType>>> const &data
) {
    using FitResult                         = typename NS::Estimator::FitResult;
    using Batches                           = std::vector<std::vector<std::remove_const_t<std::remove_reference_t<typename PipelineT::InputType>>>>;

    if(inputBatches.empty() == false) {
        // Train the pipeline
        typename Batches::const_iterator        iter(inputBatches.begin());

        while(true) {
            FitResult const                     result(pipeline.fit(iter->data(), iter->size()));

            if(result == FitResult::Complete)
                break;
            else if(result == FitResult::ResetAndContinue)
                iter = inputBatches.begin();
            else if(result == FitResult::Continue) {
                ++iter;

                if(iter == inputBatches.end()) {
                    if(pipeline.complete_training() == FitResult::Complete)
                        break;

                    iter = inputBatches.begin();
                }
            }
        }
    }

    assert(pipeline.is_training_complete());

    typename PipelineT::TransformerUniquePtr                  pTransformer(pipeline.create_transformer());
    std::vector<typename PipelineT::TransformedType>    	  output;

    output.reserve(data.size());

    for(auto const &item : data)
        output.emplace_back(pTransformer->execute(item));

    return output;
}

template<typename transformedType, typename castType = uint8_t>
void NumericTestWrapper(){
    using inputType = typename NS::Traits<transformedType>::nullable_type;

    inputType null = NS::Traits<transformedType>::CreateNullValue();

    // Passing int values to make_vector for an optional type gives following error
    // error: implicit conversion loses integer precision: 'int' to 'nonstd::optional_lite::
    // Hence explicit cast to uint8_t.
    auto trainingBatches = 	make_vector<std::vector<inputType>>(
                make_vector<inputType>(static_cast<castType>(10),static_cast<castType>(20),null),
                make_vector<inputType>(static_cast<castType>(10),static_cast<castType>(30),null),
                make_vector<inputType>(static_cast<castType>(10),static_cast<castType>(10),null),
                make_vector<inputType>(static_cast<castType>(11),static_cast<castType>(15),null),
                make_vector<inputType>(static_cast<castType>(18),static_cast<castType>(8),null));

    auto inferencingInput = make_vector<inputType>(static_cast<castType>(5),static_cast<castType>(8),static_cast<castType>(20)
                ,null,null,null,null);

    auto inferencingOutput = make_vector<transformedType>(5,8,20,10,10,10,10);

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        Test(
            NS::CatImputerEstimator<transformedType>(pAllColumnAnnotations),
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

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        Test(
            NS::CatImputerEstimator<transformedType>(pAllColumnAnnotations),
            make_vector<std::vector<type>>(
                make_vector<type>("one", "one", "one",type{},type{},"two", "three")
            ),
            make_vector<type>("one", "two", "three",type{})
        ) == make_vector<transformedType>("one","two","three","one")
    );
}

TEST_CASE("CatImputer- All values Null") {
    using type = nonstd::optional<std::int64_t>;
    using transformedType = std::int64_t;

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK_THROWS_WITH(Test(
            NS::CatImputerEstimator<transformedType>(pAllColumnAnnotations),
            make_vector<std::vector<type>>(
                make_vector<type>(type{},type{},type{},type{},type{},type{})),
                make_vector<type>(5, 8, 20,type{}))
                , Catch::Contains("All null values or empty training set."));
}

TEST_CASE("Serialization/Deserialization- Numeric") {
    using type = nonstd::optional<std::int64_t>;
    using transformedType = std::int64_t;
    using transformerType = NS::HistogramConsumerEstimator<type,transformedType>::Transformer;
    auto model = std::make_shared<transformerType>(10);

    NS::Archive archive;
    model->save(archive);
    std::vector<unsigned char> vec = archive.commit();
    CHECK(vec.size() == 9);

    NS::Archive loader(vec);
    transformerType modelLoaded(loader);
    CHECK(modelLoaded.get_most_frequent_value() == 10);
}

TEST_CASE("Serialization/Deserialization- string") {
    using type = nonstd::optional<std::string>;
    using transformedType = std::string;
    using transformerType = NS::HistogramConsumerEstimator<type,transformedType>::Transformer;
    auto model = std::make_shared<transformerType>("one");

    NS::Archive archive;
    model->save(archive);
    std::vector<unsigned char> vec = archive.commit();

    NS::Archive loader(vec);
    transformerType modelLoaded(loader);
    CHECK(modelLoaded.get_most_frequent_value() == "one");

}




