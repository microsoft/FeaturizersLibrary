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
///  \class         MinMaxImputerEstimatorImpl
///  \brief         Implementation details for the `MinMaxImputerEstimator`
///
template <typename T, size_t MaxNumTrainingItemsV>
class MinMaxImputerEstimatorImpl : public TransformerEstimator<typename Traits<T>::nullable_type, T> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<T>::IsNullableType == false || Traits<T>::IsNativeNullableType, "'T' must not be a nullable type");

    using InputType                         = typename Traits<T>::nullable_type;
    using BaseType                          = TransformerEstimator<InputType, T>;

    using TransformerType                   = Components::ImputerTransformer<InputType, T>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MinMaxImputerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool useMin);
    ~MinMaxImputerEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MinMaxImputerEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;
    bool const                              _useMin;

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
        InputType const &                   value(_useMin ? data.Min : data.Max);

#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127) // conditional expression is constant
#endif

        if(std::is_same<InputType, T>::value == false && InputTypeTraits::IsNull(value))
            throw std::runtime_error("The imputed value may not be null");

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

        return typename BaseType::TransformerUniquePtr(new TransformerType(InputTypeTraits::GetNullableValue(value)));
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         MinMaxImputerEstimator
///  \brief         Creates a `Transformer` that populates null values with
///                 the min- or max-value encountered during training.
///
template <
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class MinMaxImputerEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::StatisticalMetricsEstimator<typename Traits<TransformedT>::nullable_type, MaxNumTrainingItemsV>,
        Details::MinMaxImputerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::StatisticalMetricsEstimator<typename Traits<TransformedT>::nullable_type, MaxNumTrainingItemsV>,
            Details::MinMaxImputerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MinMaxImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool useMin);
    ~MinMaxImputerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MinMaxImputerEstimator);
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
// |  Details::MinMaxImputerEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename T, size_t MaxNumTrainingItemsV>
Details::MinMaxImputerEstimatorImpl<T, MaxNumTrainingItemsV>::MinMaxImputerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool useMin) :
    BaseType("MinMaxImputerEstimatorImpl", std::move(pAllColumnAnnotations)),
    _colIndex(
        std::move(
            [this, &colIndex](void) -> size_t & {
                if(colIndex >= this->get_column_annotations().size())
                    throw std::invalid_argument("colIndex");

                return colIndex;
            }()
        )
    ),
    _useMin(std::move(useMin)) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename T, size_t MaxNumTrainingItemsV>
bool Details::MinMaxImputerEstimatorImpl<T, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    // No training is necessary
    return false;
}

template <typename T, size_t MaxNumTrainingItemsV>
FitResult Details::MinMaxImputerEstimatorImpl<T, MaxNumTrainingItemsV>::fit_impl(InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This should not be called");
}

template <typename T, size_t MaxNumTrainingItemsV>
void Details::MinMaxImputerEstimatorImpl<T, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

// ----------------------------------------------------------------------
// |
// |  MinMaxImputerEstimator
// |
// ----------------------------------------------------------------------
template <typename TransformedT, size_t MaxNumTrainingItemsV>
MinMaxImputerEstimator<TransformedT, MaxNumTrainingItemsV>::MinMaxImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool useMin) :
    BaseType(
        "MinMaxImputerEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::StatisticalMetricsEstimator<typename Traits<TransformedT>::nullable_type, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex, &useMin](void) { return Details::MinMaxImputerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex), std::move(useMin)); }
    ) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
