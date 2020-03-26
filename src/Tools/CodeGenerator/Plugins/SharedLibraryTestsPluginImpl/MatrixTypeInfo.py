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
        self._matrix_type               = "Eigen::MatrixX<{}>".format(self._type_info.CppType);
        self._map_type                  = "Eigen::Map<{}>".format(self._matrix_type)

        self.CppType                    = self._map_type

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
    def GetOutputInfo(
        self,
        result_name="result",
    ):
        return self.Result(
            "Eigen::MatrixX<{}>".format(self._type_info.CppType),
            textwrap.dedent(
                """\
                size_t {name}_cols(0);
                size_t {name}_rows(0);
                {type} * {name}_ptr(nullptr);
                """,
            ).format(
                type=self._type_info.CppType,
                name=result_name,
            ),
            "&{name}_cols, &{name}_rows, &{name}_ptr".format(
                name=result_name,
            ),
            textwrap.dedent(
                """\
                results.emplace_back(Eigen::Map<Eigen::MatrixX<{type}>>({name}_ptr, static_cast<Eigen::Index>({name}_cols), static_cast<Eigen::Index>({name}_rows)));
                """,
            ).format(
                type=self._type_info.CppType,
                name=result_name,
            ),
            "{name}_cols, {name}_rows, {name}_ptr".format(
                name=result_name,
            ),
            destroy_inline=True,
        )
