// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <unordered_map>
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
    using FrequencyMap                      = std::unordered_map<std::string, std::uint32_t>;
    using IndexMap                          = FrequencyMap;
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    FrequencyMap const                      TermFrequency;                  /// Words and the number of documents that it appears in
    IndexMap const                          TermIndex;
    std::uint32_t const                     TotalNumDocuments;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    DocumentStatisticsAnnotationData(FrequencyMap termFreq, IndexMap termIndex, std::uint32_t totalNumDocuments);
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
    using InputType                         = std::string;
    using InputTypeConstIterator            = std::string::const_iterator;
    using StringDecorator                   = std::function<std::string (InputTypeConstIterator begin, InputTypeConstIterator end)>;
    using IndexMap                          = DocumentStatisticsAnnotationData::IndexMap;
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
    DocumentStatisticsTrainingOnlyPolicy(void);
    DocumentStatisticsTrainingOnlyPolicy(StringDecorator decorator);

    void fit(InputType const &input);
    DocumentStatisticsAnnotationData complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using FrequencyMap                      = typename DocumentStatisticsAnnotationData::FrequencyMap;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    StringDecorator const                   _stringDecoratorFunc;

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
using DocumentStatisticsEstimator           = Components::TrainingOnlyEstimatorImpl<Details::DocumentStatisticsTrainingOnlyPolicy, MaxNumTrainingItemsV>;

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
// |  DocumentStatisticsAnnotationData
// |
// ----------------------------------------------------------------------
inline DocumentStatisticsAnnotationData::DocumentStatisticsAnnotationData(FrequencyMap termFreq, IndexMap termIndex, std::uint32_t totalNumDocuments) :
    TermFrequency(
        std::move(
            [&termFreq](void) -> FrequencyMap & {
                if(termFreq.empty())
                    throw std::invalid_argument("termFreq");

                return termFreq;
            }()
        )
    ),
    TermIndex(
        std::move(
            [&termIndex](void) -> IndexMap & {
                if(termIndex.empty())
                    throw std::invalid_argument("termIndex");

                return termIndex;
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
// |  Details::DocumentStatisticsTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
inline Details::DocumentStatisticsTrainingOnlyPolicy::DocumentStatisticsTrainingOnlyPolicy(void) :
    _totalNumDocuments(0) {
}

inline Details::DocumentStatisticsTrainingOnlyPolicy::DocumentStatisticsTrainingOnlyPolicy(StringDecorator decorator) :
    //DocumentStatisticsTrainingOnlyPolicy(), this gives the error: an initializer for a delegating constructor must appear alone
    _stringDecoratorFunc(
        [&decorator](void) -> StringDecorator & {
            if(!decorator)
                throw std::invalid_argument("decorator");

            return decorator;
        }()
    ),
    _totalNumDocuments(0) {
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
    IndexMap const                          termIndex(Microsoft::Featurizer::Featurizers::Components::CreateIndexMap<std::string>(_termFrequency, IndexMap()));
    return DocumentStatisticsAnnotationData(std::move(_termFrequency), std::move(termIndex), std::move(_totalNumDocuments));
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
