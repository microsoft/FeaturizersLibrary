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
template <typename TransformedT = SparseVectorEncoding<std::float_t>>
class TfidfVectorizerTransformer : public StandardTransformer<std::string, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                           = StandardTransformer<std::string, TransformedT>;
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
template <
    typename TransformedT = SparseVectorEncoding<std::float_t>,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class TfidfVectorizerEstimatorImpl : public TransformerEstimator<std::string, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<std::string, TransformedT>;
    using TransformerType                   = TfidfVectorizerTransformer<TransformedT>;
    using FrequencyMap                      = typename TfidfVectorizerTransformer<TransformedT>::FrequencyMap;
    using NormMethod                        = typename TfidfVectorizerTransformer<TransformedT>::NormMethod;
    using IndexMap                          = typename TfidfVectorizerTransformer<TransformedT>::IndexMap;
    using AnalyzerMethod                    = typename TfidfVectorizerTransformer<TransformedT>::AnalyzerMethod;

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
            new TfidfVectorizerTransformer<TransformedT>(
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
template <
    typename TransformedT = SparseVectorEncoding<std::float_t>,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class TfidfVectorizerEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::DocumentStatisticsEstimator<MaxNumTrainingItemsV>,
        Details::TfidfVectorizerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>
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
            Details::TfidfVectorizerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>
        >;

    using IndexMap                      = typename TfidfVectorizerTransformer<TransformedT>::IndexMap;
    using StringDecorator               = Components::Details::DocumentStatisticsTrainingOnlyPolicy::StringDecorator;
    using AnalyzerMethod                = Components::AnalyzerMethod;
    using NormMethod                    = typename TfidfVectorizerTransformer<TransformedT>::NormMethod;
    using TfidfPolicy                   = typename TfidfVectorizerTransformer<TransformedT>::TfidfPolicy;

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
// |  TfidfVectorizerTransformer
// |
// ----------------------------------------------------------------------
template <typename TransformedT>
TfidfVectorizerTransformer<TransformedT>::TfidfVectorizerTransformer(IndexMap labels,
                                                                     IndexMap docuFreq,
                                                                     std::uint32_t totalNumDocus,
                                                                     NormMethod norm,
                                                                     TfidfPolicy tfidfParameters,
                                                                     bool lowercase,
                                                                     AnalyzerMethod analyzer,
                                                                     std::string regexToken,
                                                                     std::uint32_t ngramRangeMin,
                                                                     std::uint32_t ngramRangeMax) :
    _labels(
        std::move(
            [&labels](void) ->  IndexMap & {
                if (labels.size() == 0) {
                    throw std::invalid_argument("Index map is empty!");
                }
                return labels;
            }()
        )
    ),
    _documentFreq(
        std::move(
            [&docuFreq](void) ->  IndexMap & {
                if (docuFreq.size() == 0) {
                    throw std::invalid_argument("DocumentFrequency map is empty!");
                }
                return docuFreq;
            }()
        )
    ),
    _totalNumsDocuments(std::move(totalNumDocus)),
    _norm(std::move(norm)),
    _tfidfParameters(std::move(tfidfParameters)),
    _lowercase(std::move(lowercase)),
    _analyzer(std::move(analyzer)),
    _regexToken(std::move(regexToken)),
    _ngramRangeMin(std::move(ngramRangeMin)),
    _ngramRangeMax(std::move(ngramRangeMax)),
    _parseFunc(Components::DocumentParseFuncGenerator(_analyzer, _regexToken, _ngramRangeMin, _ngramRangeMax)) {
}

template <typename TransformedT>
TfidfVectorizerTransformer<TransformedT>::TfidfVectorizerTransformer(Archive &ar) :
    TfidfVectorizerTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            IndexMap                       labels(Traits<IndexMap>::deserialize(ar));
            FrequencyMap                   docuFreq(Traits<FrequencyMap>::deserialize(ar));
            std::uint32_t                  totalNumDocus(Traits<std::uint32_t >::deserialize(ar));
            NormMethod                     norm(static_cast<NormMethod>(Traits<typename std::underlying_type<NormMethod>::type>::deserialize(ar)));
            TfidfPolicy                    tfidfParameters(static_cast<TfidfPolicy>(Traits<std::underlying_type<TfidfPolicy>::type>::deserialize(ar)));
            bool                           lowercase(Traits<bool>::deserialize(ar));
            AnalyzerMethod                 analyzer(static_cast<AnalyzerMethod>(Traits<std::underlying_type<AnalyzerMethod>::type>::deserialize(ar)));
            std::string                    regexToken(Traits<std::string>::deserialize(ar));
            std::uint32_t                  ngramRangeMin(Traits<std::uint32_t>::deserialize(ar));
            std::uint32_t                  ngramRangeMax(Traits<std::uint32_t>::deserialize(ar));

            return TfidfVectorizerTransformer(
                        std::move(labels),
                        std::move(docuFreq),
                        std::move(totalNumDocus),
                        std::move(norm),
                        std::move(tfidfParameters),
                        std::move(lowercase),
                        std::move(analyzer),
                        std::move(regexToken),
                        std::move(ngramRangeMin),
                        std::move(ngramRangeMax)
                    );
        }()
    ) {
}

