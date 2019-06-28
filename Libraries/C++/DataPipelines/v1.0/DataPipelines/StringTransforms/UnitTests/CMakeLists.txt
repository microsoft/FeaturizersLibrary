# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------

cmake_minimum_required(VERSION 3.5.0)

project(StringTransforms_UnitTest LANGUAGES CXX)

include(../../DataPipelinesCommon.cmake)

enable_testing()

_add_unit_tests(ITEMS regex_vectorizer_UnitTests)

target_sources(regex_vectorizer_UnitTests PUBLIC ../regex_vectorizer.cpp ../regex_vectorizer.hpp)
