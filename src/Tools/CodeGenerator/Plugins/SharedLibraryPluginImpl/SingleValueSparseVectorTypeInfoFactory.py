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

from Plugins.SharedLibraryPluginImpl.TypeInfoFactory import TypeInfoFactory

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
    def GetInputInfo(self, arg_name, is_optional, invocation_template):
        raise NotImplementedError("This structure is only used during output")

    # ----------------------------------------------------------------------
    @Interface.override
    def GetInputBufferInfo(self, arg_name, is_optional, invocation_template):
        raise NotImplementedError("This structure is only used during output")

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
                "/*out*/ uint64_t * {}_numElements".format(arg_name),
                "/*out*/ {} *{}_value".format(self._type_info.CType, arg_name),
                "/*out*/ uint64_t *{}_index".format(arg_name),
            ],
            textwrap.dedent(
                """\
                if({name}_numElements == nullptr) throw std::invalid_argument("'{name}_numElements' is null");
                if({name}_value == nullptr) throw std::invalid_argument("'{name}_value' is null");
                if({name}_index == nullptr) throw std::invalid_argument("'{name}_index' is null");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                {pointer}{name}_numElements = {result}.NumElements;
                {pointer}{name}_value = {result}.Value;
                {pointer}{name}_index = {result}.Index;
                """,
            ).format(
                name=arg_name,
                result=result_name,
                pointer="" if is_struct_member else "*",
            ),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetDestroyOutputInfo(
        self,
        arg_name="result",
    ):
        return None
