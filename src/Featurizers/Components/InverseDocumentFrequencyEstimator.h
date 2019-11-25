// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <unordered_map>
#include <set>

#include "TrainingOnlyEstimatorImpl.h"

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

static constexpr char const * const         InverseDocumentFrequencyEstimatorName("InverseDocumentFrequencyEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         InverseDocumentFrequencyAnnotationData
///  \brief         This is an annotation class which holds all the values and corresponding
///                 frequencies for an input column.
///
class InverseDocumentFrequencyAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InverseDocumentFrequency                         = std::unordered_map<std::string, std::uint32_t>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    InverseDocumentFrequency const                         TermFrequency;
    std::uint32_t const                                    TotalNumDocuments;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    InverseDocumentFrequencyAnnotationData(InverseDocumentFrequency termfreq, std::uint32_t totalnumdocu);
    ~InverseDocumentFrequencyAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(InverseDocumentFrequencyAnnotationData);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         InverseDocumentFrequencyTrainingOnlyPolicy
///  \brief         `InverseDocumentFrequencyEstimator` implementation details.
///
class InverseDocumentFrequencyTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = std::string;
    using IterRangeType                     = std::tuple<std::string::const_iterator, std::string::const_iterator>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = InverseDocumentFrequencyEstimatorName;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    void fit(InputType const &input);
    InverseDocumentFrequencyAnnotationData complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using InverseDocumentFrequency           = typename InverseDocumentFrequencyAnnotationData::InverseDocumentFrequency;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    InverseDocumentFrequency                 _inverseDocumentFrequency;
    std::uint32_t                            _totalNumDocuments = 0;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \typedef       InverseDocumentFrequencyEstimator
///  \brief         This class computes the InverseDocumentFrequency for an input column
///                 and creates a InverseDocumentFrequencyAnnotationData.
///
template <size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
using InverseDocumentFrequencyEstimator                    = Components::TrainingOnlyEstimatorImpl<Details::InverseDocumentFrequencyTrainingOnlyPolicy, MaxNumTrainingItemsV>;

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
// |  InverseDocumentFrequencyAnnotationData
// |
// ----------------------------------------------------------------------
InverseDocumentFrequencyAnnotationData::InverseDocumentFrequencyAnnotationData(InverseDocumentFrequency termfreq, std::uint32_t totalnumdocu) :
    TermFrequency(std::move(termfreq)), 
    TotalNumDocuments(std::move(totalnumdocu)) {
}

// ----------------------------------------------------------------------
// |
// |  Details::InverseDocumentFrequencyTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
void Details::InverseDocumentFrequencyTrainingOnlyPolicy::fit(InputType const &input) {

    typename std::set<IterRangeType, IterRangeComp> set_docu;

    //todo: will use vector<functor> after string header file is done
    split_temp( 
        input, 
        [&set_docu] (std::string::const_iterator & iter_start, std::string::const_iterator & iter_end) {
            set_docu.insert(std::make_tuple(iter_start, iter_end));
        }
    );

    for (auto const & iter_set : set_docu) {

        typename InverseDocumentFrequency::mapped_type &   count(
            [this, &iter_set](void) -> typename InverseDocumentFrequency::mapped_type & {

                std::string str_temp = std::string(std::get<0>(iter_set), std::get<1>(iter_set));

                typename InverseDocumentFrequency::iterator                                    iter(_inverseDocumentFrequency.find(str_temp));

                if(iter == _inverseDocumentFrequency.end()) {
                    std::pair<typename InverseDocumentFrequency::iterator, bool> const         result(_inverseDocumentFrequency.insert(std::make_pair(std::move(str_temp), 0)));

                    iter = result.first;
                }

                return iter->second;
            }()
        );

        count += 1;
    }

    ++_totalNumDocuments;
}

InverseDocumentFrequencyAnnotationData Details::InverseDocumentFrequencyTrainingOnlyPolicy::complete_training(void) {
    return InverseDocumentFrequencyAnnotationData(std::move(_inverseDocumentFrequency), std::move(_totalNumDocuments));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
