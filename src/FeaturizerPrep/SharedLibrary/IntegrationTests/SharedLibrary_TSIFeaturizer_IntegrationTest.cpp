// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "SharedLibrary_TimeSeriesImputerFeaturizer.h"

#include "../../Archive.h"
#include "../../Traits.h"

#include <chrono>

namespace NS = Microsoft::Featurizer;
using system_clock                          = std::chrono::system_clock;

TEST_CASE("End-to-end") {
    std::vector<TypeId>                                                     keyIds{ StringId, StringId };
    std::vector<TypeId>                                                     dataIds{ Int32Id, Float32Id, UInt32Id};
    TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *             estimatorHandle(nullptr);
    ErrorInfoHandle *                                                       pErrorInfo(nullptr);
    bool suppressErrors(false);

    CHECK(
        TimeSeriesImputerFeaturizer_BinaryArchive_CreateEstimator(
            keyIds.data(),
            keyIds.size(),
            dataIds.data(),
            dataIds.size(),
            Forward,
            &suppressErrors,
            &estimatorHandle,
            &pErrorInfo
        )
    );
    CHECK(estimatorHandle != nullptr);
    CHECK(pErrorInfo == nullptr);

    // Fit
    NS::Archive::ByteArray const            bytes(
        [](void) {
            NS::Archive                         archive;

            NS::Traits<system_clock::time_point>::serialize(archive, system_clock::from_time_t(time_t(217081624)));
            NS::Traits<std::string>::serialize(archive, "Hello");
            NS::Traits<std::string>::serialize(archive, "World");
            NS::Traits<typename NS::Traits<std::int32_t>::nullable_type>::serialize(archive, 18);
            NS::Traits<typename NS::Traits<std::float_t>::nullable_type>::serialize(archive, 2.0f);
            NS::Traits<typename NS::Traits<std::uint32_t>::nullable_type>::serialize(archive, static_cast<std::uint32_t>(123456));

            return archive.commit();
        }()
    );

    BinaryArchiveData                       data;

    data.pBuffer = bytes.data();
    data.cBuffer = bytes.size();

    FitResult                               fitResult;

    CHECK(
        TimeSeriesImputerFeaturizer_BinaryArchive_Fit(
            estimatorHandle,
            data,
            &fitResult,
            &pErrorInfo
        )
    );
    CHECK(fitResult == Continue);
    CHECK(pErrorInfo == nullptr);

    // Complete training
    CHECK(TimeSeriesImputerFeaturizer_BinaryArchive_CompleteTraining(estimatorHandle, &fitResult, &pErrorInfo));
    CHECK(fitResult == Complete);
    CHECK(pErrorInfo == nullptr);

    // Create Transformer
    TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *           transformerHandle(nullptr);

    CHECK(TimeSeriesImputerFeaturizer_BinaryArchive_CreateTransformerFromEstimator(estimatorHandle, &transformerHandle, &pErrorInfo));
    CHECK(transformerHandle != nullptr);
    CHECK(pErrorInfo == nullptr);

    // Destroy the Estimator
    CHECK(TimeSeriesImputerFeaturizer_BinaryArchive_DestroyEstimator(estimatorHandle, &pErrorInfo));
    CHECK(pErrorInfo == nullptr);

    // Transform
    BinaryArchiveData *                     pTransformResults(nullptr);
    size_t                                  cNumResults(0);

    CHECK(
        TimeSeriesImputerFeaturizer_BinaryArchive_Transform(
            transformerHandle,
            data,
            &pTransformResults,
            &cNumResults,
            &pErrorInfo
        )
    );
    CHECK(pErrorInfo == nullptr);
    REQUIRE(pTransformResults != nullptr);
    REQUIRE(cNumResults != 0);

    // Deserialize the data
    REQUIRE(cNumResults == 1);

    {
        NS::Archive                         archive(pTransformResults->pBuffer, pTransformResults->cBuffer);

        bool const                                                          rowAdded(NS::Traits<bool>::deserialize(archive));
        system_clock::time_point const                                      timePoint(NS::Traits<system_clock::time_point>::deserialize(archive));
        std::string const                                                   key1(NS::Traits<std::string>::deserialize(archive));
        std::string const                                                   key2(NS::Traits<std::string>::deserialize(archive));
        typename NS::Traits<int32_t>::nullable_type const                   data1(NS::Traits<typename NS::Traits<int32_t>::nullable_type>::deserialize(archive));
        typename NS::Traits<float_t>::nullable_type const                   data2(NS::Traits<typename NS::Traits<float_t>::nullable_type>::deserialize(archive));
        typename NS::Traits<uint32_t>::nullable_type const                  data3(NS::Traits<typename NS::Traits<uint32_t>::nullable_type>::deserialize(archive));

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

        CHECK(rowAdded == false);
        CHECK(key1 == "Hello");
        CHECK(key2 == "World");
        REQUIRE(NS::Traits<decltype(data1)>::IsNull(data1) == false);
        CHECK(NS::Traits<decltype(data1)>::GetNullableValue(data1) == 18);
        REQUIRE(NS::Traits<decltype(data2)>::IsNull(data2) == false);
        CHECK(NS::Traits<decltype(data2)>::GetNullableValue(data2) == 2.0f);
        REQUIRE(NS::Traits<decltype(data3)>::IsNull(data3) == false);
        CHECK(NS::Traits<decltype(data3)>::GetNullableValue(data3) == 123456);

        std::ignore = timePoint; // BugBug

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
    }

    // Destroy the data
    CHECK(TimeSeriesImputerFeaturizer_BinaryArchive_DestroyTransformedData(pTransformResults, cNumResults, &pErrorInfo));
    CHECK(pErrorInfo == nullptr);

    // Destroy the transformer
    CHECK(TimeSeriesImputerFeaturizer_BinaryArchive_DestroyTransformer(transformerHandle, &pErrorInfo));
    CHECK(pErrorInfo == nullptr);
}
