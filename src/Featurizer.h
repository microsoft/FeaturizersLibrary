// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <cstring>                          // For `strcmp`
#include <memory>
#include <map>
#include <string>
#include <vector>

#include "Traits.h"

#include "3rdParty/optional.h"

namespace Microsoft {
namespace Featurizer {

// ----------------------------------------------------------------------
// |
// |  Preprocessor Definitions
// |
// ----------------------------------------------------------------------
// TODO: During a future refactor, this preprocessor definition(s) should be
// moved to a different file.

/////////////////////////////////////////////////////////////////////////
///  \def           FEATURIZER_MOVE_CONSTRUCTOR_ONLY
///  \brief         Disables the methods below, while setting the move
///                 constructor to default.
///
///                 Disables:
///                     - Copy constructor
///                     - Copy assignment
///                     - Move assignment
///
#define FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ClassName)     \
    ClassName(ClassName const &) = delete;              \
    ClassName & operator =(ClassName const &) = delete; \
    ClassName(ClassName &&) = default;                  \
    ClassName & operator =(ClassName &&) = delete;

// ----------------------------------------------------------------------
// |  Forward Declarations
class Archive; // Defined in Archive.h

/////////////////////////////////////////////////////////////////////////
///  \class         Transformer
///  \brief         Object that uses state to produce a result during
///                 inferencing activities.
///
template <typename InputT, typename TransformedT>
class Transformer {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(std::is_reference<InputT>::value == false, "InputT should not be a reference type");
    static_assert(std::is_const<InputT>::value == false, "InputT should not be a const type");

    using InputType                     = InputT;
    using TransformedType               = TransformedT;

    using Archive                       = Microsoft::Featurizer::Archive;

    using CallbackFunction              = std::function<void (TransformedType)>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    Transformer(void) = default;
    virtual ~Transformer(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Transformer);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            execute
    ///  \brief         Invokes the provided callback for each result generated
    ///                 by the provided input.
    ///
    void execute(InputType const &input, CallbackFunction const &callback);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            flush
    ///  \brief         Flushes any remaining elements before the `Transformer`
    ///                 is destroyed.
    ///
    void flush(CallbackFunction const &callback);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            save
    ///  \brief         Saves the state of the object so it can be reconstructed
    ///                 at a later time.
    ///
    virtual void save(Archive &ar) const = 0;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    virtual void execute_impl(InputType const &input, CallbackFunction const &callback) = 0;
    virtual void flush_impl(CallbackFunction const &callback) = 0;
};

/////////////////////////////////////////////////////////////////////////
///  \class         StandardTransformer
///  \brief         Most `Transformers` will generate a single transformed
///                 type for each input. However, the `Transformer` base
///                 class is written for the more infrequent scenario where
///                 a single input may generate zero or more transformed types.
///                 This derived class provides functionality common where
///                 there is only one output for each input.
///
template <typename InputT, typename TransformedT>
class StandardTransformer : public Transformer<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = Transformer<InputT, TransformedT>;

    using InputType                         = typename BaseType::InputType;
    using TransformedType                   = typename BaseType::TransformedType;
    using CallbackFunction                  = typename BaseType::CallbackFunction;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    StandardTransformer(void) = default;
    ~StandardTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(StandardTransformer);

    TransformedType execute(InputType &input);
    TransformedType execute(InputType const &input);
    using BaseType::execute;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void flush_impl(CallbackFunction const &callback) override;
};

/////////////////////////////////////////////////////////////////////////
///  \class         Annotation
///  \brief         Base class for an individual datum associated with a column that is produced
///                 by an `Estimator`. Once an `Annotation` is created and associated with a column,
///                 any downstream `Estimator` can query for the `Annotation` and retrieve its
///                 associated values. With this system in place, we ensure that data associated with
///                 a column isn't calculated repeatedly.
///
///                 Examples of possible derived classes:
///                     - Mean of all values in a column, as calculated by a Mean `FitEstimator`
///                     - Most common value in a column, as calculated by a histogram-like `FitEstimator`
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
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    Annotation(void) = default;
    virtual ~Annotation(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Annotation);
};

using AnnotationPtr                         = std::shared_ptr<Annotation>;

