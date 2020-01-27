# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the VectorTypeInfoFactory object"""

import os
import re
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
class VectorTypeInfoFactory(TypeInfoFactory):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty(re.compile(r"vector\<(?P<type>\S+)\>"))
    CppType                                 = Interface.DerivedProperty(None)

    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    def __init__(
        self,
        custom_structs=None,
        custom_enums=None,
        member_type=None,
        create_type_info_factory_func=None,
    ):
        if member_type is not None:
            assert create_type_info_factory_func is not None

            match = self.TypeName.match(member_type)
            assert match, member_type

            the_type = match.group("type")

            type_info = create_type_info_factory_func(the_type)
            if not hasattr(type_info, "CType"):
                raise Exception("'{}' is a type that can't be directly expressed in C and therefore cannot be used with a vector".format(the_type))

            self._type_info                 = type_info

            # Override the CppType property with this type info
            self.CppType = "std::tuple<{type} *, {type} *>".format(
                type=self._type_info.CppType,
            )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputInfo(self, arg_name, is_optional, invocation_template):
        if is_optional:
            validation_statements = textwrap.dedent(
                """\
                if({name}_ptr == nullptr && {name}_elements != 0) throw std::invalid_argument("'{name}_elements' is not 0");
                if({name}_ptr != nullptr && {name}_elements == 0) throw std::invalid_argument("'{name}_elements' is 0");
                """,
            ).format(
                name=arg_name,
            )

            invocation_statements = invocation_template.format(
                "{name}_ptr ? std::make_tuple(const_cast<{type} *>({name}_ptr), const_cast<{type} *>({name}_ptr) + {name}_elements) : nonstd::optional<std::tuple<{type} const *, {type} const *>>()".format(
                    type=self._type_info.CType,
                    name=arg_name,
                ),
            )
        else:
            validation_statements = textwrap.dedent(
                """\
                if({name}_ptr == nullptr) throw std::invalid_argument("'{name}_ptr' is null");
                if({name}_elements == 0) throw std::invalid_argument("'{name}_elements' is 0");
                """,
            ).format(
                name=arg_name,
            )

            invocation_statements = invocation_template.format(
                "std::make_tuple(const_cast<{type} *>({name}_ptr), const_cast<{type} *>({name}_ptr) + {name}_elements)".format(
                    type=self._type_info.CType,
                    name=arg_name,
                ),
            )

        return self.Result(
            [
                "/*in*/ {type} const *{name}_ptr".format(
                    type=self._type_info.CType,
                    name=arg_name,
                ),
                "/*in*/ size_t {}_elements".format(arg_name),
            ],
            validation_statements,
            invocation_statements,
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(self, arg_name, is_optional, invocation_template):
        if is_optional:
            raise Exception("Optional vector values are not supported for input buffers")

        return self.Result(
            [
                "/*in*/ {type} const **{name}_values_ptr".format(
                    type=self._type_info.CType,
                    name=arg_name,
                ),
                "/*in*/ size_t const *{}_sizes_ptr".format(arg_name),
                "/*in*/ size_t {}_elements".format(arg_name),
            ],
            textwrap.dedent(
                """\
                if({name}_values_ptr == nullptr) throw std::invalid_argument("'{name}_values_ptr' is null");
                if({name}_sizes_ptr == nullptr) throw std::invalid_argument("'{name}_sizes_ptr' is null");
                if({name}_elements == 0) throw std::invalid_argument("'{name}_elements' is 0");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                std::vector<std::tuple<{type} *, {type} *>> {name}_buffer;

                {name}_buffer.reserve({name}_elements);

                {type} const * const * const {name}_values_end_ptr({name}_values_ptr + {name}_elements);

                while({name}_values_ptr != {name}_values_end_ptr) {{
                    {name}_buffer.emplace_back(const_cast<{type} *>(*{name}_values_ptr), const_cast<{type} *>(*{name}_values_ptr) + *{name}_sizes_ptr);
                    ++{name}_values_ptr;
                    ++{name}_sizes_ptr;
                }}

                {statement}
                """,
            ).format(
                type=self._type_info.CType,
                name=arg_name,
                statement=invocation_template.format(
                    "{name}_buffer.data(), {name}_buffer.size()".format(
                        name=arg_name,
                    ),
                ),
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        arg_name,
        result_name="result",
        is_struct_member=False,
    ):
        return self.Result(
            [
                "/*out*/ {type} **{name}_ptr".format(
                    type=self._type_info.CType,
                    name=arg_name,
                ),
                "/*out*/ size_t *{}_elements".format(arg_name),
            ],
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr) throw std::invalid_argument("'{name}_ptr' is null");
                if({name}_elements == nullptr) throw std::invalid_argument("'{name}_elements' is null");
                """,
            ).format(
                name=arg_name,
            ),
            # TODO: This code is assuming a result type of std::vector which
            #       will likely change in the future. This code will have to be
            #       updated when that change is made.
            textwrap.dedent(
                """\
                if({result_name}.empty()) {{
                    {pointer}{name}_ptr = nullptr;
                    {pointer}{name}_elements = 0;
                }}
                else {{
                    struct {name}Internal {{
                        static void Deleter({type} *pData) {{
                            delete [] pData;
                        }}
                    }};

                    std::unique_ptr<{type}, void (*)({type} *)> pBuffer(new {type}[{result_name}.size()], {name}Internal::Deleter);
                    {type} * ptr(pBuffer.get());

                    for(auto &value : {result_name})
                        *ptr++ = std::move(value);

                    {pointer}{name}_ptr = pBuffer.release();
                    {pointer}{name}_elements = {result_name}.size();
                }}
                """,
            ).format(
                type=self._type_info.CType,
                name=arg_name,
                result_name=result_name,
                pointer="" if is_struct_member else "*",
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        return self.Result(
            [
                "/*in*/ {type} *{name}_ptr".format(
                    type=self._type_info.CType,
                    name=arg_name,
                ),
                "/*in*/ size_t {}_elements".format(arg_name),
            ],
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr && {name}_elements != 0) throw std::invalid_argument("Invalid buffer");
                if({name}_ptr != nullptr && {name}_elements == 0) throw std::invalid_argument("Invalid buffer");
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
