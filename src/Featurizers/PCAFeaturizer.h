// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "Components/PipelineExecutionEstimatorImpl.h"

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wold-style-cast"
#   pragma clang diagnostic ignored "-Wsign-conversion"
#   pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#   pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#   pragma clang diagnostic ignored "-Wextra-semi-stmt"
#   pragma clang diagnostic ignored "-Wmissing-noreturn"
#   pragma clang diagnostic ignored "-Wdocumentation"
#   pragma clang diagnostic ignored "-Wcast-align"
#   pragma clang diagnostic ignored "-Wfloat-equal"
#elif (defined _MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4127)
#endif

#include "../3rdParty/eigen/Eigen/Core"
#include "../3rdParty/eigen/Eigen/Eigen"

#if (defined __clang__)
#   pragma clang diagnostic pop
#elif (defined _MSC_VER)
#   pragma warning(pop)
#endif

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {

namespace {

template <typename T>
inline std::vector<std::vector<T>> EigenMatrixX2VectorContainer(Eigen::MatrixX<T> const & eigenMatrix) {
    std::vector<std::vector<T>> returnVector;
    returnVector.reserve(eigenMatrix.rows());
    for (Eigen::Index rowIdx = 0; rowIdx < eigenMatrix.rows(); ++rowIdx) {
        std::vector<T> tempRow;
        tempRow.reserve(eigenMatrix.cols());
        for (Eigen::Index colIdx = 0; colIdx < eigenMatrix.cols(); ++colIdx) {
            tempRow.emplace_back(std::move(eigenMatrix(rowIdx, colIdx)));
        }
        returnVector.emplace_back(std::move(tempRow));
    }
    return returnVector;
}

template <typename T>
inline std::vector<T> EigenMatrixX2Vector(Eigen::MatrixX<T> const & eigenMatrix) {
    std::vector<T> returnVector;
    returnVector.reserve(eigenMatrix.rows() * eigenMatrix.cols());
    for (Eigen::Index rowIdx = 0; rowIdx < eigenMatrix.rows(); ++rowIdx) { 
        for (Eigen::Index colIdx = 0; colIdx < eigenMatrix.cols(); ++colIdx) {
            returnVector.emplace_back(std::move(eigenMatrix(rowIdx, colIdx)));
        }
    }
    return returnVector;
}

template <typename InputT, typename TransformedT>
inline Eigen::MatrixX<TransformedT> VectorContainer2EigenMatrix(std::vector<InputT> const & vector, size_t numRows, size_t numCols) {
    Eigen::MatrixX<TransformedT> eigenMatrix(numRows, numCols);
    size_t count = 0;
    for (InputT const & val : vector) {
        eigenMatrix(static_cast<Eigen::Index>(count / numCols), static_cast<Eigen::Index>(count % numCols)) = static_cast<TransformedT>(val);
        ++count;
    }
    return eigenMatrix;
}

}

static constexpr char const * const         PCAComponentsEstimatorName("PCAComponentsEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         MatrixDecompositionAnnotationData
///  \brief         Contains PCA components: Eigenvalues and Eigenvectors
template <typename T>
class PCAComponentsAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using EigenValues                                = std::vector<T>;
    //EigenValuesContainer is the type of EigenVector space
    using EigenValuesContainer                       = std::vector<EigenValues>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    //we call these eigen values and vectors, but keep in mind that they are the 
    //decomposition components for covariance matrix not origin matrix
    EigenValues const                                Eigenvalues;
    EigenValuesContainer const                       Eigenvectors;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    PCAComponentsAnnotationData(EigenValues eigenvalues, EigenValuesContainer eigenvectors);
    ~PCAComponentsAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(PCAComponentsAnnotationData);
};

namespace ComponentsDetails {

/////////////////////////////////////////////////////////////////////////
///  \class         PCATrainingOnlyPolicy
///  \brief         `PCAComponentsEstimator` implementation details.
///
template <typename InputT, typename TransformedT>
class PCATrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                                  = InputT;
    using EigenValues                                = std::vector<TransformedT>;
    using EigenValuesContainer                       = std::vector<EigenValues>;
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = PCAComponentsEstimator;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    PCATrainingOnlyPolicy(size_t numRows);

    void fit(InputType const &input);
    PCAComponentsAnnotationData<T> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    size_t const                                     _numRows;

    std::vector<InputType>                           _matrix;
    EigenValues                                      _eigenvalues;
    EigenValuesContainer                             _eigenvectors;
};

} // namespace ComponentsDetails

