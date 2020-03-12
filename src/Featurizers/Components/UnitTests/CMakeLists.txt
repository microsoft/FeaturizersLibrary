# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5.0)

project(Featurizers_Components_UnitTests LANGUAGES CXX)

set(_includes "$ENV{INCLUDE}")
set(_libs "$ENV{LIB}")
set(CMAKE_MODULE_PATH "$ENV{DEVELOPMENT_ENVIRONMENT_CMAKE_MODULE_PATH}")

if(NOT WIN32)
    string(REPLACE ":" ";" CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}")
    string(REPLACE ":" ";" _includes "${_includes}")
    string(REPLACE ":" ";" _libs "${_libs}")
endif()

include(CppCommon OPTIONAL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

include(${_this_path}/../cmake/FeaturizersComponentsCode.cmake)

enable_testing()

SET(
    _test_names
    DocumentStatisticsEstimator_UnitTest
    FilterFeaturizerImpl_UnitTest
    FrequencyEstimator_UnitTest
    GlobalMinimumFrequencyEstimator_UnitTest
    # This test is optionally included below:
    GrainFeaturizerImpl_UnitTest
    HistogramEstimator_UnitTest
    ImputerTransformer_UnitTest
    IndexMapEstimator_UnitTest
    InferenceOnlyFeaturizerImpl_UnitTest
    MaxAbsValueEstimator_UnitTest
    MedianEstimator_UnitTest
    MinMaxEstimator_UnitTest
    ModeEstimator_UnitTest
    NormUpdaters_UnitTest
    OrderEstimator_UnitTest
    PipelineExecutionEstimatorImpl_UnitTest
    StandardDeviationEstimator_UnitTest
    StatisticalMetricsEstimator_UnitTest
    TrainingOnlyEstimatorImpl_UnitTest
    VectorNormsEstimator_UnitTest
    WindowFeaturizerBase_UnitTest
    # TODO: Add tests for:
    #   - TimeSeriesFrequencyEstimator
    #   - TimeSeriesMedianEstimator
)

# GrainFeaturizerImpl_UnitTest causes an internal compile error under the scenario:
#
#   - Windows (1)
#   - Clang 8.0.0 and Clang 8.0.1 (the issue has been fixed on Clang 9.0.0) (2)
#   - x86 (3)
#   - Release (4)
#
# disable that test for now.

if(
    WIN32                                                                       # 1
    AND "$ENV{DEVELOPMENT_ENVIRONMENT_CPP_COMPILER_NAME}" STREQUAL "Clang-8"    # 2
    AND "$ENV{DEVELOPMENT_ENVIRONMENT_CPP_ARCHITECTURE}" STREQUAL "x86"         # 3
    AND "${CMAKE_BUILD_TYPE}" MATCHES "^Release.*$"                             # 4
)
    list(REMOVE_ITEM _test_names GrainFeaturizerImpl_UnitTest)
endif()

foreach(_test_name IN ITEMS ${_test_names})
    add_executable(
        ${_test_name}
        ${_test_name}.cpp
    )

    target_include_directories(
        ${_test_name} PRIVATE
        ${_includes}
    )

    target_link_directories(
        ${_test_name} PRIVATE
        ${_libs}
    )

    target_link_libraries(${_test_name} PRIVATE
        FeaturizersComponentsCode
    )

    add_test(NAME ${_test_name} COMMAND ${_test_name} --success)
endforeach()
