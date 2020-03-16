# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the VectorTypeInfo object"""

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
class VectorTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty(re.compile(r"vector\<(?P<type>\S+)\>"))
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
        **kwargs
    ):
        if member_type is not None:
            assert create_type_info_func is not None

            super(VectorTypeInfo, self).__init__(*args, **kwargs)

            match = self.TypeName.match(member_type)
            assert match, member_type

            the_type = match.group("type")

            type_info = create_type_info_func(the_type)
            if not hasattr(type_info, "CType"):
                raise Exception("'{}' is a type that can't be directly expressed in C and therefore cannot be used with a vector".format(the_type))

            if type_info.IsOptional:
                raise Exception("Vector types do not currently support optional values ('{}')".format(the_type))

            self._type_info                 = type_info

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        input_name="input",
    ):
        if self.IsOptional:
            statement = "{input}.empty() ? nullptr : {input}.data(), {input}.empty() ? 0 : {input}.size()".format(
                input=input_name,
                type=self._type_info.CppType,
            )
        else:
            statement = "{input_name}.data(), {input_name}.size()".format(
                input_name=input_name,
            )

        return statement

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        result_name="result",
    ):
        return self.Result(
            "std::vector<{}>".format(self._type_info.CppType),
            textwrap.dedent(
                """\
                {type} * {result_name}_ptr(nullptr);
                std::size_t {result_name}_elements(0);
                """,
            ).format(
                type=self._type_info.CppType,
                result_name=result_name,
            ),
            "&{result_name}_ptr, &{result_name}_elements".format(
                result_name=result_name,
            ),
            textwrap.dedent(
                """\
                #if (defined __apple_build_version__ || defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 8)))
                results.push_back(std::vector<{type}>({result_name}_ptr, {result_name}_ptr + {result_name}_elements));
                #else
                results.emplace_back(std::vector<{type}>({result_name}_ptr, {result_name}_ptr + {result_name}_elements));
                #endif
                """,
            ).format(
                type=self._type_info.CppType,
                result_name=result_name,
            ),
            "{result_name}_ptr, {result_name}_elements".format(
                result_name=result_name,
            ),
            destroy_inline=True,
        )
