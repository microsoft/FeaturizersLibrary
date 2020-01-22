// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/VectorNormsEstimator.h"
#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/NormUpdaters.h"
#include "../Archive.h"
#include "Structs.h"
namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

template <typename T>
struct GetNullableType {
    using type = T;
};

template <typename U>
struct GetNullableType<nonstd::optional<U>> {
    using type = U;
};

namespace {
    // tag dispatching functions for potential nullable values within iterators

    template <typename IteratorT>
    bool is_null(IteratorT const &input, std::true_type) {
        return Traits<typename std::iterator_traits<IteratorT>::value_type>::IsNull(*input);
    }

    template <typename IteratorT>
    bool is_null(IteratorT const &, std::false_type) {
        return false;
    }

    template <typename IteratorT>
    typename GetNullableType<typename std::iterator_traits<IteratorT>::value_type>::type const& get_value(IteratorT const &input, std::true_type) {
        return Traits<typename std::iterator_traits<IteratorT>::value_type>::GetNullableValue(*input);
    }

    template <typename IteratorT>
    typename std::iterator_traits<IteratorT>::value_type const& get_value(IteratorT const &input, std::false_type) {
        return *input;
    }
} // anonymous namespace

/////////////////////////////////////////////////////////////////////////
///  \class         NormalizeTransformer
///  \brief         Normalize based on l1, l2 or max norm
///
template <typename IteratorRangeT>
class NormalizeTransformer : public StandardTransformer<IteratorRangeT, std::vector<std::double_t>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------

    // checks if IteratorRangeT is a pair of iterators
    static_assert(Components::IsIteratorPair<IteratorRangeT>::value, "VectorNormsEstimator input type need to a pair of iterators of same type!");


    using BaseType     = StandardTransformer<IteratorRangeT, std::vector<std::double_t>>;

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
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using IteratorType = typename std::tuple_element<0, IteratorRangeT>::type;
    using ValueType    = typename std::iterator_traits<IteratorType>::value_type;

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
    void execute_impl(IteratorRangeT const &input, typename BaseType::CallbackFunction const &callback) override;

    void execute_impl(IteratorType &begin, IteratorType const &end, typename BaseType::CallbackFunction const &callback, std::true_type);
    void execute_impl(IteratorType &begin, IteratorType const &end, typename BaseType::CallbackFunction const &callback, std::false_type);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         NormalizeEstimatorImplx
///  \brief         Estimator that reads an annotation created by the `VectorNormsEstimator`
///                 to create a `NormalizeTransformer` object.
///
template <
    typename IteratorRangeT,
    typename UpdaterT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class NormalizeEstimatorImplx : public TransformerEstimator<IteratorRangeT, std::vector<std::double_t>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TransformedType                   = std::vector<std::double_t>;
    using BaseType                          = TransformerEstimator<IteratorRangeT, TransformedType>;
    using TransformerType                   = NormalizeTransformer<IteratorRangeT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    NormalizeEstimatorImplx(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~NormalizeEstimatorImplx(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(NormalizeEstimatorImplx);

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
    FitResult fit_impl(IteratorRangeT const *, size_t) override;
    void complete_training_impl(void) override;

    // MSVC has problems when the definition is separate from the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        // ----------------------------------------------------------------------
        using VectorNormsAnnotationData = Components::VectorNormsAnnotationData<UpdaterT>;
        using VectorNormsEstimator       = Components::VectorNormsEstimator<IteratorRangeT, UpdaterT, MaxNumTrainingItemsV>;
        // ----------------------------------------------------------------------

        VectorNormsAnnotationData const & data(VectorNormsEstimator::get_annotation_data(this->get_column_annotations(), _colIndex, Components::VectorNormsEstimatorName));

        return typename BaseType::TransformerUniquePtr(new NormalizeTransformer<IteratorRangeT>(data.Norms));
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         NormalizeEstimatorImpl
///  \brief         Chains up VectorNormsEstimator and NormalizeTransformerImpl
///                 to normalize input vector data so that it's norm becoming 1
///
template <
    typename IteratorRangeT,
    typename UpdaterT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class NormalizeEstimatorImpl :
    public Components::PipelineExecutionEstimatorImpl<
        Components::VectorNormsEstimator<IteratorRangeT, UpdaterT, MaxNumTrainingItemsV>,
        Details::NormalizeEstimatorImplx<IteratorRangeT, UpdaterT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::VectorNormsEstimator<IteratorRangeT, UpdaterT, MaxNumTrainingItemsV>,
            Details::NormalizeEstimatorImplx<IteratorRangeT, UpdaterT, MaxNumTrainingItemsV>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    NormalizeEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~NormalizeEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(NormalizeEstimatorImpl);
};

/////////////////////////////////////////////////////////////////////////
///  \typedef       L1NormalizeEstimator
///  \brief         Used to differentiate different NormalizeEstimatorImpl depends on norms
///
template <
    typename IteratorRangeT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using L1NormalizeEstimator = NormalizeEstimatorImpl<
                                    IteratorRangeT,
                                    Components::Updaters::L1NormUpdater<typename std::iterator_traits<typename std::tuple_element<0, IteratorRangeT>::type>::value_type>,
                                    MaxNumTrainingItemsV>;

/////////////////////////////////////////////////////////////////////////
///  \typedef       L2NormalizeEstimator
///  \brief         Used to differentiate different NormalizeEstimatorImpl depends on norms
///
template <
    typename IteratorRangeT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using L2NormalizeEstimator = NormalizeEstimatorImpl<
                                    IteratorRangeT,
                                    Components::Updaters::L2NormUpdater<typename std::iterator_traits<typename std::tuple_element<0, IteratorRangeT>::type>::value_type>,
                                    MaxNumTrainingItemsV>;

/////////////////////////////////////////////////////////////////////////
///  \typedef       MaxNormalizeEstimator
///  \brief         Used to differentiate different NormalizeEstimatorImpl depends on norms
///
template <
    typename IteratorRangeT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using MaxNormalizeEstimator = NormalizeEstimatorImpl<
                                    IteratorRangeT,
                                    Components::Updaters::MaxNormUpdater<typename std::iterator_traits<typename std::tuple_element<0, IteratorRangeT>::type>::value_type>,
                                    MaxNumTrainingItemsV>;

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
template <typename IteratorRangeT>
NormalizeTransformer<IteratorRangeT>::NormalizeTransformer(std::vector<std::double_t> norms) :
    _norms(std::move(norms)),
    _row(0) {
        if (_norms.empty()) {
            throw std::invalid_argument("Norms input to NormalizeTransformer is empty!");
        }
        for (auto const &norm : _norms) {
            if (norm < 0) {
                throw std::invalid_argument("Norms shouldn't be less than 0!");
            }
        }
}

template <typename IteratorRangeT>
NormalizeTransformer<IteratorRangeT>::NormalizeTransformer(Archive &ar) :
    NormalizeTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            std::vector<std::double_t> norms(Traits<std::vector<std::double_t>>::deserialize(ar));

            return NormalizeTransformer<IteratorRangeT>(std::move(norms));
        }()
    ) {
}

