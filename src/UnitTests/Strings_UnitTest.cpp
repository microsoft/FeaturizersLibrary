// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Strings.h"

using namespace Microsoft::Featurizer;

bool isWhiteSpace(char c) {
    if (c == ' ')
        return true;
    return false;
}

void IteratorVectorGeneratorTest(std::string const & input) {
    std::vector<std::string::const_iterator> iterVec(Details::IteratorVectorGenerator(input.begin(), input.end()));
    CHECK(input == std::string(iterVec[0], iterVec[iterVec.size() - 1]));
}

void ParseNgramCharHelperTest(std::string const & input,
                              std::vector<std::string> const & label,
                              size_t ngramRangeMin,
                              size_t ngramRangeMax) {
    std::vector<std::string> output;
    Details::ParseNgramCharHelper<std::string::const_iterator>(
        input.begin(),
        input.end(),
        ngramRangeMin,
        ngramRangeMax,
        [&output] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output == label);
}

void ParseTest(std::string const & input, std::vector<std::string> const & label) {
    std::vector<std::string> output1;
    Details::Parse<std::string::const_iterator>(
        input.begin(),
        input.end(),
        isWhiteSpace,
        [&output1] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output1.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output1 == label);
    std::vector<std::string> output2;
    Parse<std::string::const_iterator>(
        input,
        isWhiteSpace,
        [&output2] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output2.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output2 == label);
}

void ParseRegexTest(std::string const & input,
                    std::vector<std::string> const & label,
                    std::string const & token = "[^\\s]+") {
    std::regex rgx(token);

    std::vector<std::string> output1;
    Details::ParseRegex<std::string::const_iterator, std::regex>(
        input.begin(),
        input.end(),
        rgx,
        [&output1] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output1.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output1 == label);
    std::vector<std::string> output2;
    ParseRegex<std::string::const_iterator, std::regex>(
        input,
        rgx,
        [&output2] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output2.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output2 == label);
}

void ParseNgramWordTest(std::string & input,
                        std::vector<std::string> const & label,
                        size_t ngramRangeMin,
                        size_t ngramRangeMax) {
    std::vector<std::string> output1;
    Details::ParseNgramWord<std::string::const_iterator>(
        input,
        isWhiteSpace,
        ngramRangeMin,
        ngramRangeMax,
        [&output1] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output1.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output1 == label);
    std::vector<std::string> output2;
    ParseNgramWord<std::string::const_iterator>(
        input,
        isWhiteSpace,
        ngramRangeMin,
        ngramRangeMax,
        [&output2] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output2.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output2 == label);
}

void ParseNgramWordCopyTest(std::string const & input,
                            std::vector<std::string> const & label,
                            size_t ngramRangeMin,
                            size_t ngramRangeMax) {
    std::vector<std::string> output;
    ParseNgramWordCopy<std::string::const_iterator>(
        input,
        isWhiteSpace,
        ngramRangeMin,
        ngramRangeMax,
        [&output] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output == label);
}

void ParseNgramCharTest(std::string & input,
                        std::vector<std::string> const & label,
                        size_t ngramRangeMin,
                        size_t ngramRangeMax) {
    std::vector<std::string> output1;
    Details::ParseNgramChar<std::string::const_iterator>(
        input,
        ngramRangeMin,
        ngramRangeMax,
        [&output1] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output1.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output1 == label);
    std::vector<std::string> output2;
    ParseNgramChar<std::string::const_iterator>(
        input,
        ngramRangeMin,
        ngramRangeMax,
        [&output2] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output2.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output2 == label);
}

void ParseNgramCharCopyTest(std::string const & input,
                            std::vector<std::string> const & label,
                            size_t ngramRangeMin,
                            size_t ngramRangeMax) {
    std::vector<std::string> output;
    ParseNgramCharCopy<std::string::const_iterator>(
        input,
        ngramRangeMin,
        ngramRangeMax,
        [&output] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output == label);
}

void ParseNgramCharwbTest(std::string & input,
                          std::vector<std::string> const & label,
                          size_t ngramRangeMin,
                          size_t ngramRangeMax) {
    std::vector<std::string> output1;
    Details::ParseNgramCharwb<std::string::const_iterator>(
        input,
        isWhiteSpace,
        ngramRangeMin,
        ngramRangeMax,
        [&output1] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output1.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output1 == label);
    std::vector<std::string> output2;
    ParseNgramCharwb<std::string::const_iterator>(
        input,
        isWhiteSpace,
        ngramRangeMin,
        ngramRangeMax,
        [&output2] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output2.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output2 == label);
}

void ParseNgramCharwbCopyTest(std::string const & input,
                              std::vector<std::string> const & label,
                              size_t ngramRangeMin,
                              size_t ngramRangeMax) {
    std::vector<std::string> output;
    ParseNgramCharwbCopy<std::string::const_iterator>(
        input,
        isWhiteSpace,
        ngramRangeMin,
        ngramRangeMax,
        [&output] (std::string::const_iterator iterBegin, std::string::const_iterator iterEnd) {
            output.emplace_back(std::string(iterBegin, iterEnd));
        }
    );
    CHECK(output == label);
}

