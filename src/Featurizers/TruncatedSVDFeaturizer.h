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
///  \class         TruncatedSVDTransformer
///  \brief         Contains SVDComponents and use SVDComponents to project
///                 matrix for dimensionality reduction, also provides
///                 SVDComponents retriving
///
template <
    typename InputEigenMatrixT,
    typename OutputEigenMatrixT=Eigen::MatrixX<typename InputEigenMatrixT::Scalar>
>
class TruncatedSVDTransformer : public StandardTransformer<InputEigenMatrixT, OutputEigenMatrixT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = StandardTransformer<InputEigenMatrixT, OutputEigenMatrixT>;
    using EigenMatrix                       = Eigen::MatrixX<typename InputEigenMatrixT::Scalar>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    explicit TruncatedSVDTransformer(EigenMatrix singularvectors);
    explicit TruncatedSVDTransformer(Archive &ar);

    ~TruncatedSVDTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TruncatedSVDTransformer);

    bool operator==(TruncatedSVDTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    EigenMatrix const                       _singularvectors;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
     // MSVC has problems when the declaration and definition are separated
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override {
        if (input.size() == 0)
            throw std::invalid_argument("Input matrix size() invalid");

        if (input.cols() != _singularvectors.rows())
            throw std::invalid_argument("Input matrix cols() invalid");

        callback(input * _singularvectors);
    }
};

//the following functions are introduced from RedSVD
//Copyright attached
/*
 * A header-only version of RedSVD
 *
 * Copyright (c) 2014 Nicolas Tessore
 *
 * based on RedSVD
 *
 * Copyright (c) 2010 Daisuke Okanohara
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above Copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above Copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the authors nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 */
template<typename Scalar>
inline void sample_gaussian(Scalar& x, Scalar& y)
{
    using std::sqrt;
    using std::log;
    using std::cos;
    using std::sin;

    #if (defined __clang__)
    #   pragma clang diagnostic push
    #   pragma clang diagnostic ignored "-Wdouble-promotion"
    #endif

    const Scalar PI(3.1415926535897932384626433832795028841971693993751f);

    #if (defined __clang__)
    #   pragma clang diagnostic pop
    #endif

    Scalar v1 = static_cast<Scalar>(std::rand() + static_cast<Scalar>(1)) / (static_cast<Scalar>(RAND_MAX+static_cast<Scalar>(2)));
    Scalar v2 = static_cast<Scalar>(std::rand() + static_cast<Scalar>(1)) / (static_cast<Scalar>(RAND_MAX+static_cast<Scalar>(2)));
    Scalar len = sqrt(static_cast<Scalar>(-2) * log(v1));
    x = len * cos(static_cast<Scalar>(2) * PI * v2);
    y = len * sin(static_cast<Scalar>(2) * PI * v2);
}

template<typename MatrixType>
inline void sample_gaussian(MatrixType& mat) {

    typedef typename MatrixType::Index Index;

    for(Index i = 0; i < mat.rows(); ++i)
    {
        for(Index j = 0; j+1 < mat.cols(); j += 2)
            sample_gaussian(mat(i, j), mat(i, j+1));
        if(mat.cols() % 2)
            sample_gaussian(mat(i, mat.cols()-1), mat(i, mat.cols()-1));
    }
}

template<typename MatrixType>
inline void gram_schmidt(MatrixType& mat) {

    typedef typename MatrixType::Scalar Scalar;
    typedef typename MatrixType::Index Index;

    #if (defined __clang__)
    #   pragma clang diagnostic push
    #   pragma clang diagnostic ignored "-Wdouble-promotion"
    #endif

    static const Scalar EPS(1E-4f);

    #if (defined __clang__)
    #   pragma clang diagnostic pop
    #endif

    for(Index i = 0; i < mat.cols(); ++i) {
        for(Index j = 0; j < i; ++j) {
            Scalar r = mat.col(i).dot(mat.col(j));
            mat.col(i) -= r * mat.col(j);
        }

        Scalar norm = mat.col(i).norm();

        if(norm < EPS) {
            for(Index k = i; k < mat.cols(); ++k)
                mat.col(k).setZero();
            return;
        }
        mat.col(i) /= norm;
    }
}

