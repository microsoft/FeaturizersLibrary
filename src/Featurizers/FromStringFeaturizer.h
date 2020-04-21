// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Traits.h"
#include "Components/InferenceOnlyFeaturizerImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         FromStringTransformer
///  \brief         Transforms a string into a corresponding type.
///
template <typename T>
class FromStringTransformer : public StandardTransformer<std::string, T> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = StandardTransformer<std::string, T>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    FromStringTransformer(bool useEmptyStringsForNullValues=false);
    FromStringTransformer(Archive &ar);

    ~FromStringTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FromStringTransformer);

    bool operator==(FromStringTransformer const &other) const;
    bool operator!=(FromStringTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using Function                          = std::function<T (std::string const &)>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    bool const                              _useEmptyStringsForNullValues;
    Function const                          _impl;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems with the function declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        callback(_impl(input));
    }

    static T FromString(std::string const &value);
    static T FromStringWithEmptyStringsForNullValues(std::string const &value);
    static T FromStringWithEmptyStringsForNullValuesImpl(std::string const &value, std::true_type);
    static T FromStringWithEmptyStringsForNullValuesImpl(std::string const &value, std::false_type);
};

template <typename T>
class FromStringEstimator : public TransformerEstimator<std::string, T> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<std::string, T>;
    using TransformerType                   = FromStringTransformer<T>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    FromStringEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool useEmptyStringsForNullValues=false);
    ~FromStringEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FromStringEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    bool const                              _useEmptyStringsForNullValues;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;
    void complete_training_impl(void) override;

    // MSVC has problems when the definition and declaration are separated
    FitResult fit_impl(typename BaseType::InputType const *, size_t) override {
        throw std::runtime_error("This should never be called");
    }

    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return typename BaseType::TransformerUniquePtr(new FromStringTransformer<T>(_useEmptyStringsForNullValues));
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
// |  FromStringTransformer
// |
// ----------------------------------------------------------------------
template <typename T>
FromStringTransformer<T>::FromStringTransformer(bool useEmptyStringsForNullValues /*=false*/) :
    _useEmptyStringsForNullValues(
        std::move(
            [&useEmptyStringsForNullValues](void) -> bool & {
                if(useEmptyStringsForNullValues && Traits<T>::IsNullableType == false)
                    throw std::invalid_argument("empty strings cannot be used with types that are not nullable");

                return useEmptyStringsForNullValues;
            }()
        )
    ),
    _impl(_useEmptyStringsForNullValues ? FromStringWithEmptyStringsForNullValues : FromString)
{}

template <typename T>
FromStringTransformer<T>::FromStringTransformer(Archive &ar) :
    FromStringTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            return FromStringTransformer(Traits<bool>::deserialize(ar));
        }()
    )
{}

template <typename T>
bool FromStringTransformer<T>::operator==(FromStringTransformer const &other) const {
    return _useEmptyStringsForNullValues == other._useEmptyStringsForNullValues;
}

template <typename T>
bool FromStringTransformer<T>::operator!=(FromStringTransformer const &other) const {
    return (*this == other) == false;
}

template <typename T>
void FromStringTransformer<T>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<bool>::serialize(ar, _useEmptyStringsForNullValues);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename T>
// static
T FromStringTransformer<T>::FromString(std::string const &value) {
    return Traits<T>::FromString(value);
}

template <typename T>
// static
T FromStringTransformer<T>::FromStringWithEmptyStringsForNullValues(std::string const &value) {
    return FromStringWithEmptyStringsForNullValuesImpl(value, std::integral_constant<bool, Traits<T>::IsNullableType>());
}

template <typename T>
// static
T FromStringTransformer<T>::FromStringWithEmptyStringsForNullValuesImpl(std::string const &value, std::true_type) {
    if(value.empty())
        return Traits<T>::CreateNullValue();

    return FromString(value);
}

template <typename T>
// static
T FromStringTransformer<T>::FromStringWithEmptyStringsForNullValuesImpl(std::string const &, std::false_type) {
    throw std::runtime_error("This should never be called");
}

// ----------------------------------------------------------------------
// |
// |  FromStringEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
FromStringEstimator<T>::FromStringEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool useEmptyStringsForNullValues /*=false*/) :
    BaseType("FromStringEstimator", std::move(pAllColumnAnnotations)),
    _useEmptyStringsForNullValues(std::move(useEmptyStringsForNullValues))
{}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename T>
bool FromStringEstimator<T>::begin_training_impl(void) /*override*/ {
    // No training required
    return false;
}

template <typename T>
void FromStringEstimator<T>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
