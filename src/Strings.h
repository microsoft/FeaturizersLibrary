// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

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
///  \brief         Parse string by predicate and callback each element
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
///  \brief         Parse string by RegexToken and callback each element
///
template <
    typename IteratorT,
    typename RegexT
>
void ParseRegex(std::string const &input,
                std::vector<std::string> &intermediateValues,
                RegexT const &regexToken,
                std::function<void (IteratorT, IteratorT)> const &callback);

/////////////////////////////////////////////////////////////////////////
///  \fn            ParseNgramWord
///  \brief         N-gram applies to word(word n-grams). The Ngram range
///                 is the lower and upper boundary of the range of n-values
///                 for different n-grams to be extracted.
///                 Example:
///                     input: "word1 word2 word3"
///                     n-gram range: (1, 2)
///                     output: ["word1","word2","word3","word1 word2","word2 word3"]
///
template <
    typename IteratorT,
    typename UnaryPredicateT
>
void ParseNgramWord(std::string &input,
                    std::vector<std::string> &intermediateValues,
                    UnaryPredicateT const &predicate,
                    size_t const ngramRangeMin,
                    size_t const ngramRangeMax,
                    std::function<void (IteratorT, IteratorT)> const &callback);

/////////////////////////////////////////////////////////////////////////
///  \fn            ParseNgramWordCopy
///  \brief         See ParseNgramWord
///
template <
    typename IteratorT,
    typename UnaryPredicateT
