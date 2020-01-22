// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#pragma once

#include "Components/HistogramEstimator.h"
#include "Components/IndexMapEstimator.h"
#include "Components/PipelineExecutionEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
/////////////////////////////////////////////////////////////////////////
///  \class         NumericalizeTransformer
///  \brief         Returns a unique category id for each input.
///                 Returns no value
///
template <typename InputT>
class NumericalizeTransformer : public StandardTransformer<InputT, std::double_t> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = StandardTransformer<InputT, std::double_t>;
    using IndexMap = typename Components::IndexMapAnnotationData<InputT>::IndexMap;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    explicit NumericalizeTransformer (IndexMap map);
    explicit NumericalizeTransformer (Archive &ar);

    ~NumericalizeTransformer (void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY (NumericalizeTransformer);

    void save (Archive &ar) const override;

    bool operator==(NumericalizeTransformer const &other) const;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems when the definition and declaration are separated
    void execute_impl(typename BaseType::InputType const& input, typename BaseType::CallbackFunction const& callback) override {
        typename IndexMap::const_iterator const         iter(labels_.find(input));
        double result = 0.;
        if(iter != labels_.end()) {
            result = iter->second;
        } else {
            result = std::numeric_limits<double>::quiet_NaN();
        }
        callback(result);
    }

private:
    IndexMap const labels_;
};

namespace Details {
/////////////////////////////////////////////////////////////////////////
///  \class         NumericalizeEstimatorImpl
///  \brief         Estimator that uses the output of the
///                 `IndexMapEstmator` to produce a unique label.
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV = std::numeric_limits<size_t>::max()
>
class NumericalizeEstimatorImpl : public TransformerEstimator<InputT, std::double_t> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType = TransformerEstimator<InputT, std::double_t>;
    using TransformerType = NumericalizeTransformer<InputT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    NumericalizeEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~NumericalizeEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(NumericalizeEstimatorImpl);

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

    // MSVC has problems when the declaration and definition are separated
    FitResult fit_impl(typename BaseType::InputType const *, size_t) override {
        throw std::runtime_error("This should not be called");
    }

    void complete_training_impl(void) override;

    // MSVC has problems when the declaration and definition are separated
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        // ----------------------------------------------------------------------
        using IndexMapAnnotationData = Components::IndexMapAnnotationData<InputT>;
        using IndexMapEstimator = Components::IndexMapEstimator<InputT, MaxNumTrainingItemsV>;
        // ----------------------------------------------------------------------

        IndexMapAnnotationData const& data(IndexMapEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::IndexMapEstimatorName));

        return typename BaseType::TransformerUniquePtr(new NumericalizeTransformer<InputT>(data.Value));
    }
};
} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         NumericalizeEstimator
///  \brief         Creates a `NumericalizeTransformer` object.
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV = std::numeric_limits<size_t>::max()
>
class NumericalizeEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::HistogramEstimator<InputT, MaxNumTrainingItemsV>,
        Components::IndexMapEstimator<InputT, MaxNumTrainingItemsV>,
        Details::NumericalizeEstimatorImpl<InputT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::HistogramEstimator<InputT, MaxNumTrainingItemsV>,
            Components::IndexMapEstimator<InputT, MaxNumTrainingItemsV>,
            Details::NumericalizeEstimatorImpl<InputT, MaxNumTrainingItemsV>
        >;

    using IndexMap = typename Components::IndexMapAnnotationData<InputT>::IndexMap;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    NumericalizeEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    NumericalizeEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, IndexMap existingValues);

    ~NumericalizeEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(NumericalizeEstimator);
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
// |  NumericalizeTransformer
// |
// ----------------------------------------------------------------------

template<typename InputT>
inline NumericalizeTransformer<InputT>::NumericalizeTransformer(IndexMap map) :
    labels_(std::move(map)) {
 }

template<typename InputT>
inline NumericalizeTransformer<InputT>::NumericalizeTransformer(Archive & ar) :
    NumericalizeTransformer(
        [&ar]() {
        // Version
        std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
        std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

        if(majorVersion != 1 || minorVersion != 0)
            throw std::runtime_error("Unsupported archive version");

        // Data
        return NumericalizeTransformer(Traits<IndexMap>::deserialize(ar));
        }()
    ) {
}

template<typename InputT>
inline void NumericalizeTransformer<InputT>::save(Archive& ar) const {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(labels_)>::serialize(ar, labels_);
}

template <typename InputT>
inline bool NumericalizeTransformer<InputT>::operator==(NumericalizeTransformer const &other) const {
    return labels_ == other.labels_;
}


// ----------------------------------------------------------------------
// |
// |  LabelEncoderEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
NumericalizeEstimator<InputT, MaxNumTrainingItemsV>::NumericalizeEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    NumericalizeEstimator(std::move(pAllColumnAnnotations), colIndex, IndexMap()) {
}

template <typename InputT, size_t MaxNumTrainingItemsV>
NumericalizeEstimator<InputT, MaxNumTrainingItemsV>::NumericalizeEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, IndexMap existingValues) :
    BaseType(
        "NumericalizeEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex]() { return Components::HistogramEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), colIndex); },
        [pAllColumnAnnotations, colIndex, &existingValues]() { return Components::IndexMapEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), colIndex, std::move(existingValues)); },
        [pAllColumnAnnotations, colIndex]() { return Details::NumericalizeEstimatorImpl<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), colIndex); }
    ) {
}


// ----------------------------------------------------------------------
// |
// |  Details::NumericalizeEstimatorImpl
// |
// ----------------------------------------------------------------------
template<typename InputT, size_t MaxNumTrainingItemsV>
inline Details::NumericalizeEstimatorImpl<InputT, MaxNumTrainingItemsV>::NumericalizeEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("NumericalizeEstimatorImpl", std::move(pAllColumnAnnotations)),
    _colIndex(colIndex) {
    if(_colIndex >= this->get_column_annotations().size())
        throw std::invalid_argument("colIndex");
}

template<typename InputT, size_t MaxNumTrainingItemsV>
inline bool Details::NumericalizeEstimatorImpl<InputT, MaxNumTrainingItemsV>::begin_training_impl(void) {
    return false;
}

template<typename InputT, size_t MaxNumTrainingItemsV>
inline void Details::NumericalizeEstimatorImpl<InputT, MaxNumTrainingItemsV>::complete_training_impl(void) {
}
}  // namespace Featurizers
}  // namespace Featurizer
}  // namespace Microsoft
