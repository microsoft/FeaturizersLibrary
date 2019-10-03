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

//estimator test
template <typename InputT, typename TransformedT>
void Estimator_Test(
    std::vector<std::vector<std::remove_const_t<std::remove_reference_t<InputT>>>> const &inputBatches, 
    bool with_centering,
    std::float_t q_min,
    std::float_t q_max,
    TransformedT median, 
    TransformedT scale
) {
    
    using FitResult                         = typename NS::Estimator::FitResult;
    using Batches                           = std::vector<std::vector<std::remove_const_t<std::remove_reference_t<InputT>>>>;
    using AnnotationMaps                    = std::vector<NS::AnnotationMap>;

    using NormEstimator                     = NS::Featurizers::Components::RobustScalarNormEstimator<InputT, TransformedT, 0>;
    using RSNormAnnotation                  = NS::Featurizers::Components::RobustScalarNormAnnotation<InputT, TransformedT>;

    std::tuple<std::float_t, std::float_t> q_range = std::make_tuple<std::float_t, std::float_t>(std::move(q_min), std::move(q_max));

    NS::AnnotationMapsPtr const     pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NormEstimator                   estimator(pAllColumnAnnotations, with_centering, q_range);


    if(inputBatches.empty() == false) {
        // Train the pipeline
        typename Batches::const_iterator        iter(inputBatches.begin());

        while(true) {
            FitResult const                     result(estimator.fit(iter->data(), iter->size()));

            if(result == FitResult::Complete)
                break;
            else if(result == FitResult::ResetAndContinue)
                iter = inputBatches.begin();
            else if(result == FitResult::Continue) {
                ++iter;

                if(iter == inputBatches.end()) {
                    if(estimator.complete_training() == FitResult::Complete)
                        break;

                    iter = inputBatches.begin();
                }
            }
        }
    }
    
    AnnotationMaps const &                          maps(estimator.get_column_annotations());
      
    NS::AnnotationMap const &                       annotations(maps[0]);
    NS::AnnotationMap::const_iterator const &       iterAnnotations(annotations.find("RobustScalarNormEstimator"));
    NS::Annotation const &                          annotation(*iterAnnotations->second[0]);
    RSNormAnnotation const &                        normAnnotation(static_cast<NS::Featurizers::Components::RobustScalarNormAnnotation<InputT, TransformedT> const &>(annotation));
        
    TransformedT const &                            _median(normAnnotation.Median);
    TransformedT const &                            _scale(normAnnotation.Scale);

    TransformedT epsilon = static_cast<TransformedT>(0.000001);

    CHECK(abs(_median - median) < epsilon);
    CHECK(abs(_scale - scale) < epsilon);
}


//TestWrapper for Estimator test
template<typename InputT, typename TransformedT>
void TestWrapper_NormEstimator(){
    auto trainingBatches = 	make_vector<std::vector<InputT>>(
        make_vector<InputT>(static_cast<InputT>(1)),
        make_vector<InputT>(static_cast<InputT>(7)),
        make_vector<InputT>(static_cast<InputT>(5)),
        make_vector<InputT>(static_cast<InputT>(3)),
        make_vector<InputT>(static_cast<InputT>(9))
    );
    Estimator_Test<InputT, TransformedT>(trainingBatches, true, 0, 100, static_cast<TransformedT>(5), static_cast<TransformedT>(8)); 
    Estimator_Test<InputT, TransformedT>(trainingBatches, true, 20, 80, static_cast<TransformedT>(5), static_cast<TransformedT>(4.8)); 
    Estimator_Test<InputT, TransformedT>(trainingBatches, true, 25, 75, static_cast<TransformedT>(5), static_cast<TransformedT>(4));
    Estimator_Test<InputT, TransformedT>(trainingBatches, true, 35, 65, static_cast<TransformedT>(5), static_cast<TransformedT>(2.4));       
    Estimator_Test<InputT, TransformedT>(trainingBatches, false, 25, 75, static_cast<TransformedT>(0), static_cast<TransformedT>(4));       
}

//NormEstimator test
TEST_CASE("RobustScalarNormEstimator - input<int8_t> - output<float_t/double_t>") {
    TestWrapper_NormEstimator<std::int8_t, std::float_t>();
    TestWrapper_NormEstimator<std::int8_t, std::double_t>();
}

TEST_CASE("RobustScalarNormEstimator - input<int16_t> - output<float_t/double_t>") {
    TestWrapper_NormEstimator<std::int16_t, std::float_t>();
    TestWrapper_NormEstimator<std::int16_t, std::double_t>();
}

TEST_CASE("RobustScalarNormEstimator - input<int32_t> - output<float_t/double_t>") {
    TestWrapper_NormEstimator<std::int32_t, std::float_t>();
    TestWrapper_NormEstimator<std::int32_t, std::double_t>();
}

TEST_CASE("RobustScalarNormEstimator - input<int64_t> - output<float_t/double_t>") {
    TestWrapper_NormEstimator<std::int64_t, std::float_t>();
    TestWrapper_NormEstimator<std::int64_t, std::double_t>();
}

TEST_CASE("RobustScalarNormEstimator - input<float_t> - output<float_t/double_t>") {
    TestWrapper_NormEstimator<std::float_t, std::float_t>();
    TestWrapper_NormEstimator<std::float_t, std::double_t>();
}

TEST_CASE("RobustScalarNormEstimator - input<double_t> - output<double_t>") {
    TestWrapper_NormEstimator<std::double_t, std::double_t>();
}
