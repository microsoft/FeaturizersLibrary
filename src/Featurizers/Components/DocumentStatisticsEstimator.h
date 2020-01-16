// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <algorithm>
#include <iterator> 
#include <unordered_map>
#include <queue>
#include <set>

#include "TrainingOnlyEstimatorImpl.h"
#include "IndexMapEstimator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

namespace {

//this is temporary split algorithm
inline void split_temp(std::string const & input, std::function<void (std::string::const_iterator&, std::string::const_iterator&)> const & callback) {

    std::string::const_iterator left = input.begin();
    std::string::const_iterator right = left;

    while (left != input.end() && *left == ' ')
        ++left;

    right = left;
    while (right != input.end()) {
        if (*right == ' ') {
            callback(left, right);
            left = right;
            while (left != input.end() && *left == ' ')
                ++left;
            right = left;
        } else {
            ++right;
        }
    }
    if (left != right)
        callback(left, right);
}

struct IterRangeComp {
    bool operator()(const std::tuple<std::string::const_iterator, std::string::const_iterator>& a,
                    const std::tuple<std::string::const_iterator, std::string::const_iterator>& b) const {

        std::string::const_iterator s1 = std::get<0>(a);
        std::string::const_iterator e1 = std::get<1>(a);
        std::string::const_iterator s2 = std::get<0>(b);
        std::string::const_iterator e2 = std::get<1>(b);

        if(std::distance(s1, e1) < std::distance(s2, e2)) {
            return true;
        } else if (std::distance(s2, e2) < std::distance(s1, e1)) {
            return false;
        }

        while (s1 != e1) {
            if (s2 == e2 || *s2 < *s1) {
                return false;
            } else if (*s1 < *s2) {
                return true;
            }
            ++s1;
            ++s2;
        }
        return (s2 != e2);
    }
};

}

static constexpr char const * const         DocumentStatisticsEstimatorName("DocumentStatisticsEstimator");

/////////////////////////////////////////////////////////////////////////
///  \struct        FrequencyAndIndexStruct
///  \brief         This struct is a combination of values of FrequencyMap and 
///                 IndexMap for the purpose of keys equivelence of two maps
///
struct FrequencyAndIndexStruct {
    std::uint32_t const TermFrequency;                            // Words and the number of documents that it appears in
    std::uint32_t const Index;                              

    //copy needed in generating FrequencyAndIndexMap
    //FEATURIZER_MOVE_CONSTRUCTOR_ONLY(FrequencyAndIndexStruct);
    FrequencyAndIndexStruct(std::uint32_t termFrequency, std::uint32_t index);
    bool operator==(FrequencyAndIndexStruct const &other) const;
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
    using FrequencyAndIndexMap              = std::unordered_map<std::string, FrequencyAndIndexStruct>;
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

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(DocumentStatisticsAnnotationData);
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
    using StringDecorator                   = std::function<std::string (InputTypeConstIterator begin, InputTypeConstIterator end)>;
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
        nonstd::optional<IndexMap> vocabulary, 
        nonstd::optional<std::uint32_t> topKTerms, 
        std::float_t minDf, 
        std::float_t maxDf
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

    nonstd::optional<IndexMap> const        _existingVocabulary;
    nonstd::optional<std::uint32_t> const   _topKTerms;
    std::float_t const                      _minDf;
    std::float_t const                      _maxDf;
    
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
        nonstd::optional<IndexMap> vocabulary, 
        nonstd::optional<std::uint32_t> topKTerms, 
        std::float_t minDf, 
        std::float_t maxDf
    );
    ~DocumentStatisticsEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(DocumentStatisticsEstimator);
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
// |  FrequencyAndIndexStruct
// |
// ----------------------------------------------------------------------
FrequencyAndIndexStruct::FrequencyAndIndexStruct(std::uint32_t termFrequency, std::uint32_t index) :
    //validate not necessary in this assignment
    TermFrequency(std::move(termFrequency)),
    Index(std::move(index)) {
}

bool FrequencyAndIndexStruct::operator==(FrequencyAndIndexStruct const &other) const {
    return (TermFrequency == other.TermFrequency) && (Index == other.Index);
}

