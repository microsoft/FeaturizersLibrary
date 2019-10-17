// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../../Featurizer.h"
#include "../../Traits.h"
#include "HistogramEstimator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

/////////////////////////////////////////////////////////////////////////
///  \class         IndexMapAnnotation
///  \brief         This is an annotation class which holds all the values and corresponding
///                 index for an input column. This is just a modify on the annotation
///                 so the result would be set to complete in the constrcutor
///
template <typename KeyT, typename IndexT>
class IndexMapAnnotation : public Annotation {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    // index map is a map of <category, <index, # of appearance>>
    // Index template is input, # of appearance type is aligned with histogram type, std::uint32_t
    using IndexMap                          = std::map<KeyT, IndexT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    IndexMap const                           Value;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    IndexMapAnnotation(IndexMap value);
    ~IndexMapAnnotation(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(IndexMapAnnotation);
};

/////////////////////////////////////////////////////////////////////////
///  \class         IndexMapEstimator
///  \brief         This class computes the index map for an input column
///                 and creates a IndexMapAnnotation.
///
template <typename InputT, typename TransformedT, size_t ColIndexV>
class IndexMapEstimator : public AnnotationEstimator<InputT const &> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using NonRefType                         = typename std::remove_cv<typename std::remove_reference<InputT>::type>::type;
    using IndexMap                           = std::map<NonRefType, TransformedT>;
    using Histogram                          = std::map<NonRefType, std::uint32_t>;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    IndexMapEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~IndexMapEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(IndexMapEstimator);

    static IndexMap create_index_map_from_histogram(Histogram const& histogram);
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                           = AnnotationEstimator<InputT const &>;
    using TraitsT                            = Traits<NonRefType>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    Estimator::FitResult fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) override;

    Estimator::FitResult complete_training_impl(void) override;
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
// |  IndexMapAnnotation
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
IndexMapAnnotation<InputT, TransformedT>::IndexMapAnnotation(IndexMap t_value) :
    Annotation(this),
    Value(std::move(t_value)) {
        static_assert(Traits<TransformedT>::IsUnsignedInt::value, "Category index type must be unsigned!");
}
// ----------------------------------------------------------------------
// |
// |  IndexMapEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t ColIndexV>
IndexMapEstimator<InputT,TransformedT,ColIndexV>::IndexMapEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    AnnotationEstimator<InputT const &>("IndexMapEstimator", std::move(pAllColumnAnnotations)) {
}

template <typename InputT, typename TransformedT, size_t ColIndexV>
typename IndexMapEstimator<InputT,TransformedT,ColIndexV>::IndexMap IndexMapEstimator<InputT,TransformedT,ColIndexV>::create_index_map_from_histogram(IndexMapEstimator<InputT,TransformedT,ColIndexV>::Histogram const & t_histogram) {
    TransformedT index = 1;
    IndexMap indexmap;
    for (auto const &kvp : t_histogram) {
        if(indexmap.find(kvp.first) == indexmap.end()) {
            indexmap.insert(std::make_pair(kvp.first, index));
            ++index;
        }
    }
    return indexmap;
}

template <typename InputT, typename TransformedT, size_t ColIndexV>
Estimator::FitResult IndexMapEstimator<InputT,TransformedT,ColIndexV>::fit_impl(typename BaseType::FitBufferInputType const *, size_t) {
    // we are not doing any fit in this estimator,
    // instead we create annotation from another annotation,
    // so we can just complete the generation in complete_training_impl
    return Estimator::FitResult::Complete;
}

template <typename InputT, typename TransformedT, size_t ColIndexV>
Estimator::FitResult IndexMapEstimator<InputT,TransformedT,ColIndexV>::complete_training_impl(void) {
    // Retrieve Histogram from Annotation
    AnnotationMaps const &                          maps(Estimator::get_column_annotations());
    // Currently Annnotations are per output column index (0-based)
    // Since we've only one column as output- hardcoding this to 0 now.
    // Expect annotation design to be further rationalized in near future
    // which will address this hard-coding.
    AnnotationMap const &                           annotations(maps[0]);
    AnnotationMap::const_iterator const &           iterAnnotations(annotations.find("HistogramEstimator"));

    if(iterAnnotations == annotations.end())
        throw std::runtime_error("Couldn't retrieve HistogramEstimator.");

    // An output column can have multiple annotations from same 'kind' of estimator.
    // However, since we have only one estimator- hence the hard-coded value of 0 for retrieval.
    // Expect annotation design to be further rationalized in near future
    // which will address this hard-coding.

    Annotation const &                              annotation(*iterAnnotations->second[0]);

    HistogramAnnotation<InputT> const &       histogramAnnotation(static_cast<HistogramAnnotation<InputT> const &>(annotation));
    Histogram const &                         histogram(histogramAnnotation.Value);
    IndexMap const&                           index(create_index_map_from_histogram(histogram));

    BaseType::add_annotation(std::make_shared<IndexMapAnnotation<InputT, TransformedT>>(std::move(index)), ColIndexV);

    return Estimator::FitResult::Complete;
}


}
}
}
}
