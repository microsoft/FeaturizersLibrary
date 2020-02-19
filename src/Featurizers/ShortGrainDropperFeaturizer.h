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
///  \brief
///
class ShortGrainDropperTransformer : public StandardTransformer<std::vector<std::string>, bool> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = StandardTransformer<std::vector<std::string>, bool>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    explicit ShortGrainDropperTransformer();
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
    std::unordered_set<std::vector<std::string>> const _grainsToDrop;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
     // MSVC has problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {

    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         PCAEstimator
///  \brief         Estimator to calculate PCAComponents
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
    using TransformerType                   = ShortGrainDropperTransformer<std::vector<std::string>, bool>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    ShortGrainDropperEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~ShortGrainDropperEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(ShortGrainDropperEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------


    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;

    std::unordered_set<std::vector<std::string>> const _grainsToDrop;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;

    // MSVC has problems when the declaration and definition are separated
    FitResult fit_impl(typename BaseType::InputType const *pBuffer, size_t cElements) override {
        if(cElements != 1)
            throw std::runtime_error("Only 1 matrix can be provided");

        auto const &                        matrix(*pBuffer);


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
// |  PCATransformer
// |
// ----------------------------------------------------------------------
ShortGrainDropperTransformer::ShortGrainDropperTransformer() :
    _eigenvectors(std::move(eigenvectors)) {
    if(_eigenvectors.size() == 0)
        throw std::invalid_argument("eigenvectors");
}

ShortGrainDropperTransformer::ShortGrainDropperTransformer(Archive &ar) :
    PCATransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            return ShortGrainDropperTransformer(std::move());
        }()
    ) {
}

bool ShortGrainDropperTransformer::operator==(ShortGrainDropperTransformer const &other) const {

}

void ShortGrainDropperTransformer::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(_eigenvectors)>::serialize(ar, _eigenvectors);
}

// ----------------------------------------------------------------------
// |
// |  PCAEstimator
// |
// ----------------------------------------------------------------------
template <size_t MaxNumTrainingItemsV>
ShortGrainDropperEstimator<MaxNumTrainingItemsV>::ShortGrainDropperEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("ShortGrainDropperEstimatorImpl", std::move(pAllColumnAnnotations)),
    _colIndex(
        std::move(
            [this, &colIndex](void) -> size_t & {
                if(colIndex >= this->get_column_annotations().size())
                    throw std::invalid_argument("colIndex");

                return colIndex;
            }()
        )
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
