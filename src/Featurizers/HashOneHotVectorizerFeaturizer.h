// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Structs.h"
#include "../Traits.h"
#include "Components/InferenceOnlyFeaturizerImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         HashOneHotVectorizerTransformer
///  \brief         Convert input to hash and encode to one hot encoded vector
///
template <typename T>
class HashOneHotVectorizerTransformer : public Components::InferenceOnlyTransformerImpl<T, SingleValueSparseVectorEncoding<std::uint8_t>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = T;
    using BaseType                          = Components::InferenceOnlyTransformerImpl<Type, SingleValueSparseVectorEncoding<std::uint8_t>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    HashOneHotVectorizerTransformer(std::uint32_t hashingSeedVal, std::uint32_t numCols);
    HashOneHotVectorizerTransformer(Archive &ar);

    ~HashOneHotVectorizerTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(HashOneHotVectorizerTransformer);

    bool operator ==(HashOneHotVectorizerTransformer const &other) const;

    void save(Archive & ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Primitives
    // |
    // ----------------------------------------------------------------------
    std::uint32_t const                        _hashingSeedVal;
    std::uint32_t const                        _numCols;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    // MSVC has problems when the function is defined outside of the declaration
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {

        std::uint32_t colHashVal = MurmurHashGenerator(input, _hashingSeedVal);

        callback(
            SingleValueSparseVectorEncoding<std::uint8_t>(
                _numCols,
                1,
                static_cast<std::uint64_t>(colHashVal % _numCols)
            )
        );
    }
};

template <typename T>
class HashOneHotVectorizerEstimator : public TransformerEstimator<T, SingleValueSparseVectorEncoding<std::uint8_t>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<T, SingleValueSparseVectorEncoding<std::uint8_t>>;
    using TransformerType                   = HashOneHotVectorizerTransformer<T>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    HashOneHotVectorizerEstimator(AnnotationMapsPtr pAllCoumnAnnotations, std::uint32_t hashingSeedVal, std::uint32_t numCols);
    ~HashOneHotVectorizerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(HashOneHotVectorizerEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Primitives
    // |
    // ----------------------------------------------------------------------
    std::uint32_t const                         _hashingSeedVal;
    std::uint32_t const                         _numCols;
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;

    //MSVC will complain when the function is defined outside of the declaration
    FitResult fit_impl(typename BaseType::InputType const *, size_t) override {
        throw std::runtime_error("This should never be called as this class will not be used during training");
    }

    void complete_training_impl(void) override;

    //MSVC will complain when the function is defined outside of the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return typename BaseType::TransformerUniquePtr(new HashOneHotVectorizerTransformer<T>(_hashingSeedVal, _numCols));
    }
};

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Implementation
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// |
// |  HashOneHotVectorizerTransformer
// |
// ----------------------------------------------------------------------
template <typename T>
HashOneHotVectorizerTransformer<T>::HashOneHotVectorizerTransformer(std::uint32_t hashingSeedVal, std::uint32_t numCols):
    _hashingSeedVal(std::move(hashingSeedVal)),
    _numCols(std::move([&numCols](void)->uint32_t & {
        if (numCols <= 0)
            throw std::runtime_error("Invalid numCols");
        return numCols;
    }())){
}

template <typename T>
HashOneHotVectorizerTransformer<T>::HashOneHotVectorizerTransformer(Archive &ar) :
    HashOneHotVectorizerTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            std::uint32_t                   hashingSeedVal(Traits<std::uint32_t>::deserialize(ar));
            std::uint32_t                   numCols(Traits<std::uint32_t>::deserialize(ar));

            return HashOneHotVectorizerTransformer<T>(std::move(hashingSeedVal), std::move(numCols));
        }()
    ) {
}

template <typename T>
bool HashOneHotVectorizerTransformer<T>::operator ==(HashOneHotVectorizerTransformer const &other) const {
    return BaseType::operator==(other)
        && _hashingSeedVal == other._hashingSeedVal
        && _numCols ==  other._numCols;
}

template <typename T>
void HashOneHotVectorizerTransformer<T>::save(Archive & ar) const {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<std::uint32_t>::serialize(ar, _hashingSeedVal);
    Traits<std::uint32_t>::serialize(ar, _numCols);
}

// ----------------------------------------------------------------------
// |
// |  HashOneHotVectorizerEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
HashOneHotVectorizerEstimator<T>::HashOneHotVectorizerEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t hashingSeedVal, std::uint32_t numCols) :
    BaseType("HashOneHotVectorizerEstimator", std::move(pAllColumnAnnotations)),
    _hashingSeedVal(std::move(hashingSeedVal)),
    _numCols(std::move(numCols)) {
}

template <typename T>
bool HashOneHotVectorizerEstimator<T>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename T>
void HashOneHotVectorizerEstimator<T>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
