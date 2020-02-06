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
///  \class         CountVectorizerTransformer
///  \brief         Returns SparseVectorEncoding<std::uint32_t> for each unique input
///
class CountVectorizerTransformer : public StandardTransformer<std::string, SparseVectorEncoding<std::uint32_t>> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                           = StandardTransformer<std::string, SparseVectorEncoding<std::uint32_t>>;
    using TfidfEstimator                     = Microsoft::Featurizer::Featurizers::TfidfVectorizerEstimator<std::numeric_limits<size_t>::max()>;
    using TransformerUniquePtrType           = TfidfEstimator::TransformerUniquePtr;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    CountVectorizerTransformer(TransformerUniquePtrType pTransformer);
    CountVectorizerTransformer(Archive &ar);

    ~CountVectorizerTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(CountVectorizerTransformer);

    void save(Archive &ar) const override;

    bool operator==(CountVectorizerTransformer const &other) const;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    TransformerUniquePtrType                _pTransformer;
    // ----------------------------------------------------------------------
    // |
    // |  Private Methodsa
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override;
};

/////////////////////////////////////////////////////////////////////////
///  \class         CountVectorizerEstimator
///  \brief         Creates a `CountVectorizerTransformer` object.
///
template <size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()>
class CountVectorizerEstimator : public TransformerEstimator<std::string, SparseVectorEncoding<std::uint32_t>> {
public:

    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<std::string, SparseVectorEncoding<std::uint32_t>>;
    using TransformerType                   = CountVectorizerTransformer;
    using IndexMapType                      = Microsoft::Featurizer::Featurizers::TfidfVectorizerTransformer::IndexMap;
    using StringDecorator                   = std::function<std::string (std::string)>;
    using AnalyzerMethod                    = Components::AnalyzerMethod;
    using NormMethod                        = Microsoft::Featurizer::Featurizers::TfidfVectorizerTransformer::NormMethod;
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

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using TfidfEstimator                   = Microsoft::Featurizer::Featurizers::TfidfVectorizerEstimator<MaxNumTrainingItemsV>;
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                           _colIndex;
    TfidfEstimator                         _tfidfEstimator;
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;

    // MSVC has problems when the declaration and definition are separated
    FitResult fit_impl(typename BaseType::InputType const *pBuffer, size_t cElements) override {
        return _tfidfEstimator.fit(pBuffer, cElements);
    }

    void complete_training_impl(void) override;

    // MSVC has problems when the declaration and definition are separated
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        _tfidfEstimator.complete_training();
        typename TfidfEstimator::TransformerUniquePtr           pTransformer(CountVectorizerEstimator<MaxNumTrainingItemsV>::_tfidfEstimator.create_transformer());
        return typename BaseType::TransformerUniquePtr(new CountVectorizerTransformer(std::move(pTransformer)));
    }
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
    BaseType("CountVectorizerEstimator", pAllColumnAnnotations),
    _colIndex(
        std::move(
            [this, &colIndex](void) -> size_t & {
                if(colIndex >= this->get_column_annotations().size())
                    throw std::invalid_argument("colIndex");

                return colIndex;
            }()
        )
    ),
    _tfidfEstimator(
       TfidfEstimator(
           pAllColumnAnnotations,
           colIndex,
           lower,
           analyzer,
           regex,
           NormMethod::None,
           binary ? (TfidfPolicy::Binary) : static_cast<TfidfPolicy>(0),
           min_df,
           max_df,
           top_k_terms,
           ngram_min,
           ngram_max,
           vocabulary
       )
    ){
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
bool CountVectorizerEstimator<MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    _tfidfEstimator.begin_training();
    return true;
}

template <size_t MaxNumTrainingItemsV>
void CountVectorizerEstimator<MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Mirosoft
