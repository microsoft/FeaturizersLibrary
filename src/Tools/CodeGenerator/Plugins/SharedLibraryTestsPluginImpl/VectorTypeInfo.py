# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the VectorTypeInfo object"""

import os
import re
import textwrap

import six

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryTestsPluginImpl.TypeInfo import TypeInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class VectorTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty(re.compile(r"vector\<(?P<type>\S+)\>"))
    CppType                                 = Interface.DerivedProperty(None)

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    def __init__(
        self,
        *args,
        member_type=None,
        create_type_info_func=None,
        **kwargs
    ):
        if member_type is None:
            return

        assert create_type_info_func is not None

        super(VectorTypeInfo, self).__init__(*args, **kwargs)

        match = self.TypeName.match(member_type)
        assert match, member_type

        the_type = match.group("type")

        type_info = create_type_info_func(the_type)
        assert type_info, the_type

        # The content is expressed by a range of pointers
        self._type_info             = type_info
        self.CppType                = "std::tuple<{type} const *, {type} const *>".format(
            type=self._type_info.CppType,
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        input_name="input",
    ):
        if self.IsOptional:
            statement = "{input}.empty() ? nullptr : {input}.data(), {input}.empty() ? 0 : {input}.size()".format(
                input=input_name,
                type=self._type_info.CppType,
            )
        else:
            statement = "{input_name}.data(), {input_name}.size()".format(
                input_name=input_name,
            )

        return statement

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        result_name="result",
    ):
        result = self._type_info.GetOutputInfo(result_name)
        assert len(result.TransformVars) == 1, result.TransformVars

        parameters = [self.Type("{}*".format(p.Type), "{}_ptr".format(p.Name)) for p in result.TransformVars]
        parameters.append(self.Type("size_t", "{}_items".format(result_name)))

        assert len(parameters) == 2, parameters

        if "nonstd::optional" in result.VectorResultType:


            statements = textwrap.dedent(
                """\
                // Convert the pointers into optional values
                {{
                    std::vector<{type}> temp;

                    temp.reserve({parameter1_name});

                    for({parameter0_type}ptr = {parameter0_name}; ptr != {parameter0_name} + {parameter1_name}; ++ptr) {{
                        if(*ptr != nullptr)
                            temp.emplace_back(std::move(**ptr));
                        else
                            temp.emplace_back({type}());
                    }}

                    results.emplace_back(std::move(temp));
                }}
                """,
            ).format(
                result_name=result_name,
                type=result.VectorResultType,
                parameter0_type=parameters[0].Type,
                parameter0_name=parameters[0].Name,
                parameter1_name=parameters[1].Name,
            )
        else:
            statements = textwrap.dedent(
                """\
                results.emplace_back(std::vector<{type}>({result_name}_ptr, {result_name}_ptr + {result_name}_items));
                """,
            ).format(
                type=result.VectorResultType,
                result_name=result_name,
            )

        return self.Result(
            "std::vector<{}>".format(result.VectorResultType),
            parameters,
            ", ".join(["&{}".format(p.Name) for p in parameters]),
            statements,
            "{}, {}".format(parameters[0].Name, parameters[1].Name),
            destroy_inline=True,
        )
