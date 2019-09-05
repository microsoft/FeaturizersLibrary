# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

include(${_this_path}/generate_shared_library_attributes.cmake)

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
    ${_this_path}/../../Featurizers/CatImputerFeaturizer.h
    ${_this_path}/../../Featurizers/DateTimeFeaturizer.h
    ${_this_path}/../../Featurizers/DateTimeFeaturizer.cpp
    ${_this_path}/../../Featurizers/StringFeaturizer.h

    ${_this_path}/../GeneratedCode/SharedLibrary_Common.h
    ${_this_path}/../GeneratedCode/SharedLibrary_Common.cpp
    ${_this_path}/../GeneratedCode/SharedLibrary_CatImputerFeaturizer.h
    ${_this_path}/../GeneratedCode/SharedLibrary_CatImputerFeaturizer.cpp
    ${_this_path}/../GeneratedCode/SharedLibrary_DateTimeFeaturizer.h
    ${_this_path}/../GeneratedCode/SharedLibrary_DateTimeFeaturizer.cpp
    ${_this_path}/../GeneratedCode/SharedLibrary_StringFeaturizer.h
    ${_this_path}/../GeneratedCode/SharedLibrary_StringFeaturizer.cpp

    ${_shared_library_attributes_sources}
)

target_include_directories(Featurizers PRIVATE
    ${_this_path}/../..
    ${_this_path}/../../Featurizers
    ${_includes}
)

target_link_directories(Featurizers PRIVATE
    ${_libs}
)
