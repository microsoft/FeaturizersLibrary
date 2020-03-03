// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <unordered_map>

#include "../../Featurizer.h"
#include "Details/EstimatorTraits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

/////////////////////////////////////////////////////////////////////////
///  \class         GrainEstimatorAnnotation
///  \brief         Per-grain annotation information.
///
template <typename GrainT>
class GrainEstimatorAnnotation : public Annotation {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using AnnotationMap =
        std::unordered_map<
            GrainT,
            AnnotationPtr,
            std::hash<GrainT>,
            typename Traits<GrainT>::key_equal
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    AnnotationMap const                     Annotations;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    GrainEstimatorAnnotation(AnnotationMap annotations);
    ~GrainEstimatorAnnotation(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(GrainEstimatorAnnotation);
};

/////////////////////////////////////////////////////////////////////////
///  \class         GrainEstimatorTraits
///  \brief         Traits common to all types of `Estimators` when used within
///                 a `GrainEstimator`.
///
template <typename GrainT, typename EstimatorT>
struct GrainEstimatorTraits {
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = std::tuple<GrainT, typename EstimatorT::InputType>;
    using TransformedType                   = std::tuple<GrainT, typename Details::EstimatorOutputType<EstimatorT>::type>;
};

/////////////////////////////////////////////////////////////////////////
///  \class         GrainTransformer
///  \brief         A Transformer that applies a Transformer unique to the
///                 observed grain using grain-specific state.
///
template <typename GrainT, typename EstimatorT>
class GrainTransformer :
    public Transformer<
        typename GrainEstimatorTraits<GrainT, EstimatorT>::InputType,
        typename GrainEstimatorTraits<GrainT, EstimatorT>::TransformedType
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TheseGrainEstimatorTraits         = GrainEstimatorTraits<GrainT, EstimatorT>;

    using BaseType =
        Transformer<
            typename TheseGrainEstimatorTraits::InputType,
            typename TheseGrainEstimatorTraits::TransformedType
        >;

    using GrainTransformerType =
        Transformer<
            typename EstimatorT::InputType,
            typename EstimatorT::TransformedType
        >;

    using GrainTransformerTypeUniquePtr     = std::unique_ptr<GrainTransformerType>;
    using TransformerMap                    = std::map<GrainT, GrainTransformerTypeUniquePtr>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    GrainTransformer(TransformerMap transformers);
    GrainTransformer(Archive &ar);

    ~GrainTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(GrainTransformer);

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    TransformerMap                          _transformers;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        GrainT const &                      grain(std::get<0>(input));
        GrainTransformerType &              transformer(
            [this, &grain](void) -> GrainTransformerType & {

                typename TransformerMap::iterator const                     iter(_transformers.find(grain));

                if(iter == _transformers.end())
                    throw std::runtime_error("Grain not found");

                // TODO: Add support for a "default transformer" that (if provided during construction)
                //       is cloned when a grain isn't found.

                assert(iter->second);
                return *iter->second;
            }()
        );

        typename EstimatorT::InputType const &          grainInput(std::get<1>(input));

        transformer.execute(
            grainInput,
            [&callback, &grain](typename EstimatorT::TransformedType output) {
                callback(std::make_tuple(grain, std::move(output)));
            }
        );
    }

    // MSVC has problems when the declaration and definition are separated
    void flush_impl(typename BaseType::CallbackFunction const &callback) override {
        for(auto &kvp : _transformers) {
            kvp.second->flush(
                [&callback, &kvp](typename EstimatorT::TransformedType output) {
                    callback(std::make_tuple(kvp.first, std::move(output)));
                }
            );
        }
    }
};

namespace Impl {

/////////////////////////////////////////////////////////////////////////
///  \class         GrainEstimatorImplBase
///  \brief         Functionality common to GrainEstimators based on
///                 FitEstimator or TransformerEstimator objects.
///
template <typename BaseT, typename GrainT, typename EstimatorT, size_t MaxNumTrainingItemsV>
class GrainEstimatorImplBase : public BaseT {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using GrainType                         = GrainT;

    using TheseGrainEstimatorTraits         = GrainEstimatorTraits<GrainT, EstimatorT>;

    using InputType                         = typename TheseGrainEstimatorTraits::InputType;
    using TransformedType                   = typename TheseGrainEstimatorTraits::TransformedType;

    using CreateEstimatorFunc               = std::function<EstimatorT (AnnotationMapsPtr)>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    GrainEstimatorImplBase(char const *name, AnnotationMapsPtr pAllColumnAnnotations);
    GrainEstimatorImplBase(char const *name, AnnotationMapsPtr pAllColumnAnnotations, CreateEstimatorFunc createFunc);

