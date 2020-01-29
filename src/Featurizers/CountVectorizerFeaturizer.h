// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/DocumentStatisticsEstimator.h"
#include "../Traits.h"
#include "../Strings.h"
#include "Structs.h"

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
    using AnalyzerMethod                     = Components::AnalyzerMethod;


    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CountVectorizerTransformer(IndexMapType map, bool binary, bool lower, AnalyzerMethod analyzer, std::string regex, std::uint32_t ngram_min, std::uint32_t ngram_max);
    CountVectorizerTransformer(Archive &ar);

    ~CountVectorizerTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(CountVectorizerTransformer);

    void save(Archive &ar) const override;

    bool operator==(CountVectorizerTransformer const &other) const;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using IterRangeType                      = std::tuple<std::string::const_iterator, std::string::const_iterator>;
    using AppearanceMapType                  = typename std::map<IterRangeType, std::uint32_t, Components::IterRangeComp>;
    using StringIterator                     = std::string::const_iterator;
    using ParseFunctionType                  = std::function<
                                                   void (std::string const &,
                                                   std::function<void (StringIterator, StringIterator)> const &)
                                               >;
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    IndexMapType const                       _labels;
    bool const                               _binary;

    //data for execute same parse function as in documentstatisticestimator
    bool const                               _lower;
    AnalyzerMethod const                     _analyzer;
    std::string const                        _regex;
    std::uint32_t const                      _ngram_min;
    std::uint32_t const                      _ngram_max;


    ParseFunctionType const                  _parse_func;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methodsa
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems when the definition and declaration are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {

        AppearanceMapType appearanceMap;

        std::string processedInput(Components::DocumentDecorator(input, _lower, _analyzer, _regex, _ngram_min, _ngram_max));

        _parse_func(
            processedInput,
            [&appearanceMap] (std::string::const_iterator iter_start, std::string::const_iterator iter_end) {

                AppearanceMapType::iterator iter_apperance(appearanceMap.find(std::make_tuple(iter_start, iter_end)));

                if (iter_apperance != appearanceMap.end()) {
                    ++iter_apperance->second;
                } else {
                    appearanceMap.insert(std::make_pair(std::make_tuple(iter_start, iter_end), 1));
                }
            }
        );

        std::vector<SparseVectorEncoding<std::uint32_t>::ValueEncoding> result;

        for (auto const & wordAppearance : appearanceMap) {
            std::string const word = std::string(std::get<0>(wordAppearance.first), std::get<1>(wordAppearance.first));

            typename IndexMapType::const_iterator const      iter_label(_labels.find(word));

            if (iter_label != _labels.end()) {
                if (_binary) {
                    result.emplace_back(SparseVectorEncoding<std::uint32_t>::ValueEncoding(1, iter_label->second));
                } else {
                    result.emplace_back(SparseVectorEncoding<std::uint32_t>::ValueEncoding(wordAppearance.second, iter_label->second));
                }
            }
        }
        // SparseVectorEncoding requires ValueEncoding to be in order
        // so we sort result before creating SparseVectorEncoding
        std::sort(result.begin(), result.end(),
            [](SparseVectorEncoding<std::uint32_t>::ValueEncoding const &a, SparseVectorEncoding<std::uint32_t>::ValueEncoding const &b) {
                return a.Index < b.Index;
            }
        );
        callback(SparseVectorEncoding<std::uint32_t>(_labels.size(), std::move(result)));

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
    using AnalyzerMethod                    = Components::AnalyzerMethod;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CountVectorizerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool binary, bool lower, AnalyzerMethod analyzer, std::string regex, std::uint32_t ngram_min, std::uint32_t ngram_max);
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

    //data for execute same parse function as in documentstatisticestimator
    bool const                               _lower;
    AnalyzerMethod const                     _analyzer;
    std::string const                        _regex;
    std::uint32_t const                      _ngram_min;
    std::uint32_t const                      _ngram_max;

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
                                                            freqAndIndexes(data.TermFrequencyAndIndex);


        typename CountVectorizerTransformer::IndexMapType indexMap;


        for (auto const & freqAndIndex : freqAndIndexes) {
            indexMap.insert(std::make_pair(freqAndIndex.first, freqAndIndex.second.Index));
        }

        return typename BaseType::TransformerUniquePtr(new CountVectorizerTransformer(indexMap, _binary, _lower, _analyzer, _regex, _ngram_min, _ngram_max));
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

    using IndexMapType                      = CountVectorizerTransformer::IndexMapType;
    using StringDecorator                   = std::function<std::string (std::string)>;
    using AnalyzerMethod                    = Components::AnalyzerMethod;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CountVectorizerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool lower,
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
CountVectorizerTransformer::CountVectorizerTransformer(IndexMapType map, bool binary, bool lower, AnalyzerMethod analyzer, std::string regex, std::uint32_t ngram_min, std::uint32_t ngram_max) :
    _labels(
        std::move([&map](void) ->  IndexMapType & {
            if (map.size() == 0) {
                throw std::invalid_argument("Index map is empty!");
            }
            return map;
        }()
        )),
    _binary(std::move(binary)),
    _lower(std::move(lower)),
    _analyzer(std::move(analyzer)),
    _regex(std::move(regex)),
    _ngram_min(
        std::move(
            [&ngram_min](void) -> std::uint32_t & {
                if(ngram_min == 0)
                    throw std::invalid_argument("ngramRangeMin");

                return ngram_min;
            }()
        )),
    _ngram_max(
        std::move(
            [&ngram_max](void) -> std::uint32_t & {
                if(ngram_max == 0)
                    throw std::invalid_argument("ngramRangeMax");

                return ngram_max;
            }()
        )),
    _parse_func(
        [this](void) -> ParseFunctionType {
            ParseFunctionType parseFunc;
            DocumentParseFuncGenerator(parseFunc, _analyzer, _regex, _ngram_min, _ngram_max);
            return parseFunc;
        }()
    ) {
}

