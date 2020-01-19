// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "../Featurizer.h"
#include "../Traits.h"

#include "Components/ImputerTransformer.h"
#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/StatisticalMetricsEstimator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         MeanImputerEstimatorImpl
///  \brief         Implementation details for `MeanImputerEstimator`
///
template <typename T, size_t MaxNumTrainingItemsV>
class MeanImputerEstimatorImpl : public TransformerEstimator<typename Traits<T>::nullable_type, double> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<T>::IsNullableType == false || Traits<T>::IsNativeNullableType, "'T' must not be a nullable type");

    using InputType                         = typename Traits<T>::nullable_type;
    using BaseType                          = TransformerEstimator<InputType, double>;

    using TransformerType                   = Components::ImputerTransformer<InputType, double>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MeanImputerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~MeanImputerEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MeanImputerEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
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
        using InputTypeTraits               = Traits<InputType>;

        using StatisticalMetricsEstimator   = Components::StatisticalMetricsEstimator<InputType, MaxNumTrainingItemsV>;
        using AnnotationData                = typename StatisticalMetricsEstimator::AnnotationData;
        // ----------------------------------------------------------------------

        AnnotationData const &              data(StatisticalMetricsEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::StatisticalMetricsEstimatorName));

        // Use the Min value to determine if any values were encountered during training
#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127) // conditional expression is constant
#endif

        if(std::is_same<InputType, T>::value == false && InputTypeTraits::IsNull(data.Min)) {
            assert(InputTypeTraits::IsNull(data.Max));
            throw std::runtime_error("Mean values can't be calculated without input");
        }

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

        return typename BaseType::TransformerUniquePtr(new TransformerType(data.Average));
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         MeanImputerEstimator
///  \brief         Creates a `Transformer` that populates null values with
///                 the mean (average) of values encountered during training.
///
template <
    typename T,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class MeanImputerEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::StatisticalMetricsEstimator<typename Traits<T>::nullable_type, MaxNumTrainingItemsV>,
        Details::MeanImputerEstimatorImpl<T, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<T>::IsNullableType == false || Traits<T>::IsNativeNullableType, "'T' must not be a nullable type");

    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::StatisticalMetricsEstimator<typename Traits<T>::nullable_type, MaxNumTrainingItemsV>,
            Details::MeanImputerEstimatorImpl<T, MaxNumTrainingItemsV>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MeanImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~MeanImputerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MeanImputerEstimator);
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
// |  Details::MeanImputerEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename T, size_t MaxNumTrainingItemsV>
Details::MeanImputerEstimatorImpl<T, MaxNumTrainingItemsV>::MeanImputerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("MeanImputerEstimatorImpl", std::move(pAllColumnAnnotations)),
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
template <typename T, size_t MaxNumTrainingItemsV>
bool Details::MeanImputerEstimatorImpl<T, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    // No training is necessary
    return false;
}

template <typename T, size_t MaxNumTrainingItemsV>
FitResult Details::MeanImputerEstimatorImpl<T, MaxNumTrainingItemsV>::fit_impl(InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This should not be called");
}

template <typename T, size_t MaxNumTrainingItemsV>
void Details::MeanImputerEstimatorImpl<T, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

// ----------------------------------------------------------------------
// |
// |  MeanImputerEstimator
// |
// ----------------------------------------------------------------------
template <typename T, size_t MaxNumTrainingItemsV>
MeanImputerEstimator<T, MaxNumTrainingItemsV>::MeanImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "MeanImputerEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::StatisticalMetricsEstimator<typename Traits<T>::nullable_type, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Details::MeanImputerEstimatorImpl<T, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
