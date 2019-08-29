// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "../Featurizer.h"
#include "../PipelineExecutionEstimator.h"
#include "../Traits.h"

namespace Microsoft {
namespace Featurizer {

/////////////////////////////////////////////////////////////////////////
///  \class         HistogramAnnotation
///  \brief         This is an annotation class which holds all the values and corresponding
///                 frequencies for an input column.
///
template <typename T>
class HistogramAnnotation : public Annotation {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using Histogram                          = std::map<T, std::uint32_t>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    Histogram                                Value;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    HistogramAnnotation(Histogram value) :
        Annotation(this),
        Value(std::move(value)) {
    }

    ~HistogramAnnotation(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(HistogramAnnotation);
};

/////////////////////////////////////////////////////////////////////////
///  \class         HistogramEstimator
///  \brief         This class computes the histogram for an input column
///                 and creates a HistogramAnnotation.
///
template <typename InputT,typename TransformedT, size_t ColIndexV>
class HistogramEstimator : public AnnotationEstimator<InputT const &> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    HistogramEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
        AnnotationEstimator<InputT const &>("HistogramEstimator", std::move(pAllColumnAnnotations)){
    }

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(HistogramEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                           = AnnotationEstimator<InputT const &>;
    using Histogram                          = std::map<TransformedT, std::uint32_t>;

    using TraitsT                              = Traits<typename std::remove_cv<typename std::remove_reference<InputT>::type>::type>;
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    Histogram                                _histogram;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    Estimator::FitResult fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) override;

    Estimator::FitResult complete_training_impl(void) override;
};

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
        Transformer(TransformedT mostFreq) : _mostFreq(std::move(mostFreq)) {}
        Transformer(typename BaseType::Transformer::Archive & ar);

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
    HistogramConsumerEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
        BaseType("HistogramConsumerEstimator", std::move(pAllColumnAnnotations), true) {
    }

    ~HistogramConsumerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(HistogramConsumerEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using Histogram                          = std::map<TransformedT, std::uint32_t>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    Estimator::FitResult fit_impl(typename BaseType::BaseType::FitBufferInputType *pBuffer, size_t cBuffer) override;
    Estimator::FitResult complete_training_impl(void) override;
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override;
};

/////////////////////////////////////////////////////////////////////////
///  \class         CatImputerEstimator
///  \brief         This class 'chains' HistogramEstimator and HistogramConsumerEstimator.
///                 HistogramEstimator generates HistogramAnnotation which is consumed by
///                 HistogramConsumerEstimator to compute most frequent value.
///
template <typename T>
class CatImputerEstimator :
    public PipelineExecutionEstimator<
        HistogramEstimator<typename Traits<T>::nullable_type, T, 0>,
        HistogramConsumerEstimator<typename Traits<T>::nullable_type, T>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = PipelineExecutionEstimator<
        HistogramEstimator<typename Traits<T>::nullable_type, T, 0>,
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
// |  HistogramEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT,typename TransformedT, size_t ColIndexV>
Estimator::FitResult HistogramEstimator<InputT,TransformedT,ColIndexV>::fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) {

    typename BaseType::FitBufferInputType const * const                 pEndBuffer(pBuffer + cBuffer);

    while(pBuffer != pEndBuffer) {
        InputT const &                                   input(*pBuffer++);
        if(TraitsT::IsNull(input))
            continue;

        typename Histogram::iterator const           iter(
            [this, &input](void) -> typename Histogram::iterator {
                auto value = TraitsT::GetValue(input);
                typename Histogram::iterator const   i(_histogram.find(value));

                if(i != _histogram.end())
                    return i;

                std::pair<typename Histogram::iterator, bool> const      result(_histogram.insert(std::make_pair(value, 0)));

                return result.first;
            }()
        );

        iter->second += 1;
    }

    return Estimator::FitResult::Continue;
}

template <typename InputT,typename TransformedT, size_t ColIndexV>
Estimator::FitResult HistogramEstimator<InputT,TransformedT,ColIndexV>::complete_training_impl(void) {

    BaseType::add_annotation(std::make_shared<HistogramAnnotation<TransformedT>>(std::move(_histogram)), ColIndexV);

    return Estimator::FitResult::Complete;
}

// ----------------------------------------------------------------------
// |
// |  HistogramConsumerEstimator
// |
// ----------------------------------------------------------------------

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

    return TraitsT::GetValue(input);
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

template <typename InputT,typename TransformedT>
Estimator::FitResult HistogramConsumerEstimator<InputT,TransformedT>::fit_impl(typename BaseType::BaseType::FitBufferInputType *, size_t ) {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

template <typename InputT,typename TransformedT>
Estimator::FitResult HistogramConsumerEstimator<InputT,TransformedT>::complete_training_impl(void) {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

template <typename InputT,typename TransformedT>
typename HistogramConsumerEstimator<InputT,TransformedT>::BaseType::TransformerUniquePtr HistogramConsumerEstimator<InputT,TransformedT>::create_transformer_impl(void)  {

    // Retrieve Histogram from Annotation
    AnnotationMaps const &                        maps(Estimator::get_column_annotations());
    // Currently Annnotations are per output column index (0-based)
    // Since we've only one column as output- hardcoding this to 0 now.
    // Expect annotation design to be further rationalized in near future
    // which will address this hard-coding.
    AnnotationMap const &                        annotations(maps[0]);
    AnnotationMap::const_iterator const &       iterAnnotations(annotations.find("HistogramEstimator"));

    if(iterAnnotations == annotations.end())
        throw std::runtime_error("Couldn't retrieve HistogramAnnotation.");

    // An output column can have multiple annotations from same 'kind' of estimator.
    // However, since we have only one estimator- hence the hard-coded value of 0 for retrieval.
    // Expect annotation design to be further rationalized in near future
    // which will address this hard-coding.
    Annotation const &                          annotation(*iterAnnotations->second[0]);
    assert(dynamic_cast<HistogramAnnotation<TransformedT> const *>(&annotation));
    HistogramAnnotation<TransformedT> const &   histogramAnnotation(static_cast<HistogramAnnotation<TransformedT> const &>(annotation));
    Histogram const &                            histogram(histogramAnnotation.Value);

    // Compute most frequent value from Histogram
    typename Histogram::const_iterator          iMostCommon(histogram.end());

    for(typename Histogram::const_iterator iter=histogram.begin(); iter != histogram.end(); ++iter) {
        if(iMostCommon == histogram.end() || iter->second > iMostCommon->second) {
            iMostCommon = iter;
        }
    }
    if(iMostCommon == histogram.end())
        throw std::runtime_error("All null values or empty training set.");

    return std::make_unique<Transformer>(iMostCommon->first);
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

} // namespace Featurizer
} // namespace Microsoft
