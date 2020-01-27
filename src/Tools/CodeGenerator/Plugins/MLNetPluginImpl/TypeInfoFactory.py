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
    """Creates constructs useful when generating code for a specific type"""

    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    class Result(object):
        """Result information about a type when it is used in various scenarios"""

        # ----------------------------------------------------------------------
        def __init__(
            self,
            parameter_decl,
            validation_statements,
            invocation_statement,
            conversion_end,
            delete_transformed_data,
        ):
            self.ParameterDecl              = parameter_decl
            self.ValidationStatements       = validation_statements
            self.InvocationStatement        = invocation_statement
            self.ConversionEnd              = conversion_end
            self.DeleteTransformedData      = delete_transformed_data

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

    # ----------------------------------------------------------------------
    @Interface.abstractproperty
    def CSharpType(self):
        """C# type"""
        raise Exception("Abstract property")

    # ----------------------------------------------------------------------
    @Interface.abstractproperty
    def CSharpTypeName(self):
        """C# type name"""
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
        member_type=None,
        create_type_info_factory_func=None,
    ):
        # By default, custom structs are not used or preserved. Custom overridden
        # factories may use this information
        pass

    # ----------------------------------------------------------------------
    def __repr__(self):
        return CommonEnvironment.ObjectReprImpl(self)

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def GetNativeInputInfo(is_optional):
        """Return `Result` when the type is used as an input argument.
        """
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @staticmethod
    @Interface.abstractmethod
    def GetNativeOutputInfo(
        is_struct=False,
        featurizer_name="",
    ):
        """Return `Result` when the type is used as an output argument."""
        raise Exception("Abstract method")
