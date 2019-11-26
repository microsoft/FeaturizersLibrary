// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/InverseDocumentFrequencyEstimator.h"
#include "../Traits.h"
#include "Structs.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         CountVectorizerTransformer
///  \brief         Returns TFStruct for each unique input
///
class CountVectorizerTransformer : public StandardTransformer<std::string, TFStruct> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                           = StandardTransformer<std::string, TFStruct>;
    using IndexMapType                       = std::unordered_map<std::string, std::uint32_t>;
    using IterRangeType                      = std::tuple<std::string::const_iterator, std::string::const_iterator>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    IndexMapType const                       Labels;
    bool const                               Binary;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CountVectorizerTransformer(IndexMapType map, bool binary);
    CountVectorizerTransformer(Archive &ar);

    ~CountVectorizerTransformer(void) override = default;

    void save(Archive &ar) const override;

    bool operator==(CountVectorizerTransformer const &other) const;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems when the definition and declaration are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {

        typename std::map<IterRangeType, std::uint32_t, Components::IterRangeComp> ApperanceMap;

        //todo: will use vector<functor> after string header file is done
        Components::split_temp( 
            input, 
            [&ApperanceMap] (std::string::const_iterator & iter_start, std::string::const_iterator & iter_end) {
                
                typename std::map<IterRangeType, std::uint32_t, Components::IterRangeComp>::iterator iter_apperance(ApperanceMap.find(std::make_tuple(iter_start, iter_end)));
                
                if (iter_apperance != ApperanceMap.end()) {
                    ++iter_apperance->second;
                } else {
                    ApperanceMap.insert(std::make_pair(std::make_tuple(iter_start, iter_end), 1));
                }
            }
        );

        for (auto const & pair : ApperanceMap) {
            std::string const word = std::string(std::get<0>(pair.first), std::get<1>(pair.first));

            typename IndexMapType::const_iterator const      iter_label(Labels.find(word));

            if (iter_label != Labels.end()) {
                if (Binary) {
                    callback(TFStruct(static_cast<std::uint32_t>(iter_label->second), static_cast<std::uint32_t>(1)));
                } else {
                    callback(TFStruct(static_cast<std::uint32_t>(iter_label->second), static_cast<std::uint32_t>(pair.second)));
                }
            }
        }
                                                                                                         
    }
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         CountVectorizerEstimatorImpl
///  \brief         Estimator that uses the output of the 
///                 InverseDocumentFrequencyEstimator to provide useful
///                 information which helps calculation of CountVectorizer
template <size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class CountVectorizerEstimatorImpl : public TransformerEstimator<std::string, TFStruct> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<std::string, TFStruct>;
    using TransformerType                   = CountVectorizerTransformer;
    using IndexMapType                      = CountVectorizerTransformer::IndexMapType;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CountVectorizerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, std::float_t max_df, 
                                 std::float_t min_df, std::uint32_t max_features, IndexMapType vocabulary, bool binary);
    ~CountVectorizerEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(CountVectorizerEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                             _colIndex;
    
    std::float_t const                       _max_df;
    std::float_t const                       _min_df;
    std::uint32_t const                      _max_features;
    IndexMapType const                       _vocabulary;
    bool const                               _binary;

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
       
        using InverseDocumentFrequencyEstimator = Components::InverseDocumentFrequencyEstimator<MaxNumTrainingItemsV>;

        Components::InverseDocumentFrequencyAnnotationData const &      data(InverseDocumentFrequencyEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::InverseDocumentFrequencyEstimatorName));

        typename Components::InverseDocumentFrequencyAnnotationData::InverseDocumentFrequency const & 
                                                            docuApperance(data.TermFrequency);

        std::uint32_t const                                 totalNumDocus(data.TotalNumDocuments);
                   
        typename CountVectorizerTransformer::IndexMapType indexMap;

        if (!_vocabulary.empty()) {
            return std::make_unique<CountVectorizerTransformer>(_vocabulary, _binary);
        }

        for (auto const & pair : docuApperance) {
            std::float_t const freq = pair.second / static_cast<std::float_t>(totalNumDocus);

            if (freq >= _min_df && freq <= _max_df) 
                indexMap.insert(std::make_pair(pair.first, indexMap.size()));
        }

        return std::make_unique<CountVectorizerTransformer>(indexMap, _binary);
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         CountVectorizerEstimator
///  \brief         Creates a `CountVectorizerTransformer` object.
///
template <size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class CountVectorizerEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::InverseDocumentFrequencyEstimator<MaxNumTrainingItemsV>,
        Details::CountVectorizerEstimatorImpl<MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::InverseDocumentFrequencyEstimator<MaxNumTrainingItemsV>,
            Details::CountVectorizerEstimatorImpl<MaxNumTrainingItemsV>
        >;

    using IndexMapType              = CountVectorizerTransformer::IndexMapType;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CountVectorizerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, std::float_t max_df, std::float_t min_df, std::uint32_t max_features, IndexMapType vocabulary, bool binary);
    ~CountVectorizerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(CountVectorizerEstimator);
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
// |  CountVectorizerTransformer
// |
// ----------------------------------------------------------------------
CountVectorizerTransformer::CountVectorizerTransformer(IndexMapType map, bool binary) :
    Labels(
        std::move([&map](void) ->  IndexMapType & {
            if (map.size() == 0) {
                throw std::invalid_argument("Index map is empty!");
            }
            return map;
        }()
        )),
    Binary(std::move(binary)) {
}

