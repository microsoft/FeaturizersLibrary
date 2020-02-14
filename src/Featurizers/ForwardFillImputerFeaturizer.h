// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "../Traits.h"

#include "Components/InferenceOnlyFeaturizerImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         ForwardFillImputerTransformer
///  \brief         Imputer that populates null incoming values with the last
///                 non-null value encountered.
///
template <typename T>
class ForwardFillImputerTransformer :
    public Components::InferenceOnlyTransformerImpl<
        typename Traits<T>::nullable_type,
        T
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<T>::IsNullableType == false || Traits<T>::IsNativeNullableType, "'T' must not be a nullable type");

    using BaseType =
        Components::InferenceOnlyTransformerImpl<
            typename Traits<T>::nullable_type,
            T
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ForwardFillImputerTransformer(void) = default;
    ForwardFillImputerTransformer(T defaultValue);
    ForwardFillImputerTransformer(Archive &ar);

    ~ForwardFillImputerTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ForwardFillImputerTransformer);

    bool operator==(ForwardFillImputerTransformer const &other) const;
    bool operator!=(ForwardFillImputerTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    T                                       _lastValue;
    bool                                    _validLastValue = false;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC runs into problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        // ----------------------------------------------------------------------
        using TheseTraits                   = Traits<typename BaseType::InputType>;
        // ----------------------------------------------------------------------

        if(TheseTraits::IsNull(input)) {
            if(_validLastValue == false) {
                // This scenario will happen when the first imputed item is null, as we haven't seen a valid value yet.
                throw std::runtime_error("No source value for forward fill");
            }

            callback(_lastValue);
        }
        else {
            T const &                       value(TheseTraits::GetNullableValue(input));

            callback(value);

            _lastValue = value;
            _validLastValue = true;
        }
    }
};

/////////////////////////////////////////////////////////////////////////
///  \typedef       ForwardFillImputerEstimator
///  \brief         Estimator that creates `ForwardFillImputerTransformer`.
///
template <typename T>
using ForwardFillImputerEstimator           = Components::InferenceOnlyEstimatorImpl<ForwardFillImputerTransformer<T>>;

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Implementation
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename T>
ForwardFillImputerTransformer<T>::ForwardFillImputerTransformer(T defaultValue) :
    _lastValue(std::move(defaultValue)),
    _validLastValue(true) {
}

template <typename T>
ForwardFillImputerTransformer<T>::ForwardFillImputerTransformer(Archive &ar) :
    ForwardFillImputerTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            bool                            validLastValue(Traits<bool>::deserialize(ar));

            if(validLastValue == false)
                return ForwardFillImputerTransformer();

            T                               lastValue(Traits<T>::deserialize(ar));

            return ForwardFillImputerTransformer(std::move(lastValue));
        }()
    ) {
}

template <typename T>
bool ForwardFillImputerTransformer<T>::operator==(ForwardFillImputerTransformer const &other) const {
    if(_validLastValue != other._validLastValue)
        return false;

    if(_validLastValue == false)
        return true;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    return _lastValue == other._lastValue;

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
}

template <typename T>
bool ForwardFillImputerTransformer<T>::operator!=(ForwardFillImputerTransformer const &other) const {
    return (*this == other) == false;
}

template <typename T>
void ForwardFillImputerTransformer<T>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<bool>::serialize(ar, _validLastValue);

    if(_validLastValue)
        Traits<T>::serialize(ar, _lastValue);
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
