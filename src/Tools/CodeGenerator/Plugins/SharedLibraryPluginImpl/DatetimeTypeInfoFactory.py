# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the DateTimeTypeInfoFactory object"""

import os
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryPluginImpl.TypeInfoFactory import TypeInfoFactory

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class DateTimeTypeInfoFactory(TypeInfoFactory):
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
    @classmethod
    @Interface.override
    def GetInputInfo(cls, arg_name, is_optional, invocation_template):
        if is_optional:
            param_decorator = "const *"
            invocation = invocation_template.format(
                "{name} ? CreateDateTime({name}) : nonstd::optional<{cpp_type}>()".format(
                    name=arg_name,
                    cpp_type=cls.CppType,
                ),
            )
        else:
            param_decorator = ""
            invocation = invocation_template.format(
                "CreateDateTime({name})".format(
                    name=arg_name,
                ),
            )

        return cls.Result(
            [
                "/*in*/ DateTimeParameter {param_decorator}{name}".format(
                    name=arg_name,
                    param_decorator=param_decorator,
                ),
            ],
            "", # No validation
            invocation,
        )

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetInputBufferInfo(cls, arg_name, is_optional, invocation_template):
        if is_optional:
            param_decorator = "const *"
            validation_suffix = textwrap.dedent(
                """\
                std::vector<nonstd::optional<{cpp_type}>> {name}_buffer;

                {name}_buffer.reserve({name}_items};

                DateTimeParameter const * const * const {name}_end({name}_ptr + {name}_items);

                while({name}_ptr != {name}_end) {{
                #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
                    {name}_buffer.push_back(*{name}_ptr ? CreateDateTime(**{name}_ptr) : nonstd::optional<{cpp_type}>());
                #else
                    {name}_buffer.emplace_back(*{name}_ptr ? CreateDateTime(**{name}_ptr) : nonstd::optional<{cpp_type}>());
                #endif
                    ++{name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
                cpp_type=cls.CppType,
            )

        else:
            param_decorator = ""
            validation_suffix = textwrap.dedent(
                """\
                std::vector<{cpp_type}> {name}_buffer;

                {name}_buffer.reserve({name}_items);

                DateTimeParameter const * const {name}_end({name}_ptr + {name}_items);

                while({name}_ptr != {name}_end) {{
                #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
                    {name}_buffer.push_back(CreateDateTime(*{name}_ptr));
                #else
                    {name}_buffer.emplace_back(CreateDateTime(*{name}_ptr));
                #endif
                    ++{name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
                cpp_type=cls.CppType,
            )

        return cls.Result(
            [
                "/*in*/ DateTimeParameter const * {param_decorator}{name}_ptr".format(
                    name=arg_name,
                    param_decorator=param_decorator,
                ),
                "/*in*/ std::size_t {name}_items".format(
                    name=arg_name,
                ),
            ],
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr) throw std::invalid_argument("'{name}_ptr' is null");
                if({name}_items == 0) throw std::invalid_argument("'{name}_items' is 0");
                {validation_suffix}
                """,
            ).format(
                name=arg_name,
                validation_suffix="\n{}\n".format(
                    validation_suffix,
                ) if validation_suffix else "",
            ),
            invocation_template.format(
                "{name}_buffer.data(), {name}_buffer.size()".format(
                    name=arg_name,
                ),
            ),
        )

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetOutputInfo(
        cls,
        arg_name,
        result_name="result",
        is_struct_member=False,
    ):
        raise NotImplemented("Not implemented yet")

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetDestroyOutputInfo(
        cls,
        arg_name="result",
    ):
        raise NotImplemented("Not implemented yet")
