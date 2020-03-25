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

static constexpr char const * const         LagLeadOperatorEstimatorName("LagLeadOperatorEstimator");
static constexpr char const * const         GrainedLagLeadOperatorEstimatorName("GrainedLagLeadOperatorEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         LagLeadOperatorTransformer
///  \brief         Copy values from prior data or future data
///                 Input type is InputT, representing target column
///
template <typename InputT>
class LagLeadOperatorTransformer :
    public Transformer<
        InputT,
        Microsoft::Featurizer::RowMajMatrix<typename Microsoft::Featurizer::Traits<InputT>::nullable_type>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TransformedTargetType = typename Microsoft::Featurizer::Traits<InputT>::nullable_type;

    using BaseType =
        Transformer<
            InputT,
            Microsoft::Featurizer::RowMajMatrix<TransformedTargetType>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    LagLeadOperatorTransformer(std::uint32_t horizon, std::vector<std::int64_t> deltas);
    LagLeadOperatorTransformer(Archive &ar);

    ~LagLeadOperatorTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(LagLeadOperatorTransformer);

    bool operator==(LagLeadOperatorTransformer const &other) const;
    bool operator!=(LagLeadOperatorTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::uint32_t              const                   _horizon;
    std::int64_t               const                   _offset_delta;
    std::vector<std::uint32_t> const                   _offsets;
    Components::CircularBuffer<TransformedTargetType>  _buffer;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    // MSVC runs into problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        execute_helper(TransformedTargetType(input), callback);
    }

    void flush_impl(typename BaseType::CallbackFunction const & callback) override {
        std::int64_t max_future_delta(_offset_delta + static_cast<std::int64_t>(*std::max_element(_offsets.cbegin(), _offsets.cend())));
        bool const has_future_delta(max_future_delta > 0);

        if (has_future_delta) {
            // more null values are pushed in to ensure we get all results for every input received
            while (max_future_delta--) {
                execute_helper(Traits<TransformedTargetType>::CreateNullValue(), callback);
            }
        }

        // after flush is called, this transfomer should be reset to its starting state
        _buffer.clear();

        init_buffer();
    }

    void execute_helper(TransformedTargetType const &input, typename BaseType::CallbackFunction const &callback);

    void init_buffer();
};

/////////////////////////////////////////////////////////////////////////
///  \class         LagLeadOperatorEstimator
///  \brief         Estimator that creates `LagLeadOperatorTransformer`.
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class LagLeadOperatorEstimator :
    public TransformerEstimator<InputT, Microsoft::Featurizer::RowMajMatrix<typename Microsoft::Featurizer::Traits<InputT>::nullable_type>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, Microsoft::Featurizer::RowMajMatrix<typename Microsoft::Featurizer::Traits<InputT>::nullable_type>>;
    using TransformerType                   = LagLeadOperatorTransformer<InputT>;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    LagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, std::vector<std::int64_t> deltas);

    ~LagLeadOperatorEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(LagLeadOperatorEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Members
    // |
    // ----------------------------------------------------------------------
    std::uint32_t             const                    _horizon;
    std::vector<std::int64_t> const                    _deltas;

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
        return typename BaseType::TransformerUniquePtr(new LagLeadOperatorTransformer<InputT>(_horizon, _deltas));
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class       GrainedLagLeadOperatorEstimator
///  \brief       GrainedTransformer that creates `LagLeadOperatorEstimator`.
///
template <typename InputT, size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class GrainedLagLeadOperatorEstimator :
    public Components::GrainEstimatorImpl<std::vector<std::string>, LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = Components::GrainEstimatorImpl<std::vector<std::string>, LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    GrainedLagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, std::vector<std::int64_t> deltas);
    ~GrainedLagLeadOperatorEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(GrainedLagLeadOperatorEstimator);
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
// |  LagLeadOperatorTransformer
// |
// ----------------------------------------------------------------------
template <typename T>
LagLeadOperatorTransformer<T>::LagLeadOperatorTransformer(std::uint32_t horizon, std::vector<std::int64_t> deltas) :
    _horizon(
        std::move(
            [&horizon](void) -> std::uint32_t & {
                if (horizon == 0) {
                    throw std::invalid_argument("Horizon cannot be 0!");
                }
                return horizon;
            }()
    )),
    // value applied to each delta so that we can produce indices to a 0-based buffer
    _offset_delta(
        // TODO: change it to positive
        std::move(
            [&deltas](void) -> std::int64_t {
                if (deltas.size() == 0) {
                    throw std::invalid_argument("Lag lead orders is empty!");
                }
                // if all deltas are positive, the offset_delta should be 0 because deltas are already the indices to the 0-based buffer
                return std::min(*std::min_element(deltas.cbegin(), deltas.cend()), static_cast<std::int64_t>(0));
            }()
        )
    ),
    // apply offset_delta to deltas to get indices to the 0-based buffer
    _offsets(
        std::move(
            [this, &deltas](void) -> std::vector<std::uint32_t> {
                std::vector<std::uint32_t> ret;
                ret.reserve(deltas.size());

                for (std::int64_t const & delta : deltas) {
                    ret.emplace_back(static_cast<std::uint32_t>(delta - _offset_delta));
                }

                return ret;
            }()
        )
    ),
    //
    _buffer(
        _horizon +
        [this](void) -> size_t {
            // largest value of indices
            std::uint32_t const max_delta(*std::max_element(deltas.cbegin(), deltas.cend()));
            std::uint32_t const min_delta(*std::min_element(deltas.cbegin(), deltas.cend()));

            if (max_delta < 0) {
                return -min_delta;
            }
            else if (min_delta >= 0) {
                return max_delta;
            }
            // some are in the past, some are in the future
            return max_delta - min_delta;
        } ()
    ) {
        // init_buffer circular buffer with null values to imitate non-existing prior rows
        init_buffer();
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
            std::vector<std::int64_t> deltas = Traits<std::vector<std::int64_t>>::deserialize(ar);

            return LagLeadOperatorTransformer(std::move(horizon), std::move(deltas));
        }()
    ) {
}

