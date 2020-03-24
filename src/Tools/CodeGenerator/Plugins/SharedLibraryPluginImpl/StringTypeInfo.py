# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the StringTypeInfo object"""

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
class StringTypeInfo(TypeInfo):
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
    def __init__(
        self,
        *args,
        member_type=None,
        create_type_info_func=None,
        **kwargs
    ):
        if member_type is None:
            return

        super(StringTypeInfo, self).__init__(*args, **kwargs)

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputInfo(self, arg_name, invocation_template):
        if self.IsOptional:
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

        return self.Result(
            [self.Type("char const *", arg_name)],
            validation,
            invocation,
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(self, arg_name, invocation_template):
        if self.IsOptional:
            buffer_type = "std::vector<nonstd::optional<std::string>>"

            validation_suffix = textwrap.dedent(
                """\
                {buffer_type} {name}_buffer;

                {name}_buffer.reserve({name}_items);

                while({name}_buffer.size() < {name}_items) {{
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
                buffer_type=buffer_type,
            )

        else:
            # In theory, this could be `std::vector<char const *>`, however there is a lot of code that
            # expects std::string-like functionality. This is an area of potential optimization in the future.
            buffer_type = "std::vector<std::string>"

            validation_suffix = textwrap.dedent(
                """\
                {buffer_type} {name}_buffer;

                {name}_buffer.reserve({name}_items);

                while({name}_buffer.size() < {name}_items) {{
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
                buffer_type=buffer_type,
            )

        return self.Result(
            [
                self.Type("char const * const *", "{}_ptr".format(arg_name)),
                self.Type("size_t", "{}_items".format(arg_name)),
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
        return self.Result(
            [self.Type("char const *{}".format("" if suppress_pointer else "*"), arg_name),],
            textwrap.dedent(
                """\
                if({name} == nullptr) throw std::invalid_argument("'{name}' is null");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                if({result_name}.empty()) {{
                    {pointer}{name} = nullptr;
                }}
                else {{
                    char * string_buffer(new char[{result_name}.size() + 1]);

                    std::copy({result_name}.begin(), {result_name}.end(), string_buffer);
                    string_buffer[{result_name}.size()] = 0;

                    {pointer}{name} = string_buffer;
                }}
                """,
            ).format(
                name=arg_name,
                result_name=result_name,
                pointer="" if suppress_pointer else "*",
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        return self.Result(
            [self.Type("char const *", arg_name)],
            "",
            textwrap.dedent(
                """\
                if({name})
                    delete [] {name};
                """,
            ).format(
                name=arg_name,
            ),
        )
