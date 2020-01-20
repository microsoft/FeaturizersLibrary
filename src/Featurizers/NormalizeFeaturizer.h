// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/VectorNormsEstimator.h"
#include "Components/PipelineExecutionEstimatorImpl.h"
#include "../Archive.h"
#include "Structs.h"
namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         NormalizeTransformer
///  \brief         Normalize based on l1, l2 or max norm
///
template <typename InputT>
class NormalizeTransformer : public StandardTransformer<InputT, std::vector<std::double_t>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------

    
    using IteratorType = typename std::tuple_element<0, InputT>::type;
    using ValueType    = typename std::iterator_traits<IteratorType>::value_type;
    using BaseType     = StandardTransformer<InputT, std::vector<std::double_t>>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    NormalizeTransformer(std::vector<std::double_t> norms);
    NormalizeTransformer(Archive &ar);

    ~NormalizeTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(NormalizeTransformer);

    bool operator==(NormalizeTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::vector<std::double_t> const                   _norms;
    size_t                                             _row;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(InputT const &input, typename BaseType::CallbackFunction const &callback) override;

    void execute_impl(IteratorType &begin, IteratorType const &end, typename BaseType::CallbackFunction const &callback, std::true_type);
    void execute_impl(IteratorType &begin, IteratorType const &end, typename BaseType::CallbackFunction const &callback, std::false_type);

};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         NormalizeEstimatorImpl
///  \brief         Estimator that reads an annotation created by the `VectorNormsEstimator`
///                 to create a `NormalizeTransformer` object.
///
template <
    typename InputT,
    typename UpdaterType,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class NormalizeEstimatorImpl : public TransformerEstimator<InputT, std::vector<std::double_t>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TransformedType                   = std::vector<std::double_t>;
    using BaseType                          = TransformerEstimator<InputT, TransformedType>;
    using TransformerType                   = NormalizeTransformer<InputT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    NormalizeEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~NormalizeEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(NormalizeEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;
    FitResult fit_impl(InputT const *, size_t) override;
    void complete_training_impl(void) override;

    // MSVC has problems when the definition is separate from the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        // ----------------------------------------------------------------------
        using VectorNormsAnnotationData = Components::VectorNormsAnnotationData<UpdaterType>;
        using VectorNormsEstimator       = Components::VectorNormsEstimator<InputT, UpdaterType, MaxNumTrainingItemsV>;
        // ----------------------------------------------------------------------

        VectorNormsAnnotationData const & data(VectorNormsEstimator::get_annotation_data(this->get_column_annotations(), _colIndex, Components::VectorNormsEstimatorName));

        return typename BaseType::TransformerUniquePtr(new NormalizeTransformer<InputT>(data.Norms));
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         NormalizeEstimator
///  \brief         Chains up VectorNormsEstimator and NormalizeTransformerImpl
///                 to normalize input vector data so that it's norm becoming 1
///
template <
    typename InputT,
    typename UpdaterType,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class NormalizeEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::VectorNormsEstimator<InputT, UpdaterType, MaxNumTrainingItemsV>,
        Details::NormalizeEstimatorImpl<InputT, UpdaterType, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::VectorNormsEstimator<InputT, UpdaterType, MaxNumTrainingItemsV>,
            Details::NormalizeEstimatorImpl<InputT, UpdaterType, MaxNumTrainingItemsV>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    NormalizeEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~NormalizeEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(NormalizeEstimator);
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
// |  NormalizeTransformer
// |
// ----------------------------------------------------------------------
template <typename InputT>
NormalizeTransformer<InputT>::NormalizeTransformer(std::vector<std::double_t> norms) :
    _norms(std::move(norms)),
    _row(0) {
        if (_norms.empty()) {
            throw std::invalid_argument("Norms input to NormalizeTransformer is empty!");
        }
        for (auto norm : _norms) {
            if (norm < 0) {
                throw std::invalid_argument("Norms shouldn't be less than 0!");
            }
        }
}

template <typename InputT>
NormalizeTransformer<InputT>::NormalizeTransformer(Archive &ar) :
    NormalizeTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            std::vector<std::double_t> norms(Traits<std::vector<std::double_t>>::deserialize(ar));

            return NormalizeTransformer<InputT>(std::move(norms));
        }()
    ) {
}

