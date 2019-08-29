# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5.0)

project(Featurizers LANGUAGES CXX)

set(CMAKE_MODULE_PATH "$ENV{DEVELOPMENT_ENVIRONMENT_CMAKE_MODULE_PATH}")

if(NOT WIN32)
    string(REPLACE ":" ";" CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}")
    string(REPLACE ":" ";" _includes "$ENV{INCLUDE}")
    string(REPLACE ":" ";" _libs "$ENV{LIB}")
endif()

set(CppCommon_STATIC_CRT ON CACHE BOOL "" FORCE)

include(CppCommon)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(generate_shared_library_attributes)

generate_shared_library_attributes(
    _shared_library_attributes_sources
    NAME "Microsoft ML Featurizers"
    FILE_DESCRIPTION "Microsoft ML Featurizers"
    COMPANY_NAME "Microsoft Corporation"
    COPYRIGHT "Copyright (C) Microsoft Corporation. All rights reserved."
    VERSION_MAJOR 0
    VERSION_MINOR 1
    VERSION_PATCH 0
)

add_library(Featurizers SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/../Featurizers/DateTimeFeaturizer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../Featurizers/DateTimeFeaturizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Featurizers/StringFeaturizer.h

    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratedCode/SharedLibrary_Common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratedCode/SharedLibrary_Common.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratedCode/SharedLibrary_CatImputerFeaturizer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratedCode/SharedLibrary_CatImputerFeaturizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratedCode/SharedLibrary_DateTimeFeaturizer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratedCode/SharedLibrary_DateTimeFeaturizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratedCode/SharedLibrary_StringFeaturizer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneratedCode/SharedLibrary_StringFeaturizer.cpp

    ${_shared_library_attributes_sources}
)

target_include_directories(Featurizers PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../Featurizers
    ${_includes}
)

target_link_directories(Featurizers PRIVATE
    ${_libs}
)
