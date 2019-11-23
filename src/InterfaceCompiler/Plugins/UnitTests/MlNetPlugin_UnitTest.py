# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Unit tests for MlNetPlugin.py"""

import os
import sys
import textwrap
import unittest
import unittest.mock
from unittest.mock import patch

import six

import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

sys.path.insert(0, os.path.join(_script_dir, ".."))
with CallOnExit(lambda: sys.path.pop(0)):
    from MlNetPlugin import Plugin

# ----------------------------------------------------------------------
class StandardSuite(unittest.TestCase):
    # ----------------------------------------------------------------------
    def setUp(self):
        self.maxDiff = None

    # ----------------------------------------------------------------------
    def test_Properties(self):
        self.assertEqual(Plugin.Name, "ML.NET")
        self.assertEqual(
            Plugin.Description,
            "Creates C++ and C# Wrappers around C++ code for use in ML.NET",
        )

    # ----------------------------------------------------------------------
    def test_GetRequiredMetadataNames(self):
        self.assertEqual(Plugin.GetRequiredMetadataNames(), [])

    def test_GetAdditionalGeneratorFilenames(self):
        additionalFilenames = Plugin.GetAdditionalGeneratorFilenames()

        self.assertEqual(len(additionalFilenames), 4)
        self.assertTrue("CreateCMakeFile" in additionalFilenames[0])
        self.assertTrue("CreateCppWrapper" in additionalFilenames[1])
        self.assertTrue("CreateCsFile" in additionalFilenames[2])
        self.assertTrue("CreateCsInstructions" in additionalFilenames[3])

    # ----------------------------------------------------------------------
    def test_GenerateOutputFilenames(self):
        self.assertEqual(
            list(Plugin.GenerateOutputFilenames(self._CreateSingleFunctionInput())),
            [
                "output_name.wrapper.cpp",
                "CMakeLists.txt",
                "CSharpCompileInstructions.txt",
                "output_nameAdd.cs"
            ],
        )

    # ----------------------------------------------------------------------
    @patch("MlNetPlugin.CreateCsInstructions")
    @patch("MlNetPlugin.CreateCMakeFile")
    @patch("MlNetPlugin.CreateCsFile")
    @patch("MlNetPlugin.CreateCppWrapper")
    def test_ExecuteOneInputFile(self, cpp_mock, cs_mock, cmake_mock, cs_instructions_mock):
        cpp_mock.return_value = 0
        cs_mock.return_value = 0
        cmake_mock.return_value = 0
        cs_instructions_mock.return_value = 0

        status_stream_mock = unittest.mock.MagicMock()
        verbose_stream_mock = unittest.mock.MagicMock()

        context = self._CreateSingleFunctionInput()
        context["output_filenames"] = Plugin.GenerateOutputFilenames(context)

        result = Plugin.Execute(
            invoke_reason="An interesting invoke reason",
            context = context,
            status_stream=status_stream_mock,
            verbose_stream=verbose_stream_mock,
            verbose=False,
        )

        self.assertEqual(result, None)
        self.assertEqual(cpp_mock.call_args[0][0], "output_name.wrapper.cpp")
        self.assertEqual(cmake_mock.call_args[0][0], "CMakeLists.txt")
        self.assertEqual(cs_instructions_mock.call_args[0][0], "CSharpCompileInstructions.txt")
        self.assertEqual(cs_mock.call_args[0][1], "output_nameAdd.cs")

        self.assertEqual(cpp_mock.call_count, 1)
        self.assertEqual(cmake_mock.call_count, 1)
        self.assertEqual(cs_instructions_mock.call_count, 1)
        self.assertEqual(cs_mock.call_count, 1)

        self.assertEqual(len(status_stream_mock.method_calls), 8)
        self.assertEqual(status_stream_mock.method_calls[0][0], "write")
        self.assertEqual(
            status_stream_mock.method_calls[0][1][0],
            "'output_name.wrapper.cpp'...",
        )
        self.assertEqual(
            status_stream_mock.method_calls[2][1][0],
            "'output_nameAdd.cs'...",
        )
        self.assertEqual(
            status_stream_mock.method_calls[4][1][0],
            "'CMakeLists.txt'...",
        )
        self.assertEqual(
            status_stream_mock.method_calls[6][1][0],
            "'CSharpCompileInstructions.txt'...",
        )
        self.assertEqual(status_stream_mock.method_calls[7][0], "DoneManager")
        self.assertTrue(not status_stream_mock.method_calls[7][1])
        
        self.assertTrue(not verbose_stream_mock.mock_calls)

    @patch("MlNetPlugin.CreateCsInstructions")
    @patch("MlNetPlugin.CreateCMakeFile")
    @patch("MlNetPlugin.CreateCsFile")
    @patch("MlNetPlugin.CreateCppWrapper")
    def test_ExecuteTwoInputFiles(self, cpp_mock, cs_mock, cmake_mock, cs_instructions_mock):
        cpp_mock.return_value = 0
        cs_mock.return_value = 0
        cmake_mock.return_value = 0
        cs_instructions_mock.return_value = 0

        status_stream_mock = unittest.mock.MagicMock()
        verbose_stream_mock = unittest.mock.MagicMock()

        context = self._CreateTwoFileTwoFunctionInput()
        context["output_filenames"] = Plugin.GenerateOutputFilenames(context)

        result = Plugin.Execute(
            invoke_reason="An interesting invoke reason",
            context = context,
            status_stream=status_stream_mock,
            verbose_stream=verbose_stream_mock,
            verbose=False,
        )

        self.assertEqual(result, None)
        self.assertEqual(cpp_mock.call_args[0][0], "output_name.wrapper.cpp")
        self.assertEqual(cmake_mock.call_args[0][0], "CMakeLists.txt")
        self.assertEqual(cs_instructions_mock.call_args[0][0], "CSharpCompileInstructions.txt")
        self.assertEqual(cs_mock.call_args_list[0][0][1], "output_nameAdd.cs")
        self.assertEqual(cs_mock.call_args_list[1][0][1], "output_nameSubtract.cs")

        self.assertEqual(cpp_mock.call_count, 1)
        self.assertEqual(cmake_mock.call_count, 1)
        self.assertEqual(cs_instructions_mock.call_count, 1)
        self.assertEqual(cs_mock.call_count, 2)

        self.assertEqual(len(status_stream_mock.method_calls), 10)
        self.assertEqual(status_stream_mock.method_calls[0][0], "write")
        self.assertEqual(
            status_stream_mock.method_calls[0][1][0],
            "'output_name.wrapper.cpp'...",
        )
        self.assertEqual(
            status_stream_mock.method_calls[2][1][0],
            "'output_nameAdd.cs'...",
        )
        self.assertEqual(
            status_stream_mock.method_calls[4][1][0],
            "'output_nameSubtract.cs'...",
        )
        self.assertEqual(
            status_stream_mock.method_calls[6][1][0],
            "'CMakeLists.txt'...",
        )
        self.assertEqual(
            status_stream_mock.method_calls[8][1][0],
            "'CSharpCompileInstructions.txt'...",
        )
        self.assertEqual(status_stream_mock.method_calls[9][0], "DoneManager")
        self.assertTrue(not status_stream_mock.method_calls[9][1])
        
        self.assertTrue(not verbose_stream_mock.mock_calls)


    @classmethod
    def _CreateSingleFunctionInput(cls):
            function = cls._CreateFunction("Add", 
                ["a", "b"],
                "int",
                ["int", "int"],
                ["int", "int"],
                "int"
            )

            intermediate_object = {
                "function_list" : [function],
                "include_list" : []
            }

            plugin_context = {
                "file_name" : intermediate_object
            }

            result = {
                "plugin_context" : plugin_context,
                "output_name" : "output_name",
                "inputs" : [os.path.join("Temp", "one.cpp")],
                "output_dir" : "output_directory",
                "plugin_settings": { 
                    "binary_version" : "2.3.4"
                } 
            }

            return result
    
    @classmethod
    def _CreateTwoFileTwoFunctionInput(cls):
            function_one = cls._CreateFunction("Add", 
                ["a", "b"],
                "int",
                ["int", "int"],
                ["int", "int"],
                "int"
            )
            
            function_two = cls._CreateFunction("Subtract", 
                ["a", "b"],
                "int",
                ["int", "int"],
                ["int", "int"],
                "int"
            )

            intermediate_object_one = {
                "function_list" : [function_one],
                "include_list" : []
            }

            intermediate_object_two = {
                "function_list" : [function_two],
                "include_list" : []
            }

            plugin_context = {
                "file_name_one" : intermediate_object_one,
                "file_name_two" : intermediate_object_two
            }

            result = {
                "plugin_context" : plugin_context,
                "output_name" : "output_name",
                "inputs" : [os.path.join("Temp", "one.cpp")],
                "output_dir" : "output_directory",
                "plugin_settings": { 
                    "binary_version" : "2.3.4"
                } 
            }

            return result
    
    @staticmethod
    def _CreateFunction(func_name, var_names, simple_return_type, raw_var_type, simple_var_types, raw_return_type):
        function = {}
        function["func_name"] = func_name
        function["var_names"] = var_names
        function["raw_var_types"] = raw_var_type
        function["simple_return_type"] = simple_return_type
        function["simple_var_types"] = simple_var_types
        function["raw_return_type"] = raw_return_type

        return function



# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(
            unittest.main(
                verbosity=2,
            ),
        )
    except KeyboardInterrupt:
        pass
