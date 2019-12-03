// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../../TestHelpers.h"
#include "../DocumentStatisticsEstimator.h"

namespace NS = Microsoft::Featurizer;

// TODO: Test for DocumentStatisticsTrainingOnlyPolicy ctor - empty decorator

void TestString (std::string const & input, std::vector<std::string> const & label) {
    std::vector<std::string> predict;
    NS::Featurizers::Components::split_temp(
        input,
        [&predict] (std::string::const_iterator & iter_start, std::string::const_iterator & iter_end) {
            std::string word = std::string(iter_start, iter_end);
            predict.emplace_back(word);
        }
    );
    CHECK(predict == label);
}

NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyMap Test(std::vector<std::vector<std::string>> const &inputBatches) {
    NS::AnnotationMapsPtr                                                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::DocumentStatisticsEstimator<std::numeric_limits<size_t>::max()>
                                                                            estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, inputBatches);

    NS::Featurizers::Components::DocumentStatisticsAnnotationData const &
                                                                            annotation(estimator.get_annotation_data());
    return annotation.TermFrequency;
}

NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyMap TestIndexMap(std::vector<std::vector<std::string>> const &inputBatches) {
    NS::AnnotationMapsPtr                                                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::DocumentStatisticsEstimator<std::numeric_limits<size_t>::max()>
                                                                            estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, inputBatches);

    NS::Featurizers::Components::DocumentStatisticsAnnotationData const &
                                                                            annotation(estimator.get_annotation_data());
    return annotation.TermIndex;
}

std::uint32_t TestNum(std::vector<std::vector<std::string>> const &inputBatches) {
    NS::AnnotationMapsPtr                                                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::DocumentStatisticsEstimator<std::numeric_limits<size_t>::max()>
                                                                            estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, inputBatches);

    NS::Featurizers::Components::DocumentStatisticsAnnotationData const &
                                                                            annotation(estimator.get_annotation_data());
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

TEST_CASE("invalid_annotation") {
    using FrequencyMap = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyMap;
    using IndexMap = NS::Featurizers::Components::DocumentStatisticsAnnotationData::IndexMap;
    FrequencyMap termFreq(FrequencyMap{{"key", 1}});
    IndexMap termIndex(IndexMap{{"key", 1}});
    CHECK_THROWS_WITH(NS::Featurizers::Components::DocumentStatisticsAnnotationData(FrequencyMap(),termIndex, 1), "termFreq");
    CHECK_THROWS_WITH(NS::Featurizers::Components::DocumentStatisticsAnnotationData(termFreq, termIndex, 0), "totalNumDocuments");
    CHECK_THROWS_WITH(NS::Featurizers::Components::DocumentStatisticsAnnotationData(termFreq, IndexMap(), 1), "termIndex");
}

TEST_CASE("invalid_trainingpolicy") {
    using StringDecorator = NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy::StringDecorator;
    StringDecorator decoratorNull;
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decoratorNull), "decorator");
}

TEST_CASE("string_idf") {
    using FrequencyMap                         = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyMap;

    FrequencyMap const                         label({{"orange",3}, {"apple", 1}, {"peach", 3}, {"grape", 2}, {"banana",1}});
    std::vector<std::vector<std::string>> const            inputBatches({{" orange  apple  apple peach  grape "},
                                                                        {" grape orange     peach peach banana"},
                                                                        {"orange orange peach   peach orange "}});

    FrequencyMap const                         predict(Test(inputBatches));
    CHECK(predict == label);
}

TEST_CASE("string_idf_single_appearance") {
    using FrequencyMap                         = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyMap;

    FrequencyMap const                         label({{"orange", 1}, {"apple", 1}, {"grape", 1}});
    std::vector<std::vector<std::string>> const            inputBatches({{" apple apple  apple"},
                                                                        {"grape grape  grape "},
                                                                        {" orange orange  orange "}});

    FrequencyMap const                         predict(Test(inputBatches));
    CHECK(predict == label);
}

TEST_CASE("string_idf_full_appearance") {
    using FrequencyMap                         = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyMap;

    FrequencyMap const                         label({{"orange", 3}, {"apple", 3}, {"grape", 3}});
    std::vector<std::vector<std::string>> const            inputBatches({{"apple  grape orange  "},
                                                                         {"  apple grape   orange"},
                                                                         {" apple grape orange  "}});

    FrequencyMap const                         predict(Test(inputBatches));
    CHECK(predict == label);
}

TEST_CASE("string_num") {
    using FrequencyMap                         = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyMap;

    FrequencyMap const                         label({{"orange",3}, {"apple", 1}, {"peach", 3}, {"grape", 2}, {"banana",1}});
    std::vector<std::vector<std::string>> const            inputBatches({{"orange apple apple peach grape"},
                                                                        {"grape orange peach peach banana"},
                                                                        {"orange orange peach peach orange"}});

    std::uint32_t const                        numOfDocuments(TestNum(inputBatches));
    CHECK(numOfDocuments == 3);
}

TEST_CASE("string_indexmap") {
    using IndexMap                         = NS::Featurizers::Components::DocumentStatisticsAnnotationData::IndexMap;

    IndexMap const                         label({{"orange", 2}, {"apple", 0}, {"grape", 1}});
    std::vector<std::vector<std::string>> const            inputBatches({{" apple apple  apple"},
                                                                        {"grape grape  grape "},
                                                                        {" orange orange  orange "}});

    IndexMap const                         predict(TestIndexMap(inputBatches));
    CHECK(predict == label);
}
