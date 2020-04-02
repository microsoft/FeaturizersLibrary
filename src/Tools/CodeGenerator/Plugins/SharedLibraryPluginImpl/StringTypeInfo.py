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
            invocation = invocation_template.format("std::string({})".format(arg_name))

        return self.Result(
            [self.Type("char const *", arg_name)],
            validation,
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
            self.Type("char const * const *", "{}_ptr".format(arg_name)),
        ]

        if items_var_name is None:
            items_var_name = "{}_items".format(arg_name)
            parameters.append(self.Type("size_t", items_var_name))

        if self.IsOptional:
            buffer_type = "std::vector<nonstd::optional<std::string>>"

            validation_suffix = textwrap.dedent(
                """\
                {buffer_type} {name}_buffer;

                {name}_buffer.reserve({items_var_name});

                while({name}_buffer.size() < {items_var_name}) {{
                    {name}_buffer.emplace_back(*{name}_ptr ? *{name}_ptr : nonstd::optional<std::string>());
                    ++{name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
                items_var_name=items_var_name,
                buffer_type=buffer_type,
            )

        else:
            # In theory, this could be `std::vector<char const *>`, however there is a lot of code that
            # expects std::string-like functionality. This is an area of potential optimization in the future.
            buffer_type = "std::vector<std::string>"

            validation_suffix = textwrap.dedent(
                """\
                {buffer_type} {name}_buffer;

                {name}_buffer.reserve({items_var_name});

                while({name}_buffer.size() < {items_var_name}) {{
                    {name}_buffer.emplace_back(*{name}_ptr);
                    ++{name}_ptr;
                }}
                """,
            ).format(
                name=arg_name,
                items_var_name=items_var_name,
                buffer_type=buffer_type,
            )

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
        if self.IsOptional:
            statement = textwrap.dedent(
                """\
                if(!{result_name}) {{
                    {pointer}{name} = nullptr;
                }}
                else {{
                    std::string const & {result_name}_temp(*{result_name});
                    char * string_buffer(new char[{result_name}_temp.size() + 1]);

                    std::copy({result_name}_temp.begin(), {result_name}_temp.end(), string_buffer);
                    string_buffer[{result_name}_temp.size()] = 0;

                    {pointer}{name} = string_buffer;
                }}
                """,
            ).format(
                name=arg_name,
                result_name=result_name,
                pointer="" if suppress_pointer else "*",
            )

        else:
            statement = textwrap.dedent(
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
            )

        return self.Result(
            [self.Type("char const *{}".format("" if suppress_pointer else "*"), arg_name),],
            textwrap.dedent(
                """\
                if({name} == nullptr) throw std::invalid_argument("'{name}' is null");
                """,
            ).format(
                name=arg_name,
            ),
            statement,
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
