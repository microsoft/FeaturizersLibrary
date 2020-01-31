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
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override;
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
                                                                      std::uint32_t ngram_min, std::uint32_t ngram_max, bool binary,
                                                                      nonstd::optional<IndexMapType> vocabulary=nonstd::optional<IndexMapType>());
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
// |  CountVectorizerEstimator
// |
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
CountVectorizerEstimator<MaxNumTrainingItemsV>::CountVectorizerEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, bool lower,
                                                                                           AnalyzerMethod analyzer, std::string regex, std::float_t max_df,
                                                                                           std::float_t min_df, nonstd::optional<std::uint32_t> top_k_terms,
                                                                                           std::uint32_t ngram_min, std::uint32_t ngram_max, bool binary,
                                                                                           nonstd::optional<IndexMapType> vocabulary) :
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

} // namespace Featurizers
} // namespace Featurizer
} // namespace Mirosoft
