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

}

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
    ///  \class         BasicResult
    ///  \brief         A structure which contains the min, max and count
    ///                 for an input column. Template T can be all types
    ///
    struct BasicResult {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Data
        // |
        // ----------------------------------------------------------------------
        T             const                           Min;
        T             const                           Max;
        std::uint64_t const                           Count;

        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        BasicResult(T min, T max, std::uint64_t count);
        ~BasicResult(void) = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(BasicResult);
    };

    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = T;


    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    // first_element_flag is default to be true in constructor to guarantee
    // min, max and count are set based on first valid input element
    BasicStatsUpdater(void);

    void update(InputType input);
    // commit returns the result of min, max and count
    BasicResult commit(void);
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    InputType                                 _min;
    InputType                                 _max;
    std::uint64_t                             _count;
    bool                                      _first_element_flag;
};
/////////////////////////////////////////////////////////////////////////
///  \class         StandardStatsUpdater
///  \brief         StandardStatsUpdater updates advanced stats include
///                 sum and average
///
template <typename T>
class StandardStatsUpdater : public BasicStatsUpdater<T> {
public:
    /////////////////////////////////////////////////////////////////////////
    ///  \class         StandardResult
    ///  \brief         A struct which contains the sum and average
    ///                 for an input column. Template T can only be integer and numerical types
    ///
    struct StandardResult : public BasicStatsUpdater<T>::BasicResult {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Data
        // |
        // ----------------------------------------------------------------------
        typename TypeSelector::SumTypeSelector<T>::type   const                            Sum;
        std::double_t                                     const                            Average;

        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        StandardResult(typename TypeSelector::SumTypeSelector<T>::type sum, std::double_t average, T min, T max, std::uint64_t count);
        ~StandardResult(void) = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StandardResult);
    };
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = T;


    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StandardStatsUpdater(void);

    void update(InputType input);
    // commit returns the result of min, max, count, sum and average
    StandardResult commit(void);
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    typename TypeSelector::SumTypeSelector<T>::type                               _sum;
};
}

namespace Details {
/////////////////////////////////////////////////////////////////////////
///  \class         BasicStatsTrainingOnlyPolicy
///  \brief         BasicStatsTrainingOnlyPolicy deals with basic stats include
///                 min, max and count
///
template <typename T>
class BasicStatsTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = T;

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
    BasicStatsTrainingOnlyPolicy(void);

    void fit(InputType const &input);
    typename Updaters::BasicStatsUpdater<T>::BasicResult complete_training(void);
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    Updaters::BasicStatsUpdater<T>                         _updater;
};

/////////////////////////////////////////////////////////////////////////
///  \class         StandardStatsTrainingOnlyPolicy
///  \brief         StandardStatsTrainingOnlyPolicy deals with advanced stats include
///                 sum and average
///
template <typename T>
class StandardStatsTrainingOnlyPolicy : public BasicStatsTrainingOnlyPolicy<T> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = T;

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
    StandardStatsTrainingOnlyPolicy(void);

    void fit(InputType const &input);
    typename Updaters::StandardStatsUpdater<T>::StandardResult complete_training(void);
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    Updaters::StandardStatsUpdater<T>                      _updater;
};

template <typename T>
struct StatsPolicySelector {
    using type = BasicStatsTrainingOnlyPolicy<T>;
};

template <>
struct StatsPolicySelector<std::int8_t> {
    using type = StandardStatsTrainingOnlyPolicy<std::int8_t>;
};

template <>
struct StatsPolicySelector<std::uint8_t> {
    using type = StandardStatsTrainingOnlyPolicy<std::uint8_t>;
};

template <>
struct StatsPolicySelector<std::int16_t> {
    using type = StandardStatsTrainingOnlyPolicy<std::int16_t>;
};

template <>
struct StatsPolicySelector<std::uint16_t> {
    using type = StandardStatsTrainingOnlyPolicy<std::uint16_t>;
};

template <>
struct StatsPolicySelector<std::int32_t> {
    using type = StandardStatsTrainingOnlyPolicy<std::int32_t>;
};

