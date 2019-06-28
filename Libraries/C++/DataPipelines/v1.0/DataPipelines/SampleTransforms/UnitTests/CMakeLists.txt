# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------

cmake_minimum_required(VERSION 3.5.0)

project(SampleTransforms_UnitTest LANGUAGES CXX)

include(../../DataPipelinesCommon.cmake)

enable_testing()

_add_unit_tests(ITEMS arithmetic_UnitTests)

target_sources(arithmetic_UnitTests PRIVATE ../arithmetic.cpp ../arithmetic.hpp)
