// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"
#include "../MatrixDecompositionEstimator.h"
#include "../../../Traits.h"

namespace NS = Microsoft::Featurizer;

//estimator test
void Estimator_Test(std::vector<std::vector<std::double_t>> const &inputBatches) {

    using MDEstimator                   = NS::Featurizers::Components::MatrixDecompositionEstimator<std::double_t>;
    using MDAnnotationData              = NS::Featurizers::Components::MatrixDecompositionAnnotationData<std::double_t>;

    NS::AnnotationMapsPtr const         pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    MDEstimator                         estimator(pAllColumnAnnotations, 0, MDEstimator::DecompositionMethod::SVD, 3);

    NS::TestHelpers::Train(estimator, inputBatches);

    MDAnnotationData const &            mdAnnotation(estimator.get_annotation_data());

    std::vector<std::vector<std::double_t>> const &                uMat(mdAnnotation.U);
    std::vector<std::vector<std::double_t>> const &                vMat(mdAnnotation.V);
    std::vector<std::double_t>              const &                sMat(mdAnnotation.Sigma);

    std::cout << "U: " << NS::Traits<std::vector<std::vector<std::double_t>>>::ToString(uMat) << std::endl;
    std::cout << "V: " << NS::Traits<std::vector<std::vector<std::double_t>>>::ToString(vMat) << std::endl;
    std::cout << "S: " << NS::Traits<std::vector<std::double_t>>::ToString(sMat) << std::endl;
}


//TestWrapper for Estimator test
void TestWrapper(){
    auto trainingBatches = 	NS::TestHelpers::make_vector<std::vector<std::double_t>>(
        NS::TestHelpers::make_vector<std::double_t>(1.0, 2.0, 3.0, 4.0),
        NS::TestHelpers::make_vector<std::double_t>(5.0, 6.0, 7.0, 8.0),
        NS::TestHelpers::make_vector<std::double_t>(1.0, 3.0, 7.0, 9.0)
    );
    Estimator_Test(trainingBatches);
}

TEST_CASE("print") {
    TestWrapper();
}
