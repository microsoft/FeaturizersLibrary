# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5.0)

project(FeaturizersCode CXX)

include(cmake/FeaturizersCode.cmake)

set_target_properties(FeaturizersCode PROPERTIES CXX_STANDARD 11)
