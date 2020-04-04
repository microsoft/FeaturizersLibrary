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
        if member_type is None:
            return

        assert create_type_info_func is not None

        super(MatrixTypeInfo, self).__init__(*args, **kwargs)

        match = self.TypeName.match(member_type)
        assert match, member_type

        the_type = match.group("type")

        type_info = create_type_info_func(the_type)
        if not hasattr(type_info, "CType"):
            raise Exception("'{}' is a type that can't be directly expressed in C and therefore cannot be used with a vector".format(the_type))

        if type_info.IsOptional:
            # Support optional floats and doubles, as the optionality is built directly into the type itself
            if type_info.CType not in ["float", "double"]:
                raise Exception("Matrix types do not currently support optional values ('{}')".format(the_type))

        self._type_info                 = type_info

        # Override the CppType property with this type info
        self._matrix_type               = "Microsoft::Featurizer::RowMajMatrix<{}>".format(self._type_info.CppType);
        self._map_type                  = "Eigen::Map<{}>".format(self._matrix_type)

        self.CppType                    = self._map_type

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputInfo(self, arg_name, invocation_template):
        if self.IsOptional:
            raise Exception("Optional matrix values are not supported")

        return self.Result(
            [
                self.Type("size_t", "{}_cols".format(arg_name)),
                self.Type("size_t", "{}_rows".format(arg_name)),
                self.Type("{} const *".format(self._type_info.CType), "{}_ptr".format(arg_name)),
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
    def GetInputBufferInfo(
        self,
        arg_name,
        invocation_template,
        items_var_name=None,
    ):
        if self.IsOptional:
            raise Exception("Optional matrix values are not supported")

        parameters = [
            self.Type("size_t const *", "{}_cols_ptr".format(arg_name)),
            self.Type("size_t const *", "{}_rows_ptr".format(arg_name)),
            self.Type("{} const **".format(self._type_info.CType), "{}_values_ptr".format(arg_name)),
        ]

        if items_var_name is None:
            items_var_name = "{}_items".format(arg_name)
            parameters.append(self.Type("size_t", items_var_name))

        return self.Result(
            parameters,
            textwrap.dedent(
                """\
                if({name}_cols_ptr == nullptr) throw std::invalid_argument("'{name}_cols_ptr' is nullptr");
                if({name}_rows_ptr == nullptr) throw std::invalid_argument("'{name}_rows_ptr' is nullptr");
                if({name}_values_ptr == nullptr) throw std::invalid_argument("'{name}_values_ptr' is null");
                if({items_var_name} == 0) throw std::invalid_argument("'{items_var_name}' is 0");

                std::vector<{map_type}> {name}_buffer;

                {name}_buffer.reserve({items_var_name});

                while({name}_buffer.size() < {items_var_name}) {{
                    if(*{name}_cols_ptr == 0) throw std::invalid_argument("Invalid col element");
                    if(*{name}_rows_ptr == 0) throw std::invalid_argument("Invalid row element");
                    if(*{name}_values_ptr == nullptr) throw std::invalid_argument("Invalid values element");

                    {name}_buffer.emplace_back({map_type}(const_cast<{type} *>(*{name}_values_ptr), static_cast<Eigen::Index>(*{name}_rows_ptr), static_cast<Eigen::Index>(*{name}_cols_ptr)));

                    ++{name}_cols_ptr;
                    ++{name}_rows_ptr;
                    ++{name}_values_ptr;
                }}
                """,
            ).format(
                name=arg_name,
                items_var_name=items_var_name,
                map_type=self._map_type,
                matrix_type=self._matrix_type,
                type=self._type_info.CType,
            ),
            invocation_template.format(
                "{name}_buffer.data(), {name}_buffer.size()".format(
                    name=arg_name,
                ),
            ),
            input_buffer_type=self.Type("std::vector<{}>".format(self._map_type), "{}_buffer".format(arg_name)),
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
            [
                self.Type("size_t *", "{}_cols".format(arg_name)),
                self.Type("size_t *", "{}_rows".format(arg_name)),
                self.Type("{} **".format(self._type_info.CType), "{}_ptr".format(arg_name)),
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
            [
                self.Type("size_t", "{}_cols".format(arg_name)),
                self.Type("size_t", "{}_rows".format(arg_name)),
                self.Type("{} const *".format(self._type_info.CType), "{}_ptr".format(arg_name)),
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
