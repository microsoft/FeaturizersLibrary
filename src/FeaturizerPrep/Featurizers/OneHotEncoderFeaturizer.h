// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/HistogramEstimator.h"
#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/IndexMapEstimator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
   
/////////////////////////////////////////////////////////////////////////
///  \struct        OneHotStruct
///  \brief         Struct to hold return value of one hot encoder,
///                 consist of <category index, total size of category, # of appearances>
///
struct OneHotStruct {
    std::uint32_t index;
    std::uint32_t size;
    std::uint32_t appearances;
    bool operator==(OneHotStruct const &other) const;
};

/////////////////////////////////////////////////////////////////////////
///  \class         OneHotEstimator
///  \brief         This class retrieves a index map and get the index
///                 of each item in the index map. This map is used for generate one hot encoder struct
template <typename InputT, typename TransformedT>
class OneHotEstimator : public TransformerEstimator<InputT const &, TransformedT> {
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
    using IndexMap                           = std::map<InputT, std::uint32_t>;
    using Histogram                          = std::map<InputT, std::uint32_t>;

    class Transformer : public BaseType::Transformer {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        Transformer(IndexMap indexmap, Histogram histogram, bool suppressUnrecognizedErrors);
        Transformer(typename BaseType::Transformer::Archive & ar);
        ~Transformer(void) override = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Transformer);

        typename BaseType::TransformedType execute(typename BaseType::InputType input) override;

        void save(typename BaseType::Transformer::Archive & ar) const override;

        bool operator==(OneHotEstimator::Transformer const &other) const;
    private:
        // ----------------------------------------------------------------------
        // |
        // |  Private Data
        // |
        // ---------------------------------------------------------------------- 
        IndexMap  const                        _indexmap;
        Histogram const                        _histogram;
        bool      const                        _suppressUnrecognizedErrors;
    };

    using TransformerType                    = Transformer;
    
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    OneHotEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool suppressUnrecognizedErrors);
    ~OneHotEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(OneHotEstimator);

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
        AnnotationMap::const_iterator const &           iterAnnotationsIndexMap(annotations.find("IndexMapEstimator"));
        AnnotationMap::const_iterator const &           iterAnnotationsHistogram(annotations.find("HistogramEstimator"));

        if(iterAnnotationsIndexMap == annotations.end())
            throw std::runtime_error("Couldn't retrieve IndexMapEstimator.");
        if(iterAnnotationsHistogram == annotations.end())
            throw std::runtime_error("Couldn't retrieve HistogramEstimator.");

        // An output column can have multiple annotations from same 'kind' of estimator.
        // However, since we have only one estimator- hence the hard-coded value of 0 for retrieval.
        // Expect annotation design to be further rationalized in near future
        // which will address this hard-coding.
        Annotation const &                              annotationIndexMap(*iterAnnotationsIndexMap->second[0]);
        Annotation const &                              annotationHistogram(*iterAnnotationsHistogram->second[0]);


        Components::IndexMapAnnotation<InputT, std::uint32_t> const & IndexMapAnnotation(static_cast<Components::IndexMapAnnotation<InputT, std::uint32_t> const &>(annotationIndexMap));
        Components::HistogramAnnotation<InputT> const & HistogramAnnotation(static_cast<Components::HistogramAnnotation<InputT> const &>(annotationHistogram));

        IndexMap const &                                indexmap(IndexMapAnnotation.Value);
        Histogram const &                               histogram(HistogramAnnotation.Value);

        return std::make_unique<Transformer>(indexmap, histogram, SuppressUnrecognizedErrors);
    }

};

/////////////////////////////////////////////////////////////////////////
///  \class         OneHotEncoderEstimator
///  \brief         This class 'chains' HistogramEstimator, IndexMapEstimator and OneHotEstimator
///                 to generate a struct according to the input category. The struct is built with
///                 <category index, total # of categories, # of appearance>. The type of category index,
///                 total # of categories are fixed to uint32_t, which has a upper limit of 4294967295.
///                 # of appearance is also in type uint32_t to align with histogram estimator
///
template <typename InputT>
class OneHotEncoderEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::HistogramEstimator<InputT, 0>,
        Components::IndexMapEstimator<InputT, std::uint32_t, 0>,
        OneHotEstimator<InputT, OneHotStruct>
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
        OneHotEstimator<InputT, OneHotStruct>
    >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    OneHotEncoderEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool const& suppressUnrecognizedErrors = false);

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(OneHotEncoderEstimator);
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
// |  OneHotStruct
// |
// ----------------------------------------------------------------------

bool OneHotStruct::operator==(OneHotStruct const &other) const {
    return (appearances == other.appearances) && (index == other.index) && (size == other.size);
}

