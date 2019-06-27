// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#include "regex_vectorizer.hpp"

const char* const str_regex_word = "(\\S)+";

namespace DataPipelines::StringTransforms::RegEx {
    using namespace std;
    
    // Use some template trickery to reuse the same code 
    // for whatever type 
    template<typename T> constexpr T true_val() { return 1; }
    template<typename T> constexpr T false_val() { return 0; }
    template<> constexpr bool true_val<bool>() { return true; }
    template<> constexpr bool false_val<bool>() { return false; }
    template<> constexpr double true_val<double>() { return 1.0; }
    template<> constexpr double false_val<double>() { return 0.0; }


    // Vectorize occurences of a list of regexes in a list of strings.
    template<typename T> vector<vector<T>> 
    VectorizeList(const vector<re>& regexList, const vector<string>& input, bool normalize) {

        vector<vector<T>> results;
        results.reserve(input.size());
        size_t count = regexList.size();
        T trueVal = true_val<T>();

        // I really don't think this is right, not really normalized,
        // but it's what the python reference does...
        if (normalize && count) {
            trueVal /= static_cast<T>(count);
        }
        for (auto s : input)
        {
            vector<T> v;
            v.reserve(count);
            for (const re& regEx : regexList)
            {
                v.emplace_back(
                    std::regex_search(s, regEx, reconst::match_any | reconst::match_not_null) 
                    ? trueVal : false_val<T>());
            }
            results.push_back(std::move(v));
        }
        return results;
    }
    vector<vector<double>> 
    VectorizeList(const vector<re>& regexList, const vector<string>& input, bool normalize) {
        return VectorizeList<double>(regexList, input, normalize);
    }
    vector<vector<bool>> 
    VectorizeListBool(const vector<re>& regexList, const vector<string>& input) {
        return VectorizeList<bool>(regexList, input, false);
    }
 
    // Vectorize occurences of a list of regexes in individual words 
    // in a list of strings.
    vector3<double>
    VectorizeWords(const vector<re>& regexList, const vector<string>& input, bool normalize) {

        vector3<double> results;
        results.reserve(input.size());

        for (const string& str : input) {
            // Break the string up into a vector of words
            vector<string> v;
            std::regex wordsRegex(str_regex_word);
            auto words_end = std::sregex_iterator();
            for (auto i = std::sregex_iterator(str.begin(), str.end(), wordsRegex); 
                 i != words_end; ++i) {
                std::smatch m = *i;
                v.push_back(m.str());
            }
            // Now vectorize this list of strings and add it on.
            results.emplace_back(VectorizeList(regexList, v, normalize));
        }
        return results;
    }
}

