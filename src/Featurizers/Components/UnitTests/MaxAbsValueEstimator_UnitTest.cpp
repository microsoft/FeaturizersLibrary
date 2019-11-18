// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../MaxAbsValueEstimator.h"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"

namespace NS = Microsoft::Featurizer;

//estimator test
template <typename TransformedT, typename InputT>
TransformedT FindMax(std::vector<std::vector<InputT>> const &inputBatches) {
    NS::AnnotationMapsPtr const                                                     pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::MaxAbsValueEstimator<InputT, TransformedT>         estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, inputBatches);

    NS::Featurizers::Components::MaxAbsValueAnnotationData<TransformedT> const &    annotation(estimator.get_annotation_data());

    return annotation.Value;
}

TEST_CASE("Invalid Annotation") {
    CHECK_THROWS_WITH(NS::Featurizers::Components::MaxAbsValueAnnotationData<unsigned char>(-1), "maxAbsValue");
    CHECK_THROWS_WITH(NS::Featurizers::Components::MaxAbsValueAnnotationData<unsigned char>(10000), "maxAbsValue overflow");
}

TEST_CASE("Standard Tests") {
    CHECK(FindMax<std::uint32_t>(NS::TestHelpers::make_vector<std::vector<std::int32_t>>(NS::TestHelpers::make_vector<std::int32_t>(10, 3, 4))) == 10);
    CHECK(FindMax<std::uint32_t>(NS::TestHelpers::make_vector<std::vector<std::int32_t>>(NS::TestHelpers::make_vector<std::int32_t>(10, 3, 4, -12))) == 12);
}