template <typename InputT>
void NormalizeTransformer<InputT>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<std::vector<std::double_t>>::serialize(ar, _norms);
}

template <typename InputT>
bool NormalizeTransformer<InputT>::operator==(NormalizeTransformer const &other) const {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    return this->_norms == other._norms;

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

}


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT>
void NormalizeTransformer<InputT>::execute_impl(InputT const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    execute_impl(const_cast<IteratorType&>(std::get<0>(input)), std::get<1>(input), callback, std::integral_constant<bool, Microsoft::Featurizer::Traits<ValueType>::IsNullableType>());
}

template <typename InputT>
void NormalizeTransformer<InputT>::execute_impl(IteratorType &begin, IteratorType const &end, typename BaseType::CallbackFunction const &callback, std::true_type) {
    // ----------------------------------------------------------------------
    using InputTraits                       = Traits<ValueType>;
    using TransformedTraits                 = Traits<std::double_t>;
    // ----------------------------------------------------------------------
    if (std::distance(begin, end) < 0) {
        throw std::runtime_error("Input iterators to VectorNormsEstimator are invalid!");
    }
    if (_row >= _norms.size()) {
        throw std::runtime_error("Number of norms is not aligned with number of rows!");
    }


    std::vector<std::double_t> res;
    res.reserve(static_cast<size_t>(std::distance(begin, end)));
    while (begin != end) {
        if(InputTraits::IsNull(*begin)) {
            res.emplace_back(TransformedTraits::CreateNullValue());
            ++begin;
            continue;
        }
        res.emplace_back(static_cast<std::double_t>(static_cast<long double>(InputTraits::GetNullableValue(*begin)) / static_cast<long double>(_norms[_row])));
        ++begin;
    }
    ++_row;
    callback(res);
}

template <typename InputT>
void NormalizeTransformer<InputT>::execute_impl(IteratorType &begin, IteratorType const &end, typename BaseType::CallbackFunction const &callback, std::false_type) {
    if (std::distance(begin, end) < 0) {
        throw std::runtime_error("Input iterators to VectorNormsEstimator are invalid!");
    }

    if (_row >= _norms.size()) {
        throw std::runtime_error("Number of norms is not aligned with number of rows!");
    }


    std::vector<std::double_t> res;
    res.reserve(static_cast<size_t>(std::distance(begin, end)));
    while (begin != end) {
        res.emplace_back(static_cast<std::double_t>(static_cast<long double>(*begin) / static_cast<long double>(_norms[_row])));
        ++begin;
    }
    ++_row;
    callback(res);
}


// ----------------------------------------------------------------------
// |
// |  NormalizeEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename UpdaterType, size_t MaxNumTrainingItemsV>
NormalizeEstimator<InputT, UpdaterType, MaxNumTrainingItemsV>::NormalizeEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "NormalizeEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::VectorNormsEstimator<InputT, UpdaterType, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Details::NormalizeEstimatorImpl<InputT, UpdaterType, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::NormalizeEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename InputT, typename UpdaterType, size_t MaxNumTrainingItemsV>
Details::NormalizeEstimatorImpl<InputT, UpdaterType, MaxNumTrainingItemsV>::NormalizeEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("NormalizeEstimatorImpl", std::move(pAllColumnAnnotations)),
    _colIndex(
        std::move(
            [this, &colIndex](void) -> size_t & {
                if(colIndex >= this->get_column_annotations().size())
                    throw std::invalid_argument("colIndex");

                return colIndex;
            }()
        )
    ) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename UpdaterType, size_t MaxNumTrainingItemsV>
bool Details::NormalizeEstimatorImpl<InputT, UpdaterType, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename InputT, typename UpdaterType, size_t MaxNumTrainingItemsV>
FitResult Details::NormalizeEstimatorImpl<InputT, UpdaterType, MaxNumTrainingItemsV>::fit_impl(InputT const *, size_t) /*override*/ {
    throw std::runtime_error("This will never be called");
}

template <typename InputT, typename UpdaterType, size_t MaxNumTrainingItemsV>
void Details::NormalizeEstimatorImpl<InputT, UpdaterType, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
