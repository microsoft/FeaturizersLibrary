// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include <unordered_map>

#include "TrainingOnlyEstimatorImpl.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         OrderEstimatorName("OrderEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         OrderAnnotationData
///  \brief         Contains a map between unique values and the order in which
///                 those values first appeared.
///
template <typename T>
class OrderAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using OrderMap =
        std::unordered_map<
            T,
            std::uint32_t,
            std::hash<T>,
            typename Traits<T>::key_equal
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    OrderMap const                          Value;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    OrderAnnotationData(OrderMap value);
    ~OrderAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(OrderAnnotationData);
};

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         OrderTrainingOnlyPolicy
///  \brief         `OrderEstimator` implementation details.
///
template <typename T>
class OrderTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = T;
    using OrderMap                          = typename OrderAnnotationData<InputType>::OrderMap;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = OrderEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    OrderTrainingOnlyPolicy(OrderMap previousItems);

    void fit(InputType const &input);
    OrderAnnotationData<T> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    OrderMap                                _values;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         OrderEstimator
///  \brief         Estimator that tracks the order in which unique items
///                 appeared during training.
///
template <
    typename T,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class OrderEstimator : public TrainingOnlyEstimatorImpl<Details::OrderTrainingOnlyPolicy<T>, MaxNumTrainingItemsV> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using BaseType =                        TrainingOnlyEstimatorImpl<Details::OrderTrainingOnlyPolicy<T>, MaxNumTrainingItemsV>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    OrderEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    OrderEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, typename OrderAnnotationData<T>::OrderMap existingValues);

    ~OrderEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(OrderEstimator);
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
// |  OrderAnnotationData
// |
// ----------------------------------------------------------------------
template <typename T>
OrderAnnotationData<T>::OrderAnnotationData(OrderMap value) :
    Value(
        std::move(
            [&value](void) -> OrderMap & {
                if(value.empty())
                    throw std::invalid_argument("value");

                return value;
            }()
        )
    ) {
}

// ----------------------------------------------------------------------
// |
// |  Details::OrderTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T>
Details::OrderTrainingOnlyPolicy<T>::OrderTrainingOnlyPolicy(OrderMap previousItems) :
    _values(std::move(previousItems)) {
}

template <typename T>
void Details::OrderTrainingOnlyPolicy<T>::fit(InputType const &input) {
    // This call to emplace will return a pair with an element set to false if the
    // input was already in the map. This is acceptable in this case as we don't
    // want to overwrite the value anyway.
    _values.emplace(input, static_cast<std::uint32_t>(_values.size()));
}

template <typename T>
OrderAnnotationData<T> Details::OrderTrainingOnlyPolicy<T>::complete_training(void) {
    return OrderAnnotationData<T>(std::move(_values));
}

// ----------------------------------------------------------------------
// |
// |  OrderEstimator
// |
// ----------------------------------------------------------------------
template <typename T, size_t MaxNumTrainingItemsV>
OrderEstimator<T, MaxNumTrainingItemsV>::OrderEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex), true, typename OrderAnnotationData<T>::OrderMap()) {
}

template <typename T, size_t MaxNumTrainingItemsV>
OrderEstimator<T, MaxNumTrainingItemsV>::OrderEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, typename OrderAnnotationData<T>::OrderMap existingValues) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex), true, std::move(existingValues)) {
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
