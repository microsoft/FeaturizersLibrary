# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5.0)

set(_featurizers_this_path ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "")

function(Impl)
    # Defining a function here to introduce a new scope for local variables
    set(_project_name Featurizers)
    set(_version_major 0)                   # '1' in the release 1.2.3-alpha1+201910161322
    set(_version_minor 4)                   # '2' in the release 1.2.3-alpha1+201910161322
    set(_version_patch 0)                   # '3' in the release 1.2.3-alpha1+201910161322
    set(_version_prerelease_info "")        # Optional 'alpha1' in the release 1.2.3-alpha1+201910161322
    set(_version_build_info "")             # Optional '201910161322' in the release 1.2.3-alpha1+201910161322

    set(_version ${_version_major}.${_version_minor}.${_version_patch})

    # Alpha version components (which are supported in SemVer) present problems
    # for cmake when the version is provided inline. However, things work as expected
    # when setting the version as a property.
    project(${_project_name} LANGUAGES CXX)
    set(PROJECT_VERSION ${_version})

    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    set(_includes "$ENV{INCLUDE}")
    set(_libs "$ENV{LIB}")
    set(CMAKE_MODULE_PATH "$ENV{DEVELOPMENT_ENVIRONMENT_CMAKE_MODULE_PATH}")

    if(NOT WIN32)
        string(REPLACE ":" ";" CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}")
        string(REPLACE ":" ";" _includes "${_includes}")
        string(REPLACE ":" ";" _libs "${_libs}")
    endif()

    include(CppCommon)
    include(GenerateFileAttributes)

    generate_file_attributes(
        _featurizers_file_attribute_sources
        NAME "Microsoft MLFeaturizers"
        COMPANY_NAME "Microsoft Corporation"
        VERSION_MAJOR ${_version_major}
        VERSION_MINOR ${_version_minor}
        VERSION_PATCH ${_version_patch}
        VERSION_PRERELEASE_INFO ${_version_prerelease_info}
        VERSION_BUILD_INFO ${_version_build_info}
        COPYRIGHT "(C) Microsoft Corporation. All rights reserved."
    )

    include(${_featurizers_this_path}/../../Featurizers/cmake/FeaturizersCode.cmake)

    add_library(
        ${_project_name} SHARED

        ${_featurizers_this_path}/../SharedLibrary_DateTimeFeaturizerCustom.h
        ${_featurizers_this_path}/../SharedLibrary_DateTimeFeaturizerCustom.cpp
        ${_featurizers_this_path}/../SharedLibrary_RobustScalerFeaturizerCustom.h
        ${_featurizers_this_path}/../SharedLibrary_RobustScalerFeaturizerCustom.cpp
        ${_featurizers_this_path}/../SharedLibrary_TimeSeriesImputerFeaturizer.h
        ${_featurizers_this_path}/../SharedLibrary_TimeSeriesImputerFeaturizer.cpp

        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_CatImputerFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_CatImputerFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_Common.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_Common.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_Common.hpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_CountVectorizerFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_CountVectorizerFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_DateTimeFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_DateTimeFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_FromStringFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_FromStringFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_HashOneHotVectorizerFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_HashOneHotVectorizerFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_ImputationMarkerFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_ImputationMarkerFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_L1NormalizeFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_L1NormalizeFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_L2NormalizeFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_L2NormalizeFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_LabelEncoderFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_LabelEncoderFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MaxAbsScalerFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MaxAbsScalerFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MaxNormalizeFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MaxNormalizeFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MeanImputerFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MeanImputerFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MedianImputerFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MedianImputerFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MinMaxImputerFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MinMaxImputerFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MinMaxScalerFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MinMaxScalerFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MissingDummiesFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_MissingDummiesFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_ModeImputerFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_ModeImputerFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_NumericalizeFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_NumericalizeFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_OneHotEncoderFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_OneHotEncoderFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_PCAFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_PCAFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_PointerTable.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_PointerTable.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_RobustScalerFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_RobustScalerFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_StandardScaleWrapperFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_StandardScaleWrapperFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_StringFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_StringFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_TfidfVectorizerFeaturizer.h
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_TfidfVectorizerFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_TruncatedSVDFeaturizer.cpp
        ${_featurizers_this_path}/../GeneratedCode/SharedLibrary_TruncatedSVDFeaturizer.h

        ${_featurizers_file_attribute_sources}
    )

    set_target_properties(
        ${_project_name} PROPERTIES
        VERSION ${_version}
        SOVERSION ${_version_major}
    )

    target_link_libraries(
        ${_project_name} PRIVATE
        FeaturizersCode
    )

    target_include_directories(
        ${_project_name} PRIVATE
        ${_featurizers_this_path}/../GeneratedCode
        ${_featurizers_this_path}/../..
        ${_featurizers_this_path}/../../Featurizers
        ${_includes}
    )

    target_link_directories(
        ${_project_name} PRIVATE
        ${_libs}
    )
endfunction()

Impl()
