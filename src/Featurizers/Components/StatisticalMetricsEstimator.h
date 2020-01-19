// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>

#include "TrainingOnlyEstimatorImpl.h"
#include "../../Traits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         StatisticalMetricsEstimatorName("StatisticalMetricsEstimator");

namespace TypeSelector {

// sum type selector is created for selecting different types for sum based on input type
// when input type is integer, int64 is chosen for performance
// when input type is numeric, long double is chosen
template <typename T>
struct SumTypeSelector {
    using type = std::int64_t;
    static constexpr bool const IsNumeric = false;
};
template <>
struct SumTypeSelector<std::float_t> {
    using type = long double;
    static constexpr bool const IsNumeric = true;
};

template <>
struct SumTypeSelector<std::double_t> {
    using type = long double;
    static constexpr bool const IsNumeric = true;
};

} // namespace TypeSelector

namespace Updaters {
// TODO: Updaters should be extracted to a separate file

/////////////////////////////////////////////////////////////////////////
///  \class         BasicStatsUpdater
///  \brief         BasicStatsUpdater updates basic stats include
///                 min, max and count
///
template <typename T>
class BasicStatsUpdater {
public:
    /////////////////////////////////////////////////////////////////////////
    ///  \class         Result
    ///  \brief         A structure which contains the min, max and count
    ///                 for an input column. Template T can be all types
    ///
    struct Result {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Data
        // |
        // ----------------------------------------------------------------------
        T             const                 Min;
        T             const                 Max;
        std::uint64_t const                 Count;

        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        Result(T min, T max, std::uint64_t count);
        ~Result(void) = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Result);
    };

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    // first_element_flag is default to be true in constructor to guarantee
    // min, max and count are set based on first valid input element
    BasicStatsUpdater(void);

    void update(T input);
    // commit returns the result of min, max and count
    Result commit(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    T                                       _min;
    T                                       _max;
    std::uint64_t                           _count;
    bool                                    _first_element_flag;
};

/////////////////////////////////////////////////////////////////////////
///  \class         StandardStatsUpdater
///  \brief         StandardStatsUpdater updates advanced stats include
///                 sum and average
///
template <typename T>
class StandardStatsUpdater : public BasicStatsUpdater<T> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = BasicStatsUpdater<T>;

    /////////////////////////////////////////////////////////////////////////
    ///  \class         Result
    ///  \brief         A struct which contains the sum and average
    ///                 for an input column. Template T can only be integer and numerical types
    ///
    struct Result : public BasicStatsUpdater<T>::Result {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Types
        // |
        // ----------------------------------------------------------------------
        using BaseType                      = typename BasicStatsUpdater<T>::Result;

        // ----------------------------------------------------------------------
        // |
        // |  Public Data
        // |
        // ----------------------------------------------------------------------
        typename TypeSelector::SumTypeSelector<T>::type const               Sum;
        std::double_t                                   const               Average;

        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        Result(typename TypeSelector::SumTypeSelector<T>::type sum, std::double_t average, T min, T max, std::uint64_t count);
        ~Result(void) = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Result);
    };

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StandardStatsUpdater(void);

    void update(T input);
    // commit returns the result of min, max, count, sum and average
    Result commit(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    typename TypeSelector::SumTypeSelector<T>::type     _sum;
};

} // namespace Updaters

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         StatisticalMetricsTrainingOnlyPolicy
///  \brief         Applies statistical calculations on non-null inputs.
///
template <typename InputT, typename UpdaterT>
class StatisticalMetricsTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = InputT;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = StatisticalMetricsEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StatisticalMetricsTrainingOnlyPolicy(void);

    void fit(InputType const &input);
    typename UpdaterT::Result complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    UpdaterT                                _updater;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void fit_impl(InputType const &input, std::true_type /*is_nullable*/);
    void fit_impl(InputType const &input, std::false_type /*is_nullable*/);
};

template <typename T>
struct StatsUpdaterSelector {
    using type = Updaters::BasicStatsUpdater<T>;
};

template <>
struct StatsUpdaterSelector<std::int8_t> {
    using type = Updaters::StandardStatsUpdater<std::int8_t>;
};

template <>
struct StatsUpdaterSelector<std::uint8_t> {
    using type = Updaters::StandardStatsUpdater<std::uint8_t>;
};

template <>
struct StatsUpdaterSelector<std::int16_t> {
    using type = Updaters::StandardStatsUpdater<std::int16_t>;
};

