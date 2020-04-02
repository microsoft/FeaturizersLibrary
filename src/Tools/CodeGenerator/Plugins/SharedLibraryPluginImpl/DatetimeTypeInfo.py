# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the DateTimeTypeInfo object"""

import os
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryPluginImpl.TypeInfo import TypeInfo

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class DateTimeTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty("datetime")
    CppType                                 = Interface.DerivedProperty("std::chrono::system_clock::time_point")

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputInfo(self, arg_name, invocation_template):
        if self.IsOptional:
            param_decorator = "const *"
            invocation = invocation_template.format(
                "{name} ? CreateDateTime({name}) : nonstd::optional<{cpp_type}>()".format(
                    name=arg_name,
                    cpp_type=self.CppType,
                ),
            )
        else:
            param_decorator = ""
            invocation = invocation_template.format(
                "CreateDateTime({name})".format(
                    name=arg_name,
                ),
            )

        return self.Result(
            [
                self.Type("DateTimeParameter {}".format(param_decorator), arg_name),
            ],
            "", # No validation
            invocation,
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(
        self,
        arg_name,
        invocation_template,
        items_var_name=None,
    ):
        parameters = [
            # The type will be filled in below
            self.Type(None, "{}_ptr".format(arg_name)),
        ]

        if items_var_name is None:
            items_var_name = "{}_items".format(arg_name)
            parameters.append(self.Type("size_t", items_var_name))

        if self.IsOptional:
            param_decorator = "const *"
            validation_suffix = textwrap.dedent(
                """\
                std::vector<nonstd::optional<{cpp_type}>> {name}_buffer;

                {name}_buffer.reserve({items_var_name}};

                while({name}_buffer.size() < {items_var_name}) {{
                    {name}_buffer.emplace_back(*{name}_ptr ? CreateDateTime(**{name}_ptr) : nonstd::optional<{cpp_type}>());
                    ++{name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
                items_var_name=items_var_name,
                cpp_type=self.CppType,
            )

            buffer_type = "std::vector<nonstd::optional<{}>>".format(self.CppType)

        else:
            param_decorator = ""
            validation_suffix = textwrap.dedent(
                """\
                std::vector<{cpp_type}> {name}_buffer;

                {name}_buffer.reserve({items_var_name});

                DateTimeParameter const * const {name}_end({name}_ptr + {items_var_name});

                while({name}_ptr != {name}_end) {{
                    {name}_buffer.emplace_back(CreateDateTime(*{name}_ptr));
                    ++{name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
                items_var_name=items_var_name,
                cpp_type=self.CppType,
            )

            buffer_type = "std::vector<{}>".format(self.CppType)

        parameters[0].Type = "DateTimeParameter const * {}".format(param_decorator)

        return self.Result(
            parameters,
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr) throw std::invalid_argument("'{name}_ptr' is null");
                if({items_var_name} == 0) throw std::invalid_argument("'{items_var_name}' is 0");
                {validation_suffix}
                """,
            ).format(
                name=arg_name,
                items_var_name=items_var_name,
                validation_suffix="\n{}\n".format(
                    validation_suffix,
                ) if validation_suffix else "",
            ),
            invocation_template.format(
                "{name}_buffer.data(), {name}_buffer.size()".format(
                    name=arg_name,
                ),
            ),
            input_buffer_type=self.Type(buffer_type, "{}_buffer".format(arg_name)),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        arg_name,
        result_name="result",
        suppress_pointer=False,
    ):
        raise NotImplemented("Not implemented yet")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        raise NotImplemented("Not implemented yet")