    ~GrainEstimatorImplBase(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(GrainEstimatorImplBase);

protected:
    // ----------------------------------------------------------------------
    // |
    // |  Protected Types
    // |
    // ----------------------------------------------------------------------
    // using GrainEstimatorType = Estimator;

    // using GrainEstimatorTypeUniquePtr       = std::unique_ptr<GrainEstimatorType>;
    using EstimatorMap                      = std::map<GrainT, EstimatorT>;

    // ----------------------------------------------------------------------
    // |
    // |  Protected Data
    // |
    // ----------------------------------------------------------------------
    EstimatorMap                            _estimators;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------

    // Maintain the smart pointer to this object so that we can provide it when
    // invoking _createFunc.
    AnnotationMapsPtr const                 _pAllColumnAnnotations;
    CreateEstimatorFunc const               _createFunc;

    size_t                                  _cRemainingTrainingItems;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;
    FitResult fit_impl(InputType const *pItems, size_t cItems) override;
    void complete_training_impl(void) override;
};

/////////////////////////////////////////////////////////////////////////
///  \class         GrainEstimatorImpl
///  \brief         Baseline template for implementations specialized below.
///
template <typename GrainT, typename EstimatorT, size_t MaxNumTrainingItemsV, typename EnableIfT=void>
class GrainEstimatorImpl;

/////////////////////////////////////////////////////////////////////////
///  \class         GrainEstimatorImpl
///  \brief         Implementation for a GrainEstimator when the underlying
///                 Estimator is a FitEstimator.
///
template <typename GrainT, typename EstimatorT, size_t MaxNumTrainingItemsV>
class GrainEstimatorImpl<
    GrainT,
    EstimatorT,
    MaxNumTrainingItemsV,
    typename std::enable_if<Details::IsTransformerEstimator<EstimatorT>::value == false>::type
> :
    public Impl::GrainEstimatorImplBase<
        FitEstimator<typename GrainEstimatorTraits<GrainT, EstimatorT>::InputType>,
        GrainT,
        EstimatorT,
        MaxNumTrainingItemsV
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TheseGrainTraits                  = GrainEstimatorTraits<GrainT, EstimatorT>;

    using BaseType =
        Impl::GrainEstimatorImplBase<
            FitEstimator<typename TheseGrainTraits::InputType>,
            GrainT,
            EstimatorT,
            MaxNumTrainingItemsV
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    using BaseType::BaseType;

    ~GrainEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(GrainEstimatorImpl);
};

/////////////////////////////////////////////////////////////////////////
///  \class         GrainEstimatorImpl
///  \brief         Implementation for a GrainEstimator when the underlying
///                 Estimator is a TransformerEstimator.
///
template <typename GrainT, typename EstimatorT, size_t MaxNumTrainingItemsV>
class GrainEstimatorImpl<
    GrainT,
    EstimatorT,
    MaxNumTrainingItemsV,
    typename std::enable_if<Details::IsTransformerEstimator<EstimatorT>::value>::type
> :
    public Impl::GrainEstimatorImplBase<
        TransformerEstimator<
            typename GrainEstimatorTraits<GrainT, EstimatorT>::InputType,
            typename GrainEstimatorTraits<GrainT, EstimatorT>::TransformedType
        >,
        GrainT,
        EstimatorT,
        MaxNumTrainingItemsV
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TheseGrainTraits                  = GrainEstimatorTraits<GrainT, EstimatorT>;

    using BaseType =
        Impl::GrainEstimatorImplBase<
            TransformerEstimator<
                typename TheseGrainTraits::InputType,
                typename TheseGrainTraits::TransformedType
            >,
            GrainT,
            EstimatorT,
            MaxNumTrainingItemsV
        >;

    using TransformerType                   = GrainTransformer<GrainT, EstimatorT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    using BaseType::BaseType;

    ~GrainEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(GrainEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        typename TransformerType::TransformerMap        transformers;

        for(auto & kvp: this->_estimators)
            transformers.emplace(std::make_pair(kvp.first, kvp.second.create_transformer()));

        return typename BaseType::TransformerUniquePtr(new TransformerType(std::move(transformers)));
    }
};

} // namespace Impl

