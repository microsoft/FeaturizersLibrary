// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Archive.h"
#include "Calculators/Calculators.h"
#include "Components/InferenceOnlyFeaturizerImpl.h"
#include "Components/WindowFeaturizerBase.h"
#include "../Featurizer.h"
#include "../Traits.h"

#include <vector>

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

/////////////////////////////////////////////////////////////////////////
///  \class         RollingWindowTransformerBase
///  \brief         RollingWindow class that is used for all analytical window computations.
///                 This class does not have an archive constructor or a save method as those need
///                 to be implemented by the derived classes.
///
template <
    typename InputT,
    typename OutputT,
    size_t MaxNumTrainingItemsV
>
class RollingWindowTransformerBase:
    public Components::InferenceOnlyTransformerImpl<InputT, std::vector<OutputT>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::InferenceOnlyTransformerImpl<InputT, std::vector<OutputT>>;
    using CalculatorFunctionInputType = typename Components::CircularBuffer<InputT>::iterator;
    using CalculatorFunction = std::function<typename OutputT(typename CalculatorFunctionInputType, typename CalculatorFunctionInputType)>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    RollingWindowTransformerBase(std::uint32_t windowSize, CalculatorFunction calculator, std::uint32_t horizon, std::uint32_t minWindowSize) ;
    ~RollingWindowTransformerBase(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(RollingWindowTransformerBase);

    bool operator==(RollingWindowTransformerBase const &other) const;
    bool operator!=(RollingWindowTransformerBase const &other) const;

protected:
    // ----------------------------------------------------------------------
    // |
    // |  Protected Members
    // |
    // ----------------------------------------------------------------------
    // These are protected so that the derived classes can use them for saving of state.
    const std::uint32_t                             _windowSize;
    const std::uint32_t                             _horizon;
    const std::uint32_t                             _minWindowSize;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Members
    // |
    // ----------------------------------------------------------------------
    Components::CircularBuffer<InputT>              _buffer;
    CalculatorFunction                              _calculator;

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

        OutputT result;
        size_t numElements;
        size_t startingOffset;

        for (std::uint32_t offset = 0; offset < _horizon; ++offset){

            // If we don't have enough elements then output NaN
            if ((_horizon - offset) + _minWindowSize > bufferSize) {
                result = Traits<OutputT>::CreateNullValue();

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

                result = _calculator(start_iter, end_iter);

            }

            results[offset] = result;
        }

        callback(results);
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
// |  RollingWindowTransformerBase
// |
// ----------------------------------------------------------------------
template <typename InputT, typename OutputT, size_t MaxNumTrainingItemsV>
RollingWindowTransformerBase<InputT, OutputT, MaxNumTrainingItemsV>::RollingWindowTransformerBase(std::uint32_t windowSize, CalculatorFunction calculator, std::uint32_t horizon, std::uint32_t minWindowSize) :
    _windowSize(
        std::move(
            [this, &windowSize]() -> std::uint32_t & {
                if(windowSize < 1)
                    throw std::invalid_argument("windowSize");

                return windowSize;
            }()
        )),
    _calculator(std::move(calculator)),
    _horizon(
        std::move(
            [this, &horizon]() -> std::uint32_t & {
                if(horizon < 1)
                    throw std::invalid_argument("horizon");

                return horizon;
            }()
        )
    ),
    _minWindowSize(
        std::move(
            [this, &minWindowSize]() -> std::uint32_t & {
                if(minWindowSize < 1)
                    throw std::invalid_argument("minWindowSize");

                return minWindowSize;
            }()
        )
    ),
    _buffer(horizon + windowSize) {

}

template <typename InputT, typename OutputT, size_t MaxNumTrainingItemsV>
bool RollingWindowTransformerBase<InputT, OutputT, MaxNumTrainingItemsV>::operator==(RollingWindowTransformerBase const &other) const {
    return _windowSize  == other._windowSize && _calculator == other._calculator && _horizon == other._horizon && _minWindowSize == other._minWindowSize;
}

template <typename InputT, typename OutputT, size_t MaxNumTrainingItemsV>
bool RollingWindowTransformerBase<InputT, OutputT, MaxNumTrainingItemsV>::operator!=(RollingWindowTransformerBase const &other) const {
    return (*this == other) == false;
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
