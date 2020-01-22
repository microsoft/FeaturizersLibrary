// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

namespace Microsoft {
namespace Featurizer {
namespace Details {

template<typename IteratorT>
inline std::vector<IteratorT> IteratorVectorGenerator(IteratorT begin,
                                                      IteratorT end) {
    std::vector<IteratorT> wordIterVector;

    for (IteratorT strIter = begin; strIter != end; ++strIter)
        wordIterVector.emplace_back(strIter);
    wordIterVector.emplace_back(end);

    return wordIterVector;
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Parse string by isPredicate and callback each element
template <
    typename IteratorT,
    typename IsPredicateT
>
inline void Parse(IteratorT const &begin,
                  IteratorT const &end,
                  IsPredicateT const &isPredicate,
                  std::function<void (IteratorT, IteratorT)> const &callback) {

    IteratorT left = begin;
    IteratorT right = left;
    while (left != end && isPredicate(*left))
        ++left;

    right = left;
    while (right != end) {
        if (isPredicate(*right)) {
            callback(left, right);
            left = right;
            while (left != end && isPredicate(*left))
                ++left;
            right = left;
        } else {
            ++right;
        }
    }
    if (left != right)
        callback(left, right);
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Parse string by RegexToken and callback each element
template <
    typename IteratorT,
    typename RegexT
>
inline void ParseRegex(IteratorT const &begin,
                       IteratorT const &end,
                       RegexT const &regexToken,
                       std::function<void (IteratorT, IteratorT)> const &callback) {

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

/////////////////////////////////////////////////////////////////////////
///  \brief         Replace each char to whitespace if it's isPredicate()
///                 and de-duplicate whitespaces
template <typename PredicateT>
inline std::string ReplaceAndDeDuplicate(std::string input,
                                         PredicateT isPredicate = [](char c) {if (std::ispunct(c)) return true; return false;}) {
    //replace all punctuations with spaces
    std::transform(input.begin(), input.end(), input.begin(), [&isPredicate](char c) {
        if (isPredicate(c) )
            return ' ';
        return c;
    });

    //remove duplicate space
    bool prevIsSpace = false;
    input.erase(
        std::remove_if(
            input.begin(),
            input.end(),
            [&prevIsSpace](char curr){
                bool isDupSpace = std::isspace(curr) && prevIsSpace;
                prevIsSpace = std::isspace(curr);
                return isDupSpace;
            }
        ),
        input.end()
    );

    return input;
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Helper function used by ParseNgram series
template <typename IteratorT>
inline void ParseNgramCharHelper(IteratorT const &begin,
                                 IteratorT const &end,
                                 size_t const ngramRangeMin,
                                 size_t const ngramRangeMax,
                                 std::function<void (IteratorT, IteratorT)> const &callback) {

    std::vector<IteratorT> wordIterVector(IteratorVectorGenerator(begin, end));

    for (size_t strIterOffset = 0; strIterOffset < wordIterVector.size(); ++strIterOffset)  {
        for (size_t ngramRangeVal = ngramRangeMin; ngramRangeVal <= ngramRangeMax; ++ngramRangeVal) {
            if (strIterOffset + ngramRangeVal < wordIterVector.size()) {
                callback(wordIterVector[strIterOffset], wordIterVector[strIterOffset + ngramRangeVal]);
                break;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////
///  \brief         N-gram applies to word(word n-grams). The Ngram range
///                 is the lower and upper boundary of the range of n-values
///                 for different n-grams to be extracted.
///                 Example:
///                     input: "word1 word2 word3"
///                     n-gram range: (1, 2)
///                     output: ["word1","word2","word3","word1 word2","word2 word3"]
template <
    typename IteratorT,
    typename IsPredicateT
>
inline void ParseNgramWord(std::string &input,
                           IsPredicateT const &isPredicate,
                           size_t const ngramRangeMin,
                           size_t const ngramRangeMax,
                           std::function<void (IteratorT, IteratorT)> const &callback) {

    std::string trimedString(ReplaceAndDeDuplicate<std::function<bool (char)>>(input));

    //wordIterPairVector is used to store the begin and end iterator of words in input
    std::vector<std::pair<IteratorT, IteratorT>> wordIterPairVector;
    Details::Parse<IteratorT, IsPredicateT>(
        trimedString.begin(),
        trimedString.end(),
        isPredicate,
        [&wordIterPairVector] (IteratorT iterBegin, IteratorT iterEnd) {
            wordIterPairVector.emplace_back(iterBegin, iterEnd);
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

/////////////////////////////////////////////////////////////////////////
///  \brief         N-gram applies to character(char n-grams).
///
///                 Example:
///                     input: "jumpy fox"
///                     n-gram range: (5, 5)
///                     output: ["jumpy", "umpy ", "mpy f", "py fo", "y fox"]
template <typename IteratorT>
inline void ParseNgramChar(std::string &input,
                           size_t const ngramRangeMin,
                           size_t const ngramRangeMax,
                           std::function<void (IteratorT, IteratorT)> const &callback) {

    std::string trimedString(ReplaceAndDeDuplicate<std::function<bool (char)>>(input));

    if (ngramRangeMin < 1 || ngramRangeMin > ngramRangeMax || ngramRangeMax > trimedString.size())
        throw std::invalid_argument("ngramRangeMin and ngramRangeMax not valid");

    ParseNgramCharHelper<IteratorT>(trimedString.begin(), trimedString.end(), ngramRangeMin, ngramRangeMax, callback);
}

/////////////////////////////////////////////////////////////////////////
///  \brief         N-gram applies to character within bound(charwb n-grams).
///                 Each word will be padded with whitespace and then applied
///                 char n-grams.
///
///                 Example:
///                     input: "jumpy fox"
///                     n-gram range: (5, 5)
///                     output: [" jump", "jumpy", "umpy ", " fox "]
template <
    typename IteratorT,
    typename IsPredicateT
>
inline void ParseNgramCharwb(std::string &input,
                             IsPredicateT const &isPredicate,
                             size_t const ngramRangeMin,
                             size_t const ngramRangeMax,
                             std::function<void (IteratorT, IteratorT)> const &callback) {

    std::string trimedString(ReplaceAndDeDuplicate<std::function<bool (char)>>(input));

    //wordIterPairVector is used to store the begin and end iterator of words in input
    std::vector<std::pair<IteratorT, IteratorT>> wordIterPairVector;
    Details::Parse<IteratorT, IsPredicateT>(
        trimedString.begin(),
        trimedString.end(),
        isPredicate,
        [&wordIterPairVector] (IteratorT iterBegin, IteratorT iterEnd) {
            wordIterPairVector.emplace_back(iterBegin, iterEnd);
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

/////////////////////////////////////////////////////////////////////////
///  \brief         lowercase string
///                 only support ASCII, will do UTF-8 in later PR
inline std::string ToLower(std::string input) {
    //static_cast<char> is to suppress MSVC compiler warning on implicitly conversion of int to char
    std::transform(input.begin(), input.end(), input.begin(), [](char c) { return static_cast<char>(std::tolower(c)); });
    return input;
}

/////////////////////////////////////////////////////////////////////////
///  \brief         uppercase string
///                 only support ASCII, will do UTF-8 in later PR
inline std::string ToUpper(std::string input) {
    //static_cast<char> is to suppress MSVC compiler warning on implicitly conversion of int to char
    std::transform(input.begin(), input.end(), input.begin(), [](char c) { return static_cast<char>(std::toupper(c)); });
    return input;
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Trim all the leading elements determined by isPredicate
///                 in a string
template <typename PredicateT>
inline std::string TrimLeft(std::string input,
                            PredicateT isPredicate) {
    input.erase(input.begin(), std::find_if(input.begin(), input.end(), [&isPredicate](char c) {
        return !isPredicate(c);
    }));
    return input;
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Trim all the tailing elements determined by isPredicate
///                 in a string
template <typename PredicateT>
inline std::string TrimRight(std::string input,
                             PredicateT isPredicate) {
    input.erase(std::find_if(input.rbegin(), input.rend(), [&isPredicate](char c) {
        return !isPredicate(c);}).base(), input.end());
    return input;
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Trim all the leading and tailing elements determined
///                 by isPredicate in a string
template <typename PredicateT>
inline std::string Trim(std::string input,
                        PredicateT isPredicate) {
    return TrimRight(TrimLeft(input, isPredicate), isPredicate);
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Details::Parse wrapper
template <
    typename IteratorT,
    typename IsPredicateT
>
inline void Parse(std::string const &input,
                  IsPredicateT const &isPredicate,
                  std::function<void (IteratorT, IteratorT)> const &callback) {

    Details::Parse(input.begin(), input.end(), isPredicate, callback);
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Details::ParseRegex wrapper
template <
    typename IteratorT,
    typename RegexT
>
inline void ParseRegex(std::string const &input,
                       RegexT const &regexToken,
                       std::function<void (IteratorT, IteratorT)> const &callback) {

    Details::ParseRegex(input.begin(), input.end(), regexToken, callback);
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Details::ParseNgramWord wrapper for mutable input string
template <
    typename IteratorT,
    typename IsPredicateT
>
inline void ParseNgramWord(std::string &input,
                           IsPredicateT const &isPredicate,
                           size_t const ngramRangeMin,
                           size_t const ngramRangeMax,
                           std::function<void (IteratorT, IteratorT)> const &callback) {

    Details::ParseNgramWord(input, isPredicate, ngramRangeMin, ngramRangeMax, callback);
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Details::ParseNgramWord wrapper for const input string
template <
    typename IteratorT,
    typename IsPredicateT
>
inline void ParseNgramWordCopy(std::string const &input,
                               IsPredicateT const &isPredicate,
                               size_t const ngramRangeMin,
                               size_t const ngramRangeMax,
                               std::function<void (IteratorT, IteratorT)> const &callback) {

    //copy string to trim
    std::string inputCopy(input);
    Details::ParseNgramWord(inputCopy, isPredicate, ngramRangeMin, ngramRangeMax, callback);
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Details::ParseNgramChar wrapper for mutable input string
template <typename IteratorT>
inline void ParseNgramChar(std::string &input,
                           size_t const ngramRangeMin,
                           size_t const ngramRangeMax,
                           std::function<void (IteratorT, IteratorT)> const &callback) {

    Details::ParseNgramChar(input, ngramRangeMin, ngramRangeMax, callback);
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Details::ParseNgramChar wrapper for const input string
template <typename IteratorT>
inline void ParseNgramCharCopy(std::string const &input,
                               size_t const ngramRangeMin,
                               size_t const ngramRangeMax,
                               std::function<void (IteratorT, IteratorT)> const &callback) {

    //copy string to trim
    std::string inputCopy(input);
    Details::ParseNgramChar(inputCopy, ngramRangeMin, ngramRangeMax, callback);
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Details::ParseNgramCharwb wrapper for mutable input string
template <
    typename IteratorT,
    typename IsPredicateT
>
inline void ParseNgramCharwb(std::string &input,
                             IsPredicateT const &isPredicate,
                             size_t const ngramRangeMin,
                             size_t const ngramRangeMax,
                             std::function<void (IteratorT, IteratorT)> const &callback) {

    Details::ParseNgramCharwb(input, isPredicate, ngramRangeMin, ngramRangeMax, callback);
}

/////////////////////////////////////////////////////////////////////////
///  \brief         Details::ParseNgramCharwb wrapper for const input string
template <
    typename IteratorT,
    typename IsPredicateT
>
inline void ParseNgramCharwbCopy(std::string const &input,
                                 IsPredicateT const &isPredicate,
                                 size_t const ngramRangeMin,
                                 size_t const ngramRangeMax,
                                 std::function<void (IteratorT, IteratorT)> const &callback) {

    //copy string to trim
    std::string inputCopy(input);
    Details::ParseNgramCharwb(inputCopy, isPredicate, ngramRangeMin, ngramRangeMax, callback);
}

} // namespace Featurizer
} // namespace Microsoft