// ----------------------------------------------------------------------
// |
// |  OneHotEstimator
// |
// ----------------------------------------------------------------------

template <typename InputT, typename TransformedT>
OneHotEstimator<InputT,TransformedT>::OneHotEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool suppressUnrecognizedErrors) :
    BaseType("OneHotEstimator", std::move(pAllColumnAnnotations), true),
    SuppressUnrecognizedErrors(suppressUnrecognizedErrors) {
}

template <typename InputT, typename TransformedT>
Estimator::FitResult OneHotEstimator<InputT, TransformedT>::complete_training_impl(void) {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

// ----------------------------------------------------------------------
// |
// |  OneHotEstimator::Transformer
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
OneHotEstimator<InputT, TransformedT>::Transformer::Transformer(IndexMap indexmap, Histogram histogram, bool suppressUnrecognizedErrors) :
    _indexmap(std::move(indexmap)),
    _histogram(std::move(histogram)),
    _suppressUnrecognizedErrors(suppressUnrecognizedErrors) {
}

template <typename InputT, typename TransformedT>
OneHotEstimator<InputT, TransformedT>::Transformer::Transformer(typename BaseType::Transformer::Archive & ar) :
    _indexmap(Traits<IndexMap>::deserialize(ar)),
    _histogram(Traits<Histogram>::deserialize(ar)),
    _suppressUnrecognizedErrors(Traits<bool>::deserialize(ar)) {
}
template <typename InputT, typename TransformedT>
typename OneHotEstimator<InputT, TransformedT>::BaseType::TransformedType OneHotEstimator<InputT,TransformedT>::Transformer::execute(typename BaseType::InputType input) {
    // suppressUnrecognizedErrors is to specify throw an error or not
    // if suppressUnrecognizedErrors is true, throw an error
    
    #if (defined _MSC_VER)
    #   pragma warning(push)
    #   pragma warning(disable: 4267) // possible loss of data
    #endif

    if (Traits<typename BaseType::InputType>::IsNull(input)) {
        // TODO: return appropriate value for null inferencing data
        throw std::runtime_error("null inferencing data is not supported for one hot encoder yet!");
    }
    if (_indexmap.find(input) != _indexmap.end()) {
        return OneHotStruct{static_cast<std::uint32_t>(_indexmap.find(input)->second),   // category index
                            static_cast<std::uint32_t>(_indexmap.size()),                // category total size
                            static_cast<std::uint32_t>(_histogram.find(input)->second)   // number of appearances
        };   
    }
    if(_suppressUnrecognizedErrors) {
        return OneHotStruct{static_cast<std::uint32_t>(0),
                            static_cast<std::uint32_t>(_indexmap.size()),
                            static_cast<std::uint32_t>(0)
        };
    }
    throw std::runtime_error("Throwing an error is enabled when unseen inference data is taken! If you want different behaviours, change the input flag!");
    
    #if (defined _MSC_VER)
    #   pragma warning(pop)
    #endif
}

template <typename InputT, typename TransformedT>
void OneHotEstimator<InputT,TransformedT>::Transformer::save(typename OneHotEstimator<InputT,TransformedT>::BaseType::Transformer::Archive & ar) const {
    Traits<IndexMap>::serialize(ar, _indexmap);
    Traits<Histogram>::serialize(ar, _histogram);
    Traits<bool>::serialize(ar, _suppressUnrecognizedErrors);
}

template <typename InputT, typename TransformedT>
bool OneHotEstimator<InputT,TransformedT>::Transformer::operator==(OneHotEstimator<InputT,TransformedT>::Transformer const &other) const {
    return (_indexmap == other._indexmap) && (_histogram == other._histogram) && (_suppressUnrecognizedErrors==other._suppressUnrecognizedErrors);
}

// ----------------------------------------------------------------------
// |
// |  OneHotEncoderEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT>
OneHotEncoderEstimator<InputT>::OneHotEncoderEstimator(AnnotationMapsPtr pAllColumnAnnotations, bool const& suppressUnrecognizedErrors) :
    BaseType("OneHotEncoderEstimator",
    pAllColumnAnnotations,
    [&pAllColumnAnnotations](void) { return Components::HistogramEstimator<InputT, 0>(pAllColumnAnnotations); },
    [&pAllColumnAnnotations](void) { return Components::IndexMapEstimator<InputT, std::uint32_t, 0>(pAllColumnAnnotations); },
    [&pAllColumnAnnotations, &suppressUnrecognizedErrors](void) { return OneHotEstimator<InputT, OneHotStruct>(pAllColumnAnnotations, suppressUnrecognizedErrors); }
    ) {
}
}
}
}