template <typename IteratorRangeT>
void NormalizeTransformer<IteratorRangeT>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<std::vector<std::double_t>>::serialize(ar, _norms);
}

template <typename IteratorRangeT>
bool NormalizeTransformer<IteratorRangeT>::operator==(NormalizeTransformer const &other) const {

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
template <typename IteratorRangeT>
void NormalizeTransformer<IteratorRangeT>::execute_impl(IteratorRangeT const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    // unpack input to two iterators
    IteratorType begin = std::get<0>(input);
    IteratorType const & end = std::get<1>(input);

    if (std::distance(begin, end) < 0) {
        throw std::runtime_error("Input iterators to VectorNormsEstimator are invalid!");
    }
    if (_row >= _norms.size()) {
        throw std::runtime_error("Number of norms is not aligned with number of rows!");
    }

    std::vector<std::double_t> res;
    res.reserve(static_cast<size_t>(std::distance(begin, end)));
    while (begin != end) {
        if(is_null(begin, std::integral_constant<bool, Microsoft::Featurizer::Traits<ValueType>::IsNullableType>())) {
            res.emplace_back(Traits<std::double_t>::CreateNullValue());
        }
        else {
            res.emplace_back(static_cast<std::double_t>(static_cast<long double>(get_value(begin, std::integral_constant<bool, Microsoft::Featurizer::Traits<ValueType>::IsNullableType>())) / static_cast<long double>(_norms[_row])));
        }
        ++begin;
    }
    ++_row;
    callback(res);
}



// ----------------------------------------------------------------------
// |
// |  NormalizeEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename IteratorRangeT, typename UpdaterT, size_t MaxNumTrainingItemsV>
NormalizeEstimatorImpl<IteratorRangeT, UpdaterT, MaxNumTrainingItemsV>::NormalizeEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "NormalizeEstimatorImpl",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::VectorNormsEstimator<IteratorRangeT, UpdaterT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Details::NormalizeEstimatorImplx<IteratorRangeT, UpdaterT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::NormalizeEstimatorImplx
// |
// ----------------------------------------------------------------------
template <typename IteratorRangeT, typename UpdaterT, size_t MaxNumTrainingItemsV>
Details::NormalizeEstimatorImplx<IteratorRangeT, UpdaterT, MaxNumTrainingItemsV>::NormalizeEstimatorImplx(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("NormalizeEstimatorImplx", std::move(pAllColumnAnnotations)),
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
template <typename IteratorRangeT, typename UpdaterT, size_t MaxNumTrainingItemsV>
bool Details::NormalizeEstimatorImplx<IteratorRangeT, UpdaterT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename IteratorRangeT, typename UpdaterT, size_t MaxNumTrainingItemsV>
FitResult Details::NormalizeEstimatorImplx<IteratorRangeT, UpdaterT, MaxNumTrainingItemsV>::fit_impl(IteratorRangeT const *, size_t) /*override*/ {
    throw std::runtime_error("This will never be called");
}

template <typename IteratorRangeT, typename UpdaterT, size_t MaxNumTrainingItemsV>
void Details::NormalizeEstimatorImplx<IteratorRangeT, UpdaterT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
