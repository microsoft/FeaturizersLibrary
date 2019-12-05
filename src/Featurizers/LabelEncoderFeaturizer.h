// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/HistogramEstimator.h"
#include "Components/IndexMapEstimator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         LabelEncoderTransformer
///  \brief         Returns a unique category id for each input.
///
template <typename InputT>
class LabelEncoderTransformer : public StandardTransformer<InputT, std::uint32_t> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = StandardTransformer<InputT, std::uint32_t>;
    using IndexMap                          = typename Components::IndexMapAnnotationData<InputT>::IndexMap;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    IndexMap const                          Labels;
    bool const                              AllowMissingValues;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    LabelEncoderTransformer(IndexMap map, bool allowMissingValues);
    LabelEncoderTransformer(Archive &ar);

    ~LabelEncoderTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(LabelEncoderTransformer);

    void save(Archive &ar) const override;

    bool operator==(LabelEncoderTransformer const &other) const;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems when the definition and declaration are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        typename IndexMap::const_iterator const         iter(Labels.find(input));

        if(iter == Labels.end()) {
            if(AllowMissingValues) {
                callback(0);
                return;
            }

            throw std::invalid_argument("'input' was not found");
        }

        callback(iter->second + (AllowMissingValues ? 1 : 0));
    }
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         LabelEncoderEstimatorImpl
///  \brief         Estimator that uses the output of the
///                 `IndexMapEstmator` to produce a unique label.
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class LabelEncoderEstimatorImpl : public TransformerEstimator<InputT, std::uint32_t> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, std::uint32_t>;
    using TransformerType                   = LabelEncoderTransformer<InputT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    LabelEncoderEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool allowMissingValues);
    ~LabelEncoderEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(LabelEncoderEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;
    bool const                              _allowMissingValues;

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
        using IndexMapAnnotationData        = Components::IndexMapAnnotationData<InputT>;
        using IndexMapEstimator             = Components::IndexMapEstimator<InputT, MaxNumTrainingItemsV>;
        // ----------------------------------------------------------------------

        IndexMapAnnotationData const &      data(IndexMapEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::IndexMapEstimatorName));

        return std::make_unique<LabelEncoderTransformer<InputT>>(data.Value, _allowMissingValues);
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         LabelEncoderEstimator
///  \brief         Creates a `LabelEncoderTransformer` object.
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class LabelEncoderEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::HistogramEstimator<InputT, MaxNumTrainingItemsV>,
        Components::IndexMapEstimator<InputT, MaxNumTrainingItemsV>,
        Details::LabelEncoderEstimatorImpl<InputT, MaxNumTrainingItemsV>
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
            Details::LabelEncoderEstimatorImpl<InputT, MaxNumTrainingItemsV>
        >;

    using IndexMap                          = typename Components::IndexMapAnnotationData<InputT>::IndexMap;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    LabelEncoderEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool allowMissingValues);
    LabelEncoderEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool allowMissingValues, IndexMap existingValues);

    ~LabelEncoderEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(LabelEncoderEstimator);
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
// |  LabelEncoderTransformer
// |
// ----------------------------------------------------------------------
template <typename InputT>
LabelEncoderTransformer<InputT>::LabelEncoderTransformer(IndexMap map, bool allowMissingValues) :
    Labels(std::move(map)),
    AllowMissingValues(std::move(allowMissingValues)) {
}

template <typename InputT>
LabelEncoderTransformer<InputT>::LabelEncoderTransformer(Archive &ar) :
    // TODO: Labels(Traits<decltype(Labels)>::deserialize(ar)),
    AllowMissingValues(Traits<decltype(AllowMissingValues)>::deserialize(ar)) {
}

template <typename InputT>
void LabelEncoderTransformer<InputT>::save(Archive &ar) const /*override*/ {
    // TODO: Traits<decltype(Labels)>::serialize(ar, Labels);
    Traits<decltype(AllowMissingValues)>::serialize(ar, AllowMissingValues);
}

template <typename InputT>
bool LabelEncoderTransformer<InputT>::operator==(LabelEncoderTransformer const &other) const {
    return Labels == other.Labels
        && AllowMissingValues == other.AllowMissingValues;
}

// ----------------------------------------------------------------------
// |
// |  LabelEncoderEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
LabelEncoderEstimator<InputT, MaxNumTrainingItemsV>::LabelEncoderEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool allowMissingValues) :
    LabelEncoderEstimator(std::move(pAllColumnAnnotations), std::move(colIndex), std::move(allowMissingValues), IndexMap()) {
}

template <typename InputT, size_t MaxNumTrainingItemsV>
LabelEncoderEstimator<InputT, MaxNumTrainingItemsV>::LabelEncoderEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool allowMissingValues, IndexMap existingValues) :
    BaseType(
        "LabelEncoderEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::HistogramEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex, &existingValues](void) { return Components::IndexMapEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex), std::move(existingValues)); },
        [pAllColumnAnnotations, colIndex, &allowMissingValues](void) { return Details::LabelEncoderEstimatorImpl<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex), std::move(allowMissingValues)); }
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::LabelEncoderEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
Details::LabelEncoderEstimatorImpl<InputT, MaxNumTrainingItemsV>::LabelEncoderEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool allowMissingValues) :
    BaseType("LabelEncoderEstimatorImpl", std::move(pAllColumnAnnotations)),
    _colIndex(
        std::move(
            [this, &colIndex](void) -> size_t & {
                if(colIndex >= this->get_column_annotations().size())
                    throw std::invalid_argument("colIndex");

                return colIndex;
            }()
        )
    ),
    _allowMissingValues(std::move(allowMissingValues)) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
bool Details::LabelEncoderEstimatorImpl<InputT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename InputT, size_t MaxNumTrainingItemsV>
void Details::LabelEncoderEstimatorImpl<InputT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
