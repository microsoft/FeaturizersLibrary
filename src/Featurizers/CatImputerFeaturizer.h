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
///  \struct         CatImputerTraits
///  \brief         Traits for mapping the input/output types for the CatImptuter.
///                 This allows us to only change one place if typings need to change.
///

template <typename TransformedT>
struct CatImputerTraits{
    using InputType = typename Traits<TransformedT>::nullable_type;

    static_assert(Traits<InputType>::IsNullableType, "'InputT' must be a nullable type");
    static_assert(Traits<TransformedT>::IsNullableType == false || Traits<TransformedT>::IsNativeNullableType, "'TransformedT' must not be a nullable type");
};

/////////////////////////////////////////////////////////////////////////
///  \class         CatImputerTransformer
///  \brief         Transformer that populates null values with the most
///                 frequent value found in the training data set.
///
template <typename TransformedT>
class CatImputerTransformer : public StandardTransformer<typename CatImputerTraits<TransformedT>::InputType, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    
    using InputType                         = typename CatImputerTraits<TransformedT>::InputType;
    using BaseType                          = StandardTransformer<InputType, TransformedT>;
    using TransformedType                   = TransformedT;
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
    CatImputerTransformer(typename TransformedType value);
    CatImputerTransformer(Archive &ar);

    ~CatImputerTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(CatImputerTransformer);

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename InputType const &input, typename BaseType::CallbackFunction const &callback) override;
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         CatImputerEstimatorImpl
///  \brief         Estimator that reads the imputation strategy value and
///                 creates a `CatImputerTransformer` object.
///
template <
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class CatImputerEstimatorImpl : public TransformerEstimator<typename CatImputerTraits<TransformedT>::InputType, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = typename CatImputerTraits<TransformedT>::InputType;
    using BaseType                          = TransformerEstimator<typename InputType, TransformedT>;
    using TransformerType                   = CatImputerTransformer<TransformedT>;

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
    FitResult fit_impl(typename InputType const *, size_t) override;
    void complete_training_impl(void) override;

    // MSVC runs into problems when separating the definition for this method
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        // ----------------------------------------------------------------------
        using ModeAnnotationData            = Components::ModeAnnotationData<InputType>;
        using ModeEstimator                 = Components::ModeEstimator<InputType, false, MaxNumTrainingItemsV>;

        using TheseTraits                   = Traits<InputType>;
        // ----------------------------------------------------------------------

        ModeAnnotationData const &          data(ModeEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::ModeEstimatorName));

        assert(TheseTraits::IsNullableType);
        return std::make_unique<CatImputerTransformer<TransformedT>>(TheseTraits::GetNullableValue(data.Value));
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
        Components::HistogramEstimator<typename CatImputerTraits<TransformedT>::InputType, MaxNumTrainingItemsV>,
        Components::ModeEstimator<typename CatImputerTraits<TransformedT>::InputType, false, MaxNumTrainingItemsV>,
        Details::CatImputerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::HistogramEstimator<typename CatImputerTraits<TransformedT>::InputType, MaxNumTrainingItemsV>,
            Components::ModeEstimator<typename CatImputerTraits<TransformedT>::InputType, false, MaxNumTrainingItemsV>,
            Details::CatImputerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>
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
template <typename TransformedT>
CatImputerTransformer<TransformedT>::CatImputerTransformer(typename TransformedType value) :
    Value(std::move(value)) {
}

template <typename TransformedT>
CatImputerTransformer<TransformedT>::CatImputerTransformer(Archive &ar) :
    Value(Traits<decltype(Value)>::deserialize(ar)) {
}

template <typename TransformedT>
void CatImputerTransformer<TransformedT>::save(Archive &ar) const /*override*/ {
    Traits<decltype(Value)>::serialize(ar, Value);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename TransformedT>
void CatImputerTransformer<TransformedT>::execute_impl(typename InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    // ----------------------------------------------------------------------
    using TheseTraits                       = Traits<InputType>;
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
        [pAllColumnAnnotations, colIndex](void) { return Components::HistogramEstimator<typename CatImputerTraits<TransformedT>::InputType, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Components::ModeEstimator<typename CatImputerTraits<TransformedT>::InputType, false, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Details::CatImputerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::CatImputerEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename TransformedT, size_t MaxNumTrainingItemsV>
Details::CatImputerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>::CatImputerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
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
template <typename TransformedT, size_t MaxNumTrainingItemsV>
bool Details::CatImputerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename TransformedT, size_t MaxNumTrainingItemsV>
FitResult Details::CatImputerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>::fit_impl(typename InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This should not be called");
}

template <typename TransformedT, size_t MaxNumTrainingItemsV>
void Details::CatImputerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
