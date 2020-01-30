# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the StringTypeInfoFactory object"""

import os
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryTestsPluginImpl.TypeInfoFactory import TypeInfoFactory

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class StringTypeInfoFactory(TypeInfoFactory):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty("string")
    CppType                                 = Interface.DerivedProperty("std::string")

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        is_input_optional,
        input_name="input",
    ):
        if is_input_optional:
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
                std::size_t {result_name}_items(0);
                """,
            ).format(
                result_name=result_name,
            ),
            "&{result_name}_ptr, &{result_name}_items".format(
                result_name=result_name,
            ),
            textwrap.dedent(
                """\
                #if (defined __apple_build_version__)
                results.push_back({result}_ptr ? std::string({result}_ptr) : std::string());
                #else
                results.emplace_back({result}_ptr ? std::string({result}_ptr) : std::string());
                #endif
                """,
            ).format(
                result=result_name,
            ),
            "{result_name}_ptr, {result_name}_items".format(
                result_name=result_name,
            ),
            destroy_inline=True,
        )
