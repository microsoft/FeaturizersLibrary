// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../../Featurizer.h"
#include "Details/PipelineExecutionEstimatorImpl_details.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

/////////////////////////////////////////////////////////////////////////
///  \class         PipelineExecutionTransformer
///  \brief         `Transformer` associated with a `PipelineExecutionEstimatorImpl`
///                 object.
///
template <typename... EstimatorTs>
class PipelineExecutionTransformer :
    public Transformer<
        typename Details::PipelineTraits<EstimatorTs...>::InputType,
        typename Details::PipelineTraits<EstimatorTs...>::TransformedType
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using PipelineTraits                    = Details::PipelineTraits<EstimatorTs...>;

    using BaseType =
        Transformer<
            typename PipelineTraits::InputType,
            typename PipelineTraits::TransformedType
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    PipelineExecutionTransformer(typename PipelineTraits::EstimatorChain &estimatorChain);
    PipelineExecutionTransformer(Archive &ar);

    ~PipelineExecutionTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(PipelineExecutionTransformer);

    void save(Archive &ar) const override;

    using BaseType::execute;

    // MSVC has problems when the method definition is separated from the declaration
    typename BaseType::TransformedType execute(typename BaseType::InputType &input) {
        // ----------------------------------------------------------------------
        using TransformedType               = typename BaseType::TransformedType;
        // ----------------------------------------------------------------------

        // Do absolutely everything possible to avoid default construction, as we don't want
        // to burden transformed types with that concept.
        TransformedType *                   pResult(reinterpret_cast<TransformedType *>(alloca(sizeof(TransformedType))));
        size_t                              cResults(0);

        execute(
            input,
            [&pResult, &cResults](TransformedType value) {
                ++cResults;
                new (reinterpret_cast<void *>(pResult)) TransformedType(std::move(value));
            }
        );

        if(cResults != 1)
            throw std::runtime_error("This method should only be used with Transformers that generate 1 output value for each input value");

        return std::move(*pResult);
    }

    typename BaseType::TransformedType execute(typename BaseType::InputType const &input) {
        typename BaseType::InputType        temp(input);

        return execute(temp);
    }

