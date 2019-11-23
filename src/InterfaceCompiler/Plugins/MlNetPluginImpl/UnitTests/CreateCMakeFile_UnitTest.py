# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Unit tests for CreateCMakeFile.py"""

import os
import sys
import textwrap
import unittest
import unittest.mock

import six

import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

sys.path.insert(0, os.path.join(_script_dir, "..", ".."))
with CallOnExit(lambda: sys.path.pop(0)):
    from MlNetPluginImpl import CreateCMakeFile

# ----------------------------------------------------------------------
class StandardSuite(unittest.TestCase):
    # ----------------------------------------------------------------------
    def setUp(self):
        self.maxDiff = None

    # ----------------------------------------------------------------------
    def test_Standard(self):
        with unittest.mock.patch("MlNetPluginImpl.CreateCMakeFile.open") as mocked:
            sink = six.moves.StringIO()
            sink.close = lambda: None

            mocked.return_value = sink

            result = CreateCMakeFile.CreateCMakeFile(
                "TestOutputFilename",
                None,
                "TestOutputName",
                ["one.cpp", "two.cpp"],
                "generated.wrapper.cpp",
                lambda prefix: "{}The file header!\n".format(prefix),
                binary_version="2.3.4",
            )
            sink = sink.getvalue()

            self.assertEqual(result, 0)
            self.assertEqual(
                sink,
                textwrap.dedent(
                    """\
                    # The file header!
                    cmake_minimum_required(VERSION 3.5.0)

                    project(TestOutputName VERSION 2.3.4 LANGUAGES CXX)

                    set(CMAKE_MODULE_PATH "$ENV{DEVELOPMENT_ENVIRONMENT_CMAKE_MODULE_PATH}")
                    set(_includes "$ENV{INCLUDE}")
                    set(_libs "$ENV{LIB}")

                    if(NOT WIN32)
                        string(REPLACE ":" ";" CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}")
                        string(REPLACE ":" ";" _includes "${_includes}")
                        string(REPLACE ":" ";" _libs "${_libs}")
                    endif()

                    include(CppCommon OPTIONAL)

                    set(CMAKE_CXX_STANDARD 17)
                    set(CMAKE_CXX_STANDARD_REQUIRED ON)
                    set(CMAKE_CXX_EXTENSIONS OFF)

                    if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
                        foreach(_flag IN ITEMS
                            -Wno-missing-prototypes
                        )
                            string(APPEND CMAKE_CXX_FLAGS " ${_flag}")
                        endforeach()
                    endif()

                    add_library( TestOutputName SHARED
                        one.cpp
                        two.cpp
                        generated.wrapper.cpp
                    )

                    target_include_directories(TestOutputName PRIVATE ${_includes})
                    target_link_directories(TestOutputName PRIVATE ${_libs})
                    """,
                ),
            )

    def test_allFileShouldHavePosixFilenamesForCMakeFile(self):
        with unittest.mock.patch("MlNetPluginImpl.CreateCMakeFile.open") as mocked:
            sink = six.moves.StringIO()
            sink.close = lambda: None

            mocked.return_value = sink

            result = CreateCMakeFile.CreateCMakeFile(
                "TestOutputFilename",
                None,
                "TestOutputName",
                [os.path.join("Temp", "one.cpp"), os.path.join("Temp", "two.cpp")],
                "generated.wrapper.cpp",
                lambda prefix: "{}The file header!\n".format(prefix),
                binary_version="2.3.4",
            )
            sink = sink.getvalue()

            self.assertEqual(result, 0)
            self.assertEqual(
                sink,
                textwrap.dedent(
                    """\
                    # The file header!
                    cmake_minimum_required(VERSION 3.5.0)

                    project(TestOutputName VERSION 2.3.4 LANGUAGES CXX)

                    set(CMAKE_MODULE_PATH "$ENV{DEVELOPMENT_ENVIRONMENT_CMAKE_MODULE_PATH}")
                    set(_includes "$ENV{INCLUDE}")
                    set(_libs "$ENV{LIB}")

                    if(NOT WIN32)
                        string(REPLACE ":" ";" CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}")
                        string(REPLACE ":" ";" _includes "${_includes}")
                        string(REPLACE ":" ";" _libs "${_libs}")
                    endif()

                    include(CppCommon OPTIONAL)

                    set(CMAKE_CXX_STANDARD 17)
                    set(CMAKE_CXX_STANDARD_REQUIRED ON)
                    set(CMAKE_CXX_EXTENSIONS OFF)

                    if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
                        foreach(_flag IN ITEMS
                            -Wno-missing-prototypes
                        )
                            string(APPEND CMAKE_CXX_FLAGS " ${_flag}")
                        endforeach()
                    endif()

                    add_library( TestOutputName SHARED
                        Temp/one.cpp
                        Temp/two.cpp
                        generated.wrapper.cpp
                    )

                    target_include_directories(TestOutputName PRIVATE ${_includes})
                    target_link_directories(TestOutputName PRIVATE ${_libs})
                    """,
                ),
            )

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(unittest.main(verbosity=2))
    except KeyboardInterrupt:
        pass
