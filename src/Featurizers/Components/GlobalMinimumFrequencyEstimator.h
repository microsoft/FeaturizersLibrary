// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>

#include "TrainingOnlyEstimatorImpl.h"
#include "FrequencyEstimator.h"
#include "GrainFeaturizerImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

// TODO: This should be removed in favor of the StatisticalMetricsEstimator

static constexpr char const * const         GlobalMinimumFrequencyEstimatorName("GlobalMinimumFrequencyEstimator");
static constexpr char const * const         GrainedFrequencyEstimatorName("GrainedFrequencyEstimator");

using GrainedFrequencyEstimator = GrainEstimatorImpl<std::string, FrequencyEstimator<>>;

/////////////////////////////////////////////////////////////////////////
///  \class         GlobalMinimumFrequencyAnnotation
///  \brief         This is an annotation class which holds the frequency
///                 of TimeSeries
///
class GlobalMinimumFrequencyAnnotation{
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using FrequencyType                     = std::chrono::system_clock::duration;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    FrequencyType                           Value;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    GlobalMinimumFrequencyAnnotation(FrequencyType value);
    ~GlobalMinimumFrequencyAnnotation(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(GlobalMinimumFrequencyAnnotation);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         GlobalMinimumFrequencyTrainingOnlyPolicy
///  \brief         `GlobalMinimumFrequencyEstimator` implementation details.
///
template <typename EstimatorT>
class GlobalMinimumFrequencyTrainingOnlyPolicy {
public:

    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                     = std::tuple<std::string, std::chrono::system_clock::time_point>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = GlobalMinimumFrequencyEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    GlobalMinimumFrequencyTrainingOnlyPolicy(void);

    void fit(InputType const &input);
    GlobalMinimumFrequencyAnnotation complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using FrequencyType                     = std::chrono::system_clock::duration;
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    GrainedFrequencyEstimator                      _estimator;
};
}
/////////////////////////////////////////////////////////////////////////
///  \typedef       GlobalMinimumFrequencyEstimator
///  \brief         A training-only class that finds the min, max
///
template <
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class GlobalMinimumFrequencyEstimator :
    public TrainingOnlyEstimatorImpl<
        Details::GlobalMinimumFrequencyTrainingOnlyPolicy<GlobalMinimumFrequencyEstimator<MaxNumTrainingItemsV>>,
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
            Details::GlobalMinimumFrequencyTrainingOnlyPolicy<GlobalMinimumFrequencyEstimator<MaxNumTrainingItemsV>>,
            MaxNumTrainingItemsV
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    GlobalMinimumFrequencyEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);

    ~GlobalMinimumFrequencyEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(GlobalMinimumFrequencyEstimator);

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
// |  GlobalMinimumFrequencyAnnotation
// |
// ----------------------------------------------------------------------
inline GlobalMinimumFrequencyAnnotation::GlobalMinimumFrequencyAnnotation(GlobalMinimumFrequencyAnnotation::FrequencyType value) :
    Value(std::move(value)) {
}

// ----------------------------------------------------------------------
// |
// |  GlobalMinimumFrequencyEstimator
// |
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
GlobalMinimumFrequencyEstimator<MaxNumTrainingItemsV>::GlobalMinimumFrequencyEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex)) {
}

// ----------------------------------------------------------------------
// |
// |  Details::GlobalMinimumFrequencyTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename EstimatorT>
Details::GlobalMinimumFrequencyTrainingOnlyPolicy<EstimatorT>::GlobalMinimumFrequencyTrainingOnlyPolicy(void) :
    _estimator(
        GrainedFrequencyEstimatorName,
        std::make_shared<AnnotationMaps>(
            [this]() {
                EstimatorT const & estimator(static_cast<EstimatorT const &>(*this));
                return estimator.get_column_annotations();
            }()
        ),
        //std::make_shared<AnnotationMaps>(estimator.get_column_annotations()),
        [](AnnotationMapsPtr pAllColumnAnnotationsParam) {
            return FrequencyEstimator<>(std::move(pAllColumnAnnotationsParam), 0);
        }
    )
 {
    _estimator.begin_training();
}

template <typename EstimatorT>
void Details::GlobalMinimumFrequencyTrainingOnlyPolicy<EstimatorT>::fit(InputType const &input) {
    _estimator.fit(input);
}

template <typename EstimatorT>
GlobalMinimumFrequencyAnnotation Details::GlobalMinimumFrequencyTrainingOnlyPolicy<EstimatorT>::complete_training(void) {
    _estimator.complete_training();
    GrainEstimatorAnnotation<std::string> const & data(GrainedFrequencyEstimator::get_annotation(_estimator.get_column_annotations(), 0, GrainedFrequencyEstimatorName));

    GrainEstimatorAnnotation<std::string>::AnnotationMap annotation(data.Annotations);

    FrequencyType freq(std::chrono::system_clock::duration::max().count());
    for (auto it = annotation.begin(); it != annotation.end(); it++) {
        FrequencyType f(FrequencyEstimator<>::get_annotation_data(*it->second).Value);
        if (f < freq) {
            freq = f;
        }
    }
    return GlobalMinimumFrequencyAnnotation(std::move(freq));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