TEST_CASE("IteratorVectorGenerator") {
    IteratorVectorGeneratorTest("this is a document");
}

TEST_CASE("ToLower") {
    std::string input("THIS IS THE FIRST DOCUMENT.");
    std::string label("this is the first document.");
    std::string output(ToLower(input));
    CHECK(output == label);
}

TEST_CASE("ToUpper") {
    std::string input("this is the first document.");
    std::string label("THIS IS THE FIRST DOCUMENT.");
    std::string output(ToUpper(input));
    CHECK(output == label);
}

TEST_CASE("TrimLeft") {
    std::string input("    this is the first document.");
    std::string label("this is the first document.");
    std::string output(TrimLeft(input, isWhiteSpace));
    CHECK(output == label);
}

TEST_CASE("TrimRight") {
    std::string input("this is the first document.        ");
    std::string label("this is the first document.");
    std::string output(TrimRight(input, isWhiteSpace));
    CHECK(output == label);
}

TEST_CASE("Trim") {
    std::string input("     this is the first document.     ");
    std::string label("this is the first document.");
    std::string output(Trim(input, isWhiteSpace));
    CHECK(output == label);
}

TEST_CASE("ReplaceAndTrimDuplicate") {
    std::string input(" ! is  this the   * first#document  ?   ");
    std::string label(" is this the first document ");
    std::string output(Details::ReplaceAndDeDuplicate<std::function<bool (char)>>(input));
    CHECK(output == label);
}

TEST_CASE("Parse") {
    ParseTest("this is a document", {"this", "is", "a", "document"});
    ParseTest("this   is a   document ", {"this", "is", "a", "document"});
    ParseTest(" this is   a document", {"this", "is", "a", "document"});
    ParseTest(" this is a document ", {"this", "is", "a", "document"});
    ParseTest(" this   is a   document  ", {"this", "is", "a", "document"});
    ParseTest("this", {"this"});
    ParseTest(" this", {"this"});
    ParseTest("this ", {"this"});
    ParseTest(" this ", {"this"});
    ParseTest("  this  ", {"this"});
    ParseTest("", {});
    ParseTest(" ", {});
    ParseTest("  ", {});
}

TEST_CASE("ParseRegex") {
    ParseRegexTest("this is a document", {"this", "is", "a", "document"});
    ParseRegexTest("this   is a   document ", {"this", "is", "a", "document"});
    ParseRegexTest(" this is   a document", {"this", "is", "a", "document"});
    ParseRegexTest(" this is a document ", {"this", "is", "a", "document"});
    ParseRegexTest(" this   is a   document  ", {"this", "is", "a", "document"});
}

TEST_CASE("ParseNgramWord") {
    CHECK_THROWS_WITH(ParseNgramWordCopyTest(" ", {}, 1, 1), "wordIterPairVector.size() == 0");
    CHECK_THROWS_WITH(ParseNgramWordCopyTest("hi", {}, 0, 3), "ngramRangeMin and ngramRangeMax not valid");
    ParseNgramWordCopyTest("? this$is a   document  &", {"this", "is", "a", "document"}, 1, 1);
    ParseNgramWordCopyTest("? this$is a   document  &", {"this is a", "is a document"}, 3, 3);
    ParseNgramWordCopyTest("? this$is a   document  &", {"this is", "is a", "a document"}, 2, 2);
    ParseNgramWordCopyTest("? this$is a   document  &", {"this is a document"}, 4, 4);
    ParseNgramWordCopyTest("? this$is a   document  &", {"this", "is", "a", "document", "this is", "is a", "a document"}, 1, 2);
    ParseNgramWordCopyTest("? this$is a   document  &", {"this is", "is a", "a document", "this is a", "is a document"}, 2, 3);
    ParseNgramWordCopyTest("? this$is a   document  &", {"this is a", "is a document", "this is a document"}, 3, 4);
    ParseNgramWordCopyTest("? this$is a   document  &", {"this", "is", "a", "document", "this is", "is a", "a document", "this is a", "is a document"}, 1, 3);
    ParseNgramWordCopyTest("? this$is a   document  &", {"this is", "is a", "a document", "this is a", "is a document", "this is a document"}, 2, 4);
    ParseNgramWordCopyTest("? this$is a   document  &", {"this", "is", "a", "document", "this is", "is a", "a document", "this is a", "is a document", "this is a document"}, 1, 4);
    std::string input(" bi-grams    are cool! ");
    std::string emptyInput(" ");
    CHECK_THROWS_WITH(ParseNgramWordTest(emptyInput, {}, 1, 1), "wordIterPairVector.size() == 0");
    CHECK_THROWS_WITH(ParseNgramWordTest(input, {}, 0, 8), "ngramRangeMin and ngramRangeMax not valid");
    ParseNgramWordTest(input, {"bi", "grams", "are", "cool", "bi grams", "grams are", "are cool"}, 1, 2);
    ParseNgramWordTest(input, {"bi grams", "grams are", "are cool", "bi grams are", "grams are cool"}, 2, 3);
}

