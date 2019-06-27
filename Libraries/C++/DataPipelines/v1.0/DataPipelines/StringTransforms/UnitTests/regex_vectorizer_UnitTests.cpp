// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include "../regex_vectorizer.cpp"

using namespace DataPipelines::StringTransforms;

struct TestData {
    std::vector<std::string> dataIn;
    std::vector<std::string> regexIn;
    std::vector<std::vector<double>> vectorOut;
};

inline std::vector<std::vector<bool>> 
doubleArrayToBool(const std::vector<std::vector<double>>& inData) {
    std::vector<std::vector<bool>> out;
    for (auto vec : inData) {
        std::vector<bool> v;
        std::transform(vec.begin(), vec.end(), std::back_insert_iterator(v), 
                        [](double d) -> bool { return d != 0.0; });
        out.push_back(v);
    }
    return out;
}

inline std::vector<std::vector<double>>
normalizeDoubleArray(const std::vector<std::vector<double>>& inData)
{
    std::vector<std::vector<double>> out;
    for (auto vec : inData) {
        std::vector<double> v;
        if (vec.size()) {
            std::transform(vec.begin(), vec.end(), std::back_insert_iterator(v), 
                            [&vec](double d) -> double { return d / static_cast<double>(vec.size()); });
        }
        out.push_back(v);
    }
    return out;
}

inline RegEx::vector3<double> 
normalizeDoubleArray(const RegEx::vector3<double>& inData)
{
    RegEx::vector3<double> out;
    for (auto vec : inData) {
        out.push_back(normalizeDoubleArray(vec));
    }
    return out;
}

