# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Methods that help when creating the CMake wrapper"""

import os
import textwrap
from pathlib import Path

import CommonEnvironment
from CommonEnvironment import StringHelpers

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
# <unused argument> pylint: disable = W0613
def CreateCMakeFile(
    output_filename,
    data,
    output_name,
    input_filenames,
    cpp_wrapper_filename,
    generate_header_func,
    binary_version="1.0.0",
):
    output = [generate_header_func("# ")]

    output.append(
        textwrap.dedent(
            """\
            cmake_minimum_required(VERSION 3.5.0)

            project({output_name} VERSION {binary_version} LANGUAGES CXX)

            set(CMAKE_MODULE_PATH "$ENV{{DEVELOPMENT_ENVIRONMENT_CMAKE_MODULE_PATH}}")
            set(_includes "$ENV{{INCLUDE}}")
            set(_libs "$ENV{{LIB}}")

            if(NOT WIN32)
                string(REPLACE ":" ";" CMAKE_MODULE_PATH "${{CMAKE_MODULE_PATH}}")
                string(REPLACE ":" ";" _includes "${{_includes}}")
                string(REPLACE ":" ";" _libs "${{_libs}}")
            endif()

            include(CppCommon)

            set(CMAKE_CXX_STANDARD 17)
            set(CMAKE_CXX_STANDARD_REQUIRED ON)
            set(CMAKE_CXX_EXTENSIONS OFF)

            if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
                foreach(_flag IN ITEMS
                    -Wno-missing-prototypes
                )
                    string(APPEND CMAKE_CXX_FLAGS " ${{_flag}}")
                endforeach()
            endif()

            add_library( {output_name} SHARED
                {filenames}
            )

            target_include_directories({output_name} PRIVATE ${{_includes}})
            target_link_directories({output_name} PRIVATE ${{_libs}})
            """,
        ).format(
            output_name=output_name,
            binary_version=binary_version,
            filenames=StringHelpers.LeftJustify(Path("\n".join(input_filenames + [cpp_wrapper_filename])).as_posix(), 4).rstrip(),
        ),
    )

    with open(output_filename, "w") as f:
        f.write("".join(output))

    return 0
