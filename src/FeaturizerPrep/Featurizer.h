// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <memory>
#include <map>
#include <vector>

#include <boost/optional.hpp>

namespace Microsoft {
namespace Featurizer {

// ----------------------------------------------------------------------
// |  Forward Declarations
class Archive; // Defined in Archive.h

/////////////////////////////////////////////////////////////////////////
///  \class         Annotation
///  \brief         Base class for an individual datum associated with a column that is produced
///                 by an `Estimator`. Once an `Annotation` is created and associated with a column,
///                 any downstream `Estimator` can query for the `Annotation` and retrieve its
///                 associated values. With this system in place, we ensure that data associated with
///                 a column isn't calculated repeatedly.
///
///                 Examples of possible derived classes:
///                     - Mean of all values in a column, as calculated by a Mean `AnnotationEstimator`
///                     - Most common value in a column, as calculated by a histogram-like `AnnotationEstimator`
///                     - etc.
///
///                 This base class doesn't contain the data produced by an `Estimator`, but
///                 `Estimators` should implement functionality to easily retrieve annotation
///                 data that they have created for a specific column. Note the virtual destructor
///                 to ensure proper cleanup when these values are destroyed.
///
class Annotation {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------

    /////////////////////////////////////////////////////////////////////////
    ///  \typedef       EstimatorUniqueId
    ///  \brief         Different estimators of the same name produce annotations that must be uniquely
    ///                 identifiable. For example, the results produce by a mean `AnnotationEstimator`
    ///                 based on the first 200 values must be distinguishable from the results produced
    ///                 by a mean `AnnotationEstimator` based on the first 500 values.
    ///
    ///                 The estimator's address is memory is used to determine uniqueness.
    ///
    ///                 THIS IMPLEMENTATION WILL BREAK IF WE EVER SUPPORT SERIALIZATION, as the memory
    ///                 address of a deserialized object will be different from the memory address used
    ///                 when originally creating the `Annotation`. If we want to support serialization
    ///                 during training, we will need to introduce a mechanisms to uniquely identify
    ///                 object instances in a way that persists after objects are serialized/deserialized.
    ///                 `Annotations` are only used during training, so this will not be an issue when
    ///                 serializing `Transformers`.
    ///
    using EstimatorUniqueId                 = void const *;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    EstimatorUniqueId const                 CreatorId;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    virtual ~Annotation(void) = default;

    Annotation(Annotation const &) = delete;
    Annotation & operator =(Annotation const &) = delete;

    Annotation(Annotation &&) = default;
    Annotation & operator =(Annotation &&) = delete;

protected:
    // ----------------------------------------------------------------------
    // |
    // |  Protected Methods
    // |
    // ----------------------------------------------------------------------
    Annotation(EstimatorUniqueId creator_id);
};

using AnnotationPtr                         = std::shared_ptr<Annotation>;

// `Estimators` with the same name may generate different Annotations based on
// the settings provided when it was constructed...
using AnnotationPtrs                        = std::vector<AnnotationPtr>;
// TODO: Updating the vector should be thread safe when executing the DAGs in parallel.

// A single column supports `Annotations` from different `Estimators`...
using AnnotationMap                         = std::map<std::string, AnnotationPtrs>;
// TODO: Updating the map should be thread safe when executing the DAGs in parallel.

// An `Estimator` may support multiple columns...
using AnnotationMaps                        = std::vector<AnnotationMap>;

// All `Estimators` within a DAG should use the same collection of column `Annotations`.
using AnnotationMapsPtr                     = std::shared_ptr<AnnotationMaps>;

// TODO: Expect more classes with regards to Annotation as we use the functionality more.

/////////////////////////////////////////////////////////////////////////
///  \function      CreateTestAnnotationMapsPtr
///  \brief         An `Estimator` requires an `AnnotationMapsPtr` upon
///                 construction. This method can be used to quickly create
///                 one of these objects during testing.
///
///                 THIS FUNCTION SHOULD NOT BE USED IN ANY PRODUCTION CODE!
///
AnnotationMapsPtr CreateTestAnnotationMapsPtr(size_t num_cols);

/////////////////////////////////////////////////////////////////////////
///  \class         Estimator
///  \brief         An `Estimator` collects data during the training process and ultimately generates
///                 state data that is used during training or inferencing. Note that
///                 `Estimators` are only used during the training process.
///
class Estimator {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using AnnotationMapsPtr                 = AnnotationMapsPtr;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    std::string const                       Name;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    virtual ~Estimator(void) = default;

