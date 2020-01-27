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
template <
    typename InputEigenMatrixT,
    typename OutputEigenMatrixT = typename InputMatrixTypeMapper<InputEigenMatrixT>::OutType
>
class PCATransformer : public StandardTransformer<InputEigenMatrixT, OutputEigenMatrixT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = StandardTransformer<InputEigenMatrixT, OutputEigenMatrixT>;

    using EigenMatrix                       = typename InputMatrixTypeMapper<InputEigenMatrixT>::MatrixType;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    explicit PCATransformer(EigenMatrix eigenvectors);
    explicit PCATransformer(Archive &ar);

    ~PCATransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(PCATransformer);

    bool operator==(PCATransformer const &other) const;

    void save(Archive &ar) const override;

    std::ptrdiff_t getEigenVectorRowsNumber() const;
    std::ptrdiff_t getEigenVectorColsNumber() const;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    EigenMatrix const                       _eigenvectors;

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

        // TODO: We should compute this transformation during construction and cache that value rather
        //       then repeatedly calculating it here.
        callback(input * _eigenvectors.transpose());
    }
};

/////////////////////////////////////////////////////////////////////////
///  \class         PCAEstimator
///  \brief         Estimator to calculate PCAComponents
///
template <
    typename InputEigenMatrixT,
    typename OutputEigenMatrixT= typename InputMatrixTypeMapper<InputEigenMatrixT>::OutType,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class PCAEstimator : public TransformerEstimator<InputEigenMatrixT, OutputEigenMatrixT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputEigenMatrixT, OutputEigenMatrixT>;
    using TransformerType                   = PCATransformer<InputEigenMatrixT, OutputEigenMatrixT>;

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
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using EigenMatrix                       = typename InputMatrixTypeMapper<InputEigenMatrixT>::MatrixType;
    using SelfAdjointEigenSolver            = Eigen::SelfAdjointEigenSolver<EigenMatrix>;
    using EigenVectors                      = typename SelfAdjointEigenSolver::EigenvectorsType;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;

    EigenVectors                            _eigenVectors;

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

        SelfAdjointEigenSolver              eig(
            [&matrix]() {
                //compute for centered training data
                EigenMatrix                 centered = matrix.rowwise() - matrix.colwise().mean();

                //compute for covariance matrix
                EigenMatrix                 cov = centered.adjoint() * centered;

                //using covariance matrix to compute PCA
                return cov;
            }()
        );

        _eigenVectors = eig.eigenvectors();

        return FitResult::Complete;
    }

    void complete_training_impl(void) override;

    // MSVC has problems when the definition is separate from the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return typename BaseType::TransformerUniquePtr(new TransformerType(std::move(_eigenVectors)));
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
template <typename InputEigenMatrixT, typename OutputEigenMatrixT>
PCATransformer<InputEigenMatrixT, OutputEigenMatrixT>::PCATransformer(EigenMatrix eigenvectors) :
    _eigenvectors(std::move(eigenvectors)) {
    if(_eigenvectors.size() == 0)
        throw std::invalid_argument("eigenvectors");
}

template <typename InputEigenMatrixT, typename OutputEigenMatrixT>
PCATransformer<InputEigenMatrixT, OutputEigenMatrixT>::PCATransformer(Archive &ar) :
    PCATransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            EigenMatrix                     eigenvectors(Traits<EigenMatrix>::deserialize(ar));

            return PCATransformer(std::move(eigenvectors));
        }()
    ) {
}

template <typename InputEigenMatrixT, typename OutputEigenMatrixT>
bool PCATransformer<InputEigenMatrixT, OutputEigenMatrixT>::operator==(PCATransformer const &other) const {
    if ((this->_eigenvectors - other._eigenvectors).norm() > 0.000001f)
        return false;

    return true;
}

template <typename InputEigenMatrixT, typename OutputEigenMatrixT>
void PCATransformer<InputEigenMatrixT, OutputEigenMatrixT>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(_eigenvectors)>::serialize(ar, _eigenvectors);
}

template <typename InputEigenMatrixT, typename OutputEigenMatrixT>
std::ptrdiff_t PCATransformer<InputEigenMatrixT, OutputEigenMatrixT>::getEigenVectorRowsNumber() const {
    return _eigenvectors.rows();
}

template <typename InputEigenMatrixT, typename OutputEigenMatrixT>
std::ptrdiff_t PCATransformer<InputEigenMatrixT, OutputEigenMatrixT>::getEigenVectorColsNumber() const {
    return _eigenvectors.cols();
}

// ----------------------------------------------------------------------
// |
// |  PCAEstimator
// |
// ----------------------------------------------------------------------
template <typename InputEigenMatrixT, typename OutputEigenMatrixT, size_t MaxNumTrainingItemsV>
PCAEstimator<InputEigenMatrixT, OutputEigenMatrixT, MaxNumTrainingItemsV>::PCAEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("SVDEstimatorImpl", std::move(pAllColumnAnnotations)),
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
template <typename InputEigenMatrixT, typename OutputEigenMatrixT, size_t MaxNumTrainingItemsV>
bool PCAEstimator<InputEigenMatrixT, OutputEigenMatrixT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return true;
}

template <typename InputEigenMatrixT, typename OutputEigenMatrixT, size_t MaxNumTrainingItemsV>
void PCAEstimator<InputEigenMatrixT, OutputEigenMatrixT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
