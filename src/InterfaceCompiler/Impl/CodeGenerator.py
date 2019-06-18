# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the CodeGenerator object"""

import os

from collections import OrderedDict

import six

import CommonEnvironment
from CommonEnvironment import Interface

from CommonEnvironment.CompilerImpl.CodeGenerator import CodeGenerator as CodeGeneratorBase
from CommonEnvironment.CompilerImpl.InputProcessingMixin.AtomicInputProcessingMixin import AtomicInputProcessingMixin
from CommonEnvironment.CompilerImpl.InvocationQueryMixin.ConditionalInvocationQueryMixin import ConditionalInvocationQueryMixin
from CommonEnvironment.CompilerImpl.OutputMixin.MultipleOutputMixin import MultipleOutputMixin

from CommonEnvironment.TypeInfo.FundamentalTypes.All import CreateFromPythonType
from CommonEnvironment.TypeInfo.FundamentalTypes.FilenameTypeInfo import FilenameTypeInfo
from CommonEnvironment.TypeInfo.FundamentalTypes.Serialization.StringSerialization import StringSerialization

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
def CreateCodeGenerator(plugin):
    # ----------------------------------------------------------------------
    # <Too many ancestors> pylint: disable = R0901
    @Interface.staticderived
    class CodeGenerator(
        AtomicInputProcessingMixin,
        ConditionalInvocationQueryMixin,
        MultipleOutputMixin,
        CodeGeneratorBase,
    ):
        # ----------------------------------------------------------------------
        # |
        # |  Properties
        # |
        # ----------------------------------------------------------------------
        Name                                    = Interface.DerivedProperty("Interface Compiler")
        Description                             = Interface.DerivedProperty("Extracts C++ methods and generates code according to the specified plugin")
        InputTypeInfo                           = Interface.DerivedProperty(
            FilenameTypeInfo(
                validation_expression=r".+(?:\.c|\.cpp|\.cc|\.h|\.hpp)",
            ),
        )

        # ----------------------------------------------------------------------
        # |
        # |  Private Methods
        # |
        # ----------------------------------------------------------------------
        @classmethod
        @Interface.override
        def _GetRequiredMetadataNames(cls):
            return ["plugin_name", "output_name",] + super(CodeGenerator, cls)._GetRequiredMetadataNames()

        # ----------------------------------------------------------------------
        @classmethod
        @Interface.override
        def _GetOptionalMetadata(cls):
            return [("plugin_settings", {}),] + super(CodeGenerator, cls)._GetOptionalMetadata()

        # ----------------------------------------------------------------------
        @classmethod
        @Interface.override
        def _CreateContext(cls, metadata, status_stream):
            # Ensure that all plugin settings are present and that they are the
            # expected type.
            custom_settings = OrderedDict([(k, v) for k, v in plugin.GenerateCustomMetadataSettingsAndDefaults()])

            assert "plugin_settings" in metadata
            plugin_settings = metadata["plugin_settings"]

            for k, v in six.iteritems(plugin_settings):
                if k not in custom_settings:
                    raise Exception("'{}' is not a valid plugin setting".format(k))

                desired_type = type(custom_settings[k])

                if type(v) != desired_type: # <prefer isinstance> pylint: disable = C0123
                    assert isinstance(v, six.string_types), (v, type(v))
                    plugin_settings[k] = StringSerialization.DeserializeItem(CreateFromPythonType(desired_type), v)

            for k, v in six.iteritems(custom_settings):
                if k not in plugin_settings:
                    plugin_settings[k] = v

            # Ensure that the required metadata is present
            for required in plugin.GetRequiredMetadataNames():
                if required not in plugin_settings:
                    raise Exception("'{}' is required but was not found".format(required))

            metadata["plugin_settings"] = plugin.PreprocessMetadata(plugin_settings)

            context = plugin.PreprocessContext(metadata)
            context["output_filenames"] = [os.path.join(context["output_dir"], filename) for filename in plugin.GenerateOutputFilenames(context)]
            context = plugin.PostprocessContext(context)

            return super(CodeGenerator, cls)._CreateContext(context, status_stream)

        # ----------------------------------------------------------------------
        @classmethod
        @Interface.override
        def _GetAdditionalGeneratorItems(cls, context):
            return plugin.GetAdditionalGeneratorFilenames() + super(CodeGenerator, cls)._GetAdditionalGeneratorItems(context)

        # ----------------------------------------------------------------------
        @staticmethod
        @Interface.override
        def _InvokeImpl(
            invoke_reason,
            context,
            status_stream,
            verbose_stream,
            verbose,
        ):
            return plugin.Execute(invoke_reason, context, status_stream, verbose_stream, verbose)

    # ----------------------------------------------------------------------

    return CodeGenerator
