// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Featurizer.h"
#include "../Archive.h"
#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/FilterDecoratorFeaturizer.h"
#include "Components/GrainFeaturizerImpl.h"
#include "Components/WindowFeaturizerBase.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         LagLeadOperatorTransformer
///  \brief         Copy values from prior data or future data
///                 Input type is a tuple of std::vector<std::string>, representing grains, and InputT, representing target column
///
template <typename InputT>
class LagLeadOperatorTransformer :
    public Transformer<
        InputT,
        Microsoft::Featurizer::RowMajMatrix<nonstd::optional<InputT>>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------

    using BaseType =
        Transformer<
            InputT,
            Microsoft::Featurizer::RowMajMatrix<nonstd::optional<InputT>>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    LagLeadOperatorTransformer(std::uint32_t horizon, std::vector<std::int64_t> offsets);
    LagLeadOperatorTransformer(Archive &ar);

    ~LagLeadOperatorTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(LagLeadOperatorTransformer);

    bool operator==(LagLeadOperatorTransformer const &other) const;
    bool operator!=(LagLeadOperatorTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using GrainType  = std::vector<std::string>;
    using TargetType = nonstd::optional<InputT>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::uint32_t const                     _horizon;
    std::vector<std::int64_t> const         _offsets;
    std::int64_t const                      _max_future_offset;
    std::int64_t const                      _max_prior_offset;
    Components::CircularBuffer<TargetType>  _buffer;
    

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    // MSVC runs into problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        execute_helper(nonstd::optional<typename BaseType::InputType>(input), callback);
    }

    void flush_impl(typename BaseType::CallbackFunction const & callback) override {
        std::int64_t _numPending = 0;
        while (_numPending < _max_future_offset) {
            execute_helper(Traits<nonstd::optional<InputT>>::CreateNullValue(), callback);
            ++_numPending;
        }
    }

    void execute_helper(nonstd::optional<typename BaseType::InputType> const &input, typename BaseType::CallbackFunction const &callback);
};

/////////////////////////////////////////////////////////////////////////
///  \typedef       LagLeadOperatorEstimator
///  \brief         Estimator that creates `LagLeadOperatorTransformer`.
///
template <typename InputT>
using LagLeadOperatorEstimator           = Components::InferenceOnlyEstimatorImpl<LagLeadOperatorTransformer<InputT>>;

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Implementation
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename T>
LagLeadOperatorTransformer<T>::LagLeadOperatorTransformer(std::uint32_t horizon, std::vector<std::int64_t> offsets) :
    _horizon(
        std::move(
            [&horizon](void) -> std::uint32_t & {
                if (horizon == 0) {
                    throw std::invalid_argument("Horizon cannot be 0!");
                }
                return horizon;
            }()
    )),
    _offsets(
        std::move(
            [&offsets](void) -> std::vector<std::int64_t> & {
                if (offsets.size() == 0) {
                    throw std::invalid_argument("Offsets is empty!");
                }
                return offsets;
            }()
        )
    ),
    _max_future_offset(std::move(
        *std::max_element(_offsets.cbegin(), _offsets.cend()) > 0 ?  *std::max_element(_offsets.cbegin(), _offsets.cend()) : 0
    )),
    _max_prior_offset(std::move(
        *std::min_element(_offsets.cbegin(), _offsets.cend()) < 0 ?  *std::min_element(_offsets.cbegin(), _offsets.cend()) : 0
    )),
    // if there are more than one offset provided, we need find the difference between max and min value to determine buffer size
    // and if there's only one offset, we use the absolute value of it as the size
    _buffer(
        _horizon + 
        (_offsets.size() == 1 ? 
        static_cast<size_t>(std::abs(_offsets[0])) : 
        static_cast<size_t>(_max_future_offset-_max_prior_offset))
    ) {
        // prepopulate circular buffer with null values to imitate non-existing prior rows
        for (std::int64_t i = 0; i < (static_cast<std::int64_t>(_horizon) - _max_prior_offset - 1); ++i) {
            _buffer.push(Traits<nonstd::optional<T>>::CreateNullValue());
        }
}

template <typename T>
LagLeadOperatorTransformer<T>::LagLeadOperatorTransformer(Archive &ar) :
    LagLeadOperatorTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            std::uint32_t horizon = Traits<std::uint32_t>::deserialize(ar);
            std::vector<std::int64_t> offsets = Traits<std::vector<std::int64_t>>::deserialize(ar);
            
            return LagLeadOperatorTransformer(std::move(horizon), std::move(offsets));
        }()
    ) {
}

template <typename T>
bool LagLeadOperatorTransformer<T>::operator==(LagLeadOperatorTransformer const &other) const {
    return this->_horizon == other._horizon
            && this->_offsets == other._offsets;
}

template <typename T>
bool LagLeadOperatorTransformer<T>::operator!=(LagLeadOperatorTransformer const &other) const {
    return (*this == other) == false;
}

template <typename T>
void LagLeadOperatorTransformer<T>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<std::uint32_t>::serialize(ar, _horizon);
    Traits<std::vector<std::int64_t>>::serialize(ar, _offsets);

    // Note that we aren't serializing working state
}

template <typename T>
void LagLeadOperatorTransformer<T>::execute_helper(nonstd::optional<typename BaseType::InputType> const &input, typename BaseType::CallbackFunction const &callback) {
    _buffer.push(input);
    // until the circular buffer is full, we don't have enough data to generate output matrix
    if (_buffer.is_full()) {
        Microsoft::Featurizer::RowMajMatrix<nonstd::optional<T>> ret(_offsets.size(), _horizon);
        for (std::uint32_t row = 0; row < _offsets.size(); ++row) {
            // the circular buffer starts with the needed data for the _max_prior_offset
            // so the difference between offsets[row] and _max_prior_offset is the position to find the data to copy
            std::tuple<typename Components::CircularBuffer<TargetType>::iterator, typename Components::CircularBuffer<TargetType>::iterator> range = _buffer.range(_horizon, static_cast<size_t>(_offsets[row] - _max_prior_offset));
            typename Components::CircularBuffer<TargetType>::iterator start_iter = std::get<0>(range);
            for (std::int32_t col = 0; col < static_cast<std::int32_t>(_horizon); ++col) {
                ret(static_cast<std::int32_t>(row), col) = *start_iter;
                ++start_iter;
            }
        }
        callback(ret);
    }
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