template <>
struct StatsUpdaterSelector<std::uint16_t> {
    using type = Updaters::StandardStatsUpdater<std::uint16_t>;
};

template <>
struct StatsUpdaterSelector<std::int32_t> {
    using type = Updaters::StandardStatsUpdater<std::int32_t>;
};

template <>
struct StatsUpdaterSelector<std::uint32_t> {
    using type = Updaters::StandardStatsUpdater<std::uint32_t>;
};

template <>
struct StatsUpdaterSelector<std::int64_t> {
    using type = Updaters::StandardStatsUpdater<std::int64_t>;
};

template <>
struct StatsUpdaterSelector<std::uint64_t> {
    using type = Updaters::StandardStatsUpdater<std::uint64_t>;
};

template <>
struct StatsUpdaterSelector<std::float_t> {
    using type = Updaters::StandardStatsUpdater<std::float_t>;
};

template <>
struct StatsUpdaterSelector<std::double_t> {
    using type = Updaters::StandardStatsUpdater<std::double_t>;
};

template <typename T, bool IsNullableTypeV>
struct NonNullableTypeExtractorImpl {
    using type                              = typename std::remove_cv<typename std::remove_reference<decltype(Traits<T>::GetNullableValue(std::declval<T>()))>::type>::type;
};

template <typename T>
struct NonNullableTypeExtractorImpl<T, false> {
    using type                              = T;
};

template <typename T>
struct NonNullableTypeExtractor : public NonNullableTypeExtractorImpl<T, Traits<T>::IsNullableType> {};

} // namespace Details

// Updater itself should contain the structure of return result
// to avoid confusion for user who would expect annotation data from
// the estimator, we put using statement here
template <typename T>
using BasicStatisticalAnnotationData = typename Updaters::BasicStatsUpdater<T>::Result;

template <typename T>
using StandardStatisticalAnnotationData = typename Updaters::StandardStatsUpdater<T>::Result;

/////////////////////////////////////////////////////////////////////////
///  \typedef       StatisticalMetricsEstimator
///  \brief         A training-only class that finds the min, max
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using StatisticalMetricsEstimator =
    TrainingOnlyEstimatorImpl<
        Details::StatisticalMetricsTrainingOnlyPolicy<
            InputT,
            typename Details::StatsUpdaterSelector<
                typename Details::NonNullableTypeExtractor<InputT>::type
            >::type
        >,
        MaxNumTrainingItemsV
    >;

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Implementation
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

// ----------------------------------------------------------------------
// |
// |  Updaters::BasicStatsUpdater
// |
// ----------------------------------------------------------------------
template <typename T>
Updaters::BasicStatsUpdater<T>::BasicStatsUpdater(void) :
    _count(0),
    _first_element_flag(true) {
}

template <typename T>
Updaters::BasicStatsUpdater<T>::Result::Result(T min, T max, std::uint64_t count) :
    Min(std::move(min)),
    Max(std::move(max)),
    Count(std::move(count)) {
        if((Count != 0) && (Min > Max))
            throw std::invalid_argument("min is > max");
}

template <typename T>
void Updaters::BasicStatsUpdater<T>::update(T input) {
    // first valid input element will set min and max
    if (_first_element_flag) {
        _min = input;
        _max = input;
        _first_element_flag = false;
    } else {
        if(input < _min) {
            _min = input;
        }
        if(input > _max) {
            _max = input;
        }
    }
    // check if count will be out of bounds
    if (std::numeric_limits<std::uint64_t>::max() == _count) {
        throw std::runtime_error("Overflow occurred for count during calculating statistic metrics! Check your data!");
    }
    ++_count;
}

template <typename T>
typename Updaters::BasicStatsUpdater<T>::Result Updaters::BasicStatsUpdater<T>::commit(void) {
    if(_count == 0)
        throw std::runtime_error("No values were provided");

    assert(_min <= _max);
    return Result(std::move(_min), std::move(_max), std::move(_count));
}

// ----------------------------------------------------------------------
// |
// |  Updaters::StandardStatsUpdater
// |
// ----------------------------------------------------------------------
template <typename T>
Updaters::StandardStatsUpdater<T>::StandardStatsUpdater(void) :
    _sum(0) {
}

