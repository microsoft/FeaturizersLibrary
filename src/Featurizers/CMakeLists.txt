# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5.0)

project(FeaturizersCode CXX)

include(cmake/FeaturizersCode.cmake)

set_target_properties(FeaturizersCode PROPERTIES CXX_STANDARD 11)

option(featurizers_MSVC_STATIC_RUNTIME "Compile for the static CRT" OFF)

if(MSVC)
  if (featurizers_MSVC_STATIC_RUNTIME)
    message(STATUS "Linking Featurizers to static MSVCRT")
      # In case we are building static libraries, link also the runtime library statically
      # so that MSVCR*.DLL is not required at runtime.
      # https://msdn.microsoft.com/en-us/library/2kzt1wy3.aspx
      # This is achieved by replacing msvc option /MD with /MT and /MDd with /MTd
      # https://gitlab.kitware.com/cmake/community/wikis/FAQ#how-can-i-build-my-msvc-application-with-a-static-runtime
      foreach(flag_var
          CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
          CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
          CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
          CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/MD")
          string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/MD")
      endforeach(flag_var)
  else()
    message(STATUS "Linking Featurizers to MSVCRT DLL")
  endif()
endif()
