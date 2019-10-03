// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../../Featurizers/RobustScalarFeaturizer.h"

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

// Fuzzy check is used to check if two vectors<double/float> are same considering precision loss 
template <typename T>
bool FuzzyCheck(std::vector<T> const & vec1, std::vector<T> const & vec2, std::double_t epsilon = 0.000001) {
    assert(vec1.size() == vec2.size());

    size_t vec_size = vec1.size();
    for (size_t idx = 0; idx < vec_size; ++idx) {
        if (abs(vec1[idx] - vec2[idx]) > static_cast<T>(epsilon)) {
            return false;
        }
    }
    return true;
}

//transformer test
template <typename InputT, typename TransformedT>
void Transformer_Test(
    std::vector<std::remove_const_t<std::remove_reference_t<InputT>>> const &data,
    TransformedT median,
    TransformedT scale,
    std::vector<std::remove_const_t<std::remove_reference_t<TransformedT>>> const &label
) {
    using NormEstimator                         = NS::Featurizers::Components::RobustScalarEstimator<InputT, TransformedT>;
    using Transformer                           = typename NormEstimator::Transformer;

    NS::AnnotationMapsPtr const                 pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NormEstimator                               estimator(pAllColumnAnnotations);


    typename NormEstimator::TransformerUniquePtr         pTransformer(std::make_unique<Transformer>(median, scale));

    std::vector<TransformedT>    	            output;

    output.reserve(data.size());

    for(auto const &item : data) {
        output.emplace_back(pTransformer->execute(item));
    }

    CHECK(FuzzyCheck(output, label));
}

//TestWrapper for Transformer test
template<typename InputT, typename TransformedT>
void TestWrapper_Transformer(){
    auto inferencingInput = make_vector<InputT>(
        static_cast<InputT>(1),
        static_cast<InputT>(3),
        static_cast<InputT>(5),
        static_cast<InputT>(7),
        static_cast<InputT>(9)
    );

    auto inferencingOutput = make_vector<TransformedT>(
        static_cast<TransformedT>(-1.0),
        static_cast<TransformedT>(-0.5),
        static_cast<TransformedT>( 0.0),
        static_cast<TransformedT>( 0.5),
        static_cast<TransformedT>( 1.0)
    );
    Transformer_Test<InputT, TransformedT>(inferencingInput, 5, 4, inferencingOutput);
}

//Tranformer test
TEST_CASE("RobustScalarTransformer - input<int8_t> - output<float_t/double_t>") {
    TestWrapper_Transformer<std::int8_t, std::float_t>();
    TestWrapper_Transformer<std::int8_t, std::double_t>();
}

TEST_CASE("RobustScalarTransformer - input<int16_t> - output<float_t/double_t>") {
    TestWrapper_Transformer<std::int16_t, std::float_t>();
    TestWrapper_Transformer<std::int16_t, std::double_t>();
}

TEST_CASE("RobustScalarTransformer - input<int32_t> - output<float_t/double_t>") {
    TestWrapper_Transformer<std::int32_t, std::float_t>();
    TestWrapper_Transformer<std::int32_t, std::double_t>();
}

TEST_CASE("RobustScalarTransformer - input<int64_t> - output<float_t/double_t>") {
    TestWrapper_Transformer<std::int64_t, std::float_t>();
    TestWrapper_Transformer<std::int64_t, std::double_t>();
}

TEST_CASE("RobustScalarTransformer - input<float_t> - output<float_t/double_t>") {
    TestWrapper_Transformer<std::float_t, std::float_t>();
    TestWrapper_Transformer<std::float_t, std::double_t>();
}

TEST_CASE("RobustScalarTransformer - input<double_t> - output<float_t/double_t>") {
    TestWrapper_Transformer<std::double_t, std::double_t>();
}
