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
///  \class         MaxAbsScalarEstimator
///  \brief         This class retrieves a MaxAbsValueAnnotation and computes
///                 using the scale. 
///
template <typename InputT,typename TransformedT>
class MaxAbsScalarEstimator : public TransformerEstimator<InputT const &, TransformedT> {
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
        Transformer(TransformedT scale);
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
        TransformedT const                            _scale;
    };

    using TransformerType                        = Transformer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    MaxAbsScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~MaxAbsScalarEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(MaxAbsScalarEstimator);

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
 
        AnnotationMap const &                           annotations(maps[0]);
        AnnotationMap::const_iterator const &           iterAnnotations(annotations.find("MaxAbsValueEstimator"));

        if(iterAnnotations == annotations.end())
            throw std::runtime_error("Couldn't retrieve MaxAbsValueAnnotation.");

        
        Annotation const &                              annotation(*iterAnnotations->second[0]);

        MaxAbsValueAnnotation<InputT, TransformedT> const &       
                                                        maxAbsValueAnnotation(static_cast<MaxAbsValueAnnotation<InputT, TransformedT> const &>(annotation));
        
        TransformedT const &                            scale(maxAbsValueAnnotation.MaxAbsVal);
      
        return std::make_unique<Transformer>(scale);
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
// |  MaxAbsScalarEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT,typename TransformedT>
MaxAbsScalarEstimator<InputT,TransformedT>::MaxAbsScalarEstimator(AnnotationMapsPtr pAllColumnAnnotations):
    BaseType("MaxAbsScalarEstimator", std::move(pAllColumnAnnotations), true) {
}

template <typename InputT,typename TransformedT>
Estimator::FitResult MaxAbsScalarEstimator<InputT, TransformedT>::complete_training_impl(void) {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

// ----------------------------------------------------------------------
// |
// |  MaxAbsScalarEstimator::Transformer
// |
// ----------------------------------------------------------------------
template <typename InputT,typename TransformedT>
MaxAbsScalarEstimator<InputT,TransformedT>::Transformer::Transformer(TransformedT scale) :
    _scale(std::move(scale)) {
}

template <typename InputT,typename TransformedT>
MaxAbsScalarEstimator<InputT,TransformedT>::Transformer::Transformer(typename BaseType::Transformer::Archive & ar) : 
    _scale(Traits<TransformedT>::deserialize(ar)) {
}

template <typename InputT,typename TransformedT>
typename MaxAbsScalarEstimator<InputT,TransformedT>::BaseType::TransformedType MaxAbsScalarEstimator<InputT,TransformedT>::Transformer::execute(typename BaseType::InputType input) {
    return static_cast<TransformedT>(input) / _scale; 
}

template <typename InputT,typename TransformedT>
void MaxAbsScalarEstimator<InputT,TransformedT>::Transformer::save(typename MaxAbsScalarEstimator<InputT,TransformedT>::BaseType::Transformer::Archive & ar) const {
    Traits<TransformedT>::serialize(ar, _scale);
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
