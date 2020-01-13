// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/MinMaxEstimator.h"
#include "Components/PipelineExecutionEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         MinMaxScalarTransformer
///  \brief         Scales values based on learned min and max values.
///
template <
    typename InputT,
    typename TransformedT=std::double_t
>
class MinMaxScalarTransformer : public StandardTransformer<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<TransformedT>::IsNullableType, "'TransformedT' must be a nullable type");

    using BaseType                          = StandardTransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MinMaxScalarTransformer(typename BaseType::InputType min, typename BaseType::InputType max);
    MinMaxScalarTransformer(Archive &ar);

    ~MinMaxScalarTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MinMaxScalarTransformer);

    bool operator==(MinMaxScalarTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    typename BaseType::InputType const      _min;
    typename BaseType::InputType const      _span;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override;

    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback, std::true_type);
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback, std::false_type);

    template <typename U>
    void execute_implex(U const &input, typename BaseType::CallbackFunction const &callback);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         MinMaxScalarEstimatorImpl
///  \brief         Estimator that reads an annotation created by the `MinMaxEstimator`
///                 and creates a `MinMaxScalarTransformer` object.
///
template <
    typename InputT,
    typename TransformedT=std::double_t,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class MinMaxScalarEstimatorImpl : public TransformerEstimator<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, TransformedT>;
    using TransformerType                   = MinMaxScalarTransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MinMaxScalarEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~MinMaxScalarEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MinMaxScalarEstimatorImpl);

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

    // MSVC has problems when the definition is separate from the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        // ----------------------------------------------------------------------
        using MinMaxAnnotationData          = Components::MinMaxAnnotationData<InputT>;
        using MinMaxEstimator               = Components::MinMaxEstimator<InputT, MaxNumTrainingItemsV>;
        // ----------------------------------------------------------------------

        MinMaxAnnotationData const &        data(MinMaxEstimator::get_annotation_data(this->get_column_annotations(), _colIndex, Components::MinMaxEstimatorName));

        return typename BaseType::TransformerUniquePtr(new MinMaxScalarTransformer<InputT, TransformedT>(data.Min, data.Max));
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         MinMaxScalarFeaturizer
///  \brief         Creates the `MinMaxScalarTransformer` object.
///
template <
    typename InputT,
    typename TransformedT=std::double_t,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class MinMaxScalarEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::MinMaxEstimator<InputT, MaxNumTrainingItemsV>,
        Details::MinMaxScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::MinMaxEstimator<InputT, MaxNumTrainingItemsV>,
            Details::MinMaxScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MinMaxScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~MinMaxScalarEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MinMaxScalarEstimator);
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
// |  MinMaxScalarTransformer
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
MinMaxScalarTransformer<InputT, TransformedT>::MinMaxScalarTransformer(typename BaseType::InputType min, typename BaseType::InputType max) :
    _min(std::move(min)),
    _span(
        [this, &max](void) -> typename BaseType::InputType {
            if(this->_min > max)
                throw std::invalid_argument("max");

            return max - this->_min;
        }()
    ) {
}

template <typename InputT, typename TransformedT>
MinMaxScalarTransformer<InputT, TransformedT>::MinMaxScalarTransformer(Archive &ar) :
    MinMaxScalarTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            typename BaseType::InputType    min(Traits<typename BaseType::InputType>::deserialize(ar));
            typename BaseType::InputType    max(Traits<typename BaseType::InputType>::deserialize(ar));

            return MinMaxScalarTransformer<InputT, TransformedT>(std::move(min), std::move(max));
        }()
    ) {
}

template <typename InputT, typename TransformedT>
bool MinMaxScalarTransformer<InputT, TransformedT>::operator==(MinMaxScalarTransformer const &other) const {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    return this->_min == other._min
        && this->_span == other._span;

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

}

template <typename InputT, typename TransformedT>
void MinMaxScalarTransformer<InputT, TransformedT>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(_min)>::serialize(ar, _min);

    // Note that we are serializing the max value rather than just the span so
    // that we can deserialize in a way that is consistent with the constructor's
    // parameters (min, max).
    Traits<decltype(_span)>::serialize(ar, _min + _span);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
void MinMaxScalarTransformer<InputT, TransformedT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    execute_impl(input, callback, std::integral_constant<bool, Microsoft::Featurizer::Traits<InputT>::IsNullableType>());
}

template <typename InputT, typename TransformedT>
void MinMaxScalarTransformer<InputT, TransformedT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback, std::true_type) {
    // ----------------------------------------------------------------------
    using InputTraits                       = Traits<InputT>;
    using TransformedTraits                 = Traits<TransformedT>;
    // ----------------------------------------------------------------------

    if(InputTraits::IsNull(input)) {
        callback(TransformedTraits::CreateNullValue());
        return;
    }

    execute_implex(InputTraits::GetNullableValue(input), callback);
}

template <typename InputT, typename TransformedT>
void MinMaxScalarTransformer<InputT, TransformedT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback, std::false_type) {
    execute_implex(input, callback);
}

template <typename InputT, typename TransformedT>
template <typename U>
void MinMaxScalarTransformer<InputT, TransformedT>::execute_implex(U const &input, typename BaseType::CallbackFunction const &callback) {
#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    if(_span == static_cast<InputT>(0)) {
        callback(static_cast<TransformedT>(0));
        return;
    }

    callback((static_cast<TransformedT>(input) - _min) / _span);

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
}

// ----------------------------------------------------------------------
// |
// |  MinMaxScalarEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
MinMaxScalarEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::MinMaxScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "MinMaxScalarEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::MinMaxEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Details::MinMaxScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::MinMaxScalarEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
Details::MinMaxScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::MinMaxScalarEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("MinMaxScalarEstimatorImpl", std::move(pAllColumnAnnotations)),
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
bool Details::MinMaxScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
FitResult Details::MinMaxScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::fit_impl(typename BaseType::InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This will never be called");
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
void Details::MinMaxScalarEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
