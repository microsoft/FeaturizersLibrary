// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>

#include "TrainingOnlyEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         NormEstimatorName("NormEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         NormAnnotationData
///  \brief         store all three kinds of norms: l1, l2 and max norm
///
template <typename T>
class NormAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
   long double const                           L1_norm;
   long double const                           L2_norm;
   long double const                           Max_norm;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    NormAnnotationData(long double l1_norm, long double l2_norm, long double max_norm);
    ~NormAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(NormAnnotationData);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         NormTrainingOnlyPolicy
///  \brief         Calculate all three norms
///                 l1 norm is the sum of distance away from average, |x[i] - average| for i from 0 to n-1
///                 l2 norm is the sum of square of distance away from average, |x[i] - average|^2 for i from 0 to n-1
///                 max norm is the maximum of absolute value of x[i] for i from 0 to n-1
///
template <typename T>
class NormTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = T;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = NormEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    NormTrainingOnlyPolicy(void);

    void fit(InputType const &input);
    NormAnnotationData<T> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Method
    // |
    // ----------------------------------------------------------------------
    void retrieve_annotation();
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    long double                                             _l1_norm;
    long double                                             _l2_norm;
    InputType                                               _min;
    InputType                                               _max;
    std::double_t                                           _average;
    long double                                             _count;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \typedef       NormEstimator
///  \brief         A training-only class that finds the min, max
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using NormEstimator                       = TrainingOnlyEstimatorImpl<Details::NormTrainingOnlyPolicy<InputT>, MaxNumTrainingItemsV>;

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
// |  NormAnnotationData
// |
// ----------------------------------------------------------------------
template <typename T>
NormAnnotationData<T>::NormAnnotationData(long double l1_norm, long double l2_norm, long double max_norm) :
    L1_norm(std::move(l1_norm)),
    L2_norm(std::move(l2_norm)),
    Max_norm(std::move(max_norm)) {
}

// ----------------------------------------------------------------------
// |
// |  Details::NormTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::NormTrainingOnlyPolicy<T>::NormTrainingOnlyPolicy(void) :
    _l1_norm(0),
    _l2_norm(0),
    _count(static_cast<long double>(count)) {
}

template <typename T>
void Details::NormTrainingOnlyPolicy<T>::retrieve_annotation() {
    // ----------------------------------------------------------------------
    using StatisticalMetricsAnnotationData           = StatisticalMetricsAnnotationData<T>;
    using StatisticalMetricsEstimator                = StatisticalMetricsEstimator<T, MaxNumTrainingItemsV>;
    // ----------------------------------------------------------------------

    StatisticalMetricsAnnotationData const &         data(StatisticalMetricsEstimator::get_annotation_data(estimator.get_column_annotations(), estimator.get_column_index(), StatisticalMetricsEstimatorName));


}

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

void update_norms(long double input, long double& l1_norm, long double& l2_norm, long double const& average) {
    // update l1_norm and l2_norm based on input and average
    // std::isinf is used to check long double bounds
    long double diff = std::abs(input - average);


    if ((l1_norm + diff == l1_norm) && (diff != 0)) {
        throw std::runtime_error("In l1 norm calculation, difference between input and average is so small comparing to l1_norm that l1_norm is the same after long double addition!");
    }
    l1_norm += diff;

    // check if l1_norm will be out of bound
    if (std::isinf(l1_norm)) {
        throw std::runtime_error("Overflows occured during calculating l1_norm! Check your data!");
    }

    long double diff_square = std::pow(diff, 2);

    if ((l2_norm + diff_square == l2_norm) && (diff_square != 0)) {
        throw std::runtime_error("In l2 norm calculation, square of difference between input and average is so small comparing to l2_norm that l2_norm is the same after long double addition!");
    }
    l2_norm += diff_square;

    // check if exceeds bound
    if (std::isinf(l2_norm)) {
        throw std::runtime_error("Overflows occured during calculating l2_norm! Check your data!");
    }
}
template <typename T>
void Details::NormTrainingOnlyPolicy<T>::fit(InputType const &input) {
    if (_annotation_retrieve_flag) {
        retrieve_annotation();
        _annotation_retrieve_flag = false;
    }

    if (_count == 0) {
        return;
    }
    if(Microsoft::Featurizer::Traits<T>::IsNull(input))
        return;
    update_norms(static_cast<long double>(input), _l1_norm, _l2_norm, static_cast<long double>(_average));

    return;
}

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
template <typename T>
NormAnnotationData<T> Details::NormTrainingOnlyPolicy<T>::complete_training(void) {
    return NormAnnotationData<T>(std::move(_min), std::move(_max));
}


