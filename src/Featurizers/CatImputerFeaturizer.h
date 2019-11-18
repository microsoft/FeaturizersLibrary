// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "../Featurizer.h"
#include "../Traits.h"

#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/HistogramEstimator.h"
#include "Components/ModeEstimator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         CatImputerTransformer
///  \brief         Transformer that populates null values with the most
///                 frequent value found in the training data set.
///
template <typename InputT, typename TransformedT>
class CatImputerTransformer : public StandardTransformer<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<InputT>::IsNullableType, "'InputT' must be a nullable type");
    static_assert(Traits<TransformedT>::IsNullableType == false || Traits<TransformedT>::IsNativeNullableType, "'TransformedT' must not be a nullable type");

    using BaseType                          = StandardTransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    typename BaseType::TransformedType const            Value;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CatImputerTransformer(typename BaseType::TransformedType value);
    CatImputerTransformer(Archive &ar);

    ~CatImputerTransformer(void) override = default;

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
///  \class         CatImputerEstimatorImpl
///  \brief         Estimator that reads the imputation strategy value and
///                 creates a `CatImputerTransformer` object.
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class CatImputerEstimatorImpl : public TransformerEstimator<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, TransformedT>;
    using TransformerType                   = CatImputerTransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CatImputerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~CatImputerEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(CatImputerEstimatorImpl);

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
        using ModeAnnotationData            = Components::ModeAnnotationData<InputT>;
        using ModeEstimator                 = Components::ModeEstimator<InputT, false, MaxNumTrainingItemsV>;

        using TheseTraits                   = Traits<InputT>;
        // ----------------------------------------------------------------------

        ModeAnnotationData const &          data(ModeEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::ModeEstimatorName));

        assert(TheseTraits::IsNullableType);
        return std::make_unique<CatImputerTransformer<InputT, TransformedT>>(TheseTraits::GetNullableValue(data.Value));
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         CatImputerEstimator
///  \brief         Creates a `CatImputerTransformer` object.
///
template <
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class CatImputerEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::HistogramEstimator<typename Traits<TransformedT>::nullable_type, MaxNumTrainingItemsV>,
        Components::ModeEstimator<typename Traits<TransformedT>::nullable_type, false, MaxNumTrainingItemsV>,
        Details::CatImputerEstimatorImpl<typename Traits<TransformedT>::nullable_type, TransformedT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::HistogramEstimator<typename Traits<TransformedT>::nullable_type, MaxNumTrainingItemsV>,
            Components::ModeEstimator<typename Traits<TransformedT>::nullable_type, false, MaxNumTrainingItemsV>,
            Details::CatImputerEstimatorImpl<typename Traits<TransformedT>::nullable_type, TransformedT, MaxNumTrainingItemsV>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CatImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~CatImputerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(CatImputerEstimator);
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
// |  CatImputerTransformer
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
CatImputerTransformer<InputT, TransformedT>::CatImputerTransformer(typename BaseType::TransformedType value) :
    Value(std::move(value)) {
}

template <typename InputT, typename TransformedT>
CatImputerTransformer<InputT, TransformedT>::CatImputerTransformer(Archive &ar) :
    Value(Traits<decltype(Value)>::deserialize(ar)) {
}

template <typename InputT, typename TransformedT>
void CatImputerTransformer<InputT, TransformedT>::save(Archive &ar) const /*override*/ {
    Traits<decltype(Value)>::serialize(ar, Value);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
void CatImputerTransformer<InputT, TransformedT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    // ----------------------------------------------------------------------
    using TheseTraits                       = Traits<InputT>;
    // ----------------------------------------------------------------------

    if(TheseTraits::IsNull(input))
        callback(Value);
    else
        callback(TheseTraits::GetNullableValue(input));
}

// ----------------------------------------------------------------------
// |
// |  CatImputerEstimator
// |
// ----------------------------------------------------------------------
template <typename TransformedT, size_t MaxNumTrainingItemsV>
CatImputerEstimator<TransformedT, MaxNumTrainingItemsV>::CatImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "CatImputerEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::HistogramEstimator<typename Traits<TransformedT>::nullable_type, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Components::ModeEstimator<typename Traits<TransformedT>::nullable_type, false, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Details::CatImputerEstimatorImpl<typename Traits<TransformedT>::nullable_type, TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::CatImputerEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
Details::CatImputerEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::CatImputerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("CatImputerEstimatorImpl", std::move(pAllColumnAnnotations)),
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
bool Details::CatImputerEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
FitResult Details::CatImputerEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::fit_impl(typename BaseType::InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This should not be called");
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
void Details::CatImputerEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
