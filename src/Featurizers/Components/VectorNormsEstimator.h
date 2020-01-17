// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>

#include "TrainingOnlyEstimatorImpl.h"
#include "../../Traits.h"
#include "NormUpdaters.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         VectorNormsEstimatorName("VectorNormsEstimator");

namespace TypeSelector {

// updater type selector is created to select different updater based on input parameter
template <typename T, NormType NormT>
struct UpdaterTypeSelector {
};
template <typename T>
struct UpdaterTypeSelector<T, NormType::L1> {
    using type = Updaters::L1NormUpdater<T>;
};

template <typename T>
struct UpdaterTypeSelector<T, NormType::L2> {
    using type = Updaters::L2NormUpdater<T>;
};

template <typename T>
struct UpdaterTypeSelector<T, NormType::MAX> {
    using type = Updaters::MaxNormUpdater<T>;
};

} // namespace TypeSelector



/////////////////////////////////////////////////////////////////////////
///  \class         VectorNormsAnnotationData
///  \brief         An annotation class which contains the norms of a matrix
///
template <NormType NormT>
class VectorNormsAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    std::vector<std::double_t> const Norms;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    VectorNormsAnnotationData(std::vector<std::double_t> norms);
    ~VectorNormsAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(VectorNormsAnnotationData);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         VectorNormsTrainingOnlyPolicy
///  \brief         `VectorNormsEstimator` implementation details.
///
template <typename T, NormType NormT>
class VectorNormsTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------

    // using ValueType = typename std::iterator_traits<std::tuple_element<0, T>::type>::value_type;
    using ValueType = typename T::value_type;
    using InputType = T;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = VectorNormsEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    VectorNormsTrainingOnlyPolicy(void);

    void fit(InputType const &input);
    VectorNormsAnnotationData<NormT> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    std::vector<std::double_t> _norms;
    typename TypeSelector::UpdaterTypeSelector<ValueType, NormT>::type _updater;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    void fit_impl(InputType const &input, std::true_type /*is_optional*/);
    void fit_impl(InputType const &input, std::false_type /*is_optional*/);
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \typedef       VectorNormsEstimator
///  \brief         A training-only class that finds vector-based norms of a matrix
///
template <
    typename InputT,
    NormType NormT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using VectorNormsEstimator                       = TrainingOnlyEstimatorImpl<Details::VectorNormsTrainingOnlyPolicy<InputT, NormT>, MaxNumTrainingItemsV>;

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
// |  VectorNormsAnnotationData
// |
// ----------------------------------------------------------------------
template <NormType NormT>
VectorNormsAnnotationData<NormT>::VectorNormsAnnotationData(std::vector<std::double_t> norms) :
    Norms(std::move(norms)) {
        for (auto const & norm : Norms) {
            if (norm < 0) {
                throw std::invalid_argument("Norms shouldn't be less than 0!");
            }
        }
}

// ----------------------------------------------------------------------
// |
// |  Details::VectorNormsTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T, NormType NormT>
Details::VectorNormsTrainingOnlyPolicy<T, NormT>::VectorNormsTrainingOnlyPolicy(void) {
}

template <typename T, NormType NormT>
void Details::VectorNormsTrainingOnlyPolicy<T, NormT>::fit(InputType const &input) {
    // T is a pair of iterators
    fit_impl(input, std::integral_constant<bool, Microsoft::Featurizer::Traits<ValueType>::IsNullableType>());
}

template <typename T, NormType NormT>
VectorNormsAnnotationData<NormT> Details::VectorNormsTrainingOnlyPolicy<T, NormT>::complete_training(void) {
    return VectorNormsAnnotationData<NormT>(std::move(_norms));
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
template <typename T, NormType NormT>
void Details::VectorNormsTrainingOnlyPolicy<T, NormT>::fit_impl(InputType const &input, std::true_type) {
    // ----------------------------------------------------------------------
    using TheseTraits                       = Microsoft::Featurizer::Traits<ValueType>;
    // ----------------------------------------------------------------------

    for (auto const & value : input) {
        if(!TheseTraits::IsNull(value))
            _updater.update(TheseTraits::GetNullableValue(value));
    }
    _norms.emplace_back(static_cast<std::double_t>(_updater.commit()));
    _updater.reset();
}

template <typename T, NormType NormT>
void Details::VectorNormsTrainingOnlyPolicy<T, NormT>::fit_impl(InputType const &input, std::false_type) {
    for (auto const & value : input) {
        _updater.update(value);
    }
    _norms.emplace_back(static_cast<std::double_t>(_updater.commit()));
    _updater.reset();
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
