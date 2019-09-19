// ----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License
// ----------------------------------------------------------------------
#pragma once

#include "../../Archive.h"
#include "../../Featurizer.h"
#include "../../Traits.h"
#include "PipelineExecutionEstimatorImpl.h"
#include "TimeSeriesFrequencyEstimator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

enum class TimeSeriesImputeStrategy : unsigned char {
    Forward = 1,                            ///< TODO: Document this
    Backward,                               ///< TODO: Document this
    Interpolate,                            ///< TODO: Document this

    NumValues
};

inline bool IsValid(TimeSeriesImputeStrategy value) {
    return value == TimeSeriesImputeStrategy::Forward
        || value == TimeSeriesImputeStrategy::Backward
        || value == TimeSeriesImputeStrategy::Interpolate;
}

using TimeSeriesImputerEstimatorInputType = std::tuple<
    std::chrono::system_clock::time_point,
    std::vector<std::string>,
    std::vector<nonstd::optional<std::string>>
> const &;

using TimeSeriesImputerEstimatorTransformedType = std::vector<
    std::tuple<
        bool,
        std::chrono::system_clock::time_point,
        std::vector<std::string>,
        std::vector<nonstd::optional<std::string>>
    >
>;

/////////////////////////////////////////////////////////////////////////
///  \class         TimeSeriesImputerEstimator
///  \brief         This class retrieves TimeSeriesFrequencyAnnotation and
///                 Creates Imputation transformers
///
class TimeSeriesImputerEstimator : public TransformerEstimator<TimeSeriesImputerEstimatorInputType, TimeSeriesImputerEstimatorTransformedType> {
public:
    // ----------------------------------------------------------------------
    // |
    // |  Public Types
    // |
    // ----------------------------------------------------------------------
    using TimePointType                     = std::chrono::system_clock::time_point;
    using FrequencyType                     = std::chrono::system_clock::duration;
    using KeyType                           = std::vector<std::string>;
    using ColsToImputeType                  = std::vector<nonstd::optional<std::string>>;
    using OutputRowType                     = std::tuple<bool,std::chrono::system_clock::time_point, std::vector<std::string>, std::vector<nonstd::optional<std::string>>>;
    using BaseType                          = TransformerEstimator<TimeSeriesImputerEstimatorInputType, TimeSeriesImputerEstimatorTransformedType>;


    class Transformer : public QueuedTransformer<typename BaseType::InputType,typename BaseType::TransformedType> {
    public:

        using TraitsStr                        = Traits<typename std::remove_cv<typename std::remove_reference<std::string>::type>::type>;
        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        Transformer(FrequencyType value, std::vector<TypeId> colsToImputeDataTypes, TimeSeriesImputeStrategy tsImputeStrategy);
        Transformer(typename BaseType::Transformer::Archive & ar);
        ~Transformer(void) override = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Transformer);

        typename BaseType::TransformedType execute(typename BaseType::InputType input) override;

        typename BaseType::TransformedType flush(void) override;

        void save(typename BaseType::Transformer::Archive & ar) const override;

    private:
        // ----------------------------------------------------------------------
        // |
        // |  Private Data
        // |
        // ----------------------------------------------------------------------
        FrequencyType const                           _frequency;
        std::vector<TypeId> const                     _colsToImputeDataTypes;
        TimeSeriesImputeStrategy const                _tsImputeStrategy;
    };

    using TransformerType                   = Transformer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TimeSeriesImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations,std::vector<TypeId> colsToImputeDataTypes={TypeId::Float64},TimeSeriesImputeStrategy tsImputeStrategy = TimeSeriesImputeStrategy::Forward);
    ~TimeSeriesImputerEstimator(void) override = default;

    FEATURIZER_MOVE_CONSTRUCTOR_ONLY(TimeSeriesImputerEstimator);

