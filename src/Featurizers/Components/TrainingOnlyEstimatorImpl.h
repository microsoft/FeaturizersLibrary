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
///                         static constexpr char const * const     NameValue;
///
///                     Methods
///                     -------
///                         [optional]
///                         bool begin_training(AnnotationMap const &annotations);
///
///                         void fit(InputType const &item);
///                             or
///                         void fit(InputType const *pItems, size_t cItems);
///
///                         <structure or value containing state data> complete_training(void);
///
template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
class TrainingOnlyEstimatorImpl :
    public FitEstimator<typename EstimatorPolicyT::InputType>,
    public EstimatorPolicyT
{
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(MaxNumTrainingItemsV != 0, "MaxNumTrainingItemsV must be > 0");
    static constexpr size_t const           MaxNumTrainingItems = MaxNumTrainingItemsV;

    using BaseType                          = FitEstimator<typename EstimatorPolicyT::InputType>;

    using InputType                         = typename EstimatorPolicyT::InputType;
    using AnnotationData                    = decltype(std::declval<EstimatorPolicyT>().complete_training());

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TrainingOnlyEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool requiresTraining=true);

    template <typename... ArgsT>
    TrainingOnlyEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool requiresTraining, ArgsT &&... estimator_policy_args);

    ~TrainingOnlyEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TrainingOnlyEstimatorImpl);

    using BaseType::begin_training;
    using BaseType::fit;
    using BaseType::on_data_completed;
    using BaseType::complete_training;

    size_t get_column_index(void) const;

    AnnotationData const & get_annotation_data(void) const;
    AnnotationData const * get_annotation_data_nothrow(void) const;

    static AnnotationData const & get_annotation_data(AnnotationMaps const &columnAnnotations, size_t colIndex, char const *name);
    static AnnotationData const * get_annotation_data_nothrow(AnnotationMaps const &columnAnnotations, size_t colIndex, char const *name);

    static AnnotationData const & get_annotation_data(Annotation const &annotation);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------

    /////////////////////////////////////////////////////////////////////////
    ///  \class         ScalarWrapper
    ///  \brief         Type used if AnnotationData is a scalar
    ///
    template <typename T>
    struct ScalarWrapper {
        // ----------------------------------------------------------------------
        // |  Public Data
        T                                   Value;

        // ----------------------------------------------------------------------
        // |  Public Methods
        ScalarWrapper(T value) :
            Value(std::move(value)) {
        }

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ScalarWrapper);
    };

    using AnnotationImplBase =
        typename std::conditional<
            std::is_class<AnnotationData>::value,
            AnnotationData,
            ScalarWrapper<AnnotationData>
        >::type;

    /////////////////////////////////////////////////////////////////////////
    ///  \class         AnnotationImpl
    ///  \brief         Wraps the desired data into a class that can be stored
    ///                 as a polymorphic Annotation.
    ///
    class AnnotationImpl :
        public Annotation,
        public AnnotationImplBase {
    public:
        // ----------------------------------------------------------------------
        // |  Public Methods
        template <typename... ArgsT>
        AnnotationImpl(ArgsT &&... args);
        ~AnnotationImpl(void) override = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(AnnotationImpl);
    };

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;
    bool const                              _requiresTraining;

    bool                                    _hasAnnotation;
    size_t                                  _cRemainingTrainingItems;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    static AnnotationData const * get_annotation_data_nothrow(AnnotationMaps const &columnAnnotations, size_t colIndex, char const *name, std::true_type);
    static AnnotationData const * get_annotation_data_nothrow(AnnotationMaps const &columnAnnotations, size_t colIndex, char const *name, std::false_type);

    bool begin_training_impl(void) override;
    bool begin_training_impl(std::true_type);
    bool begin_training_impl(std::false_type);

    FitResult fit_impl(typename BaseType::InputType const *pItems, size_t cItems) override;
    void fit_impl(typename BaseType::InputType const *pItems, size_t cItems, std::true_type);
    void fit_impl(typename BaseType::InputType const *pItems, size_t cItems, std::false_type);

    void complete_training_impl(void) override;
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
namespace Details {

template <typename, typename T>
class HasFitBufferMethodImpl {
    static_assert(std::integral_constant<T, false>::value, "Second template parameter must be a function type");
};

template <typename T, typename ReturnT, typename... ArgTs>
class HasFitBufferMethodImpl<T, ReturnT (ArgTs...)> {
private:
    template <typename U> static constexpr std::false_type Check(...);