// `Estimators` with the same name may generate different Annotations based on
// the settings provided when it was constructed...
using AnnotationPtrs                        = std::vector<AnnotationPtr>;
// TODO: Updating the vector should be thread safe when executing the DAGs in parallel.

namespace Details {

struct RawStringComparison {
    inline bool operator()(char const *p1, char const *p2) const { return strcmp(p1, p2) < 0; }
};

} // namespace Details

// A single column supports `Annotations` from different `Estimators`...
using AnnotationMap                         = std::map<char const *, AnnotationPtrs, Details::RawStringComparison>;
// TODO: Updating the map should be thread safe when executing the DAGs in parallel.

// An `Estimator` may support multiple columns...
using AnnotationMaps                        = std::vector<AnnotationMap>;

// All `Estimators` within a DAG should use the same collection of column `Annotations`.
using AnnotationMapsPtr                     = std::shared_ptr<AnnotationMaps>;

/////////////////////////////////////////////////////////////////////////
///  \fn            CreateTestAnnotationMapsPtr
///  \brief         An `Estimator` requires an `AnnotationMapsPtr` upon
///                 construction. This method can be used to quickly create
///                 one of these objects during testing.
///
///                 THIS FUNCTION SHOULD NOT BE USED IN ANY PRODUCTION CODE!
///
AnnotationMapsPtr CreateTestAnnotationMapsPtr(size_t numCols);

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
    using AnnotationMapsPtr                 = Microsoft::Featurizer::AnnotationMapsPtr;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    char const * const                      Name;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    virtual ~Estimator(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Estimator);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            get_column_annotations
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
    Estimator(char const *name, AnnotationMapsPtr pAllColumnAnnotations);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            add_annotation
    ///  \brief         Adds an `Annotation` to the specified column.
    ///
    void add_annotation(AnnotationPtr pAnnotation, size_t colIndex) const;

    static void add_annotation(AnnotationMapsPtr const allColumnAnnotations, AnnotationPtr pAnnotation, size_t colIndex, char const *name);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            get_annotation_impl
    ///  \brief         Helper method that can be used by derived class when implementation functionality
    ///                 to retrieve `Annotation` data created by the derived class itself.
    ///
    ///                 Note that the return type of this function used to be
    ///                 boost::optional<DerivedAnnotationT &> then nonstd::optional<DerivedAnnotationT &>.
    ///                 Unfortunately, nonstd::optional doesn't support reference types.
    ///                 Consider the return value to be a potentially null pointer.
    ///
    template <typename DerivedAnnotationT>
    static DerivedAnnotationT * get_annotation_impl(AnnotationMaps const &allAnnotations, size_t colIndex, char const *name);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    AnnotationMapsPtr const                 _allColumnAnnotations;
};

/////////////////////////////////////////////////////////////////////////
///  \enum          TrainingState
///  \brief         Training state associated with an `Estimator`.
///
enum class TrainingState : unsigned char {
    Pending = 1,                            ///> `begin_training` has not been called.
    Training,                               ///> `fit` may be invoked.
    Finished,                               ///> The estimator has received enough data and should be completed; future calls to `fit` will raise an exception.
    Completed                               ///> `complete_training` has been called; calls to `begin_training`, `fit`, and `complete_training` will fail.
};

/////////////////////////////////////////////////////////////////////////
///  \enum          FitResult
///  \brief         Result returned from calls to fit.
///
enum class FitResult : unsigned char {
    Complete = 1,                           ///> Training is complete; any future calls to fit will fail.
    Continue,                               ///> Continue to provide training data.
    Reset                                   ///> Training should continue, but data should be provided from the start of the batch
};

/////////////////////////////////////////////////////////////////////////
///  \class         FitEstimator
///  \brief         Base class for an `Estimator` that supports fit functionality. Derived
///                 classes can produce `Annotations` used by other `Estimators` during the training
///                 process and/or state that is returned to the caller during runtime as a part
///                 of training and inferencing activities.
///
template <typename InputT>
class FitEstimator : public Estimator {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(std::is_reference<InputT>::value == false, "InputT should not be a reference type");
    static_assert(std::is_const<InputT>::value == false, "InputT should not be a const type");