private:
    // ----------------------------------------------------------------------
    // |  Private Types
    using TransformerChain                  = typename PipelineTraits::TransformerChain;

    // ----------------------------------------------------------------------
    // |  Private Data
    TransformerChain                        _transformerChain;

    // ----------------------------------------------------------------------
    // |  Private Methods

    // MSVC has problems when attempting to separate the definition from the declaration
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        _transformerChain.execute(input, callback);
    }

    // MSVC has problems when attempting to separate the definition from the declaration
    void flush_impl(typename BaseType::CallbackFunction const &callback) override {
        _transformerChain.flush(callback);
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         PipelineExecutionEstimatorImpl
///  \brief         Executes one or more `Estimators` in sequential
///                 order. This object is used to stich together individual
///                 `Estimators` into a larger directed acyclic graph (DAG).
///
template <typename... EstimatorTs>
class PipelineExecutionEstimatorImpl :
    public TransformerEstimator<
        typename Details::PipelineTraits<EstimatorTs...>::InputType,
        typename Details::PipelineTraits<EstimatorTs...>::TransformedType
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using PipelineTraits                    = Details::PipelineTraits<EstimatorTs...>;

    using BaseType = TransformerEstimator<
        typename PipelineTraits::InputType,
        typename PipelineTraits::TransformedType
    >;

    using TransformerType                   = PipelineExecutionTransformer<EstimatorTs...>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    PipelineExecutionEstimatorImpl(char const *name, AnnotationMapsPtr pAllColumnAnnotations);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            PipelineExecutionEstimatorImpl
    ///  \brief         This constructor should be used when one or more of
    ///                 the `Estimators` within the pipeline require custom
    ///                 arguments during construction.
    ///
    ///                 Standard:
    ///                     MyObject(AnnotationMapsPtr pAllColumnAnnotations);
    ///
    ///                 Custom (example):
    ///                     MyObject(AnnotationMapsPtr pAllColumnAnnotations, int value1, bool value2);
    ///
    ///                 If any Estimator requires Custom constructor, then a ConstructFuncT
    ///                 must be provided (even for those that may not require
    ///                 custom construction).
    ///
    ///                 Example:
    ///                     class MyEstimator :
    ///                         public PipelineExecutionEstimator<
    ///                             StandardEstimator1,
    ///                             CustomEstimator1,
    ///                             CustomEstimator2,
    ///                             StandardEstimator2
    ///                         > {
    ///                     ...
    ///
    ///                         MyEstimator(AnnotationMapsPtr pAllColumnAnnotations, int customArg1, std::string customArg2A, int customArg2B) :
    ///                             PipelineExecutionEstimator<
    ///                                 StandardEstimator1,
    ///                                 CustomEstimator1,
    ///                                 CustomEsitmator2,
    ///                                 StandardEstimator2,
    ///                             >(
    ///                                 "MyEstimator",
    ///                                 pAllColumnAnnotations,
    ///                                 [&pAllColumnAnnotations](void) { return StandardEstimator1(std::move(pAllColumnAnnotations)); },
    ///                                 [&customArg1](void) { return CustomEstimator1(customArg1); },
    ///                                 [&customArg2A, &customArg2B](void) { return CustomEstimator2(customArg2A, cutomArg2B); },
    ///                                 [&pAllColumnAnnotations](void) { return StandardEstimator2(std::move(pAllColumnAnnotations)); }
    ///                             ) {
    ///                             ...
    ///                         }
    ///                     };
    ///
    template <typename... ConstructFuncTs>
    PipelineExecutionEstimatorImpl(char const *name, AnnotationMapsPtr pAllColumnAnnotations, ConstructFuncTs &&... args);

    ~PipelineExecutionEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(PipelineExecutionEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using EstimatorChain                    = typename PipelineTraits::EstimatorChain;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    EstimatorChain                          _estimatorChain;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;

    // MSVC has problems when attempting to separate the definition from the declaration
    FitResult fit_impl(typename BaseType::InputType const *pBuffer, size_t cBuffer) override {
        return _estimatorChain.fit(pBuffer, cBuffer);
    }

    bool on_data_completed_impl(void) override;
    void complete_training_impl(void) override;

    // MSVC has problems when attempting to separate the definition from the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return typename BaseType::TransformerUniquePtr(new TransformerType(_estimatorChain));
    }
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
// |  PipelineExecutionTransformer
// |
// ----------------------------------------------------------------------
template <typename... EstimatorTs>
PipelineExecutionTransformer<EstimatorTs...>::PipelineExecutionTransformer(typename PipelineTraits::EstimatorChain &estimatorChain) :
    _transformerChain(estimatorChain) {
}

template <typename... EstimatorTs>
PipelineExecutionTransformer<EstimatorTs...>::PipelineExecutionTransformer(Archive &ar) :
    _transformerChain(ar) {
}

template <typename... EstimatorTs>
void PipelineExecutionTransformer<EstimatorTs...>::save(Archive &ar) const /*override*/ {
    _transformerChain.save(ar);
}

// ----------------------------------------------------------------------
// |
// |  PipelineExecutionEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename... EstimatorTs>
PipelineExecutionEstimatorImpl<EstimatorTs...>::PipelineExecutionEstimatorImpl(char const *name, AnnotationMapsPtr pAllColumnAnnotations) :
    BaseType(name, pAllColumnAnnotations),
    _estimatorChain(pAllColumnAnnotations) {
}

template <typename... EstimatorTs>
template <typename... ConstructFuncTs>
PipelineExecutionEstimatorImpl<EstimatorTs...>::PipelineExecutionEstimatorImpl(char const *name, AnnotationMapsPtr pAllColumnAnnotations, ConstructFuncTs &&... funcs) :
    BaseType(name, pAllColumnAnnotations),
    _estimatorChain(std::forward<ConstructFuncTs>(funcs)...) {

    static_assert(sizeof...(EstimatorTs) == sizeof...(ConstructFuncTs), "The number of constructor creation args must be equal to the number of estimators");
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename... EstimatorTs>
bool PipelineExecutionEstimatorImpl<EstimatorTs...>::begin_training_impl(void) /*override*/ {
    return _estimatorChain.begin_training();
}

template <typename... EstimatorTs>
bool PipelineExecutionEstimatorImpl<EstimatorTs...>::on_data_completed_impl(void) /*override*/ {
    return _estimatorChain.on_data_completed();
}

template <typename... EstimatorTs>
void PipelineExecutionEstimatorImpl<EstimatorTs...>::complete_training_impl(void) /*override*/ {
    _estimatorChain.complete_training();
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
