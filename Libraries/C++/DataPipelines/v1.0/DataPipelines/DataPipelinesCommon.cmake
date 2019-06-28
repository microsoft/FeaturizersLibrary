# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
set(CMAKE_MODULE_PATH "$ENV{DEVELOPMENT_ENVIRONMENT_CMAKE_MODULE_PATH}")

if(NOT WIN32)
    string(REPLACE ":" ";" CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}")
    string(REPLACE ":" ";" _includes "$ENV{INCLUDE}")
    string(REPLACE ":" ";" _libs "$ENV{LIB}")
endif()

include(CppCommon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(_add_unit_test _name)
    add_executable(${_name} ${_name}.cpp)

    target_include_directories(${_name} PRIVATE ${_includes})
    target_link_directories(${_name} PRIVATE ${_libs})

    add_test(NAME ${_name} COMMAND ${_name} --success)
endfunction(_add_unit_test)

function(_add_unit_tests)
    enable_testing()
    foreach(_name IN ${ARGN})
        _add_unit_test(${_name})
    endforeach()
endfunction(_add_unit_tests)
