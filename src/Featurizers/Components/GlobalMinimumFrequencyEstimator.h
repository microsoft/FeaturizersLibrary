// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>

#include "TrainingOnlyEstimatorImpl.h"
#include "FrequencyEstimator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         GlobalMinimumFrequencyEstimatorName("GlobalMinimumFrequencyEstimator");

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
template <typename GlobalMinimumFrequencyEstimatorT, size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class GlobalMinimumFrequencyTrainingOnlyPolicy {
public:

    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using GrainType                     = std::vector<std::string>;
    using InputType                     = std::tuple<GrainType const &, std::chrono::system_clock::time_point const &>;
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

    void fit(InputType const &input);
    GlobalMinimumFrequencyAnnotation complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using FrequencyType                     = std::chrono::system_clock::duration;
};
}
/////////////////////////////////////////////////////////////////////////
///  \typedef       GlobalMinimumFrequencyEstimator
///  \brief         A training-only class that does no training but retrieve annotation from GrainedFrequencyEstimator
///                 and finds global minimum frequency according to grain
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
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex), false) {
}

// ----------------------------------------------------------------------
// |
// |  Details::GlobalMinimumFrequencyTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename GlobalMinimumFrequencyEstimatorT, size_t MaxNumTrainingItemsV>
void Details::GlobalMinimumFrequencyTrainingOnlyPolicy<GlobalMinimumFrequencyEstimatorT, MaxNumTrainingItemsV>::fit(InputType const &) {
    throw std::runtime_error("This will never be called");
}

template <typename GlobalMinimumFrequencyEstimatorT, size_t MaxNumTrainingItemsV>
GlobalMinimumFrequencyAnnotation Details::GlobalMinimumFrequencyTrainingOnlyPolicy<GlobalMinimumFrequencyEstimatorT, MaxNumTrainingItemsV>::complete_training(void) {
    GlobalMinimumFrequencyEstimatorT                                         const & estimator(static_cast<GlobalMinimumFrequencyEstimatorT const &>(*this));
    GrainEstimatorAnnotation<GrainType> const & data(GrainedFrequencyEstimator<MaxNumTrainingItemsV>::get_annotation(estimator.get_column_annotations(), estimator.get_column_index(), GrainFrequencyEstimatorName));

    GrainEstimatorAnnotation<GrainType>::AnnotationMap const & annotation(data.Annotations);

    FrequencyType freq(std::chrono::system_clock::duration::max().count());
    for(auto const & kvp : annotation) {
        FrequencyType f(FrequencyEstimator<MaxNumTrainingItemsV>::get_annotation_data(*kvp.second).Value);
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
