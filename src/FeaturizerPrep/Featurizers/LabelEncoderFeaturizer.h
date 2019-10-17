// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/HistogramEstimator.h"
#include "Components/IndexMapEstimator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {


/////////////////////////////////////////////////////////////////////////
///  \class         CategorizeEstimator
///  \brief         This class retrieves a index map and get the index
///                 of each item in the indexmap. This map is used for generate label
template <typename InputT, typename TransformedT>
class CategorizeEstimator : public TransformerEstimator<InputT const &, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    bool const SuppressUnrecognizedErrors;
    
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                           = TransformerEstimator<InputT const &, TransformedT>;
    using IndexMap                           = std::map<InputT, TransformedT>;

    class Transformer : public BaseType::Transformer {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        Transformer(IndexMap indexmap, bool suppressUnrecognizedErrors);
        Transformer(typename BaseType::Transformer::Archive & ar);
        ~Transformer(void) override = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Transformer);

        typename BaseType::TransformedType execute(typename BaseType::InputType input) override;

        void save(typename BaseType::Transformer::Archive & ar) const override;
        bool operator==(CategorizeEstimator::Transformer const &other) const;
    private:
        // ----------------------------------------------------------------------
        // |
        // |  Private Data
        // |
        // ---------------------------------------------------------------------- 
        IndexMap const                        _indexmap;
        bool     const                        _suppressUnrecognizedErrors;
    };

    using TransformerType                   = Transformer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CategorizeEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool suppressUnrecognizedErrors);
    ~CategorizeEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(CategorizeEstimator);

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
        AnnotationMap::const_iterator const &           iterAnnotations(annotations.find("IndexMapEstimator"));

        if(iterAnnotations == annotations.end())
            throw std::runtime_error("Couldn't retrieve IndexMapEstimator.");

        // An output column can have multiple annotations from same 'kind' of estimator.
        // However, since we have only one estimator- hence the hard-coded value of 0 for retrieval.
        // Expect annotation design to be further rationalized in near future
        // which will address this hard-coding.
        Annotation const &                                                  annotation(*iterAnnotations->second[0]);

        Components::IndexMapAnnotation<InputT, std::uint32_t> const &       IndexMapAnnotation(static_cast<Components::IndexMapAnnotation<InputT, std::uint32_t> const &>(annotation));
        IndexMap const &                                                    indexmap(IndexMapAnnotation.Value);

        return std::make_unique<Transformer>(indexmap, SuppressUnrecognizedErrors);
    }

};

/////////////////////////////////////////////////////////////////////////
///  \class         LabelEncoderEstimator
///  \brief         This class 'chains' HistogramEstimator, IndexMapEstimator and CategorizeEstimator.
///                 HistogramEstimator generates Histogram which is consumed by
///                 IndexMapEstimator to get a index map which is consumed by CategorizeEstimator
///                 to get the category index. Transformed type of Label encoder is fixed to uint32_t,
///                 which has a upper limit of 4294967295.
///
template <typename InputT>
class LabelEncoderEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::HistogramEstimator<InputT, 0>,
        Components::IndexMapEstimator<InputT, std::uint32_t, 0>,
        CategorizeEstimator<InputT, std::uint32_t>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::PipelineExecutionEstimatorImpl<
        Components::HistogramEstimator<InputT, 0>,
        Components::IndexMapEstimator<InputT, std::uint32_t, 0>,
        CategorizeEstimator<InputT, std::uint32_t>
    >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    LabelEncoderEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool const& suppressUnrecognizedErrors = false);

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(LabelEncoderEstimator);
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
// |  CategorizeEstimator
// |
// ----------------------------------------------------------------------

template <typename InputT, typename TransformedT>
CategorizeEstimator<InputT,TransformedT>::CategorizeEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool suppressUnrecognizedErrors) :
    BaseType("CategorizeEstimator", std::move(pAllColumnAnnotations), true),
    SuppressUnrecognizedErrors(suppressUnrecognizedErrors) {
}

template <typename InputT, typename TransformedT>
Estimator::FitResult CategorizeEstimator<InputT,TransformedT>::complete_training_impl(void) {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

// ----------------------------------------------------------------------
// |
// |  CategorizeEstimator::Transformer
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
CategorizeEstimator<InputT, TransformedT>::Transformer::Transformer(IndexMap indexmap, bool suppressUnrecognizedErrors) :
    _indexmap(std::move(indexmap)),
    _suppressUnrecognizedErrors(suppressUnrecognizedErrors){
}

template <typename InputT, typename TransformedT>
CategorizeEstimator<InputT,TransformedT>::Transformer::Transformer(typename BaseType::Transformer::Archive & ar) :
    _indexmap(Traits<IndexMap>::deserialize(ar)),
    _suppressUnrecognizedErrors(Traits<bool>::deserialize(ar))
    {
}

template <typename InputT, typename TransformedT>
typename CategorizeEstimator<InputT, TransformedT>::BaseType::TransformedType CategorizeEstimator<InputT,TransformedT>::Transformer::execute(typename BaseType::InputType input) {
    // suppressUnrecognizedErrors is to specify throw an error or not
    // if suppressUnrecognizedErrors is true, throw an error
    if (Traits<typename BaseType::InputType>::IsNull(input)) {
        // TODO: return appropriate value for null inferencing data
        throw std::runtime_error("null inferencing data is not supported for label encoder yet!");
    }
    if (_indexmap.find(input) != _indexmap.end()) {
        return _indexmap.find(input)->second;
    }
    if(_suppressUnrecognizedErrors) {
        return 0;
    }
    throw std::runtime_error("Throwing an error is enabled when unseen inference data is taken! If you want different behaviours, change the input flag!");
}

template <typename InputT, typename TransformedT>
void CategorizeEstimator<InputT,TransformedT>::Transformer::save(typename CategorizeEstimator<InputT, TransformedT>::BaseType::Transformer::Archive & ar) const {
    Traits<IndexMap>::serialize(ar, _indexmap);
    Traits<bool>::serialize(ar, _suppressUnrecognizedErrors);
}

template <typename InputT, typename TransformedT>
bool CategorizeEstimator<InputT,TransformedT>::Transformer::operator==(CategorizeEstimator<InputT,TransformedT>::Transformer const &other) const {
    return (_indexmap == other._indexmap) && (_suppressUnrecognizedErrors == other._suppressUnrecognizedErrors);
}

// ----------------------------------------------------------------------
// |
// |  LabelEncoderEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT>
LabelEncoderEstimator<InputT>::LabelEncoderEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool const& suppressUnrecognizedErrors) :
    BaseType("LabelEncoderEstimator",
    pAllColumnAnnotations,
    [&pAllColumnAnnotations](void) { return Components::HistogramEstimator<InputT, 0>(pAllColumnAnnotations); },
    [&pAllColumnAnnotations](void) { return Components::IndexMapEstimator<InputT, std::uint32_t, 0>(pAllColumnAnnotations); },
    [&pAllColumnAnnotations, &suppressUnrecognizedErrors](void) { return CategorizeEstimator<InputT, std::uint32_t>(pAllColumnAnnotations, suppressUnrecognizedErrors); }
    ) {
}
}
}
}
