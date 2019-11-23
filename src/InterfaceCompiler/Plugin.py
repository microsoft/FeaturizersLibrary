# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the PluginBase object"""

import datetime
import os
import textwrap

import CommonEnvironment
from CommonEnvironment import FileSystem
from CommonEnvironment import Interface
from CommonEnvironment.StreamDecorator import StreamDecorator

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class PluginBase(Interface.Interface):
    """Abstract base class for plugins that generate source for methods exposed in C++.

    There are multiple ways that a plugin can modify the data used to ultimately
    generate new code. At a high level, the work flow is as follows. Subitems
    represent extension points where a plugin may customize the process (see each
    method description for additional information).

        1) Metadata is extracted from the environment and command line arguments.
        2) Context is created from the metadata and any default values provided by the plugin.
            A) GetRequiredMetadataNames
            B) GenerateCustomMetadataSettingsAndDefaults
            C) PreprocessMetadata
            D) PreprocessContext
            E) PostprocessContext
        3) Context is passed to the plugin during execution.
    """

    # ----------------------------------------------------------------------
    # |
    # |  Public Properties
    # |
    # ----------------------------------------------------------------------
    @Interface.abstractproperty
    def Name(self):
        """Name of the plugin - this will be used on the command line and should be unique across all plugins"""
        raise Exception("Abstract property")

    # ----------------------------------------------------------------------
    @Interface.abstractproperty
    def Description(self):
        """Description of the plugin - this will be displayed on the command line"""
        raise Exception("Abstract property")

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.extensionmethod
    def IsValidEnvironment():
        """Return an error string if the current environment is not suitable for execution of this plugin"""

        # By default, the environment is suitable
        return None

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.extensionmethod
    def GetAdditionalGeneratorFilenames():
        """Return filenames of Python source code that implements the code generation process.

        When a user invoked the code generation process, metrics will be used to determine
        if code generation is necessary (updates to the input files, changes to arguments, etc.).
        This query helps ensure that actual code generation is invoked only when necessary
        (a trait that is especially helpful if the code generation process is expensive).

        One of the metrics used is to check if any Python source files used in the code
        generation process have been updated since the last generation took place.

        BY DEFAULT, the code will only check the Python source code file used to implement
        the concrete Python class that derived from this base class.

        ONLY IMPLEMENT THIS METHOD IF YOUR PLUGIN IS IMPLEMENTED ACROSS MULTIPLE PYTHON
        SOURCE CODE FILES.

        Returns (List[str]):
            List of filenames that should be queried when determining if code should be generated.

        """

        # No additional source files are used in the implementation of the derived plugin
        return []

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def GetRequiredMetadataNames():
        """Returns a list of names that must be present in the metadata collection.

        Returns (List[string]):
            Names that must be a part of the provided metadata.

        """
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.extensionmethod
    def GenerateCustomMetadataSettingsAndDefaults():
        """Generator that provides metadata settings and default values (if the setting isn't provided).

        Returns (Generator[(string, Any)]):
            Generates tuples of attribute names and default values to use if a value
            wasn't otherwise provided.
        """

        # No items by default

        # Funky syntax is to ensure that this method is a generator
        if False:
            yield

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.extensionmethod
    def PreprocessMetadata(metadata):
        """Opportunity to decorate the metadata before it is converted into context.

        The method is optional; the default behavior is to not provide any decoration.

        Args:
            metadata (Dict[string, Any]):
                Metadata to process.

        Returns (Dict[string, Any]):
            The decorated metadata.

        """

        # No decoration by default
        return metadata

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.extensionmethod
    def PreprocessContext(context):
        """Opportunity to decorate the context before it is modified by other compiler mixins.

        The method is optional; the default behavior is to not provide any decoration.

        Args:
            context (Dict[string, Any]):
                Context to process.

        Returns (Dict[string, Any]):
            The decorated Context.

        """

        # No decoration by default
        return context

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def GenerateOutputFilenames(context):
        """All output filenames for the content produced by the CodeGenerator.

        Args:
            context (Dict[string, Any]):
                Context used to determine the files and/or filenames to generate.

        Returns (Generator[string]):
            The filenames that will be generated.

        """
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.extensionmethod
    def PostprocessContext(context):
        """Opportunity to decorate the context before it is Executed.

        This method is optional; the default behavior is to not provide any decoration.

        A longer description that may span multiple lines.

        Args:
            context (Dict[string, Any]):
                Context to process.

        Returns (Dict[string, Any]):
            The decorated Context.

        """

        # No decoration by default
        return context

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def Execute(
        invoke_reason,
        context,
        status_stream,
        verbose_stream,
        verbose,
    ):
        """Executes the plugin.

        Args:
            invoke_reason (int):
                Integer value specifying why the plugin is being invoked (output not found, input changes, plugin source code changes, etc.)

            context (Dict[string, Any]):
                The Context to use when generating code.

            status_stream (file-like):
                Output stream used to generate short status messages.

            verbose_stream (file-like):
                Output stream used to generate verbose messages (only displayed when verbose is set to True)

            verbose (bool):
                True if the CodeGenerator was called with verbose.

        Returns (int):
            Return code.

        """
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.extensionmethod
    def Clean(context, status_stream):
        """Cleans content previously generated.

        The default behavior is to delete the output directory.

        Args:
            context (Dict[string, Any]):
                The Context to use when generating code.

            status_stream (file-like):
                Output stream used to generate short status messages.

        Returns (int):
            Return code.

        """

        assert "output_dir" in context, context
        output_dir = context["output_dir"]

        if not os.path.isdir(output_dir):
            status_stream.write("The output directory '{}' does not exist.\n".format(output_dir))
        else:
            status_stream.write("Removing '{}'...".format(output_dir))
            with status_stream.DoneManager():
                FileSystem.RemoveTree(output_dir)

        return 0

    # ----------------------------------------------------------------------
    # |
    # |  Protected Methods
    # |
    # ----------------------------------------------------------------------
    @classmethod
    def _GenerateFileHeader(
        cls,
        prefix="",
        line_break="--------------------------------------------------------------------------------",
        filename_parts=3,
        filename_prefix=None,
        callstack_offset=0,
    ):
        """Helper method that creates a "this is a generated file so do not modify"-style comment header.

        This method can be used by derived classes to output consistent headers that can be written at the
        beginning of any generated files. A consistent header message helps people to understand that they
        shouldn't modify the file directly (especially if it is checked in).

        Args:
            prefix (str):
                The comment prefix (the value depends on the language of the file being generated).

            line_break (str):
                Text used for line breaks.

            filename_parts (int):
                Only include the last N parts of the Python file used to generate the code. By only keeping
                the last N parts, we ensure a display string that is consistent when generated on different
                machines (that may have different paths).

            filename_prefix (str):
                Optional text to prepend to filenames after the last N parts have been calculated. This can be
                useful in providing general context to a file's location.

            callstack_offset (int):
                When calculating the name of the python file to display, use the callstack frame plus this offset.

        Returns (str):
            The generated header.

        """

        import inspect

        frame = inspect.stack()[callstack_offset + 1][0]
        filename = frame.f_code.co_filename

        filename = "/".join(filename.split(os.path.sep)[-filename_parts:])

        return textwrap.dedent(
            """\
            {prefix}{line_break}
            {prefix}|
            {prefix}|  WARNING:
            {prefix}|  This file was generated; any local changes will be overwritten during
            {prefix}|  future invocations of the generator!
            {prefix}|
            {prefix}|  Generated by: {by}
            {prefix}|  Generated on: {now}
            {prefix}|
            {prefix}{line_break}
            """,
        ).format(
            prefix=prefix,
            line_break=line_break,
            by="{}{}".format(filename_prefix or '', filename),
            now=str(datetime.datetime.now()),
        )