inline TestData TestData1()
{
    TestData td;
    // The test data currently is just a copy of what is in regex_vectorizer.py..
    td.dataIn = {
        "@adoran2 Good points made by article - I am home, in case anyone is wondering  ", 
        " Wow a Phil Collins song I've not heard.  Nice! ", 
        " a_dubstar Nahhhhhh i'm even worst ", 
        " @abtnova can u please tell me if the jonas brothers competition has finished im a finalist and apparently it has  ill b devo if its not me ", 
        " @afiaa_1212 wow wow wow who just made a new account yaaa?? Hahahaha hello fellow twitter  tweet tweet tweet "
    };
    td.regexIn = {
        "[0-9]{4,10}",
        "[A-Z]{2,6}",
        "([A-Z])\\1{4,6}",
        "(.)\\1{3,6}",
        "[!@#$%&\\*!]",
        "@[A-Za-z0-9]+",
        "(\\w+\\s)\\1{2,4}",
        "[!@#\\*]{3,5}",
        "[A-Z#!\\*]{4,6}"
    };
    td.vectorOut = {
        { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 },
        { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
        { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 },
        { 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0 }
    };

    return td;
}


TEST_CASE("Vectorizer", "[strings][regex][vectorizer]") {
    TestData td = TestData1();

    std::vector<std::vector<bool>> boolVectorization = doubleArrayToBool(td.vectorOut);
    std::vector<std::vector<double>> normVectorization = normalizeDoubleArray(td.vectorOut);

    REQUIRE(boolVectorization.size() == td.dataIn.size());
    REQUIRE(boolVectorization[0].size() == td.regexIn.size());

    RegEx::Vectorizer vectorizer(td.regexIn);

    SECTION("Vectorize") {
        SECTION("Vectorizer Object") {
            // "normalized"
            auto v1 = vectorizer.Vectorize(td.dataIn, true);
            CHECK(v1 == normVectorization);

            // straight
            auto v2 = vectorizer.Vectorize(td.dataIn, false);
            CHECK(v2 == td.vectorOut);

            // boolean 
            auto v3 = vectorizer.VectorizeBool(td.dataIn);
            CHECK(v3 == boolVectorization);
        }

        SECTION("Persistent regex list") {
            auto regexes = RegEx::Compile(td.regexIn);
            CHECK(regexes.size() == td.regexIn.size());

            auto v1 = RegEx::VectorizeList(regexes, td.dataIn);
            CHECK(v1 == normVectorization);

            auto v2 = RegEx::VectorizeList(regexes, td.dataIn, false);
            CHECK(v2 == td.vectorOut);

            auto v3 = RegEx::VectorizeListBool(regexes, td.dataIn);
            CHECK(v3 == boolVectorization);
        }

        SECTION("Vectorize straight from strings, no persistence") {
            auto v1 = RegEx::VectorizeStrings(td.regexIn, td.dataIn);
            CHECK(v1 == normVectorization);

            auto v2 = RegEx::VectorizeStrings(td.regexIn, td.dataIn, false);
            CHECK(v2 == td.vectorOut);

            auto v3 = RegEx::VectorizeStringsBool(td.regexIn, td.dataIn);
            CHECK(v3 == boolVectorization);
        }
    }
}

TEST_CASE("Empty Lists", "[strings][regex][vectorizer][edge case]") {
    TestData td;

    td.dataIn = {
        "@adoran2 Good points made by article - I am home, in case anyone is wondering  ", 
        " Wow a Phil Collins song I've not heard.  Nice! "
    };
    td.regexIn = {
        "[0-9]{4,10}",
        "[A-Z]{2,6}",
        "([A-Z])\\1{4,6}"
    };

    std::vector<std::string> emptyInList = {};
    std::vector<std::vector<double>> emptyStringOutList = {}; // empty outer
    std::vector<std::vector<double>> emptyRegexOutList = {{},{}};   // 2 outer, empty inner

    SECTION("Empty input") {
            auto v1 = RegEx::VectorizeStrings(td.regexIn, emptyInList, false);
            CHECK(v1 == emptyStringOutList);
            auto v2 = RegEx::VectorizeStrings(td.regexIn, emptyInList, true);
            CHECK(v2 == emptyStringOutList);
    }
    SECTION("Empty regex") {
            auto v1 = RegEx::VectorizeStrings(emptyInList, td.dataIn, false);
            CHECK(v1 == emptyRegexOutList);
            auto v2 = RegEx::VectorizeStrings(emptyInList, td.dataIn, true);
            CHECK(v2 == emptyRegexOutList);
    }
    SECTION("Empty regex and input") {
        auto v1 = RegEx::VectorizeStrings(emptyInList, emptyInList, false);
        CHECK(v1 == emptyStringOutList);
        auto v2 = RegEx::VectorizeStrings(emptyInList, emptyInList, true);
        CHECK(v2 == emptyStringOutList);
    }
}

TEST_CASE("Invalid Regex", "[strings][regex][vectorizer][error]") {
    TestData td;
    td.dataIn = {
        "1234 5678", 
        " blah blah"
    };
    td.regexIn = {
            "[0-9]{]",
            "[[[]]]]{}" 
    };

    SECTION("Vectorizer Object") {
        CHECK_THROWS_AS(RegEx::Vectorizer(td.regexIn), std::regex_error);
    }
    SECTION("Persistent list")  {

        CHECK_THROWS_AS(RegEx::Compile(td.regexIn), std::regex_error);
    }
    SECTION("From string")  {
        CHECK_THROWS_AS(RegEx::VectorizeStrings(td.regexIn, td.dataIn), 
                        std::regex_error);
    }
}

TEST_CASE("Empty Strings", "[strings][regex][vectorizer][edge case]") {
    TestData td;

    td.dataIn = {
        "1234 9876 ", 
        "ABCCD FFFFF"
    };
    td.regexIn = {
        "[0-9]{4,10}",
        "[A-Z]{2,6}",
        "([A-Z])\\1{4,6}"
    };
    td.vectorOut = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 1.0 } };
    std::vector<double> emptyStrOut = { { 0.0, 0.0, 0.0 } };

    std::vector<std::string> regexStrEmpty(3);
    regexStrEmpty[0] = "";
    regexStrEmpty[1] = td.regexIn[1];
    regexStrEmpty[2] = td.regexIn[2];

    std::vector<std::string> inputEmpty(3);
        inputEmpty[0] = td.dataIn[0];
        inputEmpty[1] = "";
        inputEmpty[2] = td.dataIn[1];

    SECTION("Empty input string") {
        auto v1 = RegEx::VectorizeStrings(td.regexIn, inputEmpty, false);
        CHECK(v1[0] == td.vectorOut[0]);
        CHECK(v1[1] == emptyStrOut);
        CHECK(v1[2] == td.vectorOut[1]);
        
    }
    SECTION("Empty regex string") {
        auto v1 = RegEx::VectorizeStrings(regexStrEmpty, td.dataIn, false);

        CHECK(v1[0][0] == 0.0);
        CHECK(v1[1][0] == 0.0);
        CHECK(v1[1][1] == 1.0);
    }
    SECTION("Empty string in regex and input") {
        auto v1 = RegEx::VectorizeStrings(regexStrEmpty, inputEmpty, false);
        CHECK(v1[0][0] == 0.0);
        CHECK(v1[1][0] == 0.0);
        CHECK(v1[2][0] == 0.0);
        CHECK(v1[1][1] == 0.0);
        CHECK(v1[2][2] == 1.0);
    }
}

TEST_CASE("Vectorize Words", "[strings][regex][vectorizer]") {
     TestData td;

    td.dataIn = {
        "@adoran2 Good points made by article - I am home, in ", 
        " @afiaa_1212 bla blah ",
        "1234 9876 ", 
        "ABCCD FFFFF"
    };
    td.regexIn = {
        "[0-9]{4,10}",
        "[A-Z]{2,6}",
        "([A-Z])\\1{4,6}"
    };

    RegEx::vector3<double> vectorOut = {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
            {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{1, 0, 0}, {1, 0, 0}},
        {{0, 1, 0}, {0, 1, 1}}
    };

    RegEx::vector3<double> normVectorization = normalizeDoubleArray(vectorOut);

    RegEx::Vectorizer vectorizer(td.regexIn);

    SECTION("Vectorize") {
        SECTION("Vectorizer Object") {
            // "normalized"
            auto v1 = vectorizer.VectorizeWords(td.dataIn, true);
            CHECK(v1 == normVectorization);

            // straight
            auto v2 = vectorizer.VectorizeWords(td.dataIn, false);
            CHECK(v2 == vectorOut);
        }

        SECTION("Persistent regex list") {
            auto regexes = RegEx::Compile(td.regexIn);
            CHECK(regexes.size() == td.regexIn.size());

            auto v1 = RegEx::VectorizeWords(regexes, td.dataIn);
            CHECK(v1 == normVectorization);

            auto v2 = RegEx::VectorizeWords(regexes, td.dataIn, false);
            CHECK(v2 == vectorOut);
        }
    }
}
