# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5.0)

project(Featurizer_UnitTests LANGUAGES CXX)

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

set(_src_this_path ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "")
include(${_src_this_path}/../Featurizers/cmake/FeaturizersCode.cmake)

enable_testing()

foreach(_test_name IN ITEMS
    Archive_UnitTest
    Featurizer_UnitTest
    Strings_UnitTest
    Traits_UnitTest
)
    add_executable(${_test_name} ${_test_name}.cpp)

    target_include_directories(
        ${_test_name} PRIVATE
        ${_includes}
        FeaturizersCode
    )

    target_link_directories(${_test_name} PRIVATE ${_libs})

    target_link_libraries(
        ${_test_name}
        FeaturizersCode
    )

    add_test(NAME ${_test_name} COMMAND ${_test_name} --success)
endforeach()
