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
///                 Input type is a tuple of std::vector<std::string>, representing grains, and std::double_t, representing target column
///
template <typename InputT>
class LagLeadOperatorTransformer :
    public Transformer<
        InputT,
        Microsoft::Featurizer::RowMajMatrix<std::double_t>
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
            Microsoft::Featurizer::RowMajMatrix<std::double_t>
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
    // TODO: change target type to general types
    using TargetType = std::double_t;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::uint32_t const                     _horizon;
    std::vector<std::int64_t> const         _offsets;
    Components::CircularBuffer<TargetType>  _buffer;
    std::int64_t const                      _max_future_offset;
    std::int64_t                            _index;
    std::uint32_t                           _numPending;
    

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC runs into problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        if (_max_future_offset != 0 && _index <= _max_future_offset + _horizon - 1) {
            ++_index;
            ++_numPending;
            _buffer.push(input);
            return;
        }
        Microsoft::Featurizer::RowMajMatrix<std::double_t> ret(_offsets.size(), _horizon);
        for (std::uint32_t row = 0; row < _offsets.size(); ++row) {
            // col ranges from _horizon - 1 to 0
            for (std::uint32_t col = _horizon - 1; col < _horizon; --col) {
                if ((_index - _numPending - col + _offsets[row] < 0)) {
                    ret(static_cast<std::int32_t>(row), static_cast<std::int32_t>(_horizon - 1 - col)) = std::nan("");
                }
                else {
                    if (_offsets[row] == 0 && col == 0) {
                        ret(static_cast<std::int32_t>(row), static_cast<std::int32_t>(_horizon - 1 - col)) = input;
                    }
                    else {
                        ret(static_cast<std::int32_t>(row), static_cast<std::int32_t>(_horizon - 1 - col)) = *std::get<0>(_buffer.range(
                                                                                        1, 
                                                                                        static_cast<size_t>(static_cast<std::int64_t>(_buffer.size() - _numPending - col) + _offsets[row])
                                                                                      ));
                    }
                }
            }
        }
        _buffer.push(input);
        ++_index;
        callback(ret);
    }

    void flush_impl(typename BaseType::CallbackFunction const & callback) override {
        if (_numPending != 0) {
            while(_numPending) {
                Microsoft::Featurizer::RowMajMatrix<std::double_t> ret(_offsets.size(), _horizon);
                for (std::uint32_t row = 0; row < _offsets.size(); ++row) {
                    // col ranges from _horizon - 1 to 0
                    for (std::uint32_t col = _horizon - 1; col < _horizon; --col) {
                        if (
                            (_index - _numPending - col + _offsets[row] < 0) ||
                            (_numPending <= _offsets[row] - col)) {
                            ret(static_cast<std::int32_t>(row), static_cast<std::int32_t>(_horizon - 1 - col)) = std::nan("");
                        }
                        else {
                            ret(static_cast<std::int32_t>(row), static_cast<std::int32_t>(_horizon - 1 - col)) = *std::get<0>(_buffer.range(
                                                                                                1, 
                                                                                                static_cast<size_t>(static_cast<std::int64_t>(_buffer.size() - _numPending - col) + _offsets[row])
                                                                                              ));
                        }
                    }
                }
                callback(ret);
                _numPending--;
            }
        }
    }
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
    // if there are more than one offset provided, we need find the difference between max and min value to determine buffer size
    // and if there's only one offset, we use the absolute value of it as the size
    _buffer(Components::CircularBuffer<TargetType>(
        horizon +
        (_offsets.size() == 1 ? 
        static_cast<size_t>(std::abs(_offsets[0])) : 
        static_cast<size_t>(*std::max_element(_offsets.cbegin(),_offsets.cend()) - *std::min_element(_offsets.cbegin(),_offsets.cend()))))
    ),
    _max_future_offset(std::move(
        *std::max_element(_offsets.cbegin(), _offsets.cend()) > 0 ?  *std::max_element(_offsets.cbegin(), _offsets.cend()) : 0
    )),
    _index(0),
    _numPending(0) {
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

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
