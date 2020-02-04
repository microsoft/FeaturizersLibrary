// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/DocumentStatisticsEstimator.h"
#include "TfidfVectorizerFeaturizer.h"
#include "../Traits.h"
#include "../Strings.h"
#include "Structs.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         CountVectorizerEstimator
///  \brief         Creates a `CountVectorizerTransformer` object.
///
template <size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class CountVectorizerEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        Components::DocumentStatisticsEstimator<MaxNumTrainingItemsV>,
        Details::TfidfVectorizerEstimatorImpl<SparseVectorEncoding<std::uint32_t>, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TransformedT = SparseVectorEncoding<std::uint32_t>;
    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            Components::DocumentStatisticsEstimator<MaxNumTrainingItemsV>,
            Details::TfidfVectorizerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>
        >;

    using IndexMapType                      = Microsoft::Featurizer::Featurizers::TfidfVectorizerTransformer<TransformedT>::IndexMap;
    using StringDecorator                   = std::function<std::string (std::string)>;
    using AnalyzerMethod                    = Components::AnalyzerMethod;
    using NormMethod                        = Microsoft::Featurizer::Featurizers::TfidfVectorizerTransformer<TransformedT>::NormMethod;
    using TfidfPolicy                       = Microsoft::Featurizer::Featurizers::TfidfPolicy;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CountVectorizerEstimator(
        AnnotationMapsPtr pAllColumnAnnotations, 
        size_t colIndex, 
        bool lower,
        AnalyzerMethod analyzer, 
        std::string regex, 
        std::float_t max_df,
        std::float_t min_df, 
        nonstd::optional<std::uint32_t> top_k_terms,
        std::uint32_t ngram_min, 
        std::uint32_t ngram_max, 
        bool binary,
        nonstd::optional<IndexMapType> vocabulary=nonstd::optional<IndexMapType>()
    );

    ~CountVectorizerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(CountVectorizerEstimator);
};

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// |
// |  Implementation
// |
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// |
// |  CountVectorizerEstimator
// |
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
CountVectorizerEstimator<MaxNumTrainingItemsV>::CountVectorizerEstimator(
    AnnotationMapsPtr pAllColumnAnnotations, 
    size_t colIndex, 
    bool lower,
    AnalyzerMethod analyzer, 
    std::string regex, 
    std::float_t max_df,
    std::float_t min_df, 
    nonstd::optional<std::uint32_t> top_k_terms,
    std::uint32_t ngram_min, 
    std::uint32_t ngram_max, 
    bool binary,
    nonstd::optional<IndexMapType> vocabulary
) :
    BaseType(
        "CountVectorizerEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex, lower, analyzer, regex, &vocabulary, &top_k_terms, &min_df, &max_df, ngram_min, ngram_max](void) {
            StringDecorator decorator = lower ? Microsoft::Featurizer::Strings::ToLower : StringDecorator();
            return Components::DocumentStatisticsEstimator<MaxNumTrainingItemsV>(
                std::move(pAllColumnAnnotations),
                std::move(colIndex),
                std::move(decorator),
                std::move(analyzer),
                std::move(regex),
                std::move(vocabulary),
                std::move(top_k_terms),
                std::move(min_df),
                std::move(max_df),
                std::move(ngram_min),
                std::move(ngram_max)
                );
        },
        [pAllColumnAnnotations, colIndex, &binary, &lower, &analyzer, &regex, &ngram_min, &ngram_max](void) {
            return Details::TfidfVectorizerEstimatorImpl<TransformedT, MaxNumTrainingItemsV>(
                std::move(pAllColumnAnnotations),
                std::move(colIndex),
                NormMethod::None,
                binary ? (TfidfPolicy::Binary) : static_cast<TfidfPolicy>(0),
                std::move(lower),
                std::move(analyzer),
                std::move(regex),
                std::move(ngram_min),
                std::move(ngram_max)
            );
        }
    ) {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Mirosoft
