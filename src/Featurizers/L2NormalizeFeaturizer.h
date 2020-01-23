// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "NormalizeFeaturizerBase/NormalizeFeaturizer.h"
namespace Microsoft {
namespace Featurizer {
namespace Featurizers {


/////////////////////////////////////////////////////////////////////////
///  \typedef       L2NormalizeEstimator
///  \brief         Normalize a vector so that its l2 norm is 1
///
template <
    typename IteratorRangeT,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
using L2NormalizeEstimator = NormalizeEstimatorBase<
                                    IteratorRangeT,
                                    Components::Updaters::L2NormUpdater<typename std::iterator_traits<typename std::tuple_element<0, IteratorRangeT>::type>::value_type>,
                                    MaxNumTrainingItemsV>;

} // Featurizers
} // Featurizer
} // Microsoft
