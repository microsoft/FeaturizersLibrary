// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/HistogramEstimator.h"
#include "Components/IndexMapEstimator.h"
#include "Structs.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         OneHotEncoderTransformer
///  \brief         Returns a unique one hot struct for each input.
///
template <typename InputT>
class OneHotEncoderTransformer : public StandardTransformer<InputT, SingleValueSparseVectorEncoding<std::uint8_t>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = StandardTransformer<InputT, SingleValueSparseVectorEncoding<std::uint8_t>>;
    using IndexMap                          = typename Components::IndexMapAnnotationData<InputT>::IndexMap;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    IndexMap  const                         Labels;
    bool const                              AllowMissingValues;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    OneHotEncoderTransformer(IndexMap map, bool allowMissingValues);
    OneHotEncoderTransformer(Archive &ar);

    ~OneHotEncoderTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(OneHotEncoderTransformer);

    bool operator==(OneHotEncoderTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems when the definition and declaration are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        // when missing values are allowed, the total size is increased by 1 and the 0th element in the vector represent missing values
        std::uint64_t const                 offset(AllowMissingValues ? 1 : 0);

        // Create the encoding value
        std::uint64_t                       encodingIndex;

        typename IndexMap::const_iterator const         label_iter(Labels.find(input));

        if(label_iter == Labels.end()) {
            if(AllowMissingValues == false)
                throw std::invalid_argument("'input' was not found");

            encodingIndex = 0;
        }
        else
            encodingIndex = static_cast<std::uint64_t>(label_iter->second + offset);

        callback(SingleValueSparseVectorEncoding<std::uint8_t>(Labels.size() + offset, 1, encodingIndex));
    }
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         OneHotEncoderEstimatorImpl
///  \brief         Estimator that uses the output of the
///                 `IndexMapEstmator` and `HistogramEstmator`
///                 to produce a unique label.
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class OneHotEncoderEstimatorImpl : public TransformerEstimator<InputT, SingleValueSparseVectorEncoding<std::uint8_t>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, SingleValueSparseVectorEncoding<std::uint8_t>>;
    using TransformerType                   = OneHotEncoderTransformer<InputT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    OneHotEncoderEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool allowMissingValues);
    ~OneHotEncoderEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(OneHotEncoderEstimatorImpl);

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

        IndexMapAnnotationData const &       i_data(IndexMapEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::IndexMapEstimatorName));

        return typename BaseType::TransformerUniquePtr(new OneHotEncoderTransformer<InputT>(i_data.Value, _allowMissingValues));
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         OneHotEncoderEstimator
///  \brief         Creates a `OneHotEncoderTransformer` object.
///
template <
    typename InputT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class OneHotEncoderEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::HistogramEstimator<InputT, MaxNumTrainingItemsV>,
        Components::IndexMapEstimator<InputT, MaxNumTrainingItemsV>,
        Details::OneHotEncoderEstimatorImpl<InputT, MaxNumTrainingItemsV>
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
            Details::OneHotEncoderEstimatorImpl<InputT, MaxNumTrainingItemsV>
        >;

    using IndexMap                          = typename Components::IndexMapAnnotationData<InputT>::IndexMap;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    OneHotEncoderEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool allowMissingValues);
    OneHotEncoderEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool allowMissingValues, IndexMap existingValues);

    ~OneHotEncoderEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(OneHotEncoderEstimator);
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
// |  OneHotEncoderTransformer
// |
// ----------------------------------------------------------------------
template <typename InputT>
OneHotEncoderTransformer<InputT>::OneHotEncoderTransformer(IndexMap map, bool allowMissingValues) :
    Labels(
        std::move(
            [&map](void) ->  IndexMap & {
                if (map.size() == 0) {
                    throw std::invalid_argument("Index map is empty!");
                }
                return map;
            }()
        )
    ),
    AllowMissingValues(std::move(allowMissingValues)) {
}

template <typename InputT>
OneHotEncoderTransformer<InputT>::OneHotEncoderTransformer(Archive &ar) :
    OneHotEncoderTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            IndexMap                        map(Traits<IndexMap>::deserialize(ar));
            bool                            allowMissingValues(Traits<bool>::deserialize(ar));

            return OneHotEncoderTransformer(std::move(map), std::move(allowMissingValues));
        }()
    ) {
}

template <typename InputT>
void OneHotEncoderTransformer<InputT>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(Labels)>::serialize(ar, Labels);
    Traits<decltype(AllowMissingValues)>::serialize(ar, AllowMissingValues);
}

template <typename InputT>
bool OneHotEncoderTransformer<InputT>::operator==(OneHotEncoderTransformer const &other) const {
    return Labels == other.Labels
        && AllowMissingValues == other.AllowMissingValues;
}

// ----------------------------------------------------------------------
// |
// |  OneHotEncoderEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
OneHotEncoderEstimator<InputT, MaxNumTrainingItemsV>::OneHotEncoderEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool allowMissingValues) :
    OneHotEncoderEstimator(std::move(pAllColumnAnnotations), std::move(colIndex), std::move(allowMissingValues), IndexMap()) {
}

template <typename InputT, size_t MaxNumTrainingItemsV>
OneHotEncoderEstimator<InputT, MaxNumTrainingItemsV>::OneHotEncoderEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool allowMissingValues, IndexMap existingValues) :
    BaseType(
        "OneHotEncoderEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::HistogramEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex, &existingValues](void) { return Components::IndexMapEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex), std::move(existingValues)); },
        [pAllColumnAnnotations, colIndex, &allowMissingValues](void) { return Details::OneHotEncoderEstimatorImpl<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex), std::move(allowMissingValues)); }
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::OneHotEncoderEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename InputT, size_t MaxNumTrainingItemsV>
Details::OneHotEncoderEstimatorImpl<InputT, MaxNumTrainingItemsV>::OneHotEncoderEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool allowMissingValues) :
    BaseType("OneHotEncoderEstimatorImpl", std::move(pAllColumnAnnotations)),
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
bool Details::OneHotEncoderEstimatorImpl<InputT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename InputT, size_t MaxNumTrainingItemsV>
void Details::OneHotEncoderEstimatorImpl<InputT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizers
} // namespace Microsoft
