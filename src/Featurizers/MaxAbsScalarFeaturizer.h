// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "../Featurizer.h"
#include "../Traits.h"

#include "Components/MaxAbsValueEstimator.h"
#include "Components/PipelineExecutionEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {


/////////////////////////////////////////////////////////////////////////
///  \class         MaxAbsScalarTransformer
///  \brief         This class retrieves a MaxAbsValueAnnotation and computes
///                 using the scale.
///
template <typename InputT,typename TransformedT>
class MaxAbsScalarTransformer : public StandardTransformer<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                         = StandardTransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    typename BaseType::TransformedType const            Scale;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MaxAbsScalarTransformer(typename BaseType::TransformedType scale);
    MaxAbsScalarTransformer(Archive & ar);

    ~MaxAbsScalarTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MaxAbsScalarTransformer);

    void save(Archive & ar) const override;

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
///  \class         MaxAbsScalarEstimatorImpl
///  \brief         retrieves a MaxAbsValueAnnotation and computes
///                 using the scale.
///

template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class MaxAbsScalarEstimatorImpl : public TransformerEstimator<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, TransformedT>;
    using TransformerType                   = MaxAbsScalarTransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MaxAbsScalarEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~MaxAbsScalarEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MaxAbsScalarEstimatorImpl);

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
        using MaxAbsValueAnnotationData       = Components::MaxAbsValueAnnotationData<TransformedT>;
        using MaxAbsValueEstimator            = Components::MaxAbsValueEstimator<InputT, TransformedT, MaxNumTrainingItemsV>;

        // ----------------------------------------------------------------------

        MaxAbsValueAnnotationData const &     data(MaxAbsValueEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::MaxAbsValueEstimatorName));

        return std::make_unique<MaxAbsScalarTransformer<InputT, TransformedT>>(data.Value);
    }
};

} // namespace Details


/////////////////////////////////////////////////////////////////////////
///  \class         MaxAbsScalarEstimator
///  \brief         This class 'chains' MaxAbsValueEstimator and MaxAbsScalarEstimator.
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class MaxAbsScalarEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::MaxAbsValueEstimator<InputT, TransformedT, MaxNumTrainingItemsV>,
        Details::MaxAbsScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::PipelineExecutionEstimatorImpl<
        Components::MaxAbsValueEstimator<InputT, TransformedT, MaxNumTrainingItemsV>,
        Details::MaxAbsScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
    >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MaxAbsScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~MaxAbsScalarEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MaxAbsScalarEstimator);
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
MaxAbsScalarTransformer<InputT, TransformedT>::MaxAbsScalarTransformer(typename BaseType::TransformedType scale) :
    Scale(std::move(scale)) {
}

template <typename InputT, typename TransformedT>
MaxAbsScalarTransformer<InputT, TransformedT>::MaxAbsScalarTransformer(Archive &ar) :
    Scale(Traits<decltype(Scale)>::deserialize(ar)) {
}

template <typename InputT, typename TransformedT>
void MaxAbsScalarTransformer<InputT, TransformedT>::save(Archive &ar) const /*override*/ {
    Traits<decltype(Scale)>::serialize(ar, Scale);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
void MaxAbsScalarTransformer<InputT, TransformedT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    if (Scale != static_cast<TransformedT>(0)) {
        callback(static_cast<TransformedT>(input) / Scale);
        return;
    }

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

    callback(static_cast<TransformedT>(input));
}


// ----------------------------------------------------------------------
// |
// |  Details::MaxAbsScalarEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
Details::MaxAbsScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::MaxAbsScalarEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("MaxAbsScalarEstimatorImpl", std::move(pAllColumnAnnotations)),
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
bool Details::MaxAbsScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
FitResult Details::MaxAbsScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::fit_impl(typename BaseType::InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This should not be called");
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
void Details::MaxAbsScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}


// ----------------------------------------------------------------------
// |
// |  MaxAbsScalarEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
MaxAbsScalarEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::MaxAbsScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "MaxAbsScalarEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::MaxAbsValueEstimator<InputT, TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Details::MaxAbsScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
