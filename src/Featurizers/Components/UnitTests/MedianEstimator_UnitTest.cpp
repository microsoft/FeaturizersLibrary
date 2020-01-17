// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../MedianEstimator.h"
#include "../../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

template <bool InterpolateValuesV, typename InputT, typename TransformedT>
void Test(std::vector<InputT> inputs, TransformedT median) {
    // ----------------------------------------------------------------------
    using MedianEstimator                   = NS::Featurizers::Components::MedianEstimator<InputT, TransformedT, InterpolateValuesV>;
    using MedianAnnotationData              = NS::Featurizers::Components::MedianAnnotationData<TransformedT>;
    // ----------------------------------------------------------------------

    NS::AnnotationMapsPtr const             pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    MedianEstimator                         estimator(pAllColumnAnnotations, 0);
    std::vector<std::vector<InputT>>        inputBatches{std::move(inputs)};

    NS::TestHelpers::Train(estimator, inputBatches);

    MedianAnnotationData const &            annotation(estimator.get_annotation_data());

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    CHECK(annotation.Median == median);

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
}

TEST_CASE("ints") {
    Test<true, int>({1, 2, 3, 4, 5}, 3);
    Test<true, int>({1, 2, 3, 4}, 2.5);
    Test<false, int>({1, 2, 3, 4}, 2);
}

TEST_CASE("strings") {
    Test<false, std::string, std::string>({"1", "2", "3", "4", "5"}, "3");
    Test<false, std::string, std::string>({"1", "2", "3", "4"}, "2");
}

TEST_CASE("error conditions") {
    NS::AnnotationMapsPtr const                         pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::MedianEstimator<int>   estimator(pAllColumnAnnotations, 0);

    estimator.begin_training();
    CHECK_THROWS_WITH(estimator.complete_training(), "No elements were provided during training");
}
