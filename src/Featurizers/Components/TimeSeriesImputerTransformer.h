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
#include "TimeSeriesMedianEstimator.h"

namespace Microsoft {
namespace Featurizer {
namespace Featurizers {
namespace Components {

enum class TimeSeriesImputeStrategy : uint8_t {
    Forward = 1,                            ///< TODO: Document this
    Backward,                               ///< TODO: Document this
    Median,                                 ///< TODO: Document this
    Interpolate,                            ///< TODO: Document this

    NumValues
};

inline bool IsValid(TimeSeriesImputeStrategy value) {
    return value == TimeSeriesImputeStrategy::Forward
        || value == TimeSeriesImputeStrategy::Backward
        || value == TimeSeriesImputeStrategy::Median
        || value == TimeSeriesImputeStrategy::Interpolate;
}

using TimeSeriesImputerEstimatorInputType = std::tuple<
    std::chrono::system_clock::time_point,
    std::vector<std::string>,
    std::vector<nonstd::optional<std::string>>
>;

using TimeSeriesImputerEstimatorTransformedType = std::tuple<
        bool,
        std::chrono::system_clock::time_point,
        std::vector<std::string>,
        std::vector<nonstd::optional<std::string>>
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
    //std::chrono::system_clock::duration has different specializations of std::chrono::duration
    //in Windows and Linux. So for serDe we convert frequency to this specific type.
    using SerDeDurationType = std::chrono::duration<int64_t, std::ratio<1,1000000000>>;


    class Transformer : public Microsoft::Featurizer::Transformer<typename BaseType::InputType,typename BaseType::TransformedType> {
    public:

        using StrTraits                     = Traits<std::string>;
        using ThisBaseType                  = Microsoft::Featurizer::Transformer<typename BaseType::InputType,typename BaseType::TransformedType>;

        // ----------------------------------------------------------------------
        // |
        // |  Public Methods
        // |
        // ----------------------------------------------------------------------
        Transformer(FrequencyType value, std::vector<TypeId> colsToImputeDataTypes, TimeSeriesImputeStrategy tsImputeStrategy, bool supressError, std::map<KeyType,std::vector<double_t>> medianValues);
        Transformer(Archive & ar);
        ~Transformer(void) override = default;

        FEATURIZER_MOVE_CONSTRUCTOR_ONLY(Transformer);

        bool operator==(Transformer const &other) const;

        void save(Archive & ar) const override;

        // ----------------------------------------------------------------------
        // |
        // |  Public Data
        // |
        // ----------------------------------------------------------------------
        FrequencyType const                             _frequency;
        std::vector<TypeId> const                       _colsToImputeDataTypes;
        TimeSeriesImputeStrategy const                  _tsImputeStrategy;
        std::map<KeyType,std::vector<double_t>> const   _medianValues;
        bool const                                      _supressError;

    private:
        // ----------------------------------------------------------------------
        // |
        // |  Private Data
        // |
        // ----------------------------------------------------------------------
        std::map<KeyType,OutputRowType>                                     _lastRowtracker;
        std::map<KeyType,std::vector<BaseType::TransformedType>>            _buffer;

        // ----------------------------------------------------------------------
        // |
        // |  Private Methods
        // |
        // ----------------------------------------------------------------------
        void execute_impl(typename ThisBaseType::InputType const &input, typename ThisBaseType::CallbackFunction const &callback) override;
        void flush_impl(typename ThisBaseType::CallbackFunction const &callback) override;

        std::vector<typename BaseType::TransformedType> generate_rows(typename ThisBaseType::InputType const &input, TimePointType const & lastObservedTP);
        void impute(ColsToImputeType & prev, ColsToImputeType & current);
        bool no_nulls(ColsToImputeType const & input);
        void bfill(typename ThisBaseType::InputType const &input, typename ThisBaseType::CallbackFunction const &callback);
        void ffill_or_median(typename ThisBaseType::InputType const &input, typename ThisBaseType::CallbackFunction const &callback);
    };

    using TransformerType                   = Transformer;

