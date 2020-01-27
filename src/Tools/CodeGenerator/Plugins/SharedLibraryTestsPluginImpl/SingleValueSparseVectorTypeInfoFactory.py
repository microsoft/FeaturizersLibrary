# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the SingleValueSparseVectorTypeInfoFactory object"""

import os
import re
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryTestsPluginImpl.TypeInfoFactory import TypeInfoFactory

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
#  ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class SingleValueSparseVectorTypeInfoFactory(TypeInfoFactory):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty(re.compile(r"single_value_sparse_vector\<(?P<type>\S+)\>"))
    CppType                                 = Interface.DerivedProperty(None)

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
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
                raise Exception("'{}' is a type that can't be directly expressed in C and therefore cannot be used with a single_value_sparse_vector".format(the_type))

            self._type_info                 = type_info

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        is_input_optional,
        input_name="input",
    ):
        raise NotImplementedError("This structure is only used during output")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        result_name="result",
    ):
        return self.Result(
            "Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<{}>".format(self._type_info.CppType),
            textwrap.dedent(
                """\
                uint64_t {result}_numElements(0);
                {type} {result}_value;
                uint64_t {result}_index(0);
                """,
            ).format(
                type=self._type_info.CppType,
                result=result_name,
            ),
            "&{result}_numElements, &{result}_value, &{result}_index".format(
                result=result_name,
            ),
            textwrap.dedent(
                """\
                #if (defined __apple_build_version__)
                results.push_back(Microsoft::Featurizer::Featurizers::SingleValueSparseVectorEncoding<{type}>({result}_numElements, {result}_value, {result}_index));
                #else
                results.emplace_back({result}_numElements, {result}_value, {result}_index);
                #endif
                """,
            ).format(
                result=result_name,
                type=self._type_info.CppType,
            ),
            None,
        )
