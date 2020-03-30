# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Contains the TupleTypeInfo object"""

import os
import re
import textwrap

import CommonEnvironment
from CommonEnvironment import Interface

from Plugins.SharedLibraryTestsPluginImpl.TypeInfo import TypeInfo
from Plugin import GetTemplateArgs

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
@Interface.staticderived
class TupleTypeInfo(TypeInfo):
    # ----------------------------------------------------------------------
    # |
    # |  Public Types
    # |
    # ----------------------------------------------------------------------
    TypeName                                = Interface.DerivedProperty(re.compile(r"tuple\<(?P<types>.+)\>"))
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
        if member_type is None:
            return

        assert create_type_info_func is not None

        super(TupleTypeInfo, self).__init__(*args, **kwargs)

        match = self.TypeName.match(member_type)
        assert match, member_type

        type_infos = []

        for type_ in GetTemplateArgs(match.group("types")):
            type_info = create_type_info_func(type_)
            assert type_info, type_

            type_infos.append(type_info)

        self._type_infos                    = type_infos
        self._create_type_info_func         = create_type_info_func

        # Override the CppType property with this type info
        self.CppType                        = "std::tuple<{}>".format(
            ", ".join([ type_info.CppType for type_info in self._type_infos ]),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetTransformInputArgs(
        self,
        input_name="input",
    ):
        parameters = []
        prefix_statements = []

        for index, type_info in enumerate(self._type_infos):
            result = type_info.GetTransformInputArgs("{}{}".format(input_name, index))

            these_prefix_statements = "auto const & {name}{index}(std::get<{index}>({name}));".format(
                name=input_name,
                index=index,
            )

            if isinstance(result, tuple):
                these_prefix_statements += "\n\n{}\n".format(result[1].rstrip())
                result = result[0]

            parameters.append(result)
            prefix_statements.append(these_prefix_statements)

        return (
            ", ".join(parameters),
            "\n".join(prefix_statements),
        )

    # ----------------------------------------------------------------------
    @Interface.override
    def GetOutputInfo(
        self,
        result_name="result",
    ):
        return self.Result(
            "BugBug1",
            [self.Type("BugBug2,1", "BugBug2.2")],
            "BugBug3",
            "BugBug4",
            "BugBug5",
            destroy_inline=True,
        )