private:
    // ----------------------------------------------------------------------
    // |
    // |  Private Types
    // |
    // ----------------------------------------------------------------------

    // ----------------------------------------------------------------------
    // |
    // |  Private Data
    // |
    // ----------------------------------------------------------------------
    std::vector<TypeId> const                       _colsToImputeDataTypes;
    TimeSeriesImputeStrategy const                  _tsImputeStrategy;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------

    // MSVC has problems when the function is defined outside of the declaration
    Estimator::FitResult fit_impl(typename BaseType::BaseType::FitBufferInputType *, size_t) override {
        throw std::runtime_error("This should never be called as this class will not be used during training");
    }

    Estimator::FitResult complete_training_impl(void) override;

    // MSVC has problems when the function is defined outside of the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        AnnotationMaps const &                          maps(Estimator::get_column_annotations());
        AnnotationMap const &                           annotations(maps[0]);
        AnnotationMap::const_iterator const &           iterAnnotations(annotations.find("TimeSeriesFrequencyEstimator"));
        if(iterAnnotations == annotations.end())
            throw std::runtime_error("Couldn't retrieve Annotation.");
        Annotation const &                              annotation(*iterAnnotations->second[0]);
        assert(dynamic_cast<TimeSeriesFrequencyAnnotation const *>(&annotation));

        TimeSeriesFrequencyAnnotation const &       TSFreqAnnotation(static_cast<TimeSeriesFrequencyAnnotation const &>(annotation));
        return std::make_unique<Transformer>(TSFreqAnnotation.Value, std::move(_colsToImputeDataTypes), std::move(_tsImputeStrategy));
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
// |  TimeSeriesImputerEstimator
// |
// ----------------------------------------------------------------------
TimeSeriesImputerEstimator::TimeSeriesImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations,std::vector<TypeId> colsToImputeDataTypes,TimeSeriesImputeStrategy tsImputeStrategy) :
    BaseType("TimeSeriesImputerEstimator", std::move(pAllColumnAnnotations), true),
    _colsToImputeDataTypes(std::move(colsToImputeDataTypes)),
    _tsImputeStrategy(std::move(tsImputeStrategy)){
}

Estimator::FitResult TimeSeriesImputerEstimator::complete_training_impl(void) {
    throw std::runtime_error("This should never be called as this class will not be used during training");
}

// ----------------------------------------------------------------------
// |
// |  TimeSeriesImputerEstimator::Transformer
// |
// ----------------------------------------------------------------------
TimeSeriesImputerEstimator::Transformer::Transformer(TimeSeriesImputerEstimator::FrequencyType value, std::vector<TypeId> colsToImputeDataTypes,TimeSeriesImputeStrategy tsImputeStrategy) :
    _frequency(std::move(value)),
    _colsToImputeDataTypes(std::move(colsToImputeDataTypes)),
    _tsImputeStrategy(std::move(tsImputeStrategy)) {

    if(_colsToImputeDataTypes.size() == 0)
        throw std::runtime_error("Column metadata can't be empty.");

}

TimeSeriesImputerEstimator::Transformer::Transformer(typename BaseType::Transformer::Archive & ar) :
    _frequency(std::chrono::system_clock::duration::max().count()),
    _colsToImputeDataTypes({TypeId::Float64}),
    _tsImputeStrategy(TimeSeriesImputeStrategy::Forward) {
    if(Traits<std::uint8_t>::deserialize(ar) != 1)
        throw std::runtime_error("Invalid transformer version");
}

typename TimeSeriesImputerEstimator::BaseType::TransformedType TimeSeriesImputerEstimator::Transformer::execute(typename BaseType::InputType input) {

    return {std::tuple_cat(std::make_tuple(false),input)};
}

typename TimeSeriesImputerEstimator::BaseType::TransformedType TimeSeriesImputerEstimator::Transformer::flush() {

    return typename TimeSeriesImputerEstimator::BaseType::TransformedType();
}

void  TimeSeriesImputerEstimator::Transformer::save(typename  TimeSeriesImputerEstimator::BaseType::Transformer::Archive & ar) const {
    Traits<std::uint8_t>::serialize(ar, 1); // Current version
}


} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
