// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "Calculators/MaxCalculator.h"
#include "Calculators/MinCalculator.h"
#include "Components/InferenceOnlyFeaturizerImpl.h"
#include "Components/WindowFeaturizerBase.h"
#include "Components/GrainFeaturizerImpl.h"
#include "../Featurizer.h"
#include "../Traits.h"

#include <vector>

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

static constexpr char const * const         SimpleRollingWindowEstimatorName("SimpleRollingWindowEstimator");

/////////////////////////////////////////////////////////////////////////
///  \fn            SimpleRollingWindowCalculation
///  \brief         Which type of calculation will be performed on the rolling window.
///                 Currently only one of calculation is supported. This will be expanded upon in the future,
///                 so we are peparing by making this an enum from the get go.
///
enum class SimpleRollingWindowCalculation : std::uint8_t {
    Min = 1,
    Max = 2
};


/////////////////////////////////////////////////////////////////////////
///  \class         SimpleRollingWindowTransformer
///  \brief         RollingWindow class that is used for all simple window computations like min or max.
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class SimpleRollingWindowTransformer:
    public Components::InferenceOnlyTransformerImpl<InputT, std::vector<typename Traits<InputT>::nullable_type>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::InferenceOnlyTransformerImpl<InputT, std::vector<typename Traits<InputT>::nullable_type>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SimpleRollingWindowTransformer(std::uint32_t windowSize, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowCount = 1) ;
    SimpleRollingWindowTransformer(Archive &ar);
    ~SimpleRollingWindowTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SimpleRollingWindowTransformer);

    bool operator==(SimpleRollingWindowTransformer const &other) const;
    bool operator!=(SimpleRollingWindowTransformer const &other) const;
    void save(Archive & ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Members
    // |
    // ----------------------------------------------------------------------
    // _windowSizes and _minWindowCount are int64 so that we can have the full positive range of the uint32 it comes
    // in as but can still support negative numbers.
    Components::CircularBuffer<InputT>              _buffer;
    const std::uint32_t                             _windowSize;
    const std::uint32_t                             _horizon;
    const std::uint32_t                             _minWindowSize;
    const SimpleRollingWindowCalculation            _windowCalculation;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC runs into problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        typename BaseType::TransformedType         results(_horizon);
        
        _buffer.push(input);
        size_t bufferSize = _buffer.size();

        typename Traits<InputT>::nullable_type result;
        size_t numElements;
        size_t startingOffset;

        for (std::uint32_t offset = 0; offset < _horizon; ++offset){

            // If we don't have enough elements then output NaN
            if ((_horizon - offset) + _minWindowSize > bufferSize) {
                result = Traits<InputT>::CreateNullValue();

            // If we have strictly less elements then the window size, but more then the minimum size
            } else {
                if (bufferSize - (_horizon - offset) < _windowSize) {
                    numElements = bufferSize - (_horizon - offset); //asfd
                    startingOffset = 0;
                } else {
                    numElements = _windowSize;
                    startingOffset = offset - (_buffer.capacity() - bufferSize);
                }

                const std::tuple<typename Components::CircularBuffer<InputT>::iterator, typename Components::CircularBuffer<InputT>::iterator> range = _buffer.range(numElements, startingOffset);
                const typename Components::CircularBuffer<InputT>::iterator start_iter = std::get<0>(range);
                const typename Components::CircularBuffer<InputT>::iterator end_iter = std::get<1>(range);

                // TODO: Need a better way to deal with this.
                if (_windowCalculation == SimpleRollingWindowCalculation::Min) {
                    result = Calculators::MinCalculator<BaseType::InputType>::execute(start_iter, end_iter);
                } else if (_windowCalculation == SimpleRollingWindowCalculation::Max) {
                    result = Calculators::MaxCalculator<BaseType::InputType>::execute(start_iter, end_iter);
                }
            }

            results[offset] = result;
        }

        callback(results);
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         SimpleRollingWindowEstimator
///  \brief         Estimator that creates `SimpleRollingWindowTransformer`.
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class SimpleRollingWindowEstimator :
    public TransformerEstimator<InputT, std::vector<typename Traits<InputT>::nullable_type>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, std::vector<typename Traits<InputT>::nullable_type>>;
    using TransformerType                   = SimpleRollingWindowTransformer<InputT, MaxNumTrainingItemsV>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SimpleRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t windowSize, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowCount = 1);
    ~SimpleRollingWindowEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SimpleRollingWindowEstimator);


