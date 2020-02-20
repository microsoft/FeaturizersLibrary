# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------

# This is defined as a function to limit the visibility of _this_path so that
# it doesn't conflict with other cmake modules.
function(Impl)
    set(_project_name FeaturizersCalculatorsCode)
    get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

    include(${_this_path}/../../../3rdParty/cmake/Featurizer3rdParty.cmake)

    # Uncomment this content if we add .cpp files to the directory

    # add_library(${_project_name} STATIC
    #     ${_this_path}/../Calculators.h
    # )
    #
    # target_include_directories(
    #     ${_project_name} PUBLIC
    #     Featurizer3rdParty
    # )
    #
    # target_link_libraries(
    #     ${_project_name} PUBLIC
    #     Featurizer3rdParty
    # )
endfunction()

Impl()
