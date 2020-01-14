// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/PipelineExecutionEstimatorImpl.h"
#include "Components/TrainingOnlyEstimatorImpl.h"

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wold-style-cast"
#   pragma clang diagnostic ignored "-Wsign-conversion"
#   pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#   pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#   pragma clang diagnostic ignored "-Wextra-semi-stmt"
#   pragma clang diagnostic ignored "-Wmissing-noreturn"
#   pragma clang diagnostic ignored "-Wdocumentation"
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#   pragma clang diagnostic ignored "-Wcast-align"
#   pragma clang diagnostic ignored "-Wfloat-equal"
#   pragma clang diagnostic ignored "-Wshadow"
#elif (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127)
#endif

#include "Eigen/Dense"

#if (defined __clang__)
#   pragma clang diagnostic pop
#elif (defined _MSC_VER)
#   pragma warning(pop)
#endif

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

static constexpr char const * const         SVDComponentsEstimatorName("SVDComponentsEstimator");

namespace {
//the following functions in anonymous space are introduced from RedSVD
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

} //anonymous namespace

/////////////////////////////////////////////////////////////////////////
///  \class         SVDComponentsAnnotationData
///  \brief         Contains SVD components: Eigenvalues and Eigenvectors
template <typename T>
class SVDComponentsAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------

    T const                                          SingularValues;
    T const                                          SingularVectors;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SVDComponentsAnnotationData(T singularvalues, T singularvectors);
    ~SVDComponentsAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SVDComponentsAnnotationData);
};

namespace ComponentsDetails {

/////////////////////////////////////////////////////////////////////////
///  \class         SVDTrainingOnlyPolicy
///  \brief         `SVDComponentsEstimator` implementation details.
///
template <typename InputT, typename TransformedT>
class SVDTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                                  = InputT;
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const    NameValue = SVDComponentsEstimatorName;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------

    void fit(InputType const &input);
    SVDComponentsAnnotationData<TransformedT> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    TransformedT                                     _matrix;
    TransformedT                                     _singularvalues;
    TransformedT                                     _singularvectors;
};

} // namespace ComponentsDetails

/////////////////////////////////////////////////////////////////////////
///  \class         SVDComponentsEstimator
///  \brief         This class generates SVDComponentsAnnotationData
///                 by processing input matrix using Eigen
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class SVDComponentsEstimator :
    public Components::TrainingOnlyEstimatorImpl<
        ComponentsDetails::SVDTrainingOnlyPolicy<InputT, TransformedT>,
        MaxNumTrainingItemsV
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        Components::TrainingOnlyEstimatorImpl<
            ComponentsDetails::SVDTrainingOnlyPolicy<InputT, TransformedT>,
            MaxNumTrainingItemsV
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SVDComponentsEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~SVDComponentsEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SVDComponentsEstimator);
};


/////////////////////////////////////////////////////////////////////////
///  \class         SVDTransformer
///  \brief         Contains SVDComponents and use SVDComponents to project
///                 matrix for dimensionality reduction, also provides 
///                 SVDComponents retriving
///
template <
    typename InputT,
    typename TransformedT
>
class SVDTransformer : public StandardTransformer<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                                   = StandardTransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SVDTransformer(TransformedT singularvalues, TransformedT singularvectors);
    SVDTransformer(Archive &ar);

    ~SVDTransformer(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SVDTransformer);

    bool operator==(SVDTransformer const &other) const;

    void save(Archive &ar) const override;

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    TransformedT const                               _singularvalues;
    TransformedT const                               _singularvectors;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override;
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         SVDEstimatorImpl
///  \brief         Estimator that reads an annotation created by the `SVDComponentsEstimator`
///                 and creates a `SVDTransformer` object.
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
////InputT and TransformedT are Containers type
class SVDEstimatorImpl : public TransformerEstimator<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, TransformedT>;
    using TransformerType                   = SVDTransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SVDEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~SVDEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SVDEstimatorImpl);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                            _colIndex;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;
    FitResult fit_impl(typename BaseType::InputType const *, size_t) override;
    void complete_training_impl(void) override;

    // MSVC has problems when the definition is separate from the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        //----------------------------------------------------------------------
        using SVDComponentsAnnotationData                = SVDComponentsAnnotationData<TransformedT>;
        using SVDComponentsEstimator                     = SVDComponentsEstimator<InputT, TransformedT, MaxNumTrainingItemsV>;
        // ----------------------------------------------------------------------

        SVDComponentsAnnotationData const &              data(SVDComponentsEstimator::get_annotation_data(this->get_column_annotations(), _colIndex, SVDComponentsEstimatorName));

        return typename BaseType::TransformerUniquePtr(new SVDTransformer<InputT, TransformedT>(data.SingularValues, data.SingularVectors));
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         SVDFeaturizer
///  \brief         Creates the `SVDTransformer` object.
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class SVDEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        SVDComponentsEstimator<InputT, TransformedT, MaxNumTrainingItemsV>,
        Details::SVDEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            SVDComponentsEstimator<InputT, TransformedT, MaxNumTrainingItemsV>,
            Details::SVDEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    SVDEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~SVDEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(SVDEstimator);
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
// |  SVDComponentsAnnotationData
// |
// ----------------------------------------------------------------------
template <typename T>
SVDComponentsAnnotationData<T>::SVDComponentsAnnotationData(T singularvalues, T singularvectors) :
    SingularValues(
        std::move(
            [&singularvalues](void) -> T & {
                if(singularvalues.size() == 0)
                    throw std::invalid_argument("singularvalues");

                return singularvalues;
            }()
        )
    ),
    SingularVectors(
        std::move(
            [&singularvectors](void) -> T & {
                if(singularvectors.size() == 0)
                    throw std::invalid_argument("singularvectors");

                return singularvectors;
            }()
        )
    ) {
}

