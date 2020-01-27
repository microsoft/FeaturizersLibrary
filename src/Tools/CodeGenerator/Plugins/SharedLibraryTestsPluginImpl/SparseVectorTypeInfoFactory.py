# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the SparseVectorTypeInfoFactory object"""

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
class SparseVectorTypeInfoFactory(TypeInfoFactory):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty(re.compile(r"sparse_vector\<(?P<type>\S+)\>"))
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
            assert create_type_info_factory_func

            match = self.TypeName.match(member_type)
            assert match, member_type

            the_type = match.group("type")

            type_info = create_type_info_factory_func(the_type)
            if not hasattr(type_info, "CType"):
                raise Exception("'{}' is a type that can't be directly expressed in C and therefore cannot be used with a sparse_vector".format(the_type))

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
            "Microsoft::Featurizer::Featurizers::SparseVectorEncoding<{}>".format(self._type_info.CppType),
            textwrap.dedent(
                """\
                uint64_t numElements(0);
                uint64_t numValues(0);
                {type} * pValues(nullptr);
                uint64_t *pIndexes(nullptr);
                """,
            ).format(
                type=self._type_info.CppType,
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
                type=self._type_info.CppType
            ),
            "numElements, numValues, pValues, pIndexes",
            destroy_inline=True,
        )