template <>
struct StatsPolicySelector<std::uint32_t> {
    using type = StandardStatsTrainingOnlyPolicy<std::uint32_t>;
};

template <>
struct StatsPolicySelector<std::int64_t> {
    using type = StandardStatsTrainingOnlyPolicy<std::int64_t>;
};

template <>
struct StatsPolicySelector<std::uint64_t> {
    using type = StandardStatsTrainingOnlyPolicy<std::uint64_t>;
};

template <>
struct StatsPolicySelector<std::float_t> {
    using type = StandardStatsTrainingOnlyPolicy<std::float_t>;
};

template <>
struct StatsPolicySelector<std::double_t> {
    using type = StandardStatsTrainingOnlyPolicy<std::double_t>;
};

} // namespace Details

// Updater itself should contain the structure of return result
// to avoid confusion for user who would expect annotation data from
// the estimator, we put using statement here
template <typename T>
using BasicStatisticalAnnotationData = typename Updaters::BasicStatsUpdater<T>::BasicResult;
template <typename T>
using StandardStatisticalAnnotationData = typename Updaters::StandardStatsUpdater<T>::StandardResult;


/////////////////////////////////////////////////////////////////////////
///  \typedef       StatisticalMetricsEstimator
///  \brief         A training-only class that finds the min, max
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using StatisticalMetricsEstimator                       = TrainingOnlyEstimatorImpl<typename Details::StatsPolicySelector<InputT>::type, MaxNumTrainingItemsV>;

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
Updaters::BasicStatsUpdater<T>::BasicResult::BasicResult(T min, T max, std::uint64_t count) :
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
        throw std::runtime_error("Overflow occured for count during calculating statistic metrics! Check your data!");
    }
    ++_count;
}

template <typename T>
typename Updaters::BasicStatsUpdater<T>::BasicResult Updaters::BasicStatsUpdater<T>::commit(void) {
    if(_count != 0) {
        assert(_min <= _max);
    }
    return BasicStatisticalAnnotationData<T>(std::move(_min), std::move(_max), std::move(_count));
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
Updaters::StandardStatsUpdater<T>::StandardResult::StandardResult(typename TypeSelector::SumTypeSelector<T>::type sum, std::double_t average, T min, T max, std::uint64_t count) :
    Updaters::BasicStatsUpdater<T>::BasicResult(std::move(min), std::move(max), std::move(count)),
    Sum(std::move(sum)),
    Average(std::move(average))
    {
        if(Average > BasicStatisticalAnnotationData<T>::Max || Average < BasicStatisticalAnnotationData<T>::Min)
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
typename Updaters::StandardStatsUpdater<T>::StandardResult Updaters::StandardStatsUpdater<T>::commit(void) {
    BasicStatisticalAnnotationData<T> basics = BasicStatsUpdater<T>::commit();
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
// |  Details::BasicStatsTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::BasicStatsTrainingOnlyPolicy<T>::BasicStatsTrainingOnlyPolicy(void) :
    _updater(Updaters::BasicStatsUpdater<T>()) {
}

template <typename T>
void Details::BasicStatsTrainingOnlyPolicy<T>::fit(InputType const &input) {
    if(Microsoft::Featurizer::Traits<T>::IsNull(input))
        return;
    _updater.update(input);

}

template <typename T>
BasicStatisticalAnnotationData<T> Details::BasicStatsTrainingOnlyPolicy<T>::complete_training(void) {
    return _updater.commit();
}

// ----------------------------------------------------------------------
// |
// |  Details::StandardStatsTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::StandardStatsTrainingOnlyPolicy<T>::StandardStatsTrainingOnlyPolicy(void) :
    _updater(Updaters::StandardStatsUpdater<T>()) {
}

template <typename T>
void Details::StandardStatsTrainingOnlyPolicy<T>::fit(InputType const &input) {
    if(Microsoft::Featurizer::Traits<T>::IsNull(input))
        return;
    _updater.update(input);
}

template <typename T>
StandardStatisticalAnnotationData<T> Details::StandardStatsTrainingOnlyPolicy<T>::complete_training(void) {
    return _updater.commit();
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
