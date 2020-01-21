// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "../Featurizer.h"
#include "../Traits.h"

#include "Components/ImputerTransformer.h"
#include "Components/MedianEstimator.h"
#include "Components/PipelineExecutionEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         MedianImputerEstimatorImpl
///  \brief         Implementation details for the `MedianImputerEstimatorImpl`
///
template <typename InputT, typename TransformedT, bool InterpolateValuesV, size_t MaxNumTrainingItemsV>
class MedianImputerEstimatorImpl : public TransformerEstimator<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<InputT>::IsNullableType, "'InputT' must be a nullable type");
    static_assert(Traits<TransformedT>::IsNullableType == false || Traits<TransformedT>::IsNativeNullableType, "'TransformedT' must not be a nullable type");

    using InputType                         = InputT;
    using BaseType                          = TransformerEstimator<InputType, TransformedT>;

    using TransformerType                   = Components::ImputerTransformer<InputType, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MedianImputerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~MedianImputerEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MedianImputerEstimatorImpl);

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
    FitResult fit_impl(InputType const *, size_t) override;
    void complete_training_impl(void) override;

    // MSVC has problems when the declaration and definition are separated
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        // ----------------------------------------------------------------------
        using MedianEstimator               = Components::MedianEstimator<InputT, TransformedT, InterpolateValuesV, MaxNumTrainingItemsV>;
        using AnnotationData                = typename MedianEstimator::AnnotationData;
        // ----------------------------------------------------------------------

        AnnotationData const &              data(MedianEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::MedianEstimatorName));

        return typename BaseType::TransformerUniquePtr(new TransformerType(data.Median));
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         MedianImputerEstimator
///  \brief         Creates a `Transformer` that populates null values with the
///                 median value encountered during training.
///
template <
    typename InputT,
    typename TransformedT,
    bool InterpolateValuesV=true,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class MedianImputerEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::MedianEstimator<InputT, TransformedT, InterpolateValuesV, MaxNumTrainingItemsV>,
        Details::MedianImputerEstimatorImpl<InputT, TransformedT, InterpolateValuesV, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<InputT>::IsNullableType, "'InputT' must be a nullable type");
    static_assert(Traits<TransformedT>::IsNullableType == false || Traits<TransformedT>::IsNativeNullableType, "'TransformedT' must not be a nullable type");

    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::MedianEstimator<InputT, TransformedT, InterpolateValuesV, MaxNumTrainingItemsV>,
            Details::MedianImputerEstimatorImpl<InputT, TransformedT, InterpolateValuesV, MaxNumTrainingItemsV>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MedianImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~MedianImputerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MedianImputerEstimator);
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
// |  Details::MedianImputerEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, bool InterpolateValuesV, size_t MaxNumTrainingItemsV>
Details::MedianImputerEstimatorImpl<InputT, TransformedT, InterpolateValuesV, MaxNumTrainingItemsV>::MedianImputerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("MedianImputerEstimatorImpl", std::move(pAllColumnAnnotations)),
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
template <typename InputT, typename TransformedT, bool InterpolateValuesV, size_t MaxNumTrainingItemsV>
bool Details::MedianImputerEstimatorImpl<InputT, TransformedT, InterpolateValuesV, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    // No training is necessary
    return false;
}

template <typename InputT, typename TransformedT, bool InterpolateValuesV, size_t MaxNumTrainingItemsV>
FitResult Details::MedianImputerEstimatorImpl<InputT, TransformedT, InterpolateValuesV, MaxNumTrainingItemsV>::fit_impl(InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This should not be called");
}

template <typename InputT, typename TransformedT, bool InterpolateValuesV, size_t MaxNumTrainingItemsV>
void Details::MedianImputerEstimatorImpl<InputT, TransformedT, InterpolateValuesV, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

// ----------------------------------------------------------------------
// |
// |  MedianImputerEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, bool InterpolateValuesV, size_t MaxNumTrainingItemsV>
MedianImputerEstimator<InputT, TransformedT, InterpolateValuesV, MaxNumTrainingItemsV>::MedianImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "MedianImputerEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::MedianEstimator<InputT, TransformedT, InterpolateValuesV, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Details::MedianImputerEstimatorImpl<InputT, TransformedT, InterpolateValuesV, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
