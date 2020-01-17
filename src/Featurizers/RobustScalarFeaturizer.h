// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/MedianEstimator.h"
#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/StatisticalMetricsEstimator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         RobustScalarTransformer
///  \brief         This class retrieves a RobustScalarNormAnnotation and computes
///                 the scale.
///
template <typename InputT, typename TransformedT>
class RobustScalarTransformer : public StandardTransformer<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                      = StandardTransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    typename BaseType::TransformedType const            Median;
    typename BaseType::TransformedType const            Scale;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    RobustScalarTransformer(typename BaseType::TransformedType median, typename BaseType::TransformedType scale);
    RobustScalarTransformer(Archive &ar);

    ~RobustScalarTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(RobustScalarTransformer);

    bool operator==(RobustScalarTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override;
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         RobustScalarEstimatorImpl
///  \brief         This class retrieves a RobustScalarNormAnnotation and computes
///                 the scale.
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class RobustScalarEstimatorImpl : public TransformerEstimator<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, TransformedT>;
    using TransformerType                   = RobustScalarTransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    RobustScalarEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool withCentering, float qRangeMin, float qRangeMax);
    ~RobustScalarEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(RobustScalarEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;
    bool const                              _withCentering;
    float const                             _qRangeMin;
    float const                             _qRangeMax;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;
    FitResult fit_impl(typename BaseType::InputType const *, size_t) override;
    void complete_training_impl(void) override;

    // MSVC runs into problems when separating the definition for this method
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        // ----------------------------------------------------------------------
        using MedianEstimator                           = Components::MedianEstimator<InputT, TransformedT, true, MaxNumTrainingItemsV>;
        using MedianAnnotationData                      = Components::MedianAnnotationData<TransformedT>;

        using StatisticalMetricsEstimator               = Components::StatisticalMetricsEstimator<InputT, MaxNumTrainingItemsV>;
        using StatisticalMetricsAnnoationData           = typename StatisticalMetricsEstimator::AnnotationData;
        // ----------------------------------------------------------------------

        TransformedT                        median(static_cast<TransformedT>(0.0));

        if(_withCentering) {
            MedianAnnotationData const &                medianData(MedianEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::MedianEstimatorName));

            median = medianData.Median;
        }

        TransformedT                        scale(static_cast<TransformedT>(1.0));

        if(Traits<float>::IsNull(_qRangeMin) == false) {
            float const                     qRangeRatio((_qRangeMax - _qRangeMin) / 100.0f);

            assert(qRangeRatio >= 0.0f && qRangeRatio <= 1.0f);

            StatisticalMetricsAnnoationData const &     statisticsData(StatisticalMetricsEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::StatisticalMetricsEstimatorName));

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

            scale = static_cast<TransformedT>((statisticsData.Max - statisticsData.Min) * qRangeRatio);

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
        }

        return typename BaseType::TransformerUniquePtr(new RobustScalarTransformer<InputT, TransformedT>(std::move(median), std::move(scale)));
    }
};

} // namespace Details


/////////////////////////////////////////////////////////////////////////
///  \class         RobustScalarEstimator
///  \brief         This class 'chains' RobustScalarNormEstimator and RobustScalarEstimator.
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class RobustScalarEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::MedianEstimator<InputT, TransformedT, true, MaxNumTrainingItemsV>,
        Components::StatisticalMetricsEstimator<InputT, MaxNumTrainingItemsV>,
        Details::RobustScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::PipelineExecutionEstimatorImpl<
        Components::MedianEstimator<InputT, TransformedT, true, MaxNumTrainingItemsV>,
        Components::StatisticalMetricsEstimator<InputT, MaxNumTrainingItemsV>,
        Details::RobustScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
    >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    static RobustScalarEstimator<InputT, TransformedT, MaxNumTrainingItemsV> CreateWithDefaultScaling(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool with_centering);

    // Note that the signature with distinct values for qRangeMin and qRangeMax is required
    // for compatibility with the generated C interfaces (which doesn't yet support tuples).
    // Once this support is added, this signature should change to use `OptionalScalingParameters`.
    RobustScalarEstimator(
        AnnotationMapsPtr pAllColumnAnnotations,
        size_t colIndex,
        bool withCentering,
        float qRangeMin=Traits<std::float_t>::CreateNullValue(),
        float qRangeMax=Traits<std::float_t>::CreateNullValue()
    );
    ~RobustScalarEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(RobustScalarEstimator);
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
// |  RobustScalarTransformer
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
RobustScalarTransformer<InputT, TransformedT>::RobustScalarTransformer(typename BaseType::TransformedType median,
                                                                       typename BaseType::TransformedType scale) :
    Median(std::move(median)),
    Scale(std::move(scale)) {
}

