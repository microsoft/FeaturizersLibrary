# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5.0)

project(SharedLibrary_IntegrationTests LANGUAGES CXX)

set(_includes "$ENV{INCLUDE}")
set(_libs "$ENV{LIB}")
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

get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

include(${_this_path}/../cmake/Featurizers.cmake)

enable_testing()

foreach(_test_name IN ITEMS
    SharedLibrary_CatImputerFeaturizer_IntegrationTest
    SharedLibrary_DateTimeFeaturizer_IntegrationTest
    SharedLibrary_StringFeaturizer_IntegrationTest
    SharedLibrary_TSIFeaturizer_IntegrationTest
)
    add_executable(${_test_name} ${_test_name}.cpp)

    target_include_directories(
        ${_test_name} PRIVATE
        ${_includes}
        ${_this_path}/..
        ${_this_path}/../GeneratedCode
        ${_this_path}/../..
    )

    target_link_directories(
        ${_test_name} PRIVATE
        ${_libs}
    )

    target_link_libraries(
        ${_test_name} PRIVATE
        Featurizers
    )

    add_test(NAME ${_test_name} COMMAND ${_test_name} --success)
endforeach()
