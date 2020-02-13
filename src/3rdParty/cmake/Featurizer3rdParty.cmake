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
    if (CMAKE_CXX_COMPIlER_ID MATCHES Clang OR _compiler_basename MATCHES "clang-cl.exe")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
        if (UNIX)
            find_package(Threads)
            target_link_libraries(Featurizer3rdParty PUBLIC ${CMAKE_THREAD_LIBS_INIT})
        endif()
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        find_package(Threads)
        target_link_libraries(Featurizer3rdParty PUBLIC ${CMAKE_THREAD_LIBS_INIT})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-missing-field-initializers -Wno-unknown-warning-option")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-everything ")
    endif()

    set(RE2_BUILD_TESTING OFF CACHE BOOL "" FORCE)
    add_subdirectory(${_this_path}/../re2 ${CMAKE_CURRENT_BINARY_DIR}/3rdParty/re2 EXCLUDE_FROM_ALL)

    RestoreCompilerSettings()

    target_include_directories(
        ${_project_name} PUBLIC
        ${_this_path}/../re2
    )

    target_link_libraries(
        ${_project_name} PUBLIC
        re2
    )
endfunction()

Impl()
