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

static constexpr char const * const         PCAComponentsEstimatorName("PCAComponentsEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         MatrixDecompositionAnnotationData
///  \brief         Contains PCA components: Eigenvalues and Eigenvectors
template <typename T>
class PCAComponentsAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------

    T const                                          Eigenvalues;
    T const                                          Eigenvectors;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    PCAComponentsAnnotationData(T eigenvalues, T eigenvectors);
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
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const    NameValue = PCAComponentsEstimatorName;
    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------

    void fit(InputType const &input);
    PCAComponentsAnnotationData<TransformedT> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    TransformedT                                     _matrix;
    TransformedT                                     _eigenvalues;
    TransformedT                                     _eigenvectors;
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
    public Components::TrainingOnlyEstimatorImpl<
        ComponentsDetails::PCATrainingOnlyPolicy<InputT, TransformedT>,
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
            ComponentsDetails::PCATrainingOnlyPolicy<InputT, TransformedT>,
            MaxNumTrainingItemsV
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    PCAComponentsEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
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
>
class PCATransformer : public StandardTransformer<InputT, TransformedT> {
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
    PCATransformer(TransformedT eigenvalues, TransformedT eigenvectors);
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
    TransformedT const                               _eigenvalues;
    TransformedT const                               _eigenvectors;

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
////InputT and TransformedT are Containers type
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
        using PCAComponentsAnnotationData                = PCAComponentsAnnotationData<TransformedT>;
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
PCAComponentsAnnotationData<T>::PCAComponentsAnnotationData(T eigenvalues, T eigenvectors) :
    Eigenvalues(
        std::move(
            [&eigenvalues](void) -> T & {
                if(eigenvalues.size() == 0)
                    throw std::invalid_argument("eigenvalues");

                return eigenvalues;
            }()
        )
    ),
    Eigenvectors(
        std::move(
            [&eigenvectors](void) -> T & {
                if(eigenvectors.size() == 0)
                    throw std::invalid_argument("eigenvectors");

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
PCAComponentsEstimator<InputT, TransformedT, MaxNumTrainingItemsV>::PCAComponentsEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex), true) {
}

template <typename InputT, typename TransformedT>
void ComponentsDetails::PCATrainingOnlyPolicy<InputT, TransformedT>::fit(InputType const &input) {

    //assume same type but remain InputT and TransformedT for flexibility
    if (!std::is_same<InputT,TransformedT>::value)
        throw std::invalid_argument("InputT should be equal with TransformedT");
    
    _matrix = input;
}

template <typename InputT, typename TransformedT>
PCAComponentsAnnotationData<TransformedT> ComponentsDetails::PCATrainingOnlyPolicy<InputT, TransformedT>::complete_training(void) {

    Eigen::SelfAdjointEigenSolver<TransformedT> eig(
        [&]() -> TransformedT {
            //compute for centered training data
            TransformedT centered = _matrix.rowwise() - _matrix.colwise().mean();
            //compute for covariance matrix
            TransformedT cov = centered.adjoint() * centered;
            //using covariance matrix to compute PCA
            return cov;
        }()
    );

    //PCA uses sigma but sklearn PCA uses sqrt(sigma), this implementation follows original principle. 
    _eigenvalues = eig.eigenvalues();
    _eigenvectors = eig.eigenvectors();
    
    return PCAComponentsAnnotationData<TransformedT>(std::move(_eigenvalues), std::move(_eigenvectors));
}

// ----------------------------------------------------------------------
// |
// |  PCATransformer
// |
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
PCATransformer<InputT, TransformedT>::PCATransformer(TransformedT eigenvalues, TransformedT eigenvectors) :
    //no validation here because same variable has been validated in annotation class
    _eigenvalues(std::move(eigenvalues)),
    _eigenvectors(std::move(eigenvectors)) {
}

//TODO:
// template <typename InputT, typename TransformedT>
// PCATransformer<InputT, TransformedT>::PCATransformer(Archive &ar) :
//     PCATransformer(
//         [&ar](void) {
//             // Version
//             std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
//             std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

//             if(majorVersion != 1 || minorVersion != 0)
//                 throw std::runtime_error("Unsupported archive version");

//             // Data:TODO
//             TransformedT                   eigenvalues(Traits<TransformedT>::deserialize(ar));
//             TransformedT                   eigenvectors(Traits<TransformedT>::deserialize(ar));

//             return PCATransformer<InputT, TransformedT>(std::move(eigenvalues), std::move(eigenvectors));
//         }()
//     ) {
// }

template <typename InputT, typename TransformedT>
bool PCATransformer<InputT, TransformedT>::operator==(PCATransformer const &other) const {
    if ((this->_eigenvalues - other._eigenvalues).norm() > 0.000001f || (this->_eigenvectors - other._eigenvectors).norm() > 0.000001f)
        return false;

    return true;
}

template <typename InputT, typename TransformedT>
void PCATransformer<InputT, TransformedT>::save(Archive &ar) const /*override*/ {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data TODO
    // Traits<decltype(_eigenvalues)>::serialize(ar, _eigenvalues);
    // Traits<decltype(_eigenvectors)>::serialize(ar, _eigenvectors);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename InputT, typename TransformedT>
void PCATransformer<InputT, TransformedT>::execute_impl(typename BaseType::InputType const &input, typename BaseType::CallbackFunction const &callback) /*override*/ {
    callback(std::move(input * _eigenvectors.transpose()));
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
        [pAllColumnAnnotations, colIndex](void) { return PCAComponentsEstimator<InputT, TransformedT, MaxNumTrainingItemsV>(std::move(pAllColumnAnnotations), std::move(colIndex)); },
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
