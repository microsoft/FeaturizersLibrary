// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../InferenceOnlyFeaturizerImpl.h"

#include <algorithm>

namespace Microsoft {
namespace Featurizer {
namespace Details {

// IMPLEMENTATION NOTE
// Throughout this code, PipelineT represents a compile-time list of Estimators.
// In practice, PipelineT represents a std::tuple used as a compile-time container
// to hold these values. The choice of std::tuple rather than parameter packs was
// due to the requirement that these pipelines must sometimes be modified at compile
// time to account for an additional estimator that must be added to the end of the
// pipeline in some scenarios (see NormalizePipeline for more info).

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainSuffixTransformer
///  \brief         `Transformer` that converts from a const reference object
///                 to a non-reference type. This will be used by pipeline
///                 that end with `AnnotationEstimators` (who, by default,
///                 only operator on reference types).
///
template <typename InputT>
class EstimatorChainSuffixTransformer : public InferenceOnlyTransformerImpl<InputT, std::remove_cv_t<std::remove_reference_t<InputT>>> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType                          = InferenceOnlyTransformerImpl<InputT, std::remove_cv_t<std::remove_reference_t<InputT>>>;

    // ----------------------------------------------------------------------
    // |  Public Methods
    EstimatorChainSuffixTransformer(void) = default;
    EstimatorChainSuffixTransformer(Archive &) {}

    ~EstimatorChainSuffixTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(EstimatorChainSuffixTransformer);