    using InputType                         = InputT;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    FitEstimator(char const *name, AnnotationMapsPtr pAllColumnAnnotations);
    ~FitEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FitEstimator);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            get_state
    ///  \brief         Returns the training state associated with this `Estimator`.
    ///
    TrainingState get_state(void) const;

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            begin_training
    ///  \brief         Begins training for this `Estimator`.
    ///
    FitEstimator & begin_training(void);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            Fit
    ///  \brief         Fits data according to the `Estimator's` internal logic.
    ///                 `begin_training` must be called before `fit` can be invoked.
    ///                 After calls to `fit`, an `Estimator` may transition into
    ///                 the finished state, indicating that it no longer needs
    ///                 any training data.
    ///
    FitResult fit(InputType const &value);
    FitResult fit(InputType const *pItems, size_t cItems);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            on_data_completed
    ///  \brief         Method called to notify an `Estimator` that it has seen
    ///                 all available data. An `Estimator` will either transition
    ///                 into the finished state, indicating that it no longer needs
    ///                 any training data, or remaining in the Training state. If
    ///                 the `Estimator` remains in the Training state, callers
    ///                 should reset the training data and call fit with that
    ///                 data again.
    ///
    FitEstimator & on_data_completed(void);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            complete_training
    ///  \brief         Completes training for the `Estimator`.
    ///
    FitEstimator & complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    TrainingState                           _state;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            begin_training_impl
    ///  \brief         `begin_training` performs common object state validation before invoking
    ///                 this method. Return true to set the `Estimator` into a Training state,
    ///                 false to set the `Estimator` into a Finished state.
    ///
    virtual bool begin_training_impl(void) = 0;

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            fit_impl
    ///  \brief         `fit` performs common object state and parameter validation before invoking
    ///                 this abstract method. Return true to set the `Estimator` into a Training
    ///                 state, false to set the `Estimator` into a Finished state.
    ///
    virtual FitResult fit_impl(InputType const *pItems, size_t cItems) = 0;

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            on_data_completed_impl
    ///  \brief         `on_data_completed` performs common object state validation before invoking
    ///                 this method. Unlike `begin_training_impl` and `fit_impl`, return true to set
    ///                 the `Estimator` into a Finished state and false to ensure the `Estimator`
    ///                 remains in the Training state.
    ///
    virtual bool on_data_completed_impl(void);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            complete_training_impl
    ///  \brief         `complete_training` performs common object state validation before invoking this
    ///                 abstract method.
    ///
    virtual void complete_training_impl(void) = 0;
};

