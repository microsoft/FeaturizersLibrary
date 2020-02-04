/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */

// Note that most of the shared code is generated for each Featurizer. The
// RobustScalerFeaturizer has additional functionality that is exposed here manually.

#define DLL_EXPORT_COMPILE

#include "SharedLibrary_RobustScalerFeaturizerCustom.h"
#include "SharedLibrary_PointerTable.h"

#include "RobustScalerFeaturizer.h"

#include "Archive.h"

// These method(s) are defined in SharedLibrary_Common.cpp
ErrorInfoHandle * CreateErrorInfo(std::exception const &ex);

// I don't know why MSVC thinks that there is unreachable
// code in these methods during release builds.
#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4702) // Unreachable code
#endif

template <typename InputT, typename TransformedT, typename EstimatorHandleT>
bool RobustScalerFeaturizer_CreateEstimatorWithDefault( /*in*/ bool withCentering, /*out*/ EstimatorHandleT **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        // No validation
        Microsoft::Featurizer::Featurizers::RobustScalerEstimator<InputT, TransformedT>* pEstimator = new Microsoft::Featurizer::Featurizers::RobustScalerEstimator<InputT, TransformedT>(Microsoft::Featurizer::Featurizers::RobustScalerEstimator<InputT, TransformedT>::CreateWithDefaultScaling(std::make_shared<Microsoft::Featurizer::AnnotationMaps>(1), 0, withCentering));
        size_t index(g_pointerTable.Add(pEstimator));

        *ppHandle = reinterpret_cast<EstimatorHandleT*>(index);

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

extern "C" {

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int8_CreateEstimatorWithDefault( /*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_int8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    return RobustScalerFeaturizer_CreateEstimatorWithDefault<std::int8_t, std::float_t>(withCentering, ppHandle, ppErrorInfo);
}

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int16_CreateEstimatorWithDefault( /*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_int16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    return RobustScalerFeaturizer_CreateEstimatorWithDefault<std::int16_t, std::float_t>(withCentering, ppHandle, ppErrorInfo);
}

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint8_CreateEstimatorWithDefault( /*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_uint8_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    return RobustScalerFeaturizer_CreateEstimatorWithDefault<std::uint8_t, std::float_t>(withCentering, ppHandle, ppErrorInfo);
}

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint16_CreateEstimatorWithDefault( /*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_uint16_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    return RobustScalerFeaturizer_CreateEstimatorWithDefault<std::uint16_t, std::float_t>(withCentering, ppHandle, ppErrorInfo);
}

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int32_CreateEstimatorWithDefault( /*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_int32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    return RobustScalerFeaturizer_CreateEstimatorWithDefault<std::int32_t, std::double_t>(withCentering, ppHandle, ppErrorInfo);
}

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint32_CreateEstimatorWithDefault( /*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_uint32_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    return RobustScalerFeaturizer_CreateEstimatorWithDefault<std::uint32_t, std::double_t>(withCentering, ppHandle, ppErrorInfo);
}

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_int64_CreateEstimatorWithDefault( /*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_int64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    return RobustScalerFeaturizer_CreateEstimatorWithDefault<std::int64_t, std::double_t>(withCentering, ppHandle, ppErrorInfo);
}

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_uint64_CreateEstimatorWithDefault( /*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_uint64_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    return RobustScalerFeaturizer_CreateEstimatorWithDefault<std::uint64_t, std::double_t>(withCentering, ppHandle, ppErrorInfo);
}

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_float_CreateEstimatorWithDefault( /*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_float_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    return RobustScalerFeaturizer_CreateEstimatorWithDefault<std::float_t, std::float_t>(withCentering, ppHandle, ppErrorInfo);
}

FEATURIZER_LIBRARY_API bool RobustScalerFeaturizer_double_CreateEstimatorWithDefault( /*in*/ bool withCentering, /*out*/ RobustScalerFeaturizer_double_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    return RobustScalerFeaturizer_CreateEstimatorWithDefault<std::double_t, std::double_t>(withCentering, ppHandle, ppErrorInfo);
}

} // extern "C"
