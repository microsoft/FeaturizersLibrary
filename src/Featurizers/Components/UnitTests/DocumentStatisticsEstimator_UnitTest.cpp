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

using IndexMap                             = NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy::IndexMap;
using FrequencyMap                         = IndexMap;
using FrequencyAndIndexMap                 = NS::Featurizers::Components::DocumentStatisticsAnnotationData::FrequencyAndIndexMap;
using StringDecorator                      = NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy::StringDecorator;
using FrequencyAndIndex                    = NS::Featurizers::Components::FrequencyAndIndex;
using AnalyzerMethod                       = NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy::AnalyzerMethod;



void DSRTestWrapper(std::vector<std::vector<std::string>> const &inputBatches,
                                FrequencyAndIndexMap const &label,
                                std::uint32_t docuNumsLabel,
                                StringDecorator decorator,
                                AnalyzerMethod analyzer,
                                std::string regexToken,
                                nonstd::optional<IndexMap> existingVocabulary,
                                nonstd::optional<std::uint32_t> maxFeatures,
                                std::float_t minDf,
                                std::float_t maxDf,
                                std::uint32_t ngramRangeMin,
                                std::uint32_t ngramRangeMax) {
    NS::AnnotationMapsPtr                                                   pAllColumnAnnotations(NS::CreateTestAnnotationMapsPtr(1));
    NS::Featurizers::Components::DocumentStatisticsEstimator<std::numeric_limits<size_t>::max()>
                                                                            estimator(pAllColumnAnnotations,
                                                                                      0,
                                                                                      decorator,
                                                                                      analyzer,
                                                                                      regexToken,
                                                                                      existingVocabulary,
                                                                                      maxFeatures,
                                                                                      minDf,
                                                                                      maxDf,
                                                                                      ngramRangeMin,
                                                                                      ngramRangeMax);

    NS::TestHelpers::Train(estimator, inputBatches);

    NS::Featurizers::Components::DocumentStatisticsAnnotationData const &
                                                                            annotation(estimator.get_annotation_data());
    CHECK(annotation.TermFrequencyAndIndex == label);
    CHECK(annotation.TotalNumDocuments == docuNumsLabel);
}

TEST_CASE("invalid_annotation") {
    FrequencyAndIndexMap termFreqAndIndex;
    termFreqAndIndex.emplace("key", FrequencyAndIndex(1, 1));

    CHECK_THROWS_WITH(NS::Featurizers::Components::DocumentStatisticsAnnotationData(std::move(termFreqAndIndex), 0), "totalNumDocuments");
    CHECK_THROWS_WITH(NS::Featurizers::Components::DocumentStatisticsAnnotationData(FrequencyAndIndexMap(), 1), "termFrequencyAndIndex");
}

TEST_CASE("invalid_trainingpolicy") {
    //invalid paramaters
    nonstd::optional<IndexMap> existingVocabularyEmpty = nonstd::optional<IndexMap>(IndexMap());
    nonstd::optional<std::uint32_t> maxFeaturesInvalid = nonstd::optional<std::uint32_t>(static_cast<std::uint32_t>(0));

    //valid paramaters
    StringDecorator decorator;
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>(IndexMap({{"key", 1}}));
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>(static_cast<std::uint32_t>(1));

    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator, analyzer, regexToken, existingVocabularyEmpty, maxFeatures, 0.0f, 1.0f, 1, 1), "existingVocabulary");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator, analyzer, regexToken, existingVocabulary, maxFeaturesInvalid, 0.0f, 1.0f, 1, 1), "topKTermsLowerBound");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator, analyzer, regexToken, existingVocabulary, maxFeatures, -0.5f, 1.0f, 1, 1), "minDf");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator, analyzer, regexToken, existingVocabulary, maxFeatures, 0.0f, 1.5f, 1, 1), "maxDf");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator, analyzer, regexToken, existingVocabulary, maxFeatures, 1.0f, 0.0f, 1, 1), "_minDf > _maxDf");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator, analyzer, regexToken, existingVocabulary, maxFeatures, 0.0f, 1.0f, 0, 1), "ngramRangeMin");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator, analyzer, regexToken, existingVocabulary, maxFeatures, 0.0f, 1.0f, 1, 0), "ngramRangeMax");
    CHECK_THROWS_WITH(NS::Featurizers::Components::Details::DocumentStatisticsTrainingOnlyPolicy(decorator, analyzer, regexToken, existingVocabulary, maxFeatures, 0.0f, 1.0f, 2, 1), "_ngramRangeMin > _ngramRangeMax");
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
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    std::uint32_t ngramRangeMin = 1;
    std::uint32_t ngramRangeMax = 1;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
}

