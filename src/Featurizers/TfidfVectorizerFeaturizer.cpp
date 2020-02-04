// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#include "TfidfVectorizerFeaturizer.h"

#include "../Archive.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

// ----------------------------------------------------------------------
// |
// |  TfidfVectorizerTransformer
// |
// ----------------------------------------------------------------------
TfidfVectorizerTransformer::TfidfVectorizerTransformer(IndexMap labels,
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

TfidfVectorizerTransformer::TfidfVectorizerTransformer(Archive &ar) :
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
            NormMethod                     norm(static_cast<NormMethod>(Traits<std::underlying_type<NormMethod>::type>::deserialize(ar)));
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

void TfidfVectorizerTransformer::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(_labels)>::serialize(ar, _labels);
    Traits<decltype(_documentFreq)>::serialize(ar, _documentFreq);
    Traits<decltype(_totalNumsDocuments)>::serialize(ar, _totalNumsDocuments);
    Traits<std::underlying_type<NormMethod>::type>::serialize(ar, static_cast<std::underlying_type<NormMethod>::type>(_norm));
    Traits<std::underlying_type<TfidfPolicy>::type>::serialize(ar, static_cast<std::underlying_type<TfidfPolicy>::type>(_tfidfParameters));
    Traits<decltype(_lowercase)>::serialize(ar, _lowercase);
    Traits<std::underlying_type<AnalyzerMethod>::type>::serialize(ar, static_cast<std::underlying_type<AnalyzerMethod>::type>(_analyzer));
    Traits<decltype(_regexToken)>::serialize(ar, _regexToken);
    Traits<decltype(_ngramRangeMin)>::serialize(ar, _ngramRangeMin);
    Traits<decltype(_ngramRangeMax)>::serialize(ar, _ngramRangeMax);
}

bool TfidfVectorizerTransformer::operator==(TfidfVectorizerTransformer const &other) const {
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
void TfidfVectorizerTransformer::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
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
    assert(normVal >= 0.0f);

    // l2-norm calibration
    if (_norm == NormMethod::L2)
        normVal = sqrt(normVal);

    if (_norm == NormMethod::None)
        normVal = 1.0;

    std::vector<SparseVectorEncoding<std::float_t>::ValueEncoding> sparseVector;

    for (auto & result : results) {
        sparseVector.emplace_back(SparseVectorEncoding<std::float_t>::ValueEncoding(std::get<1>(result) / normVal, std::get<0>(result)));
    }

    std::sort(sparseVector.begin(), sparseVector.end(),
        [](SparseVectorEncoding<std::float_t>::ValueEncoding const &a, SparseVectorEncoding<std::float_t>::ValueEncoding const &b) {
            return a.Index < b.Index;
        }
    );

    callback(SparseVectorEncoding<std::float_t>(_labels.size(), std::move(sparseVector)));
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
