// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "../Featurizer.h"
#include "../Traits.h"

#include "Base/RollingWindowTransformerBase.h"
#include "Calculators/MaxCalculator.h"
#include "Calculators/MinCalculator.h"
#include "Components/FilterDecoratorFeaturizer.h"
#include "Components/GrainFeaturizerImpl.h"
#include "Components/InferenceOnlyFeaturizerImpl.h"
#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/WindowFeaturizerBase.h"

#include <vector>

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

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
    public Base::RollingWindowTransformerBase<InputT, typename Traits<InputT>::nullable_type, MaxNumTrainingItemsV> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Base::RollingWindowTransformerBase<InputT, typename Traits<InputT>::nullable_type, MaxNumTrainingItemsV>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SimpleRollingWindowTransformer(SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t maxWindowSize, std::uint32_t minWindowSize = 1);
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
    SimpleRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t maxWindowSize, std::uint32_t minWindowSize = 1);
    ~SimpleRollingWindowEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SimpleRollingWindowEstimator);


private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Members
    // |
    // ----------------------------------------------------------------------
    const std::uint32_t                             _horizon;
    const std::uint32_t                             _maxWindowSize;
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
        return typename BaseType::TransformerUniquePtr(new SimpleRollingWindowTransformer<InputT, MaxNumTrainingItemsV>(_windowCalculation, _horizon, _maxWindowSize, _minWindowSize));
    }

};

/////////////////////////////////////////////////////////////////////////
///  \class       GrainedSimpleRollingWindowEstimator
///  \brief         GrainedTransformer that creates `SimpleRollingWindowEstimator`.
///

template <typename InputT, size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class GrainedSimpleRollingWindowEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::GrainEstimatorImpl<std::vector<std::string>, SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>>,
        Components::FilterDecoratorEstimator<std::tuple<std::vector<std::string> const &, std::vector<typename Traits<InputT>::nullable_type>>, 1>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using GrainType = std::vector<std::string>;

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
    GrainedSimpleRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t maxWindowSize, std::uint32_t minWindowSize = 1);
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
SimpleRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::SimpleRollingWindowTransformer(SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t maxWindowSize, std::uint32_t minWindowSize) :
    BaseType(
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
        std::move(maxWindowSize),
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

            SimpleRollingWindowCalculation      windowCalculation(static_cast<SimpleRollingWindowCalculation>(Traits<typename std::underlying_type<SimpleRollingWindowCalculation>::type>::deserialize(ar)));
            std::uint32_t                       horizon(Traits<std::uint32_t>::deserialize(ar));
            std::uint32_t                       maxWindowSize(Traits<std::uint32_t>::deserialize(ar));
            std::uint32_t                       minWindowSize(Traits<std::uint32_t>::deserialize(ar));


            return SimpleRollingWindowTransformer(std::move(windowCalculation), std::move(horizon), std::move(maxWindowSize), std::move(minWindowSize));
        }()
    ) {
}

template <typename InputT, size_t MaxNumTrainingItemsV>
bool SimpleRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::operator==(SimpleRollingWindowTransformer const &other) const {
    return this->_maxWindowSize  == other._maxWindowSize && this->_windowCalculation == other._windowCalculation && this->_horizon == other._horizon && this->_minWindowSize == other._minWindowSize;
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
    Traits<std::uint8_t>::serialize(ar, static_cast<std::uint8_t>(_windowCalculation));
    Traits<std::uint32_t>::serialize(ar, this->_horizon);
    Traits<std::uint32_t>::serialize(ar, this->_maxWindowSize);
    Traits<std::uint32_t>::serialize(ar, this->_minWindowSize);

    // Note that we aren't serializing working state
}

// ----------------------------------------------------------------------
// |
// |  SimpleRollingWindowEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>::SimpleRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t maxWindowSize, std::uint32_t minWindowSize) :
    BaseType(SimpleRollingWindowEstimatorName, std::move(pAllColumnAnnotations)),
    _horizon(
        std::move(
            [&horizon]() -> std::uint32_t & {
                if(horizon < 1)
                    throw std::invalid_argument("horizon");

                return horizon;
            }()
        )
    ),
    _maxWindowSize(
        std::move(
            [&maxWindowSize]() -> std::uint32_t & {
                if(maxWindowSize < 1)
                    throw std::invalid_argument("maxWindowSize");

                return maxWindowSize;
            }()
        )
    ),
    _minWindowSize(
        std::move(
            [this, &minWindowSize]() -> std::uint32_t & {
                if(minWindowSize < 1)
                    throw std::invalid_argument("minWindowSize");
                if(minWindowSize > this->_maxWindowSize)
                    throw std::invalid_argument("minWindowSize must be smaller than maxWindowSize");

                return minWindowSize;
            }()
        )
    ),
    _windowCalculation(std::move(windowCalculation))
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
GrainedSimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>::GrainedSimpleRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, SimpleRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t maxWindowSize, std::uint32_t minWindowCount) :
    BaseType(
        GrainedSimpleRollingWindowEstimatorName,
        pAllColumnAnnotations,
        [pAllColumnAnnotations, maxWindowSize, windowCalculation, horizon, minWindowCount] () {
            return Components::GrainEstimatorImpl<GrainType, SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>> (
                pAllColumnAnnotations,
                [maxWindowSize, windowCalculation, horizon, minWindowCount](AnnotationMapsPtr pAllColumnAnnotationsParam) {
                    return SimpleRollingWindowEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotationsParam), std::move(windowCalculation), std::move(horizon), std::move(maxWindowSize), std::move(minWindowCount));
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
