// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../../Featurizers/MaxAbsScalarFeaturizer.h"
#include "../../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

//estimator test
template <typename InputT, typename TransformedT>
void Estimator_Test(
    std::vector<std::vector<std::remove_const_t<std::remove_reference_t<InputT>>>> const &inputBatches, 
    TransformedT scale
) {
    
    using FitResult                         = typename NS::Estimator::FitResult;
    using Batches                           = std::vector<std::vector<std::remove_const_t<std::remove_reference_t<InputT>>>>;
    using AnnotationMaps                    = std::vector<NS::AnnotationMap>;

    using ScaleEstimator                    = NS::Featurizers::Components::MaxAbsValueEstimator<InputT, TransformedT, 0>;
    using MASAnnotation                     = NS::Featurizers::Components::MaxAbsValueAnnotation<InputT, TransformedT>;

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    ScaleEstimator                          estimator(pAllColumnAnnotations);


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
    NS::AnnotationMap::const_iterator const &       iterAnnotations(annotations.find("MaxAbsValueEstimator"));
    NS::Annotation const &                          annotation(*iterAnnotations->second[0]);
    MASAnnotation const &                           scaleAnnotation(static_cast<NS::Featurizers::Components::MaxAbsValueAnnotation<InputT, TransformedT> const &>(annotation));
        
    TransformedT const &                            _scale(scaleAnnotation.MaxAbsVal);

    TransformedT epsilon = static_cast<TransformedT>(0.000001);

    CHECK(abs(_scale - scale) < epsilon);
}


//TestWrapper for Estimator test
template<typename InputT, typename TransformedT>
void TestWrapper_ScaleEstimator(){
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<InputT>>(
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(-1)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>( 7)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(-5)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>( 3)),
        NS::TestHelpers::make_vector<InputT>(static_cast<InputT>(-9))
    );
    Estimator_Test<InputT, TransformedT>(trainingBatches, static_cast<TransformedT>(9)); 
}

//NormEstimator test
TEST_CASE("MaxAbsValueEstimator - input<int8_t> - output<float_t/double_t>") {
    TestWrapper_ScaleEstimator<std::int8_t, std::float_t>();
    TestWrapper_ScaleEstimator<std::int8_t, std::double_t>();
}

TEST_CASE("MaxAbsValueEstimator - input<int16_t> - output<float_t/double_t>") {
    TestWrapper_ScaleEstimator<std::int16_t, std::float_t>();
    TestWrapper_ScaleEstimator<std::int16_t, std::double_t>();
}

TEST_CASE("MaxAbsValueEstimator - input<int32_t> - output<float_t/double_t>") {
    TestWrapper_ScaleEstimator<std::int32_t, std::float_t>();
    TestWrapper_ScaleEstimator<std::int32_t, std::double_t>();
}

TEST_CASE("MaxAbsValueEstimator - input<int64_t> - output<float_t/double_t>") {
    TestWrapper_ScaleEstimator<std::int64_t, std::float_t>();
    TestWrapper_ScaleEstimator<std::int64_t, std::double_t>();
}

TEST_CASE("MaxAbsValueEstimator - input<float_t> - output<float_t/double_t>") {
    TestWrapper_ScaleEstimator<std::float_t, std::float_t>();
    TestWrapper_ScaleEstimator<std::float_t, std::double_t>();
}

TEST_CASE("MaxAbsValueEstimator - input<double_t> - output<double_t>") {
    TestWrapper_ScaleEstimator<std::double_t, std::double_t>();
}
