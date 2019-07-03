# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the Plugin object"""

import os
import sys


import CommonEnvironment
from CommonEnvironment.CallOnExit import CallOnExit
from CommonEnvironment import Interface

from MlNetPluginImpl.CreateCMakeFile import CreateCMakeFile
from MlNetPluginImpl.CreateCppWrapper import CreateCppWrapper
from MlNetPluginImpl.CreateCsFile import CreateCsFile
from MlNetPluginImpl.CreateCsInstructions import CreateCsInstructions

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

sys.path.insert(0, os.path.join(_script_dir, ".."))
with CallOnExit(lambda: sys.path.pop(0)):
    from Plugin import PluginBase

# ----------------------------------------------------------------------
@Interface.staticderived
class Plugin(PluginBase):
    # ----------------------------------------------------------------------
    # |  Properties
    Name                                    = Interface.DerivedProperty("ML.NET")
    Description                             = Interface.DerivedProperty("Creates C++ and C# Wrappers around C++ code for use in ML.NET")

    # ----------------------------------------------------------------------
    # |  Methods
    @staticmethod
    @Interface.override
    def GetRequiredMetadataNames():
        return []

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GenerateCustomMetadataSettingsAndDefaults(cls):
        # TODO: yield any custom settings here
        yield ("binary_version", "1.0.0")
        yield from super(Plugin, cls).GenerateCustomMetadataSettingsAndDefaults()

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetAdditionalGeneratorFilenames(cls):
        import inspect

        return [
            inspect.getfile(CreateCMakeFile),
            inspect.getfile(CreateCppWrapper),
            inspect.getfile(CreateCsFile),
            inspect.getfile(CreateCsInstructions),
        ] + super(Plugin, cls).GetAdditionalGeneratorFilenames()

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.override
    def GenerateOutputFilenames(context):
        assert "output_name" in context
        output_name = context["output_name"]

        yield "{}.wrapper.cpp".format(output_name)
        yield "CMakeLists.txt"
        yield "CSharpCompileInstructions.txt"

        # C# creates one .cs class per function, so we are loopiong through
        # all the function names to correctly determine the .cs file name.

        for value in context["plugin_context"].values():
            function_list = value["function_list"]
            for function in function_list:
                function_name = function["func_name"]
                yield "{}{}.cs".format(output_name, function_name)
        

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def Execute(
        cls,
        invoke_reason,
        context,
        status_stream,
        verbose_stream,
        verbose,
    ):
        (
            cpp_filename,
            cmake_filename,
            cs_instructions,
            *cs_filenames,
        ) = context["output_filenames"]

        plugin_context = context["plugin_context"]

        status_stream.write("'{}'...".format(cpp_filename))
        with status_stream.DoneManager() as dm:
            dm.result = CreateCppWrapper(
                cpp_filename,
                plugin_context,
                cls._GenerateFileHeader,
            )
            if dm.result != 0:
                return dm.result

        for value in plugin_context.values():
            function_list = value["function_list"]
            for function, file_name in zip(function_list, cs_filenames):
                status_stream.write("'{}'...".format(file_name))
                with status_stream.DoneManager() as dm:
                    dm.result = CreateCsFile(
                        function,
                        file_name,
                        context["output_name"],
                        cls._GenerateFileHeader,
                    )
                    if dm.result != 0:
                        return dm.result

        status_stream.write("'{}'...".format(cmake_filename))
        with status_stream.DoneManager() as dm:
            dm.result = CreateCMakeFile(
                cmake_filename,
                plugin_context,
                context["output_name"],
                context["inputs"],
                cpp_filename,
                cls._GenerateFileHeader,
                binary_version=context["plugin_settings"]["binary_version"],
            )
            if dm.result != 0:
                return dm.result

        status_stream.write("'{}'...".format(cs_instructions))
        with status_stream.DoneManager() as dm:
            dm.result = CreateCsInstructions(
                cs_instructions,
                context["output_name"],
                context["output_dir"],
                cls._GenerateFileHeader,
            )
            if dm.result != 0:
                return dm.result
