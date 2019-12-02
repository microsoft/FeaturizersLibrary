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
class StandardStatisticalAnnotaionData : BasicStatisticalAnnotationData {
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
///  \class         StatisticalMetricsTrainingOnlyPolicy
///  \brief         `StatisticalMetricsEstimator` implementation details.
///
template <typename T>
class StatisticalMetricsTrainingOnlyPolicy {
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
    StatisticalMetricsTrainingOnlyPolicy(void);

    void fit(InputType const &input);
    StatisticalMetricsAnnotationData<T> complete_training(void);

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

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \typedef       StatisticalMetricsEstimator
///  \brief         A training-only class that finds the min, max
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using StatisticalMetricsEstimator                       = TrainingOnlyEstimatorImpl<Details::StatisticalMetricsTrainingOnlyPolicy<InputT>, MaxNumTrainingItemsV>;

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
// |  StatisticalMetricsAnnotationData
// |
// ----------------------------------------------------------------------
template <typename T>
StatisticalMetricsAnnotationData<T>::StatisticalMetricsAnnotationData(long double sum, std::double_t average, T min, T max, std::uint64_t count) :
    Sum(std::move(sum)),
    Average(std::move(average)),
    Min(std::move(min)),
    Max(std::move(max)),
    Count(std::move(count)) {
        if(Min > Max)
            throw std::invalid_argument("min is > max");
        if(Average > Max || Average < Min)
            throw std::invalid_argument("average is not in the correct range");

}
StatisticalMetricsAnnotationData<std::string>::StatisticalMetricsAnnotationData(std::string min, std::string max, std::uint64_t count) :
    Min(std::move(min)),
    Max(std::move(max)),
    Count(std::move(count)) {
        if(Min > Max)
            throw std::invalid_argument("min is > max");

}

// ----------------------------------------------------------------------
// |
// |  Details::StatisticalMetricsTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::StatisticalMetricsTrainingOnlyPolicy<T>::StatisticalMetricsTrainingOnlyPolicy(void) :
    // default values are 0
    _sum(0),
    _average(0),
    _min(0),
    _max(0),
    _count(0),
    _first_element_flag(true) {
}
template <>
Details::StatisticalMetricsTrainingOnlyPolicy<std::string>::StatisticalMetricsTrainingOnlyPolicy(void) :
    _min(""),
    _max(""),
    _count(0),
    _first_element_flag(true) {
}


#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

template <typename T>
void update_statistics(T input, T& min, T& max, std::uint64_t& count, long double& sum, bool& first_element_flag) {
    // first non-null element will set min and max
    // if there is no valid element, min and max will be 0
    if (first_element_flag) {
        min = input;
        max = input;
        sum += static_cast<long double>(input);
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
    if ((sum + static_cast<long double>(input) == sum) && (input != 0)) {
        throw std::runtime_error("Input is so small comparing to sum that sum is the same after long double addition!");
    }
    sum += static_cast<long double>(input);
    // check if out of bound
    // std::isinf is used for check long double bounds
    if (std::isinf(sum)) {
        throw std::runtime_error("Overflow occured for sum during calculating statistic metrics! Check your data!");
    }
    // check if count will be out of bounds
    if (std::numeric_limits<std::uint64_t>::max() == count) {
        throw std::runtime_error("Overflow occured for count during calculating statistic metrics! Check your data!");
    }
    ++count;
    return;
}

void update_string_statistics(std::string input, std::string& min, std::string& max, std::uint64_t& count, bool& first_element_flag) {
    // first non-null element will set min and max
    // if there is no valid element, min and max will be 0
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
void Details::StatisticalMetricsTrainingOnlyPolicy<T>::fit(InputType const &input) {
    if(Microsoft::Featurizer::Traits<T>::IsNull(input))
        return;
    update_statistics(input, _min, _max, _count, _sum, _first_element_flag);
}
template <>
void Details::StatisticalMetricsTrainingOnlyPolicy<std::string>::fit(std::string const &input) {
    update_string_statistics(input, _min, _max, _count, _first_element_flag);
}

template <typename T>
StatisticalMetricsAnnotationData<T> Details::StatisticalMetricsTrainingOnlyPolicy<T>::complete_training(void) {
    if (_count != 0) {
        // double and long double have the same size in some systems but in others, long doubles are of greater size
        // so there can be overflow when converting long double to double
        if (_sum/static_cast<long double>(_count) > static_cast<long double>(std::numeric_limits<std::double_t>::max())) {
            throw std::runtime_error("double and long double are different sizes on your system, overflow encountered when calculating average!");
        }
        _average = static_cast<std::double_t>(_sum/static_cast<long double>(_count));
        assert(_min<=_max);
        assert(_average >= _min && _average <= _max);
    } else {
        // no input is taken
        assert(_min == 0);
        assert(_max == 0);
        assert(_count == 0);
        assert(_sum == 0);
        assert(_average == 0);
    }
    return StatisticalMetricsAnnotationData<T>(std::move(_sum), std::move(_average), std::move(_min), std::move(_max), std::move(_count));
}
template <>
StatisticalMetricsAnnotationData<std::string> Details::StatisticalMetricsTrainingOnlyPolicy<std::string>::complete_training(void) {
    if (_count != 0) {
        assert(_min<=_max);
    } else {
        // no input is taken
        assert(_min == "");
        assert(_max == "");
        assert(_count == 0);
    }
    return StatisticalMetricsAnnotationData<std::string>(std::move(_min), std::move(_max), std::move(_count));
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
