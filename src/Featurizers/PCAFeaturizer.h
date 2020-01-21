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
///  \class         PCATransformer
///  \brief         Contains PCAComponents and use PCAComponents to project
///                 matrix for dimensionality reduction, also provides
///                 PCAComponents retriving
///
template <typename MatrixT>
class PCATransformer : public StandardTransformer<MatrixT, MatrixT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                                   = StandardTransformer<MatrixT, MatrixT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    explicit PCATransformer(MatrixT eigenvectors);
    explicit PCATransformer(Archive &ar);

    ~PCATransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(PCATransformer);

    bool operator==(PCATransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    MatrixT const                                    _eigenvectors;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
     // MSVC has problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        if (input.size() == 0)
            throw std::invalid_argument("Input matrix size() invalid");

        //this is simplified(mathematically) from input.col() == _eigenvectors.transpose().rows()
        if (input.cols() != _eigenvectors.cols())
            throw std::invalid_argument("Input matrix cols() invalid");

        callback(input * _eigenvectors.transpose());
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         PCAEstimator
///  \brief         Estimator to calculate PCAComponents
///
template <
    typename MatrixT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class PCAEstimator : public TransformerEstimator<MatrixT, MatrixT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<MatrixT, MatrixT>;
    using TransformerType                   = PCATransformer<MatrixT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    PCAEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~PCAEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(PCAEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;
    MatrixT                                 _matrix;

    bool                                    _hasCalledFit;
    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;
    // MSVC has problems when the declaration and definition are separated
    FitResult fit_impl(typename BaseType::InputType const *pBuffer, size_t) override {
        if (_hasCalledFit)
            throw std::runtime_error("fit_impl() should not be called move than once in PCAFeaturizer");

        _matrix = *pBuffer;
        _hasCalledFit = true;

        return FitResult::Continue;
    }
    void complete_training_impl(void) override;

    // MSVC has problems when the definition is separate from the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {

        Eigen::SelfAdjointEigenSolver<MatrixT> eig(
            [this]() -> MatrixT {
                //compute for centered training data
                MatrixT centered = _matrix.rowwise() - _matrix.colwise().mean();
                //compute for covariance matrix
                MatrixT cov = centered.adjoint() * centered;
                //using covariance matrix to compute PCA
                return cov;
            }()
        );

        // free _matrix
        _matrix.resize(0, 0);

        return typename BaseType::TransformerUniquePtr(new PCATransformer<MatrixT>(eig.eigenvectors()));
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
template <typename MatrixT>
PCATransformer<MatrixT>::PCATransformer(MatrixT eigenvectors) :
    _eigenvectors(std::move(eigenvectors)) {
    if(_eigenvectors.size() == 0)
        throw std::invalid_argument("eigenvectors");
}

template <typename MatrixT>
PCATransformer<MatrixT>::PCATransformer(Archive &ar) :
    PCATransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            MatrixT                        eigenvectors(Traits<MatrixT>::deserialize(ar));

            return PCATransformer<MatrixT>(std::move(eigenvectors));
        }()
    ) {
}

template <typename MatrixT>
bool PCATransformer<MatrixT>::operator==(PCATransformer const &other) const {
    if ((this->_eigenvectors - other._eigenvectors).norm() > 0.000001f)
        return false;

    return true;
}

template <typename MatrixT>
void PCATransformer<MatrixT>::save(Archive &ar) const /*override*/ {
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
template <typename MatrixT, size_t MaxNumTrainingItemsV>
PCAEstimator<MatrixT, MaxNumTrainingItemsV>::PCAEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("SVDEstimatorImpl", std::move(pAllColumnAnnotations)),
    _colIndex(
        std::move(
            [this, &colIndex](void) -> size_t & {
                if(colIndex >= this->get_column_annotations().size())
                    throw std::invalid_argument("colIndex");

                return colIndex;
            }()
        )
    ),
    _hasCalledFit(false) {
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename MatrixT,size_t MaxNumTrainingItemsV>
bool PCAEstimator<MatrixT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return true;
}

template <typename MatrixT, size_t MaxNumTrainingItemsV>
void PCAEstimator<MatrixT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
