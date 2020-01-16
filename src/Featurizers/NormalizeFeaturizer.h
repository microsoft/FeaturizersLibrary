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
class NormalizeTransformer : public StandardTransformer<InputT, std::vector<long double>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    static_assert(Traits<InputT>::IsVectorType, "Input type has to be vector!");
    static_assert(Traits<typename InputT::value_type>::IsIntOrNumeric::value, "Vector elements has to be ints or numeric types!");

    using ValueType                         = typename InputT::value_type;
    using BaseType                          = StandardTransformer<InputT, std::vector<long double>>;

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
    std::vector<std::double_t> const                     _norms;
    std::uint64_t                                      _row;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override;

    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback, std::true_type);
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback, std::false_type);

};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         NormalizeEstimatorImpl
///  \brief         Estimator that reads an annotation created by the `VectorNormsEstimator`
///                 to create a `NormalizeTransformer` object.
///
template <
    typename InputT,
    NormType NormT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class NormalizeEstimatorImpl : public TransformerEstimator<InputT, std::vector<long double>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TransformedType                   = std::vector<long double>;
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
    FitResult fit_impl(typename BaseType::InputType const *, size_t) override;
    void complete_training_impl(void) override;

    // MSVC has problems when the definition is separate from the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        // ----------------------------------------------------------------------
        using VectorNormsAnnotationData = Components::VectorNormsAnnotationData;
        using VectorNormsEstimator       = Components::VectorNormsEstimator<InputT, NormT, MaxNumTrainingItemsV>;
        // ----------------------------------------------------------------------

        VectorNormsAnnotationData const & data(VectorNormsEstimator::get_annotation_data(this->get_column_annotations(), _colIndex, Components::VectorNormsEstimatorName));

        assert(data.Type == NormT);
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
    NormType NormT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class NormalizeEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::VectorNormsEstimator<InputT, NormT, MaxNumTrainingItemsV>,
        Details::NormalizeEstimatorImpl<InputT, NormT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::VectorNormsEstimator<InputT, NormT, MaxNumTrainingItemsV>,
            Details::NormalizeEstimatorImpl<InputT, NormT, MaxNumTrainingItemsV>
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
        for (auto it = norms.begin(); it != norms.end(); ++it) {
            if (*it < 0) {
                throw std::invalid_argument("Norms shouldn't be less than 0!");
            }
        }
}

template <typename InputT>
NormalizeTransformer<InputT>::NormalizeTransformer(Archive &ar) :
    NormalizeTransformer(
        [&ar](void) {
            std::vector<std::double_t> norms(Traits<std::vector<std::double_t>>::deserialize(ar));

            return NormalizeTransformer<InputT>(std::move(norms));
        }()
    ) {
}

template <typename InputT>
void NormalizeTransformer<InputT>::save(Archive &ar) const /*override*/ {
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
void NormalizeTransformer<InputT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    execute_impl(input, callback, std::integral_constant<bool, Microsoft::Featurizer::Traits<ValueType>::IsNullableType>());
}

template <typename InputT>
void NormalizeTransformer<InputT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback, std::true_type) {
    // ----------------------------------------------------------------------
    using InputTraits                       = Traits<ValueType>;
    using TransformedTraits                 = Traits<long double>;
    // ----------------------------------------------------------------------
    std::vector<long double> res;
    for (auto it = input.begin(); it != input.end(); ++it) {
        if(InputTraits::IsNull(*it)) {
            res.push_back(TransformedTraits::CreateNullValue());
            continue;
        }
        res.push_back(static_cast<long double>(InputTraits::GetNullableValue(*it)) / static_cast<long double>(_norms[_row]));
    }
    ++_row;
    callback(res);
}

template <typename InputT>
void NormalizeTransformer<InputT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback, std::false_type) {
    std::vector<long double> res;
    for (auto it = input.begin(); it != input.end(); ++it) {
        res.push_back(static_cast<long double>(*it) / static_cast<long double>(_norms[_row]));
    }
    ++_row;
    callback(res);
}


// ----------------------------------------------------------------------
// |
// |  NormalizeEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, NormType NormT, size_t MaxNumTrainingItemsV>
NormalizeEstimator<InputT, NormT, MaxNumTrainingItemsV>::NormalizeEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "NormalizeEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::VectorNormsEstimator<InputT, NormT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Details::NormalizeEstimatorImpl<InputT, NormT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::NormalizeEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename InputT, NormType NormT, size_t MaxNumTrainingItemsV>
Details::NormalizeEstimatorImpl<InputT, NormT, MaxNumTrainingItemsV>::NormalizeEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
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
template <typename InputT, NormType NormT, size_t MaxNumTrainingItemsV>
bool Details::NormalizeEstimatorImpl<InputT, NormT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename InputT, NormType NormT, size_t MaxNumTrainingItemsV>
FitResult Details::NormalizeEstimatorImpl<InputT, NormT, MaxNumTrainingItemsV>::fit_impl(typename BaseType::InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This will never be called");
}

template <typename InputT, NormType NormT, size_t MaxNumTrainingItemsV>
void Details::NormalizeEstimatorImpl<InputT, NormT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
