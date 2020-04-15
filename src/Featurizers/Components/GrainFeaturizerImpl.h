// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <unordered_map>

#include "../../Archive.h"
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
        std::map<
            GrainT,
            AnnotationPtr
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
///  \class         StandardGrainImplPolicy
///  \brief         BugBug
///
template <typename GrainT, typename EstimatorT>
struct StandardGrainImplPolicy {
    // ----------------------------------------------------------------------
    // |  Public Types
    static_assert(std::is_reference<GrainT>::value == false, "'GrainT' must not be a reference");
    static_assert(std::is_reference<typename EstimatorT::InputType>::value == false, "'EstimatorT::InputType' must not be a reference");

    using EstimatorInputType                = typename EstimatorT::InputType;
    using EstimatorTransformedType          = typename Details::EstimatorOutputType<EstimatorT>::type;

    using InputType                         = std::tuple<GrainT const &, EstimatorInputType const &>;
    using TransformedType                   = std::tuple<GrainT const &, EstimatorTransformedType>;

    // ----------------------------------------------------------------------
    // |  Public Methods
    template <typename TransformerT, typename CallbackT>
    static void execute(GrainT const &grain, TransformerT &transformer, EstimatorInputType const &input, CallbackT const &callback);

    template <typename TransformerMapT, typename CallbackT>
    static void flush(TransformerMapT const &transformers, CallbackT const &callback);
};

/////////////////////////////////////////////////////////////////////////
///  \class         GrainTransformer
///  \brief         A Transformer that applies a Transformer unique to the
///                 observed grain using grain-specific state.
///
template <
    typename GrainT,
    typename EstimatorT,
    // BugBug: Explain policy
    template <typename, typename> class GrainImplPolicyT
>
class GrainTransformer :
    public Transformer<
        typename GrainImplPolicyT<GrainT, EstimatorT>::InputType,
        typename GrainImplPolicyT<GrainT, EstimatorT>::TransformedType
    >,
    private GrainImplPolicyT<GrainT, EstimatorT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using GrainImplPolicy                   = GrainImplPolicyT<GrainT, EstimatorT>;

    using typename GrainImplPolicy::InputType;
    using typename GrainImplPolicy::TransformedType;

    using BaseType =
        Transformer<
            typename GrainImplPolicy::InputType,
            typename GrainImplPolicy::TransformedType
        >;

    using GrainTransformerType =
        Transformer<
            typename EstimatorT::InputType,
            typename EstimatorT::TransformedType
        >;

    using GrainTransformerTypeUniquePtr     = std::unique_ptr<GrainTransformerType>;
    using TransformerMap                    = std::map<GrainT, GrainTransformerTypeUniquePtr>;

    using CreateTransformerFunc             = std::function<GrainTransformerTypeUniquePtr (void)>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------

    // BugBug: Pass grainimpl featurizers

    // The `createFunc` is invoked (if available) when a grain is encountered during
    // prediction time that wasn't seen during training.
    GrainTransformer(TransformerMap transformers, CreateTransformerFunc createFunc=CreateTransformerFunc());
    GrainTransformer(CreateTransformerFunc createFunc);

    GrainTransformer(Archive &ar);

    GrainTransformer(GrainTransformer && other);
    GrainTransformer(GrainTransformer const &) = delete;

    ~GrainTransformer(void) override = default;

    GrainTransformer & operator =(GrainTransformer const &) = delete;
    GrainTransformer & operator =(GrainTransformer &&) = delete;

    void save(Archive &ar) const override;

    using BaseType::execute;
    using BaseType::flush;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    struct UseDeserializationCtorTag {};

    using GrainImplPolicy                   = GrainImplPolicyT<GrainT, EstimatorT>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    bool const                              _hadTransformersWhenCreated;

    // Archive used when deserializing an object that was serialized with a createFunc.
    // This archive will be used by a special createFunc that creates Transformers
    // based on the data available in an archive.
    Archive const                           _createFuncArchive;
    CreateTransformerFunc const             _createFunc;

    TransformerMap                          _transformers;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    GrainTransformer(TransformerMap transformers, Archive createFuncArchive, UseDeserializationCtorTag);

    // MSVC has problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        GrainT const &                      grain(std::get<0>(input));
        GrainTransformerType &              transformer(
            [this, &grain](void) -> GrainTransformerType & {

                typename TransformerMap::iterator const                     iter(
                    [this, &grain]() {
                        typename TransformerMap::iterator const             i(_transformers.find(grain));

                        if(i != _transformers.end())
                            return i;

                        if(!_createFunc)
                            throw std::runtime_error("Grain not found");

                        return _transformers.emplace(grain, _createFunc()).first;
                    }()
                );

                assert(iter->second);
                return *iter->second;
            }()
        );

        typename EstimatorT::InputType const &          grainInput(std::get<1>(input));

        static_cast<GrainImplPolicy &>(*this).execute(grain, transformer, grainInput, callback);
    }

    // MSVC has problems when the declaration and definition are separated
    void flush_impl(typename BaseType::CallbackFunction const &callback) override {
        static_cast<GrainImplPolicy &>(*this).flush(_transformers, callback);
    }

    GrainTransformerTypeUniquePtr CreateTransformerFromArchive(void) const;
};

