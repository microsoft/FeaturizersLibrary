# This is implemented as a function to provide scope for local variables
function(Impl)
    set(_project_name Featurizer3rdParty)
    get_filename_component(_this_path ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)

    # Retrieve the submodules
    execute_process(COMMAND "git submodule update --init --recursive")

    # BugBug: Only invoke if HEAD is different

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
    # BugBug add_subdirectory(${_this_path}/../re2 ${CMAKE_CURRENT_BINARY_DIR}/3rdParty/re2 EXCLUDE_FROM_ALL)
    # BugBug set_target_properties(re2 PROPERTIES FOLDER "BugBug/External/re2")
    # BugBug add_library(re2::re2 ALIAS STATIC re2)
    # BugBug # BugBug add_library(re2::re2 STATIC re2)
    # BugBug set(RE2_INCLUDE_DIR ${_this_path}/../re2)





    # BugBug set(_prev_build_shared_libs ${BUILD_SHARED_LIBS})
    # BugBug set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
    # BugBug set(RE2_BUILD_TESTING OFF CACHE BOOL "" FORCE)

    add_subdirectory(${_this_path}/../re2 ${CMAKE_CURRENT_BINARY_DIR}/3rdParty/re2 EXCLUDE_FROM_ALL)
    # BugBug add_library(Featurizers3rdParty STATIC IMPORTED DEPENDS RE2) # BugBug
    # BugBug set(BUILD_SHARED_LIBS ${_prev_build_shared_libs} CACHE BOOL "" FORCE)

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
