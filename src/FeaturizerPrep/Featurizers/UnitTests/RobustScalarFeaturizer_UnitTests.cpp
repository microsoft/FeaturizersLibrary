// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../../Featurizers/RobustScalarFeaturizer.h"

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

//integration test
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

template<typename InputT, typename TransformedT>
void TestWrapper_Default_WithCentering(){
    auto trainingBatches = 	make_vector<std::vector<InputT>>(
        make_vector<InputT>(static_cast<InputT>(1)),
        make_vector<InputT>(static_cast<InputT>(7)),
        make_vector<InputT>(static_cast<InputT>(5)),
        make_vector<InputT>(static_cast<InputT>(3)),
        make_vector<InputT>(static_cast<InputT>(9))
    );

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

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));


    CHECK(
        FuzzyCheck(
            Test(
                NS::Featurizers::RobustScalarEstimator<InputT, TransformedT>::CreateWithDefaultScaling(pAllColumnAnnotations, true),
                trainingBatches,
                inferencingInput
            ), 
            inferencingOutput
        )
    );
}

template<typename InputT, typename TransformedT>
void TestWrapper_Default_NoCentering(){
    auto trainingBatches = 	make_vector<std::vector<InputT>>(
        make_vector<InputT>(static_cast<InputT>(1)),
        make_vector<InputT>(static_cast<InputT>(7)),
        make_vector<InputT>(static_cast<InputT>(5)),
        make_vector<InputT>(static_cast<InputT>(3)),
        make_vector<InputT>(static_cast<InputT>(9))
    );

    auto inferencingInput = make_vector<InputT>(
        static_cast<InputT>(1),
        static_cast<InputT>(3),
        static_cast<InputT>(5),
        static_cast<InputT>(7),
        static_cast<InputT>(9)
    );

    auto inferencingOutput = make_vector<TransformedT>(
        static_cast<TransformedT>(1.0/4.0),
        static_cast<TransformedT>(3.0/4.0),
        static_cast<TransformedT>(5.0/4.0),
        static_cast<TransformedT>(7.0/4.0),
        static_cast<TransformedT>(9.0/4.0)
    );

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));


    CHECK(
        FuzzyCheck(
            Test(
                NS::Featurizers::RobustScalarEstimator<InputT, TransformedT>::CreateWithDefaultScaling(pAllColumnAnnotations, false),
                trainingBatches,
                inferencingInput
            ), 
            inferencingOutput
        )
    );
}

template<typename InputT, typename TransformedT>
void TestWrapper_WithCentering_NoScaling(){
    auto trainingBatches = 	make_vector<std::vector<InputT>>(
        make_vector<InputT>(static_cast<InputT>(1)),
        make_vector<InputT>(static_cast<InputT>(7)),
        make_vector<InputT>(static_cast<InputT>(5)),
        make_vector<InputT>(static_cast<InputT>(3)),
        make_vector<InputT>(static_cast<InputT>(9))
    );

    auto inferencingInput = make_vector<InputT>(
        static_cast<InputT>(1),
        static_cast<InputT>(3),
        static_cast<InputT>(5),
        static_cast<InputT>(7),
        static_cast<InputT>(9)
    );

    auto inferencingOutput = make_vector<TransformedT>(
        static_cast<TransformedT>(-4),
        static_cast<TransformedT>(-2),
        static_cast<TransformedT>(0),
        static_cast<TransformedT>(2),
        static_cast<TransformedT>(4)
    );

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    CHECK(
        FuzzyCheck(
            Test(
                NS::Featurizers::RobustScalarEstimator<InputT, TransformedT>(pAllColumnAnnotations, true),
                trainingBatches,
                inferencingInput
            ), 
            inferencingOutput
        )
    );
}

