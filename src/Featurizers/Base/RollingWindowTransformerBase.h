// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Components/InferenceOnlyFeaturizerImpl.h"
#include "../Components/WindowFeaturizerBase.h"
#include "../../Featurizer.h"
#include "../../Traits.h"

#include <vector>

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Base {

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
    using CalculatorFunction = std::function<OutputT(CalculatorFunctionInputType, CalculatorFunctionInputType)>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    RollingWindowTransformerBase(std::uint32_t maxWindowSize, CalculatorFunction calculator, std::uint32_t horizon, std::uint32_t minWindowSize) ;
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
    const std::uint32_t                             _maxWindowSize;
    const std::uint32_t                             _minWindowSize;
    const std::uint32_t                             _horizon;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Members
    // |
    // ----------------------------------------------------------------------
    CalculatorFunction                              _calculator;
    Components::CircularBuffer<InputT>              _buffer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC runs into problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        _buffer.push(input);
        const size_t bufferSize = _buffer.size();

        typename BaseType::TransformedType         results(_horizon);

        for (std::uint32_t offset = 0; offset < _horizon; ++offset){
            OutputT result;
            
            // If we don't have enough elements then output NaN
            if (bufferSize < _horizon - offset + _minWindowSize) {
                result = Traits<OutputT>::CreateNullValue();

            } else {
                // If we have strictly less elements then the window size, but more then the minimum size
                size_t numElements;
                size_t startingOffset;

                if (bufferSize < _maxWindowSize + _horizon - offset) { ///bufferSize - (_horizon - offset) < _maxWindowSize)
                    numElements = bufferSize - (_horizon - offset);
                    startingOffset = 0;
                } else {
                    numElements = _maxWindowSize;
                    startingOffset = offset - (_buffer.capacity() - bufferSize);
                }

                const std::tuple<typename Components::CircularBuffer<InputT>::iterator, typename Components::CircularBuffer<InputT>::iterator> range(_buffer.range(numElements, startingOffset));
                const typename Components::CircularBuffer<InputT>::iterator start_iter(std::get<0>(range));
                const typename Components::CircularBuffer<InputT>::iterator end_iter(std::get<1>(range));

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
RollingWindowTransformerBase<InputT, OutputT, MaxNumTrainingItemsV>::RollingWindowTransformerBase(std::uint32_t maxWindowSize, CalculatorFunction calculator, std::uint32_t horizon, std::uint32_t minWindowSize) :
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
    _horizon(
        std::move(
            [&horizon]() -> std::uint32_t & {
                if(horizon < 1)
                    throw std::invalid_argument("horizon");

                return horizon;
            }()
        )
    ),
    _calculator(std::move(calculator)),
    _buffer(horizon + maxWindowSize) {

}

template <typename InputT, typename OutputT, size_t MaxNumTrainingItemsV>
bool RollingWindowTransformerBase<InputT, OutputT, MaxNumTrainingItemsV>::operator==(RollingWindowTransformerBase const &other) const {
    return _maxWindowSize  == other._maxWindowSize && _calculator == other._calculator && _horizon == other._horizon && _minWindowSize == other._minWindowSize;
}

template <typename InputT, typename OutputT, size_t MaxNumTrainingItemsV>
bool RollingWindowTransformerBase<InputT, OutputT, MaxNumTrainingItemsV>::operator!=(RollingWindowTransformerBase const &other) const {
    return (*this == other) == false;
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
