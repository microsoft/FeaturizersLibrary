// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------

#pragma once

#include <vector>
#include <regex>

namespace DataPipelines::StringTransforms::RegEx {

    // define some things so the types aren't all 80 chars long
    using re = std::regex;
    namespace reconst = std::regex_constants;

    template <typename T> using vector2 = std::vector<std::vector<T>>;
    template <typename T> using vector3 = std::vector<std::vector<std::vector<T>>>;

    // Default flags - use ECMAScript matching (this is the language default)
    // and 'optimize', which optimizes for actually searching the regex over
    // create/compile 
    const static re::flag_type default_flags = reconst::ECMAScript | reconst::optimize;

    // Compile: Compile regex strings into std::regex objects. 
    // These are persistent, to be passed back in future calls 
    // to Vectorize
    inline std::vector<re> Compile(const std::vector<std::string>& regexStrings, 
                                   const re::flag_type syntaxFlags = default_flags);

    // VectorizeList: Vectorize the strings given.
    // Returns 1.0 per regex (per string) if there is a match. Not the number
    // of matches, just a 1 or 0
    // normalize: does a sort of normalizing of the strings over all the regexes,
    // so its 1/N or 0 instead of 1 or 0
    vector2<double> VectorizeList(const std::vector<re>& regexList, 
                                  const std::vector<std::string>& input,
                                  bool normalize = true);

    // VectorizeListBool: Same as above, but with bool instead of double
    vector2<bool> VectorizeListBool(const std::vector<re>& regexList, 
                                    const std::vector<std::string>& input);
    
    // vector<vector<vector<double>>> ....
    // Needs a multi-dimensional vectors. 
    // Requires discussion regarding e.g. linear algebra libraries, etc.
    vector3<double> VectorizeWords(const std::vector<re>& regexList, 
                                   const std::vector<std::string>& input,
                                   bool normalize = true);


    // One-off straight from string regexes. Simpler if you only need to
    // use the regex list one time. 
    // If you need to reuse the regexes, use one of the persistent versions
    inline vector2<double>
    VectorizeStrings(const std::vector<std::string>& regexStrings, 
                     const std::vector<std::string>& input,
                     bool vectorize = true);
    inline vector2<bool> 
    VectorizeStringsBool(const std::vector<std::string>& regexStrings, 
                        const std::vector<std::string>& input);

    // C++ class encapsulating the persistent regexes and vectorization
    class Vectorizer {
        public:
            Vectorizer(const std::vector<std::string>& regexStrings, 
                        const re::flag_type syntaxFlags = default_flags) :
                        regexList(Compile(regexStrings, syntaxFlags)) {}
                
            Vectorizer(Vectorizer&& other) : regexList(std::move(other.regexList)) {}
        
            Vectorizer(const Vectorizer&) = delete;
            Vectorizer operator=(const Vectorizer&) = delete;

            inline vector2<double>
            Vectorize(const std::vector<std::string>& input, bool normalize = true);

            inline vector2<bool>
            VectorizeBool(const std::vector<std::string>& input);

            inline vector3<double> 
            VectorizeWords(const std::vector<std::string>& input,
                           bool normalize = true);
        private:
            std::vector<re> regexList;
    };
    
    ///// Inline implementations 
    inline std::vector<re> 
    Compile(const std::vector<std::string>& regexStrings, 
            const re::flag_type syntaxFlags) {
        std::vector<re> regexList;
        regexList.reserve(regexStrings.size());
        for (auto regexStr : regexStrings) {
            regexList.push_back(re(regexStr, syntaxFlags));
        }
        return regexList;
    }

    inline vector2<double>
    VectorizeStrings(const std::vector<std::string>& regexStrings, 
                     const std::vector<std::string>& input,
                     bool normalize) {
        return VectorizeList(Compile(regexStrings), input, normalize);
    }
    inline vector2<bool>
    VectorizeStringsBool(const std::vector<std::string>& regexStrings, 
                         const std::vector<std::string>& input) {
        return VectorizeListBool(Compile(regexStrings), input);
    }

    inline vector2<double>
    Vectorizer::Vectorize(const std::vector<std::string>& input, bool normalize) {
        return VectorizeList(regexList, input, normalize);
    }
    inline vector2<bool>
    Vectorizer::VectorizeBool(const std::vector<std::string>& input) {
        return VectorizeListBool(regexList, input);
    }
    inline vector3<double>
    Vectorizer::VectorizeWords(const std::vector<std::string>& input, bool normalize) {
        return ::DataPipelines::StringTransforms::RegEx::VectorizeWords(regexList, input, normalize);
    }
}