template <typename T>
bool LagLeadOperatorTransformer<T>::operator==(LagLeadOperatorTransformer const &other) const {
    return this->_horizon == other._horizon && this->_offset_delta == other._offset_delta
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

    // reset _offsets to delta
    std::vector<std::int64_t> deltas;
    for (auto it = _offsets.begin(); it != _offsets.end(); it++) {
        deltas.emplace_back(*it + _offset_delta);
    }
    Traits<std::vector<std::int64_t>>::serialize(ar, deltas);

    // Note that we aren't serializing working state
}

template <typename T>
void LagLeadOperatorTransformer<T>::execute_helper(TransformedTargetType const &input, typename BaseType::CallbackFunction const &callback) {
    _buffer.push(input);
    // until the circular buffer is full, we don't have enough data to generate output matrix
    if (!_buffer.is_full()) {
        return;
    }
    typename BaseType::TransformedType ret(_offsets.size(), _horizon);

    for (std::uint32_t row = 0; row < _offsets.size(); ++row) {                                                                                                                              1, 3  0, 2 0  [*, *, *]
        std::tuple<typename Components::CircularBuffer<TransformedTargetType>::iterator, typename Components::CircularBuffer<TransformedTargetType>::iterator> range{_buffer.range(_horizon, _deltas[row] - delta_offset)};
        typename Components::CircularBuffer<TransformedTargetType>::iterator start_iter = std::get<0>(range);

        for (std::int32_t col = 0; col < static_cast<std::int32_t>(_horizon); ++col) {
            ret(static_cast<std::int32_t>(row), col) = *start_iter;
            ++start_iter;
        }
    }

    callback(std::move(ret));
}

template <typename T>
void LagLeadOperatorTransformer<T>::init_buffer() {
    min

    for (std::int64_t i = 0; i < (static_cast<std::int64_t>(_horizon) - _offset_delta - 1); ++i) {
        _buffer.push(Traits<TransformedTargetType>::CreateNullValue());
    }
}

// ----------------------------------------------------------------------
// |
// |  LagLeadOperatorEstimator
// |
// ----------------------------------------------------------------------

template <typename InputT, size_t MaxNumTrainingItemsV>
LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>::LagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, std::vector<std::int64_t> deltas) :
    BaseType(LagLeadOperatorEstimatorName, std::move(pAllColumnAnnotations)),
    _horizon(
        std::move(
            [&horizon](void) -> std::uint32_t & {
                if (horizon == 0) {
                    throw std::invalid_argument("Horizon cannot be 0!");
                }
                return horizon;
            }()
        )
    ),
    _deltas(
        std::move(
            [&deltas](void) -> std::vector<std::int64_t> & {
                if (deltas.size() == 0) {
                    throw std::invalid_argument("Lag lead orders is empty!");
                }
                return deltas;
            }()
        )
    ) {
}

template <typename InputT, size_t MaxNumTrainingItemsV>
bool LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    // Do not allow any further training
    return false;
}

template <typename InputT, size_t MaxNumTrainingItemsV>
FitResult LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>::fit_impl(InputT const *, size_t) /*override*/ {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

template <typename InputT, size_t MaxNumTrainingItemsV>
void LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}


// ----------------------------------------------------------------------
// |
// |  GrainedLagLeadOperatorEstimator
// |
// ----------------------------------------------------------------------

template <typename InputT, size_t MaxNumTrainingItemsV>
GrainedLagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>::GrainedLagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, std::vector<std::int64_t> deltas) :
    BaseType(
        pAllColumnAnnotations,
        [horizon, deltas](AnnotationMapsPtr pAllColumnAnnotationsParam) {
            return LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotationsParam), horizon, deltas);
        }
    ) {
}


} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
