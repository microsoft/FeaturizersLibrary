/* ---------------------------------------------------------------------- */
/* Copyright (c) Microsoft Corporation. All rights reserved.              */
/* Licensed under the MIT License                                         */
/* ---------------------------------------------------------------------- */

// Note that most of the shared code is generated for each Featurizer. The
// TimeSeriesImputer is more complex than the other Featurizers, so this one
// is written by hand for now.

#define DLL_EXPORT_COMPILE

#include "SharedLibrary_TimeSeriesImputerFeaturizer.h"
#include "SharedLibrary_PointerTable.h"

#include "Archive.h"
#include "TimeSeriesImputerFeaturizer.h"

#include <cstring> // for memcpy

// These method(s) are defined in SharedLibrary_Common.cpp
ErrorInfoHandle * CreateErrorInfo(std::exception const &ex);

/* ---------------------------------------------------------------------- */
/* |                                                                      */
/* |  TimeSeriesImputerFeaturizer <BinaryArchive> */
/* |                                                                      */
/* ---------------------------------------------------------------------- */
using time_point                            = std::chrono::system_clock::time_point;
using Strings                               = std::vector<std::string>;
using OptionalString                        = nonstd::optional<std::string>;
using OptionalStrings                       = std::vector<OptionalString>;
using InputTuple                            = std::tuple<time_point, Strings, OptionalStrings>;
using TransformedTuple                      = std::tuple<bool, time_point, Strings, OptionalStrings>;
using TransformedTuples                     = std::vector<TransformedTuple>;

/////////////////////////////////////////////////////////////////////////
///  \class         Serializer
///  \brief         Object that is able to deserialize Input and serialize
///                 Transformed data according to the provided column types.
///
class Serializer {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TypeIds                           = std::vector<Microsoft::Featurizer::TypeId>;
    using Bytes                             = std::vector<unsigned char>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    TypeIds const                           KeyTypes;
    TypeIds const                           DataTypes;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    Serializer(TypeIds keyTypes, TypeIds dataTypes);
    Serializer(Microsoft::Featurizer::Archive &ar);

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Serializer);

    Microsoft::Featurizer::Archive & save(Microsoft::Featurizer::Archive &ar) const;

    InputTuple Deserialize(unsigned char const *pBuffer, size_t cbBuffer) const;
    std::tuple<BinaryArchiveData *, size_t> Serialize(TransformedTuples const &values) const;

    static void DestroySerializedData(BinaryArchiveData const *pData, size_t numDataElements);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    struct PrivateConstructorTag {};

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    Serializer(TypeIds keyTypes, TypeIds dataTypes, PrivateConstructorTag);

    Strings _LoadKeyStrings(Microsoft::Featurizer::Archive &ar) const;
    OptionalStrings _LoadDataStrings(Microsoft::Featurizer::Archive &ar) const;

    void _SaveKeyStrings(Microsoft::Featurizer::Archive &ar, Strings const &strings) const;
    void _SaveDataStrings(Microsoft::Featurizer::Archive &ar, OptionalStrings const &strings) const;
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorMemory
///  \brief         Memory used when interacting with an Estimator.
///
struct EstimatorMemory {
    using SerializerType                    = Serializer;

    SerializerType                                                          EstimatorSerializer;
    Microsoft::Featurizer::Featurizers::TimeSeriesImputerEstimator          Estimator;

    EstimatorMemory(SerializerType serializer, Microsoft::Featurizer::Featurizers::TimeSeriesImputerEstimator estimator);

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(EstimatorMemory);
};

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerMemory
///  \brief         Memory used when interacting with a Transformer.
///
struct TransformerMemory {
    using SerializerType                    = Serializer;
    using TransformerUniquePtr              = Microsoft::Featurizer::Featurizers::TimeSeriesImputerEstimator::TransformerUniquePtr;

    SerializerType                          TransformerSerializer;
    TransformerUniquePtr                    Transformer;