/////////////////////////////////////////////////////////////////////////
///  \typedef       GrainEstimatorImpl
///  \brief         Estimator that trains and transforms based on a grain
///                 (also known as a unique key). With this class,
///                 Estimators and Transformers can be written without
///                 being aware of grains, and then "wrapped" by this object
///                 in those scenarios where grain-specific state is required.
///
///                 Note that this using statement immediately forwards to
///                 a second implementation, as it isn't possible in C++
///                 to have a template that supports both default template
///                 values (this typedef) and partial template specialization
///                 (the forwarding class).
///
template <
    typename GrainT,
    typename EstimatorT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using GrainEstimatorImpl                    = Impl::GrainEstimatorImpl<GrainT, EstimatorT, MaxNumTrainingItemsV>;

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
// |  GrainEstimatorAnnotation
// |
// ----------------------------------------------------------------------
template <typename GrainT>
GrainEstimatorAnnotation<GrainT>::GrainEstimatorAnnotation(AnnotationMap annotations) :
    Annotations(
        std::move(
            [&annotations](void) -> AnnotationMap & {
                if(annotations.empty())
                    throw std::invalid_argument("annotations");

                return annotations;
            }()
        )
    ) {
}

// ----------------------------------------------------------------------
// |
// |  GrainTransformer
// |
// ----------------------------------------------------------------------
template <typename GrainT, typename EstimatorT>
GrainTransformer<GrainT, EstimatorT>::GrainTransformer(TransformerMap transformers) :
    _transformers(
        std::move(
            [&transformers](void) -> TransformerMap & {
                if(transformers.empty())
                    throw std::invalid_argument("transformers");

                return transformers;
            }()
        )
    ) {
}

template <typename GrainT, typename EstimatorT>
GrainTransformer<GrainT, EstimatorT>::GrainTransformer(Archive &ar) :
    GrainTransformer(
        [&ar](void) -> TransformerMap {
            std::uint64_t                   cElements(Traits<std::uint64_t>::deserialize(ar));

            if(cElements == 0)
                throw std::runtime_error("Invalid elements");

            TransformerMap                  transformers;

            while(cElements--) {
                GrainT                                  grain(Traits<GrainT>::deserialize(ar));
                GrainTransformerTypeUniquePtr           pTransformer(new typename EstimatorT::TransformerType(ar));

                std::pair<typename TransformerMap::iterator, bool> const    result(transformers.emplace(std::make_pair(std::move(grain), std::move(pTransformer))));

                if(result.first == transformers.end() || result.second == false)
                    throw std::runtime_error("Invalid insertion");
            }

            return transformers;
        }()
    ) {
}

template <typename GrainT, typename EstimatorT>
void GrainTransformer<GrainT, EstimatorT>::save(Archive &ar) const /*override*/ {
    Traits<std::uint64_t>::serialize(ar, _transformers.size());

    for(auto const &kvp: _transformers) {
        Traits<GrainT>::serialize(ar, kvp.first);
        kvp.second->save(ar);
    }
}

// ----------------------------------------------------------------------
// |
// |  Impl::GrainEstimatorImplBase
// |
// ----------------------------------------------------------------------
template <typename BaseT, typename GrainT, typename EstimatorT, size_t MaxNumTrainingItemsV>
Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, MaxNumTrainingItemsV>::GrainEstimatorImplBase(char const *name, AnnotationMapsPtr pAllColumnAnnotations) :
    GrainEstimatorImplBase(
        name,
        std::move(pAllColumnAnnotations),
        [](AnnotationMapsPtr pAllColumnAnnotationsParam) {
            return EstimatorT(std::move(pAllColumnAnnotationsParam));
        }
    ) {
}

template <typename BaseT, typename GrainT, typename EstimatorT, size_t MaxNumTrainingItemsV>
Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, MaxNumTrainingItemsV>::GrainEstimatorImplBase(char const *name, AnnotationMapsPtr pAllColumnAnnotations, CreateEstimatorFunc createFunc) :
    BaseT(name, pAllColumnAnnotations),
    _pAllColumnAnnotations(pAllColumnAnnotations),
    _createFunc(
        std::move(
            [&createFunc](void) -> CreateEstimatorFunc const & {
                if(!createFunc)
                    throw std::invalid_argument("createFunc");

                return createFunc;
            }()
        )
    ),
    _cRemainingTrainingItems(MaxNumTrainingItemsV) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename BaseT, typename GrainT, typename EstimatorT, size_t MaxNumTrainingItemsV>
bool Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return _cRemainingTrainingItems != 0;
}

