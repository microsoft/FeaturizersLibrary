// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <tuple>

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {
namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         IsTuple
///  \brief         Contains a Value set to true if the incoming type is a tuple.
///
template <typename T>
struct IsTuple : public std::false_type {
};

template <typename... ArgTs>
struct IsTuple<std::tuple<ArgTs...>> : public std::true_type {
};

namespace Details {

template <size_t FilterIndexV, size_t... FilterIndexVs>
struct GetFirstIndexValue {
    static constexpr size_t const           Value = FilterIndexV;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         FilterFeaturizerTraits
///  \brief         Traits common to all types of `Estimators` and `Transformers`
///                 when used within Filter featurizer constructs.
///
template <typename InputTupleT, size_t... FilterInputTupleIndexVs>
struct FilterFeaturizerTraits {
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(IsTuple<InputTupleT>::value, "'InputTupleT' must be a tuple");

    // The first N elements in the tuple represent the original input data and must therefore be
    // references. However, not all of the tuple elements must be references. For example, if this
    // FilterFeaturizer is part of a pipeline with upstream FilterFeaturizers, the first elements
    // associated with the original input will be references, but the latter elements will be the
    // result of the transformer (and not references).
    //
    // This check isn't perfect, but hopefully enough to prevent unintentional bugs associated with
    // unnecessary copies of incoming data.
    static_assert(std::is_reference<typename std::tuple_element<0, InputTupleT>::type>::value, "The initial elements in 'InputTupleT' must be references");

    using FilteredType =
        typename std::conditional<
            sizeof...(FilterInputTupleIndexVs) != 1,
            std::tuple<typename std::tuple_element<FilterInputTupleIndexVs, InputTupleT>::type...>,
            typename std::tuple_element<Details::GetFirstIndexValue<FilterInputTupleIndexVs...>::Value, InputTupleT>::type
        >::type;

    using ToFilteredTypeReturnValue =
        typename std::conditional<
            sizeof...(FilterInputTupleIndexVs) != 1,
            // We need to create a new tuple to pass to the chained object
            FilteredType,
            // We can extract a single value from the input tuple and pass it to the chained object
            typename std::add_lvalue_reference<typename std::add_const<FilteredType>::type>::type
        >::type;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    static ToFilteredTypeReturnValue ToFilteredType(InputTupleT const &input);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    static ToFilteredTypeReturnValue ToFilteredTypeImpl(InputTupleT const &input, std::true_type /*IsFilteredTypeATuple*/);
    static ToFilteredTypeReturnValue ToFilteredTypeImpl(InputTupleT const &input, std::false_type /*IsFilteredTypeATuple*/);
};

/////////////////////////////////////////////////////////////////////////
///  \class         FilterTransformerTraits
///  \brief         Traits common to `TransformerEstimators` and `Transformers`
///                 when used within Filter featurizer constructs.
///
template <
    typename ChainedT,
    typename InputTupleT,
    size_t... FilterInputTupleIndexVs
>
struct FilterTransformerTraits :
    public FilterFeaturizerTraits<InputTupleT, FilterInputTupleIndexVs...>
{
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static constexpr bool const             IsChainedTransformedTypeATuple = IsTuple<typename ChainedT::TransformedType>::value;

    using ChainedTransformedTypeTuple =
        typename std::conditional<
            IsChainedTransformedTypeATuple,
            typename ChainedT::TransformedType,
            std::tuple<typename ChainedT::TransformedType>
        >::type;

    using TransformedType =
        decltype(std::tuple_cat(std::declval<InputTupleT>(), std::declval<ChainedTransformedTypeTuple>()));

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    static TransformedType ToTransformedType(InputTupleT const &input, typename ChainedT::TransformedType output);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    static TransformedType ToTransformedTypeImpl(InputTupleT const &input, typename ChainedT::TransformedType output, std::true_type /*IsChainedTransformedTypeATuple*/);
    static TransformedType ToTransformedTypeImpl(InputTupleT const &input, typename ChainedT::TransformedType output, std::false_type /*IsChainedTransformedTypeATuple*/);
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
// |  FilterFeaturizerTraits
// |
// ----------------------------------------------------------------------
template <typename InputTupleT, size_t... FilterInputTupleIndexVs>
// static
typename FilterFeaturizerTraits<InputTupleT, FilterInputTupleIndexVs...>::ToFilteredTypeReturnValue
FilterFeaturizerTraits<InputTupleT, FilterInputTupleIndexVs...>::ToFilteredType(InputTupleT const &input) {
    return ToFilteredTypeImpl(input, std::integral_constant<bool, sizeof...(FilterInputTupleIndexVs) != 1>());
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputTupleT, size_t... FilterInputTupleIndexVs>
// static
typename FilterFeaturizerTraits<InputTupleT, FilterInputTupleIndexVs...>::ToFilteredTypeReturnValue
FilterFeaturizerTraits<InputTupleT, FilterInputTupleIndexVs...>::ToFilteredTypeImpl(InputTupleT const &input, std::true_type /*IsFilteredTypeATuple*/) {
    return FilteredType(std::get<FilterInputTupleIndexVs>(input)...);
}

template <typename InputTupleT, size_t... FilterInputTupleIndexVs>
// static
typename FilterFeaturizerTraits<InputTupleT, FilterInputTupleIndexVs...>::ToFilteredTypeReturnValue
FilterFeaturizerTraits<InputTupleT, FilterInputTupleIndexVs...>::ToFilteredTypeImpl(InputTupleT const &input, std::false_type /*IsFilteredTypeATuple*/) {
    // ----------------------------------------------------------------------
    static constexpr size_t const           Index = Details::GetFirstIndexValue<FilterInputTupleIndexVs...>::Value;
    // ----------------------------------------------------------------------

    static_assert(Index < std::tuple_size<InputTupleT>::value, "Indexes must be smaller than the input tuple");

    return std::get<Index>(input);
}

// ----------------------------------------------------------------------
// |
// |  FilterTransformerTraits
// |
// ----------------------------------------------------------------------
template <typename ChainedT, typename InputTupleT, size_t... FilterInputTupleIndexVs>
// static
typename FilterTransformerTraits<ChainedT, InputTupleT, FilterInputTupleIndexVs...>::TransformedType
FilterTransformerTraits<ChainedT, InputTupleT, FilterInputTupleIndexVs...>::ToTransformedType(InputTupleT const &input, typename ChainedT::TransformedType output) {
    return ToTransformedTypeImpl(input, std::move(output), std::integral_constant<bool, IsChainedTransformedTypeATuple>());
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename ChainedT, typename InputTupleT, size_t... FilterInputTupleIndexVs>
// static
typename FilterTransformerTraits<ChainedT, InputTupleT, FilterInputTupleIndexVs...>::TransformedType
FilterTransformerTraits<ChainedT, InputTupleT, FilterInputTupleIndexVs...>::ToTransformedTypeImpl(InputTupleT const &input, typename ChainedT::TransformedType output, std::true_type /*IsChainedTransformedTypeATuple*/) {
    return std::tuple_cat(input, std::move(output));
}

template <typename ChainedT, typename InputTupleT, size_t... FilterInputTupleIndexVs>
// static
typename FilterTransformerTraits<ChainedT, InputTupleT, FilterInputTupleIndexVs...>::TransformedType
FilterTransformerTraits<ChainedT, InputTupleT, FilterInputTupleIndexVs...>::ToTransformedTypeImpl(InputTupleT const &input, typename ChainedT::TransformedType output, std::false_type /*IsChainedTransformedTypeATuple*/) {
    return std::tuple_cat(input, std::make_tuple(std::move(output)));
}

} // namespace Details
} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
