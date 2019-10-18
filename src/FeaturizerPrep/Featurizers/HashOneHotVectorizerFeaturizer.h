// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Traits.h"
#include "Components/InferenceOnlyFeaturizerImpl.h"
#include "../3rdParty/MurmurHash3.h"

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wold-style-cast"
#   pragma clang diagnostic ignored "-Wcast-align"
#   pragma clang diagnostic ignored "-Wsign-conversion"
#endif

#include "../3rdParty/MurmurHash3.cpp"

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {


namespace {

static inline std::uint32_t MurmurHashHelper(std::string const &input, std::uint32_t hashingSeedVal) {
    std::uint32_t colHashVal;
    MurmurHash3_x86_32(input.c_str(), static_cast<int>(sizeof(*input.c_str())) * static_cast<int>(input.size()), hashingSeedVal, &colHashVal);
    return colHashVal;
}

template<typename T>
static inline std::uint32_t MurmurHashHelper(T const &input, std::uint32_t hashingSeedVal) {
    static_assert(std::is_pod<T>::value, "Input must be PODs");
    std::uint32_t colHashVal;
    MurmurHash3_x86_32(reinterpret_cast<unsigned char const*>(&input), sizeof(input), hashingSeedVal, &colHashVal);
    return colHashVal;
}

}

/////////////////////////////////////////////////////////////////////////
///  \class         HashOneHotVectorizer Struct
///  \brief         <std::uint32_t colIndex, std::uint32_t numCols, bool val>
///
struct HashOneHotVectorizerStruct {
    std::uint32_t colIndex;
    std::uint32_t numCols;
    bool          val;
    bool operator==(HashOneHotVectorizerStruct const &obj) const;
};

/////////////////////////////////////////////////////////////////////////
///  \class         HashOneHotVectorizerTransformer
///  \brief         Convert input to hash and encode to one hot encoded vector
///
template <typename T>
class HashOneHotVectorizerTransformer : public Components::InferenceOnlyTransformerImpl<T, HashOneHotVectorizerStruct> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Type                              = T;
    using ThisType                          = HashOneHotVectorizerTransformer<Type>;
    using BaseType                          = Components::InferenceOnlyTransformerImpl<Type, HashOneHotVectorizerStruct>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    HashOneHotVectorizerTransformer(std::uint32_t hashingSeedVal, std::uint32_t numCols);
    HashOneHotVectorizerTransformer(Archive &ar);

    ~HashOneHotVectorizerTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(HashOneHotVectorizerTransformer);

    // MSVC has problems when the function is defined outside of the declaration
    typename BaseType::TransformedType execute(typename BaseType::InputType input) override {

        std::uint32_t colHashVal = MurmurHashHelper(input, _hashingSeedVal);

        return HashOneHotVectorizerStruct{static_cast<std::uint32_t>(colHashVal % _numCols),
                                          static_cast<std::uint32_t>(_numCols), 
                                          static_cast<bool>(true)
        };

    }

    void save(Archive & ar) const override;

private:

    // ----------------------------------------------------------------------
    // |
    // |  Private Primitives
    // |
    // ----------------------------------------------------------------------
    std::uint32_t const                        _hashingSeedVal;
    std::uint32_t const                        _numCols;
};

template <typename T>
class HashOneHotVectorizerEstimator : public TransformerEstimator<T, HashOneHotVectorizerStruct> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<T, HashOneHotVectorizerStruct>;

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
    //MSVC will complain when the function is defined outside of the declaration
    Estimator::FitResult fit_impl(typename BaseType::BaseType::FitBufferInputType const *, size_t) override {
        throw std::runtime_error("This should never be called as this class will not be used during training");
    }

    Estimator::FitResult complete_training_impl(void) override;

    //MSVC will complain when the function is defined outside of the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return std::make_unique<HashOneHotVectorizerTransformer<T>>(_hashingSeedVal, _numCols);
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
// |  HashOneHotVectorizerStruct
// |
// ----------------------------------------------------------------------
bool HashOneHotVectorizerStruct::operator==(HashOneHotVectorizerStruct const &obj) const {
    return (colIndex == obj.colIndex && numCols == obj.numCols && val == obj.val);
}

// ----------------------------------------------------------------------
// |
// |  HashOneHotVectorizerTransformer
// |
// ----------------------------------------------------------------------
template <typename T>
HashOneHotVectorizerTransformer<T>::HashOneHotVectorizerTransformer(std::uint32_t hashingSeedVal, std::uint32_t numCols):
    _hashingSeedVal(std::move(hashingSeedVal)),
    _numCols([&numCols](void)->uint32_t {
        if (numCols <= 0)
            throw std::runtime_error("Invalid numCols");
        return std::move(numCols);
    }()){
}

template <typename T>
HashOneHotVectorizerTransformer<T>::HashOneHotVectorizerTransformer(Archive &ar) :
    _hashingSeedVal(Traits<std::uint32_t>::deserialize(ar)) ,
    _numCols(Traits<std::uint32_t>::deserialize(ar)) {
}

template <typename T>
void HashOneHotVectorizerTransformer<T>::save(Archive & ar) const {
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
    BaseType("HashOneHotVectorizerEstimator", std::move(pAllColumnAnnotations), true),
    _hashingSeedVal(std::move(hashingSeedVal)),
    _numCols(std::move(numCols)) {
}

template <typename T>
Estimator::FitResult HashOneHotVectorizerEstimator<T>::complete_training_impl(void) /*override*/ {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