template <typename BaseT, typename GrainT, typename EstimatorT, size_t MaxNumTrainingItemsV>
FitResult Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, MaxNumTrainingItemsV>::fit_impl(InputType const *pItems, size_t cItems) /*override*/ {
    size_t const                            cRemainingItems(std::min(_cRemainingTrainingItems, cItems));
    InputType const * const                 pEndItems(pItems + cRemainingItems);

    while(pItems != pEndItems) {
        EstimatorT &                        estimator(
            [this, pItems](void) -> EstimatorT & {
                GrainT const &                          grain(std::get<0>(*pItems));
                typename EstimatorMap::iterator const   iter(_estimators.find(grain));

                if(iter != _estimators.end())
                    return iter->second;

                std::pair<typename EstimatorMap::iterator, bool> const      result(_estimators.emplace(std::make_pair(grain, _createFunc(_pAllColumnAnnotations))));

                result.first->second.begin_training();

                return result.first->second;
            }()
        );

        if(estimator.get_state() == TrainingState::Training) {
            typename EstimatorT::InputType const &      input(std::get<1>(*pItems));
            FitResult const                             result(estimator.fit(input));

            // Don't allow resetting, as we don't have a good way to reset all of the estimators associated with
            // each of the unique grains.

            if(result == FitResult::Reset)
                throw std::runtime_error("Resetting estimators can not be used as GrainEstimators");
        }

        ++pItems;
    }

    _cRemainingTrainingItems -= cRemainingItems;
    return _cRemainingTrainingItems ? FitResult::Continue : FitResult::Complete;
}

template <typename BaseT, typename GrainT, typename EstimatorT, size_t MaxNumTrainingItemsV>
void Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
    // ----------------------------------------------------------------------
    using ThisAnnotation                    = GrainEstimatorAnnotation<GrainT>;
    using ThisAnnotationMap                 = typename ThisAnnotation::AnnotationMap;
    using Sizes                             = std::vector<size_t>;
    // ----------------------------------------------------------------------

    // This code is admittedly strange. We don't know if the per-grain `Estimator` creates `Annotations`.
    // We are making the assumption that `Annotations` will only be created when `complete_training` is called
    // (I believe that that is a reasonable assumption).
    //
    // To check if the `Estimator` has created an `Annotation`, we will capture the size of the `AnnotationMaps`
    // before `complete_training` and after `complete_training` is invoked. Changes in size indicate that an
    // `Annotation` has been created (note that this isn't safe if multiple threads are simultaneously
    // modifying the `AnnotationMap` (but that problem will go away when we switch to contexts)).
    //
    // If a new `Annotation` is detected, we will remove it from the global `AnnotationMaps` and add it to our
    // internal `AnnotationMap`. Once complete, we will check for the presence of added `Annotations` and
    // create a grain-based `Annotation` that contains all the grain-specific `Annotations`.
    //
    // TODO: All of this code needs to change when we switch from using `AnnotationMaps` in favor of graph
    //       contexts.

    Sizes const                             sizes(
        [this](void) {
            Sizes                           result;

            result.reserve(_pAllColumnAnnotations->size());

            for(AnnotationMap const &map: *_pAllColumnAnnotations)
                result.emplace_back(map.size());

            return result;
        }()
    );

    ThisAnnotationMap                       newAnnotations;
    size_t                                  colIndex(0);

    for(auto & kvp : _estimators) {
        kvp.second.complete_training();

        bool                                addedNewAnnotation(false);

        for(size_t i = 0; i < _pAllColumnAnnotations->size(); ++i) {
            assert(_pAllColumnAnnotations->size() == sizes.size());
            assert(i < _pAllColumnAnnotations->size());

            AnnotationMap &                 map((*_pAllColumnAnnotations)[i]);
            size_t const &                  size(sizes[i]);

            if(map.size() != size) {
                assert(map.size() == size + 1);

                if(addedNewAnnotation)
                    throw std::runtime_error("Unexpected AnnotationMap insertion (duplicate)");

                if(newAnnotations.empty() == false && colIndex != i)
                    throw std::runtime_error("Unexpected AnnotationMap insertion (different column)");

                colIndex = i;

                // If here, something was added. We expect that Annotation to be associated with the grain-based Estimator.
                AnnotationMap::iterator     iter(map.find(kvp.second.Name));

                if(iter == map.end())
                    throw std::runtime_error("Unexpected AnnotationMap insertion (different Estimator)");

                // There should be only one entry
                if(iter->second.size() != 1)
                    throw std::runtime_error("Unexpected AnnotationMap size");

                // Insert this value into our working map
                std::pair<typename ThisAnnotationMap::iterator, bool> const     result(newAnnotations.emplace(std::make_pair(kvp.first, std::move(iter->second[0]))));

                if(result.first == newAnnotations.end() || result.second == false)
                    throw std::runtime_error("Invalid AnnotationMap insertion");

                addedNewAnnotation = true;

                // Remove the value from the global map (which should restore the original sizes)
                map.erase(iter);
            }
        }
    }

    if(newAnnotations.empty() == false)
        BaseT::add_annotation(std::make_shared<ThisAnnotation>(std::move(newAnnotations)), std::move(colIndex));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
