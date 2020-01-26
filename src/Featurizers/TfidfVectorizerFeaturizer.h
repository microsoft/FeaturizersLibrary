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

    // ----------------------------------------------------------------------
    // |
    // |  Public Class
    // |
    // ----------------------------------------------------------------------
    enum class NormMethod : unsigned char {
        L1 = 1,
        L2 = 2
    };

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    IndexMap const                           Labels;
    FrequencyMap const                       DocumentFreq;
    std::uint32_t const                      TotalNumsDocuments;
    NormMethod const                         Norm;
    TfidfPolicy const                        TfidfParameters;

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
        TfidfPolicy tfidfParameters
    );
    explicit TfidfVectorizerTransformer(Archive &ar);

    ~TfidfVectorizerTransformer(void) override = default;

    void save(Archive &ar) const override;

    bool operator==(TfidfVectorizerTransformer const &other) const;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems when the definition and declaration are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        //termfrequency for specific document
        MapWithIterRange documentTermFrequency;

        //todo: will use vector<functor> after string header file is done
        Strings::Parse<std::string::const_iterator>(
            input,
            [](char c) {return std::isspace(c);},
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

            IndexMap::const_iterator const      labelIter(Labels.find(word));

            if (labelIter != Labels.end()) {

                std::float_t tf;
                std::float_t idf;

                //calculate tf(term frequency) which measures how frequently a term occurs in a document.
                //Since every document is different in length, it is possible that a term would appear much more times
                //in long documents than shorter ones. Thus, the term frequency is often divided by the document length
                //(aka. the total number of terms in the document) as a way of normalization:
                //TF(t) = (Number of times term t appears in a document) / (Total number of terms in the document)
                //source:http://www.tfidf.com/
                if ((TfidfParameters & TfidfPolicy::Binary) == TfidfPolicy::Binary) {
                    tf = 1.0f;
                } else if (!((TfidfParameters & TfidfPolicy::SublinearTf) == TfidfPolicy::SublinearTf)) {
                    tf = wordIteratorPair.second;
                } else {
                    tf = 1.0f + std::log(static_cast<std::float_t>(wordIteratorPair.second));
                }

                //calculate idf(inverse document frequency) which measures how important a term is. While computing TF,
                //all terms are considered equally important. However it is known that certain terms, such as "is", "of",
                //and "that", may appear a lot of times but have little importance. Thus we need to weigh down the frequent
                //terms while scale up the rare ones, by computing the following:
                //IDF(t) = log_e(Total number of documents / Number of documents with term t in it).
                //source:http://www.tfidf.com/
                if (!((TfidfParameters & TfidfPolicy::UseIdf) == TfidfPolicy::UseIdf)) {
                    idf = 1.0f;
                } else if ((TfidfParameters & TfidfPolicy::SmoothIdf) == TfidfPolicy::SmoothIdf) {
                    idf = 1.0f + std::log((1 + TotalNumsDocuments) / (1.0f + static_cast<std::float_t>(DocumentFreq.at(word))));
                } else {
                    idf = 1.0f + std::log((1 + TotalNumsDocuments) / static_cast<std::float_t>(DocumentFreq.at(word)));
                }

                //calculate tfidf (tfidf = tf * idf)
                std::float_t tfidf = tf * idf;

                //calculate normVal
                if(Norm == NormMethod::L1) {
                    normVal += abs(tfidf);
                } else if (Norm == NormMethod::L2) {
                    normVal += tfidf * tfidf;
                }

                //temperarily put output in a vector for future normalization
                results.emplace_back(std::make_tuple(labelIter->second, tfidf));
            }
        }
        //normVal will never be 0 as long as results is not empty
        assert(normVal != 0.0f);

        // l2-norm calibration
        if (Norm == NormMethod::L2)
            normVal = sqrt(normVal);

        std::vector<SparseVectorEncoding<std::float_t>::ValueEncoding> sparseVector;

        for (auto & result : results) {
            sparseVector.emplace_back(SparseVectorEncoding<std::float_t>::ValueEncoding(std::get<1>(result) / normVal, std::get<0>(result)));
        }

        std::sort(sparseVector.begin(), sparseVector.end(),
            [](SparseVectorEncoding<std::float_t>::ValueEncoding const &a, SparseVectorEncoding<std::float_t>::ValueEncoding const &b) {
                return a.Index < b.Index;
            }
        );

        callback(SparseVectorEncoding<std::float_t>(Labels.size(), std::move(sparseVector)));
    }

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
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TfidfVectorizerEstimatorImpl(
        AnnotationMapsPtr pAllColumnAnnotations,
        size_t colIndex,
        NormMethod norm,
        TfidfPolicy tfidfParameters
    );
    ~TfidfVectorizerEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TfidfVectorizerEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                             _colIndex;
    NormMethod const                         _norm;
    TfidfPolicy const                        _tfidfParameters;

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

        return typename BaseType::TransformerUniquePtr(new TfidfVectorizerTransformer(
                                                            std::move(termIndexes),
                                                            std::move(termFrequencys),
                                                            std::move(totalNumDocus),
                                                            std::move(_norm),
                                                            std::move(_tfidfParameters)
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
    using AnalyzerMethod                = Components::Details::DocumentStatisticsTrainingOnlyPolicy::AnalyzerMethod;
    using NormMethod                    = TfidfVectorizerTransformer::NormMethod;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TfidfVectorizerEstimator(
        AnnotationMapsPtr pAllColumnAnnotations,
        size_t colIndex,
        StringDecorator decorator,
        AnalyzerMethod analyzer,
        std::string regex,
        std::float_t minDf = 0.0f,
        std::float_t maxDf = 1.0f,
        nonstd::optional<std::uint32_t> topKTerms = nonstd::optional<std::uint32_t>(),
        nonstd::optional<IndexMap> vocabulary = nonstd::optional<IndexMap>(),
        std::uint32_t ngramRangeMin = 1,
        std::uint32_t ngramRangeMax = 1,
        NormMethod norm = NormMethod::L2,
        TfidfPolicy tfidfParameters = TfidfPolicy::UseIdf|TfidfPolicy::SmoothIdf
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
constexpr TfidfPolicy operator|(TfidfPolicy const & a, TfidfPolicy const & b) {
    return static_cast<TfidfPolicy>(
        static_cast<unsigned int>(a)
        | static_cast<unsigned int>(b)
    );
}

constexpr TfidfPolicy operator&(TfidfPolicy const & a, TfidfPolicy const & b) {
    return static_cast<TfidfPolicy>(
        static_cast<unsigned int>(a)
        & static_cast<unsigned int>(b)
    );
}

// ----------------------------------------------------------------------
// |
// |  TfidfVectorizerTransformer
// |
// ----------------------------------------------------------------------
TfidfVectorizerTransformer::TfidfVectorizerTransformer(IndexMap labels,
                                                       IndexMap docuFreq,
                                                       std::uint32_t totalNumDocus,
                                                       NormMethod norm,
                                                       TfidfPolicy tfidfParameters) :
    Labels(
        std::move(
            [&labels](void) ->  IndexMap & {
                if (labels.size() == 0) {
                    throw std::invalid_argument("Index map is empty!");
                }
                return labels;
            }()
        )
    ),
    DocumentFreq(
        std::move(
            [&docuFreq](void) ->  IndexMap & {
                if (docuFreq.size() == 0) {
                    throw std::invalid_argument("DocumentFrequency map is empty!");
                }
                return docuFreq;
            }()
        )
    ),
    TotalNumsDocuments(std::move(totalNumDocus)),
    Norm(std::move(norm)),
    TfidfParameters(std::move(tfidfParameters)) {
}

TfidfVectorizerTransformer::TfidfVectorizerTransformer(Archive &ar) :
    Labels(Traits<decltype(Labels)>::deserialize(ar)),
    DocumentFreq(Traits<decltype(DocumentFreq)>::deserialize(ar)),
    TotalNumsDocuments(Traits<decltype(TotalNumsDocuments)>::deserialize(ar)),
    //todo: unsigned char ?
    //Norm(Traits<decltype(Norm)>::deserialize(ar)),
    Norm(),
    //todo: uint32 ?
    TfidfParameters() {
}

void TfidfVectorizerTransformer::save(Archive &ar) const /*override*/ {
    //call ctor
    Traits<decltype(Labels)>::serialize(ar, Labels);
    Traits<decltype(DocumentFreq)>::serialize(ar, DocumentFreq);
    Traits<decltype(TotalNumsDocuments)>::serialize(ar, TotalNumsDocuments);
    //todo
    //Traits<decltype(Norm)>::serialize(ar, Norm);

    //todo
    //Traits<decltype(TfidfPolicy)>::serialize(ar, TfidfPolicy);
}

bool TfidfVectorizerTransformer::operator==(TfidfVectorizerTransformer const &other) const {
    return Labels == other.Labels
        && DocumentFreq == other.DocumentFreq
        && TotalNumsDocuments == other.TotalNumsDocuments
        && Norm == other.Norm
        && TfidfParameters == other.TfidfParameters;
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
    StringDecorator decorator,
    AnalyzerMethod analyzer,
    std::string regex,
    std::float_t minDf,
    std::float_t maxDf,
    nonstd::optional<std::uint32_t> topKTerms,
    nonstd::optional<IndexMap> vocabulary,
    std::uint32_t ngramRangeMin,
    std::uint32_t ngramRangeMax,
    NormMethod norm,
    TfidfPolicy tfidfParameters
) :
    BaseType(
        "TfidfVectorizerEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex, &decorator, &analyzer, &regex, &vocabulary, &topKTerms, &minDf, &maxDf, &ngramRangeMin, &ngramRangeMax](void) {
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
        [pAllColumnAnnotations, colIndex, &norm, &tfidfParameters](void) {
            return Details::TfidfVectorizerEstimatorImpl<MaxNumTrainingItemsV>(
                std::move(pAllColumnAnnotations),
                std::move(colIndex),
                std::move(norm),
                std::move(tfidfParameters)
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
    TfidfPolicy tfidfParameters
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
    _tfidfParameters(std::move(tfidfParameters)) {
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
