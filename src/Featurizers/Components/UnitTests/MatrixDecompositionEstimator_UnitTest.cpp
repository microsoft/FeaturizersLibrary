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

template<typename dataT, typename DecompositionPolicy>
void Estimator_Test(std::vector<std::vector<dataT>> const &inputBatches,
                       std::vector<dataT> const &sigmaLabel,
                       std::vector<std::vector<dataT>> const &uLabel,
                       std::vector<std::vector<dataT>> const &vLabel) {
    //using SVD                           = NS::Featurizers::Components::Details::SVDTrainingOnlyPolicy<dataT>;

    using MDEstimator                   = NS::Featurizers::Components::MatrixDecompositionEstimator<DecompositionPolicy>;
    using MDAnnotationData              = NS::Featurizers::Components::MatrixDecompositionAnnotationData<dataT>;

    NS::AnnotationMapsPtr const         pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    MDEstimator                         estimator(pAllColumnAnnotations, 0, inputBatches.size());

    NS::TestHelpers::Train(estimator, inputBatches);

    MDAnnotationData const &            mdAnnotation(estimator.get_annotation_data());

    std::vector<std::vector<dataT>> const &                uMat(mdAnnotation.U);
    std::vector<std::vector<dataT>> const &                vMat(mdAnnotation.V);
    std::vector<dataT>              const &                sMat(mdAnnotation.Sigma);

    CHECK(NS::TestHelpers::FuzzyCheck(sMat, sigmaLabel));
    for (size_t rowNum = 0; rowNum < uLabel.size(); ++rowNum)
        CHECK(NS::TestHelpers::FuzzyCheck(uMat[rowNum], uLabel[rowNum]));
    for (size_t rowNum = 0; rowNum < vLabel.size(); ++rowNum)
        CHECK(NS::TestHelpers::FuzzyCheck(vMat[rowNum], vLabel[rowNum]));

    // std::cout << "U: " << NS::Traits<std::vector<std::vector<dataT>>>::ToString(uMat) << std::endl;
    // std::cout << "V: " << NS::Traits<std::vector<std::vector<dataT>>>::ToString(vMat) << std::endl;
    // std::cout << "S: " << NS::Traits<std::vector<dataT>>::ToString(sMat) << std::endl;
}

template<typename dataT>
void TestWrapperSVD(){
    using SVD                           = NS::Featurizers::Components::Details::SVDTrainingOnlyPolicy<dataT>;

    auto trainingBatches = NS::TestHelpers::make_vector<std::vector<dataT>>(
        NS::TestHelpers::make_vector<dataT>( 1.0, 2.0),
        NS::TestHelpers::make_vector<dataT>(-1.0,-2.0),
        NS::TestHelpers::make_vector<dataT>( 1.0,-2.0)
    );
    auto sigmaLabel = NS::TestHelpers::make_vector<dataT>( 3.524830, 1.604859);
    auto uLabel = NS::TestHelpers::make_vector<std::vector<dataT>>(
        NS::TestHelpers::make_vector<dataT>( 0.613937, 0.350830),
        NS::TestHelpers::make_vector<dataT>(-0.613937,-0.350830),
        NS::TestHelpers::make_vector<dataT>(-0.496149, 0.868238)
    );
    auto vLabel = NS::TestHelpers::make_vector<std::vector<dataT>>(
        NS::TestHelpers::make_vector<dataT>( 0.207592, 0.978216),
        NS::TestHelpers::make_vector<dataT>( 0.978216,-0.207592)
    );
    Estimator_Test<dataT, SVD>(trainingBatches, sigmaLabel, uLabel, vLabel);
}

template<typename dataT>
void TestWrapperPCA(){
    using PCA                           = NS::Featurizers::Components::Details::PCATrainingOnlyPolicy<dataT>;

    auto trainingBatches = NS::TestHelpers::make_vector<std::vector<dataT>>(
        NS::TestHelpers::make_vector<dataT>(-1.0, -1.0),
        NS::TestHelpers::make_vector<dataT>(-2.0, -1.0),
        NS::TestHelpers::make_vector<dataT>(-3.0, -2.0),
        NS::TestHelpers::make_vector<dataT>( 1.0,  1.0),
        NS::TestHelpers::make_vector<dataT>( 2.0,  1.0),
        NS::TestHelpers::make_vector<dataT>( 3.0,  2.0)
    );
    auto sigmaLabel = NS::TestHelpers::make_vector<dataT>( 0.302284, 39.697716);
    auto uLabel = NS::TestHelpers::make_vector<std::vector<dataT>>(
        NS::TestHelpers::make_vector<dataT>(-0.544914, 0.838492),
        NS::TestHelpers::make_vector<dataT>( 0.838492, 0.544914)
    );
    auto vLabel = NS::TestHelpers::make_vector<std::vector<dataT>>(
        NS::TestHelpers::make_vector<dataT>(-0.544914, 0.838492),
        NS::TestHelpers::make_vector<dataT>( 0.838492, 0.544914)
    );
    Estimator_Test<dataT, PCA>(trainingBatches, sigmaLabel, uLabel, vLabel);
}

TEST_CASE("Invalid_Annotation") {
    using dataT = std::float_t;
    auto validCharacteristicValue = NS::TestHelpers::make_vector<dataT>(0.0);
    auto validFeatureVector = NS::TestHelpers::make_vector<std::vector<dataT>>(NS::TestHelpers::make_vector<dataT>(0.0));
    auto invalidCharacteristicValue = NS::TestHelpers::make_vector<dataT>();
    auto invalidFeatureVector = NS::TestHelpers::make_vector<std::vector<dataT>>(NS::TestHelpers::make_vector<dataT>());
    CHECK_THROWS_WITH(NS::Featurizers::Components::MatrixDecompositionAnnotationData<dataT>(invalidCharacteristicValue, validFeatureVector, validFeatureVector), "sigma");
    CHECK_THROWS_WITH(NS::Featurizers::Components::MatrixDecompositionAnnotationData<dataT>(validCharacteristicValue, invalidFeatureVector, validFeatureVector), "u");
    CHECK_THROWS_WITH(NS::Featurizers::Components::MatrixDecompositionAnnotationData<dataT>(validCharacteristicValue, validFeatureVector, invalidFeatureVector), "v");
}

TEST_CASE("Invalid_TrainingPolicy") {
    using dataT = std::float_t;
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::SVDTrainingOnlyPolicy<dataT>(0), "numRows");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::PCATrainingOnlyPolicy<dataT>(0), "numRows");
}

TEST_CASE("Eigen_Itegration") {
    TestWrapperSVD<std::float_t>();
    TestWrapperPCA<std::float_t>();
    TestWrapperSVD<std::double_t>();
    TestWrapperPCA<std::double_t>();
}