// ----------------------------------------------------------------------
// |
// |  DocumentStatisticsAnnotationData
// |
// ----------------------------------------------------------------------
inline DocumentStatisticsAnnotationData::DocumentStatisticsAnnotationData(FrequencyAndIndexMap termFrequencyAndIndex, std::uint32_t totalNumDocuments) :
    TermFrequencyAndIndex(
        std::move(
            [&termFrequencyAndIndex](void) -> FrequencyAndIndexMap & {
                if(termFrequencyAndIndex.empty())
                    throw std::invalid_argument("termFrequencyAndIndex");

                return termFrequencyAndIndex;
            }()
        )
    ),
    TotalNumDocuments(
        std::move(
            [&totalNumDocuments](void) -> std::uint32_t & {
                if(totalNumDocuments == 0)
                    throw std::invalid_argument("totalNumDocuments");

                return totalNumDocuments;
            }()
        )
    ) {
}

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
    nonstd::optional<IndexMap> existingVocabulary, 
    nonstd::optional<std::uint32_t> topKTerms, 
    std::float_t minDf, 
    std::float_t maxDf
) :
    BaseType(
        std::move(pAllColumnAnnotations),
        std::move(colIndex),
        true,
        std::move(decorator),
        std::move(existingVocabulary),
        std::move(topKTerms),
        std::move(minDf),
        std::move(maxDf)
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Anonymous namespace
// |
// ----------------------------------------------------------------------
namespace {

inline Details::DocumentStatisticsTrainingOnlyPolicy::FrequencyMap PruneTermFreqMap(Details::DocumentStatisticsTrainingOnlyPolicy::FrequencyMap termFrequency, 
                                                                                    std::float_t minDf, 
                                                                                    std::float_t maxDf, 
                                                                                    std::float_t totalNumDocumentsFloat,
                                                                                    nonstd::optional<std::uint32_t> topKTerms) {

    using FrequencyMap = Details::DocumentStatisticsTrainingOnlyPolicy::FrequencyMap;
    
    //trim by minDf and maxDf
    if (minDf > 0.0f || maxDf < 1.0f) {
        FrequencyMap::iterator termFrequencyIter = termFrequency.begin();
        while (termFrequencyIter != termFrequency.end()) {
            std::float_t const freq = termFrequencyIter->second / totalNumDocumentsFloat;

            if (freq < minDf || freq > maxDf) {
                termFrequencyIter = termFrequency.erase(termFrequencyIter);
            } else {
                ++termFrequencyIter;
            }       
        }
    }

    //trim by topKTerms
    if (!topKTerms.has_value() || termFrequency.empty() || *topKTerms >= termFrequency.size())
        return termFrequency;

    std::uint32_t const & topKTermsValue(*topKTerms);

    std::tuple<std::uint32_t, long long> targetPack(
        [&termFrequency, &topKTermsValue]() -> std::tuple<std::uint32_t, long long> {
            std::vector<std::uint32_t> frequencyVector;
            frequencyVector.reserve(termFrequency.size());

            std::transform(
                termFrequency.begin(), 
                termFrequency.end(), 
                std::back_inserter(frequencyVector), 
                [](auto const & kv) { 
                    return kv.second; 
                }
            );

            //partial sort, ave O(n)
            std::nth_element(
                frequencyVector.begin(), 
                frequencyVector.begin() + static_cast<int>(topKTermsValue) - 1, 
                frequencyVector.end(), 
                std::greater<std::uint32_t>()
            );

            std::uint32_t targetValue = frequencyVector[topKTermsValue - 1];
            long long remainingTargetValue = std::count(
                frequencyVector.begin(), 
                frequencyVector.begin() + static_cast<int>(topKTermsValue),
                targetValue
            );

            return std::make_tuple<std::uint32_t, long long>(
                std::move(targetValue), 
                std::move(remainingTargetValue)
            );
        }()
    );
    
    std::uint32_t targetValue = std::get<0>(targetPack);
    long long remainingTargetValue = std::get<1>(targetPack);

    FrequencyMap::iterator termFrequencyIter = termFrequency.begin();
    while (termFrequencyIter != termFrequency.end()) {
        if (termFrequencyIter->second < targetValue) {
            termFrequencyIter = termFrequency.erase(termFrequencyIter);
            continue;
        } else if (termFrequencyIter->second == targetValue) {
            if (remainingTargetValue == 0) {
               termFrequencyIter = termFrequency.erase(termFrequencyIter);
            } else {
                ++termFrequencyIter;
                --remainingTargetValue;
            }
        } else {
            ++termFrequencyIter;
        }
    }

    return termFrequency;
}

inline DocumentStatisticsAnnotationData::FrequencyAndIndexMap MergeTwoMapsWithSameKeys(Details::DocumentStatisticsTrainingOnlyPolicy::FrequencyMap const termFrequency, 
                                                                                       Details::DocumentStatisticsTrainingOnlyPolicy::IndexMap const termIndex) {
    DocumentStatisticsAnnotationData::FrequencyAndIndexMap termFrequencyAndIndex;
    for (auto const & termFrequencyIter : termFrequency) {
        //assert that termFrequencyIter.first is in termIndex
        auto termIndexIter = termIndex.find(termFrequencyIter.first);
        if (termIndexIter == termIndex.end())
            throw std::invalid_argument("the keys in termFrequency and termIndex do not match");

        FrequencyAndIndexStruct value(termFrequencyIter.second, termIndexIter->second);
        termFrequencyAndIndex.emplace(DocumentStatisticsAnnotationData::FrequencyAndIndexMap::value_type(
            termFrequencyIter.first, 
            std::move(value))
        );
        // FrequencyAndIndexStruct value(termFrequencyIter.second, termIndex.at(termFrequencyIter.first));
        // termFrequencyAndIndex.emplace(std::make_pair(termFrequencyIter.first, std::move(value)));
        //termFrequencyAndIndex.emplace(std::make_pair(termFrequencyIter.first, FrequencyAndIndexStruct(termFrequencyIter.second, termIndex.at(termFrequencyIter.first))));
    }
    return termFrequencyAndIndex;
}

}

// ----------------------------------------------------------------------
// |
// |  Details::DocumentStatisticsTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
inline Details::DocumentStatisticsTrainingOnlyPolicy::DocumentStatisticsTrainingOnlyPolicy(
    StringDecorator decorator, 
    nonstd::optional<IndexMap> existingVocabulary, 
    nonstd::optional<std::uint32_t> topKTerms, 
    std::float_t minDf, 
    std::float_t maxDf
) :
    _stringDecoratorFunc(
        [&decorator](void) -> StringDecorator & {
            //temporary mute this validate
            // if(!decorator)
            //     throw std::invalid_argument("decorator");
            return decorator;
        }()
    ),
    _existingVocabulary(
        std::move(
            [&existingVocabulary](void) -> nonstd::optional<IndexMap> & {
                if(existingVocabulary.has_value() && existingVocabulary->empty()) 
                    throw std::invalid_argument("existingVocabulary");

                return existingVocabulary;
            }()
        )
    ),
    _topKTerms(
        std::move(
            [&topKTerms](void) -> nonstd::optional<std::uint32_t> & {
                if(topKTerms.has_value() && *topKTerms == 0)
                    throw std::invalid_argument("topKTermsLowerBound");

                return topKTerms;
            }()
        )
    ),
    _minDf(
        std::move(
            [&minDf](void) -> std::float_t & {
                if(minDf < 0.0f || minDf > 1.0f)
                    throw std::invalid_argument("minDf");

                return minDf;
            }()
        )
    ),
    _maxDf(
        std::move(
            [&maxDf](void) -> std::float_t & {
                if(maxDf < 0.0f || maxDf > 1.0f)
                    throw std::invalid_argument("maxDf");

                return maxDf;
            }()
        )
    ),
    _totalNumDocuments(0) {
        if (_minDf > _maxDf)
            throw std::invalid_argument("_minDf > _maxDf");
}

inline void Details::DocumentStatisticsTrainingOnlyPolicy::fit(InputType const &input) {
    if(_stringDecoratorFunc) {
        fit_impl<std::set<std::string>>(
            input,
            [this](InputTypeConstIterator begin, InputTypeConstIterator end) -> std::string {
                return _stringDecoratorFunc(begin, end);
            },
            [](std::string const &value) -> std::string const & { //I add a const here
                return value;
            }
        );
    }
    else {
        // ----------------------------------------------------------------------
        using InputTypeConstIteratorRange               = std::tuple<InputTypeConstIterator, InputTypeConstIterator>;
        using InputTypeConstIteratorRangeSet            = std::set<InputTypeConstIteratorRange, IterRangeComp>;
        // ----------------------------------------------------------------------

        fit_impl<InputTypeConstIteratorRangeSet>(
            input,
            [](InputTypeConstIterator begin, InputTypeConstIterator end) {
                return std::make_pair(begin, end);
            },
            [](InputTypeConstIteratorRange const &range) -> std::string {
                return std::string(std::get<0>(range), std::get<1>(range));
            }
        );
    }
}

inline DocumentStatisticsAnnotationData Details::DocumentStatisticsTrainingOnlyPolicy::complete_training(void) {

    //prune map by maxDf, minDf and topKTerms
    FrequencyMap                            prunedTermFreq(PruneTermFreqMap(std::move(_termFrequency), _minDf, _maxDf, static_cast<std::float_t>(_totalNumDocuments), _topKTerms));

    //In general, the custom vocabulary should assign values to words that no bigger than the map's size
    //however, some may choose to use unique values. We do not check if the given vocabulary is appropriate
    //But suggest customer use reasonable mapping 
    IndexMap                                termIndex(Microsoft::Featurizer::Featurizers::Components::CreateIndexMap<std::string>(prunedTermFreq, 
                                                                                                                                  _existingVocabulary.has_value() ? *_existingVocabulary : IndexMap()));

    //here the termIndex includes(strictly) termFrequency, which means termIndex has all the keys that appear in termFrequency, but may has some keys not in termFrequency
    //ignore the additional keys in termIndex
    FrequencyAndIndexMap                    termFrequencyAndIndex(MergeTwoMapsWithSameKeys(std::move(prunedTermFreq), std::move(termIndex)));

    return DocumentStatisticsAnnotationData(std::move(termFrequencyAndIndex), std::move(_totalNumDocuments));
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename SetT, typename CreateKeyFuncT, typename KeyToStringFuncT>
void Details::DocumentStatisticsTrainingOnlyPolicy::fit_impl(InputType const &input, CreateKeyFuncT const &createKeyFunc, KeyToStringFuncT const &keyToStringFunc) {
    SetT                                    documents;

    split_temp(
        input,
        [&createKeyFunc, &documents](InputTypeConstIterator begin, InputTypeConstIterator end) {
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