TEST_CASE("ParseNgramCharHelper") {
    ParseNgramCharHelperTest(" jumpy ", {" jump", "jumpy", "umpy "}, 5, 5);
}

TEST_CASE("ParseNgramChar") {
    CHECK_THROWS_WITH(ParseNgramCharCopyTest("hi", {}, 0, 3), "ngramRangeMin and ngramRangeMax not valid");
    CHECK_THROWS_WITH(ParseNgramCharCopyTest("jumpy   ?? fox", {}, 10, 10), "ngramRangeMin and ngramRangeMax not valid");
    ParseNgramCharCopyTest("jumpy   ?? fox", {"j", "u", "m", "p", "y", " ", "f", "o", "x"}, 1, 1);
    ParseNgramCharCopyTest("jumpy   ?? fox", {"ju", "um", "mp", "py", "y ", " f", "fo", "ox"}, 2, 2);
    ParseNgramCharCopyTest("jumpy   ?? fox", {"jum", "ump", "mpy", "py ", "y f", " fo", "fox"}, 3, 3);
    ParseNgramCharCopyTest("jumpy   ?? fox", {"jump", "umpy", "mpy ", "py f", "y fo", " fox"}, 4, 4);
    ParseNgramCharCopyTest("jumpy   ?? fox", {"jumpy", "umpy ", "mpy f", "py fo", "y fox"}, 5, 5);
    ParseNgramCharCopyTest("jumpy   ?? fox", {"jumpy ", "umpy f", "mpy fo", "py fox"}, 6, 6);
    ParseNgramCharCopyTest("jumpy   ?? fox", {"jumpy f", "umpy fo", "mpy fox"}, 7, 7);
    ParseNgramCharCopyTest("jumpy   ?? fox", {"jumpy fo", "umpy fox"}, 8, 8);
    ParseNgramCharCopyTest("jumpy   ?? fox", {"jumpy fox"}, 9, 9);
    std::string input("jumpy   ?? fox");
    std::string emptyInput(" ");
    CHECK_THROWS_WITH(ParseNgramCharTest(emptyInput, {}, 0, 3), "ngramRangeMin and ngramRangeMax not valid");
    CHECK_THROWS_WITH(ParseNgramCharTest(input, {}, 10, 10), "ngramRangeMin and ngramRangeMax not valid");
    ParseNgramCharTest(input, {"jumpy fox"}, 9, 9);
}

TEST_CASE("ParseNgramCharwb") {
    CHECK_THROWS_WITH(ParseNgramCharwbCopyTest(" ", {}, 1, 1), "wordIterPairVector.size() == 0");
    CHECK_THROWS_WITH(ParseNgramCharwbCopyTest("hi", {}, 0, 3), "ngramRangeMin and ngramRangeMax not valid");
    ParseNgramCharwbCopyTest("? jumpy ^fox )", {" ", "j", "u", "m", "p", "y", " ", " ", "f", "o", "x", " "}, 1, 1);
    ParseNgramCharwbCopyTest("? jumpy ^fox )", {" j", "ju", "um", "mp", "py", "y ", " f", "fo", "ox", "x "}, 2, 2);
    ParseNgramCharwbCopyTest("? jumpy ^fox )", {" ju", "jum", "ump", "mpy", "py ", " fo", "fox", "ox "}, 3, 3);
    ParseNgramCharwbCopyTest("? jumpy ^fox )", {" jum", "jump", "umpy", "mpy ", " fox", "fox "}, 4, 4);
    ParseNgramCharwbCopyTest("? jumpy ^fox )", {" jump", "jumpy", "umpy ", " fox "}, 5, 5);
    ParseNgramCharwbCopyTest("? jumpy ^fox )", {" jumpy", "jumpy "}, 6, 6);
    ParseNgramCharwbCopyTest("? jumpy ^fox )", {" jumpy "}, 7, 7);
    ParseNgramCharwbCopyTest("? jumpy ^fox )", {}, 8, 8);
    std::string input("? jumpy ^fox )");
    std::string emptyInput(" ");
    CHECK_THROWS_WITH(ParseNgramCharwbTest(emptyInput, {}, 1, 1), "wordIterPairVector.size() == 0");
    CHECK_THROWS_WITH(ParseNgramCharwbTest(input, {}, 0, 8), "ngramRangeMin and ngramRangeMax not valid");
    ParseNgramCharwbTest(input, {}, 8, 8);
}