TEST_CASE("string_idf_custom_decorator") {
    FrequencyMap const                         termFreqLabel({{"orange",3}, {"apple", 1}, {"peach", 3}, {"grape", 2}, {"banana",1}});
    IndexMap const                             termIndexLabel({{"apple", 0}, {"banana",1}, {"grape", 2}, {"orange",3}, {"peach", 4}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const
                                               inputBatches({{" ORANGE  APPLE  apple peach  grape "},
                                                            {" grape orange     peach PEACH BANANA"},
                                                            {"orange ORANGE peach   peach orange "}});
    //parameter initialization
    StringDecorator decorator = Microsoft::Featurizer::Strings::ToLower;
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    std::uint32_t ngramRangeMin = 1;
    std::uint32_t ngramRangeMax = 1;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
}

TEST_CASE("string_idf_custom_regex") {
    FrequencyMap const                         termFreqLabel({{"orange",3}, {"apple", 1}, {"peach", 3}, {"grape", 2}, {"banana",1}});
    IndexMap const                             termIndexLabel({{"apple", 0}, {"banana",1}, {"grape", 2}, {"orange",3}, {"peach", 4}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const
                                               inputBatches({{" ORANGE  APPLE  apple peach  grape "},
                                                            {" grape orange     peach PEACH BANANA"},
                                                            {"orange ORANGE peach   peach orange "}});
    //parameter initialization
    StringDecorator decorator = Microsoft::Featurizer::Strings::ToLower;
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "[^\\s]+";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    std::uint32_t ngramRangeMin = 1;
    std::uint32_t ngramRangeMax = 1;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
}

// //problematic test(dangling iterators)
// TEST_CASE("string_idf_ngramword_no_decorator") {
//     FrequencyMap const                         termFreqLabel({{"jumpy", 1}, {"fox", 1}, {"jumpy fox", 1}});
//     IndexMap const                             termIndexLabel({{"fox", 0}, {"jumpy fox", 2}, {"jumpy", 1}});
//     FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
//     std::uint32_t const                        docuNumsLabel(1);

//     std::vector<std::vector<std::string>> const
//                                                inputBatches({{"jumpy fox"}});

//     //parameter initialization
//     //StringDecorator decorator = Microsoft::Featurizer::Strings::ToLower;
//     StringDecorator decorator;
//     AnalyzerMethod analyzer = AnalyzerMethod::Word;
//     std::string regexToken = "";
//     nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>();
//     nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
//     std::float_t minDf = 0.0f;
//     std::float_t maxDf = 1.0f;
//     std::uint32_t ngramRangeMin = 1;
//     std::uint32_t ngramRangeMax = 2;

//     FrequencyAndIndexMap const                 termFreqAndIndexAnnotation(TrainTermFrequencyAndIndex(inputBatches, decorator, analyzer, regexToken, existingVocabulary, maxFeatures, minDf, maxDf, ngramRangeMin, ngramRangeMax));
//     std::uint32_t const                        docuNumsAnnotation(TrainDocuNum(inputBatches, decorator, analyzer, regexToken, existingVocabulary, maxFeatures, minDf, maxDf, ngramRangeMin, ngramRangeMax));

//     CHECK(termFreqAndIndexAnnotation == termFreqAndIndexLabel);
//     CHECK(docuNumsAnnotation == docuNumsLabel);
// }

TEST_CASE("string_idf_ngramword") {
    FrequencyMap const                         termFreqLabel({{"jumpy", 1}, {"fox", 1}, {"jumpy fox", 1}});
    IndexMap const                             termIndexLabel({{"fox", 0}, {"jumpy fox", 2}, {"jumpy", 1}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(1);

    std::vector<std::vector<std::string>> const
                                               inputBatches({{"jumpy fox"}});

    //parameter initialization
    StringDecorator decorator = Microsoft::Featurizer::Strings::ToLower;
    //StringDecorator decorator;
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    std::uint32_t ngramRangeMin = 1;
    std::uint32_t ngramRangeMax = 2;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
}

TEST_CASE("string_idf_ngramchar") {
    FrequencyMap const                         termFreqLabel({{"jumpy f", 1}, {"mpy fox", 1}, {"umpy fo", 1}});
    IndexMap const                             termIndexLabel({{"jumpy f", 0}, {"mpy fox", 1}, {"umpy fo", 2}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(1);

    std::vector<std::vector<std::string>> const
                                               inputBatches({{"jumpy fox"}});

    //parameter initialization
    StringDecorator decorator = Microsoft::Featurizer::Strings::ToLower;
    //StringDecorator decorator;
    AnalyzerMethod analyzer = AnalyzerMethod::Char;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    std::uint32_t ngramRangeMin = 7;
    std::uint32_t ngramRangeMax = 7;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
}

TEST_CASE("string_idf_ngramcharwb") {
    FrequencyMap const                         termFreqLabel({{" jump", 1}, {"jumpy", 1}, {"umpy ", 1}, {" fox ", 1}});
    IndexMap const                             termIndexLabel({{" jump", 1}, {"jumpy", 2}, {"umpy ", 3}, {" fox ", 0}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(1);

    std::vector<std::vector<std::string>> const
                                               inputBatches({{"jumpy fox"}});

    //parameter initialization
    StringDecorator decorator = Microsoft::Featurizer::Strings::ToLower;
    //StringDecorator decorator;
    AnalyzerMethod analyzer = AnalyzerMethod::Charwb;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    std::uint32_t ngramRangeMin = 5;
    std::uint32_t ngramRangeMax = 5;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
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
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    std::uint32_t ngramRangeMin = 1;
    std::uint32_t ngramRangeMax = 1;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
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
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    std::uint32_t ngramRangeMin = 1;
    std::uint32_t ngramRangeMax = 1;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
}

TEST_CASE("string_idf_df[0.4, 0.8]") {
    FrequencyMap const                         termFreqLabel({{"grape", 2}});
    IndexMap const                             termIndexLabel({{"grape", 0}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const
                                               inputBatches({{" orange  apple  apple peach  grape "},
                                                            {" grape orange     peach peach banana"},
                                                            {"orange orange peach   peach orange "}});
    //parameter initialization
    StringDecorator decorator;
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.4f;
    std::float_t maxDf = 0.8f;
    std::uint32_t ngramRangeMin = 1;
    std::uint32_t ngramRangeMax = 1;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
}

TEST_CASE("string_idf_df[0.0, 0.7]") {
    FrequencyMap const                         termFreqLabel({{"apple", 1}, {"grape", 2}, {"banana",1}});
    IndexMap const                             termIndexLabel({{"apple", 0}, {"grape", 2}, {"banana",1}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const
                                               inputBatches({{" orange  apple  apple peach  grape "},
                                                            {" grape orange     peach peach banana"},
                                                            {"orange orange peach   peach orange "}});
    //parameter initialization
    StringDecorator decorator;
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 0.7f;
    std::uint32_t ngramRangeMin = 1;
    std::uint32_t ngramRangeMax = 1;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
}

TEST_CASE("string_idf_max1features") {
#if (defined _WIN32)
    FrequencyMap const                         termFreqLabel({{"peach", 3}});
    IndexMap const                             termIndexLabel({{"peach", 0}});
#else
    FrequencyMap const                         termFreqLabel({{"orange", 3}});
    IndexMap const                             termIndexLabel({{"orange", 0}});
#endif
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const
                                               inputBatches({{" orange  apple  apple peach  grape "},
                                                            {" grape orange     peach peach banana"},
                                                            {"orange orange peach   peach orange "}});
    //parameter initialization
    StringDecorator decorator;
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>(static_cast<std::uint32_t>(1));
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    std::uint32_t ngramRangeMin = 1;
    std::uint32_t ngramRangeMax = 1;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
}

TEST_CASE("string_idf_max4features") {
#if (defined _WIN32)
    FrequencyMap const                         termFreqLabel({{"orange",3}, {"apple", 1}, {"peach", 3}, {"grape", 2}});
    IndexMap const                             termIndexLabel({{"orange", 2}, {"apple", 0}, {"peach", 3}, {"grape", 1}});
#else
    FrequencyMap const                         termFreqLabel({{"orange",3}, {"banana", 1}, {"peach", 3}, {"grape", 2}});
    IndexMap const                             termIndexLabel({{"orange", 2}, {"banana", 0}, {"peach", 3}, {"grape", 1}});
#endif
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const
                                               inputBatches({{" orange  apple  apple peach  grape "},
                                                            {" grape orange     peach peach banana"},
                                                            {"orange orange peach   peach orange "}});
    //parameter initialization
    StringDecorator decorator;
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>();
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>(static_cast<std::uint32_t>(4));
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    std::uint32_t ngramRangeMin = 1;
    std::uint32_t ngramRangeMax = 1;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
}

TEST_CASE("string_idf_custom_full_existingVocabulary") {
    FrequencyMap const                         termFreqLabel({{"orange",3}, {"apple", 1}, {"peach", 3}, {"grape", 2}, {"banana",1}});
    IndexMap const                             termIndexLabel({{"apple", 222}, {"banana",333}, {"grape", 666}, {"orange",999}, {"peach", 777}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const
                                               inputBatches({{" orange  apple  apple peach  grape "},
                                                            {" grape orange     peach peach banana"},
                                                            {"orange orange peach   peach orange "}});
    //parameter initialization
    StringDecorator decorator;
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>(IndexMap({{"apple", 222}, {"banana", 333}, {"grape", 666}, {"orange",999}, {"peach", 777}}));
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    std::uint32_t ngramRangeMin = 1;
    std::uint32_t ngramRangeMax = 1;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
}

TEST_CASE("string_idf_custom_insufficient_existingVocabulary") {
    FrequencyMap const                         termFreqLabel({{"orange",3}, {"apple", 1}, {"peach", 3}, {"grape", 2}, {"banana",1}});
    IndexMap const                             termIndexLabel({{"apple", 222}, {"banana",333}, {"grape", 666}, {"orange", 3}, {"peach", 4}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const
                                               inputBatches({{" orange  apple  apple peach  grape "},
                                                            {" grape orange     peach peach banana"},
                                                            {"orange orange peach   peach orange "}});
    //parameter initialization
    StringDecorator decorator;
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>(IndexMap({{"apple", 222}, {"banana", 333}, {"grape", 666}}));
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    std::uint32_t ngramRangeMin = 1;
    std::uint32_t ngramRangeMax = 1;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
}

TEST_CASE("string_idf_custom_over_existingVocabulary") {
    FrequencyMap const                         termFreqLabel({{"orange",3}, {"apple", 1}, {"peach", 3}, {"grape", 2}, {"banana",1}});
    IndexMap const                             termIndexLabel({{"apple", 222}, {"banana",333}, {"grape", 666}, {"orange",999}, {"peach", 777}});
    FrequencyAndIndexMap const                 termFreqAndIndexLabel = NS::Featurizers::Components::MergeTwoMapsWithSameKeys(termFreqLabel, termIndexLabel);
    std::uint32_t const                        docuNumsLabel(3);

    std::vector<std::vector<std::string>> const
                                               inputBatches({{" orange  apple  apple peach  grape "},
                                                            {" grape orange     peach peach banana"},
                                                            {"orange orange peach   peach orange "}});
    //parameter initialization
    StringDecorator decorator;
    AnalyzerMethod analyzer = AnalyzerMethod::Word;
    std::string regexToken = "";
    nonstd::optional<IndexMap> existingVocabulary = nonstd::optional<IndexMap>(IndexMap({{"apple", 222}, {"banana", 333}, {"grape", 666}, {"orange",999}, {"peach", 777}, {"fruit", 444}}));
    nonstd::optional<std::uint32_t> maxFeatures = nonstd::optional<std::uint32_t>();
    std::float_t minDf = 0.0f;
    std::float_t maxDf = 1.0f;
    std::uint32_t ngramRangeMin = 1;
    std::uint32_t ngramRangeMax = 1;

    DSRTestWrapper(inputBatches,
                   termFreqAndIndexLabel,
                   docuNumsLabel,
                   decorator,
                   analyzer,
                   regexToken,
                   existingVocabulary,
                   maxFeatures,
                   minDf,
                   maxDf,
                   ngramRangeMin,
                   ngramRangeMax);
}
