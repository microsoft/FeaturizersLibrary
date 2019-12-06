// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../../../3rdParty/optional.h"
#include "../DocumentStatisticsEstimator.h"
#include "../../TestHelpers.h"
#include "../../../Traits.h"

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

using FrequencyMap                         = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyMap;
using IndexMap                             = NS::Featurizers::Components::DocumentStatisticsAnnotationData::IndexMap;
using FrequencyAndIndexMap                 = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyAndIndexMap;
using StringDecorator                      = NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy::StringDecorator;
using FrequencyAndIndexStruct              = NS::Featurizers::Components::FrequencyAndIndexStruct;


NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyAndIndexMap TrainTermFrequencyAndIndex(std::vector<std::vector<std::string>> const &inputBatches,
                                                                                                               StringDecorator decorator, 
                                                                                                               nonstd::optional<IndexMap> vocabulary, 
                                                                                                               nonstd::optional<std::uint32_t> maxFeatures, 
                                                                                                               std::float_t minDf, 
                                                                                                               std::float_t maxDf) {
    NS::AnnotationMapsPtr                                                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::DocumentStatisticsEstimator<std::numeric_limits<size_t>::max()>
                                                                            estimator(pAllColumnAnnotations, 0, decorator, vocabulary, maxFeatures, minDf, maxDf);

    NS::TestHelpers::Train(estimator, inputBatches);

    NS::Featurizers::Components::DocumentStatisticsAnnotationData const &
                                                                            annotation(estimator.get_annotation_data());
    return annotation.TermFrequencyAndIndex;
}

std::uint32_t TrainDocuNum(std::vector<std::vector<std::string>> const &inputBatches,
                           StringDecorator decorator, 
                           nonstd::optional<IndexMap> vocabulary, 
                           nonstd::optional<std::uint32_t> maxFeatures, 
                           std::float_t minDf, 
                           std::float_t maxDf) {
    NS::AnnotationMapsPtr                                                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::DocumentStatisticsEstimator<std::numeric_limits<size_t>::max()>
                                                                            estimator(pAllColumnAnnotations, 0, decorator, vocabulary, maxFeatures, minDf, maxDf);

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
    FrequencyAndIndexMap termFreqAndIndex(FrequencyAndIndexMap{{"key", FrequencyAndIndexStruct(1, 1)}});
    
    CHECK_THROWS_WITH(NS::Featurizers::Components::DocumentStatisticsAnnotationData(termFreqAndIndex, 0), "totalNumDocuments");
    CHECK_THROWS_WITH(NS::Featurizers::Components::DocumentStatisticsAnnotationData(FrequencyAndIndexMap(), 1), "termFrequencyAndIndex");
}

TEST_CASE("invalid_trainingpolicy") {
    //invalid paramaters
    StringDecorator decorator;
    nonstd::optional<IndexMap> vocabularyEmpty = nonstd::optional<IndexMap>(IndexMap());
    nonstd::optional<std::uint32_t> maxFeaturesInvalid = nonstd::optional<std::uint32_t>(static_cast<std::uint32_t>(0));
    
    //valid paramaters
    nonstd::optional<IndexMap> vocabulary = nonstd::optional<IndexMap>(IndexMap({{"key", 1}}));
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>(static_cast<std::uint32_t>(1));

    //the validate of decorator is temporarily muted
    //CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator), "decorator");

    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator, vocabularyEmpty, maxFeatures, 0.0f, 1.0f), "vocabulary");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator, vocabulary, maxFeaturesInvalid, 0.0f, 1.0f), "maxFeaturesLowerBound");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator, vocabulary, maxFeatures, -0.5f, 1.0f), "minDf");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator, vocabulary, maxFeatures, 0.0f, 1.5f), "maxDf");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator, vocabulary, maxFeatures, 1.0f, 0.0f), "_minDf > _maxDf");
}

TEST_CASE("string_idf") {
    FrequencyMap const                         termFreqLabel({{"orange",3}, {"apple", 1}, {"peach", 3}, {"grape", 2}, {"banana",1}});
    IndexMap const                             termIndexLabel({{"apple", 0}, {"banana",1}, {"grape", 2}, {"orange",3}, {"peach", 4}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const            
                                               inputBatches({{" orange  apple  apple peach  grape "},
                                                            {" grape orange     peach peach banana"},
                                                            {"orange orange peach   peach orange "}});
    //parameter initialization
    StringDecorator decorator;
    nonstd::optional<IndexMap> vocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;

    FrequencyAndIndexMap const                 termFreqAndIndexAnnotation(TrainTermFrequencyAndIndex(inputBatches, decorator, vocabulary, maxFeatures, minDf, maxDf));
    std::uint32_t const                        docuNumsAnnotation(TrainDocuNum(inputBatches, decorator, vocabulary, maxFeatures, minDf, maxDf));

    CHECK(termFreqAndIndexAnnotation == termFreqAndIndexLabel);
    CHECK(docuNumsAnnotation == docuNumsLabel);
}

TEST_CASE("string_idf_single_appearance") {
    FrequencyMap const                         termFreqLabel({{"orange", 1}, {"apple", 1}, {"grape", 1}});
    IndexMap const                             termIndexLabel({{"apple", 0}, {"grape", 1}, {"orange", 2}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const            
                                               inputBatches({{" apple apple  apple"},
                                                            {"grape grape  grape "},
                                                            {" orange orange  orange "}});

    //parameter initialization
    StringDecorator decorator;
    nonstd::optional<IndexMap> vocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;

    FrequencyAndIndexMap const                 termFreqAndIndexAnnotation(TrainTermFrequencyAndIndex(inputBatches, decorator, vocabulary, maxFeatures, minDf, maxDf));
    std::uint32_t const                        docuNumsAnnotation(TrainDocuNum(inputBatches, decorator, vocabulary, maxFeatures, minDf, maxDf));

    CHECK(termFreqAndIndexAnnotation == termFreqAndIndexLabel);
    CHECK(docuNumsAnnotation == docuNumsLabel);
}

TEST_CASE("string_idf_full_appearance") {
    FrequencyMap const                         termFreqLabel({{"orange", 3}, {"apple", 3}, {"grape", 3}});
    IndexMap const                             termIndexLabel({{"apple", 0}, {"grape", 1}, {"orange", 2}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const            
                                               inputBatches({{"apple  grape orange  "},
                                                            {"  apple grape   orange"},
                                                            {" apple grape orange  "}});

    //parameter initialization
    StringDecorator decorator;
    nonstd::optional<IndexMap> vocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    
    FrequencyAndIndexMap const                 termFreqAndIndexAnnotation(TrainTermFrequencyAndIndex(inputBatches, decorator, vocabulary, maxFeatures, minDf, maxDf));
    std::uint32_t const                        docuNumsAnnotation(TrainDocuNum(inputBatches, decorator, vocabulary, maxFeatures, minDf, maxDf));

    CHECK(termFreqAndIndexAnnotation == termFreqAndIndexLabel);
    CHECK(docuNumsAnnotation == docuNumsLabel);
}
