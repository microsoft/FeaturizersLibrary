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

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {



/////////////////////////////////////////////////////////////////////////
///  \class         HistogramConsumerEstimator
///  \brief         This class retrieves a HistogramAnnotation and computes
///                 the most frequent value from it. This value is used to
///                    replace null values.
///
template <typename InputT,typename TransformedT>
class HistogramConsumerEstimator : public TransformerEstimator<InputT const &, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                           = TransformerEstimator<InputT const &, TransformedT>;
    using TraitsT                              = Traits<typename std::remove_cv<typename std::remove_reference<InputT>::type>::type>;

    class Transformer : public BaseType::Transformer {
    public:
        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        Transformer(TransformedT mostFreq);
        Transformer(typename BaseType::Transformer::Archive & ar);
        ~Transformer(void) override = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Transformer);

        typename BaseType::TransformedType execute(typename BaseType::InputType input) override;

        void save(typename BaseType::Transformer::Archive & ar) const override;

        TransformedT const & get_most_frequent_value() const;

    private:
        // ----------------------------------------------------------------------
        // |
        // |  Private Data
        // |
        // ----------------------------------------------------------------------
        TransformedT                              _mostFreq;
    };

    using TransformerType                   = Transformer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    HistogramConsumerEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~HistogramConsumerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(HistogramConsumerEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using Histogram                          = std::map<InputT, std::uint32_t>;

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

    // MSVC has problems when the function is defined outside of the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        // Retrieve Histogram from Annotation
        AnnotationMaps const &                          maps(Estimator::get_column_annotations());
        // Currently Annnotations are per output column index (0-based)
        // Since we've only one column as output- hardcoding this to 0 now.
        // Expect annotation design to be further rationalized in near future
        // which will address this hard-coding.
        AnnotationMap const &                           annotations(maps[0]);
        AnnotationMap::const_iterator const &           iterAnnotations(annotations.find("HistogramEstimator"));

        if(iterAnnotations == annotations.end())
            throw std::runtime_error("Couldn't retrieve HistogramAnnotation.");

        // An output column can have multiple annotations from same 'kind' of estimator.
        // However, since we have only one estimator- hence the hard-coded value of 0 for retrieval.
        // Expect annotation design to be further rationalized in near future
        // which will address this hard-coding.
        Annotation const &                              annotation(*iterAnnotations->second[0]);

        assert(dynamic_cast<Components::HistogramAnnotation<InputT> const *>(&annotation));

        Components::HistogramAnnotation<InputT> const &       histogramAnnotation(static_cast<Components::HistogramAnnotation<InputT> const &>(annotation));
        Histogram const &                               histogram(histogramAnnotation.Value);

        // Compute most frequent value from Histogram
        typename Histogram::const_iterator              iMostCommon(histogram.end());

        for(typename Histogram::const_iterator iter=histogram.begin(); iter != histogram.end(); ++iter) {
            if(iMostCommon == histogram.end() || iter->second > iMostCommon->second) {
                iMostCommon = iter;
            }
        }
        if(iMostCommon == histogram.end())
            throw std::runtime_error("All null values or empty training set.");

        return std::make_unique<Transformer>(Traits<InputT>::GetNullableValue(iMostCommon->first));
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         CatImputerEstimator
///  \brief         This class 'chains' HistogramEstimator and HistogramConsumerEstimator.
///                 HistogramEstimator generates HistogramAnnotation which is consumed by
///                 HistogramConsumerEstimator to compute most frequent value.
///
template <typename T>
class CatImputerEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::HistogramEstimator<typename Traits<T>::nullable_type, 0>,
        HistogramConsumerEstimator<typename Traits<T>::nullable_type, T>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::PipelineExecutionEstimatorImpl<
        Components::HistogramEstimator<typename Traits<T>::nullable_type, 0>,
        HistogramConsumerEstimator<typename Traits<T>::nullable_type, T>
    >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CatImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations);

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
// |  HistogramConsumerEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT,typename TransformedT>
HistogramConsumerEstimator<InputT,TransformedT>::HistogramConsumerEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("HistogramConsumerEstimator", std::move(pAllColumnAnnotations), true) {
}

template <typename InputT,typename TransformedT>
Estimator::FitResult HistogramConsumerEstimator<InputT,TransformedT>::complete_training_impl(void) {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

// ----------------------------------------------------------------------
// |
// |  HistogramConsumerEstimator::Transformer
// |
// ----------------------------------------------------------------------
template <typename InputT,typename TransformedT>
HistogramConsumerEstimator<InputT,TransformedT>::Transformer::Transformer(TransformedT mostFreq) :
    _mostFreq(std::move(mostFreq)) {
}

template <typename InputT,typename TransformedT>
HistogramConsumerEstimator<InputT,TransformedT>::Transformer::Transformer(typename BaseType::Transformer::Archive & ar) {
    if(Traits<std::uint8_t>::deserialize(ar) != 1)
        throw std::runtime_error("Invalid transformer version");

    _mostFreq = Traits<TransformedT>::deserialize(ar);
}

template <typename InputT,typename TransformedT>
typename HistogramConsumerEstimator<InputT,TransformedT>::BaseType::TransformedType HistogramConsumerEstimator<InputT,TransformedT>::Transformer::execute(typename BaseType::InputType input) {

    if(TraitsT::IsNull(input))
        return _mostFreq;

    return TraitsT::GetNullableValue(input);
}

template <typename InputT,typename TransformedT>
void HistogramConsumerEstimator<InputT,TransformedT>::Transformer::save(typename HistogramConsumerEstimator<InputT,TransformedT>::BaseType::Transformer::Archive & ar) const {
    Traits<std::uint8_t>::serialize(ar, 1); // Current version
    Traits<TransformedT>::serialize(ar,_mostFreq);
}

template <typename InputT,typename TransformedT>
TransformedT const & HistogramConsumerEstimator<InputT,TransformedT>::Transformer::get_most_frequent_value() const {
    return _mostFreq;
}

// ----------------------------------------------------------------------
// |
// |  CatImputerEstimator
// |
// ----------------------------------------------------------------------
template <typename T>
CatImputerEstimator<T>::CatImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType("CatImputerEstimator", std::move(pAllColumnAnnotations)) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
