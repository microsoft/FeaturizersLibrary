// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/RobustScalarNormEstimator.h"
#include "Components/PipelineExecutionEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {



/////////////////////////////////////////////////////////////////////////
///  \class         RobustScalarTransformer
///  \brief         This class retrieves a RobustScalarNormAnnotation and computes
///                 the scale.
///
template <typename InputT,typename TransformedT>
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
    RobustScalarEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~RobustScalarEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(RobustScalarEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;

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
        using RobustScalarNormAnnotationData            = Components::RobustScalarNormAnnotationData<TransformedT>;
        using RobustScalarNormEstimator                 = Components::RobustScalarNormEstimator<InputT, TransformedT, MaxNumTrainingItemsV>;

        // ----------------------------------------------------------------------

        RobustScalarNormAnnotationData const &          data(RobustScalarNormEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::RobustScalarNormEstimatorName));

        return std::make_unique<RobustScalarTransformer<InputT, TransformedT>>(data.Median, data.Scale);
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
        Components::RobustScalarNormEstimator<InputT, TransformedT, MaxNumTrainingItemsV>,
        Details::RobustScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::PipelineExecutionEstimatorImpl<
        Components::RobustScalarNormEstimator<InputT, TransformedT, MaxNumTrainingItemsV>,
        Details::RobustScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
    >;

    using OptionalScalingParameters = typename Components::RobustScalarNormEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::OptionalScalingParameters;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------

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

    static RobustScalarEstimator<InputT, TransformedT, MaxNumTrainingItemsV> CreateWithDefaultScaling(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool with_centering);
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
    Median(Traits<decltype(Median)>::deserialize(ar)),
    Scale(Traits<decltype(Scale)>::deserialize(ar)) {
}

template <typename InputT, typename TransformedT>
void RobustScalarTransformer<InputT, TransformedT>::save(Archive &ar) const /*override*/ {
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
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
Details::RobustScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::RobustScalarEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("RobustScalarEstimatorImpl", std::move(pAllColumnAnnotations)),
    _colIndex(
        std::move(
            [this, &colIndex](void) -> size_t & {
                if(colIndex >= this->get_column_annotations().size())
                    throw std::invalid_argument("colIndex");

                return colIndex;
            }()
        )
    ) {
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
        [pAllColumnAnnotations, colIndex, &withCentering, &qRangeMin, &qRangeMax](void) {
            OptionalScalingParameters       optionalScalingParameters(
                [&qRangeMin, &qRangeMax](void) -> OptionalScalingParameters {
                    if(Traits<std::float_t>::IsNull(qRangeMin) == false || Traits<std::float_t>::IsNull(qRangeMax) == false) {
                        if(Traits<std::float_t>::IsNull(qRangeMin) || Traits<std::float_t>::IsNull(qRangeMax))
                            throw std::invalid_argument("Both 'qRangeMin' and 'qRangeMax' should be specified");

                        return std::make_tuple(qRangeMin, qRangeMax);
                    }

                    return OptionalScalingParameters();
                }()
            );

            return Components::RobustScalarNormEstimator<InputT, TransformedT, MaxNumTrainingItemsV> (
                std::move(pAllColumnAnnotations),
                std::move(colIndex),
                std::move(withCentering),
                std::move(optionalScalingParameters)
            );
        },
        [pAllColumnAnnotations, colIndex](void) {
            return Details::RobustScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>(
                std::move(pAllColumnAnnotations),
                std::move(colIndex)
            );
        }
    ) {
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
RobustScalarEstimator<InputT, TransformedT, MaxNumTrainingItemsV> RobustScalarEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::CreateWithDefaultScaling(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool withCentering) {
    return RobustScalarEstimator(std::move(pAllColumnAnnotations), std::move(colIndex), withCentering, 25.0f, 75.0f);

    // TODO: Restore this code path once `OptionalScalingParameters` support is restored.
    //
    // OptionalScalingParameters optionalScalingParameters = nonstd::optional<std::tuple<float, float>>(std::tuple<float, float>(25.0f, 75.0f));
    //
    // if (withCentering) {
    //     return RobustScalarEstimator(pAllColumnAnnotations, colIndex, true, optionalScalingParameters);
    // }
    // return RobustScalarEstimator(pAllColumnAnnotations, colIndex, false, optionalScalingParameters);
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
