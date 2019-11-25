# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the StringTypeInfoFactory object"""

import os
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.MLNetPluginImpl.TypeInfoFactory import TypeInfoFactory

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class StringTypeInfoFactory(TypeInfoFactory):
    # ----------------------------------------------------------------------
    # |
    # |  Public Properties
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty("string")
    CSharpType                              = Interface.DerivedProperty("ReadOnlyMemory<char>")
    CSharpTypeName                          = Interface.DerivedProperty("ReadOnlyMemoryChar")

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetNativeInputInfo(cls, is_optional):
        if is_optional:
            invocation_statement = textwrap.dedent(
                """\
                var inputAsString = input.ToString();
                \t\t\t\t\tfixed (byte* interopInput = (string.IsNullOrEmpty(inputAsString) && _parent._options.TreatDefaultAsNull) ? null : Encoding.UTF8.GetBytes(inputAsString + char.MinValue))
                \t\t\t\t\t{{
                """,
            ).format(cls.CSharpType)

        else:
            invocation_statement = textwrap.dedent(
                """\
                var inputAsString = input.ToString();
                fixed (byte* interopInput = Encoding.UTF8.GetBytes(inputAsString + char.MinValue))
                {{
                """,
            ).format(cls.CSharpType)

        decl = "byte* input"

        return cls.Result(decl, None, invocation_statement, "}", "")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetNativeOutputInfo(
        cls,
        is_struct=False,
        featurizer_name="",
    ):
        decl = "out IntPtr interopOutput, out IntPtr outputSize".format(cls.CSharpType)
        invocation_statement = textwrap.dedent(
            """\
            if (outputSize.ToInt32() == 0)
                \t\t\t\t\treturn new ReadOnlyMemory<char>(string.Empty.ToArray());
            \t\t\t\t\tReadOnlyMemory<char> output;
            \t\t\t\t\tusing (var handler = new TransformedDataSafeHandle(interopOutput, outputSize, DestroyTransformedDataNative))
            \t\t\t\t\t{{
                \t\t\t\t\tbyte[] buffer = new byte[outputSize.ToInt32()];
                \t\t\t\t\tMarshal.Copy(interopOutput, buffer, 0, buffer.Length);
                \t\t\t\t\toutput = new ReadOnlyMemory<char>(Encoding.UTF8.GetString(buffer).ToArray());
            \t\t\t\t\t}}
            """,
        ).format(cls.CSharpType)

        delete_transformed_data = textwrap.dedent(
            """\
            [DllImport("Featurizers", EntryPoint = "{}_string_DestroyTransformedData", CallingConvention = CallingConvention.Cdecl), SuppressUnmanagedCodeSecurity]
            \t\t\t\tprivate static extern bool DestroyTransformedDataNative(IntPtr output, IntPtr outputSize, out IntPtr errorHandle);
            """,
        ).format(featurizer_name)

        return cls.Result(
            decl,
            None,                           # No validation
            invocation_statement,
            "",
            delete_transformed_data,
        )