template <typename T>
Updaters::StandardStatsUpdater<T>::Result::Result(typename TypeSelector::SumTypeSelector<T>::type sum, std::double_t average, T min, T max, std::uint64_t count) :
    BaseType(std::move(min), std::move(max), std::move(count)),
    Sum(std::move(sum)),
    Average(std::move(average))
    {
        if(Average > BaseType::Max || Average < BaseType::Min)
            throw std::invalid_argument("average is not in the correct range");
}

template <typename T>
void Updaters::StandardStatsUpdater<T>::update(T input) {
    BasicStatsUpdater<T>::update(input);
    if (TypeSelector::SumTypeSelector<T>::IsNumeric) {
        // if sum is of type long double, check for overflows
        if ((_sum + static_cast<long double>(input) == _sum) && (input != 0)) {
            throw std::runtime_error("Input is so small comparing to sum that sum is the same after long double addition!");
        }
        _sum += static_cast<typename TypeSelector::SumTypeSelector<T>::type>(input);
        // check if out of bound
        // std::isinf is used for check long double bounds
        if (std::isinf(static_cast<long double>(_sum))) {
            throw std::runtime_error("Overflow occured for sum during calculating statistic metrics! Check your data!");
        }
    }
    else {
        // if sum is of type int64_t, check for overflow
        if ( ((input > 0) && (std::numeric_limits<std::int64_t>::max() - static_cast<std::int64_t>(input) < _sum))
         || ((input < 0) && (std::numeric_limits<std::int64_t>::lowest() - static_cast<std::int64_t>(input) > _sum))) {
            throw std::runtime_error("Overflow occured for sum during calculating statistic metrics! Check your data!");
        }
        _sum += static_cast<typename TypeSelector::SumTypeSelector<T>::type>(input);
    }
}

template <typename T>
typename Updaters::StandardStatsUpdater<T>::Result Updaters::StandardStatsUpdater<T>::commit(void) {
    typename Result::BaseType               basics(BaseType::commit());

    if (basics.Count != 0) {
        if (TypeSelector::SumTypeSelector<T>::IsNumeric) {
            // double and long double have the same size in some systems but in others, long doubles are of greater size
            // so there can be overflow when converting long double to double
            if (_sum/static_cast<long double>(basics.Count) > static_cast<long double>(std::numeric_limits<std::double_t>::max())) {
                throw std::runtime_error("double and long double are different sizes on your system, overflow encountered when calculating average!");
            }
        }
        std::double_t _average = static_cast<std::double_t>(static_cast<long double>(_sum)/static_cast<long double>(basics.Count));
        assert(basics.Min <= basics.Max);
        assert(_average >= basics.Min && _average <= basics.Max);
        return StandardStatisticalAnnotationData<T>(std::move(_sum), std::move(_average), std::move(basics.Min), std::move(basics.Max), std::move(basics.Count));
    } else {
        return StandardStatisticalAnnotationData<T>(0,0,0,0,0);
    }
}

// ----------------------------------------------------------------------
// |
// |  Details::StatisticalMetricsTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename InputT, typename UpdaterT>
Details::StatisticalMetricsTrainingOnlyPolicy<InputT, UpdaterT>::StatisticalMetricsTrainingOnlyPolicy(void) {
}

template <typename InputT, typename UpdaterT>
void Details::StatisticalMetricsTrainingOnlyPolicy<InputT, UpdaterT>::fit(InputType const &input) {
    fit_impl(input, std::integral_constant<bool, Microsoft::Featurizer::Traits<InputT>::IsNullableType>());
}

template <typename InputT, typename UpdaterT>
typename UpdaterT::Result Details::StatisticalMetricsTrainingOnlyPolicy<InputT, UpdaterT>::complete_training(void) {
    return _updater.commit();
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename UpdaterT>
void Details::StatisticalMetricsTrainingOnlyPolicy<InputT, UpdaterT>::fit_impl(InputType const &input, std::true_type /*is_nullable*/) {
    // ----------------------------------------------------------------------
    using TheseTraits                       = Microsoft::Featurizer::Traits<InputT>;
    // ----------------------------------------------------------------------

    if(TheseTraits::IsNull(input))
        return;

    _updater.update(TheseTraits::GetNullableValue(input));
}

template <typename InputT, typename UpdaterT>
void Details::StatisticalMetricsTrainingOnlyPolicy<InputT, UpdaterT>::fit_impl(InputType const &input, std::false_type /*is_nullable*/) {
    _updater.update(input);
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