    Estimator(Estimator const &) = delete;
    Estimator & operator =(Estimator const &) = delete;

    Estimator(Estimator &&) = default;
    Estimator & operator =(Estimator &&) = delete;

    /////////////////////////////////////////////////////////////////////////
    ///  \function      get_column_annotations
    ///  \brief         Returns the column annotations for all columns. Note
    ///                 that this information is shared across all `Estimators`
    ///                 with the DAG.
    ///
    ///                 Note that is most cases, callers should prefer to retrieve
    ///                 `Annotation` values from a derived class method rather than
    ///                 this method. This method is here so that the final
    ///                 `Annotation` states for all columns can be used in
    ///                 framework-specific code.
    ///
    AnnotationMaps const & get_column_annotations(void) const;

protected:
    // ----------------------------------------------------------------------
    // |
    // |  Protected Methods
    // |
    // ----------------------------------------------------------------------
    Estimator(std::string name, AnnotationMapsPtr pAllColumnAnnotations);

    /////////////////////////////////////////////////////////////////////////
    ///  \function      add_annotation
    ///  \brief         Adds an `Annotation` to the specified column.
    ///
    void add_annotation(AnnotationPtr pAnnotation, size_t col_index) const;

    /////////////////////////////////////////////////////////////////////////
    ///  \function      get_annotation_impl
    ///  \brief         Helper method that can be used by derived class when implementation functionality
    ///                 to retrieve `Annotation` data created by the derived class itself.
    ///
    template <typename DerivedAnnotationT>
    boost::optional<DerivedAnnotationT &> get_annotation_impl(size_t col_index) const;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    AnnotationMapsPtr const                 _all_column_annotations;
};

/////////////////////////////////////////////////////////////////////////
///  \class         FitEstimatorImpl
///  \brief         Common base class for an `Estimator` that supports fit functionality. Derived
///                 classes can produce `Annotations` used by other `Estimators` during the training
///                 process and/or state that is returned to the caller during runtime as a part
///                 of training and inferencing activities.
///
template <typename InputT>
class FitEstimatorImpl : public Estimator {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = InputT;
    using ThisType                          = FitEstimatorImpl<InputType>;

    /////////////////////////////////////////////////////////////////////////
    ///  \enum          FitResult
    ///  \brief         Result returned by the `fit` method.
    ///
    enum class FitResult {
        Complete,                           /// Fitting is complete and there is no need to call `fit` on this `Estimator` any more.
        Continue                            /// Continue providing data to `fit` (if such data is available).
    };

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    FitEstimatorImpl(std::string name, AnnotationMapsPtr pAllColumnAnnotations, bool is_training_complete=false);
    ~FitEstimatorImpl(void) override = default;

    FitEstimatorImpl(FitEstimatorImpl const &) = delete;
    FitEstimatorImpl & operator =(FitEstimatorImpl const &) = delete;

    FitEstimatorImpl(FitEstimatorImpl &&) = default;
    FitEstimatorImpl & operator =(FitEstimatorImpl &&) = delete;

    /////////////////////////////////////////////////////////////////////////
    ///  \function      is_training_complete
    ///  \brief         Returns true if the `complete_training` method has been called
    ///                 for this `Estimator`. `fit` should not be invoked on
    ///                 an `Estimator` where training has been completed.
    ///
    bool is_training_complete(void) const;

