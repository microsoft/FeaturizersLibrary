# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
set(_project_name Featurizers)
set(_${_project_name}_version_major 0)
set(_${_project_name}_version_minor 1)
set(_${_project_name}_version_patch 0)
set(_${_project_name}_version ${_${_project_name}_version_major}.${_${_project_name}_version_minor}.${_${_project_name}_version_patch})

project(${_project_name} VERSION ${_${_project_name}_version} LANGUAGES CXX)

get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

include(${_this_path}/generate_shared_library_attributes.cmake)
include(${_this_path}/../../Featurizers/cmake/FeaturizersCode.cmake)

get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

generate_shared_library_attributes(
    _shared_library_attributes_sources
    NAME "Microsoft ML Featurizers"
    FILE_DESCRIPTION "Microsoft ML Featurizers"
    COMPANY_NAME "Microsoft Corporation"
    COPYRIGHT "Copyright (C) Microsoft Corporation. All rights reserved."
    VERSION_MAJOR ${_${_project_name}_version_major}
    VERSION_MINOR ${_${_project_name}_version_minor}
    VERSION_PATCH ${_${_project_name}_version_patch}
    ICON "NA"
)

add_library(Featurizers SHARED
    ${_this_path}/../SharedLibrary_DateTimeFeaturizerCustom.h
    ${_this_path}/../SharedLibrary_DateTimeFeaturizerCustom.cpp
    ${_this_path}/../SharedLibrary_RobustScalarFeaturizerCustom.h
    ${_this_path}/../SharedLibrary_RobustScalarFeaturizerCustom.cpp
    ${_this_path}/../SharedLibrary_TimeSeriesImputerFeaturizer.h
    ${_this_path}/../SharedLibrary_TimeSeriesImputerFeaturizer.cpp

    ${_this_path}/../GeneratedCode/SharedLibrary_CatImputerFeaturizer.h
    ${_this_path}/../GeneratedCode/SharedLibrary_CatImputerFeaturizer.cpp
    ${_this_path}/../GeneratedCode/SharedLibrary_Common.h
    ${_this_path}/../GeneratedCode/SharedLibrary_Common.cpp
    ${_this_path}/../GeneratedCode/SharedLibrary_DateTimeFeaturizer.h
    ${_this_path}/../GeneratedCode/SharedLibrary_DateTimeFeaturizer.cpp
    ${_this_path}/../GeneratedCode/SharedLibrary_HashOneHotVectorizerFeaturizer.h
    ${_this_path}/../GeneratedCode/SharedLibrary_HashOneHotVectorizerFeaturizer.cpp
    ${_this_path}/../GeneratedCode/SharedLibrary_ImputationMakerFeaturizer.h
    ${_this_path}/../GeneratedCode/SharedLibrary_ImputationMakerFeaturizer.cpp
    ${_this_path}/../GeneratedCode/SharedLibrary_LabelEncoderFeaturizer.h
    ${_this_path}/../GeneratedCode/SharedLibrary_LabelEncoderFeaturizer.cpp
    ${_this_path}/../GeneratedCode/SharedLibrary_OneHotEncoderFeaturizer.h
    ${_this_path}/../GeneratedCode/SharedLibrary_OneHotEncoderFeaturizer.cpp
    ${_this_path}/../GeneratedCode/SharedLibrary_PointerTable.h
    ${_this_path}/../GeneratedCode/SharedLibrary_PointerTable.cpp
    ${_this_path}/../GeneratedCode/SharedLibrary_RobustScalarFeaturizer.h
    ${_this_path}/../GeneratedCode/SharedLibrary_RobustScalarFeaturizer.cpp
    ${_this_path}/../GeneratedCode/SharedLibrary_StringFeaturizer.h
    ${_this_path}/../GeneratedCode/SharedLibrary_StringFeaturizer.cpp

    ${_shared_library_attributes_sources}
)

target_link_libraries(Featurizers PRIVATE
    FeaturizersCode
)

target_include_directories(Featurizers PRIVATE
    ${_this_path}/../GeneratedCode
    ${_this_path}/../..
    ${_this_path}/../../Featurizers
    ${_includes}
)

target_link_directories(Featurizers PRIVATE
    ${_libs}
)

set_target_properties(
    ${_project_name} PROPERTIES
    VERSION ${_${_project_name}_version}
    SOVERSION ${_${_project_name}_version_major}
)
