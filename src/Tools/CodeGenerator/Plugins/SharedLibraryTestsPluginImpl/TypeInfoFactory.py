# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the TypeInfoFactory object"""

import os

import CommonEnvironment
from CommonEnvironment import Interface

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class TypeInfoFactory(Interface.Interface):
    """Creates constructs that are useful when generating test code for a specific type"""

    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    class Result(object):
        """Result information about a type when it is used in various scenarios."""

        # ----------------------------------------------------------------------
        def __init__(
            self,
            vector_result_type,
            transform_vars,
            transform_output_vars,
            append_result_statement,
            destroy_args=None,
            destroy_inline=None,
        ):
            self.VectorResultType           = vector_result_type
            self.TransformVars              = transform_vars
            self.TransformOutputVars        = transform_output_vars
            self.AppendResultStatement      = append_result_statement
            self.DestroyArgs                = destroy_args
            self.DestroyInline              = destroy_inline

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
    ):
        # By default, custom structs are not used or preserved. Custom overridden
        # factories may use this information.
        pass

    # ----------------------------------------------------------------------
    def __repr__(self):
        return CommonEnvironment.ObjectReprImpl(self)

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def GetTransformInputArgs(
        is_input_optional,
        input_name="input",
    ):
        """\
        Returns information about the type when used to create transformer-related tests.
        """
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def GetOutputInfo(
        result_name="result",
    ):
        """\
        Returns information about the type when used to create output info.
        """
        raise Exception("Abstract method")