// ----------------------------------------------------------------------
// |
// |  SVDComponentsEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
SVDComponentsEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::SVDComponentsEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex), true) {
}

template <typename InputT, typename TransformedT>
void ComponentsDetails::SVDTrainingOnlyPolicy<InputT, TransformedT>::fit(InputType const &input) {

    //assume same type but remain InputT and TransformedT for flexibility
    if (!std::is_same<InputT,TransformedT>::value)
        throw std::invalid_argument("InputT should be equal with TransformedT");
    
    _matrix = input;
}

template <typename InputT, typename TransformedT>
SVDComponentsAnnotationData<TransformedT> ComponentsDetails::SVDTrainingOnlyPolicy<InputT, TransformedT>::complete_training(void) {

    //the following code in this function is introduced from RedSVD
    typedef typename TransformedT::Scalar Scalar;
    typedef typename Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> DenseMatrix;

    Eigen::Index rank = (_matrix.rows() < _matrix.cols()) ? _matrix.rows() : _matrix.cols();

    // Gaussian Random Matrix for _matrix^T
    DenseMatrix O(_matrix.rows(), rank);
    sample_gaussian(O);
			
    // Compute Sample Matrix of _matrix^T
    DenseMatrix Y = _matrix.transpose() * std::move(O);
			
    // Orthonormalize Y
    gram_schmidt(Y);
			
    // Range(B) = Range(_matrix^T)
    DenseMatrix B = _matrix * Y;
			
    // Gaussian Random Matrix
    DenseMatrix P(B.cols(), rank);
    sample_gaussian(P);
			
    // Compute Sample Matrix of B
    DenseMatrix Z = B * P;
			
    // Orthonormalize Z
    gram_schmidt(Z);
			
    // Range(C) = Range(B)
    DenseMatrix C = Z.transpose() * std::move(B); 
			
    Eigen::JacobiSVD<DenseMatrix> svdOfC(C, Eigen::ComputeThinV);
			
    // C = USV^T
    // A = Z * U * S * V^T * Y^T()
    _singularvalues = svdOfC.singularValues();
    _singularvectors = std::move(Y) * svdOfC.matrixV();

    return SVDComponentsAnnotationData<TransformedT>(std::move(_singularvalues), std::move(_singularvectors));
}

// ----------------------------------------------------------------------
// |
// |  SVDTransformer
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
SVDTransformer<InputT, TransformedT>::SVDTransformer(TransformedT singularvalues, TransformedT singularvectors) :
    //no validation here because same variable has been validated in annotation class
    _singularvalues(std::move(singularvalues)),
    _singularvectors(std::move(singularvectors)) {
}

template <typename InputT, typename TransformedT>
SVDTransformer<InputT, TransformedT>::SVDTransformer(Archive &ar) :
    SVDTransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data:TODO
            TransformedT                   singularvalues(Traits<TransformedT>::deserialize(ar));
            TransformedT                   singularvectors(Traits<TransformedT>::deserialize(ar));

            return SVDTransformer<InputT, TransformedT>(std::move(singularvalues), std::move(singularvectors));
        }()
    ) {
}

template <typename InputT, typename TransformedT>
bool SVDTransformer<InputT, TransformedT>::operator==(SVDTransformer const &other) const {
    if ((this->_singularvalues - other._singularvalues).norm() > 0.000001f || (this->_singularvectors - other._singularvectors).norm() > 0.000001f)
        return false;

    return true;
}

template <typename InputT, typename TransformedT>
void SVDTransformer<InputT, TransformedT>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data 
    Traits<decltype(_singularvalues)>::serialize(ar, _singularvalues);
    Traits<decltype(_singularvectors)>::serialize(ar, _singularvectors);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
void SVDTransformer<InputT, TransformedT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    if (input.rows() == 0)
        throw std::invalid_argument("Input matrix rows() invalid");
    
    if (input.cols() != _singularvectors.rows()) 
        throw std::invalid_argument("Input matrix cols() invalid");

    callback(std::move(input * _singularvectors));
}

// ----------------------------------------------------------------------
// |
// |  SVDEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
SVDEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::SVDEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "SVDEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return SVDComponentsEstimator<InputT, TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Details::SVDEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::SVDEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
Details::SVDEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::SVDEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
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
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
bool Details::SVDEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
FitResult Details::SVDEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::fit_impl(typename BaseType::InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This will never be called");
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
void Details::SVDEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
