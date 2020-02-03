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
///  \class         MaxAbsScalerTransformer
///  \brief         This class retrieves a MaxAbsValueAnnotation and computes
///                 using the scale.
///
template <typename InputT, typename TransformedT>
class MaxAbsScalerTransformer : public StandardTransformer<InputT, TransformedT> {
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
    MaxAbsScalerTransformer(typename BaseType::TransformedType scale);
    MaxAbsScalerTransformer(Archive & ar);

    ~MaxAbsScalerTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MaxAbsScalerTransformer);

    bool operator==(MaxAbsScalerTransformer const &other) const;

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
///  \class         MaxAbsScalerEstimatorImpl
///  \brief         retrieves a MaxAbsValueAnnotation and computes
///                 using the scale.
///

template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class MaxAbsScalerEstimatorImpl : public TransformerEstimator<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, TransformedT>;
    using TransformerType                   = MaxAbsScalerTransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MaxAbsScalerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~MaxAbsScalerEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MaxAbsScalerEstimatorImpl);

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

        return typename BaseType::TransformerUniquePtr(new MaxAbsScalerTransformer<InputT, TransformedT>(data.Value));
    }
};

} // namespace Details


/////////////////////////////////////////////////////////////////////////
///  \class         MaxAbsScalerEstimator
///  \brief         This class 'chains' MaxAbsValueEstimator and MaxAbsScalerEstimator.
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class MaxAbsScalerEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::MaxAbsValueEstimator<InputT, TransformedT, MaxNumTrainingItemsV>,
        Details::MaxAbsScalerEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::PipelineExecutionEstimatorImpl<
        Components::MaxAbsValueEstimator<InputT, TransformedT, MaxNumTrainingItemsV>,
        Details::MaxAbsScalerEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
    >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MaxAbsScalerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~MaxAbsScalerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MaxAbsScalerEstimator);
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
MaxAbsScalerTransformer<InputT, TransformedT>::MaxAbsScalerTransformer(typename BaseType::TransformedType scale) :
    Scale(std::move(scale)) {
}

template <typename InputT, typename TransformedT>
MaxAbsScalerTransformer<InputT, TransformedT>::MaxAbsScalerTransformer(Archive &ar) :
    MaxAbsScalerTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            return MaxAbsScalerTransformer(Traits<decltype(Scale)>::deserialize(ar));
        }()
    ) {
}

template <typename InputT, typename TransformedT>
bool MaxAbsScalerTransformer<InputT, TransformedT>::operator==(MaxAbsScalerTransformer const &other) const {
#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    return Scale == other.Scale;

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
}

template <typename InputT, typename TransformedT>
void MaxAbsScalerTransformer<InputT, TransformedT>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(Scale)>::serialize(ar, Scale);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
void MaxAbsScalerTransformer<InputT, TransformedT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {

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
// |  Details::MaxAbsScalerEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
Details::MaxAbsScalerEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::MaxAbsScalerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("MaxAbsScalerEstimatorImpl", std::move(pAllColumnAnnotations)),
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
bool Details::MaxAbsScalerEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
FitResult Details::MaxAbsScalerEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::fit_impl(typename BaseType::InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This should not be called");
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
void Details::MaxAbsScalerEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}


// ----------------------------------------------------------------------
// |
// |  MaxAbsScalerEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
MaxAbsScalerEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::MaxAbsScalerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "MaxAbsScalerEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::MaxAbsValueEstimator<InputT, TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Details::MaxAbsScalerEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
