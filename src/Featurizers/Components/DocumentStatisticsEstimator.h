// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <queue>
#include <regex>
#include <set>

#include "TrainingOnlyEstimatorImpl.h"
#include "IndexMapEstimator.h"
#include "../../Strings.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {


static constexpr char const * const         DocumentStatisticsEstimatorName("DocumentStatisticsEstimator");

using StringIterator                    = std::string::const_iterator;
using ParseFunctionType                 = std::function<void (std::string const &, std::function<void (StringIterator, StringIterator)> const &)>;

enum class AnalyzerMethod : unsigned char {
    Word = 1,
    Char = 2,
    Charwb = 3
};

/////////////////////////////////////////////////////////////////////////
///  \class         IterRangeComp
///  \brief         Compares two iterator ranges (where a range is a tuple
///                 of a begin and end iterator).
///
struct IterRangeComp {
    bool operator()(const std::tuple<std::string::const_iterator, std::string::const_iterator>& a,
                    const std::tuple<std::string::const_iterator, std::string::const_iterator>& b) const;
};

/////////////////////////////////////////////////////////////////////////
///  \struct        FrequencyAndIndex
///  \brief         This struct is a combination of values of FrequencyMap and
///                 IndexMap for the purpose of keys equivelence of two maps
///
struct FrequencyAndIndex {
    std::uint32_t const TermFrequency;                            // Words and the number of documents that it appears in
    std::uint32_t const Index;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FrequencyAndIndex);

    FrequencyAndIndex(std::uint32_t termFrequency, std::uint32_t index);
    bool operator==(FrequencyAndIndex const &other) const;
};

/////////////////////////////////////////////////////////////////////////
///  \class         DocumentStatisticsAnnotationData
///  \brief         Collection about statistics found within a number of
///                 documents.
///
class DocumentStatisticsAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using FrequencyAndIndexMap              = std::unordered_map<std::string, FrequencyAndIndex>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    FrequencyAndIndexMap const              TermFrequencyAndIndex;
    std::uint32_t const                     TotalNumDocuments;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    DocumentStatisticsAnnotationData(FrequencyAndIndexMap termFrequencyAndIndex, std::uint32_t totalNumDocuments);
    ~DocumentStatisticsAnnotationData(void) = default;

    DocumentStatisticsAnnotationData(DocumentStatisticsAnnotationData &&other);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         DocumentStatisticsTrainingOnlyPolicy
///  \brief         `DocumentStatisticsEstimator` implementation details.
///
class DocumentStatisticsTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------

    // TODO: Rather than using std::string, we should use a type that makes it clear that
    //       the content is UTF8; this type should also compare using unicode characters
    //       rather than asci characters.
    using InputType                         = std::string;
    using InputTypeConstIterator            = std::string::const_iterator;
    using StringDecorator                   = std::function<std::string (std::string)>;
    using IndexMap                          = std::unordered_map<std::string, std::uint32_t>;
    using FrequencyMap                      = IndexMap;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = DocumentStatisticsEstimatorName;


    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    DocumentStatisticsTrainingOnlyPolicy(
        StringDecorator decorator,
        AnalyzerMethod analyzer,
        std::string regexToken,
        nonstd::optional<IndexMap> vocabulary,
        nonstd::optional<std::uint32_t> topKTerms,
        std::float_t minDf,
        std::float_t maxDf,
        std::uint32_t ngramRangeMin,
        std::uint32_t ngramRangeMax
    );

    void fit(InputType const &input);
    DocumentStatisticsAnnotationData complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using FrequencyAndIndexMap              = DocumentStatisticsAnnotationData::FrequencyAndIndexMap;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    StringDecorator const                   _stringDecoratorFunc;
    AnalyzerMethod const                    _analyzer;
    std::string const                       _regexToken;

    nonstd::optional<IndexMap> const        _existingVocabulary;
    nonstd::optional<std::uint32_t> const   _topKTerms;
    std::float_t const                      _minDf;
    std::float_t const                      _maxDf;
    std::uint32_t const                     _ngramRangeMin;
    std::uint32_t const                     _ngramRangeMax;

    ParseFunctionType const                 _parseFunc;

    FrequencyMap                            _termFrequency;
    std::uint32_t                           _totalNumDocuments;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    template <
        typename SetT,
        typename CreateKeyFuncT,            // SetT::value_type (InputTypeConstIterator begin, InputTypeConstIterator end)
        typename KeyToStringFuncT           // <string-like> (SetT::value_type), where <string-like> will be a string reference or object depending on the set type
    >
    void fit_impl(
        InputType const &input,
        CreateKeyFuncT const &createKeyFunc,
        KeyToStringFuncT const &createStringFromKeyFunc
    );
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \typedef       DocumentStatisticsEstimator
///  \brief         This class computes the DocumentStatistics for an input column
///                 and creates a DocumentStatisticsAnnotationData.
///
template <
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class DocumentStatisticsEstimator : public TrainingOnlyEstimatorImpl<Details::DocumentStatisticsTrainingOnlyPolicy, MaxNumTrainingItemsV> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TrainingOnlyEstimatorImpl<Details::DocumentStatisticsTrainingOnlyPolicy, MaxNumTrainingItemsV>;
    using StringDecorator                   = Details::DocumentStatisticsTrainingOnlyPolicy::StringDecorator;
    using IndexMap                          = Details::DocumentStatisticsTrainingOnlyPolicy::IndexMap;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    DocumentStatisticsEstimator(
        AnnotationMapsPtr pAllColumnAnnotations,
        size_t colIndex,
        StringDecorator decorator,
        AnalyzerMethod analyzer,
        std::string regexToken,
        nonstd::optional<IndexMap> vocabulary,
        nonstd::optional<std::uint32_t> topKTerms,
        std::float_t minDf,
        std::float_t maxDf,
        std::uint32_t ngramRangeMin,
        std::uint32_t ngramRangeMax
    );
    ~DocumentStatisticsEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(DocumentStatisticsEstimator);
};