    template <typename U>
    static constexpr std::true_type Check(
        U *,
        typename std::enable_if<
            std::is_same<
                decltype(std::declval<U>().fit(std::declval<ArgTs>()...)),
                ReturnT
            >::value,
            void *
        >::type
    );

public:
    static constexpr bool const             value = std::is_same<std::true_type, decltype(Check<T>(nullptr, nullptr))>::value;
};

template <typename InputT, typename T>
class HasFitBufferMethod : public HasFitBufferMethodImpl<T, void (InputT const *, size_t)> {};

// ----------------------------------------------------------------------
template <typename, typename T>
class HasBeginTrainingMethodImpl {
    static_assert(std::integral_constant<T, false>::value, "Second template parameter must be a function type");
};

template <typename T, typename ReturnT, typename... ArgTs>
class HasBeginTrainingMethodImpl<T, ReturnT (ArgTs...)> {
private:
    template <typename U> static constexpr std::false_type Check(...);

    template <typename U>
    static constexpr std::true_type Check(
        U *,
        typename std::enable_if<
            std::is_same<
                decltype(std::declval<U>().begin_training(std::declval<ArgTs>()...)),
                ReturnT
            >::value,
            void *
        >::type
    );

public:
    static constexpr bool const             value = std::is_same<std::true_type, decltype(Check<T>(nullptr, nullptr))>::value;
};

template <typename T>
class HasBeginTrainingMethod : public HasBeginTrainingMethodImpl<T, bool (AnnotationMap const &)> {};

} // namespace Details

