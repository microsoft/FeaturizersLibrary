// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {
namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         HasHasCreatedTransformerMethodImpl
///  \brief         Base declaration to determine if a type has the method
///                 'has_created_transformer'.
///
template <typename T, typename FunctionT>
struct HasHasCreatedTransformerMethodImpl {
    static_assert(std::integral_constant<T, false>::value, "Second template parameter must be a function type");
};

/////////////////////////////////////////////////////////////////////////
///  \class         HasHasCreatedTransformerMethodImpl
///  \brief         Partial template specialization that is able to detect
///                 a method's return type and arguments.
///
template <typename T, typename ReturnT, typename... ArgTs>
class HasHasCreatedTransformerMethodImpl<T, ReturnT (ArgTs...)> {
private:
    template <typename U> static constexpr std::false_type Check(...);

    template <typename U>
    static constexpr std::true_type Check(
        U *,
        std::enable_if_t<
            std::is_same<
                decltype(std::declval<U>().has_created_transformer(std::declval<ArgTs>()...)),
                ReturnT
            >::value,
            void *
        >
    );

public:
    static constexpr bool const             value = std::is_same<std::true_type, decltype(Check<T>(nullptr, nullptr))>::value;
};

/////////////////////////////////////////////////////////////////////////
///  \class         HasHasCreatedTransformerMethod
///  \brief         Has a constexpr bool value set to true if the provided
///                 object has the method:
///
///                     bool has_created_transformer(void) const
///
template <typename T>
class HasHasCreatedTransformerMethod : public HasHasCreatedTransformerMethodImpl<T, bool ()> {};

/////////////////////////////////////////////////////////////////////////
///  \class         IsTransformerEstimator
///  \brief         Contains a constant value of true if the provided `Estimator`
///                 is a `TransformerEstimator`.
///
template <typename EstimatorT>
struct IsTransformerEstimator {
    static constexpr bool const             value = HasHasCreatedTransformerMethod<EstimatorT>::value;
};

#if (defined DEBUG)
    static_assert(IsTransformerEstimator<TransformerEstimator<char, int>>::value, "");
    static_assert(IsTransformerEstimator<TransformerEstimator<std::string, std::string>>::value, "");
    static_assert(IsTransformerEstimator<FitEstimator<char>>::value == false, "");
#endif

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorOutputTypeImpl
///  \brief         Output type for `TransformerEstimator` objects.
///
template <typename EstimatorT, bool IsTransformerEstimatorV>
struct EstimatorOutputTypeImpl {
    using type                              = typename EstimatorT::TransformedType;
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorOutputTypeImpl
///  \brief         Output type for non-`TransformerEstimator` objects.
///
template <typename EstimatorT>
struct EstimatorOutputTypeImpl<EstimatorT, false> {
    using type                              = typename EstimatorT::InputType;
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorOutputType
///  \brief         Provides a consistent interface for an `Estimator's` output
///                 type.
///
template <typename EstimatorT>
struct EstimatorOutputType : public EstimatorOutputTypeImpl<EstimatorT, IsTransformerEstimator<EstimatorT>::value> {};

} // namespace Details
} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
