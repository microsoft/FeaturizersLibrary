// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/DocumentStatisticsEstimator.h"
#include "Structs.h"
#include "../Traits.h"
#include "../Strings.h"

#include <cmath>

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \fn            TfidfPolicy
///  \brief         Contains 4 Tfidf parameters for using bit flags
///
enum class TfidfPolicy : unsigned int {
    //Binary: If True, all non zero counts are set to 1.
    //This is useful for discrete probabilistic models that model binary events rather than integer counts.
    Binary = 1 << 0,
    UseIdf = 1 << 1,
    SmoothIdf = 1 << 2,
    SublinearTf = 1 << 3
};

//override | and & operator for TfidfPolicy
constexpr TfidfPolicy operator|(TfidfPolicy const & a, TfidfPolicy const & b);
constexpr TfidfPolicy operator&(TfidfPolicy const & a, TfidfPolicy const & b);

/////////////////////////////////////////////////////////////////////////
///  \class         TfidfVectorizerTransformer
///  \brief         Returns a unique TFIDFStruct for each input.
///
class TfidfVectorizerTransformer : public StandardTransformer<std::string, SparseVectorEncoding<std::float_t>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                           = StandardTransformer<std::string, SparseVectorEncoding<std::float_t>>;
    using IndexMap                           = std::unordered_map<std::string, std::uint32_t>;
    using FrequencyMap                       = IndexMap;
    using IterRangeType                      = std::tuple<std::string::const_iterator, std::string::const_iterator>;
    using MapWithIterRange                   = std::map<IterRangeType, std::uint32_t, Components::IterRangeComp>;
    using AnalyzerMethod                     = Components::AnalyzerMethod;
    using StringIterator                     = std::string::const_iterator;
    using TfidfPolicy                        = Microsoft::Featurizer::Featurizers::TfidfPolicy;

    enum class NormMethod : unsigned char {
        L1 = 1,
        L2 = 2,
        None = 3
    };

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    explicit TfidfVectorizerTransformer(
        IndexMap labels,
        FrequencyMap docuFreq,
        std::uint32_t totalNumDocus,
        NormMethod norm,
        TfidfPolicy tfidfParameters,
        bool lowercase,
        AnalyzerMethod analyzer,
        std::string regexToken,
        std::uint32_t ngramRangeMin,
        std::uint32_t ngramRangeMax
    );
    explicit TfidfVectorizerTransformer(Archive &ar);

    ~TfidfVectorizerTransformer(void) override = default;

    void save(Archive &ar) const override;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TfidfVectorizerTransformer);

    bool operator==(TfidfVectorizerTransformer const &other) const;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using ParseFunctionType                  = std::function<
                                                   void (std::string const &,
                                                   std::function<void (StringIterator, StringIterator)> const &)
                                               >;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    IndexMap const                          _labels;
    FrequencyMap const                      _documentFreq;
    std::uint32_t const                     _totalNumsDocuments;
    NormMethod const                        _norm;
    TfidfPolicy const                       _tfidfParameters;

    //data for execute same parse function as in documentstatisticestimator
    bool const                              _lowercase;
    AnalyzerMethod const                    _analyzer;
    std::string const                       _regexToken;
    std::uint32_t const                     _ngramRangeMin;
    std::uint32_t const                     _ngramRangeMax;

    ParseFunctionType const                 _parseFunc;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override;
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         TfidfVectorizerEstimatorImpl
///  \brief         Estimator that uses the output of the
///                 InverseDocumentFrequencyEstimator to provide useful
///                 information which helps calculation of TfidfVectorizer
///
template <size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class TfidfVectorizerEstimatorImpl : public TransformerEstimator<std::string, SparseVectorEncoding<std::float_t>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<std::string, SparseVectorEncoding<std::float_t>>;
    using TransformerType                   = TfidfVectorizerTransformer;
    using IndexMap                          = TfidfVectorizerTransformer::IndexMap;
    using FrequencyMap                      = TfidfVectorizerTransformer::FrequencyMap;
    using NormMethod                        = TfidfVectorizerTransformer::NormMethod;
    using AnalyzerMethod                    = TfidfVectorizerTransformer::AnalyzerMethod;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TfidfVectorizerEstimatorImpl(
        AnnotationMapsPtr pAllColumnAnnotations,
        size_t colIndex,
        NormMethod norm,
        TfidfPolicy tfidfParameters,
        bool lowercase,
        AnalyzerMethod analyzer,
        std::string regexToken,
        std::uint32_t ngramRangeMin,
        std::uint32_t ngramRangeMax
    );
    ~TfidfVectorizerEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TfidfVectorizerEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;
    NormMethod const                        _norm;
    TfidfPolicy const                       _tfidfParameters;

    bool const                              _lowercase;
    AnalyzerMethod const                    _analyzer;
    std::string const                       _regexToken;
    std::uint32_t const                     _ngramRangeMin;
    std::uint32_t const                     _ngramRangeMax;

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
        using DocumentStatisticsAnnotationData          = Components::DocumentStatisticsAnnotationData;
        using DocumentStatisticsEstimator               = Components::DocumentStatisticsEstimator<MaxNumTrainingItemsV>;
        // ----------------------------------------------------------------------

        DocumentStatisticsAnnotationData const &        data(DocumentStatisticsEstimator::get_annotation_data(BaseType::get_column_annotations(), _colIndex, Components::DocumentStatisticsEstimatorName));

        typename DocumentStatisticsAnnotationData::FrequencyAndIndexMap const &
                                                        termFrequencyAndIndex(data.TermFrequencyAndIndex);
        std::uint32_t const                             totalNumDocus(data.TotalNumDocuments);

        FrequencyMap termFrequencys;
        IndexMap termIndexes;
        for (auto const & termFrequencyAndIndexPair : termFrequencyAndIndex) {
            //termFrequency and termIndex share the exactly same keys
            termFrequencys.insert(std::make_pair(termFrequencyAndIndexPair.first, termFrequencyAndIndexPair.second.TermFrequency));
            termIndexes.insert(std::make_pair(termFrequencyAndIndexPair.first, termFrequencyAndIndexPair.second.Index));
        }

        return typename BaseType::TransformerUniquePtr(
            new TfidfVectorizerTransformer(
                std::move(termIndexes),
                std::move(termFrequencys),
                std::move(totalNumDocus),
                std::move(_norm),
                std::move(_tfidfParameters),
                std::move(_lowercase),
                std::move(_analyzer),
                std::move(_regexToken),
                std::move(_ngramRangeMin),
                std::move(_ngramRangeMax)
            )
        );
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         TfidfVectorizerEstimator
///  \brief         Creates a `TfidfVectorizerTransformer` object.
///
template <size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class TfidfVectorizerEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::DocumentStatisticsEstimator<MaxNumTrainingItemsV>,
        Details::TfidfVectorizerEstimatorImpl<MaxNumTrainingItemsV>
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
            Details::TfidfVectorizerEstimatorImpl<MaxNumTrainingItemsV>
        >;

    using IndexMap                      = TfidfVectorizerTransformer::IndexMap;
    using StringDecorator               = Components::Details::DocumentStatisticsTrainingOnlyPolicy::StringDecorator;
    using AnalyzerMethod                = Components::AnalyzerMethod;
    using NormMethod                    = TfidfVectorizerTransformer::NormMethod;
    using TfidfPolicy                   = TfidfVectorizerTransformer::TfidfPolicy;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TfidfVectorizerEstimator(
        AnnotationMapsPtr pAllColumnAnnotations,
        size_t colIndex,
        bool lowercase,
        AnalyzerMethod analyzer,
        std::string regex,
        NormMethod norm = NormMethod::L2,
        TfidfPolicy tfidfParameters = TfidfPolicy::UseIdf|TfidfPolicy::SmoothIdf,
        std::float_t minDf = 0.0f,
        std::float_t maxDf = 1.0f,
        nonstd::optional<std::uint32_t> topKTerms = nonstd::optional<std::uint32_t>(),
        std::uint32_t ngramRangeMin = 1,
        std::uint32_t ngramRangeMax = 1,
        nonstd::optional<IndexMap> vocabulary = nonstd::optional<IndexMap>()
    );
    ~TfidfVectorizerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TfidfVectorizerEstimator);
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
// |  TfidfPolicy
// |
// ----------------------------------------------------------------------
inline constexpr TfidfPolicy operator|(TfidfPolicy const & a, TfidfPolicy const & b) {
    return static_cast<TfidfPolicy>(
        static_cast<std::uint32_t>(a)
        | static_cast<std::uint32_t>(b)
    );
}

