// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/StatisticalMetricsEstimator.h"
#include "Components/StandardDeviationEstimator.h"
#include "Components/PipelineExecutionEstimatorImpl.h"
#include "../Archive.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         StandardScalerTransformer
///  \brief         Scales values based on learned mean and standard deviation values.
///
template <typename InputT, typename TransformedT>
class StandardScalerTransformer : public StandardTransformer<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<TransformedT>::IsNullableType && Traits<TransformedT>::IsIntOrNumeric::value, "'TransformedT' must be a numeric type");

    using BaseType                          = StandardTransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StandardScalerTransformer(std::double_t average, std::double_t deviation);
    StandardScalerTransformer(Archive &ar);

    ~StandardScalerTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StandardScalerTransformer);

    bool operator==(StandardScalerTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::double_t const                     _average;
    std::double_t const                     _deviation;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override;
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         StandardScaleWrapperEstimatorImpl
///  \brief         Estimator that reads an annotation created by the `StatisticalMetricsEstimator`
///                 and the `StandardDeviationEstimator` to create a `StandardScalerTransformer` object.
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class StandardScaleWrapperEstimatorImpl : public TransformerEstimator<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, TransformedT>;
    using TransformerType                   = StandardScalerTransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StandardScaleWrapperEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool withMean, bool withStd);
    ~StandardScaleWrapperEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StandardScaleWrapperEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;
    bool          const                     _withMean;
    bool          const                     _withStd;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;
    FitResult fit_impl(typename BaseType::InputType const *, size_t) override;
    void complete_training_impl(void) override;

    // MSVC has problems when the definition is separate from the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        // ----------------------------------------------------------------------
        using StandardStatisticalAnnotationData = Components::StandardStatisticalAnnotationData<InputT>;
        using StatisticalMetricsEstimator       = Components::StatisticalMetricsEstimator<InputT, MaxNumTrainingItemsV>;

        using StandardDeviationAnnotationData   = Components::StandardDeviationAnnotationData;
        using StandardDeviationEstimator        = Components::StandardDeviationEstimator<InputT, MaxNumTrainingItemsV>;
        // ----------------------------------------------------------------------
        // if _withMean is false, average is set to 0
        std::double_t average = 0;
        // if _withStd is false, deviation is set to 1
        std::double_t deviation = 1;
        std::uint64_t average_count = 0;
        std::uint64_t deviation_count = 0;
        if (_withMean) {
            StandardStatisticalAnnotationData const &        average_stats(StatisticalMetricsEstimator::get_annotation_data(this->get_column_annotations(), _colIndex, Components::StatisticalMetricsEstimatorName));
            average = average_stats.Average;
        }
        if (_withStd) {
            StandardDeviationAnnotationData   const &        deviation_stats(StandardDeviationEstimator::get_annotation_data(this->get_column_annotations(), _colIndex, Components::StandardDeviationEstimatorName));
            deviation = static_cast<std::double_t>(deviation_stats.StandardDeviation);
        }
        if (_withMean && _withStd) {
            assert(average_count == deviation_count);
        }

        // check if deviation is 0
        // if it's 0, change it to 1
        if (deviation == 0.0) {
            deviation = 1.0;
        }

        return typename BaseType::TransformerUniquePtr(new StandardScalerTransformer<InputT, TransformedT>(average, deviation));
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         StandardScaleWrapperEstimator
///  \brief         Chains up StatisticalMetricsEstimator, StandardDeviationEstimator and StandardScalerTransformerImpl
///                 to scale input data set so that it's centered around 0 with unit standard deviation
///
template <
    typename InputT,
    typename TransformedT=std::double_t,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class StandardScaleWrapperEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::StatisticalMetricsEstimator<InputT, MaxNumTrainingItemsV>,
        Components::StandardDeviationEstimator<InputT, MaxNumTrainingItemsV>,
        Details::StandardScaleWrapperEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::StatisticalMetricsEstimator<InputT, MaxNumTrainingItemsV>,
            Components::StandardDeviationEstimator<InputT, MaxNumTrainingItemsV>,
            Details::StandardScaleWrapperEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StandardScaleWrapperEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool withMean, bool withStd);
    ~StandardScaleWrapperEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StandardScaleWrapperEstimator);
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
// |  StandardScalerTransformer
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
StandardScalerTransformer<InputT, TransformedT>::StandardScalerTransformer(std::double_t average, std::double_t deviation) :
    _average(std::move(average)),
    _deviation(std::move(deviation)) {
        if(_deviation < 0) {
            throw std::invalid_argument("Standard deviation should be greater or equal to 0 in StandardScaleWrapperFeaturizer!");
        }
}

template <typename InputT, typename TransformedT>
StandardScalerTransformer<InputT, TransformedT>::StandardScalerTransformer(Archive &ar) :
    StandardScalerTransformer(
        [&ar](void) {
            std::double_t average(Traits<std::double_t>::deserialize(ar));
            std::double_t deviation(Traits<std::double_t>::deserialize(ar));

            return StandardScalerTransformer<InputT, TransformedT>(std::move(average), std::move(deviation));
        }()
    ) {
}

template <typename InputT, typename TransformedT>
void StandardScalerTransformer<InputT, TransformedT>::save(Archive &ar) const /*override*/ {
    Traits<std::double_t>::serialize(ar, _average);
    Traits<std::double_t>::serialize(ar, _deviation);
}

template <typename InputT, typename TransformedT>
bool StandardScalerTransformer<InputT, TransformedT>::operator==(StandardScalerTransformer const &other) const {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    return this->_average == other._average
        && this->_deviation == other._deviation;

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

}


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
void StandardScalerTransformer<InputT, TransformedT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    // ----------------------------------------------------------------------
    using InputTraits                       = Traits<InputT>;
    using TransformedTraits                 = Traits<TransformedT>;
    // ----------------------------------------------------------------------

    // TODO: Implement different strategies to handle nulls
    // potential strategies can be returning 0s for nulls, throwing errors, returning nulls for nulls
    if(InputTraits::IsNull(input)) {
        callback(TransformedTraits::CreateNullValue());
        return;
    }

    callback((static_cast<TransformedT>(input) - _average) / _deviation);

}

// ----------------------------------------------------------------------
// |
// |  StandardScaleWrapperEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
StandardScaleWrapperEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::StandardScaleWrapperEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool withMean, bool withStd) :
    BaseType(
        "StandardScaleWrapperEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::StatisticalMetricsEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Components::StandardDeviationEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex, &withMean, &withStd](void) { return Details::StandardScaleWrapperEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex), std::move(withMean), std::move(withStd)); }
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::StandardScaleWrapperEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
Details::StandardScaleWrapperEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::StandardScaleWrapperEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool withMean, bool withStd) :
    BaseType("StandardScaleWrapperEstimatorImpl", std::move(pAllColumnAnnotations)),
    _colIndex(
        std::move(
            [this, &colIndex](void) -> size_t & {
                if(colIndex >= this->get_column_annotations().size())
                    throw std::invalid_argument("colIndex");

                return colIndex;
            }()
        )
    ),
    _withMean(std::move(withMean)),
    _withStd(std::move(withStd)) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
bool Details::StandardScaleWrapperEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
FitResult Details::StandardScaleWrapperEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::fit_impl(typename BaseType::InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This will never be called");
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
void Details::StandardScaleWrapperEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

}
}
}
