// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "../Featurizer.h"
#include "../Traits.h"

#include "Components/HistogramEstimator.h"
#include "Components/ImputerTransformer.h"
#include "Components/ModeEstimator.h"
#include "Components/OrderEstimator.h"
#include "Components/PipelineExecutionEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         ModeImputerEstimatorImpl
///  \brief         Implementation details for `ModeImputerEstimator`
///
template <typename T, size_t MaxNumTrainingItemsV>
class ModeImputerEstimatorImpl : public TransformerEstimator<typename Traits<T>::nullable_type, T> {
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
    ModeImputerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~ModeImputerEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ModeImputerEstimatorImpl);

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
        using InputTypeTraits               = Traits<InputType>;

        using ModeEstimator                 = Components::ModeEstimator<InputType, false, MaxNumTrainingItemsV>;
        using AnnotationData                = typename ModeEstimator::AnnotationData;
        // ----------------------------------------------------------------------

        AnnotationData const &              data(ModeEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::ModeEstimatorName));

#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127) // conditional expression is constant
#endif

        if(std::is_same<InputType, T>::value == false && InputTypeTraits::IsNull(data.Value))
            throw std::runtime_error("The imputed value may not be null");

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

        return typename BaseType::TransformerUniquePtr(new TransformerType(InputTypeTraits::GetNullableValue(data.Value)));
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         ModeImputerEstimator
///  \brief         Creates a `Transformer` that populates null values with
///                 the mode (or most commonly found value) during traiing.
///
template <
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class ModeImputerEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::HistogramEstimator<typename Traits<TransformedT>::nullable_type, MaxNumTrainingItemsV>,
        Components::OrderEstimator<typename Traits<TransformedT>::nullable_type, MaxNumTrainingItemsV>,
        Components::ModeEstimator<typename Traits<TransformedT>::nullable_type, false, MaxNumTrainingItemsV>,
        Details::ModeImputerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<TransformedT>::IsNullableType == false || Traits<TransformedT>::IsNativeNullableType, "'TransformedT' must not be a nullable type");

    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::HistogramEstimator<typename Traits<TransformedT>::nullable_type, MaxNumTrainingItemsV>,
            Components::OrderEstimator<typename Traits<TransformedT>::nullable_type, MaxNumTrainingItemsV>,
            Components::ModeEstimator<typename Traits<TransformedT>::nullable_type, false, MaxNumTrainingItemsV>,
            Details::ModeImputerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ModeImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~ModeImputerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ModeImputerEstimator);
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
// |  Details::ModeImputerEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename T, size_t MaxNumTrainingItemsV>
Details::ModeImputerEstimatorImpl<T, MaxNumTrainingItemsV>::ModeImputerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("ModeImputerEstimatorImpl", std::move(pAllColumnAnnotations)),
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
bool Details::ModeImputerEstimatorImpl<T, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    // No training is necessary
    return false;
}

template <typename T, size_t MaxNumTrainingItemsV>
FitResult Details::ModeImputerEstimatorImpl<T, MaxNumTrainingItemsV>::fit_impl(InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This should not be called");
}

template <typename T, size_t MaxNumTrainingItemsV>
void Details::ModeImputerEstimatorImpl<T, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

// ----------------------------------------------------------------------
// |
// |  ModeImputerEstimator
// |
// ----------------------------------------------------------------------
template <typename TransformedT, size_t MaxNumTrainingItemsV>
ModeImputerEstimator<TransformedT, MaxNumTrainingItemsV>::ModeImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "ModeImputerEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::HistogramEstimator<typename Traits<TransformedT>::nullable_type, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Components::OrderEstimator<typename Traits<TransformedT>::nullable_type, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Components::ModeEstimator<typename Traits<TransformedT>::nullable_type, false, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Details::ModeImputerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
