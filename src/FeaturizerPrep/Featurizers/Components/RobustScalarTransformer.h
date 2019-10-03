// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../../Archive.h"
#include "../../Featurizer.h"
#include "../../Traits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

/////////////////////////////////////////////////////////////////////////
///  \class         RobustScalarEstimator
///  \brief         This class retrieves a RobustScalarNormAnnotation and computes
///                 the scale. 
///
template <typename InputT,typename TransformedT>
class RobustScalarEstimator : public TransformerEstimator<InputT const &, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                               = TransformerEstimator<InputT const &, TransformedT>;
    
    class Transformer : public BaseType::Transformer {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        Transformer(TransformedT median, TransformedT scale);
        Transformer(typename BaseType::Transformer::Archive & ar);
        ~Transformer(void) override = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Transformer);

        typename BaseType::TransformedType execute(typename BaseType::InputType input) override;

        void save(typename BaseType::Transformer::Archive & ar) const override;

    private:
        // ----------------------------------------------------------------------
        // |
        // |  Private Data
        // |
        // ---------------------------------------------------------------------- 
        TransformedT const                            _median;
        TransformedT const                            _scale;
    };

    using TransformerType                        = Transformer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    RobustScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~RobustScalarEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(RobustScalarEstimator);

private:    
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    //The MSVC compiler will complain when the definition is outside the declaration 
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
        AnnotationMap::const_iterator const &           iterAnnotations(annotations.find("RobustScalarNormEstimator"));

        if(iterAnnotations == annotations.end())
            throw std::runtime_error("Couldn't retrieve NormAnnotation.");

        // An output column can have multiple annotations from same 'kind' of estimator.
        // However, since we have only one estimator- hence the hard-coded value of 0 for retrieval.
        // Expect annotation design to be further rationalized in near future
        // which will address this hard-coding.
        Annotation const &                              annotation(*iterAnnotations->second[0]);

        RobustScalarNormAnnotation<InputT, TransformedT> const &       
                                                        normAnnotation(static_cast<RobustScalarNormAnnotation<InputT, TransformedT> const &>(annotation));
        
        TransformedT const &                            median(normAnnotation.Median);
        TransformedT const &                            scale(normAnnotation.Scale);
      
        return std::make_unique<Transformer>(median, scale);
    }
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
// |  RobustScalarEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT,typename TransformedT>
RobustScalarEstimator<InputT,TransformedT>::RobustScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations):
    BaseType("RobustScalarEstimator", std::move(pAllColumnAnnotations), true) {
}

template <typename InputT,typename TransformedT>
Estimator::FitResult RobustScalarEstimator<InputT, TransformedT>::complete_training_impl(void) {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

// ----------------------------------------------------------------------
// |
// |  RobustScalarEstimator::Transformer
// |
// ----------------------------------------------------------------------
template <typename InputT,typename TransformedT>
RobustScalarEstimator<InputT,TransformedT>::Transformer::Transformer(TransformedT median, TransformedT scale) :
    _median(std::move(median)),
    _scale(std::move(scale)) {
}

template <typename InputT,typename TransformedT>
RobustScalarEstimator<InputT,TransformedT>::Transformer::Transformer(typename BaseType::Transformer::Archive & ar) {
    Transformer(Traits<TransformedT>::deserialize(ar), Traits<TransformedT>::deserialize(ar));
}

template <typename InputT,typename TransformedT>
typename RobustScalarEstimator<InputT,TransformedT>::BaseType::TransformedType RobustScalarEstimator<InputT,TransformedT>::Transformer::execute(typename BaseType::InputType input) {
    return (static_cast<TransformedT>(input) - _median) / _scale; 
}

template <typename InputT,typename TransformedT>
void RobustScalarEstimator<InputT,TransformedT>::Transformer::save(typename RobustScalarEstimator<InputT,TransformedT>::BaseType::Transformer::Archive & ar) const {
    Traits<TransformedT>::serialize(ar, _median);
    Traits<TransformedT>::serialize(ar, _scale);
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
