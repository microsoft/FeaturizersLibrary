// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../../Featurizer.h"
#include "../../Traits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

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
    Histogram const                           Value;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    HistogramAnnotation(Histogram value);
    ~HistogramAnnotation(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(HistogramAnnotation);
};

/////////////////////////////////////////////////////////////////////////
///  \class         HistogramEstimator
///  \brief         This class computes the histogram for an input column
///                 and creates a HistogramAnnotation.
///
template <typename InputT, size_t ColIndexV>
class HistogramEstimator : public AnnotationEstimator<InputT const &> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    HistogramEstimator(AnnotationMapsPtr pAllColumnAnnotations);
    ~HistogramEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(HistogramEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using NonRefType                         = typename std::remove_cv<typename std::remove_reference<InputT>::type>::type;
    using BaseType                           = AnnotationEstimator<InputT const &>;
    using Histogram                          = std::map<NonRefType, std::uint32_t>;
    using TraitsT                            = Traits<NonRefType>;
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

namespace {
    template <typename T>
    T const& GetNullableValue(T const &value) {
        return value;
    }
    template <typename T>
    T const& GetNullableValue(nonstd::optional<T> const &value) {
        return Traits<typename std::remove_cv<typename std::remove_reference<nonstd::optional<T>>::type>::type>::GetNullableValue(value);
    }
    template <typename T>
    T const& GetNullableValue(std::float_t const &value) {
        return Traits<typename std::remove_cv<typename std::remove_reference<nonstd::optional<T>>::type>::type>::GetNullableValue(value);
    }
    template <typename T>
    T const& GetNullableValue(std::double_t const &value) {
        return Traits<typename std::remove_cv<typename std::remove_reference<nonstd::optional<T>>::type>::type>::GetNullableValue(value);
    }
} // anonymous namespace


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
// |  HistogramAnnotation
// |
// ----------------------------------------------------------------------
template <typename T>
HistogramAnnotation<T>::HistogramAnnotation(Histogram value) :
    Annotation(this),
    Value(std::move(value)) {
}

// ----------------------------------------------------------------------
// |
// |  HistogramEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t ColIndexV>
HistogramEstimator<InputT,ColIndexV>::HistogramEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    AnnotationEstimator<InputT const &>("HistogramEstimator", std::move(pAllColumnAnnotations)){
}


template <typename InputT, size_t ColIndexV>
Estimator::FitResult HistogramEstimator<InputT,ColIndexV>::fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) {
    typename BaseType::FitBufferInputType const * const                 pEndBuffer(pBuffer + cBuffer);
    while(pBuffer != pEndBuffer) {
        InputT const &                                   input(*pBuffer++);
        if(TraitsT::IsNull(input))
            continue;

        typename Histogram::iterator const           iter(
            // TODO: Base HistogramEstimator on TrainingOnlyEstimatorImpl.h later
            //       to limit the number of training items if necessary
            [this, &input](void) -> typename Histogram::iterator {
                NonRefType const& value = GetNullableValue(input);
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

template <typename InputT, size_t ColIndexV>
Estimator::FitResult HistogramEstimator<InputT,ColIndexV>::complete_training_impl(void) {

    BaseType::add_annotation(std::make_shared<HistogramAnnotation<InputT>>(std::move(_histogram)), ColIndexV);

    return Estimator::FitResult::Complete;
}
}
}
}
}
