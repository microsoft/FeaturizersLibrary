# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the MatrixTypeInfo object"""

import os
import re
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
class MatrixTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty(re.compile(r"matrix\<(?P<type>\S+)\>"))
    CppType                                 = Interface.DerivedProperty(None)

    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    def __init__(
        self,
        *args,
        member_type=None,
        create_type_info_func=None,
        **kwargs,
    ):
        if member_type is not None:
            assert create_type_info_func is not None

            super(MatrixTypeInfo, self).__init__(*args, **kwargs)

            match = self.TypeName.match(member_type)
            assert match, member_type

            the_type = match.group("type")

            type_info = create_type_info_func(the_type)
            if not hasattr(type_info, "CType"):
                raise Exception("'{}' is a type that can't be directly expressed in C and therefore cannot be used with a vector".format(the_type))

            if type_info.IsOptional:
                raise Exception("Matrix types do not currently support optional values ('{}')".format(the_type))

            self._type_info                 = type_info

            # Override the CppType property with this type info
            self._matrix_type               = "Eigen::MatrixX<{}>".format(self._type_info.CType);
            self._map_type                  = "Eigen::Map<{}>".format(self._matrix_type)

            self.CppType                    = self._map_type

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputInfo(self, arg_name, invocation_template):
        if self.IsOptional:
            raise Exception("Optional matrix values are not supported")

        return self.Result(
            [
                "/*in*/ size_t {}_cols".format(arg_name),
                "/*in*/ size_t {}_rows".format(arg_name),
                "/*in*/ {type} const * {name}_ptr".format(
                    type=self._type_info.CType,
                    name=arg_name,
                ),
            ],
            textwrap.dedent(
                """\
                if({name}_cols == 0) throw std::invalid_argument("'{name}_cols' is 0");
                if({name}_rows == 0) throw std::invalid_argument("'{name}_rows' is 0");
                if({name}_ptr == nullptr) throw std::invalid_argument("'{name}_ptr' is null");
                """,
            ).format(
                name=arg_name,
            ),
            invocation_template.format(
                "{map_type}(const_cast<{type} *>({name}_ptr), static_cast<Eigen::Index>({name}_rows), static_cast<Eigen::Index>({name}_cols))".format(
                    name=arg_name,
                    type=self._type_info.CType,
                    map_type=self._map_type,
                ),
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(self, arg_name, invocation_template):
        if self.IsOptional:
            raise Exception("Optional matrix values are not supported")

        return self.Result(
            [
                "/*in*/ size_t {}_cols".format(arg_name),
                "/*in*/ size_t {}_rows".format(arg_name),
                "/*in*/ {type} const **{name}_values_ptr".format(
                    type=self._type_info.CType,
                    name=arg_name,
                ),
                "/*in*/ size_t {}_elements".format(arg_name),
            ],
            textwrap.dedent(
                """\
                if({name}_cols == 0) throw std::invalid_argument("'{name}_cols' is 0");
                if({name}_rows == 0) throw std::invalid_argument("'{name}_rows' is 0");
                if({name}_values_ptr == nullptr) throw std::invalid_argument("'{name}_values_ptr' is null");
                if({name}_elements == 0) throw std::invalid_argument("'{name}_elements' is 0");

                std::vector<{map_type}> {name}_buffer;

                {name}_buffer.reserve({name}_elements);

                {type} const * const * const {name}_values_end({name}_values_ptr + {name}_elements);

                while({name}_values_ptr != {name}_values_end) {{
                #if (defined __apple_build_verion__)
                    {name}_buffer.push_back({map_type}(const_cast<{type} *>(*{name}_values_ptr), static_cast<Eigen::Index>({name}_rows), static_cast<Eigen::Index>({name}_cols)));
                #else
                    {name}_buffer.emplace_back({map_type}(const_cast<{type} *>(*{name}_values_ptr), static_cast<Eigen::Index>({name}_rows), static_cast<Eigen::Index>({name}_cols)));
                #endif
                    ++{name}_values_ptr;
                }}
                """,
            ).format(
                name=arg_name,
                map_type=self._map_type,
                matrix_type=self._matrix_type,
                type=self._type_info.CType,
            ),
            invocation_template.format(
                "{name}_buffer.data(), {name}_buffer.size()".format(
                    name=arg_name,
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
                "/*out*/ size_t *{}_cols".format(arg_name),
                "/*out*/ size_t *{}_rows".format(arg_name),
                "/*out*/ {type} **{name}_ptr".format(
                    type=self._type_info.CType,
                    name=arg_name,
                ),
            ],
            textwrap.dedent(
                """\
                if({name}_cols == nullptr) throw std::invalid_argument("'{name}_cols' is null");
                if({name}_rows == nullptr) throw std::invalid_argument("'{name}_rows' is null");
                if({name}_ptr == nullptr) throw std::invalid_argument("'{name}_ptr' is null");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                struct {name}Internal {{
                    static void Deleter({type} *pData) {{
                        delete [] pData;
                    }}
                }};

                std::unique_ptr<{type}, void (*)({type} *)> {name}_buffer(new {type}[static_cast<size_t>({result_name}.size())], {name}Internal::Deleter);

                memcpy({name}_buffer.get(), {result_name}.data(), static_cast<size_t>({result_name}.size()) * sizeof({type}));

                {pointer}{name}_ptr = {name}_buffer.release();
                {pointer}{name}_cols = static_cast<size_t>({result_name}.cols());
                {pointer}{name}_rows = static_cast<size_t>({result_name}.rows());
                """,
            ).format(
                name=arg_name,
                type=self._type_info.CType,
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
                "/*in*/ size_t {}_cols".format(arg_name),
                "/*in*/ size_t {}_rows".format(arg_name),
                "/*in*/ {type} *{name}_ptr".format(
                    type=self._type_info.CType,
                    name=arg_name,
                ),
            ],
            textwrap.dedent(
                """\
                if({name}_ptr == nullptr && ({name}_cols != 0 || {name}_rows != 0)) throw std::invalid_argument("Invalid buffer");
                if({name}_ptr != nullptr && ({name}_cols == 0 || {name}_rows == 0)) throw std::invalid_argument("Invalid buffer");
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
