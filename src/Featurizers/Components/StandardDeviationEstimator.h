// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>

#include "TrainingOnlyEstimatorImpl.h"
#include "../../Traits.h"
#include "NormUpdaters.h"
#include "StatisticalMetricsEstimator.h"
namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

static constexpr char const * const         StandardDeviationEstimatorName("StandardDeviationEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         StandardDeviationAnnotationData
///  \brief         An annotation class which contains the standard deviation and count of input elements
///                 for an input column
///
class StandardDeviationAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    long double   const StandardDeviation;
    std::uint64_t const Count;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StandardDeviationAnnotationData(long double standard_deviation, std::uint64_t count);
    ~StandardDeviationAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StandardDeviationAnnotationData);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         StandardDeviationTrainingOnlyPolicy
///  \brief         `StandardDeviationTrainingOnlyPolicy` implementation details.
///
template <typename T, typename EstimatorT>
class StandardDeviationTrainingOnlyPolicy {
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
    static constexpr char const * const     NameValue = StandardDeviationEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    // this constructor is used for StandardDeviationEstimator following StatisticalMetricsEstimator
    // which will retrieve average from AnnotationMap
    StandardDeviationTrainingOnlyPolicy(void);
    // this constructor is used for user inputs a specific average
    StandardDeviationTrainingOnlyPolicy(std::double_t average);

    bool begin_training(AnnotationMap const &annotations);
    void fit(InputType const &input);
    StandardDeviationAnnotationData complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    Updaters::L2NormUpdater<std::double_t>    _updater;
    std::double_t                             _average;
    std::uint64_t                             _count;
    // this flag is to mark if user input a specific average
    bool                                      _user_average_flag;
};

} // namespace Details



/////////////////////////////////////////////////////////////////////////
///  \typedef       StandardDeviationEstimator
///  \brief         A training-only class that calculate standard deviation based on
///                 average and count
///
template <
    typename T,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class StandardDeviationEstimator :
    public TrainingOnlyEstimatorImpl<
        Details::StandardDeviationTrainingOnlyPolicy<
            T,
            StandardDeviationEstimator<T, MaxNumTrainingItemsV>
        >,
        MaxNumTrainingItemsV
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        TrainingOnlyEstimatorImpl<
            Details::StandardDeviationTrainingOnlyPolicy<
                T,
                StandardDeviationEstimator<T, MaxNumTrainingItemsV>
            >,
            MaxNumTrainingItemsV
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StandardDeviationEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    StandardDeviationEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, std::double_t average);

    ~StandardDeviationEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StandardDeviationEstimator);
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
// |  StandardDeviationAnnotationData
// |
// ----------------------------------------------------------------------

StandardDeviationAnnotationData::StandardDeviationAnnotationData(long double standard_deviation, std::uint64_t count) :
    StandardDeviation(std::move(standard_deviation)),
    Count(std::move(count)) {
        if (StandardDeviation < 0) {
            throw std::invalid_argument("Standard deviation shouldn't be less than 0!");
        }
        if ((Count == 0) && (StandardDeviation != 0)) {
            throw std::invalid_argument("Standard deviation is not 0 when count is 0!");
        }
}

// ----------------------------------------------------------------------
// |
// |  StandardDeviationEstimator
// |
// ----------------------------------------------------------------------
template <typename T, size_t MaxNumTrainingItemsV>
StandardDeviationEstimator<T, MaxNumTrainingItemsV>::StandardDeviationEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex)) {
}

template <typename T, size_t MaxNumTrainingItemsV>
StandardDeviationEstimator<T, MaxNumTrainingItemsV>::StandardDeviationEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, std::double_t average) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex), true, std::move(average)) {
}

// ----------------------------------------------------------------------
// |
// |  Details::StandardDeviationTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T, typename StandardDeviationEstimatorT>
Details::StandardDeviationTrainingOnlyPolicy<T, StandardDeviationEstimatorT>::StandardDeviationTrainingOnlyPolicy(void) :
    _updater(Updaters::L2NormUpdater<std::double_t>()),
    _average(0),
    _count(0),
    _user_average_flag(false) {
}

template <typename T, typename StandardDeviationEstimatorT>
Details::StandardDeviationTrainingOnlyPolicy<T, StandardDeviationEstimatorT>::StandardDeviationTrainingOnlyPolicy(std::double_t average) :
    _updater(Updaters::L2NormUpdater<std::double_t>()),
    _average(std::move(average)),
    _count(0),
    _user_average_flag(true) {
}

template <typename T, typename StandardDeviationEstimatorT>
bool Details::StandardDeviationTrainingOnlyPolicy<T, StandardDeviationEstimatorT>::begin_training(AnnotationMap const &) {
    // if user doesn't specify an average value, retrieve the StatisticalMetricsEstimator annotation to get average and count
    if (!_user_average_flag) {
        // ----------------------------------------------------------------------
        using StandardStatisticalAnnotationData            = Components::StandardStatisticalAnnotationData<T>;
        using StatisticalMetricsEstimator                  = Components::StatisticalMetricsEstimator<T, StandardDeviationEstimatorT::MaxNumTrainingItems>;
        // ----------------------------------------------------------------------

        StandardDeviationEstimatorT       const &          estimator(static_cast<StandardDeviationEstimatorT const &>(*this));
        StandardStatisticalAnnotationData const &          data(StatisticalMetricsEstimator::get_annotation_data(estimator.get_column_annotations(), estimator.get_column_index(), StatisticalMetricsEstimatorName));

        _average = data.Average;
    }
    return true;
}

template <typename T, typename StandardDeviationEstimatorT>
void Details::StandardDeviationTrainingOnlyPolicy<T, StandardDeviationEstimatorT>::fit(InputType const &input) {
    // TODO: Implement different strategies for dealing with null
    if(Microsoft::Featurizer::Traits<T>::IsNull(input))
        return;
    _updater.update(static_cast<std::double_t>(input) - _average);
    // check if count will be out of bounds
    if (std::numeric_limits<std::uint64_t>::max() == _count) {
        throw std::runtime_error("Overflow occured for count during calculating standard deviation! You might input too much data");
    }
    ++_count;
}

template <typename T, typename StandardDeviationEstimatorT>
StandardDeviationAnnotationData Details::StandardDeviationTrainingOnlyPolicy<T, StandardDeviationEstimatorT>::complete_training(void) {
    long double deviation = _updater.commit()/std::sqrt(static_cast<long double>(_count));
    assert(deviation >= 0);
    return StandardDeviationAnnotationData(std::move(deviation), std::move(_count));
}


#if (defined __clang__)
#   pragma clang diagnostic pop
#endif


}
}
}
}
