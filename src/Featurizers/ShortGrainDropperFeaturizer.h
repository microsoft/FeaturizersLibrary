// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Featurizer.h"
#include "../Archive.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

/////////////////////////////////////////////////////////////////////////
///  \class         ContainerHash
///  \brief         Hash function for Container type
///
template <typename Container>
struct ContainerHash {
    std::size_t operator()(Container const& container) const noexcept {
        std::size_t hash = 0;
        for (typename Container::value_type const & val : container)
            hash ^= std::hash<typename Container::value_type>{}(val) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        return hash;
    }
};


/////////////////////////////////////////////////////////////////////////
///  \class         ShortGrainDropperTransformer
///  \brief         Return true if a grain needs dropping
///
class ShortGrainDropperTransformer : public StandardTransformer<std::vector<std::string>, bool> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = StandardTransformer<std::vector<std::string>, bool>;
    using GrainsSet                         = std::unordered_set<std::vector<std::string>, ContainerHash<std::vector<std::string>>>;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    explicit ShortGrainDropperTransformer(GrainsSet grainsToDrop);
    explicit ShortGrainDropperTransformer(Archive &ar);

    ~ShortGrainDropperTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ShortGrainDropperTransformer);

    bool operator==(ShortGrainDropperTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    GrainsSet const                         _grainsToDrop;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override;
};

/////////////////////////////////////////////////////////////////////////
///  \class         ShortGrainDropperEstimator
///  \brief         Estimator to determine which grain to drop given the
///                 threshod minPoints calculated by:
///
///                 windowSize: the rolling window size.
///                 lags: The lag sizes.
///                 maxHorizon: the desired length of forecasting (the number of new rows generated)
///                 cv: the number of cross validations.
///
template <
    size_t MaxNumTrainingItemsV = std::numeric_limits<size_t>::max()
>
class ShortGrainDropperEstimator : public TransformerEstimator<std::vector<std::string>, bool> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<std::vector<std::string>, bool>;
    using TransformerType                   = ShortGrainDropperTransformer;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ShortGrainDropperEstimator(
        AnnotationMapsPtr pAllColumnAnnotations,
        size_t colIndex,
        std::uint8_t windowSize,
        std::vector<std::uint8_t> lags,
        std::uint8_t maxHorizon,
        nonstd::optional<std::uint8_t> cv
    );
    ~ShortGrainDropperEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ShortGrainDropperEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using GrainsSet                         = ShortGrainDropperTransformer::GrainsSet;
    using GrainsMap                         = std::unordered_map<std::vector<std::string>, std::uint32_t, ContainerHash<std::vector<std::string>>>;
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;
    std::uint16_t const                     _minPoints;
    GrainsSet                               _grainsToDrop;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;

    // MSVC has problems when the declaration and definition are separated
    FitResult fit_impl(typename BaseType::InputType const *pBuffer, size_t cElements) override {

        InputType const * const                 pEndBuffer(pBuffer + cElements);

        GrainsMap groupByGrains;
        while(pBuffer != pEndBuffer) {
            GrainsMap::iterator grainsMapIter(groupByGrains.find(*pBuffer));
            if (grainsMapIter != groupByGrains.end())
                ++grainsMapIter->second;
            else
                groupByGrains.emplace(*pBuffer, 1);
            ++pBuffer;
        }

        for (GrainsMap::value_type const & groupByGrainsElement : groupByGrains) {
            if (groupByGrainsElement.second <= _minPoints)
                _grainsToDrop.emplace(std::move(groupByGrainsElement.first));
        }

        return FitResult::Complete;
    }

    void complete_training_impl(void) override;

    // MSVC has problems when the definition is separate from the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return typename BaseType::TransformerUniquePtr(new TransformerType(std::move(_grainsToDrop)));
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

// --------------------------------------------------------------------
// |
// |  ShortGrainDropperEstimator
// |
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
ShortGrainDropperEstimator<MaxNumTrainingItemsV>::ShortGrainDropperEstimator(
    AnnotationMapsPtr pAllColumnAnnotations,
    size_t colIndex,
    std::uint8_t windowSize,
    std::vector<std::uint8_t> lags,
    std::uint8_t maxHorizon,
    nonstd::optional<std::uint8_t> cv
) :
    BaseType("ShortGrainDropperEstimatorImpl", std::move(pAllColumnAnnotations)),
    _colIndex(
        [this, &colIndex](void) -> size_t & {
            if(colIndex >= this->get_column_annotations().size())
                throw std::invalid_argument("colIndex");
            return colIndex;
        }()
    ),
    _minPoints(
        [&windowSize, &lags, &maxHorizon, &cv](void) -> std::uint16_t {
            //it appears automl tests show that
            //windowSize can be 0
            //lags could contain 0s
            //maxHorizon may not be 0, not sure currently
            //cv may not be 0, not sure currently
            if (lags.size() == 0)
                throw std::invalid_argument("lags");
            if (!cv.has_value())
                return (maxHorizon + std::max(windowSize, *std::max_element(lags.cbegin(), lags.cend())) + 1);
            return (2*maxHorizon + static_cast<std::uint8_t>(*cv) + std::max(windowSize, *std::max_element(lags.cbegin(), lags.cend())) + 1);
        }()
    ) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
bool ShortGrainDropperEstimator<MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return true;
}

template <size_t MaxNumTrainingItemsV>
void ShortGrainDropperEstimator<MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
