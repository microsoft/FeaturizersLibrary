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
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::uint32_t const                                _horizon;
    std::int64_t const                                 _offset_delta;
    std::vector<std::int64_t> const                    _offsets;
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
        std::int64_t numPending = 0;
        std::int64_t max_future((_offset_delta + *std::max_element(_offsets.cbegin(), _offsets.cend())) > 0 ? (_offset_delta + *std::max_element(_offsets.cbegin(), _offsets.cend())) : 0);

        while (numPending < max_future) {
            execute_helper(Traits<TransformedTargetType>::CreateNullValue(), callback);
            ++numPending;
        }
        // after flush is called, this transfomer should be reset to its starting state
        _buffer.clear();
        for (std::int64_t i = 0; i < (static_cast<std::int64_t>(_horizon) - _offset_delta - 1); ++i) {
            _buffer.push(Traits<TransformedTargetType>::CreateNullValue());
        }
    }

    void execute_helper(TransformedTargetType const &input, typename BaseType::CallbackFunction const &callback);
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
    LagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, std::vector<std::int64_t> offsets);

    ~LagLeadOperatorEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(LagLeadOperatorEstimator);


private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Members
    // |
    // ----------------------------------------------------------------------
    std::uint32_t             const                    _horizon;
    std::vector<std::int64_t> const                    _offsets;


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
        return typename BaseType::TransformerUniquePtr(new LagLeadOperatorTransformer<InputT>(_horizon, _offsets));
    }

};

/////////////////////////////////////////////////////////////////////////
///  \class       GrainedLagLeadOperatorEstimator
///  \brief       GrainedTransformer that creates `LagLeadOperatorEstimator`.
///

template <typename InputT, size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class GrainedLagLeadOperatorEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::GrainEstimatorImpl<std::vector<std::string>, LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>>,
        Components::FilterDecoratorEstimator<std::tuple<std::vector<std::string> const &, Microsoft::Featurizer::RowMajMatrix<typename Microsoft::Featurizer::Traits<InputT>::nullable_type>>, 1>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = 
        Components::PipelineExecutionEstimatorImpl<
            Components::GrainEstimatorImpl<std::vector<std::string>, LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>>,
            Components::FilterDecoratorEstimator<std::tuple<std::vector<std::string> const &, Microsoft::Featurizer::RowMajMatrix<typename Microsoft::Featurizer::Traits<InputT>::nullable_type>>, 1>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    GrainedLagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, std::vector<std::int64_t> offsets);
    ~GrainedLagLeadOperatorEstimator(void) override = default;
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
    _offset_delta(
        std::move(
            [&offsets](void) -> std::int64_t {
                if (offsets.size() == 0) {
                    throw std::invalid_argument("Offsets is empty!");
                }
                return *std::min_element(offsets.cbegin(), offsets.cend()) < 0 ? *std::min_element(offsets.cbegin(), offsets.cend()) : 0;
            }()
        )
    ),
    // calibrate offsets to minimum offset = 0
    _offsets(
        std::move(
            [&offsets](void) -> std::vector<std::int64_t> & {
                std::int64_t min = *std::min_element(offsets.cbegin(), offsets.cend()) < 0 ? *std::min_element(offsets.cbegin(), offsets.cend()) : 0;
                for (auto it = offsets.begin(); it != offsets.end(); it++) {
                    *it -= min;
                }
                return offsets;
            }()
        )
    ),
    // if there's only one offset, we use the absolute value of it plus horizon as the size
    // otherwise we need to check if the minimum offset is negative:
    // if it is, the buffer size is the absolute value of minimum offset plus horizon
    // if it's not, the buffer size is the difference between min and max of offsets, which is already calculated in the offsets calibration so we can use max_element directly
    _buffer(
        _horizon + 
        (_offsets.size() == 1 ? 
        static_cast<size_t>(std::abs(_offsets[0] + _offset_delta)) : 
        static_cast<size_t>(
            *std::max_element(_offsets.cbegin(), _offsets.cend()) + _offset_delta < 0 ? 
            std::abs(_offset_delta) : 
            *std::max_element(_offsets.cbegin(), _offsets.cend())))
    ) {
        // prepopulate circular buffer with null values to imitate non-existing prior rows
        for (std::int64_t i = 0; i < (static_cast<std::int64_t>(_horizon) - _offset_delta - 1); ++i) {
            _buffer.push(Traits<TransformedTargetType>::CreateNullValue());
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

    // reset _offsets to its input version
    std::vector<std::int64_t> offsets(_offsets);
    for (auto it = offsets.begin(); it != offsets.end(); it++) {
        *it += _offset_delta;
    }
    Traits<std::vector<std::int64_t>>::serialize(ar, offsets);

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
        std::tuple<typename Components::CircularBuffer<TransformedTargetType>::iterator, typename Components::CircularBuffer<TransformedTargetType>::iterator> range{_buffer.range(_horizon, static_cast<size_t>(_offsets[row]))};
        typename Components::CircularBuffer<TransformedTargetType>::iterator start_iter = std::get<0>(range);

        for (std::int32_t col = 0; col < static_cast<std::int32_t>(_horizon); ++col) {
            ret(static_cast<std::int32_t>(row), col) = *start_iter;
            ++start_iter;
        }
    }

    callback(std::move(ret));
}


// ----------------------------------------------------------------------
// |
// |  LagLeadOperatorEstimator
// |
// ----------------------------------------------------------------------

template <typename InputT, size_t MaxNumTrainingItemsV>
LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>::LagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, std::vector<std::int64_t> offsets) :
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
    _offsets(
        std::move(
            [&offsets](void) -> std::vector<std::int64_t> & {
                if (offsets.size() == 0) {
                    throw std::invalid_argument("Offsets is empty!");
                }
                return offsets;
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
GrainedLagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>::GrainedLagLeadOperatorEstimator(AnnotationMapsPtr pAllColumnAnnotations, std::uint32_t horizon, std::vector<std::int64_t> offsets) :
    BaseType(
        GrainedLagLeadOperatorEstimatorName,
        pAllColumnAnnotations,
        [pAllColumnAnnotations, horizon, offsets] () {
            return Components::GrainEstimatorImpl<std::vector<std::string>, LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>, MaxNumTrainingItemsV>(
                pAllColumnAnnotations,
                [horizon, offsets](AnnotationMapsPtr pAllColumnAnnotationsParam) {
                    return LagLeadOperatorEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotationsParam), std::move(horizon), std::move(offsets));
                }
            );
        },
        [pAllColumnAnnotations]() {
            return Components::FilterDecoratorEstimator<std::tuple<std::vector<std::string> const &, Microsoft::Featurizer::RowMajMatrix<typename Microsoft::Featurizer::Traits<InputT>::nullable_type>>, 1>(std::move(pAllColumnAnnotations));
        }
    ) {
}


} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
