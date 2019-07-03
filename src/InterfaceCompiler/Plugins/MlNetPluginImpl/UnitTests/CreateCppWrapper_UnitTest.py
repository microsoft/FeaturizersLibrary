# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Unit tests for CreateCppWrapper.py"""

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
    from MlNetPluginImpl import CreateCppWrapper

# ----------------------------------------------------------------------
class StandardSuite(unittest.TestCase):
    # ----------------------------------------------------------------------
    def test_Standard(self):
        with unittest.mock.patch("MlNetPluginImpl.CreateCppWrapper.open") as mocked:
            sink = six.moves.StringIO()
            sink.close = lambda: None

            mocked.return_value = sink

            function_input = self.CreateSingleFunctionInput()

            result = CreateCppWrapper.CreateCppWrapper("ignored", function_input, lambda prefix: "{}The file header!\n".format(prefix))
            sink = sink.getvalue()

            self.assertEqual(result, 0)
            self.assertEqual(
                sink,
                textwrap.dedent(
                    """\
                    // The file header!
                    
                    #if defined(_MSC_VER)
                    #   define EXPORT __declspec(dllexport)
                    #elif defined(__GNUC__)
                    #   define EXPORT __attribute__((visibility("default")))
                    #else
                    #   error unsupported!
                    #endif
                                        
                    int Add(int, int);
                    extern "C" {
                        EXPORT int AddProxy(int a, int b) {
                            return Add(a, b);
                        }
                    }
                    """
                ),
            )

    def test_TwoFunctionsShouldBeInSameFileOneBelowTheOther(self):
        with unittest.mock.patch("MlNetPluginImpl.CreateCppWrapper.open") as mocked:
            sink = six.moves.StringIO()
            sink.close = lambda: None

            mocked.return_value = sink

            function_input = self.CreateTwoFunctionInput()

            result = CreateCppWrapper.CreateCppWrapper("ignored", function_input, lambda prefix: "{}The file header!\n".format(prefix))
            sink = sink.getvalue()

            self.assertEqual(result, 0)
            self.assertEqual(
                sink,
                textwrap.dedent(
                    """\
                    // The file header!
                    
                    #if defined(_MSC_VER)
                    #   define EXPORT __declspec(dllexport)
                    #elif defined(__GNUC__)
                    #   define EXPORT __attribute__((visibility("default")))
                    #else
                    #   error unsupported!
                    #endif
                                        
                    int Add(int, int);
                    extern "C" {
                        EXPORT int AddProxy(int a, int b) {
                            return Add(a, b);
                        }
                    }

                    int Subtract(int, int);
                    extern "C" {
                        EXPORT int SubtractProxy(int a, int b) {
                            return Subtract(a, b);
                        }
                    }
                    """
                ),
            )

    def test_FunctionWithOneParameterShouldWorkCorrectly(self):
        with unittest.mock.patch("MlNetPluginImpl.CreateCppWrapper.open") as mocked:
            sink = six.moves.StringIO()
            sink.close = lambda: None

            mocked.return_value = sink

            function_input = self.CreateFunctionOneInputParameter()

            result = CreateCppWrapper.CreateCppWrapper("ignored", function_input, lambda prefix: "{}The file header!\n".format(prefix))
            sink = sink.getvalue()

            self.assertEqual(result, 0)
            self.assertEqual(
                sink,
                textwrap.dedent(
                    """\
                    // The file header!
                    
                    #if defined(_MSC_VER)
                    #   define EXPORT __declspec(dllexport)
                    #elif defined(__GNUC__)
                    #   define EXPORT __attribute__((visibility("default")))
                    #else
                    #   error unsupported!
                    #endif
                                        
                    int Add(int);
                    extern "C" {
                        EXPORT int AddProxy(int a) {
                            return Add(a);
                        }
                    }
                    """
                ),
            )

    def test_FunctionWithNoParametersShouldWorkCorrectly(self):
        with unittest.mock.patch("MlNetPluginImpl.CreateCppWrapper.open") as mocked:
            sink = six.moves.StringIO()
            sink.close = lambda: None

            mocked.return_value = sink

            function_input = self.CreateFunctionNoInputParameters()

            result = CreateCppWrapper.CreateCppWrapper("ignored", function_input, lambda prefix: "{}The file header!\n".format(prefix))
            sink = sink.getvalue()

            self.assertEqual(result, 0)
            self.assertEqual(
                sink,
                textwrap.dedent(
                    """\
                    // The file header!
                    
                    #if defined(_MSC_VER)
                    #   define EXPORT __declspec(dllexport)
                    #elif defined(__GNUC__)
                    #   define EXPORT __attribute__((visibility("default")))
                    #else
                    #   error unsupported!
                    #endif
                                        
                    int Add();
                    extern "C" {
                        EXPORT int AddProxy() {
                            return Add();
                        }
                    }
                    """
                ),
            )
    
    """
    TESTING HELPER METHODS
    """
    def CreateFunctionOneInputParameter(self):
        result = {}
        function_list = []
        intermediate_object = {}
        function = self.CreateFunction("Add", 
            ["a"],
            "int",
            ["int"],
            ["int"],
            "int"
        )
        function_list.append(function)
        intermediate_object["function_list"] = function_list
        result["file_name"] = intermediate_object

        return result

    def CreateFunctionNoInputParameters(self):
        result = {}
        function_list = []
        intermediate_object = {}
        function = self.CreateFunction("Add", 
            [],
            "int",
            [],
            [],
            "int"
        )
        function_list.append(function)
        intermediate_object["function_list"] = function_list
        result["file_name"] = intermediate_object

        return result

    def CreateSingleFunctionInput(self):
        result = {}
        function_list = []
        intermediate_object = {}
        function = self.CreateFunction("Add", 
            ["a", "b"],
            "int",
            ["int", "int"],
            ["int", "int"],
            "int"
        )
        function_list.append(function)
        intermediate_object["function_list"] = function_list
        result["file_name"] = intermediate_object

        return result

    def CreateTwoFunctionInput(self):
        result = {}
        function_list = []
        intermediate_object = {}
        first_function = self.CreateFunction("Add", 
            ["a", "b"],
            "int",
            ["int", "int"],
            ["int", "int"],
            "int"
        )

        second_function = self.CreateFunction("Subtract", 
            ["a", "b"],
            "int",
            ["int", "int"],
            ["int", "int"],
            "int"
        )

        function_list.append(first_function)
        function_list.append(second_function)
        intermediate_object["function_list"] = function_list
        result["file_name"] = intermediate_object

        return result

    def CreateFunction(self, func_name, var_names, simple_return_type, raw_var_type, simple_var_types, raw_return_type):
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
        sys.exit(unittest.main(verbosity=2))
    except KeyboardInterrupt:
        pass
