// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../Featurizer.h"
#include "../Archive.h"
#include "../Traits.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

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
    using GrainsSet                         = std::unordered_set<std::vector<std::string>, Microsoft::Featurizer::ContainerHash<std::vector<std::string>>>;
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
///                 threshod minPoints calculated by windowSize, lags,
///                 maxHorizon and cv.
///                 todo: more comments will add here later
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
    template <typename LagInputIteratorT>
    ShortGrainDropperEstimator(
        AnnotationMapsPtr pAllColumnAnnotations,
        size_t colIndex,
        std::uint32_t maxWindowSize,
        //todo: possible name change and add commments, after sync with other Timeseries related Featurizers
        std::tuple<LagInputIteratorT, LagInputIteratorT> lags,
        //todo: possible name change and add commments, after sync with other Timeseries related Featurizers
        std::uint32_t horizon,
        //todo: possible name change and add commments, after sync with other Timeseries related Featurizers
        nonstd::optional<std::uint32_t> crossValidation
        //todo: possible name change and add commments, after sync with other Timeseries related Featurizers
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
    using GrainsMap                         = std::unordered_map<std::vector<std::string>, std::uint32_t, Microsoft::Featurizer::ContainerHash<std::vector<std::string>>>;
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;
    std::uint32_t const                     _minPoints;
    GrainsSet                               _grainsToDrop;
    GrainsMap                               _groupByGrains;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;

    // MSVC has problems when the declaration and definition are separated
    FitResult fit_impl(typename BaseType::InputType const *pBuffer, size_t cElements) override {

        InputType const * const                 pEndBuffer(pBuffer + cElements);

        while(pBuffer != pEndBuffer) {
            GrainsMap::iterator grainsMapIter(_groupByGrains.find(*pBuffer));
            if (grainsMapIter != _groupByGrains.end())
                ++grainsMapIter->second;
            else
                _groupByGrains.emplace(*pBuffer, 1);
            ++pBuffer;
        }

        return FitResult::Continue;
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
template <typename LagInputIteratorT>
ShortGrainDropperEstimator<MaxNumTrainingItemsV>::ShortGrainDropperEstimator(
    AnnotationMapsPtr pAllColumnAnnotations,
    size_t colIndex,
    std::uint32_t maxWindowSize,
    std::tuple<LagInputIteratorT, LagInputIteratorT> lags,
    std::uint32_t horizon,
    nonstd::optional<std::uint32_t> crossValidation
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
        [&maxWindowSize, &lags, &horizon, &crossValidation](void) -> std::uint32_t {
            static_assert(std::is_same<typename std::iterator_traits<LagInputIteratorT>::value_type, std::uint32_t>::value, "'LagInputIteratorT' must point to an uint8");

            //it appears automl tests show that
            //windowSize can be 0
            //lags could contain 0s
            //maxHorizon may not be 0, not sure currently
            //cv may not be 0, not sure currently
            if (std::distance(std::get<0>(lags), std::get<1>(lags)) == 0)
                throw std::invalid_argument("lags");
            if (!crossValidation.has_value())
                return (horizon + std::max(maxWindowSize, *std::max_element(std::get<0>(lags), std::get<1>(lags))) + 1);
            return (2*horizon + *crossValidation + std::max(maxWindowSize, *std::max_element(std::get<0>(lags), std::get<1>(lags))) + 1);
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
    for (GrainsMap::value_type const & groupByGrainsElement : _groupByGrains) {
        if (groupByGrainsElement.second <= _minPoints)
            _grainsToDrop.emplace(std::move(groupByGrainsElement.first));
    }
    //clear _groupByGrains
    _groupByGrains = {};
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