/////////////////////////////////////////////////////////////////////////
///  \class         TruncatedSVDEstimator
///  \brief         Estimator that reads an annotation created by the `SVDComponentsEstimator`
///                 and creates a `SVDTransformer` object.
///
template <
    typename InputEigenMatrixT,
    typename OutputEigenMatrixT=Eigen::MatrixX<typename InputEigenMatrixT::Scalar>,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class TruncatedSVDEstimator : public TransformerEstimator<InputEigenMatrixT, OutputEigenMatrixT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputEigenMatrixT, OutputEigenMatrixT>;
    using TransformerType                   = TruncatedSVDTransformer<InputEigenMatrixT, OutputEigenMatrixT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TruncatedSVDEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~TruncatedSVDEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TruncatedSVDEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using EigenMatrix                       = Eigen::MatrixX<typename InputEigenMatrixT::Scalar>;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;

    EigenMatrix                             _state;

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
        Eigen::Index                        rank((matrix.rows() < matrix.cols()) ? matrix.rows() : matrix.cols());

        // Gaussian Random Matrix for _matrix^T
        EigenMatrix                         O(matrix.rows(), rank);
        sample_gaussian(O);

        // Compute Sample Matrix of _matrix^T
        EigenMatrix                         Y(matrix.transpose() * O);

        // Orthonormalize Y
        gram_schmidt(Y);

        // Range(B) = Range(_matrix^T)
        EigenMatrix                         B(matrix * Y);

        // Gaussian Random Matrix
        EigenMatrix                         P(B.cols(), rank);

        sample_gaussian(P);

        // Compute Sample Matrix of B
        EigenMatrix                         Z(B * P);

        // Orthonormalize Z
        gram_schmidt(Z);

        // Range(C) = Range(B)
        EigenMatrix                         C(Z.transpose() * B);

        Eigen::JacobiSVD<EigenMatrix>       svdOfC(C, Eigen::ComputeThinV);

        _state = Y * svdOfC.matrixV();

        return FitResult::Complete;
    }

    void complete_training_impl(void) override;

    // MSVC has problems when the definition is separate from the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        return typename BaseType::TransformerUniquePtr(new TransformerType(std::move(_state)));
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
// |  TruncatedSVDTransformer
// |
// ----------------------------------------------------------------------
template <typename InputEigenMatrixT, typename OutputEigenMatrixT>
TruncatedSVDTransformer<InputEigenMatrixT, OutputEigenMatrixT>::TruncatedSVDTransformer(EigenMatrix singularvectors) :
    _singularvectors(std::move(singularvectors)) {
    if(_singularvectors.size() == 0)
        throw std::invalid_argument("singularvectors");
}

template <typename InputEigenMatrixT, typename OutputEigenMatrixT>
TruncatedSVDTransformer<InputEigenMatrixT, OutputEigenMatrixT>::TruncatedSVDTransformer(Archive &ar) :
    TruncatedSVDTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            EigenMatrix                     singularvectors(Traits<EigenMatrix>::deserialize(ar));

            return TruncatedSVDTransformer(std::move(singularvectors));
        }()
    ) {
}

template <typename InputEigenMatrixT, typename OutputEigenMatrixT>
bool TruncatedSVDTransformer<InputEigenMatrixT, OutputEigenMatrixT>::operator==(TruncatedSVDTransformer const &other) const {
    if ((this->_singularvectors - other._singularvectors).norm() > 0.000001f)
        return false;

    return true;
}

template <typename InputEigenMatrixT, typename OutputEigenMatrixT>
void TruncatedSVDTransformer<InputEigenMatrixT, OutputEigenMatrixT>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(_singularvectors)>::serialize(ar, _singularvectors);
}

// ----------------------------------------------------------------------
// |
// |  TruncatedSVDEstimator
// |
// ----------------------------------------------------------------------
template <typename InputEigenMatrixT, typename OutputEigenMatrixT, size_t MaxNumTrainingItemsV>
TruncatedSVDEstimator<InputEigenMatrixT, OutputEigenMatrixT, MaxNumTrainingItemsV>::TruncatedSVDEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
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
bool TruncatedSVDEstimator<InputEigenMatrixT, OutputEigenMatrixT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return true;
}

template <typename InputEigenMatrixT, typename OutputEigenMatrixT, size_t MaxNumTrainingItemsV>
void TruncatedSVDEstimator<InputEigenMatrixT, OutputEigenMatrixT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
