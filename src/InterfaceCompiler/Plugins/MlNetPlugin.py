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
        ] + super(Plugin, cls).GetAdditionalGeneratorFilenames()

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.override
    def GenerateOutputFilenames(context):
        assert "output_name" in context
        output_name = context["output_name"]

        yield "{}.cpp".format(output_name)
        yield "{}.cs".format(output_name)
        yield "CMakeLists.txt"

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
            cs_filename,
            cmake_filename,
        ) = context["output_filenames"]

        context = context["plugin_context"]

        status_stream.write("'{}'...".format(cpp_filename))
        with status_stream.DoneManager() as dm:
            dm.result = CreateCppWrapper(
                cpp_filename,
                context,
                cls._GenerateFileHeader,
            )
            if dm.result != 0:
                return dm.result

        status_stream.write("'{}'...".format(cs_filename))
        with status_stream.DoneManager() as dm:
            dm.result = CreateCsFile(
                cs_filename,
                context,
                cls._GenerateFileHeader,
            )
            if dm.result != 0:
                return dm.result

        status_stream.write("'{}'...".format(cmake_filename))
        with status_stream.DoneManager() as dm:
            dm.result = CreateCMakeFile(
                cmake_filename,
                context,
                cls._GenerateFileHeader,
            )
            if dm.result != 0:
                return dm.result
