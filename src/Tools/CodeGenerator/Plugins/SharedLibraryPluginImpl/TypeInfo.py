# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the TypeInfo object"""

import os
import re

import CommonEnvironment
from CommonEnvironment import Interface

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class TypeInfo(Interface.Interface):
    """Creates constructs useful when generating code for a specific type"""

    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    class Type(object):
        # ----------------------------------------------------------------------
        def __init__(self, type, name):
            self.Type                       = type
            self.Name                       = name

        # ----------------------------------------------------------------------
        def __repr__(self):
            return CommonEnvironment.ObjectReprImpl(self)

    # ----------------------------------------------------------------------
    class Result(object):
        """Result information about a type when it is used in various scenarios."""

        # ----------------------------------------------------------------------
        def __init__(
            self,
            parameters,
            validation_statements,
            invocation_statements,
            input_buffer_type=None,
        ):
            self.Parameters                 = parameters
            self.ValidationStatements       = validation_statements
            self.InvocationStatements       = invocation_statements
            self.InputBufferType            = input_buffer_type

        # ----------------------------------------------------------------------
        def __repr__(self):
            return CommonEnvironment.ObjectReprImpl(self)

    # ----------------------------------------------------------------------
    # |
    # |  Public Properties
    # |
    # ----------------------------------------------------------------------
    @Interface.abstractproperty
    def TypeName(self):
        """Name of the type"""
        raise Exception("Abstract property")

    @Interface.abstractproperty
    def CppType(self):
        """C++ type"""
        raise Exception("Abstract property")

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    def __init__(
        self,
        custom_structs=None,
        custom_enums=None,
        is_optional=False,
        member_type=None,
        create_type_info_func=None,
    ):
        self.CustomStructs                  = custom_structs
        self.CustomEnums                    = custom_enums
        self.IsOptional                     = is_optional

    # ----------------------------------------------------------------------
    def __repr__(self):
        return CommonEnvironment.ObjectReprImpl(self)

    # ----------------------------------------------------------------------
    @Interface.extensionmethod
    def GetCppTemplateSuffix(self, template_mapping):
        """Return the type to use when this type is used as a template"""
        return self.CppType

    # ----------------------------------------------------------------------
    @Interface.abstractmethod
    def GetInputInfo(self, arg_name, invocation_template):
        """\
        Returns information about the type when used as an input argument.

        `invocation_template` is a template string that should be formatted with
        the argument values.
        """
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @Interface.abstractmethod
    def GetInputBufferInfo(self, arg_name, invocation_template):
        """\
        Returns information about the type when used as a buffer input argument.

        `invocation_template` is a template string that should be formatted with
        the argument values.
        """
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @Interface.abstractmethod
    def GetOutputInfo(
        self,
        arg_name,
        result_name="result",
        suppress_pointer=False,
    ):
        """\
        Returns information about the type when used as an output argument.

        `result_name` is the name of the result returned by the shared library.
        """
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @Interface.abstractmethod
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        """\
        Returns information about the type when data generated by `GetOutputInfo` needs
        to be deleted by the caller.

        Return `None` if no explicit destruction functionality is required.
        """
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    # ----------------------------------------------------------------------
    # ----------------------------------------------------------------------

    # Some types generate complicated buffers to store incoming data while
    # others simply provide the pointer and items. Handle both scenarios by
    # generating the content with an easily-recognizable string; extract
    # the content within the string for later use, and then remove it from
    # the invocation contents.
    _InvocationTemplate                     = "*****{}*****"

    # ----------------------------------------------------------------------
    _invocation_statement_regex             = re.compile(
        r"\*\*\*\*\*(?P<content>.+)\*\*\*\*\*",
        re.DOTALL | re.MULTILINE,
    )

    @classmethod
    def _ExtractDecoratedInvocationStatements(cls, invocation_statements):
        """\
        Returns a decorated invocation statement and tuple containing invocation instructions
        """

        match = cls._invocation_statement_regex.search(invocation_statements)
        assert match, invocation_statements

        invocation_tuple = [item.strip() for item in match.group("content").split(",")]
        assert len(invocation_tuple) == 2, invocation_tuple

        invocation_statements = invocation_statements[:match.start()].rstrip()

        return invocation_statements, invocation_tuple
