// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../../Archive.h"
#include "../../Featurizer.h"
#include "../../Traits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

/////////////////////////////////////////////////////////////////////////
///  \class         ImputerTransformer
///  \brief         Common transformer that imputes a given value for null
///                 input. This Transformer can be used across a number of
///                 different imputers, where each of this estimators calculates
///                 the value to be imputed in different ways.
///
template <typename InputT, typename TransformedT>
class ImputerTransformer : public StandardTransformer<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<InputT>::IsNullableType, "'InputT' must be a nullable type");
    static_assert(Traits<TransformedT>::IsNullableType == false || Traits<TransformedT>::IsNativeNullableType, "'TransformedT' should not be a nullable type");

    using InputType                         = InputT;
    using TransformedType                   = TransformedT;
    using BaseType                          = StandardTransformer<InputType, TransformedType>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    TransformedType const                   Value;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ImputerTransformer(TransformedType value);
    ImputerTransformer(Archive &ar);

    ~ImputerTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ImputerTransformer);

    bool operator==(ImputerTransformer const &other) const;
    bool operator!=(ImputerTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(InputType const &input, typename BaseType::CallbackFunction const &callback) override;
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
template <typename InputT, typename TransformedT>
ImputerTransformer<InputT, TransformedT>::ImputerTransformer(TransformedType value) :
    Value(std::move(value)) {
}

template <typename InputT, typename TransformedT>
ImputerTransformer<InputT, TransformedT>::ImputerTransformer(Archive &ar) :
    ImputerTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            return ImputerTransformer(Traits<TransformedT>::deserialize(ar));
        }()
    ) {
}

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

template <typename InputT, typename TransformedT>
bool ImputerTransformer<InputT, TransformedT>::operator==(ImputerTransformer const &other) const {
    return Value == other.Value;
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

template <typename InputT, typename TransformedT>
bool ImputerTransformer<InputT, TransformedT>::operator!=(ImputerTransformer const &other) const {
    return (*this == other) == false;
}

template <typename InputT, typename TransformedT>
void ImputerTransformer<InputT, TransformedT>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(Value)>::serialize(ar, Value);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
void ImputerTransformer<InputT, TransformedT>::execute_impl(InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    // ----------------------------------------------------------------------
    using TheseTraits                       = Traits<InputType>;
    // ----------------------------------------------------------------------

    if(TheseTraits::IsNull(input))
        callback(Value);
    else
        callback(TheseTraits::GetNullableValue(input));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
