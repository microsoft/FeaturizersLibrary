// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../../Featurizer.h"

#include "Details/EstimatorTraits.h"
#include "Details/FilterTraits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

/////////////////////////////////////////////////////////////////////////
///  \class         FilterTransformer
///  \brief         Calls the ChainedTransformerT with a subset of the elements
///                 in the input tuple.
///
template <
    typename ChainedTransformerT,
    typename InputTupleT,
    size_t... FilterInputTupleIndexVs
>
class FilterTransformer :
    public Transformer<
        InputTupleT,
        typename Details::FilterTransformerTraits<ChainedTransformerT, InputTupleT, FilterInputTupleIndexVs...>::TransformedType
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TheseFilterTransformerTraits      = Details::FilterTransformerTraits<ChainedTransformerT, InputTupleT, FilterInputTupleIndexVs...>;

    using BaseType =
        Transformer<
            InputTupleT,
            typename TheseFilterTransformerTraits::TransformedType
        >;

    using ChainedTransformerUniquePtr =
        std::unique_ptr<
            Transformer<
                typename ChainedTransformerT::InputType,
                typename ChainedTransformerT::TransformedType
            >
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    template <typename... ChainedTransformerConstructArgTs>
    FilterTransformer(ChainedTransformerConstructArgTs &&... args);
    FilterTransformer(ChainedTransformerUniquePtr pTransformer);
    FilterTransformer(Archive &ar);

    ~FilterTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FilterTransformer);

    bool operator==(FilterTransformer const &other) const;
    bool operator!=(FilterTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    ChainedTransformerUniquePtr             _pTransformer;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        _pTransformer->execute(
            TheseFilterTransformerTraits::ToFilteredType(input),
            [&input, &callback](typename ChainedTransformerT::TransformedType value) {
                callback(TheseFilterTransformerTraits::ToTransformedType(input, std::move(value)));
            }
        );
    }

    void flush_impl(typename BaseType::CallbackFunction const &/*callback*/) override {
        _pTransformer->flush(
            [/*&callback*/](typename ChainedTransformerT::TransformedType /*value*/) {
                // If errors are raised here, it is because the ChainedTransformer has dynamic output.
                // This functionality isn't implemented right now, as we aren't sure of a good
                // way to augment `value` with the row information provided when the corresponding
                // call to `execute` was made. Furthermore, we don't have a good way to associated
                // calls to this callback with multiple calls to `execute`. Further design changes
                // will be necessary if this functionality is required in the future.
                throw std::runtime_error("Transformers that rely on flush can't be wrapped in this object at this time");
            }
        );
    }
};

namespace Impl {

/////////////////////////////////////////////////////////////////////////
///  \class         FilterEstimatorWrapper
///  \brief         Contains an Estimator. This class is useful to tightly
///                 control initialization order when a class has a dependency
///                 on this class and other bases that require an initialized
///                 estimator.
///
template <typename EstimatorT>
struct FilterEstimatorWrapper {
    // ----------------------------------------------------------------------
    // |  Public Data
    EstimatorT                              WrappedEstimator;

    // ----------------------------------------------------------------------
    // |  Public Methods
    template <typename... EstimatorConstructorArgTs>
    FilterEstimatorWrapper(EstimatorConstructorArgTs &&... args);
    ~FilterEstimatorWrapper(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FilterEstimatorWrapper);
};

/////////////////////////////////////////////////////////////////////////
///  \class         FilterEstimatorImplBase
///  \brief         Functionality common to both FitEstimator-based-
///                 and TransformerEstimator-based filter estimators.
///
template <
    typename BaseT,
    typename EstimatorT,
    typename InputTupleT,
    size_t... FilterInputTupleIndexVs
>
class FilterEstimatorImplBase :
    // Do not reorder these bases, as BaseT relies on functionality provided by
    // FilterEstimatorWrapper<EstimatorT>; BaseT's ctor takes the estimator name
    // which is created from an instantiated Estimator instance.
    //
    //      1) The Estimator is instantiated in FilterEstimatorWrapper
    //      2) A string passed in BaseT's constructor is created off of the estimator created in #1
    //      3) A reference to the estimator created in #1 is created so that it can be accessed by derived classes
    //
    private FilterEstimatorWrapper<EstimatorT>,
    public BaseT {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    template <typename... EstimatorConstructorArgTs>
    FilterEstimatorImplBase(AnnotationMapsPtr pAllColumnAnnotations, EstimatorConstructorArgTs &&... args);

    ~FilterEstimatorImplBase(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FilterEstimatorImplBase);

    EstimatorT const & get_estimator(void) const;

protected:
    // ----------------------------------------------------------------------
    // |
    // |  Protected Data
    // |
    // ----------------------------------------------------------------------
    EstimatorT &                            _estimator;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;
    FitResult fit_impl(typename BaseT::InputType const *pItems, size_t cItems) override;
    void complete_training_impl(void) override;
};

/////////////////////////////////////////////////////////////////////////
///  \class         FilterEstimatorImpl
///  \brief         Baseline template for implementations specialized below.
///
template <
    bool IsTransformerEstimatorV,
    typename EstimatorT,
    typename InputTupleT,
    size_t... FilterInputTupleIndexVs
>
class FilterEstimatorImpl;

/////////////////////////////////////////////////////////////////////////
///  \class         FilterEstimatorImpl
///  \brief         Implementation for a FilterEstimator when the underlying
///                 Estimator is a FitEstimator.
///
template <
    typename EstimatorT,
    typename InputTupleT,
    size_t... FilterInputTupleIndexVs
>
class FilterEstimatorImpl<
    false, /* IsTransformerEstimator */
    EstimatorT,
    InputTupleT,
    FilterInputTupleIndexVs...
> :
    public Impl::FilterEstimatorImplBase<
        FitEstimator<InputTupleT>,
        EstimatorT,
        InputTupleT,
        FilterInputTupleIndexVs...
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TheseFilterFeaturizerTraits       = Details::FilterFeaturizerTraits<InputTupleT, FilterInputTupleIndexVs...>;

