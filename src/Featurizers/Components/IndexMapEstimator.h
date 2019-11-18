// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "HistogramEstimator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

static constexpr char const * const         IndexMapEstimatorName("IndexMapEstimator");

/////////////////////////////////////////////////////////////////////////
///  \class         IndexMapAnnotationData
///  \brief         Contains an IndexMap where keys point to unique id values.
///
template <typename T>
class IndexMapAnnotationData {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using IndexMap                          = std::unordered_map<T, std::uint32_t>;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    IndexMap const                          Value;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    IndexMapAnnotationData(IndexMap value);
    ~IndexMapAnnotationData(void) = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(IndexMapAnnotationData);
};

template <typename T> typename IndexMapAnnotationData<T>::IndexMap CreateIndexMap(typename HistogramAnnotationData<T>::Histogram const &histogram, typename IndexMapAnnotationData<T>::IndexMap existingValues);

namespace Details {

/////////////////////////////////////////////////////////////////////////
///  \class         IndexMapTrainingOnlyPolicy
///  \brief         `IndexMapEstimator` implementation details.
///
template <typename T, typename EstimatorT>
class IndexMapTrainingOnlyPolicy {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using InputType                         = T;
    using IndexMap                          = typename IndexMapAnnotationData<InputType>::IndexMap;

    // ----------------------------------------------------------------------
    // |
    // |  Public Data
    // |
    // ----------------------------------------------------------------------
    static constexpr char const * const     NameValue = IndexMapEstimatorName;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    IndexMapTrainingOnlyPolicy(IndexMap previousItems);

    void fit(InputType const &input);
    IndexMapAnnotationData<T> complete_training(void);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    IndexMap                                _values;
};

} // namespace Details

/////////////////////////////////////////////////////////////////////////
///  \class         IndexMapEstimator
///  \brief         This class computes the index map for an input column
///                 and creates `IndexMapAnnotationData`.
///
template <
    typename T,
    size_t MaxNumTrainingItemsV=std::numeric_limits<size_t>::max()
>
class IndexMapEstimator :
    public TrainingOnlyEstimatorImpl<
        Details::IndexMapTrainingOnlyPolicy<
            T,
            IndexMapEstimator<T, MaxNumTrainingItemsV>
        >,
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
            Details::IndexMapTrainingOnlyPolicy<
                T,
                IndexMapEstimator<T, MaxNumTrainingItemsV>
            >,
            MaxNumTrainingItemsV
        >;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    IndexMapEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex);
    IndexMapEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, typename IndexMapAnnotationData<T>::IndexMap existingValues);

    ~IndexMapEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(IndexMapEstimator);
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
template <typename T>
typename IndexMapAnnotationData<T>::IndexMap CreateIndexMap(typename HistogramAnnotationData<T>::Histogram const &histogram, typename IndexMapAnnotationData<T>::IndexMap existingValues) {
    // ----------------------------------------------------------------------
    using IndexMap                          = typename IndexMapAnnotationData<T>::IndexMap;
    using Keys                              = std::vector<typename HistogramAnnotationData<T>::Histogram::key_type>;
    // ----------------------------------------------------------------------

    IndexMap                                results(std::move(existingValues));
    Keys                                    keys;

    for(auto const &kvp : histogram) {
        if(results.find(kvp.first) != results.end())
            continue;

        keys.push_back(kvp.first);
    }

    if(keys.empty() == false) {
        sort(keys.begin(), keys.end());
    }

    // There is an annoying problem here. When the reference map contains keys that are bool, we can't actually
    // get a reference to the value as the value is generated on the fly. So, rather than using 'for(auto const &kvp : keys)',
    // use an iterator instead.
    //
    // for(auto const & key : keys) {
    for(typename Keys::iterator iter=keys.begin(); iter != keys.end(); ++iter) {
        std::pair<typename IndexMap::iterator, bool>    result(results.emplace(std::make_pair(*iter, static_cast<typename IndexMap::mapped_type>(results.size()))));

        if(result.first == results.end())
            throw std::runtime_error("Invalid insertion");
    }

    return results;
}

// ----------------------------------------------------------------------
// |
// |  IndexMapAnnotationData
// |
// ----------------------------------------------------------------------
template <typename T>
IndexMapAnnotationData<T>::IndexMapAnnotationData(IndexMap value) :
    Value(std::move(value)) {
}

// ----------------------------------------------------------------------
// |
// |  IndexMapEstimator
// |
// ----------------------------------------------------------------------
template <typename T, size_t MaxNumTrainingItemsV>
IndexMapEstimator<T, MaxNumTrainingItemsV>::IndexMapEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex) :
    IndexMapEstimator(std::move(pAllColumnAnnotations), std::move(colIndex), typename IndexMapAnnotationData<T>::IndexMap()) {
}

template <typename T, size_t MaxNumTrainingItemsV>
IndexMapEstimator<T, MaxNumTrainingItemsV>::IndexMapEstimator(AnnotationMapsPtr pAllColumnAnnotations, size_t colIndex, typename IndexMapAnnotationData<T>::IndexMap existingValues) :
    BaseType(std::move(pAllColumnAnnotations), std::move(colIndex), false, std::move(existingValues)) {
}

// ----------------------------------------------------------------------
// |
// |  Details::IndexMapTrainingOnlyPolicy
// |
// ----------------------------------------------------------------------
template <typename T, typename IndexMapEstimatorT>
Details::IndexMapTrainingOnlyPolicy<T, IndexMapEstimatorT>::IndexMapTrainingOnlyPolicy(IndexMap previousItems) :
    _values(std::move(previousItems)) {
}

template <typename T, typename IndexMapEstimatorT>
void Details::IndexMapTrainingOnlyPolicy<T, IndexMapEstimatorT>::fit(InputType const &) {
    throw std::runtime_error("This will never be called");
}

template <typename T, typename IndexMapEstimatorT>
IndexMapAnnotationData<T> Details::IndexMapTrainingOnlyPolicy<T, IndexMapEstimatorT>::complete_training(void) {
    // ----------------------------------------------------------------------
    using HistogramAnnotationData           = HistogramAnnotationData<T>;
    using HistogramEstimator                = HistogramEstimator<T, IndexMapEstimatorT::MaxNumTrainingItems>;
    // ----------------------------------------------------------------------

    IndexMapEstimatorT const &              estimator(static_cast<IndexMapEstimatorT const &>(*this));
    HistogramAnnotationData const &         data(HistogramEstimator::get_annotation_data(estimator.get_column_annotations(), estimator.get_column_index(), HistogramEstimatorName));

    return IndexMapAnnotationData<T>(CreateIndexMap<T>(data.Value, std::move(_values)));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