inline constexpr TfidfPolicy operator&(TfidfPolicy const & a, TfidfPolicy const & b) {
    return static_cast<TfidfPolicy>(
        static_cast<std::uint32_t>(a)
        & static_cast<std::uint32_t>(b)
    );
}

// ----------------------------------------------------------------------
// |
// |  TfidfVectorizerEstimator
// |
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
TfidfVectorizerEstimator<MaxNumTrainingItemsV>::TfidfVectorizerEstimator(
    AnnotationMapsPtr pAllColumnAnnotations,
    size_t colIndex,
    bool lowercase,
    AnalyzerMethod analyzer,
    std::string regex,
    NormMethod norm,
    TfidfPolicy tfidfParameters,
    std::float_t minDf,
    std::float_t maxDf,
    nonstd::optional<std::uint32_t> topKTerms,
    std::uint32_t ngramRangeMin,
    std::uint32_t ngramRangeMax,
    nonstd::optional<IndexMap> vocabulary
) :
    BaseType(
        "TfidfVectorizerEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex, lowercase, analyzer, regex, &vocabulary, &topKTerms, &minDf, &maxDf, ngramRangeMin, ngramRangeMax](void) {
            StringDecorator decorator = lowercase ? Microsoft::Featurizer::Strings::ToLower : StringDecorator();
            return Components::DocumentStatisticsEstimator<MaxNumTrainingItemsV>(
                std::move(pAllColumnAnnotations),
                std::move(colIndex),
                std::move(decorator),
                std::move(analyzer),
                std::move(regex),
                std::move(vocabulary),
                std::move(topKTerms),
                std::move(minDf),
                std::move(maxDf),
                std::move(ngramRangeMin),
                std::move(ngramRangeMax)
            );
        },
        [pAllColumnAnnotations, colIndex, &norm, &tfidfParameters, lowercase, analyzer, regex, ngramRangeMin, ngramRangeMax](void) {
            return Details::TfidfVectorizerEstimatorImpl<MaxNumTrainingItemsV>(
                std::move(pAllColumnAnnotations),
                std::move(colIndex),
                std::move(norm),
                std::move(tfidfParameters),
                std::move(lowercase),
                std::move(analyzer),
                std::move(regex),
                std::move(ngramRangeMin),
                std::move(ngramRangeMax)
            );
        }
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::TfidfVectorizerEstimatorImpl
// |
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
Details::TfidfVectorizerEstimatorImpl<MaxNumTrainingItemsV>::TfidfVectorizerEstimatorImpl(
    AnnotationMapsPtr pAllColumnAnnotations,
    size_t colIndex,
    NormMethod norm,
    TfidfPolicy tfidfParameters,
    bool lowercase,
    AnalyzerMethod analyzer,
    std::string regexToken,
    std::uint32_t ngramRangeMin,
    std::uint32_t ngramRangeMax
) :
    BaseType("TfidfVectorizerEstimatorImpl", std::move(pAllColumnAnnotations)),
    _colIndex(
        std::move(
            [this, &colIndex](void) -> size_t & {
                if(colIndex >= this->get_column_annotations().size())
                    throw std::invalid_argument("colIndex");

                return colIndex;
            }()
        )
    ),
    _norm(std::move(norm)),
    _tfidfParameters(std::move(tfidfParameters)),
    _lowercase(std::move(lowercase)),
    _analyzer(std::move(analyzer)),
    _regexToken(std::move(regexToken)),
    _ngramRangeMin(std::move(ngramRangeMin)),
    _ngramRangeMax(std::move(ngramRangeMax)) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
bool Details::TfidfVectorizerEstimatorImpl<MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <size_t MaxNumTrainingItemsV>
void Details::TfidfVectorizerEstimatorImpl<MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
