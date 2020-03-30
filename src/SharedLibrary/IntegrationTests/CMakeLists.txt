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
    SharedLibrary_AnalyticalRollingWindow_IntegrationTest
    SharedLibrary_BackwardFillImputer_IntegrationTest
    SharedLibrary_CatImputer_IntegrationTest
    SharedLibrary_CountVectorizer_IntegrationTest
    SharedLibrary_DateTime_IntegrationTest
    SharedLibrary_ForwardFillImputer_IntegrationTest
    SharedLibrary_FromString_IntegrationTest
    SharedLibrary_HashOneHotVectorizer_IntegrationTest
    SharedLibrary_ImputationMarker_IntegrationTest
    SharedLibrary_L1Normalize_IntegrationTest
    SharedLibrary_L2Normalize_IntegrationTest
    SharedLibrary_LabelEncoder_IntegrationTest
    # TODO: Not available yet SharedLibrary_LagLeadOperator_IntegrationTest
    SharedLibrary_MaxAbsScaler_IntegrationTest
    SharedLibrary_MaxNormalize_IntegrationTest
    SharedLibrary_MeanImputer_IntegrationTest
    SharedLibrary_MedianImputer_IntegrationTest
    SharedLibrary_MinMaxImputer_IntegrationTest
    SharedLibrary_MinMaxScaler_IntegrationTest
    SharedLibrary_MissingDummies_IntegrationTest
    SharedLibrary_ModeImputer_IntegrationTest
    SharedLibrary_Numericalize_IntegrationTest
    SharedLibrary_OneHotEncoder_IntegrationTest
    SharedLibrary_PCA_IntegrationTest
    SharedLibrary_RobustScaler_IntegrationTest
    # TODO: Needs impl: SharedLibrary_ShortGrainDropper_IntegrationTest
    SharedLibrary_SimpleRollingWindow_IntegrationTest
    SharedLibrary_StandardScaleWrapper_IntegrationTest
    SharedLibrary_String_IntegrationTest
    SharedLibrary_TfidfVectorizer_IntegrationTest
    SharedLibrary_TimeSeriesImputer_IntegrationTest
    SharedLibrary_TruncatedSVD_IntegrationTest
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
