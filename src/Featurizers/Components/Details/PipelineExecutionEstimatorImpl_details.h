// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "EstimatorTraits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {
namespace Details {

namespace Impl {

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Miscellaneous Impl
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////
///  \class         ValidateEstimators
///  \brief         Validates that an `Estimator` is valid within an `Estimator` chain.
///                 This template declaration is the source for partial template
///                 specializations for specific `Estimator` types.
///
template <int N, typename EstimatorTupleT, typename EnableIfT=void>
struct ValidateEstimators;

/////////////////////////////////////////////////////////////////////////
///  \class         ValidateEstimators
///  \brief         Validates `Estimators` that are not the last `Estimator`
///                 in a chain of `Estimators`.
///
template <int N, typename EstimatorTupleT>
struct ValidateEstimators<
    N,
    EstimatorTupleT,
    typename std::enable_if<N != std::tuple_size<EstimatorTupleT>::value - 1>::type
> {
    using ThisEstimator                     = typename std::tuple_element<N, EstimatorTupleT>::type;
    using NextEstimator                     = typename std::tuple_element<N + 1, EstimatorTupleT>::type;

    static_assert(
        std::is_same<
            typename EstimatorOutputType<ThisEstimator>::type,
            typename NextEstimator::InputType
        >::value,
        "The output type of this estimator must match the input type of the next estimator"
    );

    static constexpr bool const             value = ValidateEstimators<N + 1, EstimatorTupleT>::value;
};

/////////////////////////////////////////////////////////////////////////
///  \class         ValidateEstimators
///  \brief         Validates `Estimators` that are the last `Estimator`
///                 in a chain of `Estimators`.
///
template <int N, typename EstimatorTupleT>
struct ValidateEstimators<
    N,
    EstimatorTupleT,
    typename std::enable_if<N == std::tuple_size<EstimatorTupleT>::value - 1>::type
> {
    static constexpr bool const             value = true;
};

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Estimator Impl
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// |  Forward Declaration
template <
    int N,
    typename EstimatorTupleT,
    typename IsIntraChainElementEnableIfT=void,
    typename IsTransformerEstimatorEnableIfT=void
>
class EstimatorChainElement;

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElement_TransformerMixin
///  \brief         Mixin used for `TransformerEstimators`.
///
template <typename EstimatorChainElementT, int N, typename EstimatorTupleT>
class EstimatorChainElement_TransformerMixin {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using ThisEstimator                     = typename std::tuple_element<N, EstimatorTupleT>::type;
    using TransformerUniquePtr              = typename ThisEstimator::TransformerUniquePtr;
    using Transformer                       = typename TransformerUniquePtr::element_type;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TransformerUniquePtr move_transformer(void) {
        assert(_pTransformer);
        return std::move(_pTransformer);
    }

protected:
    // ----------------------------------------------------------------------
    // |
    // |  Protected Methods
    // |
    // ----------------------------------------------------------------------
    void create_transformer(void) {
        assert(!_pTransformer);

        _pTransformer = static_cast<EstimatorChainElementT &>(*this).get_estimator().create_transformer();
    }

