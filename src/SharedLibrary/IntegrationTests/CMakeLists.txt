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

include(CppCommon OPTIONAL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

include(${_this_path}/../cmake/Featurizers.cmake)

enable_testing()

foreach(_test_name IN ITEMS
    SharedLibrary_CatImputerFeaturizer_IntegrationTest
    SharedLibrary_CountVecFeaturizer_IntegrationTest
    SharedLibrary_DateTimeFeaturizer_IntegrationTest
    SharedLibrary_FromStringFeaturizer_IntegrationTest
    SharedLibrary_HOHVFeaturizer_IntegrationTest
    SharedLibrary_IMFeaturizer_IntegrationTest
    SharedLibrary_L1NormalizeFeaturizer_IntegrationTest
    SharedLibrary_L2NormalizeFeaturizer_IntegrationTest
    SharedLibrary_LEFeaturizer_IntegrationTest
    SharedLibrary_MASFeaturizer_IntegrationTest
    SharedLibrary_MNormalizeFeaturizer_IntegrationTest
    SharedLibrary_MDFeaturizer_IntegrationTest
    SharedLibrary_MeanIFeaturizer_IntegrationTest
    SharedLibrary_MedianIFeaturizer_IntegrationTest
    SharedLibrary_MMIFeaturizer_IntegrationTest
    SharedLibrary_MMSFeaturizer_IntegrationTest
    SharedLibrary_ModeIFeaturizer_IntegrationTest
    SharedLibrary_NumericalizeFeaturizer_IntegrationTest
    SharedLibrary_OHEFeaturizer_IntegrationTest
    SharedLibrary_PCAFeaturizer_IntegrationTest
    SharedLibrary_RSFeaturizer_IntegrationTest
    SharedLibrary_SSWFeaturizer_IntegrationTest
    SharedLibrary_StringFeaturizer_IntegrationTest
    SharedLibrary_TfidfVecFeaturizer_IntegrationTest
    SharedLibrary_TruncatedSVDFeaturizer_IntegrationTest
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
