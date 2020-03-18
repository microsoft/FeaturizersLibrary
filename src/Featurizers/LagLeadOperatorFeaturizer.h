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
///
template <typename InputTupleT>
class LagLeadOperatorTransformer :
    public Transformer<
        InputTupleT,
        Microsoft::Featurizer::ColMajMatrix<std::double_t>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Components::Details::IsTuple<InputTupleT>::value, "'InputTupleT' must be a tuple");

    using BaseType =
        Transformer<
            InputTupleT,
            Microsoft::Featurizer::ColMajMatrix<std::double_t>
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
    Components::CircularBuffer<TargetType>  _buffer;
    std::int64_t const                      _max_future_offset;
    std::int64_t const                      _max_prior_offset;
    std::uint32_t const                     _horizon;
    std::vector<std::int64_t> const         _offsets;
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
            _buffer.push(std::get<1>(input));
            return;
        }
        Microsoft::Featurizer::ColMajMatrix<std::double_t> ret(_offsets.size(), _horizon);
        for (std::uint32_t col = 0; col < _horizon; ++col) {
            for (size_t row = 0; row < _offsets.size(); ++row) {
                if ((_index - _numPending - (_horizon - 1 - col) + _offsets[row] < 0)) {
                    ret(static_cast<long long>(row), col) = std::nan("");
                }
                else {
                    ret(static_cast<long long>(row), col) = *std::get<0>(_buffer.range(
                                                                                        1, 
                                                                                        static_cast<size_t>(static_cast<long long>(_buffer.size() - _numPending - (_horizon - 1 - col)) + _offsets[row])
                                                                                      ));
                }
            }
        }
        _buffer.push(std::get<1>(input));
        ++_index;
        callback(ret);
    }

    void flush_impl(typename BaseType::CallbackFunction const & callback) override {
        if (_numPending != 0) {
            while(_numPending) {
                Microsoft::Featurizer::ColMajMatrix<std::double_t> ret(_offsets.size(), _horizon);
                for (std::uint32_t col = 0; col < _horizon; ++col) {
                    for (size_t row = 0; row < _offsets.size(); ++row) {
                        if (
                            (_index - _numPending - (_horizon - 1 - col) + _offsets[row] < 0) ||
                            (_numPending <= _offsets[row] - (_horizon - 1 - col))) {
                            ret(static_cast<long long>(row), col) = std::nan("");
                        }
                        else {
                            ret(static_cast<long long>(row), col) = *std::get<0>(_buffer.range(
                                                                                                1, 
                                                                                                static_cast<size_t>(static_cast<long long>(_buffer.size() - _numPending - (_horizon - 1 - col)) + _offsets[row])
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
template <typename InputTupleT>
using LagLeadOperatorEstimator           = Components::InferenceOnlyEstimatorImpl<LagLeadOperatorTransformer<InputTupleT>>;

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
    // if there are more than one offset provided, we need find the difference between max and min value to determine buffer size
    // and if there's only one offset, we use the absolute value of it as the size
    _buffer(Components::CircularBuffer<TargetType>(horizon +
        (offsets.size() == 1 ? 
        static_cast<size_t>(std::abs(offsets[0])) : 
        static_cast<size_t>(*std::max_element(offsets.cbegin(),offsets.cend()) - *std::min_element(offsets.cbegin(),offsets.cend()))))
    ),
    _max_future_offset(std::move(
        *std::max_element(offsets.cbegin(), offsets.cend()) > 0 ?  *std::max_element(offsets.cbegin(), offsets.cend()) : 0
    )),
    _max_prior_offset(std::move(
        *std::min_element(offsets.cbegin(), offsets.cend()) < 0 ?  -(*std::min_element(offsets.cbegin(), offsets.cend())) : 0
    )),
    _horizon(std::move(horizon)),
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