    /////////////////////////////////////////////////////////////////////////
    ///  \function      fit
    ///  \brief         Method invoked during training. This method will be invoked until it returns `FitResult::Complete`
    ///                 or no additional data is available. Derived classes should use this columnar data to create
    ///                 state (either in the form of `Annotations`) used during the training process or state data that
    ///                 is used in future calls to `transform`. This method should not be invoked on an object that
    ///                 has already been completed.
    ///
    FitResult fit(InputType value);
    FitResult fit(InputType const *pInputBuffer, size_t cInputBuffer, boost::optional<std::uint64_t> const &optionalNumTrailingNulls=boost::optional<std::uint64_t>());

    /////////////////////////////////////////////////////////////////////////
    ///  \function      complete_training
    ///  \brief         Completes the training process. Derived classes should use this method to produce any final state
    ///                 that is used in calls to `transform` or to add `Annotations` for a column. This method should not be
    ///                 invoked on an object that has already been completed.
    ///
    FitEstimatorImpl & complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    bool                                    _is_training_complete;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    /////////////////////////////////////////////////////////////////////////
    ///  \function      fit_impl
    ///  \brief         `fit` performs common object state and parameter validation before invoking
    ///                 this abstract method.
    ///
    virtual FitResult fit_impl(InputType const *pBuffer, size_t cBuffer, boost::optional<std::uint64_t> const &optionalNumTrailingNulls) = 0;

    /////////////////////////////////////////////////////////////////////////
    ///  \function      complete_training_impl
    ///  \brief         `complete_training` performs common object state validation before invoking this
    ///                 abstract method.
    ///
    virtual void complete_training_impl(void) = 0;
};

/////////////////////////////////////////////////////////////////////////
///  \class         AnnotationEstimator
///  \brief         An `Estimator` that generates `Annotations` when completed. It is no longer
///                 invoked once its training is complete (i.e. it doesn't have a `transform`
///                 method).
///
template <typename InputT>
class AnnotationEstimator : public FitEstimatorImpl<InputT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = InputT;
    using ThisType                          = AnnotationEstimator<InputType>;
    using BaseType                          = FitEstimatorImpl<InputT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    using BaseType::BaseType;
    ~AnnotationEstimator(void) override = default;

    AnnotationEstimator(AnnotationEstimator const &) = delete;
    AnnotationEstimator & operator =(AnnotationEstimator const &) = delete;

    AnnotationEstimator(AnnotationEstimator &&) = default;
    AnnotationEstimator & operator =(AnnotationEstimator &&) = delete;
};

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerEstimator
///  \brief         An `Estimator` that performs some activity during calls
///                 to `transform`. Derived classes may or may not generate
///                 training state (in the form of `Annotations`) or transforming
///                 state.
///
template <typename InputT, typename TransformedT>
class TransformerEstimator : public FitEstimatorImpl<InputT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = InputT;
    using TransformedType                   = TransformedT;
    using ThisType                          = TransformerEstimator<InputType, TransformedType>;
    using BaseType                          = FitEstimatorImpl<InputT>;

    /////////////////////////////////////////////////////////////////////////
    ///  \class         Transformer
    ///  \brief         Object that uses state to produce a result during
    ///                 inferencing activities.
    ///
    class Transformer {
    public:
        // ----------------------------------------------------------------------
        // |  Public Types
        using InputType                     = InputType;
        using TransformedType               = TransformedType;

        // ----------------------------------------------------------------------
        // |  Public Methods
        Transformer(void) = default;
        Transformer(Archive &ar);

        virtual ~Transformer(void) = default;

        Transformer(Transformer const &) = delete;
        Transformer & operator =(Transformer const &) = delete;

        Transformer(Transformer &&) = default;
        Transformer & operator =(Transformer &&) = delete;

        /////////////////////////////////////////////////////////////////////////
        ///  \function      execute
        ///  \brief         Produces a result for a given input.
        ///
        virtual TransformedType execute(InputType input) = 0;

        /////////////////////////////////////////////////////////////////////////
        ///  \function      save
        ///  \brief         Saves the state of the object so it can be reconstructed
        ///                 at a later time.
        ///
        virtual void save(Archive &ar) const = 0;
    };

