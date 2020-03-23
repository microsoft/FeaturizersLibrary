// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "Calculators/MeanCalculator.h"
#include "Components/InferenceOnlyFeaturizerImpl.h"
#include "Components/GrainFeaturizerImpl.h"
#include "Components/RollingWindowTransformerBase.h"
#include "Components/WindowFeaturizerBase.h"
#include "../Featurizer.h"
#include "../Traits.h"

#include <vector>

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

static constexpr char const * const         AnalyticalRollingWindowEstimatorName("AnalyticalRollingWindowEstimator");

/////////////////////////////////////////////////////////////////////////
///  \fn            AnalyticalRollingWindowCalculation
///  \brief         Which type of calculation will be performed on the rolling window.
///                 Currently only one of calculation is supported. This will be expanded upon in the future,
///                 so we are peparing by making this an enum from the get go.
///
enum class AnalyticalRollingWindowCalculation : std::uint8_t {
    Mean = 1
};


/////////////////////////////////////////////////////////////////////////
///  \class         AnalyticalRollingWindowTransformer
///  \brief         RollingWindow class that is used for all analytical window computations.
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class AnalyticalRollingWindowTransformer:
    public Components::RollingWindowTransformerBase<InputT, double, MaxNumTrainingItemsV> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::RollingWindowTransformerBase<InputT, double, MaxNumTrainingItemsV>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    AnalyticalRollingWindowTransformer(std::uint32_t windowSize, AnalyticalRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowSize = 1) ;
    AnalyticalRollingWindowTransformer(Archive &ar);
    ~AnalyticalRollingWindowTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(AnalyticalRollingWindowTransformer);

    bool operator==(AnalyticalRollingWindowTransformer const &other) const;
    bool operator!=(AnalyticalRollingWindowTransformer const &other) const;
    void save(Archive & ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Members
    // |
    // ----------------------------------------------------------------------
    const AnalyticalRollingWindowCalculation        _windowCalculation;
};

/////////////////////////////////////////////////////////////////////////
///  \class         AnalyticalRollingWindowEstimator
///  \brief         Estimator that creates `AnalyticalRollingWindowTransformer`.
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class AnalyticalRollingWindowEstimator :
    public TransformerEstimator<InputT, std::vector<double>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, std::vector<double>>;
    using TransformerType                   = AnalyticalRollingWindowTransformer<InputT, MaxNumTrainingItemsV>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    AnalyticalRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t windowSize, AnalyticalRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowCount = 1);
    ~AnalyticalRollingWindowEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(AnalyticalRollingWindowEstimator);


private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Members
    // |
    // ----------------------------------------------------------------------
    const std::uint32_t                           _windowSize;
    const std::uint32_t                           _horizon;
    const std::uint32_t                           _minWindowCount;
    const AnalyticalRollingWindowCalculation      _windowCalculation;


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
        return typename BaseType::TransformerUniquePtr(new AnalyticalRollingWindowTransformer<InputT, MaxNumTrainingItemsV>(_windowSize, _windowCalculation, _horizon, _minWindowCount));
    }

};

/////////////////////////////////////////////////////////////////////////
///  \class       GrainedAnalyticalRollingWindowEstimator
///  \brief         GrainedTransformer that creates `AnalyticalRollingWindowEstimator`.
///

template <typename InputT, size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class GrainedAnalyticalRollingWindowEstimator :
    public Components::GrainEstimatorImpl<std::vector<std::string>, AnalyticalRollingWindowEstimator<InputT, MaxNumTrainingItemsV>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = Components::GrainEstimatorImpl<std::vector<std::string>, AnalyticalRollingWindowEstimator<InputT, MaxNumTrainingItemsV>>;
    
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    GrainedAnalyticalRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t windowSize, AnalyticalRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowCount = 1);
    ~GrainedAnalyticalRollingWindowEstimator(void) override = default;
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
// |  AnalyticalRollingWindowTransformer
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
AnalyticalRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::AnalyticalRollingWindowTransformer(std::uint32_t windowSize, AnalyticalRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowSize) :
    BaseType(
        std::move(windowSize), 
        [] (typename Components::CircularBuffer<InputT>::iterator begin, typename Components::CircularBuffer<InputT>::iterator end) {
            return Calculators::MeanCalculator<InputT>::execute(begin, end);
        },
        std::move(horizon),
        std::move(minWindowSize)),
        _windowCalculation(std::move(windowCalculation))
    {
}

template <typename InputT, size_t MaxNumTrainingItemsV>
AnalyticalRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::AnalyticalRollingWindowTransformer(Archive &ar) :
    AnalyticalRollingWindowTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Because we know that windowSize and minWindowCount come in originally as uint32, this cast is always safe
            std::uint32_t                       windowSize(Traits<std::uint32_t>::deserialize(ar));
            AnalyticalRollingWindowCalculation  windowCalculation(static_cast<AnalyticalRollingWindowCalculation>(Traits<std::uint8_t>::deserialize(ar)));
            std::uint32_t                       horizon(Traits<std::uint32_t>::deserialize(ar));
            std::uint32_t                       minWindowCount(Traits<std::uint32_t>::deserialize(ar));


            return AnalyticalRollingWindowTransformer(std::move(windowSize), std::move(windowCalculation), std::move(horizon), std::move(minWindowCount));
        }()
    ) {
}

template <typename InputT, size_t MaxNumTrainingItemsV>
bool AnalyticalRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::operator==(AnalyticalRollingWindowTransformer const &other) const {
    return this->_windowSize  == other._windowSize && this->_windowCalculation == other._windowCalculation && this->_horizon == other._horizon && this->_minWindowSize == other._minWindowSize;
}

template <typename InputT, size_t MaxNumTrainingItemsV>
bool AnalyticalRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::operator!=(AnalyticalRollingWindowTransformer const &other) const {
    return (*this == other) == false;
}

template <typename InputT, size_t MaxNumTrainingItemsV>
void AnalyticalRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::save(Archive &ar) const /*override*/ {
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
// |  AnalyticalRollingWindowEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
AnalyticalRollingWindowEstimator<InputT, MaxNumTrainingItemsV>::AnalyticalRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t windowSize, AnalyticalRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowCount) :
    BaseType(AnalyticalRollingWindowEstimatorName, std::move(pAllColumnAnnotations)),
    _windowSize(std::move(windowSize)),
    _windowCalculation(std::move(windowCalculation)),
    _horizon(std::move(horizon)),
    _minWindowCount(std::move(minWindowCount))
    {
}

template <typename InputT, size_t MaxNumTrainingItemsV>
bool AnalyticalRollingWindowEstimator<InputT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    // Do not allow any further training
    return false;
}

template <typename InputT, size_t MaxNumTrainingItemsV>
FitResult AnalyticalRollingWindowEstimator<InputT, MaxNumTrainingItemsV>::fit_impl(InputT const *, size_t) /*override*/ {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

template <typename InputT, size_t MaxNumTrainingItemsV>
void AnalyticalRollingWindowEstimator<InputT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

// ----------------------------------------------------------------------
// |
// |  GrainedAnalyticalRollingWindowEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
GrainedAnalyticalRollingWindowEstimator<InputT, MaxNumTrainingItemsV>::GrainedAnalyticalRollingWindowEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t windowSize, AnalyticalRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowCount) :
    BaseType(pAllColumnAnnotations,
             [windowSize, windowCalculation, horizon, minWindowCount](AnnotationMapsPtr pAllColumnAnnotationsParam) {
                 return AnalyticalRollingWindowEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotationsParam), std::move(windowSize), std::move(windowCalculation), std::move(horizon), std::move(minWindowCount));
             })
    {
}


} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
