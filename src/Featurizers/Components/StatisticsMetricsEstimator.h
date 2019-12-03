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

/////////////////////////////////////////////////////////////////////////
///  \class         BasicStatisticalAnnotationData
///  \brief         An annotation class which contains the min, max and count
///                 for an input column. Template T can be all types
///
template <typename T>
class BasicStatisticalAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    T             const                           Min;
    T             const                           Max;
    std::uint64_t  const                          Count;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    BasicStatisticalAnnotationData(T min, T max, std::uint64_t count);
    ~BasicStatisticalAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(BasicStatisticalAnnotationData);
};

/////////////////////////////////////////////////////////////////////////
///  \class         StandardStatisticalAnnotaionData
///  \brief         An annotation class which contains the sum and average
///                 for an input column. Template T can only be numerical types
///
template <typename T>
class StandardStatisticalAnnotaionData : public BasicStatisticalAnnotationData<T> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    long double   const                            Sum;
    std::double_t const                            Average;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StandardStatisticalAnnotaionData(long double sum, std::double_t average, T min, T max, std::uint64_t count);
    ~StandardStatisticalAnnotaionData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StandardStatisticalAnnotaionData);
};

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
    BasicStatisticalAnnotationData<T> complete_training(void);
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
    StandardStatisticalAnnotaionData<T> complete_training(void);
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    long double                               _sum;
    std::double_t                             _average;
    InputType                                 _min;
    InputType                                 _max;
    std::uint64_t                             _count;
    bool                                      _first_element_flag;
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

// ----------------------------------------------------------------------
// |
// |  BasicStatisticalAnnotationData
// |
// ----------------------------------------------------------------------
template <typename T>
BasicStatisticalAnnotationData<T>::BasicStatisticalAnnotationData(T min, T max, std::uint64_t count) :
    Min(std::move(min)),
    Max(std::move(max)),
    Count(std::move(count)) {
        if(Min > Max)
            throw std::invalid_argument("min is > max");

}

// ----------------------------------------------------------------------
// |
// |  StandardStatisticalAnnotaionData
// |
// ----------------------------------------------------------------------
template <typename T>
StandardStatisticalAnnotaionData<T>::StandardStatisticalAnnotaionData(long double sum, std::double_t average, T min, T max, std::uint64_t count) :
    BasicStatisticalAnnotationData<T>(min, max, count),
    Sum(std::move(sum)),
    Average(std::move(average))
    {
        assert(Microsoft::Featurizer::Traits<T>::IsNumericalType::value);
        if(Average > BasicStatisticalAnnotationData<T>::Max || Average < BasicStatisticalAnnotationData<T>::Min)
            throw std::invalid_argument("average is not in the correct range");
}

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

// ----------------------------------------------------------------------
// |
// |  update functions
// |
// ----------------------------------------------------------------------

template <typename T>
void update_basic_statistics(T input, T& min, T& max, std::uint64_t& count, bool& first_element_flag) {
    // first non-null element will set min and max
    if (first_element_flag) {
        min = input;
        max = input;
        ++count;
        first_element_flag = false;
        return;
    }
    if(input < min) {
        min = input;
    }
    if(input > max) {
        max = input;
    }
    // check if count will be out of bounds
    if (std::numeric_limits<std::uint64_t>::max() == count) {
        throw std::runtime_error("Overflow occured for count during calculating statistic metrics! Check your data!");
    }
    ++count;
    return;
}

template <typename T>
void update_standard_statistics(T input, long double& sum) {
    if ((sum + static_cast<long double>(input) == sum) && (input != 0)) {
        throw std::runtime_error("Input is so small comparing to sum that sum is the same after long double addition!");
    }
    sum += static_cast<long double>(input);
    // check if out of bound
    // std::isinf is used for check long double bounds
    if (std::isinf(sum)) {
        throw std::runtime_error("Overflow occured for sum during calculating statistic metrics! Check your data!");
    }
    return;
}

// ----------------------------------------------------------------------
// |
// |  Details::BasicStatsTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::BasicStatsTrainingOnlyPolicy<T>::BasicStatsTrainingOnlyPolicy(void) :
    _count(0),
    _first_element_flag(true) {
}



template <typename T>
void Details::BasicStatsTrainingOnlyPolicy<T>::fit(InputType const &input) {
    if(Microsoft::Featurizer::Traits<T>::IsNull(input))
        return;
    update_basic_statistics(input, _min, _max, _count, _first_element_flag);

}

template <typename T>
BasicStatisticalAnnotationData<T> Details::BasicStatsTrainingOnlyPolicy<T>::complete_training(void) {
    if (_count != 0) {
        assert(_min<=_max);
    }
    return BasicStatisticalAnnotationData<T>(std::move(_min), std::move(_max), std::move(_count));

}


// ----------------------------------------------------------------------
// |
// |  Details::StandardStatsTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::StandardStatsTrainingOnlyPolicy<T>::StandardStatsTrainingOnlyPolicy(void) :
    _sum(0),
    _average(0),
    _min(0),
    _max(0),
    _count(0),
    _first_element_flag(true) {
}

template <typename T>
void Details::StandardStatsTrainingOnlyPolicy<T>::fit(InputType const &input) {
    if(Microsoft::Featurizer::Traits<T>::IsNull(input))
        return;
    update_basic_statistics(input, _min, _max, _count, _first_element_flag);
    update_standard_statistics(input, _sum);
}

template <typename T>
StandardStatisticalAnnotaionData<T> Details::StandardStatsTrainingOnlyPolicy<T>::complete_training(void) {
    if (_count != 0) {
        // double and long double have the same size in some systems but in others, long doubles are of greater size
        // so there can be overflow when converting long double to double
        if (_sum/static_cast<long double>(_count) > static_cast<long double>(std::numeric_limits<std::double_t>::max())) {
            throw std::runtime_error("double and long double are different sizes on your system, overflow encountered when calculating average!");
        }
        _average = static_cast<std::double_t>(_sum/static_cast<long double>(_count));
        assert(_min<=_max);
        assert(_average >= _min && _average <= _max);
    }
    return StandardStatisticalAnnotaionData<T>(std::move(_sum), std::move(_average), std::move(_min), std::move(_max), std::move(_count));
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
