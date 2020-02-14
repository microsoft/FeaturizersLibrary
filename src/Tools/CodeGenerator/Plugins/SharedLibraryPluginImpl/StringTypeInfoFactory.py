# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the StringTypeInfoFactory object"""

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
    @classmethod
    @Interface.override
    def GetInputInfo(cls, arg_name, is_optional, invocation_template):
        if is_optional:
            validation = ""
            invocation = invocation_template.format(
                "{name} ? std::string({name}) : nonstd::optional<std::string>()".format(
                    name=arg_name,
                ),
            )

        else:
            validation = """if({name} == nullptr) throw std::invalid_argument("'{name}' is null");""".format(
                name=arg_name,
            )
            invocation = invocation_template.format(arg_name)

        return cls.Result(
            ["/*in*/ char const *{}".format(arg_name)],
            validation,
            invocation,
        )

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetInputBufferInfo(cls, arg_name, is_optional, invocation_template):
        if is_optional:
            validation_suffix = textwrap.dedent(
                """\
                std::vector<nonstd::optional<std::string>> {name}_buffer;

                {name}_buffer.reserve({name}_items);

                char const * const * const {name}_end({name}_ptr + {name}_items);

                while({name}_ptr != {name}_end) {{
                #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
                    {name}_buffer.push_back(*{name}_ptr ? *{name}_ptr : nonstd::optional<std::string>());
                #else
                    {name}_buffer.emplace_back(*{name}_ptr ? *{name}_ptr : nonstd::optional<std::string>());
                #endif
                    ++{name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
            )

        else:
            validation_suffix = textwrap.dedent(
                """\
                std::vector<std::string> {name}_buffer;

                {name}_buffer.reserve({name}_items);

                char const * const * const {name}_end({name}_ptr + {name}_items);

                while({name}_ptr != {name}_end) {{
                #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
                    {name}_buffer.push_back(*{name}_ptr);
                #else
                    {name}_buffer.emplace_back(*{name}_ptr);
                #endif
                    ++{name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
            )

        return cls.Result(
            [
                "/*in*/ char const * const * {name}_ptr".format(
                    name=arg_name,
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
        return cls.Result(
            [
                "/*out*/ char const *{pointer} {name}_ptr".format(
                    name=arg_name,
                    pointer="" if is_struct_member else "*",
                ),
                "/*out*/ std::size_t{pointer} {name}_items".format(
                    name=arg_name,
                    pointer="" if is_struct_member else " *",
                ),
            ],
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr) throw std::invalid_argument("'{name}_ptr' is null");
                if({name}_items == nullptr) throw std::invalid_argument("'{name}_items' is null");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                if({result_name}.empty()) {{
                    {pointer}{name}_ptr = nullptr;
                    {pointer}{name}_items = 0;
                }}
                else {{
                    char * string_buffer(new char[{result_name}.size() + 1]);

                    std::copy({result_name}.begin(), {result_name}.end(), string_buffer);
                    string_buffer[{result_name}.size()] = 0;

                    {pointer}{name}_ptr = string_buffer;
                    {pointer}{name}_items = {result_name}.size();
                }}
                """,
            ).format(
                name=arg_name,
                result_name=result_name,
                pointer="" if is_struct_member else "*",
            ),
        )

    # ----------------------------------------------------------------------
    @classmethod
    @Interface.override
    def GetDestroyOutputInfo(
        cls,
        arg_name="result",
    ):
        return cls.Result(
            [
                "/*in*/ char const *{name}_ptr".format(
                    name=arg_name,
                ),
                "/*in*/ std::size_t {name}_items".format(
                    name=arg_name,
                ),
            ],
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr && {name}_items != 0) throw std::invalid_argument("Invalid buffer");
                if({name}_ptr != nullptr && {name}_items == 0) throw std::invalid_argument("Invalid buffer");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                if({name}_ptr)
                    delete [] {name}_ptr;
                """,
            ).format(
                name=arg_name,
            ),
        )
