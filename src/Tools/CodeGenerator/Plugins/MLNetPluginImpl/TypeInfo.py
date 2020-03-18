# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the TypeInfo object"""

import os

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
    @Interface.abstractmethod
    def GetNativeInputInfo(self):
        """Return `Result` when the type is used as an input argument.
        """
        raise Exception("Abstract method")

    # ----------------------------------------------------------------------
    @Interface.abstractmethod
    def GetNativeOutputInfo(
        self,
        is_struct=False,
        featurizer_name="",
    ):
        """Return `Result` when the type is used as an output argument."""
        raise Exception("Abstract method")