template <typename TransformedT>
void TfidfVectorizerTransformer<TransformedT>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(_labels)>::serialize(ar, _labels);
    Traits<decltype(_documentFreq)>::serialize(ar, _documentFreq);
    Traits<decltype(_totalNumsDocuments)>::serialize(ar, _totalNumsDocuments);
    Traits<typename std::underlying_type<NormMethod>::type>::serialize(ar, static_cast<typename std::underlying_type<NormMethod>::type>(_norm));
    Traits<std::underlying_type<TfidfPolicy>::type>::serialize(ar, static_cast<std::underlying_type<TfidfPolicy>::type>(_tfidfParameters));
    Traits<decltype(_lowercase)>::serialize(ar, _lowercase);
    Traits<std::underlying_type<AnalyzerMethod>::type>::serialize(ar, static_cast<std::underlying_type<AnalyzerMethod>::type>(_analyzer));
    Traits<decltype(_regexToken)>::serialize(ar, _regexToken);
    Traits<decltype(_ngramRangeMin)>::serialize(ar, _ngramRangeMin);
    Traits<decltype(_ngramRangeMax)>::serialize(ar, _ngramRangeMax);
}

template <typename TransformedT>
bool TfidfVectorizerTransformer<TransformedT>::operator==(TfidfVectorizerTransformer const &other) const {
    return _labels == other._labels
        && _documentFreq == other._documentFreq
        && _totalNumsDocuments == other._totalNumsDocuments
        && _norm == other._norm
        && _tfidfParameters == other._tfidfParameters
        && _lowercase == other._lowercase
        && _analyzer == other._analyzer
        && _regexToken == other._regexToken
        && _ngramRangeMin == other._ngramRangeMin
        && _ngramRangeMax == other._ngramRangeMax;
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename TransformedT>
void TfidfVectorizerTransformer<TransformedT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    //termfrequency for specific document
    MapWithIterRange documentTermFrequency;

    std::string processedInput = Components::DocumentDecorator(input, _lowercase, _analyzer, _regexToken, _ngramRangeMin, _ngramRangeMax);

    _parseFunc(
        processedInput,
        [&documentTermFrequency] (std::string::const_iterator iterStart, std::string::const_iterator iterEnd) {
            MapWithIterRange::iterator docuTermFreqIter(documentTermFrequency.find(std::make_tuple(iterStart, iterEnd)));
            if (docuTermFreqIter != documentTermFrequency.end()) {
                ++docuTermFreqIter->second;
            } else {
                documentTermFrequency.insert(std::make_pair(std::make_tuple(iterStart, iterEnd), 1));
            }
        }
    );

    std::float_t normVal = 0.0f;
    std::vector<std::tuple<std::uint32_t, std::float_t>> results;
    for (auto const & wordIteratorPair : documentTermFrequency) {
        std::string const word(std::string(std::get<0>(wordIteratorPair.first), std::get<1>(wordIteratorPair.first)));

        IndexMap::const_iterator const      labelIter(_labels.find(word));

        if (labelIter != _labels.end()) {

            double tf;
            double idf;

            //calculate tf(term frequency) which measures how frequently a term occurs in a document.
            //Since every document is different in length, it is possible that a term would appear much more times
            //in long documents than shorter ones. Thus, the term frequency is often divided by the document length
            //(aka. the total number of terms in the document) as a way of normalization:
            //TF(t) = (Number of times term t appears in a document) / (Total number of terms in the document)
            //source:http://www.tfidf.com/
            if ((_tfidfParameters & TfidfPolicy::Binary) == TfidfPolicy::Binary) {
                tf = 1.0;
            } else if (!((_tfidfParameters & TfidfPolicy::SublinearTf) == TfidfPolicy::SublinearTf)) {
                tf = wordIteratorPair.second;
            } else {
                tf = 1.0 + std::log(wordIteratorPair.second);
            }

            //calculate idf(inverse document frequency) which measures how important a term is. While computing TF,
            //all terms are considered equally important. However it is known that certain terms, such as "is", "of",
            //and "that", may appear a lot of times but have little importance. Thus we need to weigh down the frequent
            //terms while scale up the rare ones, by computing the following:
            //IDF(t) = log_e(Total number of documents / Number of documents with term t in it).
            //source:http://www.tfidf.com/
            if (!((_tfidfParameters & TfidfPolicy::UseIdf) == TfidfPolicy::UseIdf)) {
                idf = 1.0;
            } else if ((_tfidfParameters & TfidfPolicy::SmoothIdf) == TfidfPolicy::SmoothIdf) {
                idf = 1.0 + std::log((1 + _totalNumsDocuments) / (1.0 + _documentFreq.at(word)));
            } else {
                idf = 1.0 + std::log((1 + _totalNumsDocuments) / (0.0 + _documentFreq.at(word)));
            }

            //calculate tfidf (tfidf = tf * idf)
            std::float_t tfidf = static_cast<std::float_t>(tf * idf);

            //calculate normVal
            if(_norm == NormMethod::L1) {
                assert(tfidf >= 0.0f);
                normVal += tfidf;
            } else if (_norm == NormMethod::L2) {
                normVal += tfidf * tfidf;
            }

            //temperarily put output in a vector for future normalization
            results.emplace_back(std::make_tuple(labelIter->second, tfidf));
        }
    }
    //normVal will be zero when the input is empty
    if (_norm == NormMethod::L1 || _norm == NormMethod::L2)
        assert(normVal >= 0.0f);
    else
        assert(normVal == 0.0f);

    // l2-norm calibration
    if (_norm == NormMethod::L2)
        normVal = sqrt(normVal);

    if (_norm == NormMethod::None)
        normVal = 1.0;

    std::vector<typename TransformedT::ValueEncoding> sparseVector;

    for (auto & result : results) {
        sparseVector.emplace_back(typename TransformedT::ValueEncoding(static_cast<typename TransformedT::value_type>(std::get<1>(result) / normVal), std::get<0>(result)));
    }

    std::sort(sparseVector.begin(), sparseVector.end(),
        [](typename TransformedT::ValueEncoding const &a, typename TransformedT::ValueEncoding const &b) {
            return a.Index < b.Index;
        }
    );

    callback(TransformedT(_labels.size(), std::move(sparseVector)));
}

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
template <typename TransformedT, size_t MaxNumTrainingItemsV>
TfidfVectorizerEstimator<TransformedT, MaxNumTrainingItemsV>::TfidfVectorizerEstimator(
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
            return Details::TfidfVectorizerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>(
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
template <typename TransformedT, size_t MaxNumTrainingItemsV>
Details::TfidfVectorizerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>::TfidfVectorizerEstimatorImpl(
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
template <typename TransformedT, size_t MaxNumTrainingItemsV>
bool Details::TfidfVectorizerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename TransformedT, size_t MaxNumTrainingItemsV>
void Details::TfidfVectorizerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