/////////////////////////////////////////////////////////////////////////
///  \class         TransformerEstimator
///  \brief         An `Estimator` that performs some activity during calls
///                 to `transform`. Derived classes may or may not generate
///                 training state (in the form of `Annotations`) or transforming
///                 state.
///
template <typename InputT, typename TransformedT>
class TransformerEstimator : public FitEstimator<InputT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = InputT;
    using TransformedType                   = TransformedT;

    using BaseType                          = FitEstimator<InputT>;

    using TransformerUniquePtr              = std::unique_ptr<Transformer<InputT, TransformedT>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    using BaseType::BaseType;
    ~TransformerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TransformerEstimator);

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            has_created_transformer
    ///  \brief         Returns true if this object has been used to create
    ///                 a `Transformer`. No methods should be called on the object
    ///                 once it has been used to create a transformer.
    ///
    bool has_created_transformer(void) const;

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            create_transformer
    ///  \brief         Creates a `Transformer` using the trained state of the
    ///                 object. No methods should be called on the object once
    ///                 it has been used to create a transformer.
    ///
    TransformerUniquePtr create_transformer(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    bool                                    _createdTransformer = false;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    /////////////////////////////////////////////////////////////////////////
    ///  \fn            create_transformer_impl
    ///  \brief         `create_transformer` performs common object state validation before
    ///                 calling this method.
    ///
    virtual TransformerUniquePtr create_transformer_impl(void) = 0;
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
inline AnnotationMapsPtr CreateTestAnnotationMapsPtr(size_t numCols) {
    AnnotationMaps                          maps;

    if(numCols)
        maps.resize(numCols);

    return std::make_shared<decltype(maps)>(std::move(maps));
}

// ----------------------------------------------------------------------
// |
// |  Transformer
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
void Transformer<InputT, TransformedT>::execute(InputType const &input, CallbackFunction const &callback) {
    if(!callback)
        throw std::invalid_argument("callback");

    execute_impl(input, callback);
}

template <typename InputT, typename TransformedT>
void Transformer<InputT, TransformedT>::flush(CallbackFunction const &callback) {
    if(!callback)
        throw std::invalid_argument("callback");

    flush_impl(callback);
}

// ----------------------------------------------------------------------
// |
// |  StandardTransformer
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
typename StandardTransformer<InputT, TransformedT>::TransformedType StandardTransformer<InputT, TransformedT>::execute(InputType &input) {
    // We can't use nonstd::optional here, as it doesn't properly support move semantics (which
    // becomes a problem for types that don't support copying).
    TransformedT *                          pResult(reinterpret_cast<TransformedT *>(alloca(sizeof(TransformedT))));
    bool                                    isSet(false);

    execute(
        input,
        [&pResult, &isSet](TransformedType r) {
            assert(isSet == false);
            new (reinterpret_cast<void *>(pResult)) TransformedT(std::move(r));
            isSet = true;
        }
    );

    assert(isSet);

    TransformedT                            result(std::move(*pResult));

    pResult->~TransformedT();

    return result;
}

template <typename InputT, typename TransformedT>
typename StandardTransformer<InputT, TransformedT>::TransformedType StandardTransformer<InputT, TransformedT>::execute(InputType const &input) {
    InputType                               value(input);

    return execute(value);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
void StandardTransformer<InputT, TransformedT>::flush_impl(CallbackFunction const &) /*override*/ {
    // This method doesn't do anything for StandardTransformers
}

// ----------------------------------------------------------------------
// |
// |  Estimator
// |
// ----------------------------------------------------------------------
inline AnnotationMaps const & Estimator::get_column_annotations(void) const {
    return *_allColumnAnnotations;
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
inline Estimator::Estimator(char const *name, AnnotationMapsPtr pAllColumnAnnotations) :
    Name(
        [name](void) {
            if(name == nullptr || *name == 0)
                throw std::invalid_argument("name");

            return name;
        }()
    ),
    _allColumnAnnotations(
        std::move(
            [&pAllColumnAnnotations](void) -> AnnotationMapsPtr & {
                if(!pAllColumnAnnotations || pAllColumnAnnotations->empty())
                    throw std::invalid_argument("pAllColumnAnnotations");

                return pAllColumnAnnotations;
            }()
        )
    ) {
}

/*static*/ inline void Estimator::add_annotation(AnnotationMapsPtr const allColumnAnnotations, AnnotationPtr pAnnotation, size_t colIndex, char const *name) {
    if(!pAnnotation)
        throw std::invalid_argument("pAnnotation");

    AnnotationMaps &                        allAnnotations(*allColumnAnnotations);

    if(colIndex >= allAnnotations.size())
        throw std::invalid_argument("colIndex");

    AnnotationPtrs &                        annotations(
        [&allAnnotations, &colIndex, &name](void) -> AnnotationPtrs & {
            AnnotationMap &                 columnAnnotations(allAnnotations[colIndex]);

            // TODO: Acquire read map lock
            AnnotationMap::iterator const   iter(columnAnnotations.find(name));

            if(iter != columnAnnotations.end())
                return iter->second;

            // TODO: Promote read lock to write lock
            std::pair<AnnotationMap::iterator, bool> const result(columnAnnotations.emplace(std::make_pair(name, AnnotationPtrs())));

            if(result.first == columnAnnotations.end() || result.second == false)
                throw std::runtime_error("Invalid insertion");

            return result.first->second;
        }()
    );

    // TODO: Acquire vector read lock
    annotations.emplace_back(std::move(pAnnotation));
}

inline void Estimator::add_annotation(AnnotationPtr pAnnotation, size_t colIndex) const {
    return add_annotation(_allColumnAnnotations, pAnnotation, colIndex, Name);
}

template <typename DerivedAnnotationT>
DerivedAnnotationT * Estimator::get_annotation_impl(AnnotationMaps const &allAnnotations, size_t colIndex, char const *name) {
    if(colIndex >= allAnnotations.size())
        throw std::invalid_argument("colIndex");
    if(name == nullptr || *name == 0)
        throw std::invalid_argument("name");

    AnnotationMap const &                   columnAnnotations(allAnnotations[colIndex]);

    // TODO: Acquire read map lock
    AnnotationMap::const_iterator const     column_annotations_iter(columnAnnotations.find(name));

    if(column_annotations_iter != columnAnnotations.end()) {
        AnnotationPtrs const &              annotations(column_annotations_iter->second);

        // TODO: Acquire vector read lock

        for(auto const &annotation : annotations) {
            if(dynamic_cast<DerivedAnnotationT *>(annotation.get()) != nullptr)
                return &static_cast<DerivedAnnotationT &>(*annotation);
        }
    }

    return nullptr;
}

// ----------------------------------------------------------------------
// |
// |  FitEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT>
FitEstimator<InputT>::FitEstimator(char const *name, AnnotationMapsPtr pAllColumnAnnotations) :
    Estimator(name, std::move(pAllColumnAnnotations)),
    _state(TrainingState::Pending) {
}

template <typename InputT>
TrainingState FitEstimator<InputT>::get_state(void) const {
    return _state;
}

template <typename InputT>
FitEstimator<InputT> & FitEstimator<InputT>::begin_training(void) {
    if(_state != TrainingState::Pending)
        throw std::runtime_error("`begin_training` should not be invoked on an estimator that is already training or completed");

    if(begin_training_impl())
        _state = TrainingState::Training;
    else
        _state = TrainingState::Finished;

    return *this;
}

template <typename InputT>
FitResult FitEstimator<InputT>::fit(InputType const &value) {
    return fit(&value, 1);
}

// I'm not sure why MSVC thinks that the following code is unreachable
// with release builds.
#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4702) // Unreachable code
#endif

template <typename InputT>
FitResult FitEstimator<InputT>::fit(InputType const *pInputs, size_t cInputs) {
    if(_state != TrainingState::Training)
        throw std::runtime_error("`fit` should not be invoked on an estimator that is not training or is already finished/complete");

    if(pInputs == nullptr)
        throw std::invalid_argument("pInputBuffer");

    if(cInputs == 0)
        throw std::invalid_argument("cInputBuffer");

    FitResult                               result(fit_impl(pInputs, cInputs));

    if(result == FitResult::Complete)
        _state = TrainingState::Finished;

    return result;
}

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

template <typename InputT>
FitEstimator<InputT> & FitEstimator<InputT>::on_data_completed(void) {
    if(_state != TrainingState::Training && _state != TrainingState::Finished)
        throw std::runtime_error("`on_data_completed` should not be invoked on an estimator that is not training or is already complete");

    if(_state != TrainingState::Finished && on_data_completed_impl())
        _state = TrainingState::Finished;

    return *this;
}

template <typename InputT>
FitEstimator<InputT> & FitEstimator<InputT>::complete_training(void) {
    if(_state != TrainingState::Training && _state != TrainingState::Finished)
        throw std::runtime_error("`complete_training` should not be invoked on an estimator that is not training or is already complete");

    complete_training_impl();
    _state = TrainingState::Completed;

    return *this;
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT>
/*virtual*/ bool FitEstimator<InputT>::on_data_completed_impl(void) {
    // By default, an estimator can always complete training
    return true;
}

// ----------------------------------------------------------------------
// |
// |  TransformerEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
bool TransformerEstimator<InputT, TransformedT>::has_created_transformer(void) const {
    return _createdTransformer;
}

template <typename InputT, typename TransformedT>
typename TransformerEstimator<InputT, TransformedT>::TransformerUniquePtr TransformerEstimator<InputT, TransformedT>::create_transformer(void) {
    if(BaseType::get_state() != TrainingState::Completed)
        throw std::runtime_error("`create_transformer` should not be invoked on an estimator that is not yet complete");

    if(_createdTransformer)
        throw std::runtime_error("`create_transformer` should not be invoked on an estimator that has been used to create a `Transformer`");

    TransformerUniquePtr                    result(create_transformer_impl());

    if(!result)
        throw std::runtime_error("Invalid result");

    _createdTransformer = true;
    return result;
}

} // namespace Featurizer
} // namespace Microsoft
