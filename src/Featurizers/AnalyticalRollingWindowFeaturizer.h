// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "Calculators/MeanCalculator.h"
#include "Components/InferenceOnlyFeaturizerImpl.h"
#include "Components/WindowFeaturizerBase.h"
#include "Components/GrainFeaturizerImpl.h"
#include "../Traits.h"

#include <vector>

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

static constexpr char const * const         AnalyticalRollingWindowTransformerName("AnalyticalRollingWindowTransformer");

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
///  \class         RollingWindowTransformer
///  \brief         RollingWindow class that is used for all analytical window computations.
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class AnalyticalRollingWindowTransformer:
    public Components::InferenceOnlyTransformerImpl<InputT, std::vector<double>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::InferenceOnlyTransformerImpl<InputT, std::vector<double>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Members
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     Name = AnalyticalRollingWindowTransformerName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    AnalyticalRollingWindowTransformer(std::uint32_t windowSize, AnalyticalRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowCount = 1) ;
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
    Components::CircularBuffer<InputT>      _buffer;
    std::uint32_t                           _windowSize;
    std::uint32_t                           _horizon;
    std::uint32_t                           _minWindowCount;
    AnalyticalRollingWindowCalculation      _windowCalculation;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC runs into problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        std::vector<double>         results(_horizon);
        
        _buffer.push(input);
        size_t bufferSize = _buffer.size();

        for (int i = _horizon; i > 0; i--){
            // TODO: Fix casting here.
            int elementsAvailableToUse(static_cast<int>(bufferSize) - i);

            // If we don't have enough elements then output NaN
            if (elementsAvailableToUse < static_cast<int>(_minWindowCount)) {
                results[_horizon - i] = std::nan("1");

            // If we have strictly less elements then the window size, but more then the minimum size
            } else if (elementsAvailableToUse < static_cast<int>(_windowSize)) {
                const auto range = _buffer.range(_windowSize - elementsAvailableToUse);
                auto start_iter = std::get<0>(range);
                auto end_iter = std::get<1>(range);

                results[_horizon - i] = Calculators::MeanCalculator<BaseType::InputType>::execute(start_iter, end_iter);

            // More elements in the buffer than are needed in the window
            } else {
                const auto range = _buffer.range(_windowSize, bufferSize - i - _windowSize);
                auto start_iter = std::get<0>(range);
                auto end_iter = std::get<1>(range);

                results[_horizon - i] = Calculators::MeanCalculator<BaseType::InputType>::execute(start_iter, end_iter);
            }
        }

        callback(results);
    }
};

/////////////////////////////////////////////////////////////////////////
///  \typedef       AnalyticalRollingWindowEstimator
///  \brief         Estimator that creates `AnalyticalRollingWindowTransformer`.
///
template <typename InputT, size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
using AnalyticalRollingWindowEstimator           = Components::InferenceOnlyEstimatorImpl<AnalyticalRollingWindowTransformer<InputT, MaxNumTrainingItemsV>>;

/////////////////////////////////////////////////////////////////////////
///  \typedef       GrainedAnalyticalRollingWindowEstimator
///  \brief         GrainedTransformer that creates `AnalyticalRollingWindowEstimator`.
///
// Normally we want the featurizer name at the top of the file, but GrainFeaturizers are just type defs, so we want the name next to it.
static constexpr char const * const         AnalyticalRollingWindowEstimatorName("AnalyticalRollingWindowEstimator");

template <typename InputT, size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
using GrainedAnalyticalRollingWindowEstimator = Components::GrainEstimatorImpl<std::vector<std::string>, AnalyticalRollingWindowEstimator<InputT, MaxNumTrainingItemsV>>;

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
AnalyticalRollingWindowTransformer<InputT, MaxNumTrainingItemsV>::AnalyticalRollingWindowTransformer(std::uint32_t windowSize, AnalyticalRollingWindowCalculation windowCalculation, std::uint32_t horizon, std::uint32_t minWindowCount) :
    _windowSize(std::move(windowSize)),
    _windowCalculation(std::move(windowCalculation)),
    _horizon(std::move(horizon)),
    _minWindowCount(std::move(minWindowCount)),
    _buffer(horizon + (windowSize)) {

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
    return _windowSize  == other._windowSize && _windowCalculation == other._windowCalculation && _horizon == other._horizon && _minWindowCount == other._minWindowCount;
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
    Traits<std::uint32_t>::serialize(ar, _windowSize);
    Traits<std::uint8_t>::serialize(ar, static_cast<std::uint8_t>(_windowCalculation));
    Traits<std::uint32_t>::serialize(ar, _horizon);
    Traits<std::uint32_t>::serialize(ar, _minWindowCount);

    // Note that we aren't serializing working state
}


} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