CountVectorizerTransformer::CountVectorizerTransformer(Archive &ar) :
    CountVectorizerTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            IndexMapType           labels(Traits<IndexMapType>::deserialize(ar));
            bool                   binary(Traits<bool>::deserialize(ar));

            bool                   lower(Traits<bool>::deserialize(ar));
            AnalyzerMethod         analyzer(static_cast<AnalyzerMethod>(Traits<std::uint8_t>::deserialize(ar)));
            std::string            regex(Traits<std::string>::deserialize(ar));
            std::uint32_t          ngram_min(Traits<std::uint32_t>::deserialize(ar));
            std::uint32_t          ngram_max(Traits<std::uint32_t>::deserialize(ar));

            return CountVectorizerTransformer(std::move(labels), std::move(binary), std::move(lower), std::move(analyzer), std::move(regex), std::move(ngram_min), std::move(ngram_max));
        }()
    ) {
}

void CountVectorizerTransformer::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(_labels)>::serialize(ar, _labels);
    Traits<decltype(_binary)>::serialize(ar, _binary);
    Traits<decltype(_lower)>::serialize(ar, _lower);
    Traits<std::uint8_t>::serialize(ar, static_cast<std::uint8_t>(_analyzer));
    Traits<decltype(_regex)>::serialize(ar, _regex);
    Traits<decltype(_ngram_min)>::serialize(ar, _ngram_min);
    Traits<decltype(_ngram_max)>::serialize(ar, _ngram_max);
}

bool CountVectorizerTransformer::operator==(CountVectorizerTransformer const &other) const {
    return _labels == other._labels
        && _binary == other._binary
        && _lower == other._lower
        && _analyzer == other._analyzer
        && _regex == other._regex
        && _ngram_min == other._ngram_min
        && _ngram_max == other._ngram_max;
}

// ----------------------------------------------------------------------
// |
// |  CountVectorizerEstimator
// |
// ----------------------------------------------------------------------

template <size_t MaxNumTrainingItemsV>
CountVectorizerEstimator<MaxNumTrainingItemsV>::CountVectorizerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool lower,
                                                                                           AnalyzerMethod analyzer, std::string regex, std::float_t max_df,
                                                                                           std::float_t min_df, nonstd::optional<std::uint32_t> top_k_terms,
                                                                                           nonstd::optional<IndexMapType> vocabulary,
                                                                                           std::uint32_t ngram_min, std::uint32_t ngram_max, bool binary) :
    BaseType(
        "CountVectorizerEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex, lower, analyzer, regex, &vocabulary, &top_k_terms, &min_df, &max_df, ngram_min, ngram_max](void) {
            StringDecorator decorator = lower ? Microsoft::Featurizer::Strings::ToLower : StringDecorator();
            return Components::DocumentStatisticsEstimator<MaxNumTrainingItemsV>(
                std::move(pAllColumnAnnotations),
                std::move(colIndex),
                std::move(decorator),
                std::move(analyzer),
                std::move(regex),
                std::move(vocabulary),
                std::move(top_k_terms),
                std::move(min_df),
                std::move(max_df),
                std::move(ngram_min),
                std::move(ngram_max)
                );
        },
        [pAllColumnAnnotations, colIndex, &binary, &lower, &analyzer, &regex, &ngram_min, &ngram_max](void) {
            return Details::CountVectorizerEstimatorImpl<MaxNumTrainingItemsV>(
                std::move(pAllColumnAnnotations),
                std::move(colIndex),
                std::move(binary),
                std::move(lower),
                std::move(analyzer),
                std::move(regex),
                std::move(ngram_min),
                std::move(ngram_max)
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
Details::CountVectorizerEstimatorImpl<MaxNumTrainingItemsV>::CountVectorizerEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool binary, bool lower, AnalyzerMethod analyzer, std::string regex, std::uint32_t ngram_min, std::uint32_t ngram_max) :
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
    _binary(std::move(binary)),
    _lower(std::move(lower)),
    _analyzer(std::move(analyzer)),
    _regex(std::move(regex)),
    _ngram_min(std::move(ngram_min)),
    _ngram_max(std::move(ngram_max)) {
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