    using BaseType =
        Impl::FilterEstimatorImplBase<
            FitEstimator<InputTupleT>,
            EstimatorT,
            InputTupleT,
            FilterInputTupleIndexVs...
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    using BaseType::BaseType;

    ~FilterEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FilterEstimatorImpl);
};

/////////////////////////////////////////////////////////////////////////
///  \class         FilterEstimatorImpl
///  \brief         Implementation for a FilterEstimator when the underlying
///                 Estimator is a TransformerEstimator.
///
template <
    typename EstimatorT,
    typename InputTupleT,
    size_t... FilterInputTupleIndexVs
>
class FilterEstimatorImpl<
    true, /* IsTransformerEstimator */
    EstimatorT,
    InputTupleT,
    FilterInputTupleIndexVs...
> :
    public Impl::FilterEstimatorImplBase<
        TransformerEstimator<InputTupleT, typename Details::FilterTransformerTraits<EstimatorT, InputTupleT, FilterInputTupleIndexVs...>::TransformedType>,
        EstimatorT,
        InputTupleT,
        FilterInputTupleIndexVs...
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TheseFilterTransformerTraits      = Details::FilterTransformerTraits<EstimatorT, InputTupleT, FilterInputTupleIndexVs...>;

    using BaseType =
        Impl::FilterEstimatorImplBase<
            TransformerEstimator<InputTupleT, typename TheseFilterTransformerTraits::TransformedType>,
            EstimatorT,
            InputTupleT,
            FilterInputTupleIndexVs...
        >;

    using TransformerType                   = FilterTransformer<typename EstimatorT::TransformerType, InputTupleT, FilterInputTupleIndexVs...>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    using BaseType::BaseType;
    ~FilterEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FilterEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return typename BaseType::TransformerUniquePtr(new TransformerType(this->_estimator.create_transformer()));
    }
};

} // namespace Impl

/////////////////////////////////////////////////////////////////////////
///  \typedef       FilterEstimatorImpl
///  \brief         Estimator that filters an input tuple into the input
///                 type required by the provided Estimator. This class
///                 helps with composability when creating pipelines in
///                 that an existing estimator can be used with input
///                 that is slightly different than what is required by
///                 the estimator iself.
///
///                 Note that the name of this estimator will be
///                     "Filter" + EstimatorT::Name.
///
///                 Example:
///                     struct MyEstimator : public FitEstimator<double> {}
///
///                     A previous Transformer that outputs std::tuple<int, int, double>
///
///                     To use MyEstimator in this pipeline:
///
///                         using FilteredMyEstimator =
///                             FilterEstimatorImpl<
///                                 MyEstimator,
///                                 std::tuple<int, int, double>,
///                                 2 // Pass the tuple element at index 2 when invoking MyEstimator
///                             >;
///
template <
    typename EstimatorT,
    typename InputTupleT,
    size_t... FilterInputTupleIndexVs
>
using FilterEstimatorImpl =
    Impl::FilterEstimatorImpl<
        Details::IsTransformerEstimator<EstimatorT>::value,
        EstimatorT,
        InputTupleT,
        FilterInputTupleIndexVs...
    >;

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
// |  FilterTransformer
// |
// ----------------------------------------------------------------------
template <typename ChainedTransformerT, typename InputTupleT, size_t... FilerIndexVs>
template <typename... ChainedTransformerConstructArgTs>
FilterTransformer<ChainedTransformerT, InputTupleT, FilerIndexVs...>::FilterTransformer(ChainedTransformerConstructArgTs &&... args) :
    _pTransformer(new ChainedTransformerT(std::forward<ChainedTransformerConstructArgTs>(args)...)) {
}

