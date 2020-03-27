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
    def GetOutputInfo(
        self,
        result_name="result",
    ):
        return self.Result(
            "std::string",
            textwrap.dedent(
                """\
                char const * {result_name}_ptr(nullptr);
                """,
            ).format(
                result_name=result_name,
            ),
            "&{result_name}_ptr".format(
                result_name=result_name,
            ),
            textwrap.dedent(
                """\
                results.emplace_back({result}_ptr ? std::string({result}_ptr) : std::string());
                """,
            ).format(
                result=result_name,
            ),
            "{result_name}_ptr".format(
                result_name=result_name,
            ),
            destroy_inline=True,
        )
