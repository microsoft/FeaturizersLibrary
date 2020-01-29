// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Featurizer.h"
#include "../Traits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         StringTransformer
///  \brief         Converts input into strings.
///
template <typename T>
class StringTransformer : public StandardTransformer<T, std::string> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = StandardTransformer<T, std::string>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StringTransformer(bool useEmptyStringsForNullValues=false);
    StringTransformer(Archive &ar);

    ~StringTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StringTransformer);

    bool operator==(StringTransformer const &other) const;
    bool operator!=(StringTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using Function                          = std::function<std::string (T const &)>;

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
    // MSVC has problems when the function is defined outside of the declaration
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        callback(_impl(input));
    }

    static std::string ToString(T const &value);
    static std::string ToStringWithEmptyStringsForNullValues(T const &value);
    static std::string ToStringWithEmptyStringsForNullValuesImpl(T const &value, std::true_type);
    static std::string ToStringWithEmptyStringsForNullValuesImpl(T const &value, std::false_type);
};

template <typename T>
class StringEstimator : public TransformerEstimator<T, std::string> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<T, std::string>;
    using TransformerType                   = StringTransformer<T>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StringEstimator(AnnotationMapsPtr pAllCoumnAnnotations, bool useEmptyStringsForNullValues=false);
    ~StringEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StringEstimator);

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
        return typename BaseType::TransformerUniquePtr(new StringTransformer<T>(_useEmptyStringsForNullValues));
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
// |  StringTransformer
// |
// ----------------------------------------------------------------------
template <typename T>
StringTransformer<T>::StringTransformer(bool useEmptyStringsForNullValues /*=false*/) :
    _useEmptyStringsForNullValues(
        std::move(
            [&useEmptyStringsForNullValues](void) -> bool & {
                if(useEmptyStringsForNullValues && Traits<T>::IsNullableType == false)
                    throw std::invalid_argument("empty strings cannot be used with types that are not nullable");

                return useEmptyStringsForNullValues;
            }()
        )
    ),
    _impl(_useEmptyStringsForNullValues ? ToStringWithEmptyStringsForNullValues : ToString) {
}

template <typename T>
StringTransformer<T>::StringTransformer(Archive &ar) :
    StringTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            return StringTransformer(Traits<bool>::deserialize(ar));
        }()
    ) {
}

template <typename T>
bool StringTransformer<T>::operator==(StringTransformer const &other) const {
    return _useEmptyStringsForNullValues == other._useEmptyStringsForNullValues;
}

template <typename T>
bool StringTransformer<T>::operator!=(StringTransformer const &other) const {
    return (*this == other) == false;
}

template <typename T>
void StringTransformer<T>::save(Archive &ar) const /*override*/ {
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
std::string StringTransformer<T>::ToString(T const &value) {
    return Traits<T>::ToString(value);
}

template <typename T>
// static
std::string StringTransformer<T>::ToStringWithEmptyStringsForNullValues(T const &value) {
    return ToStringWithEmptyStringsForNullValuesImpl(value, std::integral_constant<bool, Traits<T>::IsNullableType>());
}

template <typename T>
// static
std::string StringTransformer<T>::ToStringWithEmptyStringsForNullValuesImpl(T const &value, std::true_type) {
    if(Traits<T>::IsNull(value))
        return "";

    return ToString(value);
}

template <typename T>
// static
std::string StringTransformer<T>::ToStringWithEmptyStringsForNullValuesImpl(T const &, std::false_type) {
    throw std::runtime_error("This should never be called");
}

// ----------------------------------------------------------------------
// |
// |  StringEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
StringEstimator<T>::StringEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool useEmptyStringsForNullValues /*=false*/) :
    BaseType("StringEstimator", std::move(pAllColumnAnnotations)),
    _useEmptyStringsForNullValues(std::move(useEmptyStringsForNullValues)) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename T>
bool StringEstimator<T>::begin_training_impl(void) /*override*/ {
    // No training required
    return false;
}

template <typename T>
void StringEstimator<T>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
