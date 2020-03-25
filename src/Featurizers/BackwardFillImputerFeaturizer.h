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
///  \class         BackwardFillImputerTransformer
///  \brief         Imputer that populates previous incoming null values with
///                 the current value.
///
template <typename T>
class BackwardFillImputerTransformer :
    public Transformer<
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
        Transformer<
            typename Traits<T>::nullable_type,
            T
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    BackwardFillImputerTransformer(void);
    BackwardFillImputerTransformer(T defaultValue);
    BackwardFillImputerTransformer(Archive &ar);

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(BackwardFillImputerTransformer);

    bool has_pending(void) const;
    BackwardFillImputerTransformer & reset(void);

    void save(Archive &ar) const override;

    bool operator==(BackwardFillImputerTransformer const &other) const;

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

    std::uint32_t                           _numPending;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC runs into problems when the definition and declaration are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        // ----------------------------------------------------------------------
        using TheseTraits                   = Traits<typename BaseType::InputType>;
        // ----------------------------------------------------------------------

        if(TheseTraits::IsNull(input)) {
            ++_numPending;
            return;
        }

        T const &                           value(TheseTraits::GetNullableValue(input));
        std::uint32_t                       toWrite(_numPending + 1);

        while(toWrite--)
            callback(value);

        _numPending = 0;
    }

    void flush_impl(typename BaseType::CallbackFunction const &callback) override {
        // ----------------------------------------------------------------------
        using NullableTypeTraits            = Traits<NullableType>;
        // ----------------------------------------------------------------------

        if(_numPending != 0) {
            // TODO: There may be scenarios where an exception isn't the desired behavior - the caller would want us to return
            //       an optional value. However, adding this functionality will increase the complexity of the imputer. If we
            //       decide to go this route, we should only exercise this code path if the output type is optional (right now,
            //       this isn't possible as the output type is inferred) and the user opts-in to the behavior during object
            //       construction. We need this explicit opt-in behavior so that we don't return NaNs for floats and doubles as
            //       the default just because it happens to be an optional type.
            if(NullableTypeTraits::IsNull(_defaultValue))
                throw std::runtime_error("Pending backward fill items remain");

            T const &                       defaultValue(NullableTypeTraits::GetNullableValue(_defaultValue));

            while(_numPending) {
                callback(defaultValue);
                _numPending--;
            }
        }
    }
};

/////////////////////////////////////////////////////////////////////////
///  \typedef       BackwardFillImputerEstimator
///  \brief         Estimator that creates `BackwardFillImputerTransformer`
///
template <typename T>
class BackwardFillImputerEstimator : public Components::InferenceOnlyEstimatorImpl<BackwardFillImputerTransformer<T>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = Components::InferenceOnlyEstimatorImpl<BackwardFillImputerTransformer<T>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    BackwardFillImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~BackwardFillImputerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(BackwardFillImputerEstimator);
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
// |  BackwardFillImputerTransformer
// |
// ----------------------------------------------------------------------
template <typename T>
BackwardFillImputerTransformer<T>::BackwardFillImputerTransformer(void) :
    _numPending(0) {
}

template <typename T>
BackwardFillImputerTransformer<T>::BackwardFillImputerTransformer(T defaultValue) :
    _defaultValue(std::move(defaultValue)),
    _numPending(0) {
}

template <typename T>
BackwardFillImputerTransformer<T>::BackwardFillImputerTransformer(Archive &ar) :
    BackwardFillImputerTransformer(
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
                return BackwardFillImputerTransformer();

            return BackwardFillImputerTransformer(std::move(NullableTypeTraits::GetNullableValue(defaultValue)));
        }()
    ) {
}

template <typename T>
bool BackwardFillImputerTransformer<T>::has_pending(void) const {
    return _numPending != 0;
}

template <typename T>
BackwardFillImputerTransformer<T> & BackwardFillImputerTransformer<T>::reset(void) {
    _numPending = 0;
    return *this;
}

template <typename T>
void BackwardFillImputerTransformer<T>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<NullableType>::serialize(ar, _defaultValue);

    // Note that we aren't serializing working state
}

template <typename T>
bool BackwardFillImputerTransformer<T>::operator==(BackwardFillImputerTransformer const &other) const {
    // Note that we aren't comparing _numPending as we are only using initial state to compare values

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

// ----------------------------------------------------------------------
// |
// |  BackwardFillImputerTransformer
// |
// ----------------------------------------------------------------------
template <typename T>
BackwardFillImputerEstimator<T>::BackwardFillImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("BackwardFillImputerEstimator", std::move(pAllColumnAnnotations)) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
