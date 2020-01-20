// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "HistogramEstimator.h"
#include "OrderEstimator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         ModeEstimatorName("ModeEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         ModeAnnotationData
///  \brief         Contains the most frequent value found in a data set.
///
template <typename T>
class ModeAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    T const                                 Value;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ModeAnnotationData(T value);
    ~ModeAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ModeAnnotationData);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         ModeTrainingOnlyPolicy
///  \brief         `ModeEstimator` implementation details.
///
template <typename T, bool AllowNullModeV, typename EstimatorT>
class ModeTrainingOnlyPolicy {
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
    static constexpr char const * const     NameValue = ModeEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    void fit(InputType const &input);
    ModeAnnotationData<T> complete_training(void);
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         ModeEstimator
///  \brief         Creates `ModeAnnotationData` with the most common value,
///                 as determined by the `HistogramEstimator`.
///
template <
    typename T,
    bool AllowNullModeV=false,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class ModeEstimator :
    public TrainingOnlyEstimatorImpl<
        Details::ModeTrainingOnlyPolicy<
            T,
            AllowNullModeV,
            ModeEstimator<T, AllowNullModeV, MaxNumTrainingItemsV>
        >,
        MaxNumTrainingItemsV
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(AllowNullModeV == false || Traits<T>::IsNullableType, "'T' must be a nullable type if 'AllowNullModeV' is true");

    using BaseType =
        TrainingOnlyEstimatorImpl<
            Details::ModeTrainingOnlyPolicy<
                T,
                AllowNullModeV,
                ModeEstimator<T, AllowNullModeV, MaxNumTrainingItemsV>
            >,
            MaxNumTrainingItemsV
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ModeEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~ModeEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ModeEstimator);
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
// |  ModeAnnotationData
// |
// ----------------------------------------------------------------------
template <typename T>
ModeAnnotationData<T>::ModeAnnotationData(T value) :
    Value(std::move(value)) {
}

// ----------------------------------------------------------------------
// |
// |  ModeEstimator
// |
// ----------------------------------------------------------------------
template <typename T, bool AllowNullModeV, size_t MaxNumTrainingItemsV>
ModeEstimator<T, AllowNullModeV, MaxNumTrainingItemsV>::ModeEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex), false) {
}

// ----------------------------------------------------------------------
// |
// |  Details::ModeTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T, bool AllowNullModeV, typename ModeEstimatorT>
void Details::ModeTrainingOnlyPolicy<T, AllowNullModeV, ModeEstimatorT>::fit(InputType const &) {
    throw std::runtime_error("This will never be called");
}

namespace {

template <typename T>
inline bool IsSupportedModeEstimatorValue(T const &, std::true_type) {
    // Nulls are allowed, anything is supported
    return true;
}

template <typename T>
inline bool IsSupportedModeEstimatorValueIsNullable(T const &value, std::true_type) {
    return Traits<T>::IsNull(value) == false;
}

template <typename T>
inline bool IsSupportedModeEstimatorValueIsNullable(T const &, std::false_type) {
    // The value is not nullable, so it is supported
    return true;
}

template <typename T>
inline bool IsSupportedModeEstimatorValue(T const &value, std::false_type) {
    return IsSupportedModeEstimatorValueIsNullable(value, std::integral_constant<bool, Traits<T>::IsNullableType>());
}

} // anonymous namespace

template <typename T, bool AllowNullModeV, typename ModeEstimatorT>
ModeAnnotationData<T> Details::ModeTrainingOnlyPolicy<T, AllowNullModeV, ModeEstimatorT>::complete_training(void) {
    // ----------------------------------------------------------------------
    using HistogramAnnotationData           = HistogramAnnotationData<T>;
    using HistogramEstimator                = HistogramEstimator<T, ModeEstimatorT::MaxNumTrainingItems>;

    using OrderAnnotationData               = OrderAnnotationData<T>;
    using OrderEstimator                    = OrderEstimator<T, ModeEstimatorT::MaxNumTrainingItems>;
    // ----------------------------------------------------------------------

    ModeEstimatorT const &                  estimator(static_cast<ModeEstimatorT const &>(*this));
    HistogramAnnotationData const &         histogramData(HistogramEstimator::get_annotation_data(estimator.get_column_annotations(), estimator.get_column_index(), HistogramEstimatorName));
    OrderAnnotationData const &             orderData(OrderEstimator::get_annotation_data(estimator.get_column_annotations(), estimator.get_column_index(), OrderEstimatorName));

    // Find the most common value
    if(histogramData.Value.empty() || orderData.Value.empty())
        throw std::runtime_error("The histogram is empty");

    typename HistogramAnnotationData::Histogram::const_iterator             iterMode(histogramData.Value.end());
    std::uint32_t                                                           modeIndex(0);

    for(
        typename HistogramAnnotationData::Histogram::const_iterator iter=histogramData.Value.begin();
        iter != histogramData.Value.end();
        ++iter
    ) {
        if(iterMode == histogramData.Value.end() || iter->second >= iterMode->second) {
            if(IsSupportedModeEstimatorValue(iter->first, std::integral_constant<bool, AllowNullModeV>()) == false)
                continue;

            // If the values are equal, only take this value if it was seen before the current best
            typename OrderAnnotationData::OrderMap::const_iterator const    iterModeIndex(orderData.Value.find(iter->first));

            assert(iterModeIndex != orderData.Value.end());

            if(
                iterMode != histogramData.Value.end()
                && iter->second == iterMode->second
                && iterModeIndex->second > modeIndex
            )
                continue;

            iterMode = iter;
            modeIndex = iterModeIndex->second;
        }
    }

    if(iterMode == histogramData.Value.end())
        throw std::runtime_error("The histogram does not contain any supported values");

    return ModeAnnotationData<T>(iterMode->first);
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
