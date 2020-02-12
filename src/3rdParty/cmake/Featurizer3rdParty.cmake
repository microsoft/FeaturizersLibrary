# This is implemented as a function to provide scope for local variables
function(Impl)
    set(_project_name Featurizer3rdParty)
    get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

    # Retrieve the submodules
    message(STATUS "# ----------------------------------------------------------------------")
    message(STATUS "# |")
    message(STATUS "# |  git submodule update --init --recursive")
    message(STATUS "# |")
    message(STATUS "# ----------------------------------------------------------------------")
    execute_process(COMMAND "git submodule update --init --recursive")

    # BugBug: Only invoke if HEAD is different

    message(STATUS "# ----------------------------------------------------------------------")
    message(STATUS "# |")
    message(STATUS "# |  Building ${_this_path}")
    message(STATUS "# |")
    message(STATUS "# ----------------------------------------------------------------------")

    add_library(${_project_name} STATIC
        ${_this_path}/../date.h
        ${_this_path}/../iso_week.h
        ${_this_path}/../json.h
        ${_this_path}/../MurmurHash3.cpp
        ${_this_path}/../MurmurHash3.h
        ${_this_path}/../optional.h
    )

    message(STATUS "# ----------------------------------------------------------------------")
    message(STATUS "# |")
    message(STATUS "# |  Building re2")
    message(STATUS "# |")
    message(STATUS "# ----------------------------------------------------------------------")

    set(_prev_build_shared_libs ${BUILD_SHARED_LIBS})
    set(BUILD_SHARED_LIBS ON)
    set(RE2_BUILD_TESTING OFF)

    add_subdirectory(${_this_path}/../re2 ${CMAKE_CURRENT_BINARY_DIR}/3rdParty/re2 EXCLUDE_FROM_ALL)

    set(BUILD_SHARED_LIBS ${_prev_build_shared_libs})

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