template <typename ChainedTransformerT, typename InputTupleT, size_t... FilerIndexVs>
FilterTransformer<ChainedTransformerT, InputTupleT, FilerIndexVs...>::FilterTransformer(ChainedTransformerUniquePtr pTransformer) :
    _pTransformer(
        std::move(
            [&pTransformer](void) -> ChainedTransformerUniquePtr & {
                if(!pTransformer)
                    throw std::invalid_argument("pTransformer");

                return pTransformer;
            }()
        )
    ) {
}

template <typename ChainedTransformerT, typename InputTupleT, size_t... FilerIndexVs>
FilterTransformer<ChainedTransformerT, InputTupleT, FilerIndexVs...>::FilterTransformer(Archive &ar) :
    _pTransformer(new ChainedTransformerT(ar)) {
}

template <typename ChainedTransformerT, typename InputTupleT, size_t... FilerIndexVs>
bool FilterTransformer<ChainedTransformerT, InputTupleT, FilerIndexVs...>::operator==(FilterTransformer const &other) const {
    return static_cast<ChainedTransformerT const &>(*_pTransformer) == static_cast<ChainedTransformerT const &>(*other._pTransformer);
}

template <typename ChainedTransformerT, typename InputTupleT, size_t... FilerIndexVs>
bool FilterTransformer<ChainedTransformerT, InputTupleT, FilerIndexVs...>::operator!=(FilterTransformer const &other) const {
    return (*this == other) == false;
}

template <typename ChainedTransformerT, typename InputTupleT, size_t... FilerIndexVs>
void FilterTransformer<ChainedTransformerT, InputTupleT, FilerIndexVs...>::save(Archive &ar) const /*override*/ {
    _pTransformer->save(ar);
}

// ----------------------------------------------------------------------
// |
// |  Impl::FilterEstimatorWrapper
// |
// ----------------------------------------------------------------------
template <typename EstimatorT>
template <typename... EstimatorConstructorArgTs>
Impl::FilterEstimatorWrapper<EstimatorT>::FilterEstimatorWrapper(EstimatorConstructorArgTs &&... args) :
    WrappedEstimator(std::forward<EstimatorConstructorArgTs>(args)...) {
}

// ----------------------------------------------------------------------
// |
// |  Impl::FilterEstimatorImplBase
// |
// ----------------------------------------------------------------------
template <typename BaseT, typename EstimatorT, typename InputTupleT, size_t... FilterInputTupleIndexVs>
template <typename... EstimatorConstructorArgTs>
Impl::FilterEstimatorImplBase<BaseT, EstimatorT, InputTupleT, FilterInputTupleIndexVs...>::FilterEstimatorImplBase(AnnotationMapsPtr pAllColumnAnnotations, EstimatorConstructorArgTs &&... args) :
    FilterEstimatorWrapper<EstimatorT>(pAllColumnAnnotations, std::forward<EstimatorConstructorArgTs>(args)...),
    BaseT(std::string("Filter") + this->WrappedEstimator.Name, pAllColumnAnnotations),
    _estimator(this->WrappedEstimator) {
}

template <typename BaseT, typename EstimatorT, typename InputTupleT, size_t... FilterInputTupleIndexVs>
EstimatorT const & Impl::FilterEstimatorImplBase<BaseT, EstimatorT, InputTupleT, FilterInputTupleIndexVs...>::get_estimator(void) const {
    return _estimator;
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename BaseT, typename EstimatorT, typename InputTupleT, size_t... FilterInputTupleIndexVs>
bool Impl::FilterEstimatorImplBase<BaseT, EstimatorT, InputTupleT, FilterInputTupleIndexVs...>::begin_training_impl(void) /*override*/ {
    _estimator.begin_training();
    return _estimator.get_state() == TrainingState::Training;
}

// I don't understand why MSVC thinks that this is unreachable code
#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4702) // Unreachable code
#endif

template <typename BaseT, typename EstimatorT, typename InputTupleT, size_t... FilterInputTupleIndexVs>
FitResult Impl::FilterEstimatorImplBase<BaseT, EstimatorT, InputTupleT, FilterInputTupleIndexVs...>::fit_impl(typename BaseT::InputType const *pItems, size_t cItems) /*override*/ {
    // ----------------------------------------------------------------------
    using TheseFilterFeaturizerTraits       = Details::FilterFeaturizerTraits<InputTupleT, FilterInputTupleIndexVs...>;
    // ----------------------------------------------------------------------

    typename BaseT::InputType const * const             pEnd(pItems + cItems);

    while(pItems != pEnd) {
        FitResult                           result(_estimator.fit(TheseFilterFeaturizerTraits::ToFilteredType(*pItems)));

        if(result != FitResult::Continue)
            return result;

        ++pItems;
    }

    return FitResult::Continue;
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

template <typename BaseT, typename EstimatorT, typename InputTupleT, size_t... FilterInputTupleIndexVs>
void Impl::FilterEstimatorImplBase<BaseT, EstimatorT, InputTupleT, FilterInputTupleIndexVs...>::complete_training_impl(void) /*override*/ {
    _estimator.complete_training();
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
