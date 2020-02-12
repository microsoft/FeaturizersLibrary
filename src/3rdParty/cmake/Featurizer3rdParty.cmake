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

    # Add re2
    set(RE2_BUILD_TESTING OFF CACHE BOOL "" FORCE)
    add_subdirectory(${_this_path}/../re2 ${CMAKE_CURRENT_BINARY_DIR}/3rdParty/re2 EXCLUDE_FROM_ALL)

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