    Transformer & get_transformer(void) {
        assert(_pTransformer);
        return *_pTransformer;
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
///  \class         EstimatorChainElement_TerminalMixin
///  \brief         Functionality common to all `Estimators` that are the
///                 last `Estimator` in a chain of `Estimators` (aka the "terminal"
///                 `Estimator`).
///
template <typename EstimatorChainElementT, int N, typename EstimatorTupleT>
class EstimatorChainElement_TerminalMixin {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using ThisEstimator                     = typename std::tuple_element<N, EstimatorTupleT>::type;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training(void) {
        EstimatorChainElementT &            thisElement(static_cast<EstimatorChainElementT &>(*this));
        ThisEstimator &                     estimator(thisElement.get_estimator());

        estimator.begin_training();

        TrainingState const                 state(estimator.get_state());

        if(state == TrainingState::Training)
            return true;
        else if(state == TrainingState::Finished)
            return false;

        assert(!static_cast<typename std::underlying_type<TrainingState>::type>(state));
        return false; // Make the compiler happy
    }

    template <typename InputT>
    FitResult fit(InputT const *pItems, size_t cItems) {
        EstimatorChainElementT &            thisElement(static_cast<EstimatorChainElementT &>(*this));
        ThisEstimator &                     estimator(thisElement.get_estimator());

        return estimator.fit(pItems, cItems);
    }

    bool on_data_completed(void) {
        EstimatorChainElementT &            thisElement(static_cast<EstimatorChainElementT &>(*this));
        ThisEstimator &                     estimator(thisElement.get_estimator());

        estimator.on_data_completed();

        TrainingState const                 state(estimator.get_state());

        if(state == TrainingState::Training)
            return false;
        else if(state == TrainingState::Finished)
            return true;

        assert(!static_cast<typename std::underlying_type<TrainingState>::type>(state));
        return true; // Make the compiler happy
    }

    void complete_training(void) {
        EstimatorChainElementT &            thisElement(static_cast<EstimatorChainElementT &>(*this));
        ThisEstimator &                     estimator(thisElement.get_estimator());

        estimator.complete_training();
        thisElement.create_transformer_if_necessary();
    }

    bool has_all_training_finished(void) const {
        EstimatorChainElementT const &      thisElement(static_cast<EstimatorChainElementT const &>(*this));
        ThisEstimator const &               estimator(thisElement.get_estimator());

        return estimator.get_state() == TrainingState::Finished;
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElement_IntraMixin
///  \brief         Functionality common to all `Estimators` that are not
///                 the last `Estimator` in a chain of `Estimators`.
///
template <typename EstimatorChainElementT, int N, typename EstimatorTupleT>
class EstimatorChainElement_IntraMixin {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using ThisEstimator                     = typename std::tuple_element<N, EstimatorTupleT>::type;
    using NextEstimator                     = typename std::tuple_element<N + 1, EstimatorTupleT>::type;
    using NextEstimatorChainElement         = EstimatorChainElement<N + 1, EstimatorTupleT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training(void) {
        EstimatorChainElementT &            thisElement(static_cast<EstimatorChainElementT &>(*this));
        NextEstimatorChainElement &         nextElement(static_cast<NextEstimatorChainElement &>(thisElement));
        ThisEstimator &                     estimator(thisElement.get_estimator());

        if(estimator.get_state() == TrainingState::Pending) {
            estimator.begin_training();

            if(estimator.get_state() != TrainingState::Training)
                complete_chained_estimator();

            return thisElement.has_all_training_finished() == false;
        }

        return nextElement.begin_training();
    }

    template <typename InputT>
    FitResult fit(InputT const *pItems, size_t cItems) {
        EstimatorChainElementT &            thisElement(static_cast<EstimatorChainElementT &>(*this));
        ThisEstimator &                     estimator(thisElement.get_estimator());

        if(estimator.get_state() == TrainingState::Training) {
            FitResult                       result(estimator.fit(pItems, cItems));

            if(result == FitResult::Continue)
                return result;

            complete_chained_estimator();

            return thisElement.has_all_training_finished() ? FitResult::Complete : FitResult::Reset;
        }

        return thisElement.execute_next_fit(pItems, cItems);
    }

    bool on_data_completed(void) {
        EstimatorChainElementT &            thisElement(static_cast<EstimatorChainElementT &>(*this));
        NextEstimatorChainElement &         nextElement(static_cast<NextEstimatorChainElement &>(thisElement));
        ThisEstimator &                     estimator(thisElement.get_estimator());

        if(estimator.get_state() == TrainingState::Training) {
            estimator.on_data_completed();

            if(estimator.get_state() != TrainingState::Training)
                complete_chained_estimator();

            return thisElement.has_all_training_finished();
        }

        thisElement.flush_transformer_if_necessary();
        return nextElement.on_data_completed();
    }

    void complete_training(void) {
        // Note that this method will only be called when the entire chain should be completed.
        // Because of this, it should travel the entire chain.
        EstimatorChainElementT &            thisElement(static_cast<EstimatorChainElementT &>(*this));
        NextEstimatorChainElement &         nextElement(static_cast<NextEstimatorChainElement &>(thisElement));
        ThisEstimator &                     estimator(thisElement.get_estimator());

        if(estimator.get_state() != TrainingState::Completed)
            complete_chained_estimator();

        nextElement.complete_training();
    }

    bool has_all_training_finished(void) const {
        EstimatorChainElementT const &      thisElement(static_cast<EstimatorChainElementT const &>(*this));
        NextEstimatorChainElement const &   nextElement(static_cast<NextEstimatorChainElement const &>(thisElement));

        return nextElement.has_all_training_finished();
    }

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void complete_chained_estimator(void) {
        EstimatorChainElementT &            thisElement(static_cast<EstimatorChainElementT &>(*this));
        NextEstimatorChainElement &         nextElement(static_cast<NextEstimatorChainElement &>(thisElement));
        ThisEstimator &                     estimator(thisElement.get_estimator());

        assert(estimator.get_state() != TrainingState::Completed);
        estimator.complete_training();
        assert(estimator.get_state() == TrainingState::Completed);

        thisElement.create_transformer_if_necessary();

        nextElement.begin_training();
    }
};

// ----------------------------------------------------------------------
// NOTE THAT THE `EstimatorChainElement` CLASSES ARE ORDERED FROM SIMPLEST TO MOST COMPLEX.
// ----------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElementBase
///  \brief         Functionality common to all `Estimators` within a chain
///                 of `Estimators`.
///
template <int N, typename EstimatorTupleT>
class EstimatorChainElementBase {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using ThisEstimator                     = typename std::tuple_element<N, EstimatorTupleT>::type;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    EstimatorChainElementBase(AnnotationMapsPtr pAllColumnAnnotations) :
        _estimator(std::move(pAllColumnAnnotations)) {
    }

    template <typename ConstructFuncT>
    EstimatorChainElementBase(ConstructFuncT const &func) :
        _estimator(func()) {
    }

    // Mixin functionality used by multiple mixins within a chain
    ThisEstimator & get_estimator(void) {
        return _estimator;
    }

    ThisEstimator const & get_estimator(void) const {
        return _estimator;
    }

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    ThisEstimator                           _estimator;
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElement
///  \brief         Terminal element, not a `TransformerEstimator`.
///
template <int N, typename EstimatorTupleT>
class EstimatorChainElement<
    N,
    EstimatorTupleT,
    typename std::enable_if<N == std::tuple_size<EstimatorTupleT>::value - 1>::type,
    typename std::enable_if<IsTransformerEstimator<typename std::tuple_element<N, EstimatorTupleT>::type>::value == false>::type
> :
    public EstimatorChainElement_TerminalMixin<
        EstimatorChainElement<N, EstimatorTupleT>,
        N,
        EstimatorTupleT
    >,
    public EstimatorChainElementBase<N, EstimatorTupleT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TerminalMixin =
        EstimatorChainElement_TerminalMixin<
            EstimatorChainElement<N, EstimatorTupleT>,
            N,
            EstimatorTupleT
        >;

    using ThisEstimatorChainElementBase     = EstimatorChainElementBase<N, EstimatorTupleT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    using ThisEstimatorChainElementBase::ThisEstimatorChainElementBase;
    using ThisEstimatorChainElementBase::get_estimator;

    using TerminalMixin::begin_training;
    using TerminalMixin::fit;
    using TerminalMixin::on_data_completed;
    using TerminalMixin::complete_training;
    using TerminalMixin::has_all_training_finished;

private:
    // ----------------------------------------------------------------------
    // |  Relationships
    friend TerminalMixin;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // Mixin functionality
    void create_transformer_if_necessary(void) {
    }

    void flush_transformer_if_necessary(void) {
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElement
///  \brief         Terminal element, is a `TransformerEstimator`.
///
template <int N, typename EstimatorTupleT>
class EstimatorChainElement<
    N,
    EstimatorTupleT,
    typename std::enable_if<N == std::tuple_size<EstimatorTupleT>::value - 1>::type,
    typename std::enable_if<IsTransformerEstimator<typename std::tuple_element<N, EstimatorTupleT>::type>::value>::type
> :
    public EstimatorChainElement_TerminalMixin<
        EstimatorChainElement<N, EstimatorTupleT>,
        N,
        EstimatorTupleT
    >,
    public EstimatorChainElement_TransformerMixin<
        EstimatorChainElement<N, EstimatorTupleT>,
        N,
        EstimatorTupleT
    >,
    public EstimatorChainElementBase<N, EstimatorTupleT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TerminalMixin =
        EstimatorChainElement_TerminalMixin<
            EstimatorChainElement<N, EstimatorTupleT>,
            N,
            EstimatorTupleT
        >;

    using TransformerMixin =
        EstimatorChainElement_TransformerMixin<
            EstimatorChainElement<N, EstimatorTupleT>,
            N,
            EstimatorTupleT
        >;

    using ThisEstimatorChainElementBase     = EstimatorChainElementBase<N, EstimatorTupleT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    using ThisEstimatorChainElementBase::ThisEstimatorChainElementBase;
    using ThisEstimatorChainElementBase::get_estimator;

    using TerminalMixin::begin_training;
    using TerminalMixin::fit;
    using TerminalMixin::on_data_completed;
    using TerminalMixin::complete_training;
    using TerminalMixin::has_all_training_finished;

    using TransformerMixin::move_transformer;

    // ----------------------------------------------------------------------
    // |  Relationships
    friend TerminalMixin;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // Mixin functionality
    void create_transformer_if_necessary(void) {
        typename ThisEstimatorChainElementBase::ThisEstimator &             thisEstimator(ThisEstimatorChainElementBase::get_estimator());

        if(thisEstimator.has_created_transformer() == false)
            TransformerMixin::create_transformer();
    }

    void flush_transformer_if_necessary(void) {
        TransformerMixin::get_transformer()->flush();
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElement
///  \brief         Not a terminal element, not a `TransformerEstimator`.
///
template <int N, typename EstimatorTupleT>
class EstimatorChainElement<
    N,
    EstimatorTupleT,
    typename std::enable_if<N != std::tuple_size<EstimatorTupleT>::value - 1>::type,
    typename std::enable_if<IsTransformerEstimator<typename std::tuple_element<N, EstimatorTupleT>::type>::value == false>::type
> :
    public EstimatorChainElement_IntraMixin<
        EstimatorChainElement<N, EstimatorTupleT>,
        N,
        EstimatorTupleT
    >,
    public EstimatorChainElementBase<N, EstimatorTupleT>,
    public EstimatorChainElement<N + 1, EstimatorTupleT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using IntraMixin =
        EstimatorChainElement_IntraMixin<
            EstimatorChainElement<N, EstimatorTupleT>,
            N,
            EstimatorTupleT
        >;

    using ThisEstimatorChainElementBase     = EstimatorChainElementBase<N, EstimatorTupleT>;
    using NextEstimatorChainElement         = EstimatorChainElement<N + 1, EstimatorTupleT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    EstimatorChainElement(AnnotationMapsPtr pAllColumnAnnotations) :
        ThisEstimatorChainElementBase(pAllColumnAnnotations),
        NextEstimatorChainElement(std::move(pAllColumnAnnotations)) {
    }

    template <typename ConstructFuncT, typename... ConstructFuncTs>
    EstimatorChainElement(ConstructFuncT && func, ConstructFuncTs &&... funcs) :
        ThisEstimatorChainElementBase(std::forward<ConstructFuncT>(func)),
        NextEstimatorChainElement(std::forward<ConstructFuncTs>(funcs)...) {
    }

    using ThisEstimatorChainElementBase::get_estimator;

    using IntraMixin::begin_training;
    using IntraMixin::fit;
    using IntraMixin::on_data_completed;
    using IntraMixin::complete_training;
    using IntraMixin::has_all_training_finished;

private:
    // ----------------------------------------------------------------------
    // |  Relationships
    friend IntraMixin;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // Mixin functionality
    template <typename InputT>
    FitResult execute_next_fit(InputT const *pItems, size_t cItems) {
        return NextEstimatorChainElement::fit(pItems, cItems);
    }

    void create_transformer_if_necessary(void) {
    }

    void flush_transformer_if_necessary(void) {
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         EstimatorChainElement
///  \brief         Not a terminal element, is a `TransformerEstimator`.
///
template <int N, typename EstimatorTupleT>
class EstimatorChainElement<
    N,
    EstimatorTupleT,
    typename std::enable_if<N != std::tuple_size<EstimatorTupleT>::value - 1>::type,
    typename std::enable_if<IsTransformerEstimator<typename std::tuple_element<N, EstimatorTupleT>::type>::value>::type
> :
    public EstimatorChainElement_IntraMixin<
        EstimatorChainElement<N, EstimatorTupleT>,
        N,
        EstimatorTupleT
    >,
    public EstimatorChainElement_TransformerMixin<
        EstimatorChainElement<N, EstimatorTupleT>,
        N,
        EstimatorTupleT
    >,
    public EstimatorChainElementBase<N, EstimatorTupleT>,
    public EstimatorChainElement<N + 1, EstimatorTupleT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using ThisEstimator                     = typename std::tuple_element<N, EstimatorTupleT>::type;

    using IntraMixin =
        EstimatorChainElement_IntraMixin<
            EstimatorChainElement<N, EstimatorTupleT>,
            N,
            EstimatorTupleT
        >;

    using TransformerMixin =
        EstimatorChainElement_TransformerMixin<
            EstimatorChainElement<N, EstimatorTupleT>,
            N,
            EstimatorTupleT
        >;

    using ThisEstimatorChainElementBase     = EstimatorChainElementBase<N, EstimatorTupleT>;
    using NextEstimatorChainElement         = EstimatorChainElement<N + 1, EstimatorTupleT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    EstimatorChainElement(AnnotationMapsPtr pAllColumnAnnotations) :
        ThisEstimatorChainElementBase(pAllColumnAnnotations),
        NextEstimatorChainElement(std::move(pAllColumnAnnotations)) {
    }

    template <typename ConstructFuncT, typename... ConstructFuncTs>
    EstimatorChainElement(ConstructFuncT && func, ConstructFuncTs &&... funcs) :
        ThisEstimatorChainElementBase(std::forward<ConstructFuncT>(func)),
        NextEstimatorChainElement(std::forward<ConstructFuncTs>(funcs)...) {
    }

    using ThisEstimatorChainElementBase::get_estimator;

    using IntraMixin::begin_training;
    using IntraMixin::fit;
    using IntraMixin::on_data_completed;
    using IntraMixin::complete_training;
    using IntraMixin::has_all_training_finished;

    using TransformerMixin::move_transformer;

private:
    // ----------------------------------------------------------------------
    // |  Relationships
    friend IntraMixin;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // Mixin functionality
    template <typename InputT>
    FitResult execute_next_fit(InputT const *pItems, size_t cItems) {
        // ----------------------------------------------------------------------
        using TransformedType               = typename ThisEstimator::TransformedType;
        using TransformedTypes              = std::vector<TransformedType>;
        // ----------------------------------------------------------------------

        TransformedTypes                    transformed;

        // Assume a 1:1 mapping between input and output
        transformed.reserve(cItems);

        auto const                          callback(
            [&transformed](TransformedType output) {
                transformed.emplace_back(std::move(output));
            }
        );

        InputT const * const                pEndItems(pItems + cItems);
        auto &                              transformer(TransformerMixin::get_transformer());

        while(pItems != pEndItems)
            transformer.execute(*pItems++, callback);

        if(transformed.empty() == false)
            return NextEstimatorChainElement::fit(transformed.data(), transformed.size());

        return FitResult::Continue;
    }

    void create_transformer_if_necessary(void) {
        typename ThisEstimatorChainElementBase::ThisEstimator &             thisEstimator(ThisEstimatorChainElementBase::get_estimator());

        if(thisEstimator.has_created_transformer() == false)
            TransformerMixin::create_transformer();
    }

    void flush_transformer_if_necessary(void) {
        // ----------------------------------------------------------------------
        using TransformedType               = typename ThisEstimator::TransformedType;
        using TransformedTypes              = std::vector<TransformedType>;
        // ----------------------------------------------------------------------

        TransformedTypes                    transformed;
        auto &                              transformer(TransformerMixin::get_transformer());

        transformer.flush(
            [&transformed](TransformedType output) {
                transformed.emplace_back(std::move(output));
            }
        );

        if(transformed.empty() == false)
            NextEstimatorChainElement::fit(transformed.data(), transformed.size());
    }
};

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Transformer Impl
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerChainElement
///  \brief         Single `Transformer` within a chain of `Transformers`.
///
template <
    int N,
    typename EstimatorTupleT,
    typename EnableIfChainPositionT=void,
    typename EnableIfIsTransformerT=void
>
class TransformerChainElement;

// ----------------------------------------------------------------------
// NOTE THAT THE `EstimatorChainElement` CLASSES ARE ORDERED FROM SIMPLEST TO MOST COMPLEX.
// ----------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerChainElement
///  \brief         Terminal element, not a `Transformer`.
///
template <int N, typename EstimatorTupleT>
class TransformerChainElement<
    N,
    EstimatorTupleT,
    typename std::enable_if<N == std::tuple_size<EstimatorTupleT>::value - 1>::type,
    typename std::enable_if<IsTransformerEstimator<typename std::tuple_element<N, EstimatorTupleT>::type>::value == false>::type
> {
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using ThisEstimatorChainElement         = EstimatorChainElement<N, EstimatorTupleT>;

public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TransformerChainElement(ThisEstimatorChainElement &) {
    }

    TransformerChainElement(Archive &) {
    }

    void save(Archive &) const {
    }

    template <typename InputT, typename CallbackT>
    void execute(InputT &input, CallbackT const &callback) {
        callback(std::move(input));
    }

    template <typename CallbackT>
    void flush(CallbackT const &) {
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerChainElement
///  \brief         Terminal element, is a `Transformer`.
///
template <int N, typename EstimatorTupleT>
class TransformerChainElement<
    N,
    EstimatorTupleT,
    typename std::enable_if<N == std::tuple_size<EstimatorTupleT>::value - 1>::type,
    typename std::enable_if<IsTransformerEstimator<typename std::tuple_element<N, EstimatorTupleT>::type>::value>::type
> {
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using ThisEstimatorChainElement         = EstimatorChainElement<N, EstimatorTupleT>;
    using ThisEstimator                     = typename std::tuple_element<N, EstimatorTupleT>::type;

public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TransformerChainElement(ThisEstimatorChainElement &chain) :
        _pTransformer(chain.move_transformer()) {
    }

    TransformerChainElement(Archive &ar) :
        _pTransformer(std::make_unique<typename ThisEstimator::TransformerType>(ar)) {
    }

    void save(Archive &ar) const {
        _pTransformer->save(ar);
    }

    template <typename InputT, typename CallbackT>
    void execute(InputT const &input, CallbackT const &callback) {
        _pTransformer->execute(input, callback);
    }

    template <typename CallbackT>
    void flush(CallbackT const &callback) {
        _pTransformer->flush(callback);
    }

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using TransformerUniquePtr              = typename ThisEstimator::TransformerUniquePtr;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    TransformerUniquePtr const              _pTransformer;
};

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerChainElement
///  \brief         Not a terminal element, not a `Transformer`.
///
template <int N, typename EstimatorTupleT>
class TransformerChainElement<
    N,
    EstimatorTupleT,
    typename std::enable_if<N != std::tuple_size<EstimatorTupleT>::value - 1>::type,
    typename std::enable_if<IsTransformerEstimator<typename std::tuple_element<N, EstimatorTupleT>::type>::value == false>::type
> :
    private TransformerChainElement<N + 1, EstimatorTupleT> {
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using ThisEstimatorChainElement         = EstimatorChainElement<N, EstimatorTupleT>;
    using NextEstimatorChainElement         = EstimatorChainElement<N + 1, EstimatorTupleT>;

    using NextTransformerChainElement       = TransformerChainElement<N + 1, EstimatorTupleT>;

public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TransformerChainElement(ThisEstimatorChainElement &chain) :
        NextTransformerChainElement(static_cast<NextEstimatorChainElement &>(chain)) {
    }

    TransformerChainElement(Archive &ar) :
        NextTransformerChainElement(ar) {
    }

    void save(Archive &ar) const {
        NextTransformerChainElement::save(ar);
    }

    template <typename InputT, typename CallbackT>
    void execute(InputT const &input, CallbackT const &callback) {
        NextTransformerChainElement::execute(input, callback);
    }

    template <typename CallbackT>
    void flush(CallbackT const &callback) {
        NextTransformerChainElement::flush(callback);
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerChainElement
///  \brief         Not a terminal element, is a `Transformer`.
///
template <int N, typename EstimatorTupleT>
class TransformerChainElement<
    N,
    EstimatorTupleT,
    typename std::enable_if<N != std::tuple_size<EstimatorTupleT>::value - 1>::type,
    typename std::enable_if<IsTransformerEstimator<typename std::tuple_element<N, EstimatorTupleT>::type>::value>::type
> :
    private TransformerChainElement<N + 1, EstimatorTupleT> {
private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using ThisEstimatorChainElement         = EstimatorChainElement<N, EstimatorTupleT>;
    using NextEstimatorChainElement         = EstimatorChainElement<N + 1, EstimatorTupleT>;
    using NextTransformerChainElement       = TransformerChainElement<N + 1, EstimatorTupleT>;

    using ThisEstimator                     = typename std::tuple_element<N, EstimatorTupleT>::type;
    using ThisTransformer                   = typename ThisEstimator::TransformerType;

public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TransformerChainElement(ThisEstimatorChainElement &chain) :
        NextTransformerChainElement(static_cast<NextEstimatorChainElement &>(chain)),
        _pTransformer(chain.move_transformer()) {
    }

    TransformerChainElement(Archive &ar) :
        NextTransformerChainElement(ar),
        _pTransformer(std::make_unique<ThisTransformer>(ar)) {
    }

    void save(Archive &ar) const {
        NextTransformerChainElement::save(ar);
        _pTransformer->save(ar);
    }

    template <typename InputT, typename CallbackT>
    void execute(InputT const &input, CallbackT const &callback) {
        NextTransformerChainElement &       next(static_cast<NextTransformerChainElement &>(*this));

        _pTransformer->execute(
            input,
            [&callback, &next](typename ThisTransformer::TransformedType output) {
                next.execute(output, callback);
            }
        );
    }

    template <typename CallbackT>
    void flush(CallbackT const &callback) {
        NextTransformerChainElement &       next(static_cast<NextTransformerChainElement &>(*this));

        _pTransformer->flush(
            [&callback, &next](typename ThisTransformer::TransformedType output) {
                next.execute(output, callback);
            }
        );

        next.flush(callback);
    }

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using TransformerUniquePtr              = typename ThisEstimator::TransformerUniquePtr;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    TransformerUniquePtr const              _pTransformer;
};

} // namespace Impl

/////////////////////////////////////////////////////////////////////////
///  \class         PipelineTraits
///  \brief         Traits common to a Pipeline of 1 or more `Estimators`.
///
template <typename... EstimatorTs>
class PipelineTraits {
private:
    // ----------------------------------------------------------------------
    // |  Private Types
    using EstimatorTuple                    = std::tuple<EstimatorTs...>;

    static_assert(Impl::ValidateEstimators<0, EstimatorTuple>::value, "Pipeline validation failed");

public:
    // ----------------------------------------------------------------------
    // |  Public Types
    using InputType                         = typename std::tuple_element<0, EstimatorTuple>::type::InputType;
    using TransformedType                   = typename EstimatorOutputType<typename std::tuple_element<std::tuple_size<EstimatorTuple>::value - 1, EstimatorTuple>::type>::type;

    using TransformerChain                  = Impl::TransformerChainElement<0, EstimatorTuple>;
    using EstimatorChain                    = Impl::EstimatorChainElement<0, EstimatorTuple>;
};

} // namespace Details
} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
