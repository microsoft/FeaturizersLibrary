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
    using GrainsSet                         = std::unordered_set<std::string>;
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
     // MSVC has problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        callback(_grainsToDrop.find(Traits<decltype(input)>::ToString(input)) != _grainsToDrop.end());
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         ShortGrainDropperEstimator
///  \brief         Estimator to determine which grain to drop
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
        std::uint32_t windowSize,
        std::vector<std::uint32_t> lags,
        std::uint32_t maxHorizon,
        nonstd::optional<std::uint32_t> cv
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
    using GrainsMap                         = std::unordered_map<std::string, std::uint32_t>;
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;
    std::uint32_t const                     _minPoints;
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
            std::string pBufferStr = Traits<decltype(*pBuffer)>::ToString(*pBuffer);
            GrainsMap::iterator grainsMapIter(groupByGrains.find(pBufferStr));
            if (grainsMapIter != groupByGrains.end())
                ++grainsMapIter->second;
            else
                groupByGrains.emplace(pBufferStr, 1);
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

// ----------------------------------------------------------------------
// |
// |  ShortGrainDropperTransformer
// |
// ----------------------------------------------------------------------
ShortGrainDropperTransformer::ShortGrainDropperTransformer(GrainsSet grainsToDrop) :
    //grainsToDrop can be empty
    _grainsToDrop(std::move(grainsToDrop)) {
}

ShortGrainDropperTransformer::ShortGrainDropperTransformer(Archive &ar) :
    ShortGrainDropperTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            GrainsSet                       grainsToDrop(Traits<GrainsSet>::deserialize(ar));

            return ShortGrainDropperTransformer(std::move(grainsToDrop));
        }()
    ) {
}

bool ShortGrainDropperTransformer::operator==(ShortGrainDropperTransformer const &other) const {
    return this->_grainsToDrop == other._grainsToDrop;
}

void ShortGrainDropperTransformer::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(_grainsToDrop)>::serialize(ar, _grainsToDrop);
}

// ----------------------------------------------------------------------
// |
// |  ShortGrainDropperEstimator
// |
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
ShortGrainDropperEstimator<MaxNumTrainingItemsV>::ShortGrainDropperEstimator(
    AnnotationMapsPtr pAllColumnAnnotations,
    size_t colIndex,
    std::uint32_t windowSize,
    std::vector<std::uint32_t> lags,
    std::uint32_t maxHorizon,
    nonstd::optional<std::uint32_t> cv
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
        [&windowSize, &lags, &maxHorizon, &cv](void) -> std::uint32_t {
            //it appears automl tests show that
            //windowSize can be 0
            //lags could contain 0s
            //maxHorizon may not be 0, not sure currently
            //cv may not be 0, not sure currently
            if (lags.size() == 0)
                throw std::invalid_argument("lags");
            if (!cv.has_value())
                return (maxHorizon + std::max(windowSize, *std::max_element(lags.cbegin(), lags.cend())) + 1);
            return (2*maxHorizon + static_cast<std::uint32_t>(*cv) + std::max(windowSize, *std::max_element(lags.cbegin(), lags.cend())) + 1);
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
