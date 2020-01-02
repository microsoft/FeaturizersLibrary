// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../MatrixDecompositionEstimator.h"
#include "../../TestHelpers.h"
#include "../../../Traits.h"

namespace NS = Microsoft::Featurizer;

template<typename dataT>
void SVDEstimator_Test(std::vector<std::vector<dataT>> const &inputBatches) {
    using SVD                           = NS::Featurizers::Components::Details::SVDTrainingOnlyPolicy<dataT>;

    using MDEstimator                   = NS::Featurizers::Components::MatrixDecompositionEstimator<SVD>;
    using MDAnnotationData              = NS::Featurizers::Components::MatrixDecompositionAnnotationData<dataT>;

    NS::AnnotationMapsPtr const         pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    MDEstimator                         estimator(pAllColumnAnnotations, 0, inputBatches.size());

    NS::TestHelpers::Train(estimator, inputBatches);

    MDAnnotationData const &            mdAnnotation(estimator.get_annotation_data());

    std::vector<std::vector<dataT>> const &                uMat(mdAnnotation.U);
    std::vector<std::vector<dataT>> const &                vMat(mdAnnotation.V);
    std::vector<dataT>              const &                sMat(mdAnnotation.Sigma);

    std::cout << "U: " << NS::Traits<std::vector<std::vector<dataT>>>::ToString(uMat) << std::endl;
    std::cout << "V: " << NS::Traits<std::vector<std::vector<dataT>>>::ToString(vMat) << std::endl;
    std::cout << "S: " << NS::Traits<std::vector<dataT>>::ToString(sMat) << std::endl;
}

template<typename dataT>
void PCAEstimator_Test(std::vector<std::vector<dataT>> const &inputBatches) {
    using PCA                           = NS::Featurizers::Components::Details::PCATrainingOnlyPolicy<dataT>;

    using MDEstimator                   = NS::Featurizers::Components::MatrixDecompositionEstimator<PCA>;
    using MDAnnotationData              = NS::Featurizers::Components::MatrixDecompositionAnnotationData<dataT>;

    NS::AnnotationMapsPtr const         pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    MDEstimator                         estimator(pAllColumnAnnotations, 0, inputBatches.size());

    NS::TestHelpers::Train(estimator, inputBatches);

    MDAnnotationData const &            mdAnnotation(estimator.get_annotation_data());

    std::vector<std::vector<dataT>> const &                uMat(mdAnnotation.U);
    std::vector<std::vector<dataT>> const &                vMat(mdAnnotation.V);
    std::vector<dataT>              const &                sMat(mdAnnotation.Sigma);

    std::cout << "U: " << NS::Traits<std::vector<std::vector<dataT>>>::ToString(uMat) << std::endl;
    std::cout << "V: " << NS::Traits<std::vector<std::vector<dataT>>>::ToString(vMat) << std::endl;
    std::cout << "S: " << NS::Traits<std::vector<dataT>>::ToString(sMat) << std::endl;
}

template<typename dataT>
void TestWrapperSVD(){
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<dataT>>(
        NS::TestHelpers::make_vector<dataT>( 1.0, 2.0, 3.0),
        NS::TestHelpers::make_vector<dataT>(-1.0,-2.0,-3.0),
        NS::TestHelpers::make_vector<dataT>( 1.0,-2.0, 3.0)
    );
    SVDEstimator_Test<dataT>(trainingBatches);
}

template<typename dataT>
void TestWrapperPCA(){
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<dataT>>(
        NS::TestHelpers::make_vector<dataT>(-1.0, -1.0),
        NS::TestHelpers::make_vector<dataT>(-2.0, -1.0),
        NS::TestHelpers::make_vector<dataT>(-3.0, -2.0),
        NS::TestHelpers::make_vector<dataT>( 1.0,  1.0),
        NS::TestHelpers::make_vector<dataT>( 2.0,  1.0),
        NS::TestHelpers::make_vector<dataT>( 3.0,  2.0)
    );
    PCAEstimator_Test<dataT>(trainingBatches);
}

// TEST_CASE("Invalid_Annotation") {

// }

// TEST_CASE("Invalid_TrainingPolicy") {
    
// }

TEST_CASE("Eigen_Itegration") {
    TestWrapperSVD<float>();
    TestWrapperPCA<float>();
}
