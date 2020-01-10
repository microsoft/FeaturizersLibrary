# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the SparseVectorEncodingTypeInfoFactory object"""

import os
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
class SparseVectorEncodingTypeInfoFactory(TypeInfoFactory):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty("SparseVectorEncoding")
    CppType                                 = Interface.DerivedProperty(None)

    # ----------------------------------------------------------------------
    # |
    # |  Public Methods
    # |
    # ----------------------------------------------------------------------
    def __init__(
        self,
        custom_structs=None,
    ):
        if custom_structs:
            assert self.TypeName in custom_structs, custom_structs
            member_info = custom_structs[self.TypeName]

            if (
                len(member_info) != 1
                or "type" not in member_info
            ):
                raise Exception("'{}' types should have 1 member with the name 'type'".format(self.TypeName))

            the_type = member_info["type"]

            if the_type.TypeName not in ["int8", "int16", "int32", "int64", "uint8", "uint16", "uint32", "uint64", "double", "float", "bool"]:
                raise Exception("'{}' is not an expected type".format(the_type.TypeName))

            self._type                      = the_type

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
                "/*out*/ uint64_t * {}_numValues".format(arg_name),
                "/*out*/ {} **{}_values".format(self._type.CType, arg_name),
                "/*out*/ uint64_t **{}_indexes".format(arg_name),
            ],
            textwrap.dedent(
                """\
                if({name}_numElements == nullptr) throw std::invalid_argument("'{name}_numElements' is null");
                if({name}_numValues == nullptr) throw std::invalid_argument("'{name}_numValues' is null");
                if({name}_values == nullptr) throw std::invalid_argument("'{name}_values' is null");
                if({name}_indexes == nullptr) throw std::invalid_argument("'{name}_indexes' is null");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                std::unique_ptr<{type} []> pValues(new {type} [{result}.Values.size()]);
                std::unique_ptr<uint64_t []> pIndexes(new uint64_t [{result}.Values.size()]);

                {type} * pValue(pValues.get());
                uint64_t * pIndex(pIndexes.get());

                for(auto const & encoding : {result}.Values) {{
                    *pValue++ = encoding.Value;
                    *pIndex++ = encoding.Index;
                }}

                *{name}_numElements = {result}.NumElements;
                *{name}_numValues = {result}.Values.size();

                *{name}_values = pValues.release();
                *{name}_indexes = pIndexes.release();
                """,
            ).format(
                name=arg_name,
                result=result_name,
                type=self._type.CppType,
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
                "/*in*/ uint64_t {}_numElements".format(arg_name),
                "/*in*/ uint64_t {}_numValues".format(arg_name),
                "/*in*/ {} const * {}_values".format(self._type.CType, arg_name),
                "/*in*/ uint64_t const * {}_indexes".format(arg_name),
            ],
            textwrap.dedent(
                """\
                if({name}_numElements == 0) throw std::invalid_argument("'{name}_numElements' is 0");
                if({name}_numValues == 0) throw std::invalid_argument("'{name}_numValues' is 0");
                if({name}_values == nullptr) throw std::invalid_argument("'{name}_values' is null");
                if({name}_indexes == nullptr) throw std::invalid_argument("'{name}_indexes' is null");
                """,
            ).format(
                name=arg_name,
            ),
            textwrap.dedent(
                """\
                delete [] {name}_values;
                delete [] {name}_indexes;
                """,
            ).format(
                name=arg_name,
            ),
        )