    // ----------------------------------------------------------------------
    // |
    // |  Public Methods
    // |
    // ----------------------------------------------------------------------
    TimeSeriesImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations,std::vector<TypeId> colsToImputeDataTypes,TimeSeriesImputeStrategy tsImputeStrategy, bool supressError);
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
    bool const                                      _supressError;

    // ----------------------------------------------------------------------
    // |
    // |  Private Methods
    // |
    // ----------------------------------------------------------------------
    bool begin_training_impl(void) override;

    // MSVC has problems when the function is defined outside of the declaration
    FitResult fit_impl(typename BaseType::InputType const *, size_t) override {
        throw std::runtime_error("This should never be called as this class will not be used during training");
    }

    void complete_training_impl(void) override;

    // MSVC has problems when the function is defined outside of the declaration
    typename BaseType::TransformerUniquePtr create_transformer_impl(void) override {
        AnnotationMaps const &                          maps(Estimator::get_column_annotations());
        AnnotationMap const &                           annotations(maps[0]);

        AnnotationMap::const_iterator const &           tsFreqIter(annotations.find("TimeSeriesFrequencyEstimator"));
        if(tsFreqIter == annotations.end())
            throw std::runtime_error("Couldn't retrieve Frequency Annotation.");
        Annotation const &                              freqAnnotation(*tsFreqIter->second[0]);
        assert(dynamic_cast<TimeSeriesFrequencyAnnotation const *>(&freqAnnotation));
        TimeSeriesFrequencyAnnotation const &           tsFreqAnnotation(static_cast<TimeSeriesFrequencyAnnotation const &>(freqAnnotation));

        AnnotationMap::const_iterator const &           tsMedianIter(annotations.find("TimeSeriesMedianEstimator"));
        if(tsMedianIter == annotations.end())
            throw std::runtime_error("Couldn't retrieve Median Annotation.");
        Annotation const &                              medianAnnotation(*tsMedianIter->second[0]);
        assert(dynamic_cast<TimeSeriesMedianAnnotation const *>(&medianAnnotation));
        TimeSeriesMedianAnnotation const &              tsMedianAnnotation(static_cast<TimeSeriesMedianAnnotation const &>(medianAnnotation));

        return typename BaseType::TransformerUniquePtr(new Transformer(tsFreqAnnotation.Value, std::move(_colsToImputeDataTypes), std::move(_tsImputeStrategy), std::move(_supressError), tsMedianAnnotation.Value));
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
inline TimeSeriesImputerEstimator::TimeSeriesImputerEstimator(AnnotationMapsPtr pAllColumnAnnotations,std::vector<TypeId> colsToImputeDataTypes,TimeSeriesImputeStrategy tsImputeStrategy,bool supressError) :
    BaseType("TimeSeriesImputerEstimator", std::move(pAllColumnAnnotations)),
    _colsToImputeDataTypes(std::move(colsToImputeDataTypes)),
    _tsImputeStrategy(
        std::move(
            [&tsImputeStrategy](void) -> TimeSeriesImputeStrategy & {
                if(IsValid(tsImputeStrategy) == false)
                    throw std::invalid_argument("'tsImputStrategy' is not valid");

                return tsImputeStrategy;
            }()
        )
    ),
    _supressError(std::move(supressError)) {

        if(_tsImputeStrategy == TimeSeriesImputeStrategy::Median && _supressError == false) {
            // Verify that all col types are double/float
            for(auto const & colType : _colsToImputeDataTypes) {
                if(TimeSeriesMedianEstimator::DoesColTypeSupportMedian(colType) == false)
                    throw std::runtime_error("Only Numeric type columns are supported for ImputationStrategy median. (use suppressError flag to skip imputing non-numeric types)");
            }
        }

}

inline bool TimeSeriesImputerEstimator::begin_training_impl(void) /*override*/ {
    return false;
}

inline void TimeSeriesImputerEstimator::complete_training_impl(void) /*override */ {
}

// ----------------------------------------------------------------------
// |
// |  TimeSeriesImputerEstimator::Transformer
// |
// ----------------------------------------------------------------------
inline TimeSeriesImputerEstimator::Transformer::Transformer(TimeSeriesImputerEstimator::FrequencyType value, std::vector<TypeId> colsToImputeDataTypes,TimeSeriesImputeStrategy tsImputeStrategy, bool supressError, std::map<KeyType,std::vector<double_t>> medianValues) :
    _frequency(std::move(value)),
    _colsToImputeDataTypes(std::move(colsToImputeDataTypes)),
    _tsImputeStrategy(std::move(tsImputeStrategy)),
    _medianValues(std::move(medianValues)),
    _supressError(std::move(supressError)) {

    if(_colsToImputeDataTypes.size() == 0)
        throw std::runtime_error("Column metadata can't be empty.");

    if(_frequency == std::chrono::system_clock::duration::max())
        throw std::runtime_error("Frequency couldn't be inferred from training data.");

}

inline TimeSeriesImputerEstimator::Transformer::Transformer(Archive & ar) :
    TimeSeriesImputerEstimator::Transformer(
        [&ar](void) {
            // Version
            std::uint16_t                   majorVersion(Traits<std::uint16_t>::deserialize(ar));
            std::uint16_t                   minorVersion(Traits<std::uint16_t>::deserialize(ar));

            if(majorVersion != 1 || minorVersion != 0)
                throw std::runtime_error("Unsupported archive version");

            // Data
            std::chrono::system_clock::duration         duration(Traits<std::chrono::system_clock::duration>::deserialize(ar));
            std::vector<TypeId>                         colsToImputeTypes(
                [&ar](void) {
                    // ----------------------------------------------------------------------
                    using TypeIdUnderlyingType          = typename std::underlying_type<TypeId>::type;
                    // ----------------------------------------------------------------------

                    std::vector<TypeIdUnderlyingType>   rawTypes(Traits<std::vector<TypeIdUnderlyingType>>::deserialize(ar));
                    std::vector<TypeId>                 results;

                    results.reserve(rawTypes.size());

                    for(auto const &raw : rawTypes) {
                        if(IsValid(static_cast<TypeId>(raw)) == false)
                            throw std::runtime_error("Invalid type");

                        results.emplace_back(TypeId(raw));
                    }

                    return results;
                }()
            );

            TimeSeriesImputeStrategy                    strategy(
                [&ar](void) {
                    // ----------------------------------------------------------------------
                    using UnderlyingType                = typename std::underlying_type<TimeSeriesImputeStrategy>::type;
                    // ----------------------------------------------------------------------

                    UnderlyingType          raw(Traits<UnderlyingType>::deserialize(ar));

                    if(IsValid(static_cast<TimeSeriesImputeStrategy>(raw)) == false)
                        throw std::runtime_error("Invalid type");

                    return static_cast<TimeSeriesImputeStrategy>(raw);
                }()
            );

            std::map<KeyType, std::vector<double_t>>    medianValues(Traits<std::map<KeyType, std::vector<double_t>>>::deserialize(ar));
            bool                                        suppressError(Traits<bool>::deserialize(ar));

            return Transformer(
                std::move(duration),
                std::move(colsToImputeTypes),
                std::move(strategy),
                std::move(suppressError),
                std::move(medianValues)
            );
        }()
    ) {
}

inline bool TimeSeriesImputerEstimator::Transformer::operator==(Transformer const &other) const {
    return _frequency == other._frequency
        && _colsToImputeDataTypes == other._colsToImputeDataTypes
        && _tsImputeStrategy == other._tsImputeStrategy
        && _medianValues == other._medianValues
        && _supressError == other._supressError;
}

inline void TimeSeriesImputerEstimator::Transformer::save(Archive & ar) const {
    // Version
    Traits<std::uint16_t>::serialize(ar, 1); // Major
    Traits<std::uint16_t>::serialize(ar, 0); // Minor

    // Data

    //_frequency
    Traits<std::chrono::system_clock::duration>::serialize(ar,_frequency);

    //_colsToImputeDataTypes
    using TypeIdUnderlyingType = std::underlying_type<TypeId>::type;
    std::vector<TypeIdUnderlyingType> _colsToImputeDataTypesUnWrapped;
    for (auto imputeStrategy : _colsToImputeDataTypes)
        _colsToImputeDataTypesUnWrapped.push_back(static_cast<TypeIdUnderlyingType>(imputeStrategy));
    Traits<std::vector<TypeIdUnderlyingType>>::serialize(ar,_colsToImputeDataTypesUnWrapped);

    //_tsImputeStrategy
    Traits<uint8_t>::serialize(ar,static_cast<std::underlying_type<TimeSeriesImputeStrategy>::type>(_tsImputeStrategy));

    //_medianValues
    Traits<
        std::map<
            KeyType,
            std::vector<double_t>
        >
    >::serialize(ar,_medianValues);

    //_supressError
    Traits<bool>::serialize(ar,_supressError);
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
inline void TimeSeriesImputerEstimator::Transformer::execute_impl(typename ThisBaseType::InputType const &input, typename ThisBaseType::CallbackFunction const &callback) /*override*/ {
    // Ensure that this row is in chronological order
    KeyType const &                                                         key(std::get<1>(input));
    std::map<KeyType, OutputRowType>::const_iterator const                  iterLastRow(_lastRowtracker.find(key));

    if(iterLastRow != _lastRowtracker.end()) {
        std::chrono::system_clock::time_point const &   lastRowTimePoint(std::get<1>(iterLastRow->second));
        std::chrono::system_clock::time_point const &   inputTimePoint(std::get<0>(input));

        if(inputTimePoint < lastRowTimePoint)
            throw std::runtime_error("Input stream not in chronological order.");
    }

    // Invoke the specified impute strategy
    if(_tsImputeStrategy == TimeSeriesImputeStrategy::Forward || _tsImputeStrategy == TimeSeriesImputeStrategy::Median)
        ffill_or_median(input, callback);
    else if(_tsImputeStrategy == TimeSeriesImputeStrategy::Backward)
        bfill(input, callback);
    else
        throw std::runtime_error("Unsupported Impute Strategy");
}

inline void TimeSeriesImputerEstimator::Transformer::flush_impl(typename ThisBaseType::CallbackFunction const &callback) /*override*/ {
    std::vector<typename TimeSeriesImputerEstimator::BaseType::TransformedType> output;

    for (auto it = _buffer.begin(); it != _buffer.end(); ++it)
        output.insert(output.end(), it->second.begin(), it->second.end());

    // Clear the working state
    _lastRowtracker.clear();
    _buffer.clear();

    // TODO: This can be implemented more efficiently, but we are just going for functional parity during this refactor
    for(auto & addedRow : output)
        callback(std::move(addedRow));
}

inline std::vector<typename TimeSeriesImputerEstimator::Transformer::ThisBaseType::TransformedType> TimeSeriesImputerEstimator::Transformer::generate_rows(typename ThisBaseType::InputType const &input, typename TimeSeriesImputerEstimator::TimePointType const & lastObservedTP) {

    std::vector<typename TimeSeriesImputerEstimator::Transformer::ThisBaseType::TransformedType> output;
    typename TimeSeriesImputerEstimator::TimePointType tempTP = lastObservedTP + _frequency;
    typename TimeSeriesImputerEstimator::TimePointType inputTP = std::get<0>(input);

    while(tempTP < inputTP) {
        output.push_back(std::make_tuple(true, tempTP, std::get<1>(input), ColsToImputeType(std::get<2>(input).size())));
        tempTP = tempTP + _frequency;
    }

    output.push_back(std::tuple_cat(std::make_tuple(false), input));

    return output;
}

inline void TimeSeriesImputerEstimator::Transformer::impute(typename TimeSeriesImputerEstimator::ColsToImputeType & prev, typename TimeSeriesImputerEstimator::ColsToImputeType & current) {

    for(std::size_t i=0; i< current.size(); ++i)
        if(StrTraits::IsNull(current[i]))
            current[i] = prev[i];
}

inline bool TimeSeriesImputerEstimator::Transformer::no_nulls(typename TimeSeriesImputerEstimator::ColsToImputeType const & input) {

    for(std::size_t i=0; i< input.size(); ++i)
        if(StrTraits::IsNull(input[i]))
            return false;

    return true;
}

inline void TimeSeriesImputerEstimator::Transformer::bfill(typename ThisBaseType::InputType const &input, typename ThisBaseType::CallbackFunction const &callback) {

    typename TimeSeriesImputerEstimator::KeyType const & key = std::get<1>(input);

    if ( _lastRowtracker.find(key) == _lastRowtracker.end() )
            _lastRowtracker.insert(std::make_pair(key, std::tuple_cat(std::make_tuple(false), input)));

    typename TimeSeriesImputerEstimator::OutputRowType  & lastRow = _lastRowtracker[key];
    std::vector<TimeSeriesImputerEstimator::BaseType::TransformedType> addedRowsResultset = generate_rows(input, std::get<1>(lastRow));

    if ( _buffer.find(key) != _buffer.end() )
            _buffer[key].insert(_buffer[key].end(), addedRowsResultset.begin(), addedRowsResultset.end());
    else
        _buffer.insert(std::make_pair(key, addedRowsResultset));

    lastRow = _buffer[key].back();

    for (auto it = _buffer[key].rbegin(); it != _buffer[key].rend(); it++) {
        impute(std::get<3>(lastRow), std::get<3>(*it));
        lastRow = *it;
    }
    _lastRowtracker[key] = _buffer[key].back();

    std::vector<typename TimeSeriesImputerEstimator::BaseType::TransformedType> results;
    int count = 0;
    for(std::size_t i=0; i< _buffer[key].size(); ++i)
    {
        if(no_nulls(std::get<3>(_buffer[key][i]))){
            results.push_back(_buffer[key][i]);
            count++;
        }
        else
            break;
    }

    if(count > 0)
        _buffer[key].erase(_buffer[key].begin(),_buffer[key].begin()+count);

    // TODO: This can be implemented more efficiently, but we are just going for functional parity during this refactor
    for(auto & addedRow : results)
        callback(std::move(addedRow));
}

inline void TimeSeriesImputerEstimator::Transformer::ffill_or_median(typename ThisBaseType::InputType const &input, typename ThisBaseType::CallbackFunction const &callback) {

    typename TimeSeriesImputerEstimator::KeyType const & key = std::get<1>(input);
    if ( _lastRowtracker.find(key) == _lastRowtracker.end() )
            _lastRowtracker.insert(std::make_pair(key, std::tuple_cat(std::make_tuple(false), input)));

    typename TimeSeriesImputerEstimator::OutputRowType  & lastRow = _lastRowtracker[key];
    std::vector<TimeSeriesImputerEstimator::BaseType::TransformedType> addedRowsResultset = generate_rows(input, std::get<1>(lastRow));

    for(auto &addedRow : addedRowsResultset) {
        if(_tsImputeStrategy == TimeSeriesImputeStrategy::Forward)
            impute(std::get<3>(lastRow) , std::get<3>(addedRow));
        else {
            std::map<KeyType,std::vector<double_t>>::const_iterator const   iterMedian(_medianValues.find(key));
            typename TimeSeriesImputerEstimator::ColsToImputeType &         addedRowData(std::get<3>(addedRow));

            for(std::size_t addedRowColIndex = 0; addedRowColIndex < addedRowData.size(); ++addedRowColIndex) {

                if(TimeSeriesMedianEstimator::DoesColTypeSupportMedian(_colsToImputeDataTypes[addedRowColIndex]) == false)
                    continue;

                if(StrTraits::IsNull(addedRowData[addedRowColIndex])) {
                    if(iterMedian == _medianValues.end())
                    {
                        if(_supressError)
                            continue;
                        else
                            throw std::runtime_error("Invalid key");
                    }

					assert(addedRowColIndex < _colsToImputeDataTypes.size());
                    assert(addedRowColIndex < iterMedian->second.size());
                    addedRowData[addedRowColIndex] = Traits<std::double_t>::ToString(iterMedian->second[addedRowColIndex]);
                }
            }

        }

        lastRow = addedRow;
    }

    _lastRowtracker[key] = lastRow;

    // TODO: This can be implemented more efficiently, but we are just going for functional parity during this refactor
    for(auto & addedRow : addedRowsResultset)
        callback(std::move(addedRow));
}

} // namespace Components
} // namespace Featurizers
} // namespace Featurizer
} // namespace Microsoft
