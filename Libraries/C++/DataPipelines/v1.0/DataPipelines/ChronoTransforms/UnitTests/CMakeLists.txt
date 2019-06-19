# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------

cmake_minimum_required(VERSION 3.5.0)

project(ChronoTransforms_UnitTests LANGUAGES CXX)
include(../../DataPipelinesCommon.cmake)
enable_testing()
_add_unit_tests(ITEMS date_time_UnitTests)
