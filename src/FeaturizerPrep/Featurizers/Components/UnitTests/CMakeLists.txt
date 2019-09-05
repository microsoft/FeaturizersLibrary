# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5.0)

set(_project_name Featurizers_Components_UnitTest)
set(_${_project_name}_version_major 1)
set(_${_project_name}_version_minor 0)
set(_${_project_name}_version_patch 0)
set(_${_project_name}_version ${_${_project_name}_version_major}.${_${_project_name}_version_minor}.${_${_project_name}_version_patch})

project(${_project_name} VERSION ${_${_project_name}_version} LANGUAGES CXX)

set(_includes "$ENV{INCLUDE}")
set(_libs "$ENV{LIB}")
set(CMAKE_MODULE_PATH "$ENV{DEVELOPMENT_ENVIRONMENT_CMAKE_MODULE_PATH}")

if(NOT WIN32)
    string(REPLACE ":" ";" CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}")
    string(REPLACE ":" ";" _includes "${_includes}")
    string(REPLACE ":" ";" _libs "${_libs}")
endif()

include(CppCommon)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# All paths should be relative to `${_this_path}`
get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

enable_testing()

foreach(_test_name IN ITEMS
    InferenceOnlyFeaturizerImpl_UnitTest
    PipelineExecutionEstimatorImpl_UnitTest
    TrainingOnlyEstimatorImpl_UnitTest
)
    add_executable(
        ${_test_name}
        ${_test_name}.cpp
    )

    # target_link_libraries(
    #     ${_test_name}
    #     <library_name>
    # )

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
