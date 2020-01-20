// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <limits>

#include "TrainingOnlyEstimatorImpl.h"
#include "../../Traits.h"
#include "NormUpdaters.h"
#include "../Structs.h"
namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         VectorNormsEstimatorName("VectorNormsEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         VectorNormsAnnotationData
///  \brief         An annotation class which contains the norms of a matrix
///
template <typename UpdaterType>
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
template <typename T, typename UpdaterType>
class VectorNormsTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------

    using IteratorType = typename std::tuple_element<0, T>::type;
    using ValueType    = typename std::iterator_traits<IteratorType>::value_type;

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
    VectorNormsAnnotationData<UpdaterType> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    std::vector<std::double_t> _norms;
    UpdaterType _updater;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \typedef       VectorNormsEstimator
///  \brief         A training-only class that finds vector-based norms of a matrix
///
template <
    typename InputT,
    typename UpdaterType,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using VectorNormsEstimator                       = TrainingOnlyEstimatorImpl<Details::VectorNormsTrainingOnlyPolicy<InputT, UpdaterType>, MaxNumTrainingItemsV>;

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
template <typename UpdaterType>
VectorNormsAnnotationData<UpdaterType>::VectorNormsAnnotationData(std::vector<std::double_t> norms) :
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
template <typename T, typename UpdaterType>
Details::VectorNormsTrainingOnlyPolicy<T, UpdaterType>::VectorNormsTrainingOnlyPolicy(void) {
}

template <typename T, typename UpdaterType>
void Details::VectorNormsTrainingOnlyPolicy<T, UpdaterType>::fit(InputType const &input) {
    // T is a pair of iterators
    // unpack input to two iterators
    IteratorType & begin = const_cast<IteratorType&>(std::get<0>(input));
    IteratorType const & end = std::get<1>(input);

    if (std::distance(begin, end) < 0) {
        throw std::runtime_error("Input iterators to VectorNormsEstimator are invalid!");
    }
    // null values are handled inside NormUpdater
    while (begin != end) {
        _updater.update(*begin);
        ++begin;
    }
    _norms.emplace_back(static_cast<std::double_t>(_updater.commit()));
    _updater.reset();
}

template <typename T, typename UpdaterType>
VectorNormsAnnotationData<UpdaterType> Details::VectorNormsTrainingOnlyPolicy<T, UpdaterType>::complete_training(void) {
    return VectorNormsAnnotationData<UpdaterType>(std::move(_norms));
}


} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