/////////////////////////////////////////////////////////////////////////
///  \class         PCAComponentsEstimator
///  \brief         This class generates PCAComponentsAnnotationData
///                 by processing input matrix using Eigen
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class PCAComponentsEstimator :
    public TrainingOnlyEstimatorImpl<
        PCATrainingOnlyPolicy<InputT, TransformedT>,
        MaxNumTrainingItemsV
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        TrainingOnlyEstimatorImpl<
            PCATrainingOnlyPolicy<InputT, TransformedT>,
            MaxNumTrainingItemsV
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    PCAComponentsEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, size_t numRows);
    ~PCAComponentsEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(PCAComponentsEstimator);
};


/////////////////////////////////////////////////////////////////////////
///  \class         PCATransformer
///  \brief         Contains PCAComponents and use PCAComponents to project
///                 matrix for dimensionality reduction, also provides 
///                 PCAComponents retriving
///
template <
    typename InputT,
    typename TransformedT
    //If Input is float or double, suggest TransformedT = InputT
    //If Input is Integers, TransformedT = double
>
class PCATransformer : public StandardTransformer<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                                   = StandardTransformer<InputT, TransformedT>;
    using EigenValues                                = std::vector<BaseType::TransformedT>;
    using EigenValuesContainer                       = std::vector<EigenValues>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    PCATransformer(EigenValues eigenvalues, EigenValuesContainer eigenvectors);
    PCATransformer(Archive &ar);

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
    EigenValues const                                _eigenvalues;
    EigenValuesContainer const                       _eigenvectors;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) override;
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         PCAEstimatorImpl
///  \brief         Estimator that reads an annotation created by the `PCAComponentsEstimator`
///                 and creates a `PCATransformer` object.
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class PCAEstimatorImpl : public TransformerEstimator<InputT, TransformedT> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType                          = TransformerEstimator<InputT, TransformedT>;
    using TransformerType                   = PCATransformer<InputT, TransformedT>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    PCAEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~PCAEstimatorImpl(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(PCAEstimatorImpl);

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
        using PCAComponentsAnnotationData                = PCAComponentsAnnotationData<InputT, TransformedT>;
        using PCAComponentsEstimator                     = PCAComponentsEstimator<InputT, TransformedT, MaxNumTrainingItemsV>;
        // ----------------------------------------------------------------------

        PCAComponentsAnnotationData const &              data(PCAComponentsEstimator::get_annotation_data(this->get_column_annotations(), _colIndex, PCAComponentsEstimatorName));

        return typename BaseType::TransformerUniquePtr(new PCATransformer<InputT, TransformedT>(data.Eigenvalues, data.Eigenvectors));
    }
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         PCAFeaturizer
///  \brief         Creates the `PCATransformer` object.
///
template <
    typename InputT,
    typename TransformedT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class PCAEstimator :
    public Components::PipelineExecutionEstimatorImpl<
        PCAComponentsEstimator<InputT, TransformedT, MaxNumTrainingItemsV>,
        Details::PCAEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
    > {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =
        Components::PipelineExecutionEstimatorImpl<
            PCAComponentsEstimator<InputT, TransformedT, MaxNumTrainingItemsV>,
            Details::PCAEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    PCAEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    ~PCAEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(PCAEstimator);
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
// |  PCAComponentsAnnotationData
// |
// ----------------------------------------------------------------------
template <typename T>
PCAComponentsAnnotationData<T>::PCAComponentsAnnotationData(EigenValues eigenvalues, EigenValuesContainer eigenvectors) :
    Eigenvalues(
        std::move(
            [&eigenvalues](void) -> EigenValues & {
                if(eigenvalues.size() == 0)
                    throw std::invalid_argument("eigenvalues");

                return eigenvalues;
            }()
        )
    ),
    Eigenvectors(
        std::move(
            [&eigenvectors](void) -> EigenValuesContainer & {
                if(eigenvectors.size() == 0)
                    throw std::invalid_argument("eigenvectors");

                for (T const & eigenvector : eigenvectors) {
                    if (eigenvector.size() == 0)
                        throw std::invalid_argument("eigenvector");
                }

                return eigenvectors;
            }()
        )
    ) {
}

// ----------------------------------------------------------------------
// |
// |  PCAComponentsEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
PCAComponentsEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::PCAComponentsEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, size_t numRows) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex), true, std::move(numRows)) {
}

// ----------------------------------------------------------------------
// |
// |  Details::PCATrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
ComponentsDetails::PCATrainingOnlyPolicy<InputT, TransformedT>::SVDTrainingOnlyPolicy(size_t numRows) :
    _numRows(
        [&numRows](void) -> size_t & {
            if(numRows == 0)
                throw std::invalid_argument("numRows");

            return numRows;
        }()
    ) {
}

//consider flush in a row each time
template <typename InputT, typename TransformedT>
void ComponentsDetails::PCATrainingOnlyPolicy<InputT, TransformedT>::fit(InputType const &input) {
    _matrix.emplace_back(std::move(input));
}