template <typename InputT, typename TransformedT>
RobustScalarTransformer<InputT, TransformedT>::RobustScalarTransformer(Archive &ar) :
    RobustScalarTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            TransformedT                    median(Traits<TransformedT>::deserialize(ar));
            TransformedT                    scale(Traits<TransformedT>::deserialize(ar));

            return RobustScalarTransformer(std::move(median), std::move(scale));
        }()
    ) {
}

template <typename InputT, typename TransformedT>
bool RobustScalarTransformer<InputT, TransformedT>::operator==(RobustScalarTransformer const &other) const {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    return Median == other.Median
        && Scale == other.Scale;

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
}

template <typename InputT, typename TransformedT>
void RobustScalarTransformer<InputT, TransformedT>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(Median)>::serialize(ar, Median);
    Traits<decltype(Scale)>::serialize(ar, Scale);
}

template <typename InputT, typename TransformedT>
void RobustScalarTransformer<InputT, TransformedT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    if (Scale != static_cast<TransformedT>(0)) {
        callback((static_cast<TransformedT>(input) - Median) / Scale);
        return;
    }

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

    callback(static_cast<TransformedT>(input) - Median);
}

// ----------------------------------------------------------------------
// |
// |  Details::RobustScalarEstimatorImpl
// |
// ----------------------------------------------------------------------
namespace {

    using FloatTraits                       = Traits<std::float_t>;

} // anonymous namespace

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
Details::RobustScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::RobustScalarEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool withCentering, float qRangeMin, float qRangeMax) :
    BaseType("RobustScalarEstimatorImpl", std::move(pAllColumnAnnotations)),
    _colIndex(
        std::move(
            [this, &colIndex](void) -> size_t & {
                if(colIndex >= this->get_column_annotations().size())
                    throw std::invalid_argument("colIndex");

                return colIndex;
            }()
        )
    ),
    _withCentering(std::move(withCentering)),
    _qRangeMin(
        std::move(
            [&qRangeMin](void) -> float & {
                if(
                    FloatTraits::IsNull(qRangeMin) == false
                    && (
                        qRangeMin < 0.0f
                        || qRangeMin > 100.0f
                    )
                )
                    throw std::invalid_argument("qRangeMin");

                return qRangeMin;
            }()
        )
    ),
    _qRangeMax(
        std::move(
            [&qRangeMax](void) -> float & {
                if(
                    FloatTraits::IsNull(qRangeMax) == false
                    && (
                        qRangeMax < 0.0f
                        || qRangeMax > 100.f
                    )
                )
                    throw std::invalid_argument("qRangeMax");

                return qRangeMax;
            }()
        )
    ) {
        if(FloatTraits::IsNull(_qRangeMin) == false || FloatTraits::IsNull(_qRangeMax) == false) {
            if(FloatTraits::IsNull(_qRangeMin) || FloatTraits::IsNull(_qRangeMax))
                throw std::invalid_argument("qRangeMin and qRangeMax must be atomically set");

            if(_qRangeMax < _qRangeMin)
                throw std::invalid_argument("qRangeMax");
        }
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
bool Details::RobustScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
FitResult Details::RobustScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::fit_impl(typename BaseType::InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This should not be called");
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
void Details::RobustScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

// ----------------------------------------------------------------------
// |
// |  RobustScalarEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
RobustScalarEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::RobustScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool withCentering, float qRangeMin, float qRangeMax) :
    BaseType(
        "RobustScalarEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::MedianEstimator<InputT, TransformedT, true, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Components::StatisticalMetricsEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex, &withCentering, &qRangeMin, &qRangeMax](void) { return Details::RobustScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex), std::move(withCentering), std::move(qRangeMin), std::move(qRangeMax)); }
    ) {
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
RobustScalarEstimator<InputT, TransformedT, MaxNumTrainingItemsV> RobustScalarEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::CreateWithDefaultScaling(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool withCentering) {
    return RobustScalarEstimator(std::move(pAllColumnAnnotations), std::move(colIndex), withCentering, 25.0f, 75.0f);
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
