# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------

# This is defined as a function to limit the visibility of _this_path so that
# it doesn't conflict with other cmake modules.
function(Impl)
    get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

    set(FEATURIZERS_ROOT ${_this_path}/../../../..)

    include(${_this_path}/../../../3rdParty/cmake/Featurizer3rdParty.cmake)

    add_library(FeaturizersComponentsCode STATIC
        ${_this_path}/../Components.h
        ${_this_path}/../DocumentStatisticsEstimator.h
        ${_this_path}/../DocumentStatisticsEstimator.cpp
        ${_this_path}/../GrainEstimatorImpl.h
        ${_this_path}/../HistogramEstimator.h
        ${_this_path}/../ImputerTransformer.h
        ${_this_path}/../IndexMapEstimator.h
        ${_this_path}/../InferenceOnlyFeaturizerImpl.h
        ${_this_path}/../MaxAbsValueEstimator.h
        ${_this_path}/../MedianEstimator.h
        ${_this_path}/../MinMaxEstimator.h
        ${_this_path}/../ModeEstimator.h
        ${_this_path}/../NormUpdaters.h
        ${_this_path}/../OrderEstimator.h
        ${_this_path}/../PipelineExecutionEstimatorImpl.h
        ${_this_path}/../StandardDeviationEstimator.h
        ${_this_path}/../StatisticalMetricsEstimator.h
        ${_this_path}/../TimeSeriesFrequencyEstimator.h
        ${_this_path}/../TimeSeriesImputerTransformer.h
        ${_this_path}/../TimeSeriesMedianEstimator.h
        ${_this_path}/../TrainingOnlyEstimatorImpl.h
        ${_this_path}/../VectorNormsEstimator.h

        ${_this_path}/../Details/EstimatorTraits.h
        ${_this_path}/../Details/PipelineExecutionEstimatorImpl_details.h
    )

    target_include_directories(
        FeaturizersComponentsCode PUBLIC
        Featurizer3rdParty
    )

    target_link_libraries(
        FeaturizersComponentsCode PUBLIC
        Featurizer3rdParty
    )
endfunction()

Impl()
