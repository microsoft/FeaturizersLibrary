# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the StringTypeInfo object"""

import os
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryTestsPluginImpl.TypeInfo import TypeInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class StringTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty("string")
    CppType                                 = Interface.DerivedProperty("std::string")
    CType                                   = "char const *"

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        input_name="input",
    ):
        if self.IsOptional:
            return "Microsoft::Featurizer::Traits<nonstd::optional<std::string>>::IsNull({input_name}) ? nullptr : {input_name}->c_str()".format(
                input_name=input_name,
            )

        return "{}.c_str()".format(input_name)

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputBufferArgs(
        self,
        input_name='input',
    ):
        raise NotImplementedError("Not implemented yet")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        invocation_template,
        result_name="result",
    ):
        if self.IsOptional:
            vector_type = "nonstd::optional<std::string>"
            statement = "{result}_ptr ? std::string({result}_ptr) : nonstd::optional<std::string>()".format(
                result=result_name,
            )
        else:
            vector_type = "std::string"
            statement = "{result}_ptr ? std::string({result}_ptr) : std::string()".format(
                result=result_name,
            )

        return self.Result(
            vector_type,
            [self.Type("char const *", "{}_ptr".format(result_name))],
            invocation_template.format(statement),
            "{}_ptr".format(result_name),
            destroy_inline=True,
        )
