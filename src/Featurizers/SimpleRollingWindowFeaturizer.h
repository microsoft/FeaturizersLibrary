// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "../Featurizer.h"
#include "../Traits.h"

#include "Calculators/MaxCalculator.h"
#include "Calculators/MinCalculator.h"
#include "Components/FilterDecoratorFeaturizer.h"
#include "Components/GrainFeaturizerImpl.h"
#include "Components/InferenceOnlyFeaturizerImpl.h"
#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/RollingWindowTransformerBase.h"
#include "Components/WindowFeaturizerBase.h"

#include <vector>

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

// Anonymous namespace for helper using statements
namespace {
    using GrainType = std::vector<std::string>;
} // Anonymous namespace

static constexpr char const * const         SimpleRollingWindowEstimatorName("SimpleRollingWindowEstimator");
static constexpr char const * const         GrainedSimpleRollingWindowEstimatorName("GrainedSimpleRollingWindowEstimator");

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
    public Components::RollingWindowTransformerBase<InputT, typename Traits<InputT>::nullable_type, MaxNumTrainingItemsV> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::RollingWindowTransformerBase<InputT, typename Traits<InputT>::nullable_type, MaxNumTrainingItemsV>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SimpleRollingWindowTransformer(std::uint32_t windowSize, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowSize = 1);
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
    const SimpleRollingWindowCalculation            _windowCalculation;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
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
    SimpleRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t windowSize, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowSize = 1);
    ~SimpleRollingWindowEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SimpleRollingWindowEstimator);


private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Members
    // |
    // ----------------------------------------------------------------------
    const std::uint32_t                             _windowSize;
    const std::uint32_t                             _horizon;
    const std::uint32_t                             _minWindowSize;
    const SimpleRollingWindowCalculation            _windowCalculation;


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
        return typename BaseType::TransformerUniquePtr(new SimpleRollingWindowTransformer<InputT, MaxNumTrainingItemsV>(_windowSize, _windowCalculation, _horizon, _minWindowSize));
    }

};

/////////////////////////////////////////////////////////////////////////
///  \class       GrainedSimpleRollingWindowEstimator
///  \brief         GrainedTransformer that creates `SimpleRollingWindowEstimator`.
///

template <typename InputT, size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class GrainedSimpleRollingWindowEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::GrainEstimatorImpl<GrainType, SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>>,
        Components::FilterDecoratorEstimator<std::tuple<GrainType const &, std::vector<typename Traits<InputT>::nullable_type>>, 1>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = 
        Components::PipelineExecutionEstimatorImpl<
            Components::GrainEstimatorImpl<GrainType, SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>>,
            Components::FilterDecoratorEstimator<std::tuple<GrainType const &, std::vector<typename Traits<InputT>::nullable_type>>, 1>
        >;
    
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    // MSVC has problems when the definition for the constructor is separated from its declaration.
    GrainedSimpleRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t windowSize, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowSize = 1);
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
SimpleRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::SimpleRollingWindowTransformer(std::uint32_t windowSize, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowSize) :
    BaseType(
        std::move(windowSize),
        [windowCalculation] () -> typename BaseType::CalculatorFunction {
            if (windowCalculation == SimpleRollingWindowCalculation::Min) {
                return [] (typename Components::CircularBuffer<InputT>::iterator begin, typename Components::CircularBuffer<InputT>::iterator end) {
                    return Calculators::MinCalculator<InputT>::execute(begin, end);
                };
            } else {
                return [] (typename Components::CircularBuffer<InputT>::iterator begin, typename Components::CircularBuffer<InputT>::iterator end) {
                    return Calculators::MaxCalculator<InputT>::execute(begin, end);
                };
            }
        }(),
        std::move(horizon),
        std::move(minWindowSize)),
        _windowCalculation(std::move(windowCalculation)) 
    {

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
            std::uint32_t                       minWindowSize(Traits<std::uint32_t>::deserialize(ar));


            return SimpleRollingWindowTransformer(std::move(windowSize), std::move(windowCalculation), std::move(horizon), std::move(minWindowSize));
        }()
    ) {
}

template <typename InputT, size_t MaxNumTrainingItemsV>
bool SimpleRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::operator==(SimpleRollingWindowTransformer const &other) const {
    return this->_windowSize  == other._windowSize && this->_windowCalculation == other._windowCalculation && this->_horizon == other._horizon && this->_minWindowSize == other._minWindowSize;
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
    Traits<std::uint32_t>::serialize(ar, this->_windowSize);
    Traits<std::uint8_t>::serialize(ar, static_cast<std::uint8_t>(_windowCalculation));
    Traits<std::uint32_t>::serialize(ar, this->_horizon);
    Traits<std::uint32_t>::serialize(ar, this->_minWindowSize);

    // Note that we aren't serializing working state
}

// ----------------------------------------------------------------------
// |
// |  SimpleRollingWindowEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>::SimpleRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t windowSize, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowSize) :
    BaseType(SimpleRollingWindowEstimatorName, std::move(pAllColumnAnnotations)),
    _windowSize(std::move(windowSize)),
    _windowCalculation(std::move(windowCalculation)),
    _horizon(std::move(horizon)),
    _minWindowSize(std::move(minWindowSize))
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
    BaseType(
        GrainedSimpleRollingWindowEstimatorName,
        pAllColumnAnnotations,
        [pAllColumnAnnotations, windowSize, windowCalculation, horizon, minWindowCount] () {
            return Components::GrainEstimatorImpl<GrainType, SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>> (
                pAllColumnAnnotations,
                [windowSize, windowCalculation, horizon, minWindowCount](AnnotationMapsPtr pAllColumnAnnotationsParam) {
                    return SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotationsParam), std::move(windowSize), std::move(windowCalculation), std::move(horizon), std::move(minWindowCount));
                }
            );
        },
        [pAllColumnAnnotations]() {
            return Components::FilterDecoratorEstimator<std::tuple<GrainType const &, std::vector<typename Traits<InputT>::nullable_type>>, 1>(std::move(pAllColumnAnnotations));
        }
    ) {
}


} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
