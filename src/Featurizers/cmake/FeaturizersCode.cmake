# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

add_library(FeaturizersCode STATIC
    ${_this_path}/../../3rdParty/MurmurHash3.cpp

    ${_this_path}/../CatImputerFeaturizer.h
    ${_this_path}/../CountVectorizerFeaturizer.h
    ${_this_path}/../DateTimeFeaturizer.h
    ${_this_path}/../DateTimeFeaturizer.cpp
    ${_this_path}/../FromStringFeaturizer.h
    ${_this_path}/../HashOneHotVectorizerFeaturizer.h
    ${_this_path}/../ImputationMarkerFeaturizer.h
    ${_this_path}/../L1NormalizeFeaturizer.h
    ${_this_path}/../L2NormalizeFeaturizer.h
    ${_this_path}/../LabelEncoderFeaturizer.h
    ${_this_path}/../MaxAbsScalarFeaturizer.h
    ${_this_path}/../MaxNormalizeFeaturizer.h
    ${_this_path}/../MeanImputerFeaturizer.h
    ${_this_path}/../MedianImputerFeaturizer.h
    ${_this_path}/../MinMaxImputerFeaturizer.h
    ${_this_path}/../MinMaxScalarFeaturizer.h
    ${_this_path}/../MissingDummiesFeaturizer.h
    ${_this_path}/../ModeImputerFeaturizer.h
    ${_this_path}/../NumericalizeFeaturizer.h
    ${_this_path}/../OneHotEncoderFeaturizer.h
    ${_this_path}/../PCAFeaturizer.h
    ${_this_path}/../RobustScalarFeaturizer.h
    ${_this_path}/../SampleAddFeaturizer.h
    ${_this_path}/../SampleAddFeaturizer.cpp
    ${_this_path}/../StandardScaleWrapperFeaturizer.h
    ${_this_path}/../StringFeaturizer.h
    ${_this_path}/../Structs.h
    ${_this_path}/../TestHelpers.h
    ${_this_path}/../TimeSeriesImputerFeaturizer.h

    ${_this_path}/../Components/Components.h
    ${_this_path}/../Components/DocumentStatisticsEstimator.h
    ${_this_path}/../Components/GrainEstimatorImpl.h
    ${_this_path}/../Components/HistogramEstimator.h
    ${_this_path}/../Components/ImputerTransformer.h
    ${_this_path}/../Components/IndexMapEstimator.h
    ${_this_path}/../Components/InferenceOnlyFeaturizerImpl.h
    ${_this_path}/../Components/MaxAbsValueEstimator.h
    ${_this_path}/../Components/MedianEstimator.h
    ${_this_path}/../Components/MinMaxEstimator.h
    ${_this_path}/../Components/ModeEstimator.h
    ${_this_path}/../Components/NormUpdaters.h
    ${_this_path}/../Components/OrderEstimator.h
    ${_this_path}/../Components/PipelineExecutionEstimatorImpl.h
    ${_this_path}/../Components/StandardDeviationEstimator.h
    ${_this_path}/../Components/StatisticalMetricsEstimator.h
    ${_this_path}/../Components/TimeSeriesFrequencyEstimator.h
    ${_this_path}/../Components/TimeSeriesImputerTransformer.h
    ${_this_path}/../Components/TimeSeriesMedianEstimator.h
    ${_this_path}/../Components/TrainingOnlyEstimatorImpl.h
    ${_this_path}/../Components/VectorNormsEstimator.h

    ${_this_path}/../Components/Details/EstimatorTraits.h
    ${_this_path}/../Components/Details/PipelineExecutionEstimatorImpl_details.h

    ${_this_path}/../Base/NormalizeFeaturizer.h
)

file(GLOB JSON_DATA "${_this_path}/../DateTimeFeaturizerData/GeneratedCode/*.json")

foreach(df ${JSON_DATA})
    file(COPY ${df} DESTINATION Data/DateTimeFeaturizer)
endforeach()
