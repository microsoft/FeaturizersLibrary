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
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using NullableType                      = nonstd::optional<T>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    // We are using nonstd::optional here, as we always want the type to be optional
    // and not a special value of the type (for example, double is technically optional
    // (as it supports NaN), but default-constructs as something that isn't NaN;
    // we avoid this problem by always using optional).
    NullableType const                      _defaultValue;

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
            // TODO: There may be scenarios where an exception isn't the desired behavior - the caller would want us to return
            //       an optional value. However, adding this functionality will increase the complexity of the imputer. If we
            //       decide to go this route, we should only exercise this code path if the output type is optional (right now,
            //       this isn't possible as the output type is inferred) and the user opts-in to the behavior during object
            //       construction. We need this explicit opt-in behavior so that we don't return NaNs for floats and doubles as
            //       the default just because it happens to be an optional type.
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
class ForwardFillImputerEstimator : public Components::InferenceOnlyEstimatorImpl<ForwardFillImputerTransformer<T>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = Components::InferenceOnlyEstimatorImpl<ForwardFillImputerTransformer<T>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ForwardFillImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~ForwardFillImputerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ForwardFillImputerEstimator);
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
// |  ForwardFillImputerTransformer
// |
// ----------------------------------------------------------------------
template <typename T>
ForwardFillImputerTransformer<T>::ForwardFillImputerTransformer(T defaultValue) :
    _defaultValue(std::move(defaultValue)),
    _lastValue(*_defaultValue),
    _validLastValue(true) {
}

template <typename T>
ForwardFillImputerTransformer<T>::ForwardFillImputerTransformer(Archive &ar) :
    ForwardFillImputerTransformer(
        [&ar](void) {
            // ----------------------------------------------------------------------
            using NullableTypeTraits        = Traits<NullableType>;
            // ----------------------------------------------------------------------

            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            NullableType                    defaultValue(Traits<NullableType>::deserialize(ar));

            if(NullableTypeTraits::IsNull(defaultValue))
                return ForwardFillImputerTransformer();

            return ForwardFillImputerTransformer(std::move(NullableTypeTraits::GetNullableValue(defaultValue)));
        }()
    ) {
}

template <typename T>
bool ForwardFillImputerTransformer<T>::operator==(ForwardFillImputerTransformer const &other) const {
    // Note that we aren't comparing _lastValue or _validLastValue as we are only using initial state to compare values

    // We aren't using nonstd::optional's comparison operator as we aren't able to disable compiler warnings
    // associated with the comparison of float values as that code has already been #included by the time
    // that we get here. Do things manually instead.
    if(static_cast<bool>(_defaultValue) != static_cast<bool>(other._defaultValue))
        return false;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    return static_cast<bool>(_defaultValue) == false || *_defaultValue == *other._defaultValue;

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
    Traits<NullableType>::serialize(ar, _defaultValue);

    // Note that we aren't serializing working state
}

// ----------------------------------------------------------------------
// |
// |  ForwardFillImputerEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
ForwardFillImputerEstimator<T>::ForwardFillImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("ForwardFillImputerEstimator", std::move(pAllColumnAnnotations)) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
