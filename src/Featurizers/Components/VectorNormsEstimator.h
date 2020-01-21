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


template <typename T>
struct IsIteratorPair {
    static constexpr bool const value = false;
};
template <typename T>
struct IsIteratorPair<std::tuple<T, T>> {
    static constexpr bool const value = true;
};
template <typename T>
struct IsIteratorPair<std::pair<T, T>> {
    static constexpr bool const value = true;
};

/////////////////////////////////////////////////////////////////////////
///  \class         VectorNormsAnnotationData
///  \brief         An annotation class which contains the norms of a matrix
///
template <typename UpdaterT>
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
template <typename IteratorRangeT, typename UpdaterT>
class VectorNormsTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------

    // checks if IteratorRangeT is a pair of iterators
    static_assert(IsIteratorPair<IteratorRangeT>::value, "VectorNormsEstimator input type need to a pair of iterators of same type!");

    using InputType = IteratorRangeT;

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
    VectorNormsAnnotationData<UpdaterT> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------
    using IteratorType = typename std::tuple_element<0, IteratorRangeT>::type;
    using ValueType    = typename std::iterator_traits<IteratorType>::value_type;

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::vector<std::double_t> _norms;
    UpdaterT                   _updater;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \typedef       VectorNormsEstimator
///  \brief         A training-only class that finds vector-based norms of a matrix
///
template <
    typename IteratorRangeT,
    typename UpdaterT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using VectorNormsEstimator                       = TrainingOnlyEstimatorImpl<Details::VectorNormsTrainingOnlyPolicy<IteratorRangeT, UpdaterT>, MaxNumTrainingItemsV>;

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
template <typename UpdaterT>
VectorNormsAnnotationData<UpdaterT>::VectorNormsAnnotationData(std::vector<std::double_t> norms) :
    Norms(std::move(norms)) {
        if (Norms.empty()) {
            throw std::invalid_argument("No norm is passed in to VectorNormsAnnotationData!");
        }
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
template <typename IteratorRangeT, typename UpdaterT>
Details::VectorNormsTrainingOnlyPolicy<IteratorRangeT, UpdaterT>::VectorNormsTrainingOnlyPolicy(void) {
}

template <typename IteratorRangeT, typename UpdaterT>
void Details::VectorNormsTrainingOnlyPolicy<IteratorRangeT, UpdaterT>::fit(InputType const &input) {
    // T is a pair of iterators
    // unpack input to two iterators
    IteratorType begin = std::get<0>(input);
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

template <typename IteratorRangeT, typename UpdaterT>
VectorNormsAnnotationData<UpdaterT> Details::VectorNormsTrainingOnlyPolicy<IteratorRangeT, UpdaterT>::complete_training(void) {
    return VectorNormsAnnotationData<UpdaterT>(std::move(_norms));
}


} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