/**
 * // ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../../Featurizer.h"
#include "../../Traits.h"
#include "StatisticalMetricsEstimator.h"
#include <cmath>
namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {
/////////////////////////////////////////////////////////////////////////
///  \class         NormAnnotation
///  \brief         store all three kinds of norms: l1, l2 and max norm
///
///
template <typename T>
class NormAnnotation : public Annotation {
public:
   // ----------------------------------------------------------------------
   // |
   // |  Public Data
   // |
   // ----------------------------------------------------------------------
   long double const                           L1_norm;
   long double const                           L2_norm;
   long double const                           Max_norm;
   // ----------------------------------------------------------------------
   // |
   // |  Public Methods
   // |
   // ----------------------------------------------------------------------
   NormAnnotation(long double l1_norm, long double l2_norm, long double max_norm);
   ~NormAnnotation(void) override = default;
   FEATURIZER_MOVE_CONSTRUCTOR_ONLY(NormAnnotation);
};
/////////////////////////////////////////////////////////////////////////
///  \class         NormEstimator
///  \brief         Calculate all three norms
///                 l1 norm is the sum of distance away from average, |x[i] - average| for i from 0 to n-1
///                 l2 norm is the sum of square of distance away from average, |x[i] - average|^2 for i from 0 to n-1
///                 max norm is the maximum of absolute value of x[i] for i from 0 to n-1
///
template <typename InputT, size_t ColIndexV>
class NormEstimator : public AnnotationEstimator<InputT const &> {
public:
   // ----------------------------------------------------------------------
   // |
   // |  Public Methods
   // |
   // ----------------------------------------------------------------------
   NormEstimator(AnnotationMapsPtr pAllColumnAnnotations);
   ~NormEstimator(void) override = default;

   FEATURIZER_MOVE_CONSTRUCTOR_ONLY(NormEstimator);
   // comment out testing flag for now
   // TODO: add AUTOMATED_TESTING in cmake files
// #ifdef AUTOMATED_TESTING
//    NormEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::double_t average, std::int64_t count);
// #else
// private:
   NormEstimator(AnnotationMapsPtr pAllColumnAnnotations, InputT min, InputT max, std::double_t average, std::int64_t count);
// #endif

   // ----------------------------------------------------------------------
   // |
   // |  Private Types
   // |
   // ----------------------------------------------------------------------
   using BaseType                             = AnnotationEstimator<InputT const &>;
   using TraitsT                              = Traits<InputT>;

   // ----------------------------------------------------------------------
   // |
   // |  Private Data
   // |
   // ----------------------------------------------------------------------
   long double                                             _l1_norm;
   long double                                             _l2_norm;
   InputT                                                  _min;
   InputT                                                  _max;
   std::double_t                                           _average;
   long double                                             _count;
   bool                                                    _annotation_retrieve_flag;
   // ----------------------------------------------------------------------
   // |
   // |  Private Methods
   // |
   // ----------------------------------------------------------------------
   Estimator::FitResult fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) override;

   Estimator::FitResult complete_training_impl(void) override;

   void retrieve_annotation();
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
// |  NormAnnotation
// |
// ----------------------------------------------------------------------
template <typename T>
NormAnnotation<T>::NormAnnotation(long double l1_norm, long double l2_norm, long double max_norm) :
    Annotation(this),
    L1_norm(std::move(l1_norm)),
    L2_norm(std::move(l2_norm)),
    Max_norm(std::move(max_norm)) {
}

// ----------------------------------------------------------------------
// |
// |  NormEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t ColIndexV>
NormEstimator<InputT,ColIndexV>::NormEstimator(AnnotationMapsPtr pAllColumnAnnotations, InputT min, InputT max, std::double_t average, std::int64_t count) :
    AnnotationEstimator<InputT const &>("NormEstimator", std::move(pAllColumnAnnotations)),
    _l1_norm(0),
    _l2_norm(0),
    _min(min),
    _max(max),
    _average(average),
    _count(static_cast<long double>(count)),
    _annotation_retrieve_flag(false)
    {
}
template <typename InputT, size_t ColIndexV>
NormEstimator<InputT,ColIndexV>::NormEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
    AnnotationEstimator<InputT const &>("NormEstimator", std::move(pAllColumnAnnotations)),
    _l1_norm(0),
    _l2_norm(0),
    _annotation_retrieve_flag(true) {
}

template <typename InputT, size_t ColIndexV>
void NormEstimator<InputT,ColIndexV>::retrieve_annotation() {
    // Retrieve count and average from Annotation
    AnnotationMaps const &                          maps(Estimator::get_column_annotations());
    // Currently Annnotations are per output column index (0-based)
    // Since we've only one column as output- hardcoding this to 0 now.
    // Expect annotation design to be further rationalized in near future
    // which will address this hard-coding.
    AnnotationMap const &                           annotations(maps[0]);
    AnnotationMap::const_iterator const &           iterAnnotations(annotations.find("StatisticalMetricsEstimator"));

    if(iterAnnotations == annotations.end())
        throw std::runtime_error("Couldn't retrieve StatisticalMetricsEstimator.");

    // An output column can have multiple annotations from same 'kind' of estimator.
    // However, since we have only one estimator- hence the hard-coded value of 0 for retrieval.
    // Expect annotation design to be further rationalized in near future
    // which will address this hard-coding.

    Annotation const &                              annotation(*iterAnnotations->second[0]);

    StatisticalMetricsAnnotation<InputT> const &       statisticalMetricsAnnotation(static_cast<StatisticalMetricsAnnotation<InputT> const &>(annotation));
    _min = statisticalMetricsAnnotation.Min;
    _max = statisticalMetricsAnnotation.Max;
    _average = statisticalMetricsAnnotation.Average;
    _count = static_cast<long double>(statisticalMetricsAnnotation.Count);
}

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

void update_norms(long double input, long double& l1_norm, long double& l2_norm, long double const& average) {
    // update l1_norm and l2_norm based on input and average
    // std::isinf is used to check long double bounds
    long double diff = std::abs(input - average);


    if ((l1_norm + diff == l1_norm) && (diff != 0)) {
        throw std::runtime_error("In l1 norm calculation, difference between input and average is so small comparing to l1_norm that l1_norm is the same after long double addition!");
    }
    l1_norm += diff;

    // check if l1_norm will be out of bound
    if (std::isinf(l1_norm)) {
        throw std::runtime_error("Overflows occured during calculating l1_norm! Check your data!");
    }

    long double diff_square = std::pow(diff, 2);

    if ((l2_norm + diff_square == l2_norm) && (diff_square != 0)) {
        throw std::runtime_error("In l2 norm calculation, square of difference between input and average is so small comparing to l2_norm that l2_norm is the same after long double addition!");
    }
    l2_norm += diff_square;

    // check if exceeds bound
    if (std::isinf(l2_norm)) {
        throw std::runtime_error("Overflows occured during calculating l2_norm! Check your data!");
    }
}

template <typename InputT, size_t ColIndexV>
Estimator::FitResult NormEstimator<InputT,ColIndexV>::fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) {
    if (_annotation_retrieve_flag) {
        retrieve_annotation();
        _annotation_retrieve_flag = false;
    }

    if (_count == 0) {
        return Estimator::FitResult::Complete;
    }
    typename BaseType::FitBufferInputType const * const                 pEndBuffer(pBuffer + cBuffer);
    while(pBuffer != pEndBuffer) {
        InputT const &                                   input(*pBuffer++);
        if(TraitsT::IsNull(input))
            continue;
        update_norms(static_cast<long double>(input), _l1_norm, _l2_norm, static_cast<long double>(_average));
    }
    return Estimator::FitResult::Continue;
}

template <typename InputT, size_t ColIndexV>
Estimator::FitResult NormEstimator<InputT,ColIndexV>::complete_training_impl(void) {
    BaseType::add_annotation(std::make_shared<NormAnnotation<InputT>>(_l1_norm,_l2_norm, std::max(std::abs(_min), std::abs(_max))), ColIndexV);

    return Estimator::FitResult::Complete;
}
#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
}
}
}
}

**/



} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