    TransformerMemory(SerializerType serializer, TransformerUniquePtr pTransformer);
    TransformerMemory(Microsoft::Featurizer::Archive &ar);

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TransformerMemory);

    Microsoft::Featurizer::Archive & save(Microsoft::Featurizer::Archive &ar);
};

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
extern "C" {

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_CreateEstimator(/*in*/ TypeId *pKeyColTypes, /*in*/ std::size_t numKeyColTypes, /*in*/ TypeId *pDataColTypes, /*in*/ std::size_t numDataColTypes, /*in*/ ImputationStrategy strategy, /*in*/ bool *pSuppressErrors, /*out*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle **ppHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pKeyColTypes == nullptr) throw std::invalid_argument("'pKeyColTypes' is null");
        if(numKeyColTypes == 0) throw std::invalid_argument("'numKeyColTypes' is 0");
        if(pDataColTypes == nullptr) throw std::invalid_argument("'pDataColTypes' is null");
        if(numDataColTypes == 0) throw std::invalid_argument("'numDataColTypes' is 0");
        if(Microsoft::Featurizer::Featurizers::Components::IsValid(static_cast<Microsoft::Featurizer::Featurizers::Components::TimeSeriesImputeStrategy>(strategy)) == false) throw std::invalid_argument("'strategy' is not valid");

        auto const                          createTypeIds(
            [](TypeId *ptr, size_t numTypeIds) {
                Serializer::TypeIds         results;

                results.reserve(numTypeIds);

                TypeId const * const        pEnd(ptr + numTypeIds);

                while(ptr != pEnd)
                    results.emplace_back(static_cast<Microsoft::Featurizer::TypeId>(*ptr++));

                return results;
            }
        );

        Serializer::TypeIds                 colTypeIds(createTypeIds(pDataColTypes, numDataColTypes));
        std::unique_ptr<EstimatorMemory>    pMemory(
            new EstimatorMemory(
                Serializer(createTypeIds(pKeyColTypes, numKeyColTypes), colTypeIds),
                Microsoft::Featurizer::Featurizers::TimeSeriesImputerEstimator(
                    // We want to have an annotation map for each output column. Given our output type,
                    // the number of columns is:
                    //
                    //      <bool, time_point,   KeyStrings,        DataStrings>
                    //        1  +     1     +   numKeyColTypes +   numDataColTypes
                    //             2         +   numKeyColTypes +   numDataColTypes
                    //
                    // Note that numKeyColTypes/numDataColTypes is the buffer size of the type data
                    // rather than the actual number of values (this is because some values may have multiple
                    // typeids). This isn't a problem now because we are hard-coding optional for all data
                    // col types. This code will need to be revisited if this behavior changes in the future.
                    std::make_shared<Microsoft::Featurizer::AnnotationMaps>(2 + numKeyColTypes + numDataColTypes),

                    colTypeIds,
                    pSuppressErrors ? *pSuppressErrors : false,
                    static_cast<Microsoft::Featurizer::Featurizers::Components::TimeSeriesImputeStrategy>(strategy)
                )
            )
        );

        pMemory->Estimator.begin_training();

        size_t                              index(g_pointerTable.Add(pMemory.get()));

        *ppHandle = reinterpret_cast<TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *>(index);

        // If here, we are ready to commit the results
        pMemory.release();

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_DestroyEstimator(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t                              index(reinterpret_cast<size_t>(pHandle));
        EstimatorMemory *                   pEstimatorMemory(g_pointerTable.Get<EstimatorMemory>(index));

        g_pointerTable.Remove(index);
        delete pEstimatorMemory;

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_IsTrainingComplete(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pHandle, /*out*/ bool *pIsTrainingComplete, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pIsTrainingComplete == nullptr) throw std::invalid_argument("'pIsTrainingComplete' is null");

        EstimatorMemory const &             memory(*g_pointerTable.Get<EstimatorMemory>(reinterpret_cast<size_t>(pHandle)));

        *pIsTrainingComplete = memory.Estimator.get_state() != Microsoft::Featurizer::TrainingState::Training;

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_Fit(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pHandle, /*in*/ BinaryArchiveData data, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(data.pBuffer == nullptr) throw std::invalid_argument("'data' buffer is null");
        if(data.cBuffer == 0) throw std::invalid_argument("'data' buffer size is 0");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        EstimatorMemory &                   memory(*g_pointerTable.Get<EstimatorMemory>(reinterpret_cast<size_t>(pHandle)));

        *pFitResult = static_cast<unsigned char>(memory.Estimator.fit(memory.EstimatorSerializer.Deserialize(data.pBuffer, data.cBuffer)));

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_FitBuffer(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pHandle, /*in*/ BinaryArchiveData const *pData, /*in*/ std::size_t numDataElements, /*out*/ FitResult *pFitResult, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(pData == nullptr) throw std::invalid_argument("'pData' is null");
        if(numDataElements == 0) throw std::invalid_argument("'numDataElements' is 0");
        if(pFitResult == nullptr) throw std::invalid_argument("'pFitResult' is null");

        // ----------------------------------------------------------------------
        using InputTuples                   = std::vector<InputTuple>;
        // ----------------------------------------------------------------------

        EstimatorMemory &                   memory(*g_pointerTable.Get<EstimatorMemory>(reinterpret_cast<size_t>(pHandle)));

        InputTuples                         input;

        input.reserve(numDataElements);

        BinaryArchiveData const * const     pEndData(pData + numDataElements);

        while(pData != pEndData) {
            input.emplace_back(memory.EstimatorSerializer.Deserialize(pData->pBuffer, pData->cBuffer));
            ++pData;
        }

        *pFitResult = static_cast<unsigned char>(memory.Estimator.fit(input.data(), input.size()));

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_CompleteTraining(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        EstimatorMemory &                   memory(*g_pointerTable.Get<EstimatorMemory>(reinterpret_cast<size_t>(pHandle)));

        memory.Estimator.complete_training();

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_CreateTransformerFromEstimator(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_EstimatorHandle *pEstimatorHandle, /*out*/ TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pEstimatorHandle == nullptr) throw std::invalid_argument("'pEstimatorHandle' is null");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        EstimatorMemory &                   estimatorMemory(*g_pointerTable.Get<EstimatorMemory>(reinterpret_cast<size_t>(pEstimatorHandle)));
        std::unique_ptr<TransformerMemory>  pTransformerMemory(
            new TransformerMemory(
                std::move(estimatorMemory.EstimatorSerializer),
                estimatorMemory.Estimator.create_transformer()
            )
        );

        size_t                              index(g_pointerTable.Add(pTransformerMemory.get()));

        *ppTransformerHandle = reinterpret_cast<TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *>(index);

        // If here, we are ready to commit the results
        pTransformerMemory.release();

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_CreateTransformerFromSavedData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle **ppTransformerHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");
        if(ppTransformerHandle == nullptr) throw std::invalid_argument("'ppTransformerHandle' is null");

        Microsoft::Featurizer::Archive      archive(pBuffer, cBufferSize);
        std::unique_ptr<TransformerMemory>  pTransformerMemory(new TransformerMemory(archive));
        size_t                              index(g_pointerTable.Add(pTransformerMemory.get()));

        *ppTransformerHandle = reinterpret_cast<TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *>(index);

        // If here, we are ready to commit the results
        pTransformerMemory.release();

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_DestroyTransformer(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *pHandle, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");

        size_t                              index(reinterpret_cast<size_t>(pHandle));
        TransformerMemory *                 pTransformerMemory(g_pointerTable.Get<TransformerMemory>(index));

        g_pointerTable.Remove(index);
        delete pTransformerMemory;

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_CreateTransformerSaveData(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *pHandle, /*out*/ unsigned char const **ppBuffer, /*out*/ std::size_t *pBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppBuffer == nullptr) throw std::invalid_argument("'ppBuffer' is null");
        if(pBufferSize == nullptr) throw std::invalid_argument("'pBufferSize' is null");

        TransformerMemory &                 memory(*g_pointerTable.Get<TransformerMemory>(reinterpret_cast<size_t>(pHandle)));
        Microsoft::Featurizer::Archive      archive;

        memory.save(archive);

        Microsoft::Featurizer::Archive::ByteArray const buffer(archive.commit());

        unsigned char *                     new_buffer(new unsigned char[buffer.size()]);

        std::copy(buffer.begin(), buffer.end(), new_buffer);

        *ppBuffer = new_buffer;
        *pBufferSize = buffer.size();

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_DestroyTransformerSaveData(/*in*/ unsigned char const *pBuffer, /*in*/ std::size_t cBufferSize, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pBuffer == nullptr) throw std::invalid_argument("'pBuffer' is null");
        if(cBufferSize == 0) throw std::invalid_argument("'cBufferSize' is 0");

        delete [] pBuffer;

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_Transform(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *pHandle, /*in*/ BinaryArchiveData data, /*out*/ BinaryArchiveData **ppData, /*out*/ std::size_t *pNumDataElements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(data.pBuffer == nullptr) throw std::invalid_argument("'data' buffer is null");
        if(data.cBuffer == 0) throw std::invalid_argument("'data' buffer size is 0");
        if(ppData == nullptr) throw std::invalid_argument("'ppData' is null");
        if(pNumDataElements == nullptr) throw std::invalid_argument("'pNumDataElements' is null");

        TransformerMemory &                             memory(*g_pointerTable.Get<TransformerMemory>(reinterpret_cast<size_t>(pHandle)));
        TransformedTuples                               results;

        memory.Transformer->execute(
            memory.TransformerSerializer.Deserialize(data.pBuffer, data.cBuffer),
            [&results](typename TransformedTuples::value_type value) {
                results.emplace_back(std::move(value));
            }
        );

        std::tie(*ppData, *pNumDataElements) = memory.TransformerSerializer.Serialize(results);

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_Flush(/*in*/ TimeSeriesImputerFeaturizer_BinaryArchive_TransformerHandle *pHandle, /*out*/ BinaryArchiveData ** ppData, /*out*/ std::size_t *pNumDataElements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        if(pHandle == nullptr) throw std::invalid_argument("'pHandle' is null");
        if(ppData == nullptr) throw std::invalid_argument("'ppData' is null");
        if(pNumDataElements == nullptr) throw std::invalid_argument("'pNumDataElements' is null");

        TransformerMemory &                             memory(*g_pointerTable.Get<TransformerMemory>(reinterpret_cast<size_t>(pHandle)));

        // TODO assert(dynamic_cast<Microsoft::Featurizer::Featurizers::TimeSeriesImputerEstimator::Transformer *>(memory.Transformer.get()));
        // TODO Microsoft::Featurizer::Featurizers::TimeSeriesImputerEstimator::Transformer &   transformer(static_cast<Microsoft::Featurizer::Featurizers::TimeSeriesImputerEstimator::Transformer &>(*memory.Transformer));
        // TODO
        // TODO TransformedTuples                               results(transformer.flush());
        // TODO
        // TODO std::tie(*ppData, *pNumDataElements) = memory.TransformerSerializer.Serialize(results);

        // Temporary workaround
        std::ignore = memory;
        *ppData = nullptr;
        *pNumDataElements = 0;

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

FEATURIZER_LIBRARY_API bool TimeSeriesImputerFeaturizer_BinaryArchive_DestroyTransformedData(/*in*/ BinaryArchiveData const *pData, /*in*/ std::size_t numDataElements, /*out*/ ErrorInfoHandle **ppErrorInfo) {
    if(ppErrorInfo == nullptr)
        return false;

    try {
        *ppErrorInfo = nullptr;

        Serializer::DestroySerializedData(pData, numDataElements);

        return true;
    }
    catch(std::exception const &ex) {
        *ppErrorInfo = CreateErrorInfo(ex);
        return false;
    }
}

} // extern "C"

// ----------------------------------------------------------------------
// |
// |  Serializer
// |
// ----------------------------------------------------------------------
Serializer::Serializer(TypeIds keyTypes, TypeIds dataTypes) :
    Serializer(std::move(keyTypes), std::move(dataTypes), PrivateConstructorTag()) {
}

Serializer::TypeIds DeserializeTypeIds(Microsoft::Featurizer::Archive &ar) {
    // ----------------------------------------------------------------------
    using RawType                           = typename std::underlying_type<Microsoft::Featurizer::TypeId>::type;
    using RawTypes                          = std::vector<RawType>;
    // ----------------------------------------------------------------------

    RawTypes                                rawTypes(Microsoft::Featurizer::Traits<RawTypes>::deserialize(ar));

    std::vector<Microsoft::Featurizer::TypeId>          results;

    results.reserve(rawTypes.size());

    for(auto const & raw : rawTypes)
        results.emplace_back(static_cast<Microsoft::Featurizer::TypeId>(raw));

    return results;
}

Serializer::Serializer(Microsoft::Featurizer::Archive &ar) :
    Serializer(
        [&ar](void) {
            // We need to deserialize these ids in a very specific order, which means that we can't
            // invoke DeserializeTypeIds inline as the order of invocation is not well-defined for
            // parameter values.
            TypeIds                         keyIds(DeserializeTypeIds(ar));
            TypeIds                         dataIds(DeserializeTypeIds(ar));

            return Serializer(std::move(keyIds), std::move(dataIds), PrivateConstructorTag());
        }()
    ) {
}

Microsoft::Featurizer::Archive & Serializer::save(Microsoft::Featurizer::Archive &ar) const {
    auto const                              serialize(
        [&ar](TypeIds const &ids) {
            // ----------------------------------------------------------------------
            using RawType                   = typename std::underlying_type<Microsoft::Featurizer::TypeId>::type;
            using RawTypes                  = std::vector<RawType>;
            // ----------------------------------------------------------------------

            RawTypes                        rawTypes;

            rawTypes.reserve(ids.size());

            for(auto const & id : ids)
                rawTypes.emplace_back(static_cast<RawType>(id));

            Microsoft::Featurizer::Traits<RawTypes>::serialize(ar, rawTypes);
        }
    );

    serialize(KeyTypes);
    serialize(DataTypes);

    return ar;
}

InputTuple Serializer::Deserialize(unsigned char const *pBuffer, size_t cbBuffer) const {
    assert(pBuffer);
    assert(cbBuffer);

    Microsoft::Featurizer::Archive          archive(pBuffer, cbBuffer);
    time_point                              tp(Microsoft::Featurizer::Traits<time_point>::deserialize(archive));
    Strings                                 keyStrings(_LoadKeyStrings(archive));
    OptionalStrings                         dataStrings(_LoadDataStrings(archive));

    return std::make_tuple(std::move(tp), std::move(keyStrings), std::move(dataStrings));
}

std::tuple<BinaryArchiveData *, size_t> Serializer::Serialize(TransformedTuples const &values) const {
    // ----------------------------------------------------------------------
    using namespace Microsoft::Featurizer;

    struct Internal {
        static void ByteArrayDeleter(unsigned char *pData) {
            delete [] pData;
        }

        static void BinaryArchiveDataDeleter(BinaryArchiveData *pData) {
            delete [] pData;
        }
    };

    using ByteArrayUniquePtr                = std::unique_ptr<unsigned char, void (*)(unsigned char *)>;
    using ByteArrayData                     = std::vector<std::pair<ByteArrayUniquePtr, size_t>>;

    using BinaryArchiveDataUniquePtr        = std::unique_ptr<BinaryArchiveData, void (*)(BinaryArchiveData *)>;
    // ----------------------------------------------------------------------

    if(values.empty())
        return std::make_tuple(nullptr, 0);

    // Serialize each row
    ByteArrayData                           individualBuffers;

    individualBuffers.reserve(values.size());

    for(TransformedTuple const & value : values) {
        Archive                             archive;

        Traits<bool>::serialize(archive, std::get<0>(value));
        Traits<time_point>::serialize(archive, std::get<1>(value));

        _SaveKeyStrings(archive, std::get<2>(value));
        _SaveDataStrings(archive, std::get<3>(value));

        Archive::ByteArray                  bytes(archive.commit());
        ByteArrayUniquePtr                  pBytes(new unsigned char[bytes.size()], Internal::ByteArrayDeleter);

        memcpy(pBytes.get(), bytes.data(), bytes.size());

        individualBuffers.emplace_back(std::move(pBytes), bytes.size());
    }

    // Create memory for all pointers and assign the buffers
    BinaryArchiveDataUniquePtr              pArchiveData(new BinaryArchiveData[individualBuffers.size()], Internal::BinaryArchiveDataDeleter);
    BinaryArchiveData *                     pArchiveDataPtr(pArchiveData.get());

    for(auto &data : individualBuffers) {
        pArchiveDataPtr->pBuffer = std::get<0>(data).get();
        pArchiveDataPtr->cBuffer = std::get<1>(data);
        ++pArchiveDataPtr;
    }

    // If here, all memory was successfully allocated and we can release all smart pointers.
    for(auto &data : individualBuffers)
        std::get<0>(data).release();

    BinaryArchiveData * const               pResult(pArchiveData.release());

    return std::make_tuple(pResult, individualBuffers.size());
}

// static
void Serializer::DestroySerializedData(BinaryArchiveData const *pData, size_t numDataElements) {
    if(pData == nullptr && numDataElements != 0) throw std::invalid_argument("Invalid buffer");
    if(pData != nullptr && numDataElements == 0) throw std::invalid_argument("Invalid buffer");

    if(pData == nullptr)
        return;

    BinaryArchiveData const *               ptr(pData);
    BinaryArchiveData const * const         pEnd(pData + numDataElements);

    while(ptr != pEnd) {
        if(ptr->pBuffer == nullptr || ptr->cBuffer == 0) throw std::invalid_argument("Invalid buffer element");

        delete [] ptr->pBuffer;
        ++ptr;
    }

    delete [] pData;
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
Serializer::TypeIds & ValidateTypes(Serializer::TypeIds &ids) {
    if(ids.empty())
        throw std::invalid_argument("Empty TypeIds");

    for(auto const & id : ids) {
        if(IsValid(id) == false)
            throw std::invalid_argument("Invalid TypeId");
    }

    return ids;
}

Serializer::Serializer(TypeIds keyTypes, TypeIds dataTypes, PrivateConstructorTag) :
    KeyTypes(std::move(ValidateTypes(keyTypes))),
    DataTypes(std::move(ValidateTypes(dataTypes))) {
}

Strings Serializer::_LoadKeyStrings(Microsoft::Featurizer::Archive &ar) const {
    // ----------------------------------------------------------------------
    using namespace Microsoft::Featurizer;
    // ----------------------------------------------------------------------

    Strings                                 results;

    results.reserve(KeyTypes.size());

    for(auto const & typeId : KeyTypes) {
        if(typeId == Microsoft::Featurizer::TypeId::String)
            results.emplace_back(Traits<std::string>::deserialize(ar));
        else if(typeId == Microsoft::Featurizer::TypeId::Int8)
            results.emplace_back(Traits<std::int8_t>::ToString(Traits<std::int8_t>::deserialize(ar)));
        else if(typeId == Microsoft::Featurizer::TypeId::Int16)
            results.emplace_back(Traits<std::int16_t>::ToString(Traits<std::int16_t>::deserialize(ar)));
        else if(typeId == Microsoft::Featurizer::TypeId::Int32)
            results.emplace_back(Traits<std::int32_t>::ToString(Traits<std::int32_t>::deserialize(ar)));
        else if(typeId == Microsoft::Featurizer::TypeId::Int64)
            results.emplace_back(Traits<std::int64_t>::ToString(Traits<std::int64_t>::deserialize(ar)));
        else if(typeId == Microsoft::Featurizer::TypeId::UInt8)
            results.emplace_back(Traits<std::uint8_t>::ToString(Traits<std::uint8_t>::deserialize(ar)));
        else if(typeId == Microsoft::Featurizer::TypeId::UInt16)
            results.emplace_back(Traits<std::uint16_t>::ToString(Traits<std::uint16_t>::deserialize(ar)));
        else if(typeId == Microsoft::Featurizer::TypeId::UInt32)
            results.emplace_back(Traits<std::uint32_t>::ToString(Traits<std::uint32_t>::deserialize(ar)));
        else if(typeId == Microsoft::Featurizer::TypeId::UInt64)
            results.emplace_back(Traits<std::uint64_t>::ToString(Traits<std::uint64_t>::deserialize(ar)));
        // Float16 is not supported yet
        else if(typeId == Microsoft::Featurizer::TypeId::Float32)
            results.emplace_back(Traits<std::float_t>::ToString(Traits<std::float_t>::deserialize(ar)));
        else if(typeId == Microsoft::Featurizer::TypeId::Float64)
            results.emplace_back(Traits<std::double_t>::ToString(Traits<std::double_t>::deserialize(ar)));
        // Complex64 is not supported yet
        // Complex128 is not supported yet
        // BFloat16 is not supported yet
        else if(typeId == Microsoft::Featurizer::TypeId::Bool)
            results.emplace_back(Traits<bool>::ToString(Traits<bool>::deserialize(ar)));
        else if(typeId == Microsoft::Featurizer::TypeId::Timepoint)
            results.emplace_back(Traits<std::chrono::system_clock::time_point>::ToString(Traits<std::chrono::system_clock::time_point>::deserialize(ar)));
        else if(typeId == Microsoft::Featurizer::TypeId::Duration)
            results.emplace_back(Traits<std::chrono::system_clock::duration>::ToString(Traits<std::chrono::system_clock::duration>::deserialize(ar)));
        // Tensor is not supported yet
        // SparseTensor is not supported yet
        // Tabular is not supported yet
        // Nullable is not supported yet
        // Vector is not supported yet
        // Map is not supported yet
        else {
            char buffer[1024];

            snprintf(buffer, sizeof(buffer), "'%d' is not a supported type id", static_cast<int>(typeId));
            throw std::runtime_error(buffer);
        }
    }

    return results;
}

template <typename T>
void _LoadDataString(Microsoft::Featurizer::Archive &ar, OptionalStrings &results) {
    // ----------------------------------------------------------------------
    using TheseTraits               = Microsoft::Featurizer::Traits<T>;
    // ----------------------------------------------------------------------

    typename TheseTraits::nullable_type     value(Microsoft::Featurizer::Traits<typename TheseTraits::nullable_type>::deserialize(ar));

    results.emplace_back(TheseTraits::IsNull(value) ? nonstd::optional<std::string>() : TheseTraits::ToString(TheseTraits::GetNullableValue(value)));
}

OptionalStrings Serializer::_LoadDataStrings(Microsoft::Featurizer::Archive &ar) const {
    OptionalStrings                         results;

    results.reserve(DataTypes.size());

    for(auto const & typeId : DataTypes) {
        if(typeId == Microsoft::Featurizer::TypeId::String)
            _LoadDataString<std::string>(ar, results);
        else if(typeId == Microsoft::Featurizer::TypeId::Int8)
            _LoadDataString<std::int8_t>(ar, results);
        else if(typeId == Microsoft::Featurizer::TypeId::Int16)
            _LoadDataString<std::int16_t>(ar, results);
        else if(typeId == Microsoft::Featurizer::TypeId::Int32)
            _LoadDataString<std::int32_t>(ar, results);
        else if(typeId == Microsoft::Featurizer::TypeId::Int64)
            _LoadDataString<std::int64_t>(ar, results);
        else if(typeId == Microsoft::Featurizer::TypeId::UInt8)
            _LoadDataString<std::uint8_t>(ar, results);
        else if(typeId == Microsoft::Featurizer::TypeId::UInt16)
            _LoadDataString<std::uint16_t>(ar, results);
        else if(typeId == Microsoft::Featurizer::TypeId::UInt32)
            _LoadDataString<std::uint32_t>(ar, results);
        else if(typeId == Microsoft::Featurizer::TypeId::UInt64)
            _LoadDataString<std::uint64_t>(ar, results);
        // Float16 is not supported yet
        else if(typeId == Microsoft::Featurizer::TypeId::Float32)
            _LoadDataString<std::float_t>(ar, results);
        else if(typeId == Microsoft::Featurizer::TypeId::Float64)
            _LoadDataString<std::double_t>(ar, results);
        // Complex64 is not supported yet
        // Complex128 is not supported yet
        // BFloat16 is not supported yet
        else if(typeId == Microsoft::Featurizer::TypeId::Bool)
            _LoadDataString<bool>(ar, results);
        else if(typeId == Microsoft::Featurizer::TypeId::Timepoint)
            _LoadDataString<std::chrono::system_clock::time_point>(ar, results);
        else if(typeId == Microsoft::Featurizer::TypeId::Duration)
            _LoadDataString<std::chrono::system_clock::duration>(ar, results);
        // Tensor is not supported yet
        // SparseTensor is not supported yet
        // Tabular is not supported yet
        // Nullable is not supported yet
        // Vector is not supported yet
        // Map is not supported yet
        else {
            char buffer[1024];

            snprintf(buffer, sizeof(buffer), "'%d' is not a supported type id", static_cast<int>(typeId));
            throw std::runtime_error(buffer);
        }
    }

    return results;
}

void Serializer::_SaveKeyStrings(Microsoft::Featurizer::Archive &ar, Strings const &strings) const {
    // ----------------------------------------------------------------------
    using namespace Microsoft::Featurizer;
    // ----------------------------------------------------------------------

    assert(strings.size() == KeyTypes.size());

    TypeIds::const_iterator                 iterTypeId(KeyTypes.begin());

    for(auto const & s : strings) {
        Microsoft::Featurizer::TypeId       typeId(*iterTypeId++);

        if(typeId == Microsoft::Featurizer::TypeId::String)
            Traits<std::string>::serialize(ar, s);
        else if(typeId == Microsoft::Featurizer::TypeId::Int8)
            Traits<std::int8_t>::serialize(ar, Traits<std::int8_t>::FromString(s));
        else if(typeId == Microsoft::Featurizer::TypeId::Int16)
            Traits<std::int16_t>::serialize(ar, Traits<std::int16_t>::FromString(s));
        else if(typeId == Microsoft::Featurizer::TypeId::Int32)
            Traits<std::int32_t>::serialize(ar, Traits<std::int32_t>::FromString(s));
        else if(typeId == Microsoft::Featurizer::TypeId::Int64)
            Traits<std::int64_t>::serialize(ar, Traits<std::int64_t>::FromString(s));
        else if(typeId == Microsoft::Featurizer::TypeId::UInt8)
            Traits<std::uint8_t>::serialize(ar, Traits<std::uint8_t>::FromString(s));
        else if(typeId == Microsoft::Featurizer::TypeId::UInt16)
            Traits<std::uint16_t>::serialize(ar, Traits<std::uint16_t>::FromString(s));
        else if(typeId == Microsoft::Featurizer::TypeId::UInt32)
            Traits<std::uint32_t>::serialize(ar, Traits<std::uint32_t>::FromString(s));
        else if(typeId == Microsoft::Featurizer::TypeId::UInt64)
            Traits<std::uint64_t>::serialize(ar, Traits<std::uint64_t>::FromString(s));
        // Float16 is not supported yet
        else if(typeId == Microsoft::Featurizer::TypeId::Float32)
            Traits<std::float_t>::serialize(ar, Traits<std::float_t>::FromString(s));
        else if(typeId == Microsoft::Featurizer::TypeId::Float64)
            Traits<std::double_t>::serialize(ar, Traits<std::double_t>::FromString(s));
        // Complex64 is not supported yet
        // Complex128 is not supported yet
        // BFloat16 is not supported yet
        else if(typeId == Microsoft::Featurizer::TypeId::Bool)
            Traits<bool>::serialize(ar, Traits<bool>::FromString(s));
        else if(typeId == Microsoft::Featurizer::TypeId::Timepoint)
            Traits<std::chrono::system_clock::time_point>::serialize(ar, Traits<std::chrono::system_clock::time_point>::FromString(s));
        else if(typeId == Microsoft::Featurizer::TypeId::Duration)
            Traits<std::chrono::system_clock::duration>::serialize(ar, Traits<std::chrono::system_clock::duration>::FromString(s));
        // Tensor is not supported yet
        // SparseTensor is not supported yet
        // Tabular is not supported yet
        // Nullable is not supported yet
        // Vector is not supported yet
        // Map is not supported yet
        else {
            char buffer[1024];

            snprintf(buffer, sizeof(buffer), "'%d' is not a supported type id", static_cast<int>(typeId));
            throw std::runtime_error(buffer);
        }
    }
}

template <typename T>
void _SaveDataString(Microsoft::Featurizer::Archive &ar, nonstd::optional<std::string> const &s) {
    // ----------------------------------------------------------------------
    using TheseTraits                       = Microsoft::Featurizer::Traits<T>;
    // ----------------------------------------------------------------------

    typename TheseTraits::nullable_type     value(
        [&s](void) -> typename TheseTraits::nullable_type {
            if(!s)
                return TheseTraits::CreateNullValue();

            return TheseTraits::FromString(*s);
        }()
    );

    Microsoft::Featurizer::Traits<typename TheseTraits::nullable_type>::serialize(ar, value);
}

void Serializer::_SaveDataStrings(Microsoft::Featurizer::Archive &ar, OptionalStrings const &strings) const {
    assert(strings.size() == DataTypes.size());

    TypeIds::const_iterator                 iterTypeId(DataTypes.begin());

    for(auto const & s : strings) {
        Microsoft::Featurizer::TypeId       typeId(*iterTypeId++);

        if(typeId == Microsoft::Featurizer::TypeId::String)
            _SaveDataString<std::string>(ar, s);
        else if(typeId == Microsoft::Featurizer::TypeId::Int8)
            _SaveDataString<std::int8_t>(ar, s);
        else if(typeId == Microsoft::Featurizer::TypeId::Int16)
            _SaveDataString<std::int16_t>(ar, s);
        else if(typeId == Microsoft::Featurizer::TypeId::Int32)
            _SaveDataString<std::int32_t>(ar, s);
        else if(typeId == Microsoft::Featurizer::TypeId::Int64)
            _SaveDataString<std::int64_t>(ar, s);
        else if(typeId == Microsoft::Featurizer::TypeId::UInt8)
            _SaveDataString<std::uint8_t>(ar, s);
        else if(typeId == Microsoft::Featurizer::TypeId::UInt16)
            _SaveDataString<std::uint16_t>(ar, s);
        else if(typeId == Microsoft::Featurizer::TypeId::UInt32)
            _SaveDataString<std::uint32_t>(ar, s);
        else if(typeId == Microsoft::Featurizer::TypeId::UInt64)
            _SaveDataString<std::uint64_t>(ar, s);
        // Float16 is not supported yet
        else if(typeId == Microsoft::Featurizer::TypeId::Float32)
            _SaveDataString<std::float_t>(ar, s);
        else if(typeId == Microsoft::Featurizer::TypeId::Float64)
            _SaveDataString<std::double_t>(ar, s);
        // Complex64 is not supported yet
        // Complex128 is not supported yet
        // BFloat16 is not supported yet
        else if(typeId == Microsoft::Featurizer::TypeId::Bool)
            _SaveDataString<bool>(ar, s);
        else if(typeId == Microsoft::Featurizer::TypeId::Timepoint)
            _SaveDataString<std::chrono::system_clock::time_point>(ar, s);
        else if(typeId == Microsoft::Featurizer::TypeId::Duration)
            _SaveDataString<std::chrono::system_clock::duration>(ar, s);
        // Tensor is not supported yet
        // SparseTensor is not supported yet
        // Tabular is not supported yet
        // Nullable is not supported yet
        // Vector is not supported yet
        // Map is not supported yet
        else {
            char buffer[1024];

            snprintf(buffer, sizeof(buffer), "'%d' is not a supported type id", static_cast<int>(typeId));
            throw std::runtime_error(buffer);
        }
    }
}

// ----------------------------------------------------------------------
// |
// |  EstimatorMemory
// |
// ----------------------------------------------------------------------
EstimatorMemory::EstimatorMemory(SerializerType serializer, Microsoft::Featurizer::Featurizers::TimeSeriesImputerEstimator estimator) :
    EstimatorSerializer(std::move(serializer)),
    Estimator(std::move(estimator)) {
}

// ----------------------------------------------------------------------
// |
// |  TransformerMemory
// |
// ----------------------------------------------------------------------
TransformerMemory::TransformerMemory(SerializerType serializer, TransformerUniquePtr pTransformer) :
    TransformerSerializer(std::move(serializer)),
    Transformer(
        std::move(
            [&pTransformer](void) -> TransformerUniquePtr & {
                assert(pTransformer);
                return pTransformer;
            }()
        )
    ) {
}

TransformerMemory::TransformerMemory(Microsoft::Featurizer::Archive &ar) :
    TransformerSerializer(ar),
    Transformer(new Microsoft::Featurizer::Featurizers::TimeSeriesImputerEstimator::TransformerType(ar)) {
}

Microsoft::Featurizer::Archive & TransformerMemory::save(Microsoft::Featurizer::Archive &ar) {
    TransformerSerializer.save(ar);
    Transformer->save(ar);

    return ar;
}
