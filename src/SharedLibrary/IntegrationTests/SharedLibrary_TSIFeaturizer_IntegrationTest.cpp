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

TEST_CASE("End-to-end Median") {
    std::vector<TypeId>                                                     keyIds{ StringId, StringId };
    std::vector<TypeId>                                                     dataIds{ Int32Id, Float32Id, UInt32Id };
    TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *             estimatorHandle(nullptr);
    ErrorInfoHandle *                                                       pErrorInfo(nullptr);
    bool suppressErrors(true);

    REQUIRE(
        TimeSeriesImputerFeaturizer_BinaryArchive_CreateEstimator(
            keyIds.data(),
            keyIds.size(),
            dataIds.data(),
            dataIds.size(),
            Median,
            &suppressErrors,
            &estimatorHandle,
            &pErrorInfo
        )
    );
    REQUIRE(estimatorHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    system_clock::time_point                originalTimePoint(system_clock::from_time_t(time_t(217081624)));

    // Fit
    NS::Archive::ByteArray const            bytes1(
        [&originalTimePoint](void) {
            NS::Archive                         archive;

            NS::Traits<system_clock::time_point>::serialize(archive, originalTimePoint);
            NS::Traits<std::string>::serialize(archive, "Hello");
            NS::Traits<std::string>::serialize(archive, "World");
            NS::Traits<typename NS::Traits<std::int32_t>::nullable_type>::serialize(archive, 18);
            NS::Traits<typename NS::Traits<std::float_t>::nullable_type>::serialize(archive, 2.0f);
            NS::Traits<typename NS::Traits<std::uint32_t>::nullable_type>::serialize(archive, static_cast<std::uint32_t>(123456));

            return archive.commit();
        }()
    );

    BinaryArchiveData                       bad1;

    bad1.pBuffer = bytes1.data();
    bad1.cBuffer = bytes1.size();

    NS::Archive::ByteArray const            bytes2(
        [&originalTimePoint](void) {
            NS::Archive                         archive;

            NS::Traits<system_clock::time_point>::serialize(archive, originalTimePoint + std::chrono::seconds(2));
            NS::Traits<std::string>::serialize(archive, "Hello");
            NS::Traits<std::string>::serialize(archive, "World");
            NS::Traits<typename NS::Traits<std::int32_t>::nullable_type>::serialize(archive, 18);
            NS::Traits<typename NS::Traits<std::float_t>::nullable_type>::serialize(archive, 4.0f);
            NS::Traits<typename NS::Traits<std::uint32_t>::nullable_type>::serialize(archive, static_cast<std::uint32_t>(123456));

            return archive.commit();
        }()
    );

    BinaryArchiveData                       bad2;

    bad2.pBuffer = bytes2.data();
    bad2.cBuffer = bytes2.size();

    // Complete training
    while(true) {
        FitResult                               fitResult;
        TrainingState                           trainingState(0);
        REQUIRE(
            TimeSeriesImputerFeaturizer_BinaryArchive_Fit(
                estimatorHandle,
                bad1,
                &fitResult,
                &pErrorInfo
            )
        );
        REQUIRE(fitResult == Continue);
        REQUIRE(pErrorInfo == nullptr);

        REQUIRE(
            TimeSeriesImputerFeaturizer_BinaryArchive_Fit(
                estimatorHandle,
                bad2,
                &fitResult,
                &pErrorInfo
            )
        );
        REQUIRE(fitResult == Continue);
        REQUIRE(pErrorInfo == nullptr);

        REQUIRE(TimeSeriesImputerFeaturizer_BinaryArchive_OnDataCompleted(estimatorHandle, &pErrorInfo));

        TimeSeriesImputerFeaturizer_BinaryArchive_GetState(estimatorHandle,  &trainingState, &pErrorInfo);

        if(trainingState != Training)
            break;
    }

    TimeSeriesImputerFeaturizer_BinaryArchive_CompleteTraining(estimatorHandle, &pErrorInfo);

    // Create Transformer
    TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *           transformerHandle(nullptr);

    REQUIRE(TimeSeriesImputerFeaturizer_BinaryArchive_CreateTransformerFromEstimator(estimatorHandle, &transformerHandle, &pErrorInfo));
    REQUIRE(transformerHandle != nullptr);
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the Estimator
    REQUIRE(TimeSeriesImputerFeaturizer_BinaryArchive_DestroyEstimator(estimatorHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Transform
    NS::Archive::ByteArray const            bytes3(
        [&originalTimePoint](void) {
            NS::Archive                         archive;

            NS::Traits<system_clock::time_point>::serialize(archive, originalTimePoint);
            NS::Traits<std::string>::serialize(archive, "Hello");
            NS::Traits<std::string>::serialize(archive, "World");
            NS::Traits<typename NS::Traits<std::int32_t>::nullable_type>::serialize(archive, 18);
            NS::Traits<typename NS::Traits<std::float_t>::nullable_type>::serialize(archive, std::nanf("1"));
            NS::Traits<typename NS::Traits<std::uint32_t>::nullable_type>::serialize(archive, static_cast<std::uint32_t>(123456));

            return archive.commit();
        }()
    );

    BinaryArchiveData                       bad3;

    bad3.pBuffer = bytes3.data();
    bad3.cBuffer = bytes3.size();

    BinaryArchiveData *                     pTransformResults(nullptr);
    size_t                                  cNumResults(0);

    REQUIRE(
        TimeSeriesImputerFeaturizer_BinaryArchive_Transform(
            transformerHandle,
            bad3,
            &pTransformResults,
            &cNumResults,
            &pErrorInfo
        )
    );
    REQUIRE(pErrorInfo == nullptr);
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

        REQUIRE(rowAdded == false);
        REQUIRE(timePoint == originalTimePoint);
        REQUIRE(key1 == "Hello");
        REQUIRE(key2 == "World");
        REQUIRE(NS::Traits<decltype(data1)>::IsNull(data1) == false);
        REQUIRE(NS::Traits<decltype(data1)>::GetNullableValue(data1) == 18);
        REQUIRE(NS::Traits<decltype(data2)>::IsNull(data2) == false);
        REQUIRE(NS::Traits<decltype(data2)>::GetNullableValue(data2) == 3.0f);
        REQUIRE(NS::Traits<decltype(data3)>::IsNull(data3) == false);
        REQUIRE(NS::Traits<decltype(data3)>::GetNullableValue(data3) == 123456);


#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
    }

    // Destroy the data
    REQUIRE(TimeSeriesImputerFeaturizer_BinaryArchive_DestroyTransformedData(pTransformResults, cNumResults, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Flush
    pTransformResults = nullptr;
    cNumResults = 0;

    REQUIRE(TimeSeriesImputerFeaturizer_BinaryArchive_Flush(transformerHandle, &pTransformResults, &cNumResults, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
    REQUIRE(pTransformResults == nullptr);
    REQUIRE(cNumResults == 0);

    // Destroy the flush results (even though they are empty)
    REQUIRE(TimeSeriesImputerFeaturizer_BinaryArchive_DestroyTransformedData(pTransformResults, cNumResults, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Create serialized data
    unsigned char const *                   pSavedData(nullptr);
    size_t                                  cSavedData(0);

    REQUIRE(TimeSeriesImputerFeaturizer_BinaryArchive_CreateTransformerSaveData(transformerHandle, &pSavedData, &cSavedData, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
    REQUIRE(pSavedData != nullptr);
    REQUIRE(cSavedData != 0);

    // Destroy the transformer
    REQUIRE(TimeSeriesImputerFeaturizer_BinaryArchive_DestroyTransformer(transformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Create a transformer based on the serialize data
    TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *           otherTransformerHandle(nullptr);

    REQUIRE(TimeSeriesImputerFeaturizer_BinaryArchive_CreateTransformerFromSavedData(pSavedData, cSavedData, &otherTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
    REQUIRE(otherTransformerHandle != nullptr);

    // Destroy the serialized data
    REQUIRE(DestroyTransformerSaveData(pSavedData, cSavedData, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    REQUIRE(
        TimeSeriesImputerFeaturizer_BinaryArchive_Transform(
            otherTransformerHandle,
            bad1,
            &pTransformResults,
            &cNumResults,
            &pErrorInfo
        )
    );

    REQUIRE(pErrorInfo == nullptr);
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

        REQUIRE(rowAdded == false);
        REQUIRE(timePoint == originalTimePoint);
        REQUIRE(key1 == "Hello");
        REQUIRE(key2 == "World");
        REQUIRE(NS::Traits<decltype(data1)>::IsNull(data1) == false);
        REQUIRE(NS::Traits<decltype(data1)>::GetNullableValue(data1) == 18);
        REQUIRE(NS::Traits<decltype(data2)>::IsNull(data2) == false);
        REQUIRE(NS::Traits<decltype(data2)>::GetNullableValue(data2) == 2.0f);
        REQUIRE(NS::Traits<decltype(data3)>::IsNull(data3) == false);
        REQUIRE(NS::Traits<decltype(data3)>::GetNullableValue(data3) == 123456);


#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
    }

    // Destroy the data
    REQUIRE(TimeSeriesImputerFeaturizer_BinaryArchive_DestroyTransformedData(pTransformResults, cNumResults, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);

    // Destroy the transformer
    REQUIRE(TimeSeriesImputerFeaturizer_BinaryArchive_DestroyTransformer(otherTransformerHandle, &pErrorInfo));
    REQUIRE(pErrorInfo == nullptr);
}
