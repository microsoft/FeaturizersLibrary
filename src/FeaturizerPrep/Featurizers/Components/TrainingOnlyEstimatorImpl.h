// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../../Featurizer.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

/////////////////////////////////////////////////////////////////////////
///  \class         TrainingOnlyEstimatorImpl
///  \brief         Base class that simplifies the process of collecting
///                 metric data during training, invoking functionality
///                 in the provided EstimatorPolicy.
///
///                 The EstimatorPolicy must define the following items:
///
///                     Types
///                     -----
///                         InputType:                  Input to the Estimator
///
///                     Data
///                     ----
///                         static std::string const            EstimatorName;
///                         static size_t const                 MaxNumTrainingItems;
///
///                     Methods
///                     -------
///                         void fit_items(FitBufferItemType *pBuffer, size_t cItemsToProcess);
///                         void fit_nulls(std::uint64_t const &numTrailingNulls);
///                         <structure containing state data> complete_training(void);
///
template <typename EstimatorPolicyT, size_t ColIndexV>
class TrainingOnlyEstimatorImpl :
    public AnnotationEstimator<typename EstimatorPolicyT::InputType>,
    private EstimatorPolicyT
{
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using ThisType                          = TrainingOnlyEstimatorImpl<EstimatorPolicyT, ColIndexV>;
    using BaseType                          = AnnotationEstimator<typename EstimatorPolicyT::InputType>;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wold-style-cast"
#endif

    // clang doesn't like the use of reinterpret_cast here
    using AnnotationData                    = decltype(((EstimatorPolicyT *)(nullptr))->complete_training());

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TrainingOnlyEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations);
    ~TrainingOnlyEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TrainingOnlyEstimatorImpl);

    using BaseType::fit;
    using BaseType::complete_training;

    AnnotationData const & get_annotation_data(void) const;
    AnnotationData const * get_annotation_data_nothrow(void) const;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    class AnnotationImpl :
        public Annotation,
        public AnnotationData {
    public:
        // ----------------------------------------------------------------------
        // |  Public Methods
        template <typename... ArgsT>
        AnnotationImpl(EstimatorUniqueId id, ArgsT &&... args);

        ~AnnotationImpl(void) override = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(AnnotationImpl);
    };

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t                                  _cRemainingTrainingItems;

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
// |  TrainingOnlyEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename EstimatorPolicyT, size_t ColIndexV>
TrainingOnlyEstimatorImpl<EstimatorPolicyT, ColIndexV>::TrainingOnlyEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType(EstimatorPolicyT::EstimatorName, std::move(pAllColumnAnnotations)),
    _cRemainingTrainingItems(
        [](void) -> size_t {
            size_t                      cMaxNumTrainingItems(EstimatorPolicyT::MaxNumTrainingItems);

            if(cMaxNumTrainingItems == 0)
                throw std::invalid_argument("cMaxNumTrainingItems");

            return cMaxNumTrainingItems;
        }()
    ) {
}

template <typename EstimatorPolicyT, size_t ColIndexV>
typename TrainingOnlyEstimatorImpl<EstimatorPolicyT, ColIndexV>::AnnotationData const & TrainingOnlyEstimatorImpl<EstimatorPolicyT, ColIndexV>::get_annotation_data(void) const {
    AnnotationData const * const            ptr(get_annotation_data_nothrow());

    if(ptr == nullptr)
        throw std::runtime_error("Annotation data was not found for this column");

    return *ptr;
}

template <typename EstimatorPolicyT, size_t ColIndexV>
typename TrainingOnlyEstimatorImpl<EstimatorPolicyT, ColIndexV>::AnnotationData const * TrainingOnlyEstimatorImpl<EstimatorPolicyT, ColIndexV>::get_annotation_data_nothrow(void) const {
    return BaseType::template get_annotation_impl<AnnotationImpl>(ColIndexV);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename EstimatorPolicyT, size_t ColIndexV>
Estimator::FitResult TrainingOnlyEstimatorImpl<EstimatorPolicyT, ColIndexV>::fit_impl(typename BaseType::FitBufferInputType const *pBuffer, size_t cBuffer) /*override*/ {
    if(cBuffer) {
        size_t const                        cItemsToProcess(std::min(_cRemainingTrainingItems, cBuffer));

        EstimatorPolicyT::fit_items(pBuffer, cItemsToProcess);
        _cRemainingTrainingItems -= cItemsToProcess;
    }

    return _cRemainingTrainingItems ? Estimator::FitResult::Continue : Estimator::FitResult::Complete;
}

template <typename EstimatorPolicyT, size_t ColIndexV>
Estimator::FitResult TrainingOnlyEstimatorImpl<EstimatorPolicyT, ColIndexV>::complete_training_impl(void) /*override*/ {
    BaseType::add_annotation(std::make_shared<AnnotationImpl>(this, EstimatorPolicyT::complete_training()), ColIndexV);
    return Estimator::FitResult::Complete;
}

// ----------------------------------------------------------------------
// |
// |  TrainingOnlyEstimatorImpl::AnnotationImpl
// |
// ----------------------------------------------------------------------
template <typename EstimatorPolicyT, size_t ColIndexV>
template <typename... ArgsT>
TrainingOnlyEstimatorImpl<EstimatorPolicyT, ColIndexV>::AnnotationImpl::AnnotationImpl(EstimatorUniqueId id, ArgsT &&... args) :
    Annotation(id),
    AnnotationData(std::forward<ArgsT>(args)...) {
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
