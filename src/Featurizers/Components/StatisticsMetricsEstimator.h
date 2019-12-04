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
    std::uint64_t const                           Count;

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
    typename TypeSelector::SumTypeSelector<T>::type   const                            Sum;
    std::double_t                                     const                            Average;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StandardStatisticalAnnotaionData(typename TypeSelector::SumTypeSelector<T>::type sum, std::double_t average, T min, T max, std::uint64_t count);
    ~StandardStatisticalAnnotaionData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StandardStatisticalAnnotaionData);
};

namespace Details {
/////////////////////////////////////////////////////////////////////////
///  \class         BasicStatsUpdater
///  \brief         BasicStatsUpdater updates basic stats include
///                 min, max and count
///
template <typename T>
class BasicStatsUpdater {
public:
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
    std::tuple<InputType, InputType, std::uint64_t> commit(void);
protected:
    // ----------------------------------------------------------------------
    // |
    // |  Protected Data
    // |
    // ----------------------------------------------------------------------
    InputType                                 _min;
    InputType                                 _max;
    std::uint64_t                             _count;
    bool                                      _first_element_flag;
};
/////////////////////////////////////////////////////////////////////////
///  \class         StandardStatsTrainingOnlyPolicy
///  \brief         StandardStatsTrainingOnlyPolicy updates advanced stats include
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
    using InputType                         = T;


    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StandardStatsUpdater(void);

    void update(InputType input);
    // commit returns the result of min, max, count, sum and average
    std::tuple<typename TypeSelector::SumTypeSelector<T>::type, std::double_t, InputType, InputType, std::uint64_t> commit(void);
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    typename TypeSelector::SumTypeSelector<T>::type                               _sum;
};


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
protected:
    // ----------------------------------------------------------------------
    // |
    // |  Protected Data
    // |
    // ----------------------------------------------------------------------
    BasicStatsUpdater<T>                         _updater;
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
    StandardStatsUpdater<T>                      _updater;
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
StandardStatisticalAnnotaionData<T>::StandardStatisticalAnnotaionData(typename TypeSelector::SumTypeSelector<T>::type sum, std::double_t average, T min, T max, std::uint64_t count) :
    BasicStatisticalAnnotationData<T>(std::move(min), std::move(max), std::move(count)),
    Sum(std::move(sum)),
    Average(std::move(average))
    {
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
// |  Details::BasicStatsUpdater
// |
// ----------------------------------------------------------------------
template <typename T>
Details::BasicStatsUpdater<T>::BasicStatsUpdater(void) :
    _count(0),
    _first_element_flag(true) {
}


template <typename T>
void Details::BasicStatsUpdater<T>::update(T input) {
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
std::tuple<T, T, std::uint64_t> Details::BasicStatsUpdater<T>::commit(void) {
    if(_count != 0) {
        assert(_min <= _max);
    }
    return std::tuple<T, T, std::uint64_t>(_min, _max, _count);
}

// ----------------------------------------------------------------------
// |
// |  Details::StandardStatsUpdater
// |
// ----------------------------------------------------------------------
template <typename T>
Details::StandardStatsUpdater<T>::StandardStatsUpdater(void) :
    _sum(0) {
}

template <typename T>
void Details::StandardStatsUpdater<T>::update(T input) {
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
std::tuple<typename TypeSelector::SumTypeSelector<T>::type, std::double_t, T, T, std::uint64_t> Details::StandardStatsUpdater<T>::commit(void) {
    if (BasicStatsUpdater<T>::_count != 0) {
        if (TypeSelector::SumTypeSelector<T>::IsNumeric) {
            // double and long double have the same size in some systems but in others, long doubles are of greater size
            // so there can be overflow when converting long double to double
            if (_sum/static_cast<long double>(BasicStatsUpdater<T>::_count) > static_cast<long double>(std::numeric_limits<std::double_t>::max())) {
                throw std::runtime_error("double and long double are different sizes on your system, overflow encountered when calculating average!");
            }
        }
        std::double_t _average = static_cast<std::double_t>(static_cast<long double>(_sum)/static_cast<long double>(BasicStatsUpdater<T>::_count));
        assert(BasicStatsUpdater<T>::_min<=BasicStatsUpdater<T>::_max);
        assert(_average >= BasicStatsUpdater<T>::_min && _average <= BasicStatsUpdater<T>::_max);
        return std::tuple<typename TypeSelector::SumTypeSelector<T>::type, std::double_t, T, T, std::uint64_t>(_sum, _average, BasicStatsUpdater<T>::_min, BasicStatsUpdater<T>::_max, BasicStatsUpdater<T>::_count);
    } else {
        return std::tuple<typename TypeSelector::SumTypeSelector<T>::type, std::double_t, T, T, std::uint64_t>(0,0,0,0,0);
    }

}

// ----------------------------------------------------------------------
// |
// |  Details::BasicStatsTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::BasicStatsTrainingOnlyPolicy<T>::BasicStatsTrainingOnlyPolicy(void) :
    _updater(BasicStatsUpdater<T>()) {
}

template <typename T>
void Details::BasicStatsTrainingOnlyPolicy<T>::fit(InputType const &input) {
    if(Microsoft::Featurizer::Traits<T>::IsNull(input))
        return;
    _updater.update(input);

}

template <typename T>
BasicStatisticalAnnotationData<T> Details::BasicStatsTrainingOnlyPolicy<T>::complete_training(void) {
    std::tuple<T, T, std::uint64_t> ret = _updater.commit();
    return BasicStatisticalAnnotationData<T>(std::move(std::get<0>(ret)), std::move(std::get<1>(ret)), std::move(std::get<2>(ret)));
}

// ----------------------------------------------------------------------
// |
// |  Details::StandardStatsTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::StandardStatsTrainingOnlyPolicy<T>::StandardStatsTrainingOnlyPolicy(void) :
    _updater(StandardStatsUpdater<T>()) {
}

template <typename T>
void Details::StandardStatsTrainingOnlyPolicy<T>::fit(InputType const &input) {
    if(Microsoft::Featurizer::Traits<T>::IsNull(input))
        return;
    _updater.update(input);
}

template <typename T>
StandardStatisticalAnnotaionData<T> Details::StandardStatsTrainingOnlyPolicy<T>::complete_training(void) {
    std::tuple<typename TypeSelector::SumTypeSelector<T>::type, std::double_t, T, T, std::uint64_t> ret = _updater.commit();
    return StandardStatisticalAnnotaionData<T>(std::move(std::get<0>(ret)), std::move(std::get<1>(ret)), std::move(std::get<2>(ret)), std::move(std::get<3>(ret)), std::move(std::get<4>(ret)));
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