    using TransformerPtr                    = std::shared_ptr<Transformer>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    using BaseType::BaseType;
    ~TransformerEstimator(void) override = default;

    TransformerEstimator(TransformerEstimator const &) = delete;
    TransformerEstimator & operator =(TransformerEstimator const &) = delete;

    TransformerEstimator(TransformerEstimator &&) = default;
    TransformerEstimator & operator =(TransformerEstimator &&) = delete;

    ThisType & complete_training(void);

    /////////////////////////////////////////////////////////////////////////
    ///  \function      has_created_transformer
    ///  \brief         Returns true if this object has been used to create
    ///                 a `Transformer`. No methods should be called on the object
    ///                 once it has been used to create a transformer.
    ///
    bool has_created_transformer(void) const;

    /////////////////////////////////////////////////////////////////////////
    ///  \function      create_transformer
    ///  \brief         Creates a `Transformer` using the trained state of the
    ///                 object. No methods should be called on the object once
    ///                 it has been used to create a transformer.
    ///
    TransformerPtr create_transformer(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    bool                                    _created_transformer = false;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    /////////////////////////////////////////////////////////////////////////
    ///  \function      create_transformer_impl
    ///  \brief         `create_transformer` performs common object state validation before
    ///                 calling this method.
    ///
    virtual TransformerPtr create_transformer_impl(void) = 0;
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
// |  Annotation
// |
// ----------------------------------------------------------------------
inline Annotation::Annotation(EstimatorUniqueId creator_id) :
    CreatorId(
        [&creator_id]() {
            if(creator_id == nullptr)
                throw std::runtime_error("Invalid id");

            return creator_id;
        }()
    ) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
inline AnnotationMapsPtr CreateTestAnnotationMapsPtr(size_t num_cols) {
    AnnotationMaps                          maps;

    if(num_cols)
        maps.resize(num_cols);

    return std::make_shared<decltype(maps)>(std::move(maps));
}

// ----------------------------------------------------------------------
// |
// |  Estimator
// |
// ----------------------------------------------------------------------
inline AnnotationMaps const & Estimator::get_column_annotations(void) const {
    return *_all_column_annotations;
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
inline Estimator::Estimator(std::string name, AnnotationMapsPtr pAllColumnAnnotations) :
    Name(
        std::move(
            [&name](void) -> std::string & {
                if(name.empty())
                    throw std::runtime_error("Invalid name");

                return name;
            }()
        )
    ),
    _all_column_annotations(
        std::move(
            [&pAllColumnAnnotations](void) -> AnnotationMapsPtr & {
                if(!pAllColumnAnnotations || pAllColumnAnnotations->empty())
                    throw std::runtime_error("Empty annotations");

                return pAllColumnAnnotations;
            }()
        )
    ) {
}

inline void Estimator::add_annotation(AnnotationPtr pAnnotation, size_t col_index) const {
    if(!pAnnotation)
        throw std::runtime_error("Invalid annotation");

    AnnotationMaps &                        all_annotations(*_all_column_annotations);

    if(col_index >= all_annotations.size())
        throw std::runtime_error("Invalid annotation index");

    AnnotationPtrs &                        annotations(
        [&all_annotations, &col_index, this](void) -> AnnotationPtrs & {
            AnnotationMap &                 column_annotations(all_annotations[col_index]);

            // TODO: Acquire read map lock
            AnnotationMap::iterator const   iter(column_annotations.find(Name));

            if(iter != column_annotations.end())
                return iter->second;

            // TODO: Promote read lock to write lock
            std::pair<AnnotationMap::iterator, bool> const result(column_annotations.emplace(std::make_pair(Name, AnnotationPtrs())));

            if(result.first == column_annotations.end() || result.second == false)
                throw std::runtime_error("Invalid insertion");

            return result.first->second;
        }()
    );

    // TODO: Acquire vector read lock
    annotations.emplace_back(std::move(pAnnotation));
}

template <typename DerivedAnnotationT>
boost::optional<DerivedAnnotationT &> Estimator::get_annotation_impl(size_t col_index) const {
    AnnotationMaps const &                  all_annotations(*_all_column_annotations);

    if(col_index >= all_annotations.size())
        throw std::runtime_error("Invalid annotation index");

    AnnotationMap const &                   column_annotations(all_annotations[col_index]);

    // TODO: Acquire read map lock
    AnnotationMap::const_iterator const     column_annotations_iter(column_annotations.find(Name));

    if(column_annotations_iter != column_annotations.end()) {
        AnnotationPtrs const &              annotations(column_annotations_iter->second);

        // TODO: Acquire vector read lock
        for(auto const & annotation : annotations) {
            if(annotation->CreatorId == this) {
                return static_cast<DerivedAnnotationT &>(*annotation);
            }
        }
    }

    return boost::optional<DerivedAnnotationT &>();
}

// ----------------------------------------------------------------------
// |
// |  FitEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename InputT>
FitEstimatorImpl<InputT>::FitEstimatorImpl(std::string name, AnnotationMapsPtr pAllColumnAnnotations, bool is_training_complete /*=false*/) :
    Estimator(std::move(name), std::move(pAllColumnAnnotations)),
    _is_training_complete(std::move(is_training_complete)) {
}

template <typename InputT>
bool FitEstimatorImpl<InputT>::is_training_complete(void) const {
    return _is_training_complete;
}

template <typename InputT>
typename FitEstimatorImpl<InputT>::FitResult FitEstimatorImpl<InputT>::fit(InputType value) {
    return fit(&value, 1);
}

template <typename InputT>
typename FitEstimatorImpl<InputT>::FitResult FitEstimatorImpl<InputT>::fit(InputType const *pInputBuffer, size_t cInputBuffer, boost::optional<std::uint64_t> const &optionalNumTrailingNulls) {
    if(_is_training_complete)
        throw std::runtime_error("`fit` should not be invoked on an estimator that is already complete");

    if(pInputBuffer && cInputBuffer == 0)
        throw std::runtime_error("Invalid buffer");

    if(pInputBuffer == nullptr && cInputBuffer != 0)
        throw std::runtime_error("Invalid buffer");

    if(pInputBuffer == nullptr && cInputBuffer == 0 && !optionalNumTrailingNulls)
        throw std::runtime_error("Invalid invocation");

    if(optionalNumTrailingNulls && *optionalNumTrailingNulls == 0)
        throw std::runtime_error("Invalid number of nulls");

    FitResult                               result(fit_impl(pInputBuffer, cInputBuffer, optionalNumTrailingNulls));

    if(result == FitResult::Complete)
        complete_training();

    return result;
}

template <typename InputT>
FitEstimatorImpl<InputT> & FitEstimatorImpl<InputT>::complete_training(void) {
    if(_is_training_complete)
        throw std::runtime_error("`complete_training` should not be invoked on an estimator that is already complete");

    complete_training_impl();
    _is_training_complete = true;

    return *this;
}

// ----------------------------------------------------------------------
// |
// |  TransformerEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
TransformerEstimator<InputT, TransformedT> & TransformerEstimator<InputT, TransformedT>::complete_training(void) {
    return static_cast<ThisType &>(BaseType::complete_training());
}

template <typename InputT, typename TransformedT>
bool TransformerEstimator<InputT, TransformedT>::has_created_transformer(void) const {
    return _created_transformer;
}

template <typename InputT, typename TransformedT>
typename TransformerEstimator<InputT, TransformedT>::TransformerPtr TransformerEstimator<InputT, TransformedT>::create_transformer(void) {
    if(!BaseType::is_training_complete())
        throw std::runtime_error("`create_transformer` should not be invoked on an estimator that is not yet complete");

    if(_created_transformer)
        throw std::runtime_error("`create_transformer` should not be invoked on an estimator that has been used to create a `Transformer`");

    TransformerPtr                          result(create_transformer_impl());

    if(!result)
        throw std::runtime_error("Invalid result");

    _created_transformer = true;
    return result;
}

} // namespace Featurizer
} // namespace Microsoft
