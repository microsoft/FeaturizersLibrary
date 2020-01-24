// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/DocumentStatisticsEstimator.h"
#include "../Traits.h"
#include "Structs.h"
#include "../Strings.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         CountVectorizerTransformer
///  \brief         Returns SparseVectorEncoding<std::uint32_t> for each unique input
///
class CountVectorizerTransformer : public StandardTransformer<std::string, SparseVectorEncoding<std::uint32_t>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                           = StandardTransformer<std::string, SparseVectorEncoding<std::uint32_t>>;
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
    // |  Private Methodsa
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems when the definition and declaration are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {

        using ApperanceMapType = typename std::map<IterRangeType, std::uint32_t, Components::IterRangeComp>;

        ApperanceMapType apperanceMap;

        //todo: will use vector<functor> after string header file is done
        Strings::Parse<std::string::const_iterator>(
            input,
            [](char c) {return std::isspace(c);},
            [&apperanceMap] (std::string::const_iterator iter_start, std::string::const_iterator iter_end) {

                ApperanceMapType::iterator iter_apperance(apperanceMap.find(std::make_tuple(iter_start, iter_end)));

                if (iter_apperance != apperanceMap.end()) {
                    ++iter_apperance->second;
                } else {
                    apperanceMap.insert(std::make_pair(std::make_tuple(iter_start, iter_end), 1));
                }
            }
        );
        std::vector<SparseVectorEncoding<std::uint32_t>::ValueEncoding> result;

        for (auto const & pair : apperanceMap) {
            std::string const word = std::string(std::get<0>(pair.first), std::get<1>(pair.first));

            typename IndexMapType::const_iterator const      iter_label(Labels.find(word));

            if (iter_label != Labels.end()) {
                if (Binary) {
                    result.emplace_back(SparseVectorEncoding<std::uint32_t>::ValueEncoding(1, iter_label->second));
                } else {
                    result.emplace_back(SparseVectorEncoding<std::uint32_t>::ValueEncoding(pair.second, iter_label->second));
                }
            }
        }
        std::sort(result.begin(), result.end(),
            [](SparseVectorEncoding<std::uint32_t>::ValueEncoding const &a, SparseVectorEncoding<std::uint32_t>::ValueEncoding const &b) {
                return a.Index < b.Index;
            }
        );
        callback(SparseVectorEncoding<std::uint32_t>(Labels.size(), std::move(result)));

    }
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         CountVectorizerEstimatorImpl
///  \brief         Estimator that uses the output of the
///                 DocumentStatisticsEstimator to provide useful
///                 information which helps calculation of CountVectorizer
template <size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class CountVectorizerEstimatorImpl : public TransformerEstimator<std::string, SparseVectorEncoding<std::uint32_t>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<std::string, SparseVectorEncoding<std::uint32_t>>;
    using TransformerType                   = CountVectorizerTransformer;
    using IndexMapType                      = CountVectorizerTransformer::IndexMapType;
    using StringDecorator                   = std::function<std::string (std::string)>;
    using AnalyzerMethod                    = Components::Details::DocumentStatisticsTrainingOnlyPolicy::AnalyzerMethod;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CountVectorizerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool binary);
    ~CountVectorizerEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(CountVectorizerEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                             _colIndex;

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

        using DocumentStatisticsEstimator = Components::DocumentStatisticsEstimator<MaxNumTrainingItemsV>;

        Components::DocumentStatisticsAnnotationData const &      data(DocumentStatisticsEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::DocumentStatisticsEstimatorName));

        typename Components::DocumentStatisticsAnnotationData::FrequencyAndIndexMap const &
                                                            freqAndIndex(data.TermFrequencyAndIndex);


        typename CountVectorizerTransformer::IndexMapType indexMap;


        for (auto const & pair : freqAndIndex) {
            indexMap.insert(std::make_pair(pair.first, pair.second.Index));
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
        Components::DocumentStatisticsEstimator<MaxNumTrainingItemsV>,
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
            Components::DocumentStatisticsEstimator<MaxNumTrainingItemsV>,
            Details::CountVectorizerEstimatorImpl<MaxNumTrainingItemsV>
        >;

    using IndexMapType              = CountVectorizerTransformer::IndexMapType;
    using StringDecorator                   = std::function<std::string (std::string)>;
    using AnalyzerMethod                    = Components::Details::DocumentStatisticsTrainingOnlyPolicy::AnalyzerMethod;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CountVectorizerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, StringDecorator decorator,
                                                                      AnalyzerMethod analyzer, std::string regex, std::float_t max_df,
                                                                      std::float_t min_df, nonstd::optional<std::uint32_t> top_k_terms,
                                                                      nonstd::optional<IndexMapType> vocabulary,
                                                                      std::uint32_t ngram_min, std::uint32_t ngram_max, bool binary);
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
CountVectorizerEstimator<MaxNumTrainingItemsV>::CountVectorizerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, StringDecorator decorator,
                                                                                           AnalyzerMethod analyzer, std::string regex, std::float_t max_df,
                                                                                           std::float_t min_df, nonstd::optional<std::uint32_t> top_k_terms,
                                                                                           nonstd::optional<IndexMapType> vocabulary,
                                                                                           std::uint32_t ngram_min, std::uint32_t ngram_max, bool binary) :
    BaseType(
        "CountVectorizerEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex, &decorator, &analyzer, &regex, &vocabulary, &top_k_terms, &min_df, &max_df, &ngram_min, &ngram_max](void) { return Components::DocumentStatisticsEstimator<MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex),
                                                                                                                                                                                                                           std::move(decorator), std::move(analyzer), std::move(regex),
                                                                                                                                                                                                                           std::move(vocabulary), std::move(top_k_terms), std::move(min_df),
                                                                                                                                                                                                                           std::move(max_df), std::move(ngram_min), std::move(ngram_max)); },
        [pAllColumnAnnotations, colIndex, &binary](void) {
            return Details::CountVectorizerEstimatorImpl<MaxNumTrainingItemsV>(
                std::move(pAllColumnAnnotations),
                std::move(colIndex),
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
Details::CountVectorizerEstimatorImpl<MaxNumTrainingItemsV>::CountVectorizerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool binary) :
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
