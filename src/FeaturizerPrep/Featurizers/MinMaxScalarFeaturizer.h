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
///  \class         MMScalingEstimator
///  \brief         This class retrieves max and min value and scale based on these two values
template <typename InputT>
class MMScalingEstimator : public TransformerEstimator<InputT const &, std::double_t> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TransformedType                    = std::double_t;
    using BaseType                           = TransformerEstimator<InputT const &, TransformedType>;

    class Transformer : public BaseType::Transformer {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        Transformer(TransformedType min, TransformedType max);
        Transformer(typename BaseType::Transformer::Archive & ar);
        ~Transformer(void) override = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Transformer);

        typename BaseType::TransformedType execute(typename BaseType::InputType input) override;

        void save(typename BaseType::Transformer::Archive & ar) const override;

        bool operator==(MMScalingEstimator::Transformer const &other) const;
    private:
        // ----------------------------------------------------------------------
        // |
        // |  Private Data
        // |
        // ---------------------------------------------------------------------- 
        TransformedType const                        _min;
        TransformedType const                        _max;
    };

    using TransformerType                         = Transformer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MMScalingEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~MMScalingEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MMScalingEstimator);
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems when the function is defined outside of the declaration
    Estimator::FitResult fit_impl(typename BaseType::BaseType::FitBufferInputType *, size_t) override {
        throw std::runtime_error("This should never be called as this class will not be used during training");
    }

    Estimator::FitResult complete_training_impl(void) override;

    //The MSVC compiler will complain when the definition is outside the declaration 
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        AnnotationMaps const &                          maps(Estimator::get_column_annotations());
        // Currently Annnotations are per output column index (0-based)
        // Since we've only one column as output- hardcoding this to 0 now.
        // Expect annotation design to be further rationalized in near future
        // which will address this hard-coding.
        AnnotationMap const &                           annotations(maps[0]);
        AnnotationMap::const_iterator const &           iterAnnotations(annotations.find("MinMaxEstimator"));

        if(iterAnnotations == annotations.end())
            throw std::runtime_error("Couldn't retrieve MinMaxEstimator.");

        // An output column can have multiple annotations from same 'kind' of estimator.
        // However, since we have only one estimator- hence the hard-coded value of 0 for retrieval.
        // Expect annotation design to be further rationalized in near future
        // which will address this hard-coding.
        Annotation const &                                                  annotation(*iterAnnotations->second[0]);

        Components::MinMaxAnnotation<InputT> const &                        minMaxAnnotation(static_cast<Components::MinMaxAnnotation<InputT> const &>(annotation));
        InputT                               const &                        max(minMaxAnnotation.Max);
        InputT                               const &                        min(minMaxAnnotation.Min);
        return std::make_unique<Transformer>(static_cast<TransformedType>(min), static_cast<TransformedType>(max));
    }
};


/////////////////////////////////////////////////////////////////////////
///  \class         MinMaxScalarEstimator
///  \brief         This class 'chains' MinMaxEstimator which find out min and max value,
///                 and MMScalingEstimator which transforms into values in (0,1) range
///
template <typename InputT>
class MinMaxScalarEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::MinMaxEstimator<InputT, 0>,
        MMScalingEstimator<InputT>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::PipelineExecutionEstimatorImpl<
        Components::MinMaxEstimator<InputT, 0>,
        MMScalingEstimator<InputT>
    >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MinMaxScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations);

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
// |  MMScalingEstimator
// |
// ----------------------------------------------------------------------

template <typename InputT>
MMScalingEstimator<InputT>::MMScalingEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("MMScalingEstimator", std::move(pAllColumnAnnotations), true) {
}

template <typename InputT>
Estimator::FitResult MMScalingEstimator<InputT>::complete_training_impl(void) {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

// ----------------------------------------------------------------------
// |
// |  MMScalingEstimator::Transformer
// |
// ----------------------------------------------------------------------
template <typename InputT>
MMScalingEstimator<InputT>::Transformer::Transformer(TransformedType min, TransformedType max) :
    _min(std::move(min)),
    _max(std::move(max)){
}

template <typename InputT>
MMScalingEstimator<InputT>::Transformer::Transformer(typename BaseType::Transformer::Archive & ar) :
    _min(Traits<TransformedType>::deserialize(ar)),
    _max(Traits<TransformedType>::deserialize(ar))
    {
}
#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif
template <typename InputT>
typename MMScalingEstimator<InputT>::BaseType::TransformedType MMScalingEstimator<InputT>::Transformer::execute(typename BaseType::InputType input) {
    if (Traits<typename BaseType::InputType>::IsNull(input)) {
        // if input is null, it will be disregarded in fit and maintain in transform
        return  Traits<typename BaseType::TransformedType>::CreateNullValue();
    }
    // comparing two floats warning is ignored
    if (_max == _min) {
        // there is only one value in training set, the output is set to 0
        return static_cast<TransformedType>(0);
    }
    
    return (static_cast<TransformedType>(input) - _min) / (_max - _min);
}

template <typename InputT>
bool MMScalingEstimator<InputT>::Transformer::operator==(MMScalingEstimator<InputT>::Transformer const &other) const {
    
    return _min == other._min && _max == other._max;

}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

template <typename InputT>
void MMScalingEstimator<InputT>::Transformer::save(typename MMScalingEstimator<InputT>::BaseType::Transformer::Archive & ar) const {
    Traits<TransformedType>::serialize(ar, _min);
    Traits<TransformedType>::serialize(ar, _max);
}

// ----------------------------------------------------------------------
// |
// |  MinMaxScalarEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT>
MinMaxScalarEstimator<InputT>::MinMaxScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("MinMaxScalarEstimator", std::move(pAllColumnAnnotations)) {
}
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
