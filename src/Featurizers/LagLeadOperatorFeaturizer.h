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
    std::uint32_t              const                   _offset_delta;
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
        std::int64_t max_future_delta(get_max_delta());

        if (max_future_delta > 0) {
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

    std::int64_t get_min_delta();

    std::int64_t get_max_delta();
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
    template <typename DeltasInputIteratorRangeT>
    LagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, DeltasInputIteratorRangeT deltas);
    LagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, std::vector<int64_t> deltas);

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
    using GrainType = std::vector<std::string>;

    using BaseType = Components::GrainEstimatorImpl<GrainType, LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    template <typename DeltasInputIteratorRangeT>
    GrainedLagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, DeltasInputIteratorRangeT deltas);
    GrainedLagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, std::vector<int64_t> deltas);
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
        std::move(
            [&deltas](void) -> std::uint32_t {
                if (deltas.empty()) {
                    throw std::invalid_argument("Lag lead orders is empty!");
                }
                // if all deltas are positive, the offset_delta should be 0 because deltas are already the indices to the 0-based buffer
                return static_cast<std::uint32_t>(-std::min(*std::min_element(deltas.cbegin(), deltas.cend()), static_cast<std::int64_t>(0)));
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
                    ret.emplace_back(static_cast<std::uint32_t>(delta + _offset_delta));
                }

                return ret;
            }()
        )
    ),
    // the buffer size should be at least horizon because we need the current row and to look back at least horizon-1 rows
    // in addition to horizon, we need to have more data cached to find the correct data to copy according to input deltas
    _buffer(
        _horizon +
        [&deltas](void) -> size_t {
            std::int64_t const max_delta(*std::max_element(deltas.cbegin(), deltas.cend()));
            std::int64_t const min_delta(*std::min_element(deltas.cbegin(), deltas.cend()));

            if (max_delta < 0) {
                return static_cast<size_t>(-min_delta);
            }
            else if (min_delta >= 0) {
                return static_cast<size_t>(max_delta);
            }
            // some deltas are in the past while some are in the future
            return static_cast<size_t>(max_delta - min_delta);
        } ()
    ) {
        // initialize circular buffer with null values to imitate non-existing prior rows
        init_buffer();
}

template <typename T>
LagLeadOperatorTransformer<T>::LagLeadOperatorTransformer(Archive &ar) :
    LagLeadOperatorTransformer(
        [&ar](void) {
            // Version
            std::uint16_t             majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t             minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            std::uint32_t             horizon = Traits<std::uint32_t>::deserialize(ar);
            std::vector<std::int64_t> deltas  = Traits<std::vector<std::int64_t>>::deserialize(ar);

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

    // revert _offsets to delta
    std::vector<std::int64_t> deltas;
    for (std::uint32_t offset : _offsets) {
        deltas.emplace_back(static_cast<std::int64_t>(offset) - static_cast<std::int64_t>(_offset_delta));
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

    for (std::uint32_t row = 0; row < _offsets.size(); ++row) {
        // the data we try to copy is continuous in the buffer as horizon ranges from N to 1
        // so we can copy N number of data from the buffer every time
        std::tuple<typename Components::CircularBuffer<TransformedTargetType>::iterator, typename Components::CircularBuffer<TransformedTargetType>::iterator> range(_buffer.range(_horizon, _offsets[row]));
        typename Components::CircularBuffer<TransformedTargetType>::iterator start_iter(std::get<0>(range));

        for (std::int32_t col = 0; col < static_cast<std::int32_t>(_horizon); ++col) {
            ret(static_cast<std::int32_t>(row), col) = *start_iter;
            ++start_iter;
        }
    }

    callback(std::move(ret));
}

template <typename T>
void LagLeadOperatorTransformer<T>::init_buffer() {
    std::int64_t const min_delta(get_min_delta());

    // at least push in horizon -1 nulls to imitate non-existing prior data input
    for (std::int64_t i = 0; i < (static_cast<std::int64_t>(_horizon) - 1); ++i) {
        _buffer.push(Traits<TransformedTargetType>::CreateNullValue());
    }

    // push more nulls if we need to look for more prior rows
    if (min_delta < 0) {
        for (std::int64_t i = 0; i < -min_delta; ++i) {
            _buffer.push(Traits<TransformedTargetType>::CreateNullValue());
        }
    }
}

template <typename T>
std::int64_t LagLeadOperatorTransformer<T>::get_min_delta() {
    return static_cast<int64_t>(*std::min_element(_offsets.cbegin(), _offsets.cend())) - static_cast<int64_t>(_offset_delta);
}

template <typename T>
std::int64_t LagLeadOperatorTransformer<T>::get_max_delta() {
    return static_cast<int64_t>(*std::max_element(_offsets.cbegin(), _offsets.cend())) - static_cast<int64_t>(_offset_delta);
}

// ----------------------------------------------------------------------
// |
// |  LagLeadOperatorEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
template <typename DeltasInputIteratorRangeT>
LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>::LagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, DeltasInputIteratorRangeT deltas) :
    LagLeadOperatorEstimator(std::move(pAllColumnAnnotations), std::move(horizon), std::vector<int64_t>(std::get<0>(deltas), std::get<1>(deltas)))
{}

template <typename InputT, size_t MaxNumTrainingItemsV>
LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>::LagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, std::vector<int64_t> deltas) :
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
                if(deltas.empty())
                    throw std::invalid_argument("deltas");

                return deltas;
            }()
        )
    )
{}

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
template <typename DeltasInputIteratorRangeT>
GrainedLagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>::GrainedLagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, DeltasInputIteratorRangeT deltas) :
    GrainedLagLeadOperatorEstimator(std::move(pAllColumnAnnotations), horizon, std::vector<int64_t>(std::get<0>(deltas), std::get<1>(deltas)))
{}

template <typename InputT, size_t MaxNumTrainingItemsV>
GrainedLagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>::GrainedLagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, std::vector<int64_t> deltas) :
    BaseType(
        std::move(pAllColumnAnnotations),
        [horizon, deltas](AnnotationMapsPtr pAllColumnAnnotationsParam) {
            return LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>(
                std::move(pAllColumnAnnotationsParam),
                horizon,
                deltas
            );
        },
        [horizon, deltas]() {
            return typename LagLeadOperatorEstimator<InputT>::TransformerUniquePtr(
                new LagLeadOperatorTransformer<InputT>(
                    horizon,
                    deltas
                )
            );
        },
        true // isInferenceOnlyEstimator
    )
{}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
