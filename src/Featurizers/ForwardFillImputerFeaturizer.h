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
            if(_validLastValue == false)
                throw std::runtime_error("No source value for forward fill");

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

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