    typename BaseType::TransformedType execute(typename BaseType::InputType value) override {
        // This code is removing the const-ness of the object and then moving the value to
        // another location. Generally speaking, this is a really bad idea. However,
        // it happens to work in this specific sceanrio because:
        //
        //      - This object is only used with the PipelineExecutionEstimator
        //      - There must be at least one TransformerEstimator in the PipelineExecutionEstimator chain
        //        (this is verified at compile time by PipelineTraits)
        //      - A TransformerEstimator creates a new output item on execute
        //      - This transformer is only applied to chains that would otherwise end with AnnotationEstimators
        //
        // This logic means that at least one temporary will have been created during the
        // transformation process, and the last temporary will be the item passed here as value
        // and serve as the source of the move.
        return std::move(const_cast<typename BaseType::TransformedType &>(value));
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainSuffixEstimator
///  \brief         Estimator for use with the `EstimatorChainSuffixTransformer`.
///
template <typename InputT>
class EstimatorChainSuffixEstimator : public InferenceOnlyEstimatorImpl<EstimatorChainSuffixTransformer<InputT>> {
public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using BaseType                          = InferenceOnlyEstimatorImpl<EstimatorChainSuffixTransformer<InputT>>;

    // ----------------------------------------------------------------------
    // |  Public Methods
    EstimatorChainSuffixEstimator(AnnotationMapsPtr pAllColumnAnnotations) :
        BaseType("EstimatorChainSuffixEstimator", std::move(pAllColumnAnnotations)) {
    }

    ~EstimatorChainSuffixEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(EstimatorChainSuffixEstimator);
};

namespace {

/////////////////////////////////////////////////////////////////////////
///  \class         IsTransformerEstimator
///  \brief         Contains a constexpr value that is true if T is a
///                 `TransformerEstimator`.
///
template <typename T>
class IsTransformerEstimator {
private:
    // ----------------------------------------------------------------------
    // |  Private Methods
    template <typename U> static std::true_type check(typename U::TransformedType const *);
    template <typename U> static std::false_type check(...);

public:
    // ----------------------------------------------------------------------
    // |  Public Types
    static constexpr bool const             value = std::is_same<std::true_type, decltype(check<T>(nullptr))>::value;
};

/////////////////////////////////////////////////////////////////////////
///  \class         HasTransformerType
///  \brief         Contains a constexpr value that is true if T has a
///                 nested `Transformer` type. Note that not all
///                 `TransformerEstimators` need this type to be defined,
///                 but this is a requirement for those `Estimators`
///                 that participate in Pipelines to properly support
///                 transformer chain deserialization.
///
template <typename T>
class HasTransformerType {
private:
    // ----------------------------------------------------------------------
    // |  Private Methods
    template <typename U> static std::true_type check(typename U::TransformerType *);
    template <typename U> static std::false_type check(...);

public:
    // ----------------------------------------------------------------------
    // |  Public Types
    static constexpr bool const             value = std::is_same<std::true_type, decltype(check<T>(nullptr))>::value;
};

/////////////////////////////////////////////////////////////////////////
///  \class         HasFitBufferInputType
///  \brief         Contains a constexpr value that is true if T has a
///                 `FitBufferInputType` type.
///
template <typename T>
class HasFitBufferInputType {
private:
    // ----------------------------------------------------------------------
    // |  Private Methods
    template <typename U> static std::true_type check(typename U::FitBufferInputType *);
    template <typename U> static std::false_type check(...);

public:
    // ----------------------------------------------------------------------
    // |  Public Types
    static constexpr bool const             value = std::is_same<std::true_type, decltype(check<T>(nullptr))>::value;
};

/////////////////////////////////////////////////////////////////////////
///  \class         NormalizePipeline
///  \brief         Potentially modifies a pipeline to ensure that the
///                 final element in the pipeline returns a value
///                 (rather than a reference, which is what would be
///                 returned by an `AnnotationEstimator`).
///
template <typename PipelineT, bool IsLastElementTransformerEstimator>
struct NormalizePipeline {
    using type                              = PipelineT;
};

/////////////////////////////////////////////////////////////////////////
///  \class         NormalizePipeline<PipelineT,
///  \brief         Overload for a Pipeline that ends with an `AnnotationEstimator`.
///                 For these types of pipeline, we need to add a final element
///                 in the chain to ensure that we aren't returning a reference.
///
template <typename PipelineT>
struct NormalizePipeline<PipelineT, false> {
    using LastInputType                     = typename std::tuple_element<std::tuple_size<PipelineT>::value - 1, PipelineT>::type::InputType;

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wold-style-cast"
#endif

    // Note that we are using an old-style cast here as clang was generating errors
    // with reinterpret_cast.

    // This code adds a new `Estimator` to the tail end of the pipeline to ensure that
    // the final transformed type is not a reference. The syntax here is wonky, as I
    // don't know of a way to append an element to an existing tuple at compile time
    // except by using std::make_tuple. This technique simulates invoking that functionality
    // in order to get the actual result of the expressing using decltype.
    using EstimatorChainSuffixEstimator                 = EstimatorChainSuffixEstimator<LastInputType>;
    using EstimatorChainSuffixEstimatorConstRawPtr      = EstimatorChainSuffixEstimator const *;

    using type                              = decltype(std::tuple_cat(*(PipelineT *)(nullptr), std::make_tuple(*(EstimatorChainSuffixEstimatorConstRawPtr)(nullptr))));

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif
};

/////////////////////////////////////////////////////////////////////////
///  \class         LastTransformerEstimatorIndexImpl
///  \brief         Contains a constexpr value of N if the associated
///                 `Estimator` is a `TransformerEstimator` or -1.
///
template <int N, typename PipelineT>
struct LastTransformerEstimatorIndexImpl {
    static constexpr int const              value = IsTransformerEstimator<typename std::tuple_element<N, PipelineT>::type>::value ? N : -1;
};

/////////////////////////////////////////////////////////////////////////
///  \class         LastTransformerEstimatorIndex
///  \brief         Contains a constexpr value that is the index of the
///                 last `TransformerEstimator` in the list. A value of
///                 -1 indicates that no `TransformerEstimators` were found.
///
template <int N, typename PipelineT, typename EnableT=void>
struct LastTransformerEstimatorIndex;

/////////////////////////////////////////////////////////////////////////
///  \class         LastTransformerEstimatorIndex
///  \brief         Overload for any element other than the last
///
template <int N, typename PipelineT>
struct LastTransformerEstimatorIndex<
    N,
    PipelineT,
    std::enable_if_t<N != std::tuple_size<PipelineT>::value - 1>
> {
    static constexpr int const              value = std::max(LastTransformerEstimatorIndex<N + 1, PipelineT>::value, LastTransformerEstimatorIndexImpl<N, PipelineT>::value);
};

/////////////////////////////////////////////////////////////////////////
///  \class         LastTransformerEstimatorIndex
///  \brief         Overload for the last element
///
template <int N, typename PipelineT>
struct LastTransformerEstimatorIndex<
    N,
    PipelineT,
    std::enable_if_t<N == std::tuple_size<PipelineT>::value - 1>
> {
    static constexpr int const              value = LastTransformerEstimatorIndexImpl<N, PipelineT>::value;
};

/////////////////////////////////////////////////////////////////////////
///  \class         ValidateEstimator
///  \brief         Validates that the `Estimator` is valid `TransformerEstimator`.
///
template <typename TransformerEstimatorT, bool IsTransformerEstimatorV>
class ValidateEstimatorImpl {
public:
    static_assert(
        (
            std::is_lvalue_reference<typename TransformerEstimatorT::TransformedType>::value == false
            && std::is_rvalue_reference<typename TransformerEstimatorT::TransformedType>::value == false
        ),
        "`TransformerEstimators` should not return reference types"
    );

    static_assert(HasTransformerType<TransformerEstimatorT>::value, "`TransformerEstimators` must contain a type named `TransformerType` to support construction via `Archive` objects");
};


/////////////////////////////////////////////////////////////////////////
///  \class         ValidateEstimatorImpl
///  \brief         Validates that the `Estimator` is a valid `AnnotationEstimator`.
///
template <typename AnnotationEstimatorT>
struct ValidateEstimatorImpl<
    AnnotationEstimatorT,
    false
> {
    static_assert(std::is_lvalue_reference<typename AnnotationEstimatorT::InputType>::value, "`InputType` should be a reference");
};

/////////////////////////////////////////////////////////////////////////
///  \class         ValidateEstimator
///  \brief         Validates that the `Estimator` is a valid `Estimator`
///                 by invoking type-specific functionality.
///
template <typename EstimatorT>
struct ValidateEstimator :
    public ValidateEstimatorImpl<EstimatorT, IsTransformerEstimator<EstimatorT>::value>
{
    static_assert(HasFitBufferInputType<EstimatorT>::value, "This doesn't appear to be an `Estimator`; did you pass a `Transformer` object instead?");

    static constexpr bool const             value = true;
};

/////////////////////////////////////////////////////////////////////////
///  \class         ValidatePipelineEstimatorsImpl_Chained
///  \brief         Overload for any `Estimator` other than the last in a multi-estimator pipeline
///                 that is a `TransformerEstimator`.
///
template <typename EstimatorT, typename NextEstimatorT, bool IsTransformerEsitmatorV>
struct ValidatePipelineEstimatorsImpl_Chained {
private:
    using RawNextType                       = std::remove_cv_t<std::remove_reference_t<typename NextEstimatorT::InputType>>;

public:
    static_assert(std::is_same<typename EstimatorT::TransformedType, RawNextType>::value, "The `InputType` of the next `Estimator` must match the `TransformedType` of this `Estimator`");

    static constexpr bool const             value = true;
};

/////////////////////////////////////////////////////////////////////////
///  \class         ValidatePipelineEstimatorsImpl_Chained
///  \brief         Overload for any `Estimator` other than the last in a multi-estimator pipeline
///                 that is not a `TransfomerEstimator`.
///
template <typename EstimatorT, typename NextEstimatorT>
struct ValidatePipelineEstimatorsImpl_Chained<
    EstimatorT,
    NextEstimatorT,
    false
> {
    static_assert(std::is_same<typename EstimatorT::InputType, typename NextEstimatorT::InputType>::value, "The `InputType` of the next `Estimator` must match the `TransformedType` of this `Estimator`");

    static constexpr bool const             value = true;
};

/////////////////////////////////////////////////////////////////////////
///  \class         ValidatePipelineEstimatorsImpl
///  \brief         Validates an `Estimator` within a pipeline. This is a
///                 default implementation to setup partial template instantiation
///
template <int N, typename PipelineT, typename EnableT=void>
struct ValidatePipelineEstimatorsImpl;

/////////////////////////////////////////////////////////////////////////
///  \class         ValidatePipelineEstimatorsImpl
///  \brief         Overload for any `Estimator` other than the last one
///                 in a multi-estimator pipeline.
///
template <int N, typename PipelineT>
struct ValidatePipelineEstimatorsImpl<
    N,
    PipelineT,
    std::enable_if_t<N != std::tuple_size<PipelineT>::value - 1>
> {
    using EstimatorType                     = typename std::tuple_element<N, PipelineT>::type;
    using NextEstimator                     = typename std::tuple_element<N + 1, PipelineT>::type;

    static_assert(ValidateEstimator<EstimatorType>::value, "The `Estimator` is not valid");

    static_assert(
        ValidatePipelineEstimatorsImpl_Chained<
            EstimatorType,
            NextEstimator,
            IsTransformerEstimator<EstimatorType>::value
        >::value,
        "The `Estimator` is not valid within a pipeline chain"
    );

    static_assert(ValidatePipelineEstimatorsImpl<N + 1, PipelineT>::value, "The next `Estimator` is not valid");

    static constexpr bool const             value = true;
};

/////////////////////////////////////////////////////////////////////////
///  \class         ValidatePipelineEstimatorsImpl<
///  \brief         Overload for the last `Estimator` in a multi-estimator
///                 pipeline.
///
template <int N, typename PipelineT>
struct ValidatePipelineEstimatorsImpl<
    N,
    PipelineT,
    std::enable_if_t<N == std::tuple_size<PipelineT>::value - 1>
> {
    static_assert(ValidateEstimator<typename std::tuple_element<N, PipelineT>::type>::value, "The `Estimator` is not valid");

    static constexpr bool const             value = true;
};

/////////////////////////////////////////////////////////////////////////
///  \class         ValidatePipelineEstimators
///  \brief         Validates that `Estimators` in the pipeline are valid
///                 relative to each other.
///
template <typename PipelineT>
struct ValidatePipelineEstimators :
    private ValidatePipelineEstimatorsImpl<0, PipelineT>
{
    static constexpr bool const             value = true;
};

} // anonymous namespace

/////////////////////////////////////////////////////////////////////////
///  \class         PipelineTraits
///  \brief         Contains compile-time trait information about a pipeline
///                 of `Estimators`.
///
template <typename... Ts>
struct PipelineTraits {
    static_assert(LastTransformerEstimatorIndex<0, std::tuple<Ts...>>::value != -1, "There must be at least one `TransformerEstimator` in the pipeline");
    static_assert(ValidatePipelineEstimators<std::tuple<Ts...>>::value, "The `Estimator` pipeline is not valid");

    // Ensure that the pipeline doesn't return a reference (which can happen
    // when the last `Estimator` in the pipeline is an `AnnotationEstimator`.
    using Pipeline =
        typename NormalizePipeline<
            std::tuple<Ts...>,
            IsTransformerEstimator<
                typename std::tuple_element<
                    sizeof...(Ts) - 1,
                    std::tuple<Ts...>
                >::type
            >::value
        >::type;

    using InputType                         = typename std::tuple_element<0, Pipeline>::type::InputType;
    using TransformedType                   = typename std::tuple_element<std::tuple_size<Pipeline>::value - 1, Pipeline>::type::TransformedType;
};

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
namespace {

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElementBase
///  \brief         Functionality common to all `TransformerEstimator` chain elements
///                 within a pipeline.
///
template <
    int N,
    typename PipelineT,
    bool IsTransformerEstimatorV
>
class EstimatorChainElementBase :
    public std::tuple_element<N, PipelineT>::type {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using EstimatorType                     = typename std::tuple_element<N, PipelineT>::type;
    using TransformerUniquePtr              = typename EstimatorType::TransformerUniquePtr;
    using Transformer                       = typename TransformerUniquePtr::element_type;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    template <typename... ArgsT>
    EstimatorChainElementBase(ArgsT &&... args) :
        EstimatorType(std::forward<ArgsT>(args)...) {
    }

    void complete_training(void) {
        EstimatorType::complete_training();
        init_transformer();
    }

    bool has_created_transformer(void) const {
        return EstimatorType::has_created_transformer();
    }

    void init_transformer(void) {
        assert(!_pTransformer);
        _pTransformer = EstimatorType::create_transformer();
    }

    Transformer & get_transformer(void) const {
        assert(_pTransformer);
        return *_pTransformer;
    }

    TransformerUniquePtr move_transformer(void) {
        assert(_pTransformer);
        return std::move(_pTransformer);
    }

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    TransformerUniquePtr                    _pTransformer;
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElementBase
///  \brief         Functionality common to all `AnnotationEstimator` chain
///                 elements within a pipeline.
///
template <int N, typename PipelineT>
class EstimatorChainElementBase<
    N,
    PipelineT,
    false
> :
    public std::tuple_element<N, PipelineT>::type {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using EstimatorType                     = typename std::tuple_element<N, PipelineT>::type;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    using EstimatorType::EstimatorType;

    inline bool has_created_transformer(void) const {
        // This will never create a transformer, but return true so we don't get
        // spurious attempts to create one.
        return true;
    }

    inline void init_transformer(void) {}
};

// ----------------------------------------------------------------------
// |  Forward Declaration
template <int N, typename PipelineT, typename EnableT>
class EstimatorChainElement;

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElementInterFitter
///  \brief         Functionality common to `TransformerEstimators` that
///                 are chained elements (other than the last) in a multi-
///                 chain pipeline.
///
template <
    typename EstimatorChainElementT,        // Curiously Recurring Template Pattern
    int N,
    typename PipelineT,
    bool IsTransformerEstimatorV
>
class EstimatorChainElementInterFitter {
protected:
    // ----------------------------------------------------------------------
    // |
    // |  Protected Types
    // |
    // ----------------------------------------------------------------------
    using EstimatorType                     = typename std::tuple_element<N, PipelineT>::type;

    // ----------------------------------------------------------------------
    // |
    // |  Protected Methods
    // |
    // ----------------------------------------------------------------------
    inline Estimator::FitResult fit(typename EstimatorType::InputType value) {
        return fit(&value, 1);
    }

    inline Estimator::FitResult fit(typename EstimatorType::FitBufferInputType const *pBuffer, size_t cBuffer) {
        // ----------------------------------------------------------------------
        using EstimatorChainElementBase     = typename EstimatorChainElementT::EstimatorChainElementBase;
        using NextEstimatorChainElement     = typename EstimatorChainElementT::NextEstimatorChainElement;
        // ----------------------------------------------------------------------

        EstimatorChainElementT &                                            parent(static_cast<EstimatorChainElementT &>(*this));

        // Ideally, we would call `get_transformer` off of parent. However, this creates ambiguity between that implementing
        // in parent's `EstimatorChainElementBase` class or `EstimatorChainElement<N + 1, PipelineT>`. Unfortunately, we
        // can't add the statement `using EstimatorChainElementBase::get_transformer`, as `AnnotationEstimators` do not provide
        // this functionality. However, here we know that `EstimatorChainElementBase` provides the method since the same functionality
        // used to specialize this code is the same functionality used to specialize the element base.
        //
        // We can make everything work by casing the parent to the base that we know exists.
        EstimatorChainElementBase &                                         base(static_cast<EstimatorChainElementBase &>(parent));
        NextEstimatorChainElement &                                         next(static_cast<NextEstimatorChainElement &>(parent));
        typename EstimatorChainElementBase::Transformer &                   transformer(base.get_transformer());

        // Transform each value in the buffer before invoking the next Estimator
        typename EstimatorType::FitBufferInputType const * const            pEndBuffer(pBuffer + cBuffer);

        while(pBuffer < pEndBuffer) {
            Estimator::FitResult const      result(next.fit(transformer.execute(*pBuffer++)));

            if(result != Estimator::FitResult::Continue)
                return result;
        }

        return Estimator::FitResult::Continue;
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElementInterFitter
///  \brief         Functionality common to `AnnotationEstimators` that
///                 are chained elements (other than the last) in a multi-
///                 chain pipeline.
///
template <typename EstimatorChainElementT, int N, typename PipelineT>
class EstimatorChainElementInterFitter<
    EstimatorChainElementT,                 // Curiously Recurring Template Pattern
    N,
    PipelineT,
    false
> {
protected:
    // ----------------------------------------------------------------------
    // |
    // |  Protected Types
    // |
    // ----------------------------------------------------------------------
    using EstimatorType                     = typename std::tuple_element<N, PipelineT>::type;

    // ----------------------------------------------------------------------
    // |
    // |  Protected Methods
    // |
    // ----------------------------------------------------------------------
    inline typename Estimator::FitResult fit(typename EstimatorType::InputType value) {
        return fit(&value, 1);
    }

    inline typename Estimator::FitResult fit(typename EstimatorType::FitBufferInputType const *pBuffer, size_t cBuffer) {
        // ----------------------------------------------------------------------
        using NextEstimatorChainElement     = typename EstimatorChainElementT::NextEstimatorChainElement;
        // ----------------------------------------------------------------------

        EstimatorChainElementT &            parent(static_cast<EstimatorChainElementT &>(*this));
        NextEstimatorChainElement &         next(static_cast<NextEstimatorChainElement &>(parent));

        // Since we don't have to perform any transformations, we can send the
        // entire buffer to the next Estimator.
        return next.fit(pBuffer, cBuffer);
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElement
///  \brief         An `Estimator` within a pipeline. This is a default
///                 implementation to setup partial template instantiation.
///
template <int N, typename PipelineT, typename EnableT=void>
class EstimatorChainElement;

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElement
///  \brief         Overload for any element other than the last in a pipeline.
///
template <int N, typename PipelineT>
class EstimatorChainElement<
    N,
    PipelineT,
    std::enable_if_t<N != std::tuple_size<PipelineT>::value - 1>
> :
    public EstimatorChainElementBase<
        N,
        PipelineT,
        IsTransformerEstimator<typename std::tuple_element<N, PipelineT>::type>::value
    >,
    public EstimatorChainElementInterFitter<
        EstimatorChainElement<N, PipelineT>,
        N,
        PipelineT,
        IsTransformerEstimator<typename std::tuple_element<N, PipelineT>::type>::value
    >,
    public EstimatorChainElement<N + 1, PipelineT>
{
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using EstimatorType                     = typename std::tuple_element<N, PipelineT>::type;
    using EstimatorChainElementBase         = EstimatorChainElementBase<N, PipelineT, IsTransformerEstimator<EstimatorType>::value>;
    using EstimatorChainElementInterFitter  = EstimatorChainElementInterFitter<EstimatorChainElement<N, PipelineT>, N, PipelineT, IsTransformerEstimator<EstimatorType>::value>;

    using NextEstimatorChainElement         = EstimatorChainElement<N + 1, PipelineT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    EstimatorChainElement(AnnotationMapsPtr pAllColumnAnnotaitons) :
        EstimatorChainElementBase(pAllColumnAnnotaitons),
        NextEstimatorChainElement(pAllColumnAnnotaitons) {
    }

    bool is_all_training_complete() const {
        return EstimatorChainElementBase::is_training_complete() && NextEstimatorChainElement::is_all_training_complete();
    }

    Estimator::FitResult fit(typename EstimatorType::InputType value) {
        return fit(&value, 1);
    }

    Estimator::FitResult fit(typename EstimatorType::FitBufferInputType const *pBuffer, size_t cBuffer) {
        // Perform local training (if necessary)
        if(EstimatorChainElementBase::is_training_complete() == false) {
            Estimator::FitResult            result(EstimatorChainElementBase::fit(pBuffer, cBuffer));

            if(result == Estimator::FitResult::Complete) {
                _received_forceful_completion = true;
                NextEstimatorChainElement::complete_training(false);

                if(NextEstimatorChainElement::is_all_training_complete() == false)
                    result = Estimator::FitResult::ResetAndContinue;
            }

            return result;
        }

        // Invoke the next Estimator
        return EstimatorChainElementInterFitter::fit(pBuffer, cBuffer);
    }

    Estimator::FitResult complete_training(bool is_forceful_completion) {
        if(EstimatorChainElementBase::is_training_complete() == false) {
            if(is_forceful_completion) {
                // If here, the completion event generated by a call to complete outside
                // of the pipeline. Force complete this estimator and reset the flag so
                // downstream estimators aren't forced to complete as well.
                EstimatorChainElementBase::complete_training();

                is_forceful_completion = false;
                _received_forceful_completion = true;
            } else
                return Estimator::FitResult::ResetAndContinue;
        } else {
            if(EstimatorChainElementBase::has_created_transformer() == false) {
                // If here, we are looking at an inference-only estimator. Create the
                // transformer now that the ancestor state data is available.
                EstimatorChainElementBase::init_transformer();
                _received_forceful_completion = true;
            }
        }

        // If this is a forceful completion but we haven't received a forceful creation
        // notification yet, this current event is due to an internal estimator completing
        // themselves. Unset the flag so any downstream estimators aren't forced to
        // complete incorrectly.
        if(is_forceful_completion && _received_forceful_completion == false) {
            is_forceful_completion = false;
            _received_forceful_completion = true;
        }

        return NextEstimatorChainElement::complete_training(is_forceful_completion);
    }

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    bool                                    _received_forceful_completion = false;
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElement
///  \brief         Overload for the last element in a pipeline.
///
template <int N, typename PipelineT>
class EstimatorChainElement<
    N,
    PipelineT,
    std::enable_if_t<N == std::tuple_size<PipelineT>::value - 1>
> :
    public EstimatorChainElementBase<
        N,
        PipelineT,
        IsTransformerEstimator<typename std::tuple_element<N, PipelineT>::type>::value
    >
{
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using EstimatorType                     = typename std::tuple_element<N, PipelineT>::type;
    using EstimatorChainElementBase         = EstimatorChainElementBase<N, PipelineT, IsTransformerEstimator<EstimatorType>::value>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    using EstimatorChainElementBase::EstimatorChainElementBase;

    bool is_all_training_complete(void) const {
        return EstimatorChainElementBase::is_training_complete();
    }

    Estimator::FitResult complete_training(bool is_forceful_completion) {
        if(is_forceful_completion) {
            if(EstimatorChainElementBase::is_training_complete() == false)
                EstimatorChainElementBase::complete_training();
        } else {
            if(EstimatorChainElementBase::has_created_transformer() == false)
                EstimatorChainElementBase::init_transformer();
        }

        // While this chained element may be complete, we want to return a value that captures the
        // state of the entire chain.
        return EstimatorChainElementBase::is_training_complete() ? Estimator::FitResult::Complete : Estimator::FitResult::ResetAndContinue;
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerChainElementBase
///  \brief         Implements functionality common to all `TransformerEstimator`-
///                 based `Transformers`.
///
template <
    int N,
    typename PipelineT,
    bool IsTransformerEstimatorT
>
class TransformerChainElementBase {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using EstimatorChainElement             = EstimatorChainElement<N, PipelineT>;
    using EstimatorChainElementBase         = typename EstimatorChainElement::EstimatorChainElementBase;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TransformerChainElementBase(EstimatorChainElement &estimator) :
        _pTransformer(static_cast<EstimatorChainElementBase &>(estimator).move_transformer()) {
    }

    TransformerChainElementBase(Archive &ar) :
        _pTransformer(std::make_unique<typename EstimatorChainElement::EstimatorType::TransformerType>(ar)) {
    }

    inline typename EstimatorChainElement::EstimatorType::TransformedType execute(typename EstimatorChainElement::EstimatorType::InputType value) {
        return _pTransformer->execute(value);
    }

    inline void save(Archive &ar) const {
        _pTransformer->save(ar);
    }

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    typename EstimatorChainElement::EstimatorType::TransformerUniquePtr const   _pTransformer;
};

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerChainElementBase
///  \brief         Implements functionality common to all `AttributeEstimator`-
///                 based `Transformers` (which don't do anything when invoked).
///
template <int N, typename PipelineT>
class TransformerChainElementBase<N, PipelineT, false> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using EstimatorChainElement             = EstimatorChainElement<N, PipelineT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    inline TransformerChainElementBase(EstimatorChainElement &) {}
    inline TransformerChainElementBase(Archive &) {}

    inline typename EstimatorChainElement::EstimatorType::InputType execute(typename EstimatorChainElement::EstimatorType::InputType value) {
        // No change
        return value;
    }

    inline void save(Archive &) const {
        // Nothing to do, as these `Transformers` will never have any state.
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerChainElement
///  \brief         A single `Transformer` within a chain of
///                 `Transformers`. This is a default implementation
///                 to setup partial template specialization.
///
template <int N, typename PipelineT, typename EnableT=void>
class TransformerChainElement;

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerChainElement
///  \brief         Overload for any element other than the last in a
///                 pipeline.
///
template <int N, typename PipelineT>
class TransformerChainElement<
    N,
    PipelineT,
    std::enable_if_t<N != std::tuple_size<PipelineT>::value - 1>
> :
    public TransformerChainElementBase<
        N,
        PipelineT,
        IsTransformerEstimator<typename std::tuple_element<N, PipelineT>::type>::value
    >,
    public TransformerChainElement<N + 1, PipelineT>
{
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using NextEstimatorChainElement         = EstimatorChainElement<N + 1, PipelineT>;
    using EstimatorChainElement             = EstimatorChainElement<N, PipelineT>;
    using NextTransformerChainElement       = TransformerChainElement<N + 1, PipelineT>;

    using TransformerType                   = TransformerChainElementBase<
        N,
        PipelineT,
        IsTransformerEstimator<typename std::tuple_element<N, PipelineT>::type>::value
    >;

    using TransformedType                   = typename std::tuple_element<std::tuple_size<PipelineT>::value - 1, PipelineT>::type::TransformedType;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TransformerChainElement(EstimatorChainElement &element) :
        TransformerType(element),
        NextTransformerChainElement(static_cast<NextEstimatorChainElement &>(element)) {
    }

    TransformerChainElement(Archive &ar) :
        TransformerType(ar),
        NextTransformerChainElement(ar) {
    }

    inline TransformedType execute(typename EstimatorChainElement::EstimatorType::InputType value) {
        return NextTransformerChainElement::execute(TransformerType::execute(value));
    }

    inline void save(Archive &ar) const {
        TransformerType::save(ar);
        NextTransformerChainElement::save(ar);
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerChainElement
///  \brief         Overload for the last element in a pipeline.
///
template <int N, typename PipelineT>
class TransformerChainElement<
    N,
    PipelineT,
    std::enable_if_t<N == std::tuple_size<PipelineT>::value - 1>
> :
    public TransformerChainElementBase<
        N,
        PipelineT,
        IsTransformerEstimator<typename std::tuple_element<N, PipelineT>::type>::value
    >
{
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using EstimatorChainElement             = EstimatorChainElement<N, PipelineT>;

    using TransformerType = TransformerChainElementBase<
        N,
        PipelineT,
        IsTransformerEstimator<typename std::tuple_element<N, PipelineT>::type>::value
    >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TransformerChainElement(EstimatorChainElement &element) :
        TransformerType(element) {
    }

    TransformerChainElement(Archive &ar) :
        TransformerType(ar) {
    }

    // Use the `execute` and `save` methods from the base class.
};

} // anonymous namespace

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerChain
///  \brief         Chain of `Transformers`.
///
template <typename PipelineT>
class TransformerChain : public TransformerChainElement<0, PipelineT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerChainElement<0, PipelineT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    template <typename EstimatorChainT>
    TransformerChain(EstimatorChainT &estimators) :
        BaseType(static_cast<EstimatorChainElement<0, PipelineT> &>(estimators)) {
    }

    TransformerChain(Archive &ar) :
        BaseType(ar) {
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChain
///  \brief         Chain of `Estimators`.
///
template <typename PipelineT>
class EstimatorChain : public EstimatorChainElement<0, PipelineT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = EstimatorChainElement<0, PipelineT>;
    using TransformerType                   = TransformerChain<PipelineT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    EstimatorChain(AnnotationMapsPtr pAllColumnAnnotations) :
        BaseType(std::move(pAllColumnAnnotations)) {
            // Give initial inference-only estimators an opportunity to create transformers
            BaseType::complete_training(false);
    }
};

} // namespace Details
} // namespace Featurizer
} // namespace Microsoft
