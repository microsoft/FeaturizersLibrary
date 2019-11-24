// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../3rdParty/optional.h"
#include "../TestHelpers.h"
#include "../InverseDocumentFrequencyEstimator.h"

namespace NS = Microsoft::Featurizer;

void TestString (std::string const & input, std::vector<std::string> const & label) {
    std::vector<std::string> predict;
    NS::Featurizers::split_temp( 
        input, 
        [&predict] (std::string::const_iterator & iter_start, std::string::const_iterator & iter_end) {
            std::string word = std::string(iter_start, iter_end);
            predict.emplace_back(word);
        }
    );
    CHECK(predict == label);
}

NS::Featurizers::InverseDocumentFrequencyAnnotationData::InverseDocumentFrequency Test(std::vector<std::vector<std::string>> const &inputBatches) {
    NS::AnnotationMapsPtr                                                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::InverseDocumentFrequencyEstimator<std::numeric_limits<size_t>::max()>        
                                                                            estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, inputBatches);

    NS::Featurizers::InverseDocumentFrequencyAnnotationData     const &     annotation(estimator.get_annotation_data());

    return annotation.TermFrequency;
}

std::uint32_t TestNum(std::vector<std::vector<std::string>> const &inputBatches) {
    NS::AnnotationMapsPtr                                                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::InverseDocumentFrequencyEstimator<std::numeric_limits<size_t>::max()>            
                                                                            estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, inputBatches);

    NS::Featurizers::InverseDocumentFrequencyAnnotationData const &         annotation(estimator.get_annotation_data());

    return annotation.TotalNumDocuments;
}

void TestString_Batch() {
    TestString("this is a document", {"this", "is", "a", "document"});
    TestString("this   is a   document ", {"this", "is", "a", "document"});
    TestString(" this is   a document", {"this", "is", "a", "document"});
    TestString(" this is a document ", {"this", "is", "a", "document"});
    TestString(" this   is a   document  ", {"this", "is", "a", "document"});
    TestString("this", {"this"});
    TestString(" this", {"this"});
    TestString("this ", {"this"});
    TestString(" this ", {"this"});
    TestString("  this  ", {"this"});
    TestString("", {});
    TestString(" ", {});
    TestString("  ", {});
}

TEST_CASE("string_split") {
    TestString_Batch();
}

TEST_CASE("string_idf") {
    using InverseDocumentFrequency                         = NS::Featurizers::InverseDocumentFrequencyAnnotationData::InverseDocumentFrequency;

    InverseDocumentFrequency const                         label({{"orange",3}, {"apple", 1}, {"peach", 3}, {"grape", 2}, {"banana",1}});
    std::vector<std::vector<std::string>> const            inputBatches({{" orange  apple  apple peach  grape "},
                                                                        {" grape orange     peach peach banana"},
                                                                        {"orange orange peach   peach orange "}});

    InverseDocumentFrequency const                         predict(Test(inputBatches));
    CHECK(predict == label);
}

TEST_CASE("string_idf_single_appearance") {
    using InverseDocumentFrequency                         = NS::Featurizers::InverseDocumentFrequencyAnnotationData::InverseDocumentFrequency;

    InverseDocumentFrequency const                         label({{"orange", 1}, {"apple", 1}, {"grape", 1}});
    std::vector<std::vector<std::string>> const            inputBatches({{" apple apple  apple"},
                                                                        {"grape grape  grape "},
                                                                        {" orange orange  orange "}});

    InverseDocumentFrequency const                         predict(Test(inputBatches));
    CHECK(predict == label);
}

TEST_CASE("string_idf_full_appearance") {
    using InverseDocumentFrequency                         = NS::Featurizers::InverseDocumentFrequencyAnnotationData::InverseDocumentFrequency;

    InverseDocumentFrequency const                         label({{"orange", 3}, {"apple", 3}, {"grape", 3}});
    std::vector<std::vector<std::string>> const            inputBatches({{"apple  grape orange  "},
                                                                         {"  apple grape   orange"},
                                                                         {" apple grape orange  "}});

    InverseDocumentFrequency const                         predict(Test(inputBatches));
    CHECK(predict == label);
}

TEST_CASE("string_num") {
    using InverseDocumentFrequency                         = NS::Featurizers::InverseDocumentFrequencyAnnotationData::InverseDocumentFrequency;

    InverseDocumentFrequency const                         label({{"orange",3}, {"apple", 1}, {"peach", 3}, {"grape", 2}, {"banana",1}});
    std::vector<std::vector<std::string>> const            inputBatches({{"orange apple apple peach grape"},
                                                                        {"grape orange peach peach banana"},
                                                                        {"orange orange peach peach orange"}});

    std::uint32_t const                                    numOfDocuments(TestNum(inputBatches));
    CHECK(numOfDocuments == 3);
}
