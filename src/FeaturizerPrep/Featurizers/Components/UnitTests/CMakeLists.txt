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

set(CppCommon_STATIC_CRT ON CACHE BOOL "" FORCE)

include(CppCommon)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

enable_testing()

foreach(_test_name IN ITEMS
    HistogramEstimator_UnitTest
    InferenceOnlyFeaturizerImpl_UnitTest
    PipelineExecutionEstimatorImpl_UnitTest
    RobustScalarNormEstimator_UnitTest
    RobustScalarTransformer_UnitTest
    TrainingOnlyEstimatorImpl_UnitTest
)
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

    add_test(NAME ${_test_name} COMMAND ${_test_name} --success)
endforeach()