template<typename InputT, typename TransformedT>
void TestWrapper_WithCentering_CustomScaling(std::float_t q_min, std::float_t q_max){
    auto trainingBatches = 	make_vector<std::vector<InputT>>(
        make_vector<InputT>(static_cast<InputT>(1)),
        make_vector<InputT>(static_cast<InputT>(7)),
        make_vector<InputT>(static_cast<InputT>(5)),
        make_vector<InputT>(static_cast<InputT>(3)),
        make_vector<InputT>(static_cast<InputT>(9))
    );

    auto inferencingInput = make_vector<InputT>(
        static_cast<InputT>(1),
        static_cast<InputT>(3),
        static_cast<InputT>(5),
        static_cast<InputT>(7),
        static_cast<InputT>(9)
    );

    auto inferencingOutput = make_vector<TransformedT>(
        static_cast<TransformedT>(static_cast<std::float_t>(-50.0) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>(-25.0) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>(  0.0) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>( 25.0) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>( 50.0) / (q_max - q_min))
    );

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    std::tuple<std::float_t, std::float_t> q_range = std::make_tuple<std::float_t, std::float_t>(std::move(q_min), std::move(q_max));

    CHECK(
        FuzzyCheck(
            Test(
                NS::Featurizers::RobustScalarEstimator<InputT, TransformedT>(pAllColumnAnnotations, true, q_range),
                trainingBatches,
                inferencingInput
            ), 
            inferencingOutput
        )
    );
}

template<typename InputT, typename TransformedT>
void TestWrapper_NoCentering_CustomScaling(std::float_t q_min, std::float_t q_max){
    auto trainingBatches = 	make_vector<std::vector<InputT>>(
        make_vector<InputT>(static_cast<InputT>(1)),
        make_vector<InputT>(static_cast<InputT>(7)),
        make_vector<InputT>(static_cast<InputT>(5)),
        make_vector<InputT>(static_cast<InputT>(3)),
        make_vector<InputT>(static_cast<InputT>(9))
    );

    auto inferencingInput = make_vector<InputT>(
        static_cast<InputT>(1),
        static_cast<InputT>(3),
        static_cast<InputT>(5),
        static_cast<InputT>(7),
        static_cast<InputT>(9)
    );

    auto inferencingOutput = make_vector<TransformedT>(
        static_cast<TransformedT>(static_cast<std::float_t>( 12.5) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>( 37.5) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>( 62.5) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>( 87.5) / (q_max - q_min)),
        static_cast<TransformedT>(static_cast<std::float_t>(112.5) / (q_max - q_min))
    );

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));

    std::tuple<std::float_t, std::float_t> q_range = std::make_tuple<std::float_t, std::float_t>(std::move(q_min), std::move(q_max));

    CHECK(
        FuzzyCheck(
            Test(
                NS::Featurizers::RobustScalarEstimator<InputT, TransformedT>(pAllColumnAnnotations, false, q_range),
                trainingBatches,
                inferencingInput
            ), 
            inferencingOutput
        )
    );
}

//TestWrapper for Integration test
template<typename InputT, typename TransformedT>
void TestWrapper_Integration_Tests(){
    TestWrapper_Default_WithCentering<InputT, TransformedT>();
    TestWrapper_Default_NoCentering<InputT, TransformedT>();
    TestWrapper_WithCentering_NoScaling<InputT, TransformedT>();
    TestWrapper_WithCentering_CustomScaling<InputT, TransformedT>(0.0, 100.0);
    TestWrapper_WithCentering_CustomScaling<InputT, TransformedT>(20.0, 80.0);
    TestWrapper_WithCentering_CustomScaling<InputT, TransformedT>(35.0, 65.0);
    TestWrapper_NoCentering_CustomScaling<InputT, TransformedT>(0.0, 100.0);
    TestWrapper_NoCentering_CustomScaling<InputT, TransformedT>(20.0, 80.0);
    TestWrapper_NoCentering_CustomScaling<InputT, TransformedT>(35.0, 65.0);
}

//Integration test
TEST_CASE("RobustScalarFeaturizer - input<int8_t> - output<float_t/double_t>") {
    TestWrapper_Integration_Tests<std::int8_t, std::float_t>();
    TestWrapper_Integration_Tests<std::int8_t, std::double_t>();
}

TEST_CASE("RobustScalarFeaturizer - input<float_t> - output<float_t/double_t>") {
    TestWrapper_Integration_Tests<std::float_t, std::float_t>();
    TestWrapper_Integration_Tests<std::float_t, std::double_t>();
}










