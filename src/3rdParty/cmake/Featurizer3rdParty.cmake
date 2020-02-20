# This is implemented as a function to provide scope for local variables
function(Impl)
    set(_project_name Featurizer3rdParty)
    get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

    # Retrieve the submodules
    execute_process(COMMAND "git submodule update --init --recursive")

    # Add the stand-alone files files
    add_library(${_project_name} STATIC
        ${_this_path}/../date.h
        ${_this_path}/../iso_week.h
        ${_this_path}/../json.h
        ${_this_path}/../MurmurHash3.cpp
        ${_this_path}/../MurmurHash3.h
        ${_this_path}/../optional.h
    )

    # ----------------------------------------------------------------------
    macro(PreserveCompilerSettings)
        foreach(_flag_prefix IN ITEMS
            C
            CXX
            EXE_LINKER
            STATIC_LINKER
            SHARED_LINKER
            MODULE_LINKER
        )
            set(_original_CMAKE_${_flag_prefix}_FLAGS "${CMAKE_${_flag_prefix}_FLAGS}")
        endforeach()
    endmacro()

    macro(RestoreCompilerSettings)
        foreach(_flag_prefix IN ITEMS
            C
            CXX
            EXE_LINKER
            STATIC_LINKER
            SHARED_LINKER
            MODULE_LINKER
        )
            set(CMAKE_${_flag_prefix}_FLAGS "${_original_CMAKE_${_flag_prefix}_FLAGS}")
        endforeach()
    endmacro()

    # ----------------------------------------------------------------------

    # Add re2
    get_filename_component(_compiler_basename "${CMAKE_CXX_COMPILER}" NAME)

    PreserveCompilerSettings()

    # Ignore warnings in re2
    if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR _compiler_basename MATCHES "clang-cl.exe")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-missing-field-initializers -Wno-unknown-warning-option")
    elseif (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-everything")
    endif()

    if(NOT TARGET re2::re2)
        set(RE2_BUILD_TESTING OFF CACHE BOOL "" FORCE)

        add_subdirectory(${_this_path}/../re2 ${CMAKE_CURRENT_BINARY_DIR}/3rdParty/re2 EXCLUDE_FROM_ALL)
        set_target_properties(re2 PROPERTIES FOLDER "External/re2")
        add_library(re2::re2 ALIAS re2)
        set(RE2_INCLUDE_DIR ${_this_path}/../re2 CACHE PATH "" FORCE)
        
    endif()

    RestoreCompilerSettings()

    target_include_directories(
        ${_project_name} PUBLIC
        ${RE2_INCLUDE_DIR}
    )

    target_link_libraries(
        ${_project_name} PUBLIC
        re2
    )

    if (UNIX)
        find_package(Threads)
        target_link_libraries(
            ${_project_name} PUBLIC
            ${CMAKE_THREAD_LIBS_INIT}
        )
    endif()
endfunction()

Impl()
