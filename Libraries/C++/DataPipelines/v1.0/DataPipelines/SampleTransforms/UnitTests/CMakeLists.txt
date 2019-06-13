# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------

cmake_minimum_required(VERSION 3.5.0)

project(SampleTransforms_UnitTest LANGUAGES CXX)

include(../../DataPipelinesCommon.cmake)

enable_testing()

foreach(_name IN ITEMS arithmetic_UnitTests)
    add_executable(${_name} ${_name}.cpp)

    target_include_directories(${_name} PRIVATE ${_includes})
    target_link_directories(${_name} PRIVATE ${_libs})

    add_test(NAME ${_name} COMMAND ${_name} --success)
endforeach()
