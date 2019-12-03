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
class OneHotEncoderTransformer : public StandardTransformer<InputT, OneHotStruct> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = StandardTransformer<InputT, OneHotStruct>;
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

    void save(Archive &ar) const override;

    bool operator==(OneHotEncoderTransformer const &other) const;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems when the definition and declaration are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        typename IndexMap::const_iterator const         lable_iter(Labels.find(input));
        if(lable_iter == Labels.end()) {
            if(AllowMissingValues) {
                callback(OneHotStruct(0, static_cast<std::uint32_t>(Labels.size()) + 1, 1));
                return;
            }
            throw std::invalid_argument("'input' was not found");
        }
        // when missing values are allowed, the total size is increased by 1 and the 0th element in the vector represent missing values
        std::uint32_t offset = AllowMissingValues ? 1 : 0;
        callback(OneHotStruct(static_cast<std::uint32_t>(lable_iter->second + offset),   // category index
                              static_cast<std::uint32_t>(Labels.size() + offset),        // category total size
                              static_cast<std::uint32_t>(1)                              // number of appearances and
                                                                                         // this will just be 1 and 0 in one hot encoder
        ));
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
class OneHotEncoderEstimatorImpl : public TransformerEstimator<InputT, OneHotStruct> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, OneHotStruct>;
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

        return std::make_unique<OneHotEncoderTransformer<InputT>>(i_data.Value, _allowMissingValues);
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
        std::move([&map](void) ->  IndexMap & {
            if (map.size() == 0) {
                throw std::invalid_argument("Index map is empty!");
            }
            return map;
        }()
        )),
    AllowMissingValues(std::move(allowMissingValues)) {
}

template <typename InputT>
OneHotEncoderTransformer<InputT>::OneHotEncoderTransformer(Archive &ar) :
    // TODO: Labels(Traits<decltype(Labels)>::deserialize(ar)),
    AllowMissingValues(Traits<decltype(AllowMissingValues)>::deserialize(ar)) {
}

template <typename InputT>
void OneHotEncoderTransformer<InputT>::save(Archive &ar) const /*override*/ {
    // TODO: Traits<decltype(Labels)>::serialize(ar, Labels);
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

}
}
}
