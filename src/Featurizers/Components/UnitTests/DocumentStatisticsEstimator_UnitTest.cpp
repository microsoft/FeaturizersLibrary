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

NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyAndIndexMap TrainTermFrequencyAndIndex(std::vector<std::vector<std::string>> const &inputBatches) {
    NS::AnnotationMapsPtr                                                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::DocumentStatisticsEstimator<std::numeric_limits<size_t>::max()>
                                                                            estimator(pAllColumnAnnotations, 0);

    NS::TestHelpers::Train(estimator, inputBatches);

    NS::Featurizers::Components::DocumentStatisticsAnnotationData const &
                                                                            annotation(estimator.get_annotation_data());
    return annotation.TermFrequencyAndIndex;
}

std::uint32_t TrainDocuNum(std::vector<std::vector<std::string>> const &inputBatches) {
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
    using FrequencyAndIndexMap = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyAndIndexMap;
    using FrequencyAndIndexStruct = NS::Featurizers::Components::FrequencyAndIndexStruct;
    FrequencyAndIndexMap termFreqAndIndex(FrequencyAndIndexMap{{"key", FrequencyAndIndexStruct(1, 1)}});
    
    CHECK_THROWS_WITH(NS::Featurizers::Components::DocumentStatisticsAnnotationData(termFreqAndIndex, 0), "totalNumDocuments");
    CHECK_THROWS_WITH(NS::Featurizers::Components::DocumentStatisticsAnnotationData(FrequencyAndIndexMap(), 1), "termFrequencyAndIndex");
}

TEST_CASE("invalid_trainingpolicy") {
    using StringDecorator = NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy::StringDecorator;
    StringDecorator decoratorNull;
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decoratorNull), "decorator");
}

TEST_CASE("string_idf") {
    using FrequencyMap                         = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyMap;
    using IndexMap                             = NS::Featurizers::Components::DocumentStatisticsAnnotationData::IndexMap;
    using FrequencyAndIndexMap                 = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyAndIndexMap;

    FrequencyMap const                         termFreqLabel({{"orange",3}, {"apple", 1}, {"peach", 3}, {"grape", 2}, {"banana",1}});
    IndexMap const                             termIndexLabel({{"apple", 0}, {"banana",1}, {"grape", 2}, {"orange",3}, {"peach", 4}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const            
                                               inputBatches({{" orange  apple  apple peach  grape "},
                                                            {" grape orange     peach peach banana"},
                                                            {"orange orange peach   peach orange "}});

    FrequencyAndIndexMap const                 termFreqAndIndexAnnotation(TrainTermFrequencyAndIndex(inputBatches));
    std::uint32_t const                        docuNumsAnnotation(TrainDocuNum(inputBatches));

    CHECK(termFreqAndIndexAnnotation == termFreqAndIndexLabel);
    CHECK(docuNumsAnnotation == docuNumsLabel);
}

TEST_CASE("string_idf_single_appearance") {
    using FrequencyMap                         = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyMap;
    using IndexMap                             = NS::Featurizers::Components::DocumentStatisticsAnnotationData::IndexMap;
    using FrequencyAndIndexMap                 = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyAndIndexMap;

    FrequencyMap const                         termFreqLabel({{"orange", 1}, {"apple", 1}, {"grape", 1}});
    IndexMap const                             termIndexLabel({{"apple", 0}, {"grape", 1}, {"orange", 2}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const            
                                               inputBatches({{" apple apple  apple"},
                                                            {"grape grape  grape "},
                                                            {" orange orange  orange "}});

    FrequencyAndIndexMap const                 termFreqAndIndexAnnotation(TrainTermFrequencyAndIndex(inputBatches));
    std::uint32_t const                        docuNumsAnnotation(TrainDocuNum(inputBatches));

    CHECK(termFreqAndIndexAnnotation == termFreqAndIndexLabel);
    CHECK(docuNumsAnnotation == docuNumsLabel);
}

TEST_CASE("string_idf_full_appearance") {
    using FrequencyMap                         = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyMap;
    using IndexMap                             = NS::Featurizers::Components::DocumentStatisticsAnnotationData::IndexMap;
    using FrequencyAndIndexMap                 = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyAndIndexMap;

    FrequencyMap const                         termFreqLabel({{"orange", 3}, {"apple", 3}, {"grape", 3}});
    IndexMap const                             termIndexLabel({{"apple", 0}, {"grape", 1}, {"orange", 2}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const            
                                               inputBatches({{"apple  grape orange  "},
                                                            {"  apple grape   orange"},
                                                            {" apple grape orange  "}});

    FrequencyAndIndexMap const                 termFreqAndIndexAnnotation(TrainTermFrequencyAndIndex(inputBatches));
    std::uint32_t const                        docuNumsAnnotation(TrainDocuNum(inputBatches));

    CHECK(termFreqAndIndexAnnotation == termFreqAndIndexLabel);
    CHECK(docuNumsAnnotation == docuNumsLabel);
}
