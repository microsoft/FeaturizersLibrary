// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include<algorithm>
#include<functional>
#include<regex>
#include<string>
#include<vector>

namespace Microsoft {
namespace Featurizer {
namespace Strings {

/////////////////////////////////////////////////////////////////////////
///  \fn            ToLower
///  \brief         lowercase string
///                 only support ASCII, will do UTF-8 in later PR
///
inline std::string ToLower(std::string input);

/////////////////////////////////////////////////////////////////////////
///  \fn            ToUpper
///  \brief         uppercase string
///                 only support ASCII, will do UTF-8 in later PR
///
inline std::string ToUpper(std::string input);

/////////////////////////////////////////////////////////////////////////
///  \fn            TrimLeft
///  \brief         Trim all the leading elements determined by predicate
///                 in a string
///
template <typename UnaryPredicateT>
std::string TrimLeft(std::string input,
                     UnaryPredicateT predicate);

/////////////////////////////////////////////////////////////////////////
///  \fn            TrimRight
///  \brief         Trim all the tailing elements determined by predicate
///                 in a string
///
template <typename UnaryPredicateT>
std::string TrimRight(std::string input,
                      UnaryPredicateT predicate);

/////////////////////////////////////////////////////////////////////////
///  \fn            Trim
///  \brief         Trim all the leading and tailing elements determined
///                 by predicate in a string
///
template <typename UnaryPredicateT>
std::string Trim(std::string input,
                 UnaryPredicateT predicate);

/////////////////////////////////////////////////////////////////////////
///  \fn            Parse
///  \brief         Parse string using predicate and callback each element
///
template <
    typename IteratorT,
    typename UnaryPredicateT
>
void Parse(std::string const &input,
           UnaryPredicateT const &predicate,
           std::function<void (IteratorT, IteratorT)> const &callback);

/////////////////////////////////////////////////////////////////////////
///  \fn            ParseRegex
///  \brief         Parse string using RegexToken and callback each element
///
template <
    typename IteratorT,
    typename RegexT
>
void ParseRegex(std::string const &input,
                RegexT const &regexToken,
                std::function<void (IteratorT, IteratorT)> const &callback);

/////////////////////////////////////////////////////////////////////////
///  \fn            ParseNgramWord
///  \brief         N-gram applies to word(word n-grams). The Ngram range
///                 is the lower and upper boundary of the range of words
///                 can appear in a single output string
///                 Example:
///                     input: "word1 word2 word3"
///                     n-gram range: (1, 2)
///                     output: ["word1","word2","word3","word1 word2","word2 word3"]
///                 In this case, there can be 1 or 2 words within a single output string
///
template <
    typename IteratorT,
    typename UnaryPredicateT
>
void ParseNgramWord(std::string const &input,
                    UnaryPredicateT const &predicate,
                    size_t const ngramRangeMin,
                    size_t const ngramRangeMax,
                    std::function<void (IteratorT, IteratorT)> const &callback);

/////////////////////////////////////////////////////////////////////////
///  \fn            ParseNgramChar
///  \brief         N-gram applies to character(char n-grams).
///
///                 Example:
///                     input: "jumpy fox"
///                     n-gram range: (5, 5)
///                     output: ["jumpy", "umpy ", "mpy f", "py fo", "y fox"]
///
template <typename IteratorT>
void ParseNgramChar(std::string const &input,
                    size_t const ngramRangeMin,
                    size_t const ngramRangeMax,
                    std::function<void (IteratorT, IteratorT)> const &callback);


/////////////////////////////////////////////////////////////////////////
///  \fn            ParseNgramCharwb
///  \brief         N-gram applies to charwb(character within bound).
///                 Each word will be padded with whitespace and then applied
///                 char n-grams.
///
///                 Example:
///                     input: "jumpy fox"
///                     n-gram range: (5, 5)
///                     output: [" jump", "jumpy", "umpy ", " fox "]
///
template <
    typename IteratorT,
    typename UnaryPredicateT
>
void ParseNgramCharwb(std::string const &input,
                      UnaryPredicateT const &predicate,
                      size_t const ngramRangeMin,
                      size_t const ngramRangeMax,
                      std::function<void (IteratorT, IteratorT)> const &callback);


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Implementation
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
namespace Details {

template <typename UnaryPredicateT>
std::string StringPadding(std::string const & input, UnaryPredicateT predicate) {

    bool isFirstPredicate = predicate(input.at(0));
    bool isLastPredicate = predicate(input.at(input.length() - 1));

    if (!isFirstPredicate && !isLastPredicate) {
        return " " + input + " ";
    } else if (!isFirstPredicate) {
        return " " + input;
    } else if (!isLastPredicate){
        return input + " ";
    } else {
        return input;
    }
}

template<typename IteratorT>
inline std::vector<IteratorT> IteratorVectorGenerator(IteratorT begin,
                                                      IteratorT end) {
    std::vector<IteratorT> wordIterVector;

    wordIterVector.reserve(static_cast<size_t>(std::distance(begin, end) + 1));

    for (IteratorT strIter = begin; strIter != end; ++strIter)
        wordIterVector.emplace_back(strIter);
    wordIterVector.emplace_back(end);

    return wordIterVector;
}

template <
    typename IteratorT,
    typename UnaryPredicateT
>
void Parse(IteratorT const &begin,
           IteratorT const &end,
           UnaryPredicateT const &predicate,
           std::function<void (IteratorT, IteratorT)> const &callback) {

    IteratorT left = begin;
    IteratorT right = left;
    while (left != end && predicate(*left))
        ++left;

    right = left;
    while (right != end) {
        if (predicate(*right)) {
            callback(left, right);
            left = right;
            while (left != end && predicate(*left))
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
                       std::function<void (IteratorT, IteratorT)> const &callback) {

    std::sregex_iterator iter(begin, end, regexToken);
    std::sregex_iterator iterEnd;

    while (iter != iterEnd) {
        IteratorT                           matchStart(begin);
        std::advance(matchStart, iter->position());

        IteratorT                           matchEnd(matchStart);
        std::advance(matchEnd, iter->length());

        callback(matchStart, matchEnd);
        ++iter;
    }
}

template <typename IteratorT>
void ParseNgramCharHelper(IteratorT const &begin,
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

template <typename PredicateT>
std::string ReplaceAndDeDuplicate(std::string input,
                                  PredicateT predicate = [](char c) {if (std::ispunct(c)) return true; return false;}) {
    //replace all punctuations with spaces
    std::transform(
        input.begin(),
        input.end(),
        input.begin(),
        [&predicate](char c) {
            if (predicate(c) )
                return ' ';
            return c;
        }
    );

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

} // namespace Details

inline std::string ToLower(std::string input) {
    //static_cast<char> is to suppress MSVC compiler warning on implicitly conversion of int to char
    std::transform(input.begin(), input.end(), input.begin(), [](char c) { return static_cast<char>(std::tolower(c)); });
    return input;
}

inline std::string ToUpper(std::string input) {
    //static_cast<char> is to suppress MSVC compiler warning on implicitly conversion of int to char
    std::transform(input.begin(), input.end(), input.begin(), [](char c) { return static_cast<char>(std::toupper(c)); });
    return input;
}

template <typename UnaryPredicateT>
std::string TrimLeft(std::string input,
                     UnaryPredicateT predicate) {
    input.erase(input.begin(), std::find_if(input.begin(), input.end(), [&predicate](char c) {
        return !predicate(c);
    }));
    return input;
}

template <typename UnaryPredicateT>
std::string TrimRight(std::string input,
                      UnaryPredicateT predicate) {
    input.erase(std::find_if(input.rbegin(), input.rend(), [&predicate](char c) {
        return !predicate(c);}).base(), input.end());
    return input;
}

template <typename UnaryPredicateT>
std::string Trim(std::string input,
                 UnaryPredicateT predicate) {
    return TrimRight(TrimLeft(input, predicate), predicate);
}

template <
    typename IteratorT,
    typename UnaryPredicateT
>
void Parse(std::string const &input,
           UnaryPredicateT const &predicate,
           std::function<void (IteratorT, IteratorT)> const &callback) {

    Details::Parse(input.begin(), input.end(), predicate, callback);
}

template <
    typename IteratorT,
    typename RegexT
>
void ParseRegex(std::string const &input,
                RegexT const &regexToken,
                std::function<void (IteratorT, IteratorT)> const &callback) {

    Details::ParseRegex(input.begin(), input.end(), regexToken, callback);
}

template <
    typename IteratorT,
    typename UnaryPredicateT
>
void ParseNgramWord(std::string const &input,
                    UnaryPredicateT const &predicate,
                    size_t const ngramRangeMin,
                    size_t const ngramRangeMax,
                    std::function<void (IteratorT, IteratorT)> const &callback) {

    //wordIterPairVector is used to store the begin and end iterator of words in input
    std::vector<std::pair<IteratorT, IteratorT>> wordIterPairVector;
    Details::Parse<IteratorT, UnaryPredicateT>(
        input.begin(),
        input.end(),
        predicate,
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

template <typename IteratorT>
void ParseNgramChar(std::string const &input,
                    size_t const ngramRangeMin,
                    size_t const ngramRangeMax,
                    std::function<void (IteratorT, IteratorT)> const &callback) {

    if (ngramRangeMin < 1 || ngramRangeMin > ngramRangeMax || ngramRangeMax > input.size())
        throw std::invalid_argument("ngramRangeMin and ngramRangeMax not valid");

    Details::ParseNgramCharHelper<IteratorT>(input.begin(), input.end(), ngramRangeMin, ngramRangeMax, callback);
}


template <
    typename IteratorT,
    typename UnaryPredicateT
>
void ParseNgramCharwb(std::string const &input,
                      UnaryPredicateT const &predicate,
                      size_t const ngramRangeMin,
                      size_t const ngramRangeMax,
                      std::function<void (IteratorT, IteratorT)> const &callback) {

    //the pair represents a char(predicate returns true) followed by beginning position of a word,
    //the size of this vector will be 1 + number of words
    std::vector<std::pair<IteratorT, IteratorT>> wordIterPairVector;

    IteratorT itr = input.begin();
    IteratorT end = input.end();

    while (itr != end) {
        if (predicate(*itr)) {
            IteratorT spaceItr = itr;
            IteratorT wordBeginItr = ++itr;
            wordIterPairVector.emplace_back(spaceItr, wordBeginItr);
        } else {
            ++itr;
        }
    }

    if (ngramRangeMin < 1 || ngramRangeMin > ngramRangeMax )
        throw std::invalid_argument("ngramRangeMin and ngramRangeMax not valid");

    for (size_t pairIdx = 0; pairIdx < wordIterPairVector.size() - 1; ++pairIdx) {
        // using wordIterPairVector[pairIdx + 1] because that represents the pairIdx's words ending position(considering predicate returning true char)
        // for example, if we have a decorated string " hello world " and iterator pairs are stored in v
        //
        // v[0].first stores the position of the leading space in front of "hello"
        // v[0].second stores the position of "h"
        // v[1].first stores the position of the leading space in front of "world"
        // v[1].second stores the position of "w"
        //
        // in order to parse " hello ", we need v[0].first and v[1].second
        Details::ParseNgramCharHelper<IteratorT>(wordIterPairVector[pairIdx].first, wordIterPairVector[pairIdx + 1].second, ngramRangeMin, ngramRangeMax, callback);
    }
}


} // namespace Strings
} // namespace Featurizer
} // namespace Microsoft