// ----------------------------------------------------------------------
// |
// |  TrainingOnlyEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::TrainingOnlyEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool requiresTraining) :
    BaseType(EstimatorPolicyT::NameValue, std::move(pAllColumnAnnotations)),
    _colIndex(
        [this, &colIndex](void) -> size_t {
            if(colIndex >= this->get_column_annotations().size())
                throw std::invalid_argument("colIndex");

            return colIndex;
        }()
    ),
    _requiresTraining(requiresTraining),
    _hasAnnotation(false),
    _cRemainingTrainingItems(MaxNumTrainingItems) {
}

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
template <typename... ArgTs>
TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::TrainingOnlyEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool requiresTraining, ArgTs &&... estimator_policy_args) :
    BaseType(EstimatorPolicyT::NameValue, std::move(pAllColumnAnnotations)),
    EstimatorPolicyT(std::forward<ArgTs>(estimator_policy_args)...),
    _colIndex(
        [this, &colIndex](void) -> size_t {
            if(colIndex >= this->get_column_annotations().size())
                throw std::invalid_argument("colIndex");

            return colIndex;
        }()
    ),
    _requiresTraining(requiresTraining),
    _hasAnnotation(false),
    _cRemainingTrainingItems(MaxNumTrainingItemsV) {
}

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
size_t TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::get_column_index(void) const {
    return _colIndex;
}

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
typename TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::AnnotationData const & TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::get_annotation_data(void) const {
    return get_annotation_data(this->get_column_annotations(), _colIndex, this->Name);
}

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
typename TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::AnnotationData const * TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::get_annotation_data_nothrow(void) const {
    return get_annotation_data_nothrow(this->get_column_annotations(), _colIndex, this->Name);
}

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
/*static*/ typename TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::AnnotationData const & TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::get_annotation_data(AnnotationMaps const &columnAnnotations, size_t colIndex, char const *name) {
    AnnotationData const * const            ptr(get_annotation_data_nothrow(columnAnnotations, colIndex, name));

    if(ptr == nullptr)
        throw std::runtime_error("Annotation data was not found for this column");

    return *ptr;
}

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
/*static*/ typename TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::AnnotationData const * TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::get_annotation_data_nothrow(AnnotationMaps const &columnAnnotations, size_t colIndex, char const *name) {
    return get_annotation_data_nothrow(columnAnnotations, colIndex, name, std::integral_constant<bool, std::is_class<AnnotationData>::value>());
}

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
/*static*/ typename TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::AnnotationData const & TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::get_annotation_data(Annotation const &annotation) {
    assert(dynamic_cast<AnnotationImpl const *>(&annotation));
    return static_cast<AnnotationImpl const &>(annotation);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
/*static*/ typename TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::AnnotationData const * TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::get_annotation_data_nothrow(AnnotationMaps const &columnAnnotations, size_t colIndex, char const *name, std::true_type) {
    return BaseType::template get_annotation_impl<AnnotationImpl>(columnAnnotations, colIndex, name);
}

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
/*static*/ typename TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::AnnotationData const * TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::get_annotation_data_nothrow(AnnotationMaps const &columnAnnotations, size_t colIndex, char const *name, std::false_type) {
    AnnotationImpl const * const            pAnnotation(BaseType::template get_annotation_impl<AnnotationImpl>(columnAnnotations, colIndex, name));

    if(pAnnotation == nullptr)
        return nullptr;

    return &pAnnotation->Value;
}

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
bool TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    if(_requiresTraining == false)
        return false;

    // We don't want to calculate a new annotation if there is already an existing one
    _hasAnnotation = get_annotation_data_nothrow() != nullptr;
    if(_hasAnnotation)
        return false;

    return begin_training_impl(std::integral_constant<bool, Details::HasBeginTrainingMethod<EstimatorPolicyT>::value>());
}

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
bool TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::begin_training_impl(std::true_type) {
    AnnotationMaps const &                  allColumnAnnotations(BaseType::get_column_annotations());

    assert(_colIndex < allColumnAnnotations.size());
    return EstimatorPolicyT::begin_training(allColumnAnnotations[_colIndex]);
}

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
bool TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::begin_training_impl(std::false_type) {
    // Nothing to do here, allow training to continue
    return true;
}

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
FitResult TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::fit_impl(typename BaseType::InputType const *pItems, size_t cItems) /*override*/ {
    // This method returns false when there aren't any training items remaining, which
    // will put the estimator into a finished state. Fit shouldn't ever be called on an
    // estimator in a finished state.
    assert(_cRemainingTrainingItems);

    if(pItems) {
        size_t const                                    cItemsToProcess(std::min(_cRemainingTrainingItems, cItems));

        fit_impl(pItems, cItemsToProcess, std::integral_constant<bool, Details::HasFitBufferMethod<typename BaseType::InputType, EstimatorPolicyT>::value>());

        _cRemainingTrainingItems -= cItemsToProcess;
    }

    return _cRemainingTrainingItems != 0 ? FitResult::Continue : FitResult::Complete;
}

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
void TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::fit_impl(typename BaseType::InputType const *pItems, size_t cItems, std::true_type) {
    EstimatorPolicyT::fit(pItems, cItems);
}

// I don't know why MSVC thinks that this is unreachable code
#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4702) // Unreachable code
#endif

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
void TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::fit_impl(typename BaseType::InputType const *pItems, size_t cItems, std::false_type) {
    typename BaseType::InputType const * const          pEndItems(pItems + cItems);

    while(pItems != pEndItems)
        EstimatorPolicyT::fit(*pItems++);
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
void TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
    // Don't add a new annotation if one already exists
    if(_hasAnnotation == false)
        BaseType::add_annotation(std::make_shared<AnnotationImpl>(EstimatorPolicyT::complete_training()), _colIndex);
}

// ----------------------------------------------------------------------
// |
// |  TrainingOnlyEstimatorImpl::AnnotationImpl
// |
// ----------------------------------------------------------------------
template <typename EstimatorPolicyT, size_t MaxNumTrainingItemsV>
template <typename... ArgsT>
TrainingOnlyEstimatorImpl<EstimatorPolicyT, MaxNumTrainingItemsV>::AnnotationImpl::AnnotationImpl(ArgsT &&... args) :
    AnnotationImplBase(std::forward<ArgsT>(args)...) {
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
