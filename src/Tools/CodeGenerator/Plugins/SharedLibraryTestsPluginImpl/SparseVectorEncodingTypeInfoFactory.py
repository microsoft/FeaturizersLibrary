# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the SparseVectorEncodingTypeInfoFactory object"""

import os
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
            "Microsoft::Featurizer::Featurizers::SparseVectorEncoding<{}>".format(self._type.CppType),
            textwrap.dedent(
                """\
                uint64_t numElements(0);
                uint64_t numValues(0);
                {type} * pValues(nullptr);
                uint64_t *pIndexes(nullptr);
                """,
            ).format(
                type=self._type.CppType,
            ),
            "&numElements, &numValues, &pValues, &pIndexes",
            textwrap.dedent(
                """\
                std::vector<typename Microsoft::Featurizer::Featurizers::SparseVectorEncoding<{type}>::ValueEncoding> encodings;
                {type} const *pValue(pValues);
                uint64_t const *pIndex(pIndexes);

                while(numValues--) {{
                    encodings.emplace_back(*pValue++, *pIndex++);
                }}

                results.emplace_back(numElements, std::move(encodings));
                """
            ).format(
                type=self._type.CppType
            ),
            "numElements, numValues, pValues, pIndexes",
            destroy_inline=True,
        )