>
void ParseNgramWordCopy(std::string const &input,
                        std::vector<std::string> &intermediateValues,
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
void ParseNgramChar(std::string &input,
                    std::vector<std::string> &intermediateValues,
                    size_t const ngramRangeMin,
                    size_t const ngramRangeMax,
                    std::function<void (IteratorT, IteratorT)> const &callback);

/////////////////////////////////////////////////////////////////////////
///  \fn            ParseNgramCharCopy
///  \brief         See ParseNgramChar
///
template <typename IteratorT>
void ParseNgramCharCopy(std::string const &input,
                        std::vector<std::string> &intermediateValues,
                        size_t const ngramRangeMin,
                        size_t const ngramRangeMax,
                        std::function<void (IteratorT, IteratorT)> const &callback);

/////////////////////////////////////////////////////////////////////////
///  \fn            ParseNgramCharwb
///  \brief         N-gram applies to character within bound(charwb n-grams).
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
void ParseNgramCharwb(std::string &input,
                      std::vector<std::string> &intermediateValues,
                      UnaryPredicateT const &predicate,
                      size_t const ngramRangeMin,
                      size_t const ngramRangeMax,
                      std::function<void (IteratorT, IteratorT)> const &callback);

/////////////////////////////////////////////////////////////////////////
///  \fn            ParseNgramCharwbCopy
///  \brief         See ParseNgramCharwb
///
template <
    typename IteratorT,
    typename UnaryPredicateT
>
void ParseNgramCharwbCopy(std::string const &input,
                          std::vector<std::string> &intermediateValues,
                          UnaryPredicateT const &predicate,
                          size_t const ngramRangeMin,
                          size_t const ngramRangeMax,
                          std::function<void (IteratorT, IteratorT)> const &callback);

/////////////////////////////////////////////////////////////////////////
///  \fn            UParse
///  \brief         See Parse, uniform signature
///
template <
    typename IteratorT,
    typename UnaryPredicateT,
    typename RegexT
>
void UParse(std::string const &input,
            std::vector<std::string> &,
            UnaryPredicateT const &predicate,
            RegexT const &,
            size_t const,
            size_t const,
            std::function<void (IteratorT, IteratorT)> const &callback);

/////////////////////////////////////////////////////////////////////////
///  \fn            UParseRegex
///  \brief         See ParseRegex, uniform signature
///
template <
    typename IteratorT,
    typename UnaryPredicateT,
    typename RegexT
>
void UParseRegex(std::string const &input,
                 std::vector<std::string> &intermediateValues,
                 UnaryPredicateT const &,
                 RegexT const &regexToken,
                 size_t const,
                 size_t const,
                 std::function<void (IteratorT, IteratorT)> const &callback);

/////////////////////////////////////////////////////////////////////////
///  \fn            UParseNgramWordCopy
///  \brief         See ParseNgramWordCopy, uniform signature
///
template <
    typename IteratorT,
    typename UnaryPredicateT,
    typename RegexT
>
void UParseNgramWordCopy(std::string const &input,
                         std::vector<std::string> &intermediateValues,
                         UnaryPredicateT const &predicate,
                         RegexT const &,
                         size_t const ngramRangeMin,
                         size_t const ngramRangeMax,
                         std::function<void (IteratorT, IteratorT)> const &callback);

/////////////////////////////////////////////////////////////////////////
///  \fn            UParseNgramCharCopy
///  \brief         See ParseNgramCharCopy, uniform signature
///
template <
    typename IteratorT,
    typename UnaryPredicateT,
    typename RegexT
>
void UParseNgramCharCopy(std::string const &input,
                         std::vector<std::string> &intermediateValues,
                         UnaryPredicateT const &,
                         RegexT const &,
                         size_t const ngramRangeMin,
                         size_t const ngramRangeMax,
                         std::function<void (IteratorT, IteratorT)> const &callback);

/////////////////////////////////////////////////////////////////////////
///  \fn            UParseNgramCharwbCopy
///  \brief         See ParseNgramCharwbCopy, uniform signature
///
template <
    typename IteratorT,
    typename UnaryPredicateT,
    typename RegexT
>
void UParseNgramCharwbCopy(std::string const &input,
                           std::vector<std::string> &intermediateValues,
                           UnaryPredicateT const &predicate,
                           RegexT const &,
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

template<typename IteratorT>
inline std::vector<IteratorT> IteratorVectorGenerator(IteratorT const & begin,
                                                      IteratorT const & end) {
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
                       std::vector<std::string> &intermediateValues,
                       RegexT const &regexToken,
                       std::function<void (IteratorT, IteratorT)> const &callback) {

    std::sregex_iterator iter(begin, end, regexToken);
    std::sregex_iterator iterEnd;

    //this hardcode is not good but I did not find a better way
    //prevent vector re-allocation caused dangling iterator
    intermediateValues.reserve(100);

    while (iter != iterEnd) {
        std::string iterStringConst = iter->str();
        intermediateValues.emplace_back(std::move(iterStringConst));
        IteratorT beginRef = intermediateValues.back().begin();
        IteratorT endRef = intermediateValues.back().end();
        callback(beginRef, endRef);
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
                std::vector<std::string> &intermediateValues,
                RegexT const &regexToken,
                std::function<void (IteratorT, IteratorT)> const &callback) {

    Details::ParseRegex(input.begin(), input.end(), intermediateValues, regexToken, callback);
}

template <
    typename IteratorT,
    typename UnaryPredicateT
>
void ParseNgramWord(std::string &input,
                    std::vector<std::string> &intermediateValues,
                    UnaryPredicateT const &predicate,
                    size_t const ngramRangeMin,
                    size_t const ngramRangeMax,
                    std::function<void (IteratorT, IteratorT)> const &callback) {

    intermediateValues.emplace_back(Details::ReplaceAndDeDuplicate<std::function<bool (char)>>(input));

    //wordIterPairVector is used to store the begin and end iterator of words in input
    std::vector<std::pair<IteratorT, IteratorT>> wordIterPairVector;
    Details::Parse<IteratorT, UnaryPredicateT>(
        intermediateValues[0].begin(),
        intermediateValues[0].end(),
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

template <
    typename IteratorT,
    typename UnaryPredicateT
>
void ParseNgramWordCopy(std::string const &input,
                        std::vector<std::string> &intermediateValues,
                        UnaryPredicateT const &predicate,
                        size_t const ngramRangeMin,
                        size_t const ngramRangeMax,
                        std::function<void (IteratorT, IteratorT)> const &callback) {

    //copy string to trim
    std::string inputCopy(input);
    ParseNgramWord(inputCopy, intermediateValues, predicate, ngramRangeMin, ngramRangeMax, callback);
}

template <typename IteratorT>
void ParseNgramChar(std::string &input,
                    std::vector<std::string> &intermediateValues,
                    size_t const ngramRangeMin,
                    size_t const ngramRangeMax,
                    std::function<void (IteratorT, IteratorT)> const &callback) {

    intermediateValues.emplace_back(Details::ReplaceAndDeDuplicate<std::function<bool (char)>>(input));

    if (ngramRangeMin < 1 || ngramRangeMin > ngramRangeMax || ngramRangeMax > intermediateValues[0].size())
        throw std::invalid_argument("ngramRangeMin and ngramRangeMax not valid");

    Details::ParseNgramCharHelper<IteratorT>(intermediateValues[0].begin(), intermediateValues[0].end(), ngramRangeMin, ngramRangeMax, callback);
}

template <typename IteratorT>
void ParseNgramCharCopy(std::string const &input,
                        std::vector<std::string> &intermediateValues,
                        size_t const ngramRangeMin,
                        size_t const ngramRangeMax,
                        std::function<void (IteratorT, IteratorT)> const &callback) {

    //copy string to trim
    std::string inputCopy(input);
    ParseNgramChar(inputCopy, intermediateValues, ngramRangeMin, ngramRangeMax, callback);
}

template <
    typename IteratorT,
    typename UnaryPredicateT
>
void ParseNgramCharwb(std::string &input,
                      std::vector<std::string> &intermediateValues,
                      UnaryPredicateT const &predicate,
                      size_t const ngramRangeMin,
                      size_t const ngramRangeMax,
                      std::function<void (IteratorT, IteratorT)> const &callback) {

    //this hardcode is not good but I did not find a better way
    //prevent vector re-allocation caused dangling iterator
    intermediateValues.reserve(100);

    intermediateValues.emplace_back(Details::ReplaceAndDeDuplicate<std::function<bool (char)>>(input));

    //wordIterPairVector is used to store the begin and end iterator of words in input
    std::vector<std::pair<IteratorT, IteratorT>> wordIterPairVector;
    Details::Parse<IteratorT, UnaryPredicateT>(
        intermediateValues[0].begin(),
        intermediateValues[0].end(),
        predicate,
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
        std::string paddedWord = " " + std::string(wordIterPairVector[pairIdx].first, wordIterPairVector[pairIdx].second) + " ";
        intermediateValues.push_back(std::move(paddedWord));

        Details::ParseNgramCharHelper<IteratorT>(intermediateValues[pairIdx + 1].begin(), intermediateValues[pairIdx + 1].end(), ngramRangeMin, ngramRangeMax, callback);
    }
}

template <
    typename IteratorT,
    typename UnaryPredicateT
>
void ParseNgramCharwbCopy(std::string const &input,
                          std::vector<std::string> &intermediateValues,
                          UnaryPredicateT const &predicate,
                          size_t const ngramRangeMin,
                          size_t const ngramRangeMax,
                          std::function<void (IteratorT, IteratorT)> const &callback) {

    //copy string to trim
    std::string inputCopy(input);
    ParseNgramCharwb(inputCopy, intermediateValues, predicate, ngramRangeMin, ngramRangeMax, callback);
}

//to uniform so that all parse functions have same number of signature
template <
    typename IteratorT,
    typename UnaryPredicateT,
    typename RegexT
>
void UParse(std::string const &input,
            std::vector<std::string> &,
            UnaryPredicateT const &predicate,
            RegexT const &,
            size_t const,
            size_t const,
            std::function<void (IteratorT, IteratorT)> const &callback) {

    Parse(input, predicate, callback);
}

template <
    typename IteratorT,
    typename UnaryPredicateT,
    typename RegexT
>
void UParseRegex(std::string const &input,
                 std::vector<std::string> &intermediateValues,
                 UnaryPredicateT const &,
                 RegexT const &regexToken,
                 size_t const,
                 size_t const,
                 std::function<void (IteratorT, IteratorT)> const &callback) {

    ParseRegex(input, intermediateValues, regexToken, callback);
}

template <
    typename IteratorT,
    typename UnaryPredicateT,
    typename RegexT
>
void UParseNgramWordCopy(std::string const &input,
                         std::vector<std::string> &intermediateValues,
                         UnaryPredicateT const &predicate,
                         RegexT const &,
                         size_t const ngramRangeMin,
                         size_t const ngramRangeMax,
                         std::function<void (IteratorT, IteratorT)> const &callback) {

    ParseNgramWordCopy(input, intermediateValues, predicate, ngramRangeMin, ngramRangeMax, callback);
}

template <
    typename IteratorT,
    typename UnaryPredicateT,
    typename RegexT
>
void UParseNgramCharCopy(std::string const &input,
                         std::vector<std::string> &intermediateValues,
                         UnaryPredicateT const &,
                         RegexT const &,
                         size_t const ngramRangeMin,
                         size_t const ngramRangeMax,
                         std::function<void (IteratorT, IteratorT)> const &callback) {

    ParseNgramCharCopy(input, intermediateValues, ngramRangeMin, ngramRangeMax, callback);
}

template <
    typename IteratorT,
    typename UnaryPredicateT,
    typename RegexT
>
void UParseNgramCharwbCopy(std::string const &input,
                           std::vector<std::string> &intermediateValues,
                           UnaryPredicateT const &predicate,
                           RegexT const &,
                           size_t const ngramRangeMin,
                           size_t const ngramRangeMax,
                           std::function<void (IteratorT, IteratorT)> const &callback) {

    ParseNgramCharwbCopy(input, intermediateValues, predicate, ngramRangeMin, ngramRangeMax, callback);
}

} // namespace Strings
} // namespace Featurizer
} // namespace Microsoft