// ----------------------------------------------------------------------
// |
// |  Public Functions
// |
// ----------------------------------------------------------------------
DocumentStatisticsAnnotationData::FrequencyAndIndexMap MergeTwoMapsWithSameKeys(Details::DocumentStatisticsTrainingOnlyPolicy::FrequencyMap termFrequency,
                                                                                Details::DocumentStatisticsTrainingOnlyPolicy::IndexMap termIndex);

ParseFunctionType DocumentParseFuncGenerator(AnalyzerMethod const &analyzer, std::string const & regexToken, std::uint32_t const & ngramRangeMin, std::uint32_t const & ngramRangeMax);
std::string DocumentDecorator(std::string const& input, bool const& lower, AnalyzerMethod const& analyzer, std::string const& regex, std::uint32_t const& ngram_min, std::uint32_t const& ngram_max);

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
// |  DocumentStatisticsEstimator
// |
// ----------------------------------------------------------------------
//Would it be better to place default values during pipeline chaining(countvectorizer and tfidfvectorizer)? if so this ctor will show no default values
template <size_t MaxNumTrainingItemsV>
DocumentStatisticsEstimator<MaxNumTrainingItemsV>::DocumentStatisticsEstimator(
    AnnotationMapsPtr pAllColumnAnnotations,
    size_t colIndex,
    StringDecorator decorator,
    AnalyzerMethod analyzer,
    std::string regexToken,
    nonstd::optional<IndexMap> existingVocabulary,
    nonstd::optional<std::uint32_t> topKTerms,
    std::float_t minDf,
    std::float_t maxDf,
    std::uint32_t ngramRangeMin,
    std::uint32_t ngramRangeMax
) :
    BaseType(
        std::move(pAllColumnAnnotations),
        std::move(colIndex),
        true,
        std::move(decorator),
        std::move(analyzer),
        std::move(regexToken),
        std::move(existingVocabulary),
        std::move(topKTerms),
        std::move(minDf),
        std::move(maxDf),
        std::move(ngramRangeMin),
        std::move(ngramRangeMax)
    ) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename SetT, typename CreateKeyFuncT, typename KeyToStringFuncT>
void Details::DocumentStatisticsTrainingOnlyPolicy::fit_impl(InputType const &input, CreateKeyFuncT const &createKeyFunc, KeyToStringFuncT const &keyToStringFunc) {
    SetT                                    documents;

    std::string processedInput;
    if (_analyzer == AnalyzerMethod::Word) {
        if (_regexToken.empty() && !(_ngramRangeMin == 1 && _ngramRangeMax == 1)) {
            processedInput = Microsoft::Featurizer::Strings::Details::ReplaceAndDeDuplicate<std::function<bool (char)>>(input);
        } else {
            processedInput = input;
        }
    } else if (_analyzer == AnalyzerMethod::Char) {
        processedInput = Microsoft::Featurizer::Strings::Details::ReplaceAndDeDuplicate<std::function<bool (char)>>(input);
    } else {
        assert(_analyzer == AnalyzerMethod::Charwb);
        auto predicate = [] (char c) {return std::isspace(c);};

        std::string processedString(Microsoft::Featurizer::Strings::Details::ReplaceAndDeDuplicate<std::function<bool (char)>>(input));
        processedInput = Microsoft::Featurizer::Strings::Details::StringPadding<std::function<bool (char)>>(processedString, predicate);
    }

    _parseFunc(
        processedInput,
        [&createKeyFunc, &documents] (InputTypeConstIterator begin, InputTypeConstIterator end) {
            documents.insert(createKeyFunc(begin, end));
        }
    );

    auto const                              getCountFunc(
        [this, &keyToStringFunc](typename SetT::value_type const &key) -> typename FrequencyMap::mapped_type & {
            auto                                        mapKey(keyToStringFunc(key));
            typename FrequencyMap::iterator const       iter(_termFrequency.find(mapKey));

            if(iter != _termFrequency.end())
                return iter->second;

            std::pair<typename FrequencyMap::iterator, bool> const          result(_termFrequency.insert(std::make_pair(std::move(mapKey), 0)));

            return result.first->second;
        }
    );

    for(auto const &key : documents)
        getCountFunc(key) += 1;

    _totalNumDocuments += 1;
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