CountVectorizerTransformer::CountVectorizerTransformer(Archive &ar) :
    // TODO: Labels(Traits<decltype(Labels)>::deserialize(ar)),
    Binary(Traits<decltype(Binary)>::deserialize(ar)) {
}

void CountVectorizerTransformer::save(Archive &ar) const /*override*/ {
    // TODO: Traits<decltype(Labels)>::serialize(ar, Labels);
    Traits<decltype(Binary)>::serialize(ar, Binary);
}

bool CountVectorizerTransformer::operator==(CountVectorizerTransformer const &other) const {
    return Labels == other.Labels
        && Binary == other.Binary;
}

// ----------------------------------------------------------------------
// |
// |  CountVectorizerEstimator
// |
// ----------------------------------------------------------------------

template <size_t MaxNumTrainingItemsV>
CountVectorizerEstimator<MaxNumTrainingItemsV>::CountVectorizerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, std::float_t max_df, std::float_t min_df, std::uint32_t max_features, IndexMapType vocabulary, bool binary) :
    BaseType(
        "CountVectorizerEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::InverseDocumentFrequencyEstimator<MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex, &max_df, &min_df, &max_features, &vocabulary, &binary](void) { 
            return Details::CountVectorizerEstimatorImpl<MaxNumTrainingItemsV>(
                std::move(pAllColumnAnnotations), 
                std::move(colIndex), 
                std::move(max_df), 
                std::move(min_df), 
                std::move(max_features), 
                std::move(vocabulary),
                std::move(binary)
            ); 
        }
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::CountVectorizerEstimatorImpl
// |
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
Details::CountVectorizerEstimatorImpl<MaxNumTrainingItemsV>::CountVectorizerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, std::float_t max_df, std::float_t min_df, std::uint32_t max_features, IndexMapType vocabulary, bool binary) :
    BaseType("CountVectorizerEstimatorImpl", std::move(pAllColumnAnnotations)),
    _colIndex(
        std::move(
            [this, &colIndex](void) -> size_t & {
                if(colIndex >= this->get_column_annotations().size())
                    throw std::invalid_argument("colIndex");

                return colIndex;
            }()
        )
    ),
    _max_df(
        std::move(
            [&max_df](void) -> std::float_t & {
                if(max_df > 1.0f || max_df < 0.0f)
                    throw std::invalid_argument("max_df");

                return max_df;
            }()
        )
    ),
    _min_df(
        std::move(
            [&min_df](void) -> std::float_t & {
                if(min_df > 1.0f || min_df < 0.0f)
                    throw std::invalid_argument("min_df");

                return min_df;
            }()
        )
    ),
    _max_features(std::move(max_features)),
    _vocabulary(std::move(vocabulary)),
    _binary(std::move(binary)) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
bool Details::CountVectorizerEstimatorImpl<MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <size_t MaxNumTrainingItemsV>
void Details::CountVectorizerEstimatorImpl<MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

}
}
}
