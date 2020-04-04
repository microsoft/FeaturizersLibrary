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

from Plugins.SharedLibraryTestsPluginImpl.TypeInfo import TypeInfo

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
    # |  Public Methods
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
        self.CppType                    = "Microsoft::Featurizer::RowMajMatrix<{}>".format(self._type_info.CppType)

    # ----------------------------------------------------------------------
    @Interface.override
    @staticmethod
    def CreateHelperMethods(output_stream):
        output_stream.write(
            textwrap.dedent(
                """\
                template <typename T>
                Microsoft::Featurizer::RowMajMatrix<T> CreateMatrix(size_t numCols, size_t numRows, T *pData) {
                    if(numCols == 0) throw std::invalid_argument("numCols");
                    if(numRows == 0) throw std::invalid_argument("numRows");
                    if(pData == nullptr) throw std::invalid_argument("pData");

                    Microsoft::Featurizer::RowMajMatrix<T> result(numRows, numCols);

                    for(size_t row = 0; row < numRows; ++row) {
                        for(size_t col = 0; col < numCols; ++col) {
                            result(static_cast<Eigen::Index>(row), static_cast<Eigen::Index>(col)) = *pData++;
                        }
                    }

                    return result;
                }

                """,
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        input_name="input",
    ):
        if self.IsOptional:
            raise Exception("Optional matrix values are not supported")

        return "static_cast<size_t>({name}.cols()), static_cast<size_t>({name}.rows()), {name}.data()".format(
            name=input_name,
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputBufferArgs(
        self,
        input_name='input',
    ):
        return (
            "{name}_cols_buffer.data(), {name}_rows_buffer.data(), {name}_data_buffer.data(), {name}.size()".format(
                name=input_name,
            ),
            textwrap.dedent(
                """\
                std::vector<size_t> {name}_cols_buffer;
                std::vector<size_t> {name}_rows_buffer;
                std::vector<{type} const *> {name}_data_buffer;

                {name}_cols_buffer.reserve({name}.size());
                {name}_rows_buffer.reserve({name}.size());
                {name}_data_buffer.reserve({name}.size());

                for(auto const & {name}_element : {name}) {{
                    {name}_cols_buffer.emplace_back({name}_element.cols());
                    {name}_rows_buffer.emplace_back({name}_element.rows());
                    {name}_data_buffer.emplace_back({name}_element.data());
                }}
                """,
            ).format(
                name=input_name,
                type=self._type_info.CType,
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        invocation_template,
        result_name="result",
    ):
        return self.Result(
            "Microsoft::Featurizer::RowMajMatrix<{}>".format(self._type_info.CppType),
            [
                self.Type("size_t", "{}_cols".format(result_name)),
                self.Type("size_t", "{}_rows".format(result_name)),
                self.Type("{} *".format(self._type_info.CppType), "{}_ptr".format(result_name)),
            ],
            invocation_template.format(
                "CreateMatrix({name}_cols, {name}_rows, {name}_ptr)".format(
                    type=self._type_info.CppType,
                    name=result_name,
                ),
            ),
            "{name}_cols, {name}_rows, {name}_ptr".format(
                name=result_name,
            ),
            destroy_inline=True,
        )
