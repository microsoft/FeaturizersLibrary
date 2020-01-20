// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

namespace Microsoft {
namespace Featurizer {
namespace Details {

template<typename IteratorT>
inline std::vector<IteratorT> IteratorVectorGenerator(IteratorT const & begin,
                                                     IteratorT const & end) {
    std::vector<IteratorT> wordIterVector;
    wordIterVector.reserve(static_cast<unsigned long long>(std::distance(begin, end)));

    for (IteratorT strIter = begin; strIter != end; ++strIter)
        wordIterVector.emplace_back(std::move(strIter));
    wordIterVector.emplace_back(std::move(end));

    return wordIterVector;
}

template <
    typename IteratorT,
    typename IsDelimiterT
>
inline void Parse(IteratorT const &begin,
                  IteratorT const &end,
                  IsDelimiterT const &isDelimiter,
                  std::function<void (IteratorT&, IteratorT&)> const &callback) {

    IteratorT left = begin;
    IteratorT right = left;
    while (left != end && *left == isDelimiter)
        ++left;

    right = left;
    while (right != end) {
        if (*right == isDelimiter) {
            callback(left, right);
            left = right;
            while (left != end && *left == isDelimiter)
                ++left;
            right = left;
        } else {
            ++right;
        }
    }
    if (left != right)
        callback(left, right);
}

template <
    typename IteratorT,
    typename RegexT
>
inline void ParseRegex(IteratorT const &begin,
                       IteratorT const &end,
                       RegexT const &regexToken,
                       std::function<void (IteratorT&, IteratorT&)> const &callback) {

    std::sregex_iterator iter(begin, end, regexToken);
    std::sregex_iterator iterEnd;

    while (iter != iterEnd) {
        std::string const iterStringConst = iter->str();
        IteratorT beginRef = iterStringConst.begin();
        IteratorT endRef = iterStringConst.end();
        callback(beginRef, endRef);
        ++iter;
    }
}

template <typename IteratorT>
inline std::string TrimAndReplace(IteratorT begin,
                                  IteratorT end) {
    //replace all punctuations with spaces
    std::transform(begin, end, begin, [](char c) {
        if (std::ispunct(c) )
            return ' ';
        return c;
    });

    std::string result(begin, end);
    //remove duplicate space
    result.erase(
        std::unique(
            result.begin(),
            result.end(),
            [=](char lhs, char rhs){
                return (lhs == rhs) && (lhs == ' ');
            }
        ),
        result.end()
    );

    return result;
}

template <typename IteratorT>
inline void ParseNgramCharHelper(IteratorT const &begin,
                                 IteratorT const &end,
                                 size_t const &ngramRangeMin,
                                 size_t const &ngramRangeMax,
                                 std::function<void (IteratorT&, IteratorT&)> const &callback) {

    std::vector<IteratorT> wordIterVector(IteratorVectorGenerator(begin, end));

    for (size_t strIterOffset = 0; strIterOffset < wordIterVector.size(); ++strIterOffset)  {
        for (size_t ngramRangeVal = ngramRangeMin; ngramRangeVal <= ngramRangeMax; ++ngramRangeVal) {
            if (strIterOffset + ngramRangeVal < wordIterVector.size())
                callback(wordIterVector[strIterOffset], wordIterVector[strIterOffset + ngramRangeVal]);
        }
    }
}

template <
    typename IteratorT,
    typename IsDelimiterT
>
inline void ParseNgramWord(std::string &input,
                           IsDelimiterT const &isDelimiter,
                           size_t const &ngramRangeMin,
                           size_t const &ngramRangeMax,
                           std::function<void (IteratorT&, IteratorT&)> const &callback) {

    std::string trimedString(TrimAndReplace(input.begin(), input.end()));

    //wordIterPairVector is used to store the begin and end iterator of words in input
    std::vector<std::pair<IteratorT, IteratorT>> wordIterPairVector;
    Details::Parse<IteratorT, IsDelimiterT>(
        trimedString.begin(),
        trimedString.end(),
        isDelimiter,
        [&wordIterPairVector] (IteratorT &iterBegin, IteratorT &iterEnd) {
            wordIterPairVector.emplace_back(std::make_pair(iterBegin, iterEnd));
        }
    );

    if (wordIterPairVector.size() == 0)
        throw std::invalid_argument("wordIterPairVector.size() == 0");

    if (ngramRangeMin < 1 || ngramRangeMin > ngramRangeMax || ngramRangeMax > wordIterPairVector.size())
        throw std::invalid_argument("ngramRangeMin and ngramRangeMax not valid");

    for (size_t ngramRangeVal = ngramRangeMin; ngramRangeVal <= ngramRangeMax; ++ngramRangeVal) {
        for (size_t pairIdx = 0; pairIdx < wordIterPairVector.size() - ngramRangeVal + 1; ++pairIdx) {
            callback(wordIterPairVector[pairIdx].first, wordIterPairVector[pairIdx + ngramRangeVal - 1].second);
        }
    }
}

template <typename IteratorT>
inline void ParseNgramChar(std::string &input,
                           size_t const &ngramRangeMin,
                           size_t const &ngramRangeMax,
                           std::function<void (IteratorT&, IteratorT&)> const &callback) {

    std::string trimedString(TrimAndReplace(input.begin(), input.end()));

    if (ngramRangeMin < 1 || ngramRangeMin > ngramRangeMax || ngramRangeMax > trimedString.size())
        throw std::invalid_argument("ngramRangeMin and ngramRangeMax not valid");

    ParseNgramCharHelper<IteratorT>(trimedString.begin(), trimedString.end(), ngramRangeMin, ngramRangeMax, callback);
}

template <
    typename IteratorT,
    typename IsDelimiterT
>
inline void ParseNgramCharwb(std::string &input,
                             IsDelimiterT const &isDelimiter,
                             size_t const &ngramRangeMin,
                             size_t const &ngramRangeMax,
                             std::function<void (IteratorT&, IteratorT&)> const &callback) {

    std::string trimedString(TrimAndReplace(input.begin(), input.end()));

    //wordIterPairVector is used to store the begin and end iterator of words in input
    std::vector<std::pair<IteratorT, IteratorT>> wordIterPairVector;
    Details::Parse<IteratorT, IsDelimiterT>(
        trimedString.begin(),
        trimedString.end(),
        isDelimiter,
        [&wordIterPairVector] (IteratorT &iterBegin, IteratorT &iterEnd) {
            wordIterPairVector.emplace_back(std::make_pair(iterBegin, iterEnd));
        }
    );

    if (wordIterPairVector.size() == 0)
        throw std::invalid_argument("wordIterPairVector.size() == 0");

    if (ngramRangeMin < 1 || ngramRangeMin > ngramRangeMax )
        throw std::invalid_argument("ngramRangeMin and ngramRangeMax not valid");

    for (size_t pairIdx = 0; pairIdx < wordIterPairVector.size(); ++pairIdx) {
        //copy
        std::string const paddedWord = " " + std::string(wordIterPairVector[pairIdx].first, wordIterPairVector[pairIdx].second) + " ";

        ParseNgramCharHelper<IteratorT>(paddedWord.begin(), paddedWord.end(), ngramRangeMin, ngramRangeMax, callback);
    }
}

}

template <typename IteratorT>
inline std::string ToLower(IteratorT begin,
                           IteratorT end) {
    std::string result(begin, end);

#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4244) // conversion from 'unsigned int' to 'unsigned char', possible loss of data
#endif

    std::transform(result.begin(), result.end(), result.begin(), [](char c) { return std::tolower(c); });

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

    return result;
}

template <typename IteratorT>
inline std::string ToUpper(IteratorT begin,
                           IteratorT end) {
    std::string result(begin, end);

#if (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4244) // conversion from 'unsigned int' to 'unsigned char', possible loss of data
#endif

    std::transform(result.begin(), result.end(), result.begin(), [](char c) { return std::toupper(c); });

#if (defined _MSC_VER)
#   pragma warning(pop)
#endif

    return result;
}

template <
    typename IteratorT,
    typename PredicateT
>
inline std::string TrimLeft(IteratorT begin,
                            IteratorT end,
                            PredicateT isPredicate) {
    while (begin != end) {
        if (*begin == isPredicate)
            ++begin;
        else
            break;
    }
    return std::string(begin, end);
}

template <
    typename IteratorT,
    typename PredicateT
>
inline std::string TrimRight(IteratorT begin,
                             IteratorT end,
                             PredicateT isPredicate) {
    IteratorT offset = begin;
    IteratorT iter = begin;
    while (iter != end) {
        if (*iter != isPredicate)
            offset = iter;
        ++iter;
    }
    return std::string(begin, offset + 1);
}

template <
    typename IteratorT,
    typename PredicateT
>
inline std::string Trim(IteratorT begin,
                        IteratorT end,
                        PredicateT isPredicate) {
    std::string stringAfterTrimedLeft(TrimLeft(begin, end, isPredicate));
    return TrimRight(stringAfterTrimedLeft.begin(), stringAfterTrimedLeft.end(), isPredicate);
}

template <
    typename IteratorT,
    typename IsDelimiterT
>
inline void Parse(std::string const &input,
                  IsDelimiterT const &isDelimiter,
                  std::function<void (IteratorT&, IteratorT&)> const &callback) {

    Details::Parse(input.begin(), input.end(), isDelimiter, callback);
}

template <
    typename IteratorT,
    typename RegexT
>
inline void ParseRegex(std::string const &input,
                       RegexT const &regexToken,
                       std::function<void (IteratorT&, IteratorT&)> const &callback) {

    Details::ParseRegex(input.begin(), input.end(), regexToken, callback);
}

template <
    typename IteratorT,
    typename IsDelimiterT
>
inline void ParseNgramWord(std::string &input,
                           IsDelimiterT const &isDelimiter,
                           size_t const &ngramRangeMin,
                           size_t const &ngramRangeMax,
                           std::function<void (IteratorT&, IteratorT&)> const &callback) {

    Details::ParseNgramWord(input, isDelimiter, ngramRangeMin, ngramRangeMax, callback);
}

template <
    typename IteratorT,
    typename IsDelimiterT
>
inline void ParseNgramWordCopy(std::string const &input,
                               IsDelimiterT const &isDelimiter,
                               size_t const &ngramRangeMin,
                               size_t const &ngramRangeMax,
                               std::function<void (IteratorT&, IteratorT&)> const &callback) {

    //copy string to trim
    std::string inputCopy(input);
    Details::ParseNgramWord(inputCopy, isDelimiter, ngramRangeMin, ngramRangeMax, callback);
}

template <typename IteratorT>
inline void ParseNgramChar(std::string &input,
                           size_t const &ngramRangeMin,
                           size_t const &ngramRangeMax,
                           std::function<void (IteratorT&, IteratorT&)> const &callback) {

    Details::ParseNgramChar(input, ngramRangeMin, ngramRangeMax, callback);
}

template <typename IteratorT>
inline void ParseNgramCharCopy(std::string const &input,
                               size_t const &ngramRangeMin,
                               size_t const &ngramRangeMax,
                               std::function<void (IteratorT&, IteratorT&)> const &callback) {

    //copy string to trim
    std::string inputCopy(input);
    Details::ParseNgramChar(inputCopy, ngramRangeMin, ngramRangeMax, callback);
}

template <
    typename IteratorT,
    typename IsDelimiterT
>
inline void ParseNgramCharwb(std::string &input,
                             IsDelimiterT const &isDelimiter,
                             size_t const &ngramRangeMin,
                             size_t const &ngramRangeMax,
                             std::function<void (IteratorT&, IteratorT&)> const &callback) {

    Details::ParseNgramCharwb(input, isDelimiter, ngramRangeMin, ngramRangeMax, callback);
}

template <
    typename IteratorT,
    typename IsDelimiterT
>
inline void ParseNgramCharwbCopy(std::string const &input,
                                 IsDelimiterT const &isDelimiter,
                                 size_t const &ngramRangeMin,
                                 size_t const &ngramRangeMax,
                                 std::function<void (IteratorT&, IteratorT&)> const &callback) {

    //copy string to trim
    std::string inputCopy(input);
    Details::ParseNgramCharwb(inputCopy, isDelimiter, ngramRangeMin, ngramRangeMax, callback);
}

} // namespace Featurizer
} // namespace Microsoft
