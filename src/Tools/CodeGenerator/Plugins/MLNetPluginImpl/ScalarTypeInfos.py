# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the scalar type info objects"""

import os
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.MLNetPluginImpl.TypeInfo import TypeInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
class _ScalarTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    @Interface.override
    def GetNativeInputInfo(self):
        if self.IsOptional:
            decl = "{}* input".format(self.CSharpType)

            invocation_statement = textwrap.dedent(
                """\
                {}* interopInput;
                \t\t\t\t\tif (_parent._options.TreatDefaultAsNull && input == default)
                    \t\t\t\t\tinteropInput = null;
                \t\t\t\t\telse
                    \t\t\t\t\tinteropInput = &input;
                """,
            ).format(self.CSharpType)

        else:
            decl = "{} input".format(self.CSharpType)
            invocation_statement = "{} interopInput = input;".format(self.CSharpType)

        return self.Result(decl, None, invocation_statement, "", "")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetNativeOutputInfo(
        self,
        is_struct=False,
        featurizer_name="",
    ):
        decl = "out {} interopOutput".format(self.CSharpType)
        invocation_statement = "{} output = interopOutput;".format(self.CSharpType)

        return self.Result(decl, None, invocation_statement, "", "")


# ----------------------------------------------------------------------
class _FloatingPointTypeInfo(_ScalarTypeInfo):

    # ----------------------------------------------------------------------
    @Interface.override
    def GetNativeInputInfo(self):
        if self.IsOptional:
            decl = "{}* input".format(self.TypeName)
            invocation_statement = "{}* interopInput = &input;".format(self.CSharpType)
        else:
            decl = "{} input".format(self.TypeName)
            invocation_statement = "{} interopInput = input;".format(self.CSharpType)

        return self.Result(decl, None, invocation_statement, "", "")


# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
@Interface.staticderived
class Int8TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("int8")
    CSharpType                              = Interface.DerivedProperty("sbyte")
    CSharpTypeName                          = Interface.DerivedProperty("Int8")


# ----------------------------------------------------------------------
@Interface.staticderived
class Int16TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("int16")
    CSharpType                              = Interface.DerivedProperty("short")
    CSharpTypeName                          = Interface.DerivedProperty("Int16")


# ----------------------------------------------------------------------
@Interface.staticderived
class Int32TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("int32")
    CSharpType                              = Interface.DerivedProperty("int")
    CSharpTypeName                          = Interface.DerivedProperty("Int32")


# ----------------------------------------------------------------------
@Interface.staticderived
class Int64TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("int64")
    CSharpType                              = Interface.DerivedProperty("long")
    CSharpTypeName                          = Interface.DerivedProperty("Int64")


# ----------------------------------------------------------------------
@Interface.staticderived
class UInt8TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("uint8")
    CSharpType                              = Interface.DerivedProperty("byte")
    CSharpTypeName                          = Interface.DerivedProperty("UInt8")


# ----------------------------------------------------------------------
@Interface.staticderived
class UInt16TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("uint16")
    CSharpType                              = Interface.DerivedProperty("ushort")
    CSharpTypeName                          = Interface.DerivedProperty("UInt16")


# ----------------------------------------------------------------------
@Interface.staticderived
class UInt32TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("uint32")
    CSharpType                              = Interface.DerivedProperty("uint")
    CSharpTypeName                          = Interface.DerivedProperty("UInt32")


# ----------------------------------------------------------------------
@Interface.staticderived
class UInt64TypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("uint64")
    CSharpType                              = Interface.DerivedProperty("ulong")
    CSharpTypeName                          = Interface.DerivedProperty("UInt64")


# ----------------------------------------------------------------------
@Interface.staticderived
class FloatTypeInfo(_FloatingPointTypeInfo):
    TypeName                                = Interface.DerivedProperty("float")
    CSharpType                              = Interface.DerivedProperty("float")
    CSharpTypeName                          = Interface.DerivedProperty("Float")


# ----------------------------------------------------------------------
@Interface.staticderived
class DoubleTypeInfo(_FloatingPointTypeInfo):
    TypeName                                = Interface.DerivedProperty("double")
    CSharpType                              = Interface.DerivedProperty("double")
    CSharpTypeName                          = Interface.DerivedProperty("Double")


# ----------------------------------------------------------------------
@Interface.staticderived
class BoolTypeInfo(_ScalarTypeInfo):
    TypeName                                = Interface.DerivedProperty("bool")
    CSharpType                              = Interface.DerivedProperty("bool")
    CSharpTypeName                          = Interface.DerivedProperty("Bool")