namespace Impl {

/////////////////////////////////////////////////////////////////////////
///  \class         GrainEstimatorImplBase
///  \brief         Functionality common to GrainEstimators based on
///                 FitEstimator or TransformerEstimator objects.
///
template <
    typename BaseT,
    typename GrainT,
    typename EstimatorT,
    template <typename, typename> class GrainImplPolicyT,
    size_t MaxNumTrainingItemsV
>
class GrainEstimatorImplBase : public BaseT {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using GrainType                         = GrainT;

    using GrainImplPolicy                   = GrainImplPolicyT<GrainType, EstimatorT>;

    using InputType                         = typename GrainImplPolicy::InputType;
    using TransformedType                   = typename GrainImplPolicy::TransformedType;

    using GrainEstimatorAnnotation          = Microsoft::Featurizer::Featurizers::Components::GrainEstimatorAnnotation<GrainType>;
    using CreateEstimatorFunc               = std::function<EstimatorT (AnnotationMapsPtr)>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    GrainEstimatorImplBase(AnnotationMapsPtr pAllColumnAnnotations, bool isInferenceOnlyEstimator);
    GrainEstimatorImplBase(AnnotationMapsPtr pAllColumnAnnotations, CreateEstimatorFunc createFunc, bool isInferenceOnlyEstimator);

    ~GrainEstimatorImplBase(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(GrainEstimatorImplBase);

    static GrainEstimatorAnnotation const & get_annotation(AnnotationMaps const &columnAnnotations, size_t colIndex, char const *name);
    static GrainEstimatorAnnotation const * get_annotation_nothrow(AnnotationMaps const &columnAnnotations, size_t colIndex, char const *name);

protected:
    // ----------------------------------------------------------------------
    // |
    // |  Protected Types
    // |
    // ----------------------------------------------------------------------
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
    bool const                              _isInferenceOnlyEstimator;

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
template <
    typename GrainT,
    typename EstimatorT,
    template <typename, typename> class GrainImplPolicyT,
    size_t MaxNumTrainingItemsV,
    typename EnableIfT=void
>
class GrainEstimatorImpl;

/////////////////////////////////////////////////////////////////////////
///  \class         GrainEstimatorImpl
///  \brief         Implementation for a GrainEstimator when the underlying
///                 Estimator is a FitEstimator.
///
template <
    typename GrainT,
    typename EstimatorT,
    template <typename, typename> class GrainImplPolicyT,
    size_t MaxNumTrainingItemsV
>
class GrainEstimatorImpl<
    GrainT,
    EstimatorT,
    GrainImplPolicyT,
    MaxNumTrainingItemsV,
    typename std::enable_if<Details::IsTransformerEstimator<EstimatorT>::value == false>::type
> :
    public Impl::GrainEstimatorImplBase<
        FitEstimator<typename GrainImplPolicyT<GrainT, EstimatorT>::InputType>,
        GrainT,
        EstimatorT,
        GrainImplPolicyT,
        MaxNumTrainingItemsV
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using GrainImplPolicy                   = GrainImplPolicyT<GrainT, EstimatorT>;

    using BaseType =
        Impl::GrainEstimatorImplBase<
            FitEstimator<typename GrainImplPolicy::InputType>,
            GrainT,
            EstimatorT,
            GrainImplPolicyT,
            MaxNumTrainingItemsV
        >;

    using CreateEstimatorFunc               = typename BaseType::CreateEstimatorFunc;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    GrainEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations) :
        BaseType(std::move(pAllColumnAnnotations), false) {
    }

    GrainEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, CreateEstimatorFunc createFunc) :
        BaseType(std::move(pAllColumnAnnotations), std::move(createFunc), false) {
    }

    ~GrainEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(GrainEstimatorImpl);
};

/////////////////////////////////////////////////////////////////////////
///  \class         GrainEstimatorImpl
///  \brief         Implementation for a GrainEstimator when the underlying
///                 Estimator is a TransformerEstimator.
///
template <
    typename GrainT,
    typename EstimatorT,
    template <typename, typename> class GrainImplPolicyT,
    size_t MaxNumTrainingItemsV
>
class GrainEstimatorImpl<
    GrainT,
    EstimatorT,
    GrainImplPolicyT,
    MaxNumTrainingItemsV,
    typename std::enable_if<Details::IsTransformerEstimator<EstimatorT>::value>::type
> :
    public Impl::GrainEstimatorImplBase<
        TransformerEstimator<
            typename GrainImplPolicyT<GrainT, EstimatorT>::InputType,
            typename GrainImplPolicyT<GrainT, EstimatorT>::TransformedType
        >,
        GrainT,
        EstimatorT,
        GrainImplPolicyT,
        MaxNumTrainingItemsV
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using GrainImplPolicy                   = GrainImplPolicyT<GrainT, EstimatorT>;

    using BaseType =
        Impl::GrainEstimatorImplBase<
            TransformerEstimator<
                typename GrainImplPolicy::InputType,
                typename GrainImplPolicy::TransformedType
            >,
            GrainT,
            EstimatorT,
            GrainImplPolicyT,
            MaxNumTrainingItemsV
        >;

    using TransformerType                   = GrainTransformer<GrainT, EstimatorT, GrainImplPolicyT>;

    using CreateEstimatorFunc               = typename BaseType::CreateEstimatorFunc;
    using CreateTransformerFunc             = typename TransformerType::CreateTransformerFunc;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    GrainEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations) :
        BaseType(std::move(pAllColumnAnnotations), false) {
    }

    GrainEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, CreateTransformerFunc createTransformerFunc, bool isInferenceOnlyEstimator=false) :
        BaseType(std::move(pAllColumnAnnotations), isInferenceOnlyEstimator),
        _createTransformerFunc(
            std::move(
                [&createTransformerFunc](void) -> CreateTransformerFunc & {
                    if(!createTransformerFunc)
                        throw std::invalid_argument("createTransformerFunc");

                    return createTransformerFunc;
                }()
            )
        ) {
    }

    GrainEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, CreateEstimatorFunc createEstimatorFunc) :
        BaseType(std::move(pAllColumnAnnotations), std::move(createEstimatorFunc), false) {
    }

    GrainEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, CreateEstimatorFunc createEstimatorFunc, CreateTransformerFunc createTransformerFunc, bool isInferenceOnlyEstimator=false) :
        BaseType(std::move(pAllColumnAnnotations), std::move(createEstimatorFunc), isInferenceOnlyEstimator),
        _createTransformerFunc(
            std::move(
                [&createTransformerFunc](void) -> CreateTransformerFunc & {
                    if(!createTransformerFunc)
                        throw std::invalid_argument("createTransformerFunc");

                    return createTransformerFunc;
                }()
            )
        ) {
    }

    ~GrainEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(GrainEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    CreateTransformerFunc const             _createTransformerFunc;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        typename TransformerType::TransformerMap        transformers;

        for(auto & kvp: this->_estimators)
            transformers.emplace(std::make_pair(kvp.first, kvp.second.create_transformer()));

        if(transformers.empty()) {
            if(!_createTransformerFunc)
                throw std::runtime_error("`_createTransformerFunc` must be provided when no grains were encountered during training");

            return typename BaseType::TransformerUniquePtr(new TransformerType(_createTransformerFunc));
        }

        if(_createTransformerFunc)
            return typename BaseType::TransformerUniquePtr(new TransformerType(std::move(transformers), _createTransformerFunc));

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
///                 Note that the name of this estimator will be:
///                     "Grain" + EstimatorT::Name
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
    // BugBug: Better description
    // The policy type is used to determine how the results of flush should be interpreted.
    // In some cases, the output of flush must contain additional information that is used when
    // returning output to the framework.
    template <typename, typename> class GrainImplPolicyT=StandardGrainImplPolicy,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using GrainEstimatorImpl                    = Impl::GrainEstimatorImpl<GrainT, EstimatorT, GrainImplPolicyT, MaxNumTrainingItemsV>;

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
// |  StandardGrainImplPolicy
// |
// ----------------------------------------------------------------------
template <typename GrainT, typename EstimatorT>
template <typename TransformerT, typename CallbackT>
// static
void StandardGrainImplPolicy<GrainT, EstimatorT>::execute(GrainT const &grain, TransformerT &transformer, EstimatorInputType const &input, CallbackT const &callback) {
    transformer.execute(
        input,
        [&callback, &grain](EstimatorTransformedType output) {
            callback(TransformedType(grain, std::move(output)));
        }
    );
}

template <typename GrainT, typename EstimatorT>
template <typename TransformerMapT, typename CallbackT>
// static
void StandardGrainImplPolicy<GrainT, EstimatorT>::flush(TransformerMapT const &transformers, CallbackT const &callback) {
    for(auto &kvp : transformers) {
        kvp.second->flush(
            [&callback, &kvp](EstimatorTransformedType output) {
                callback(TransformedType(kvp.first, std::move(output)));
            }
        );
    }
}

// ----------------------------------------------------------------------
// |
// |  GrainTransformer
// |
// ----------------------------------------------------------------------
template <typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT>
GrainTransformer<GrainT, EstimatorT, GrainImplPolicyT>::GrainTransformer(CreateTransformerFunc createFunc) :
    _hadTransformersWhenCreated(false),
    _createFunc(
        std::move(
            [&createFunc]() -> CreateTransformerFunc & {
                if(!createFunc)
                    throw std::invalid_argument("`createFunc` is empty");

                return createFunc;
            }()
        )
    ) {
}

template <typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT>
GrainTransformer<GrainT, EstimatorT, GrainImplPolicyT>::GrainTransformer(TransformerMap transformers, CreateTransformerFunc createFunc/*=CreateTransformerFunc()*/) :
    _hadTransformersWhenCreated(true),
    _createFunc(std::move(createFunc)),
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

template <typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT>
GrainTransformer<GrainT, EstimatorT, GrainImplPolicyT>::GrainTransformer(Archive &ar) :
    GrainTransformer(
        [&ar](void) -> GrainTransformer {
            std::uint64_t                   cElements(Traits<std::uint64_t>::deserialize(ar));
            TransformerMap                  transformers;

            while(cElements--) {
                GrainT                                  grain(Traits<GrainT>::deserialize(ar));
                GrainTransformerTypeUniquePtr           pTransformer(new typename EstimatorT::TransformerType(ar));

                std::pair<typename TransformerMap::iterator, bool> const    result(transformers.emplace(std::make_pair(std::move(grain), std::move(pTransformer))));

                if(result.first == transformers.end() || result.second == false)
                    throw std::runtime_error("Invalid insertion");
            }

            bool                            hasCreateFunc(Traits<bool>::deserialize(ar));

            if(hasCreateFunc == false) {
                if(transformers.empty())
                    throw std::runtime_error("A `createFunc` must be provided to the serializing object when there aren't any transformers in the transformer map");

                return GrainTransformer(std::move(transformers));
            }

            return GrainTransformer(std::move(transformers), ar.clone(), UseDeserializationCtorTag());
        }()
    )
{}

template <typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT>
GrainTransformer<GrainT, EstimatorT, GrainImplPolicyT>::GrainTransformer(GrainTransformer && other) :
    _hadTransformersWhenCreated(std::move(make_mutable(other._hadTransformersWhenCreated))),
    _createFuncArchive(std::move(make_mutable(other._createFuncArchive))),
    _createFunc(
        [this](void) -> CreateTransformerFunc {
            if(_createFuncArchive.Mode == Archive::ModeValue::Serializing)
                return CreateTransformerFunc();

            return [this](void) { return CreateTransformerFromArchive(); };
        }()
    ),
    _transformers(std::move(make_mutable(other._transformers)))
{}

template <typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT>
void GrainTransformer<GrainT, EstimatorT, GrainImplPolicyT>::save(Archive &ar) const /*override*/ {
    if(_hadTransformersWhenCreated) {
        Traits<std::uint64_t>::serialize(ar, _transformers.size());

        for(auto const &kvp: _transformers) {
            Traits<GrainT>::serialize(ar, kvp.first);
            kvp.second->save(ar);
        }
    }
    else
        Traits<std::uint64_t>::serialize(ar, 0);

    // If there is a _createFunc, create a Transformer based on that func and then
    // serialize it. This will serve as a template for the function created when
    // deserializing the transformer.
    Traits<bool>::serialize(ar, static_cast<bool>(_createFunc));

    if(_createFunc)
        _createFunc()->save(ar);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT>
GrainTransformer<GrainT, EstimatorT, GrainImplPolicyT>::GrainTransformer(TransformerMap transformers, Archive createFuncArchive, UseDeserializationCtorTag) :
    _hadTransformersWhenCreated(transformers.empty()),
    _createFuncArchive(
        std::move(
            [&createFuncArchive](void) -> Archive & {
                if(createFuncArchive.Mode != Archive::ModeValue::Deserializing)
                    throw std::invalid_argument("Invalid serialization mode");

                return createFuncArchive;
            }()
        )
    ),
    _createFunc(
        [this](void) { return CreateTransformerFromArchive(); }
    ),
    _transformers(std::move(transformers))
{}

template <typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT>
typename GrainTransformer<GrainT, EstimatorT, GrainImplPolicyT>::GrainTransformerTypeUniquePtr
GrainTransformer<GrainT, EstimatorT, GrainImplPolicyT>::CreateTransformerFromArchive(void) const {
    assert(_createFuncArchive.Mode == Archive::ModeValue::Deserializing);

    // Clone the archive before using it so that it can be invoked multiple times.
    Archive                                 ar(_createFuncArchive.clone());

    return GrainTransformerTypeUniquePtr(new typename EstimatorT::TransformerType(ar));
}

// ----------------------------------------------------------------------
// |
// |  Impl::GrainEstimatorImplBase
// |
// ----------------------------------------------------------------------
template <typename BaseT, typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT, size_t MaxNumTrainingItemsV>
Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, GrainImplPolicyT, MaxNumTrainingItemsV>::GrainEstimatorImplBase(AnnotationMapsPtr pAllColumnAnnotations, bool isInferenceOnlyEstimator) :
    GrainEstimatorImplBase(
        std::move(pAllColumnAnnotations),
        [](AnnotationMapsPtr pAllColumnAnnotationsParam) {
            return EstimatorT(std::move(pAllColumnAnnotationsParam));
        },
        std::move(isInferenceOnlyEstimator)
    ) {
}

template <typename BaseT, typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT, size_t MaxNumTrainingItemsV>
Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, GrainImplPolicyT, MaxNumTrainingItemsV>::GrainEstimatorImplBase(AnnotationMapsPtr pAllColumnAnnotations, CreateEstimatorFunc createFunc, bool isInferenceOnlyEstimator) :
    BaseT(
        [pAllColumnAnnotations, &createFunc](void) -> std::string {
            if(!createFunc)
                throw std::invalid_argument("createFunc");

            // Create the name of the GrainEstimator as "Grain<EstimatorName>". This is slightly more
            // complicated than what would normally be expected, as we have to create an instance
            // of the estimator before we can get its name.

            EstimatorT const                estimator(createFunc(std::move(pAllColumnAnnotations)));

            return std::string("Grain") + estimator.Name;
        }(),
        pAllColumnAnnotations
    ),
    _pAllColumnAnnotations(pAllColumnAnnotations),
    _createFunc(std::move(createFunc)), // Note that createFunc has been validated when creating the Estimator name in the call to BaseT's constructor above
    _isInferenceOnlyEstimator(std::move(isInferenceOnlyEstimator)),
    _cRemainingTrainingItems(MaxNumTrainingItemsV) {
}

template <typename BaseT, typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT, size_t MaxNumTrainingItemsV>
/*static*/ typename Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, GrainImplPolicyT, MaxNumTrainingItemsV>::GrainEstimatorAnnotation const &
Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, GrainImplPolicyT, MaxNumTrainingItemsV>::get_annotation(AnnotationMaps const &columnAnnotations, size_t colIndex, char const *name) {
    GrainEstimatorAnnotation const * const  ptr(get_annotation_nothrow(columnAnnotations, colIndex, name));

    if(ptr == nullptr)
        throw std::runtime_error("Annotation data was not found for this column");

    return *ptr;
}

template <typename BaseT, typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT, size_t MaxNumTrainingItemsV>
/*static*/ typename Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, GrainImplPolicyT, MaxNumTrainingItemsV>::GrainEstimatorAnnotation const *
Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, GrainImplPolicyT, MaxNumTrainingItemsV>::get_annotation_nothrow(AnnotationMaps const &columnAnnotations, size_t colIndex, char const *name) {
    return BaseT::template get_annotation_impl<GrainEstimatorAnnotation>(columnAnnotations, colIndex, name);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename BaseT, typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT, size_t MaxNumTrainingItemsV>
bool Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, GrainImplPolicyT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return _isInferenceOnlyEstimator == false && _cRemainingTrainingItems != 0;
}

template <typename BaseT, typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT, size_t MaxNumTrainingItemsV>
FitResult Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, GrainImplPolicyT, MaxNumTrainingItemsV>::fit_impl(InputType const *pItems, size_t cItems) /*override*/ {
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

template <typename BaseT, typename GrainT, typename EstimatorT, template <typename, typename> class GrainImplPolicyT, size_t MaxNumTrainingItemsV>
void Impl::GrainEstimatorImplBase<BaseT, GrainT, EstimatorT, GrainImplPolicyT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
    // ----------------------------------------------------------------------
    using GrainEstimatorAnnotationMap       = typename GrainEstimatorAnnotation::AnnotationMap;
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

    GrainEstimatorAnnotationMap             newAnnotations;
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
                std::pair<typename GrainEstimatorAnnotationMap::iterator, bool> const   result(newAnnotations.emplace(std::make_pair(kvp.first, std::move(iter->second[0]))));

                if(result.first == newAnnotations.end() || result.second == false)
                    throw std::runtime_error("Invalid AnnotationMap insertion");

                addedNewAnnotation = true;

                // Remove the value from the global map (which should restore the original sizes)
                map.erase(iter);
            }
        }
    }

    if(newAnnotations.empty() == false)
        BaseT::add_annotation(std::make_shared<GrainEstimatorAnnotation>(std::move(newAnnotations)), std::move(colIndex));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