template <typename InputT, typename TransformedT>
PCAComponentsAnnotationData<InputT, TransformedT> ComponentsDetails::PCATrainingOnlyPolicy<T>::complete_training(void) {

    Eigen::SelfAdjointEigenSolver<Eigen::MatrixX<TransformedT>> eig(
        [&]() -> Eigen::MatrixX<TransformedT> {
            size_t const numColsConst = _matrix.size() / _numRows;
            size_t const numRowsConst = _numRows;
           
            Eigen::MatrixX<TransformedT> M = VectorContainer2EigenMatrix<InputT, TransformedT>(std::move(_matrix), numRowsConst, numColsConst);

            //compute for centered training data
            Eigen::MatrixX<TransformedT> centered = M.rowwise() - M.colwise().mean();
            //compute for covariance matrix
            Eigen::MatrixX<TransformedT> cov = centered.adjoint() * centered;
            //using covariance matrix to compute PCA
            return cov;
        }()
    );

    //PCA uses sigma but sklearn PCA uses sqrt(sigma), this implementation follows sklearn. 
    _eigenvalues = EigenMatrixX2Vector<TransformedT>(eig.eigenvalues().sqrt());
    _eigenvectors = EigenMatrixX2VectorContainer<TransformedT>(eig.eigenvectors());
    
    return PCAComponentsAnnotationData<TransformedT>(std::move(_eigenvalues), std::move(_eigenvectors));
}

// ----------------------------------------------------------------------
// |
// |  PCATransformer
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
PCATransformer<InputT, TransformedT>::PCATransformer(EigenValues eigenvalues, EigenValuesContainer eigenvectors) :
    //no validation here because same variable has been validated in annotation class
    _eigenvalues(std::move(eigenvalues)),
    _eigenvectors(std::move(eigenvectors)) {
}

template <typename InputT, typename TransformedT>
PCATransformer<InputT, TransformedT>::PCATransformer(Archive &ar) :
    PCATransformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            EigenValues             eigenvalues(Traits<EigenValues>::deserialize(ar));
            EigenValuesContainer    eigenvectors(Traits<EigenValuesContainer>::deserialize(ar));

            return PCATransformer<InputT, TransformedT>(std::move(eigenvalues), std::move(eigenvectors));
        }()
    ) {
}

template <typename InputT, typename TransformedT>
bool PCATransformer<InputT, TransformedT>::operator==(PCATransformer const &other) const {

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    
    return this->_eigenvalues == other._eigenvalues
        && this->_span == other._span;

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

}

template <typename InputT, typename TransformedT>
void PCATransformer<InputT, TransformedT>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data
    Traits<decltype(_min)>::serialize(ar, _min);

    // Note that we are serializing the max value rather than just the span so
    // that we can deserialize in a way that is consistent with the constructor's
    // parameters (min, max).
    Traits<decltype(_span)>::serialize(ar, _min + _span);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
void PCATransformer<InputT, TransformedT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    // ----------------------------------------------------------------------
    using InputTraits                       = Traits<InputT>;
    using TransformedTraits                 = Traits<TransformedT>;
    // ----------------------------------------------------------------------

    if(InputTraits::IsNull(input)) {
        callback(TransformedTraits::CreateNullValue());
        return;
    }

#if (defined __clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdouble-promotion"
#   pragma clang diagnostic ignored "-Wfloat-equal"
#endif

    if(_span == static_cast<InputT>(0)) {
        callback(static_cast<TransformedT>(0));
        return;
    }

    callback((static_cast<TransformedT>(input) - _min) / _span);

#if (defined __clang__)
#   pragma clang diagnostic pop
#endif

}

// ----------------------------------------------------------------------
// |
// |  PCAEstimator
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
PCAEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::PCAEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(
        "PCAEstimator",
        pAllColumnAnnotations,
        [pAllColumnAnnotations, colIndex](void) { return Components::MinMaxEstimator<InputT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
        [pAllColumnAnnotations, colIndex](void) { return Details::PCAEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); }
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::PCAEstimatorImpl
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
Details::PCAEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::PCAEstimatorImpl(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType("PCAEstimatorImpl", std::move(pAllColumnAnnotations)),
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
bool Details::PCAEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::begin_training_impl(void) /*override*/ {
    return false;
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
FitResult Details::PCAEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::fit_impl(typename BaseType::InputType const *, size_t) /*override*/ {
    throw std::runtime_error("This will never be called");
}

template <typename InputT, typename TransformedT, size_t MaxNumTrainingItemsV>
void Details::PCAEstimatorImpl<InputT, TransformedT, MaxNumTrainingItemsV>::complete_training_impl(void) /*override*/ {
}

} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