private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Members
    // |
    // ----------------------------------------------------------------------
    const std::uint32_t                           _windowSize;
    const std::uint32_t                           _horizon;
    const std::uint32_t                           _minWindowCount;
    const SimpleRollingWindowCalculation      _windowCalculation;


    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;

    // Note that like in the InferenceOnlyEstimator the following training methods aren't used, but need to be overridden as
    // the base implementations are abstract. The noop definitions are below.
    FitResult fit_impl(InputT const *pBuffer, size_t cBuffer) override;

    void complete_training_impl(void) override;

    // MSVC has problems when the definition for the func is separated from its declaration.
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return typename BaseType::TransformerUniquePtr(new SimpleRollingWindowTransformer<InputT, MaxNumTrainingItemsV>(_windowSize, _windowCalculation, _horizon, _minWindowCount));
    }

};

/////////////////////////////////////////////////////////////////////////
///  \class       GrainedSimpleRollingWindowEstimator
///  \brief         GrainedTransformer that creates `SimpleRollingWindowEstimator`.
///

template <typename InputT, size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class GrainedSimpleRollingWindowEstimator :
    public Components::GrainEstimatorImpl<std::vector<std::string>, SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = Components::GrainEstimatorImpl<std::vector<std::string>, SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>>;
    
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    GrainedSimpleRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t windowSize, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowCount = 1);
    ~GrainedSimpleRollingWindowEstimator(void) override = default;
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
// |  SimpleRollingWindowTransformer
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
SimpleRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::SimpleRollingWindowTransformer(std::uint32_t windowSize, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowCount) :
    _windowSize(std::move(windowSize)),
    _windowCalculation(std::move(windowCalculation)),
    _horizon(std::move(horizon)),
    _minWindowSize(std::move(minWindowCount)),
    _buffer(horizon + windowSize) {

}

template <typename InputT, size_t MaxNumTrainingItemsV>
SimpleRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::SimpleRollingWindowTransformer(Archive &ar) :
    SimpleRollingWindowTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            std::uint32_t                       windowSize(Traits<std::uint32_t>::deserialize(ar));
            SimpleRollingWindowCalculation  windowCalculation(static_cast<SimpleRollingWindowCalculation>(Traits<std::uint8_t>::deserialize(ar)));
            std::uint32_t                       horizon(Traits<std::uint32_t>::deserialize(ar));
            std::uint32_t                       minWindowCount(Traits<std::uint32_t>::deserialize(ar));


            return SimpleRollingWindowTransformer(std::move(windowSize), std::move(windowCalculation), std::move(horizon), std::move(minWindowCount));
        }()
    ) {
}

template <typename InputT, size_t MaxNumTrainingItemsV>
bool SimpleRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::operator==(SimpleRollingWindowTransformer const &other) const {
    return _windowSize  == other._windowSize && _windowCalculation == other._windowCalculation && _horizon == other._horizon && _minWindowSize == other._minWindowSize;
}

template <typename InputT, size_t MaxNumTrainingItemsV>
bool SimpleRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::operator!=(SimpleRollingWindowTransformer const &other) const {
    return (*this == other) == false;
}

template <typename InputT, size_t MaxNumTrainingItemsV>
void SimpleRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<std::uint32_t>::serialize(ar, _windowSize);
    Traits<std::uint8_t>::serialize(ar, static_cast<std::uint8_t>(_windowCalculation));
    Traits<std::uint32_t>::serialize(ar, _horizon);
    Traits<std::uint32_t>::serialize(ar, _minWindowSize);

    // Note that we aren't serializing working state
}

// ----------------------------------------------------------------------
// |
// |  SimpleRollingWindowEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>::SimpleRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t windowSize, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowCount) :
    BaseType(SimpleRollingWindowEstimatorName, std::move(pAllColumnAnnotations)),
    _windowSize(std::move(windowSize)),
    _windowCalculation(std::move(windowCalculation)),
    _horizon(std::move(horizon)),
    _minWindowCount(std::move(minWindowCount))
    {
}

template <typename InputT, size_t MaxNumTrainingItemsV>
bool SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    // Do not allow any further training
    return false;
}

template <typename InputT, size_t MaxNumTrainingItemsV>
FitResult SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>::fit_impl(InputT const *, size_t) /*override*/ {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

template <typename InputT, size_t MaxNumTrainingItemsV>
void SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

// ----------------------------------------------------------------------
// |
// |  GrainedSimpleRollingWindowEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
GrainedSimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>::GrainedSimpleRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t windowSize, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowCount) :
    BaseType(pAllColumnAnnotations,
             [windowSize, windowCalculation, horizon, minWindowCount](AnnotationMapsPtr pAllColumnAnnotationsParam) {
                 return SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotationsParam), std::move(windowSize), std::move(windowCalculation), std::move(horizon), std::move(minWindowCount));
             })
    {
}


} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
